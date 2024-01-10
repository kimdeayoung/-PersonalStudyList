using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[CreateAssetMenu(fileName = "SkillData", menuName = "ScriptableObjects/SkillData")]
public class SkillData : ScriptableObject
{
    [Serializable]
    public class Data
    {
        [Serializable]
        public class EventData
        {
            public uint eventIndex;
            public string[] bindStringValues;
            public float[] bindFloatValues;
        }

        public uint index;

        public string name;
        public string description;

        public string icon;

        public SkillType type;
        public SkillActiveType activeType;
        public TargetType targetType;

        public EventData[] eventDatas;
        public float activeCoolTime;
    }

    public Data[] data;
}
