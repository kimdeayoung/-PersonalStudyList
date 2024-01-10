using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Assertions;

public class TargetController
{
    private BattleController controller;

    public TargetController(BattleController battleController)
    {
        controller = battleController;
    }

    public BattleUnit FindBattleTarget(BattleUnit unit)
    {
        Assert.IsNotNull(unit);

        BattleUnit target = null;
        float targetDistance = float.MaxValue;

        switch (unit.SquadType)
        {
            case BattleSquadType.Ally:
                foreach (BattleUnit enemy in controller.EnemySquad.Units)
                {
                    if (enemy.IsAlive())
                    {
                        float distance = (enemy.UIBattleUnit.transform.position - unit.UIBattleUnit.transform.position).magnitude;
                        if (distance < targetDistance)
                        {
                            target = enemy;
                            targetDistance = distance;
                        }
                    }
                }
                break;
            case BattleSquadType.Enemy:
                foreach (BattleUnit enemy in controller.AllySquad.Units)
                {
                    if (enemy.IsAlive())
                    {
                        float distance = (enemy.UIBattleUnit.transform.position - unit.UIBattleUnit.transform.position).magnitude;
                        if (distance < targetDistance)
                        {
                            target = enemy;
                            targetDistance = distance;
                        }
                    }
                }
                break;
        }

        return target;
    }

    public BattleUnit[] FindSkillTarget(BattleSkill battleSkill)
    {
        BattleUnit[] battleUnits = null;

        switch (battleSkill.TargetType)
        {
            case TargetType.Team_All:
                {
                    List<BattleUnit> targets = new List<BattleUnit>();
                    for (uint i = 0; i < controller.AllySquad.Units.Length; ++i)
                    {
                        if (controller.AllySquad.Units[i].IsAlive())
                        {
                            targets.Add(controller.AllySquad.Units[i]);
                        }
                    }
                    battleUnits = targets.ToArray();
                }
                break;
            case TargetType.Enemy_Target:
                battleUnits = new BattleUnit[] { battleSkill.Owner.BattleTarget };
                break;
            case TargetType.Enemy_All:
                {
                    List<BattleUnit> targets = new List<BattleUnit>();
                    for (uint i = 0; i < controller.EnemySquad.Units.Length; ++i)
                    {
                        if (controller.EnemySquad.Units[i].IsAlive())
                        {
                            targets.Add(controller.EnemySquad.Units[i]);
                        }
                    }
                    battleUnits = targets.ToArray();
                }
                break;
        }

        return battleUnits;
    }
}
