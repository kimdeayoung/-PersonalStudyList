using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BattleDefeat : BattleState
{
    public BattleDefeat(BattleController battleController) : base(battleController)
    {
    }

    public override void StateEnter()
    {
        Debug.Log("Defeat");

        GameObject prefab = Resources.Load<GameObject>("Prefab/UIEndBattle");

        GameObject obj = GameObject.Instantiate(prefab, controller.UIController.UIBattle.CanvasTrans);
        UIBattleEnd battleEnd = obj.GetComponent<UIBattleEnd>();
        battleEnd.SetText("Defeat");
    }

    public override void StateUpdate()
    {

    }

    public override void StateExit()
    {

    }
}
