using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SkillEventHeal : SkillEvent
{
    public SkillEventHeal(EventData.Data data) : base(data)
    {
    }

    public override void ExcuteEvent(BattleUnit caster, BattleUnit[] targetUnits)
    {
        for (uint i = 0; i < targetUnits.Length; ++i)
        {
            int heal = CalculateHeal(caster, targetUnits[i]);

            targetUnits[i].ChangeUnitBattleHp(true, heal);
        }
    }
}
