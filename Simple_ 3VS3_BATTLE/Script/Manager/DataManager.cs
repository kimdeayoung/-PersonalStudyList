using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Assertions;

public class DataManager : Manager<DataManager>
{
    private CharacterData characterData;
    private SkillData skillData;
    private EventData eventData;
    private EnemyData enemyData;
    private StageData stageData;

    public CharacterData CharacterData { get => characterData; }

    public override void Init()
    {
        base.Init();

        characterData = Resources.Load<CharacterData>("Data/CharacterData");
        Assert.IsNotNull(characterData, "CharacterData Load Failed");

        skillData = Resources.Load<SkillData>("Data/SkillData");
        Assert.IsNotNull(skillData, "SkillData Load Failed");

        eventData = Resources.Load<EventData>("Data/EventData");
        Assert.IsNotNull(eventData, "EventData Load Failed");

        enemyData = Resources.Load<EnemyData>("Data/EnemyData");
        Assert.IsNotNull(enemyData, "EnemyData Load Failed");

        stageData = Resources.Load<StageData>("Data/StageData");
        Assert.IsNotNull(stageData, "StageData Load Failed");
    }

    public SkillData.Data FindSkillData(uint skilIndex)
    {
        Assert.IsTrue(skillData != null, "SkillData Load Failed");
        foreach (SkillData.Data data in skillData.data)
        {
            if (data.index == skilIndex)
            {
                return data;
            }
        }

        return null;
    }

    public EventData.Data FindEventData(uint eventIndex)
    {
        Assert.IsTrue(eventData != null, "EventData Load Failed");
        foreach (EventData.Data data in eventData.data)
        {
            if (data.index == eventIndex)
            {
                return data;
            }
        }

        return null;
    }

    public EnemyData.Data FindEnemyData(uint enemyIndex)
    {
        Assert.IsTrue(enemyData != null, "EnemyData Load Failed");
        foreach (EnemyData.Data data in enemyData.data)
        {
            if (data.index == enemyIndex)
            {
                return data;
            }
        }

        return null;
    }

    public StageData.Data FindStageData(uint stageIndex)
    {
        Assert.IsTrue(stageData != null, "StageData Load Failed");
        foreach (StageData.Data data in stageData.data)
        {
            if (data.index == stageIndex)
            {
                return data;
            }
        }

        return null;
    }

    public override void ClearData()
    {

    }
}
