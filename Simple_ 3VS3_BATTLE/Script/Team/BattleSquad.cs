using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BattleSquad
{
    private BattleController controller;
    private BattleUnit[] units;

    private BattleSquadType squadType;

    public BattleSquadType SquadType { get => squadType; }
    public BattleUnit[] Units { get => units; }
    public BattleController Controller { get => controller; set => controller = value; }

    public BattleSquad(BattleController controller, BattlePreparePreset preset, ref uint uniqueID)
    {
        this.controller = controller;
        BaseUnitInfo[][] teamCharInfos = preset.TeamCharInfos;

        units = new BattleUnit[preset.TeamCount];
        uint unitIndex = 0;
        for (uint i = 0; i < teamCharInfos.Length; ++i)
        {
            for (uint j = 0; j < teamCharInfos[i].Length; ++j)
            {
                CharacterInfo unitInfo = (CharacterInfo)teamCharInfos[i][j];
                if (unitInfo != null)
                {
                    units[unitIndex++] = new BattleCharacter(this, uniqueID++, unitInfo);
                }
            }
        }
        squadType = BattleSquadType.Ally;
    }

    public BattleSquad(BattleController controller, StageData.Data stageData, ref uint uniqueID)
    {
        this.controller = controller;
        units = new BattleUnit[stageData.enemyIndexes.Length];
        uint unitIndex = 0;
        foreach (uint enemyIndex in stageData.enemyIndexes)
        {
            units[unitIndex++] = new BattleEnemy(this, uniqueID++, DataManager.Instance.FindEnemyData(enemyIndex));
        }
        squadType = BattleSquadType.Enemy;
    }

    public void Update()
    {
        for (int i = 0; i < units.Length; ++i)
        {
            if (units[i].IsUnitDieState() == false)
            {
                units[i].Update();
            }
        }
    }

    public bool IsTeamAlive()
    {
        for (int i = 0; i < units.Length; ++i)
        {
            if (units[i].IsAlive())
            {
                return true;
            }
        }
        return false;
    }
}
