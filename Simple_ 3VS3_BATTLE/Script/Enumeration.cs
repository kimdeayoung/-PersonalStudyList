public enum PositionType
{
    Front,
    Mid,
    Back,
    Length,
}

public enum ElementType
{
    Water,
    Fire,
    Earth,
    Light,
    Dark,
    Machine,
}

public enum ClassType
{
    Warrior,
    Tank,
    Wizard,
    Sniper,
    Support,
}

public enum SkillType
{
    Attack,
    Heal,
    Stun,
}

public enum SkillActiveType
{
    Automatic, // 특정 시간에 자동으로 활성화
    Trigger, // 버튼으로 활성화
}

public enum EventType
{
    BasicAttack,
    StrongAttack,
    Heal,
    Stun,
    LongDistanceAttack,
}

public enum BattleInfluenceType
{
    None,
    Stun,
}

public enum ActionValueType
{
    Direct,
    Percent,
}

public enum TargetType
{
    Team_All,
    Enemy_Target,
    Enemy_All,
}

public enum BattleStateType
{
    Enter,
    PrepareProduction,
    Progress,
    Victory,
    Defeat,
}

public enum BattleSquadType
{
    Ally,
    Enemy,
}

public enum BattleUnitState
{
    None,
    Idle,
    MoveToTarget,
    Fight,
    Die,
}