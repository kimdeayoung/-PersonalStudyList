using DG.Tweening;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Assertions;

public class BattleUIController
{
    private BattleController controller;

    private UIBattle uiBattle;
    public Transform ProjectilesRoot { get => uiBattle.ProjectilesRoot; }
    public Transform DamageFontRoot { get => uiBattle.DamageFontRoot; }
    public UIBattle UIBattle { get => uiBattle; }

    public BattleUIController(BattleController controller)
    {
        this.controller = controller;
    }

    public void CreateBattleUI()
    {
        Assert.IsNull(uiBattle);

        GameObject prefab = Resources.Load<GameObject>("Prefab/UIBattle");
        Assert.IsNotNull(prefab);

        GameObject obj = Object.Instantiate(prefab);
        Assert.IsNotNull(obj);

        uiBattle = obj.GetComponent<UIBattle>();
    }

    public void CreateAllyUnitsUI(BattleSquad battleSquad)
    {
        Assert.IsNotNull(uiBattle);
        Assert.IsNotNull(battleSquad);
        Assert.IsTrue(battleSquad.SquadType == BattleSquadType.Ally);

        BattleUnit[] units = battleSquad.Units;
        for (uint i = 0; i < units.Length; ++i)
        {
            BattleUnit unit = units[i];
            uiBattle.CreateCharacterObj(unit);
            uiBattle.CreateSkillIcons(controller, unit);
        }
    }

    public void CreateEnemyUnitsUI(BattleSquad battleSquad)
    {
        Assert.IsNotNull(uiBattle);
        Assert.IsNotNull(battleSquad);
        Assert.IsTrue(battleSquad.SquadType == BattleSquadType.Enemy);

        BattleUnit[] units = battleSquad.Units;
        for (uint i = 0; i < units.Length; ++i)
        {
            BattleUnit unit = units[i];
            uiBattle.CreateCharacterObj(unit);
        }
    }

    public void MoveUnitToPos(uint unitID, Vector3 pos, float moveSpeed)
    {
        uiBattle.MoveUnitToPos(unitID, pos, moveSpeed);
    }

    public void SetUnitPos(uint unitID, Vector3 pos)
    {
        uiBattle.SetUnitPos(unitID, pos);
    }

    public void MoveUnitToPosX(uint unitID, float x, float duration, bool isTween, TweenCallback callback = null)
    {
        uiBattle.MoveUnitToPosX(unitID, x, duration, isTween, callback);
    }

    public UIBattleUnit FindUIBattleUnit(uint unitID)
    {
        return uiBattle.FindUIBattleUnit(unitID);
    }
}
