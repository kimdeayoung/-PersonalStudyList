using DG.Tweening;
using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BattlePrepareProduction : BattleState
{
    private int prepareBattleCompleteCount;
    private int prepareCount;

    public BattlePrepareProduction(BattleController battleController) : base(battleController)
    {
    }

    public override void StateEnter()
    {
        const float moveBattlePosDuration = 0.9f;
        TweenCallback moveUnitEnd = () =>
        {
            if (++prepareCount >= prepareBattleCompleteCount)
            {
                StateExit();
            }
        };

        float[] xOffset = new float[] { 120.0f, 60.0f, 0.0f };
        float[] battleXPos = new float[] { 500.0f, 300.0f, 200.0f };

        BattleSquad allySquad = controller.AllySquad;
        float[][] allyYPos = GetSquadYPositions(allySquad);
        uint[] allyPlacedCount = new uint[(uint)PositionType.Length];

        foreach (BattleUnit unit in allySquad.Units)
        {
            uint positionType = (uint)unit.PositionType;
            //초기 포지션 세팅
            controller.SetUnitPos(unit.UnitID, new Vector3(xOffset[positionType], allyYPos[positionType][allyPlacedCount[positionType]++]));

            //전투 위치 이동
            controller.MoveUnitToPosX(unit.UnitID, battleXPos[positionType], moveBattlePosDuration, true, moveUnitEnd);
        }

        BattleSquad enemySquad = controller.EnemySquad;
        float[][] enemyYPos = GetSquadYPositions(enemySquad);
        uint[] enemyPlacedCount = new uint[(uint)PositionType.Length];

        foreach (BattleUnit unit in enemySquad.Units)
        {
            uint positionType = (uint)unit.PositionType;
            //초기 포지션 세팅
            controller.SetUnitPos(unit.UnitID, new Vector3(-xOffset[positionType], enemyYPos[positionType][enemyPlacedCount[positionType]++]));

            //전투 위치 이동
            controller.MoveUnitToPosX(unit.UnitID, -battleXPos[positionType], moveBattlePosDuration, true, moveUnitEnd);
        }

        prepareBattleCompleteCount = allySquad.Units.Length + enemySquad.Units.Length;
    }

    public override void StateUpdate()
    {

    }

    public override void StateExit()
    {
        controller.SetBattleState(BattleStateType.Progress);
    }

    private float[][] GetSquadYPositions(BattleSquad squad)
    {
        uint[] counts = new uint[(uint)PositionType.Length];
        foreach (BattleUnit unit in squad.Units)
        {
            counts[(uint)unit.PositionType]++;
        }

        float[][] positionValues = new float[(uint)PositionType.Length][];
        for (uint i = 0; i < (uint)PositionType.Length; ++i)
        {
            uint count = counts[i];
            positionValues[i] = new float[count];
            if (count == 1)
            {
                positionValues[i][0] = 0.0f;
            }
            else if (count == 2)
            {
                positionValues[i][0] = 50.0f;
                positionValues[i][1] = -50.0f;
            }
            else if (count == 3)
            {
                positionValues[i][0] = 80.0f;
                positionValues[i][1] = 0.0f;
                positionValues[i][2] = -80.0f;
            }
        }

        return positionValues;
    }
}
