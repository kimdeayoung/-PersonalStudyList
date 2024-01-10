using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class StatusInfo
{
    protected int hp;
    protected uint def;
    protected uint atk;

    public StatusInfo()
    {

    }

    public StatusInfo(StatusInfo other)
    {
        hp = other.hp;
        def = other.def;
        atk = other.atk;
    }

    public int Hp { get => hp; set => hp = value; }
    public uint Def { get => def; set => def = value; }
    public uint Atk { get => atk; set => atk = value; }
}
