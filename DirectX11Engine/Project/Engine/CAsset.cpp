#include "pch.h"
#include "CAsset.h"

CAsset::CAsset(ASSET_TYPE type)
	: m_type(type)
	, m_refCount(0)
{
}

CAsset::~CAsset()
{
}
