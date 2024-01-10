using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Assertions;

public abstract class BattleUnit : BaseUnitInfo
{
    protected BattleSquad squad;

    protected BattleStatus battleStatus;
    protected BattleSkill[] battleSkills;

    protected uint unitID;
    protected BattleUnitState state;
    protected UIBattleUnit uiBattleUnit;

    protected BattleUnit battleTarget;
    protected BattleSkill registExcuteBattleSkill;

    public BattleUnit(BattleSquad squad, uint ID)
    {
        this.squad = squad;

        unitID = ID;
        state = BattleUnitState.None;
    }

    public BattleSquadType SquadType { get => squad.SquadType; }

    public BattleSkill[] BattleSkills { get => battleSkills; }
    public uint UnitID { get => unitID; }

    protected BattleController Controller { get => squad.Controller; }
    public BattleUnitState State { get => state; }
    public UIBattleUnit UIBattleUnit { get => uiBattleUnit; set => uiBattleUnit = value; }
    public BattleStatus BattleStatus { get => battleStatus; }
    public BattleUnit BattleTarget { get => battleTarget; }

    public abstract void Update();

    public void SetUnitState(BattleUnitState state)
    {
        this.state = state;

        switch (state)
        {
            case BattleUnitState.Idle:
                BattleUnit target = Controller.TargetController.FindBattleTarget(this);
                UIBattleUnit.Idle();
                if (target != null)
                {
                    SetTarget(target);
                }
                break;
            case BattleUnitState.Fight:
                uiBattleUnit.AttackStart();
                break;
            case BattleUnitState.Die:
                uiBattleUnit.UnitDie();
                break;
        }
    }

    public bool IsAlive()
    {
        return battleStatus.Hp > 0;
    }

    public bool IsUnitDieState()
    {
        return state == BattleUnitState.Die;
    }

    public void SetTarget(BattleUnit battleUnit)
    {
        Assert.IsNotNull(battleUnit);
        Assert.IsTrue(SquadType != battleUnit.SquadType);

        battleTarget = battleUnit;

        switch (classType)
        {
            case ClassType.Warrior:
            case ClassType.Tank:
                SetUnitState(BattleUnitState.MoveToTarget);
                break;
            case ClassType.Wizard:
            case ClassType.Sniper:
            case ClassType.Support:
                SetUnitState(BattleUnitState.Fight);
                break;
        }
    }

    public abstract void BasicAttack();

    public void OnTriggerCollider(BattleUnit unit)
    {
        if (state == BattleUnitState.Fight)
        {
            return;
        }

        if (SquadType != unit.SquadType && unit.UnitID == battleTarget.unitID)
        {
            SetUnitState(BattleUnitState.Fight);
        }
    }

    public bool IsUseSkillAble()
    {
        return state == BattleUnitState.Fight;
    }

    public void PrepareExcuteSkill(BattleSkill battleSkill)
    {
        if (battleStatus.CurrentInfluenceType == BattleInfluenceType.None)
        {
            if (battleSkill.IsSameOwner(this))
            {
                registExcuteBattleSkill = battleSkill;
            }
            uiBattleUnit.SkillAttackStart();
        }
    }

    public void ExcuteBattleSkill()
    {
        if (registExcuteBattleSkill != null)
        {
            BattleUnit[] targets = squad.Controller.TargetController.FindSkillTarget(registExcuteBattleSkill);
            registExcuteBattleSkill.ExcuteSkill(targets);
        }
        registExcuteBattleSkill = null;

        SetUnitState(state);
    }

    public void ChangeUnitBattleHp(bool isIncrease, int value)
    {
        if (isIncrease == false)
        {
            value = -value;
        }
        battleStatus.Hp += value;
        ObjectPoolManager.Instance.UseDamageFont(uiBattleUnit.DamageFontStartPos.position, value);

        if (battleStatus.Hp > defaultStatusInfo.Hp)
        {
            battleStatus.Hp = defaultStatusInfo.Hp;
        }
    }

    public void ApplyChangeStateEvent(EventType eventType, float duration)
    {
        switch (eventType)
        {
            case EventType.Stun:
                battleStatus.IncreaseInfluenceData(BattleInfluenceType.Stun, duration);
                break;
        }
    }
}
