using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BattleProgress : BattleState
{
    public BattleProgress(BattleController battleController) : base(battleController)
    {
    }

    public override void StateEnter()
    {

    }

    public override void StateUpdate()
    {
        controller.AllySquad.Update();
        controller.EnemySquad.Update();

        if (controller.EnemySquad.IsTeamAlive() == false)
        {
            StateExit();
        }
        else if(controller.AllySquad.IsTeamAlive() == false)
        {
            StateExit();
        }
    }

    public override void StateExit()
    {
        if (controller.AllySquad.IsTeamAlive())
        {
            controller.SetBattleState(BattleStateType.Victory);
        }
        else if (controller.EnemySquad.IsTeamAlive())
        {
            controller.SetBattleState(BattleStateType.Defeat);
        }
    }
}
