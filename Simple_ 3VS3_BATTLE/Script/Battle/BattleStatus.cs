using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BattleStatus : StatusInfo
{
    private BattleUnit unit;

    private Dictionary<BattleInfluenceType, float> influenceDatas;
    private BattleInfluenceType currentInfluenceType;

    public BattleStatus(BattleUnit unit)
    {
        this.unit = unit;
        influenceDatas = new Dictionary<BattleInfluenceType, float>();
        foreach (BattleInfluenceType influenceType in Enum.GetValues(typeof(BattleInfluenceType)))
        {
            if (influenceType != BattleInfluenceType.None)
            {
                influenceDatas.Add(influenceType, 0.0f);
            }
        }
        currentInfluenceType = BattleInfluenceType.None;
    }

    public BattleStatus(BattleUnit unit, StatusInfo other) : base(other)
    {
        this.unit = unit;
        influenceDatas = new Dictionary<BattleInfluenceType, float>();
        foreach (BattleInfluenceType influenceType in Enum.GetValues(typeof(BattleInfluenceType)))
        {
            if (influenceType != BattleInfluenceType.None)
            {
                influenceDatas.Add(influenceType, 0.0f);
            }
        }
        currentInfluenceType = BattleInfluenceType.None;
    }

    public BattleInfluenceType CurrentInfluenceType { get => currentInfluenceType; }

    public void IncreaseInfluenceData(BattleInfluenceType type, float leftTime)
    {
        influenceDatas[type] += leftTime;

        if (currentInfluenceType == BattleInfluenceType.None)
        {
            SetInfluenceType(type);
        }
    }

    public void Update()
    {
        BattleInfluenceType newInfluenceType = BattleInfluenceType.None;
        foreach (BattleInfluenceType influenceType in Enum.GetValues(typeof(BattleInfluenceType)))
        {
            if (influenceType != BattleInfluenceType.None)
            {
                float leftTime = influenceDatas[influenceType];
                if (leftTime > 0.0f)
                {
                    leftTime -= Time.deltaTime;
                    if (leftTime < 0.0f)
                    {
                        leftTime = 0.0f;
                    }
                    else
                    {
                        if (newInfluenceType == BattleInfluenceType.None)
                        {
                            newInfluenceType = influenceType;
                        }
                    }

                    influenceDatas[influenceType] = leftTime;
                }
            }
        }

        SetInfluenceType(newInfluenceType);
    }

    private void SetInfluenceType(BattleInfluenceType type)
    {
        if (currentInfluenceType == type)
        {
            return;
        }

        currentInfluenceType = type;

        switch (type)
        {
            case BattleInfluenceType.None:
                unit.SetUnitState(unit.State);
                break;
            case BattleInfluenceType.Stun:
                unit.UIBattleUnit.Idle();
                break;
        }
    }
}
