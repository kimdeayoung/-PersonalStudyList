using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BattleManager : ManagerWithMono<BattleManager>
{
    BattleController controller;

    public BattleController Controller { get => controller; }

    public override void Init()
    {
        base.Init();

        controller = new BattleController(TeamManager.Instance.BattleTeam, DataManager.Instance.FindStageData(1));
    }

    public void Update()
    {
        if (controller != null)
        {
            controller.Update();
        }
    }



    public override void ClearData()
    {

    }
}
