using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Assertions;

public class BattleEnemy : BattleUnit
{
    private BattleSkill basicAttack;

    public BattleEnemy(BattleSquad squad, uint ID, EnemyData.Data enemyData) : base(squad, ID)
    {
        classType = enemyData.classType;
        elementType = enemyData.elementType;

        prefabName = enemyData.prefabName;

        positionType = enemyData.position;

        defaultStatusInfo = new StatusInfo();
        defaultStatusInfo.Hp = enemyData.hp;
        defaultStatusInfo.Def = enemyData.def;
        defaultStatusInfo.Atk = enemyData.atk;

        battleStatus = new BattleStatus(this);
        battleStatus.Hp = enemyData.hp;
        battleStatus.Def = enemyData.def;
        battleStatus.Atk = enemyData.atk;

        battleSkills = new BattleSkill[enemyData.skillIndexes.Length];
        for (uint i = 0; i < enemyData.skillIndexes.Length; ++i)
        {
            SkillData.Data data = DataManager.Instance.FindSkillData(enemyData.skillIndexes[i]);
            Assert.IsNotNull(data);

            BattleSkill battleSkill = new BattleSkill(this, new Skill(data));
            Assert.IsNotNull(battleSkill);
            battleSkills[i] = battleSkill;
            if (battleSkill.ActiveType == SkillActiveType.Automatic)
            {
                basicAttack = battleSkill;
            }
        }
    }

    public override void BasicAttack()
    {
        basicAttack.ExcuteSkill(battleTarget);
    }

    public override void Update()
    {
        if (IsAlive())
        {
            if (battleTarget == null || battleTarget.IsAlive() == false)
            {
                SetUnitState(BattleUnitState.Idle);
            }

            foreach (BattleSkill skill in battleSkills)
            {
                skill.Update();

                if (state == BattleUnitState.Fight && skill.ActiveType == SkillActiveType.Trigger)
                {
                    if (skill.IsUseAble() && registExcuteBattleSkill == null)
                    {
                        PrepareExcuteSkill(skill);
                    }
                }
            }

            battleStatus.Update();
        }
        else
        {
            SetUnitState(BattleUnitState.Die);
        }

        switch (battleStatus.CurrentInfluenceType)
        {
            case BattleInfluenceType.None:
                {
                    switch (state)
                    {
                        case BattleUnitState.MoveToTarget:
                            uiBattleUnit.MoveUnitToPos(battleTarget.UIBattleUnit.transform.position, 1.7f);
                            break;
                    }
                }
                break;
        }
    }
}
