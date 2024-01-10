using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class UIProjectile : MonoBehaviour
{
    private ProjectileData data;

    public struct ProjectileData
    {
        public BattleUnit target;
        public string ImageName;
        public Vector3 startPos;
        public float moveSpeed;
        public int damage;
    }

    [SerializeField]
    private Image icon;

    [SerializeField]
    private BoxCollider2D collider;

    public void Init(ProjectileData data)
    {
        this.data = data;
        icon.sprite = Resources.Load<Sprite>(data.ImageName);
        icon.SetNativeSize();

        collider.size = new Vector2(icon.rectTransform.rect.width, icon.rectTransform.rect.height);
        transform.position = data.startPos;
    }

    public void Update()
    {
        Vector3 dir = (data.target.UIBattleUnit.transform.position - transform.position).normalized;
        transform.position += dir * data.moveSpeed * Time.deltaTime;

        if ((data.target.UIBattleUnit.transform.position - transform.position).sqrMagnitude <= 0.1f)
        {
            ObjectPoolManager.Instance.ReleaseProjectile(this);
        }
    }

    public void OnTriggerStay2D(Collider2D collision)
    {
        if (isActiveAndEnabled)
        {
            switch (collision.tag)
            {
                case Tags.Unit:
                    {
                        UIBattleUnit unit = collision.GetComponent<UIBattleUnit>();
                        if (unit.IsSameUnit(data.target.UnitID))
                        {
                            data.target.ChangeUnitBattleHp(false, data.damage);
                            ObjectPoolManager.Instance.ReleaseProjectile(this);
                        }
                    }
                    break;
            }
        }
    }
}
