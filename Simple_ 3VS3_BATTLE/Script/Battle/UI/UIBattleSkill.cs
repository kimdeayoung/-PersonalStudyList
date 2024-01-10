using System;
using System.Collections;
using System.Collections.Generic;
using TMPro;
using UnityEngine;
using UnityEngine.UI;

public class UIBattleSkill : MonoBehaviour
{
    private BattleSkill battleSkill;
    private Action<BattleSkill> onClickSkill;

    [SerializeField]
    private Image icon;

    [SerializeField]
    private Image coolTimeImage;

    [SerializeField]
    private TextMeshProUGUI coolTimeText;

    public void Init(BattleController controller, BattleSkill battleSkill)
    {
        this.battleSkill = battleSkill;
        icon.sprite = Resources.Load<Sprite>(battleSkill.Icon);
        onClickSkill = battleSkill.Owner.PrepareExcuteSkill;
    }

    public void Update()
    {
        if (battleSkill != null)
        {
            coolTimeImage.fillAmount = 1.0f - battleSkill.GetCoolTimeRatio();
            int leftTime = Mathf.CeilToInt(battleSkill.GetUseAbleCoolTime());
            if (leftTime > 0)
            {
                coolTimeText.text = leftTime.ToString();
            }
            else
            {
                coolTimeText.text = string.Empty;
            }
        }
    }

    public void OnClickIcon()
    {
        onClickSkill?.Invoke(battleSkill);
    }
}
