#pragma once

#include "CEntity.h"

class CAsset :
	public CEntity
{
private:
	std::wstring m_key; // 로딩된 키값

	std::wstring m_relativePath; // Asset의 상대 경로

	const ASSET_TYPE m_type; // Asset의 타입

	int m_refCount;

public:
	const std::wstring& GetKey() { return m_key; }
	const std::wstring& GetRelativePath() { return m_relativePath; }

	ASSET_TYPE GetAssetType() { return m_type; }

private:
	virtual int Load(const std::wstring& path) = 0;
	virtual int Save(const std::wstring& path) = 0;

private:
	void AddRefCount() { ++m_refCount; }
	void Release()
	{
		if (--m_refCount <= 0)
		{
			delete this;
		}
	}

public:
	CAsset(ASSET_TYPE type);
	CAsset(const CAsset& other) = delete;
	~CAsset();

	template<typename T> friend class Ptr;
	friend class CAssetManager;
};

