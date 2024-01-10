using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Assertions;

public class Skill
{
    private uint index;

    private string icon;

    private SkillType type;
    private SkillActiveType activeType;
    private TargetType targetType;

    private SkillEvent[] events;
    private float activeCoolTime;

    public Skill(SkillData.Data data)
    {
        index = data.index;

        icon = data.icon;
        type = data.type;
        activeType = data.activeType;
        targetType = data.targetType;

        events = new SkillEvent[data.eventDatas.Length];
        for (uint i = 0; i < events.Length; ++i)
        {
            events[i] = CreateSkillEvent(data.eventDatas[i]);
        }
        activeCoolTime = data.activeCoolTime;
    }

    public SkillType Type { get => type; }
    public SkillActiveType ActiveType { get => activeType; }
    public float ActiveCoolTime { get => activeCoolTime; }
    public SkillEvent[] Events { get => events; }
    public string Icon { get => icon; }
    public TargetType TargetType { get => targetType; }

    private SkillEvent CreateSkillEvent(SkillData.Data.EventData data)
    {
        EventData.Data eventData = DataManager.Instance.FindEventData(data.eventIndex);
        Assert.IsNotNull(eventData);

        SkillEvent skillEvent = null;
        switch (eventData.eventType)
        {
            case EventType.BasicAttack:
            case EventType.StrongAttack:
                skillEvent = new SkillEventAttack(eventData);
                break;
            case EventType.Heal:
                skillEvent = new SkillEventHeal(eventData);
                break;
            case EventType.LongDistanceAttack:
                skillEvent = new SkillEventLongDistanceAttack(eventData);
                break;
            case EventType.Stun:
                skillEvent = new SkillEventStun(eventData);
                break;
        }
        skillEvent.BindStringValues(data.bindStringValues);
        skillEvent.BindFloatValues(data.bindFloatValues);

        return skillEvent;
    }
}
