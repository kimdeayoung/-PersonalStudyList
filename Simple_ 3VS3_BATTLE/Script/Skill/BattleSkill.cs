using System.Collections;
using System.Collections.Generic;
using System.Linq;
using UnityEngine;

public class BattleSkill
{
    private BattleUnit owner;

    private Skill skill;
    private float currentCoolTime;

    public string Icon { get => skill.Icon; }
    public TargetType TargetType { get => skill.TargetType; }
    public SkillActiveType ActiveType { get => skill.ActiveType; }
    public BattleUnit Owner { get => owner; }

    public BattleSkill(BattleUnit owner, Skill skill)
    {
        this.owner = owner;
        this.skill = skill;
    }

    public bool IsSameOwner(BattleUnit unit)
    {
        return owner.UnitID == unit.UnitID;
    }

    public void Update()
    {
        if (currentCoolTime <= skill.ActiveCoolTime)
        {
            currentCoolTime += Time.deltaTime;
        }
    }

    public void ExcuteSkill(BattleUnit target)
    {
        BattleUnit[] targets = new BattleUnit[] { target };
        ExcuteSkill(targets);
    }

    public void ExcuteSkill(BattleUnit[] targets)
    {
        if (IsUseAble())
        {
            foreach (SkillEvent sklillEvent in skill.Events)
            {
                sklillEvent.ExcuteEvent(owner, targets);
            }

            currentCoolTime = 0.0f;
        }
    }

    public bool IsUseAble()
    {
        return currentCoolTime >= skill.ActiveCoolTime;
    }

    public float GetCoolTimeRatio()
    {
        return currentCoolTime / skill.ActiveCoolTime;
    }

    public float GetUseAbleCoolTime()
    {
        return skill.ActiveCoolTime - currentCoolTime;
    }
}
