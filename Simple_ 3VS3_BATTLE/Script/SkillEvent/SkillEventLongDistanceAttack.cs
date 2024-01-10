using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SkillEventLongDistanceAttack : SkillEvent
{
    public SkillEventLongDistanceAttack(EventData.Data data) : base(data)
    {
    }

    public override void ExcuteEvent(BattleUnit caster, BattleUnit[] targetUnits)
    {
        for (uint i = 0; i < targetUnits.Length; ++i)
        {
            UIProjectile.ProjectileData data;
            data.target = targetUnits[i];
            data.ImageName = stringValues[0];
            data.startPos = caster.UIBattleUnit.ProjectileStartPos.position;
            data.moveSpeed = floatValues[1];
            data.damage = CalculateAttackDamage(caster, targetUnits[i]);

            ObjectPoolManager.Instance.UseProjectile(data);
        }
    }
}
