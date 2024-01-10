using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Assertions;

public class CharacterManager : Manager<CharacterManager>
{
    private List<CharacterInfo> charInfos;

    public List<CharacterInfo> CharInfos { get => charInfos; }

    public override void Init()
    {
        base.Init();

        charInfos = new List<CharacterInfo>();

        CharacterData characterData = DataManager.Instance.CharacterData;
        foreach (CharacterData.Data data in characterData.data)
        {
            charInfos.Add(new CharacterInfo(data));
        }
    }

    public override void ClearData()
    {
        charInfos.Clear();
    }
}
