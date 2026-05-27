#include "pch.h"
#include "CCollisionManager.h"

CCollisionManager::CCollisionManager()
	: m_matrix{}
{

}

CCollisionManager::~CCollisionManager()
{

}

void CCollisionManager::Update()
{
	for (UINT row = 0; row < MAX_LAYER; ++row)
	{
		for (UINT col = row; col < MAX_LAYER; ++col)
		{
			if (m_matrix[row] & (1 << col))
			{

			}
		}
	}
}

void CCollisionManager::ToggleLayerEnable(UINT lhs, UINT rhs)
{
	UINT row = lhs;
	UINT col = rhs;

	if (row > col)
	{
		row = rhs;
		col = lhs;
	}

	m_matrix[row] ^= (1 << col);
}
