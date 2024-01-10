using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class UIAnimationReceiver : MonoBehaviour
{
    [SerializeField]
    private UIBattleUnit battleUnit;

    public void HitTargetEnemy()
    {
        battleUnit.HitTargetEnemy();
    }

    public void SkillHitToEnemy()
    {
        battleUnit.SkillHitToEnemy();
    }

    public void DieAnimEnd()
    {
        battleUnit.DieAnimEnd();
    }
}
