using System.Collections;
using System.Collections.Generic;
using Unity.VisualScripting.FullSerializer;
using UnityEngine;

public class ObjectPoolManager : Manager<ObjectPoolManager>
{
    private Queue<UIProjectile> projectiles;
    private Queue<UIDamageFont> damageTexts;

    public override void Init()
    {
        base.Init();

        projectiles = new Queue<UIProjectile>();
        damageTexts = new Queue<UIDamageFont>();
    }

    public void CreateProjectile(Transform root)
    {
        const uint createProjectilesCount = 80;

        GameObject prefab = Resources.Load<GameObject>("Prefab/UIProjectile");
        for (uint i = 0; i < createProjectilesCount; ++i)
        {
            GameObject obj = GameObject.Instantiate<GameObject>(prefab, root);
            UIProjectile projectile = obj.GetComponent<UIProjectile>();
            obj.SetActive(false);

            projectiles.Enqueue(projectile);
        }
    }

    public void CreateDamageFonts(Transform root)
    {
        const uint createDamageFontsCount = 200;

        GameObject prefab = Resources.Load<GameObject>("Prefab/UIDamageFont");
        for (uint i = 0; i < createDamageFontsCount; ++i)
        {
            GameObject obj = GameObject.Instantiate<GameObject>(prefab, root);
            UIDamageFont font = obj.GetComponent<UIDamageFont>();
            obj.SetActive(false);

            damageTexts.Enqueue(font);
        }
    }

    public UIProjectile UseProjectile(UIProjectile.ProjectileData data)
    {
        UIProjectile projectile = projectiles.Dequeue();
        projectile.gameObject.SetActive(true);
        projectile.Init(data);
        return projectile;
    }

    public void ReleaseProjectile(UIProjectile usedProjectile)
    {
        usedProjectile.gameObject.SetActive(false);
        projectiles.Enqueue(usedProjectile);
    }

    public UIDamageFont UseDamageFont(Vector3 pos, int damage)
    {
        UIDamageFont font = damageTexts.Dequeue();
        font.gameObject.SetActive(true);
        font.Init(pos, damage);
        return font;
    }

    public void ReleaseDamageFont(UIDamageFont font)
    {
        font.gameObject.SetActive(false);
        damageTexts.Enqueue(font);
    }

    public override void ClearData()
    {
        while (projectiles.Count > 0)
        {
            UIProjectile projectile = projectiles.Dequeue();
            GameObject.Destroy(projectile.gameObject);
        }

        while (damageTexts.Count > 0)
        {
            UIDamageFont font = damageTexts.Dequeue();
            GameObject.Destroy(font.gameObject);
        }
    }
}
