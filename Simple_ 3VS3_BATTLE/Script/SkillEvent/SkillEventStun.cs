using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SkillEventStun : SkillEvent
{
    public SkillEventStun(EventData.Data data) : base(data)
    {
    }

    public override void ExcuteEvent(BattleUnit caster, BattleUnit[] targetUnits)
    {
        Debug.Log("Ω∫≈œ");
        for (uint i = 0; i < targetUnits.Length; ++i)
        {
            targetUnits[i].ApplyChangeStateEvent(EventType.Stun, value);
        }
    }
}
