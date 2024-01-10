using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Assertions;

public class BattleCharacter : BattleUnit
{
    private BattleSkill basicAttack;

    public BattleCharacter(BattleSquad squad, uint ID, CharacterInfo charInfo) : base(squad, ID)
    {
        level = charInfo.Level;
        classType = charInfo.ClassType;
        elementType = charInfo.ElementType;

        prefabName = charInfo.PrefabName;

        positionType = charInfo.PositionType;

        defaultStatusInfo = new StatusInfo(charInfo.DefaultStatusInfo);
        battleStatus = new BattleStatus(this, charInfo.DefaultStatusInfo);

        battleSkills = new BattleSkill[charInfo.Skills.Length];
        for (uint i = 0; i < charInfo.Skills.Length; ++i)
        {
            BattleSkill battleSkill = new BattleSkill(this, charInfo.Skills[i]);
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
