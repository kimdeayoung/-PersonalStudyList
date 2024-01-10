using System;
using UnityEngine;

[CreateAssetMenu(fileName = "CharacterData", menuName = "ScriptableObjects/CharacterData")]
public class CharacterData : ScriptableObject
{
    [Serializable]
    public class Data
    {
        public uint index;

        public uint level;
        public uint maxLevel;

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