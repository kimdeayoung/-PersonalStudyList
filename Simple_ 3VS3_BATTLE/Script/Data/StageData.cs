using System;
using UnityEngine;

[CreateAssetMenu(fileName = "StageData", menuName = "ScriptableObjects/StageData")]
public class StageData : ScriptableObject
{
    [Serializable]
    public class Data
    {
        public uint index;
        public uint[] enemyIndexes;
    }

    public Data[] data;
}
