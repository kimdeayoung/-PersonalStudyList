using System;
using UnityEngine;

[CreateAssetMenu(fileName = "EnemyData", menuName = "ScriptableObjects/EnemyData")]
public class EnemyData : ScriptableObject
{
    [Serializable]
    public class Data
    {
        public uint index;

        public string name;
        public string prefabName;

        public PositionType position;
        public ClassType classType;
        public ElementType elementType;

        public int hp;
        public uint atk;
        public uint def;

        public uint[] skillIndexes;
    }

    public Data[] data;
}
