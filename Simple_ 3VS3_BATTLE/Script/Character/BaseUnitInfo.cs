using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public abstract class BaseUnitInfo
{
    protected uint level;

    protected string name;
    protected string prefabName;

    protected StatusInfo defaultStatusInfo;

    protected ClassType classType;
    protected ElementType elementType;

    protected PositionType positionType;

    protected Skill[] skills;

    public uint Level { get => level; }
    public string Name { get => name; }
    public StatusInfo DefaultStatusInfo { get => defaultStatusInfo; }
    public ClassType ClassType { get => classType; }
    public ElementType ElementType { get => elementType; }
    public PositionType PositionType { get => positionType; }
    public string PrefabName { get => prefabName; }
    public Skill[] Skills { get => skills; }
}