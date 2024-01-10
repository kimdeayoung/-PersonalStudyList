using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BattleVictory : BattleState
{
    public BattleVictory(BattleController battleController) : base(battleController)
    {
    }

    public override void StateEnter()
    {
        Debug.Log("Win");

        GameObject prefab = Resources.Load<GameObject>("Prefab/UIEndBattle");

        GameObject obj = GameObject.Instantiate(prefab, controller.UIController.UIBattle.CanvasTrans);
        UIBattleEnd battleEnd = obj.GetComponent<UIBattleEnd>();
        battleEnd.SetText("Victory");
    }

    public override void StateUpdate()
    {
    }

    public override void StateExit()
    {

    }
}
