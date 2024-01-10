using DG.Tweening;
using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class UIBattleUnit : MonoBehaviour
{
    private BattleUnit battleUnit;

    private Action onHitTargetEnemy;
    private Action onSkillHitToEnemy;
    private Action<BattleUnit> onTriggerCollider;

    [SerializeField]
    private Animator animator;

    [SerializeField]
    private Transform projectileStartPos;

    [SerializeField]
    private Transform damageFontStartPos;

    public Transform ProjectileStartPos { get => projectileStartPos; }
    public Transform DamageFontStartPos { get => damageFontStartPos; }

    public void Init(BattleUnit battleUnit)
    {
        this.battleUnit = battleUnit;

        onHitTargetEnemy = battleUnit.BasicAttack;
        onSkillHitToEnemy = battleUnit.ExcuteBattleSkill;
        onTriggerCollider = battleUnit.OnTriggerCollider;
    }

    public bool IsSameUnit(uint UniqueID)
    {
        return battleUnit.UnitID == UniqueID;
    }

    void OnTriggerStay2D(Collider2D collision)
    {
        if (battleUnit.State == BattleUnitState.MoveToTarget)
        {
            switch (collision.tag)
            {
                case Tags.Unit:
                    {
                        UIBattleUnit unit = collision.GetComponent<UIBattleUnit>();
                        if (unit.battleUnit.IsAlive())
                        {
                            onTriggerCollider?.Invoke(unit.battleUnit);
                        }
                    }
                    break;
            }
        }
    }

    public void MoveUnitToPos(Vector3 pos, float moveSpeed)
    {
        Vector3 dir = (pos - transform.position).normalized;
        transform.position += dir * moveSpeed * Time.deltaTime;
    }

    public void SetUnitPos(Vector3 pos)
    {
        transform.localPosition = pos;
    }

    public void MoveUnitToPosX(float x, float duration, bool isTween, TweenCallback callback = null)
    {
        animator.SetBool("Attack", false);
        if (isTween)
        {
            TweenCallback complete = () =>
            {
                callback();
                animator.SetBool("Run", false);
            };

            transform.DOLocalMoveX(x, duration).OnComplete(complete);
            animator.SetBool("Run", true);
        }
        else
        {
            transform.localPosition = new Vector3(x, transform.localPosition.y);
        }
    }

    public void Idle()
    {
        animator.SetBool("Attack", false);
        animator.SetBool("Run", false);
        animator.SetBool("SkillAttack", false);
    }

    public void AttackStart()
    {
        Idle();
        animator.SetBool("Attack", true);
    }

    public void SkillAttackStart()
    {
        Idle();
        animator.SetBool("SkillAttack", true);
    }

    public void HitTargetEnemy()
    {
        onHitTargetEnemy?.Invoke();
    }

    public void SkillHitToEnemy()
    {
        onSkillHitToEnemy?.Invoke();
    }

    public void DieAnimEnd()
    {
        gameObject.SetActive(false);
    }

    public void UnitDie()
    {
        Idle();
        animator.SetTrigger("Die");
    }
}
