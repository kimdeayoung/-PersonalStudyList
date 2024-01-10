using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BattlePreparePreset
{
    private const uint presetSize = 3;

    private BaseUnitInfo[][] teamCharInfos;
    private int teamCount;

    public BattlePreparePreset()
    {
        teamCharInfos = new BaseUnitInfo[(uint)PositionType.Length][];
        for (uint i = 0; i < teamCharInfos.Length; ++i)
        {
            teamCharInfos[i] = new BaseUnitInfo[presetSize];
        }
    }

    public static uint PresetSize => presetSize;

    public BaseUnitInfo[][] TeamCharInfos { get => teamCharInfos; }
    public int TeamCount { get => teamCount; }

    public bool InsertCharacter(BaseUnitInfo charInfo)
    {
        uint positionType = (uint)charInfo.PositionType;
        for (uint i = 0; i < presetSize; ++i)
        {
            if (teamCharInfos[positionType][i] == null)
            {
                teamCharInfos[positionType][i] = charInfo;
                ++teamCount;
                return true;
            }
        }

        return false;
    }

    public bool RemoveCharacter(PositionType positionType, uint index)
    {
        if (teamCharInfos[(uint)positionType][index] != null)
        {
            teamCharInfos[(uint)positionType][index] = null;
            --teamCount;
            return true;
        }

        return false;
    }


}
