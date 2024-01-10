using System.Collections;
using System.Collections.Generic;
using TMPro;
using UnityEngine;

public class UIDamageFont : MonoBehaviour
{
    [SerializeField]
    private TextMeshProUGUI damage;

    [SerializeField]
    private float moveSpeed;

    [SerializeField]
    private float maxDuration;

    private float duration;

    public void Init(Vector3 pos, int damage)
    {
        transform.position = pos;

        this.damage.text = damage.ToString();
        if (damage > 0)
        {
            this.damage.color = Color.green;
        }
        else
        {
            this.damage.color = Color.red;
        }
    }

    public void Update()
    {
        duration += Time.deltaTime;
        transform.localPosition += new Vector3(0, moveSpeed * Time.deltaTime);

        if (duration > maxDuration)
        {
            ObjectPoolManager.Instance.ReleaseDamageFont(this);
        }
    }
}
