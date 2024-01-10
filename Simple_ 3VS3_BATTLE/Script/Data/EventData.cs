using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[CreateAssetMenu(fileName = "EventData", menuName = "ScriptableObjects/EventData")]
public class EventData : ScriptableObject
{
    [Serializable]
    public class Data
    {
        public uint index;
        public EventType eventType;

        public ActionValueType valueType;
    }

    public Data[] data;
}
