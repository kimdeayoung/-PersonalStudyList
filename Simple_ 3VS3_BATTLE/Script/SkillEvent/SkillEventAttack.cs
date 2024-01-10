using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SkillEventAttack : SkillEvent
{
    public SkillEventAttack(EventData.Data data) : base(data)
    {
    }

    public override void ExcuteEvent(BattleUnit caster, BattleUnit[] targetUnits)
    {
        for (uint i = 0; i < targetUnits.Length; ++i)
        {
            int damage = CalculateAttackDamage(caster, targetUnits[i]);

            targetUnits[i].ChangeUnitBattleHp(false, damage);
        }
    }
}
