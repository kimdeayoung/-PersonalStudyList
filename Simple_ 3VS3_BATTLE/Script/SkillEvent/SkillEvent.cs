using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Assertions;

public abstract class SkillEvent
{
    protected EventType eventType;

    protected ActionValueType actionValueType;
    protected float value;

    protected string[] stringValues;
    protected float[] floatValues;

    public EventType EventType { get => eventType; }
    public ActionValueType ActionValueType { get => actionValueType; }
    public float Value { get => value; }

    public SkillEvent(EventData.Data data)
    {
        eventType = data.eventType;

        actionValueType = data.valueType;
    }

    public void BindFloatValues(float[] values)
    {
        Assert.IsNotNull(values);

        floatValues = values;
        value = floatValues[0];
    }

    public void BindStringValues(string[] values)
    {
        if (values != null)
        {
            stringValues = values;
        }
    }

    public abstract void ExcuteEvent(BattleUnit caster, BattleUnit[] targetUnits);

    protected int CalculateAttackDamage(BattleUnit caster, BattleUnit target)
    {
        float damage = 0;
        switch (actionValueType)
        {
            case ActionValueType.Direct:
                damage = value - target.BattleStatus.Def;
                break;
            case ActionValueType.Percent:
                damage = caster.BattleStatus.Atk * value - target.BattleStatus.Def;
                break;
        }

        if (damage <= 0)
        {
            damage = 1.0f;
        }
        return Mathf.CeilToInt(damage);
    }

    protected int CalculateHeal(BattleUnit caster, BattleUnit target)
    {
        float heal = 0;
        switch (actionValueType)
        {
            case ActionValueType.Direct:
                heal = value;
                break;
            case ActionValueType.Percent:
                heal = caster.BattleStatus.Atk * value;
                break;
        }

        return Mathf.CeilToInt(heal);
    }
}
