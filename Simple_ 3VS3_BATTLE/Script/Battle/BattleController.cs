using DG.Tweening;
using System.Buffers;
using System.Collections;
using System.Collections.Generic;
using System.Globalization;
using UnityEngine;
using UnityEngine.Assertions;

public class BattleController
{
    protected BattleUIController uiController;
    protected TargetController targetController;

    protected BattleState currentBattleState;

    protected BattleSquad allySquad;
    protected BattleSquad enemySquad;

    public BattleUIController UIController { get => uiController; }
    public TargetController TargetController { get => targetController; }

    public BattleSquad AllySquad { get => allySquad; }
    public BattleSquad EnemySquad { get => enemySquad; }

    public BattleController(BattlePreparePreset team, StageData.Data stageData)
    {
        uint uniqueID = 0;
        allySquad = new BattleSquad(this, team, ref uniqueID);
        enemySquad = new BattleSquad(this, stageData, ref uniqueID);

        uiController = new BattleUIController(this);
        targetController = new TargetController(this);

        SetBattleState(BattleStateType.Enter);
    }

    public void SetBattleState(BattleStateType type)
    {
        switch (type)
        {
            case BattleStateType.Enter:
                currentBattleState = new BattleEnter(this);
                break;
            case BattleStateType.PrepareProduction:
                currentBattleState = new BattlePrepareProduction(this);
                break;
            case BattleStateType.Progress:
                currentBattleState = new BattleProgress(this);
                break;
            case BattleStateType.Victory:
                currentBattleState = new BattleVictory(this);
                break;
            case BattleStateType.Defeat:
                currentBattleState = new BattleDefeat(this);
                break;
        }
        currentBattleState.StateEnter();
    }

    public void Update()
    {
        if (currentBattleState != null)
        {
            currentBattleState.StateUpdate();
        }
    }

    public void MoveUnitToPos(uint unitID, Vector3 pos, float moveSpeed)
    {
        uiController.MoveUnitToPos(unitID, pos, moveSpeed);
    }

    public void SetUnitPos(uint unitID, Vector3 pos)
    {
        uiController.SetUnitPos(unitID, pos);
    }

    public void MoveUnitToPosX(uint unitID, float x, float duration, bool isTween, TweenCallback callback = null)
    {
        uiController.MoveUnitToPosX(unitID, x, duration, isTween, callback);
    }

    public UIBattleUnit FindUIBattleUnit(uint unitID)
    {
        return uiController.FindUIBattleUnit(unitID);
    }
}
