using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CharacterInfo : BaseUnitInfo
{
    private uint maxLevel;

    public CharacterInfo(CharacterData.Data data)
    {
        level = data.level;
        maxLevel = data.maxLevel;
        name = data.name;
        prefabName = data.prefabName;

        classType = data.classType;
        elementType = data.elementType;

        positionType = data.position;

        defaultStatusInfo = new StatusInfo();
        defaultStatusInfo.Hp = data.hp;
        defaultStatusInfo.Atk = data.atk;
        defaultStatusInfo.Def = data.def;

        skills = new Skill[data.skillIndexes.Length];
        for (uint i = 0; i < data.skillIndexes.Length; ++i)
        {
            skills[i] = new Skill(DataManager.Instance.FindSkillData(data.skillIndexes[i]));
        }
    }

    public uint MaxLevel { get => maxLevel; }
}
