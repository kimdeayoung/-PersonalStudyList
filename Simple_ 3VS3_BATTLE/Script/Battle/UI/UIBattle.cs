using DG.Tweening;
using System.Collections;
using System.Collections.Generic;
using System.Globalization;
using UnityEngine;
using UnityEngine.Assertions;
using UnityEngine.UI;

public class UIBattle : MonoBehaviour
{
    private List<UIBattleUnit> _battleUnits;
    private List<UIBattleSkill> _battleSkills;

    [SerializeField]
    private Canvas canvas;

    [SerializeField]
    private Transform allyCharacterObjRoot;

    [SerializeField]
    private Transform enemyCharacterObjRoot;

    [SerializeField]
    private GridLayoutGroup skillIconsRoot;

    [SerializeField]
    private Transform projectilesRoot;

    [SerializeField]
    private Transform damageFontRoot;

    public Transform ProjectilesRoot { get => projectilesRoot; }
    public Transform DamageFontRoot { get => damageFontRoot; }
    public Transform CanvasTrans { get => canvas.transform; }

    private void Awake()
    {
        _battleUnits = new List<UIBattleUnit>();
        _battleSkills = new List<UIBattleSkill>();
    }

    private void Start()
    {
        canvas.renderMode = RenderMode.ScreenSpaceCamera;
        canvas.worldCamera = Camera.main;
    }

    public void CreateCharacterObj(BattleUnit battleUnit)
    {
        Assert.IsNotNull(battleUnit);

        GameObject prefab = Resources.Load<GameObject>(string.Concat("Prefab/", battleUnit.PrefabName));
        Assert.IsNotNull(prefab);
        switch (battleUnit.SquadType)
        {
            case BattleSquadType.Ally:
                {
                    GameObject obj = Instantiate(prefab, allyCharacterObjRoot);
                    Assert.IsNotNull(obj);

                    UIBattleUnit uiUnit = obj.GetComponent<UIBattleUnit>();
                    Assert.IsNotNull(uiUnit);
                    uiUnit.Init(battleUnit);
                    battleUnit.UIBattleUnit = uiUnit;

                    _battleUnits.Add(uiUnit);
                }
                break;
            case BattleSquadType.Enemy:
                {
                    GameObject obj = Instantiate(prefab, enemyCharacterObjRoot);
                    Assert.IsNotNull(obj);

                    UIBattleUnit uiUnit = obj.GetComponent<UIBattleUnit>();
                    Assert.IsNotNull(uiUnit);
                    uiUnit.Init(battleUnit);
                    battleUnit.UIBattleUnit = uiUnit;

                    _battleUnits.Add(uiUnit);
                }
                break;
        }
    }

    public void CreateSkillIcons(BattleController controller, BattleUnit battleUnit)
    {
        Assert.IsNotNull(battleUnit);
        Assert.IsTrue(battleUnit.SquadType == BattleSquadType.Ally);

        GameObject prefab = Resources.Load<GameObject>("Prefab/UIBattleSkill");
        Assert.IsNotNull(prefab);

        for (uint i = 0; i < battleUnit.BattleSkills.Length; ++i)
        {
            BattleSkill battleSkill = battleUnit.BattleSkills[i];

            if (battleSkill.ActiveType == SkillActiveType.Automatic)
            {
                continue;
            }
            GameObject obj = Instantiate(prefab, skillIconsRoot.transform);
            Assert.IsNotNull(obj);

            UIBattleSkill uiBattleSkill = obj.GetComponent<UIBattleSkill>();
            Assert.IsNotNull(uiBattleSkill);
            uiBattleSkill.Init(controller, battleSkill);

            _battleSkills.Add(uiBattleSkill);
        }
    }

    public void MoveUnitToPos(uint unitID, Vector3 pos, float moveSpeed)
    {
        foreach (UIBattleUnit unit in _battleUnits)
        {
            if (unit.IsSameUnit(unitID))
            {
                unit.MoveUnitToPos(pos, moveSpeed);
                break;
            }
        }
    }

    public void SetUnitPos(uint unitID, Vector3 pos)
    {
        foreach (UIBattleUnit unit in _battleUnits)
        {
            if (unit.IsSameUnit(unitID))
            {
                unit.SetUnitPos(pos);
                break;
            }
        }
    }

    public void MoveUnitToPosX(uint unitID, float x, float duration, bool isTween, TweenCallback callback = null)
    {
        foreach (UIBattleUnit unit in _battleUnits)
        {
            if (unit.IsSameUnit(unitID))
            {
                unit.MoveUnitToPosX(x, duration, isTween, callback);
                break;
            }
        }
    }

    public UIBattleUnit FindUIBattleUnit(uint unitID)
    {
        foreach (UIBattleUnit unit in _battleUnits)
        {
            if (unit.IsSameUnit(unitID))
            {
                return unit;
            }
        }
        return null;
    }

    public void ClearData()
    {

    }
}
