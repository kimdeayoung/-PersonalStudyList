using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BattleEnter : BattleState
{
    public BattleEnter(BattleController battleController) : base(battleController)
    {
    }

    public override void StateEnter()
    {
        controller.UIController.CreateBattleUI();
        controller.UIController.CreateAllyUnitsUI(controller.AllySquad);
        controller.UIController.CreateEnemyUnitsUI(controller.EnemySquad);

        ObjectPoolManager.Instance.CreateProjectile(controller.UIController.ProjectilesRoot);
        ObjectPoolManager.Instance.CreateDamageFonts(controller.UIController.DamageFontRoot);

        StateExit();
    }

    public override void StateUpdate()
    {
    }

    public override void StateExit()
    {
        controller.SetBattleState(BattleStateType.PrepareProduction);
    }
}
