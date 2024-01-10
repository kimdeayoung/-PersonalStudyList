using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TeamManager : Manager<TeamManager>
{
    BattlePreparePreset battleTeam;

    public BattlePreparePreset BattleTeam { get => battleTeam; }

    public override void Init()
    {
        base.Init();

        battleTeam = new BattlePreparePreset();

        for (int i = 0; i < BattlePreparePreset.PresetSize; ++i)
        {
            battleTeam.InsertCharacter(CharacterManager.Instance.CharInfos[i]);
        }
    }

    public override void ClearData()
    {

    }
}
