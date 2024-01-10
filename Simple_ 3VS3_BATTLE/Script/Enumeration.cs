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
    Automatic, // Ư�� �ð��� �ڵ����� Ȱ��ȭ
    Trigger, // ��ư���� Ȱ��ȭ
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