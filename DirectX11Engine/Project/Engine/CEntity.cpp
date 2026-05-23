#include "pch.h"
#include "CEntity.h"

UINT CEntity::g_nextInstanceID = 0;

CEntity::CEntity()
	: m_instanceID(g_nextInstanceID++)
{
}

CEntity::CEntity(const CEntity& other)
	: m_instanceID(g_nextInstanceID++)
{
}

CEntity::~CEntity()
{
}
