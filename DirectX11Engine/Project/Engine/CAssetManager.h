#pragma once
#include "Singleton.h"
#include "CAsset.h"

#include "CPathManager.h"
#include "assets.h"

class CAssetManager :
    public CSingleton<CAssetManager>
{
private:
    std::map<std::wstring, Ptr<CAsset>> m_assets[(UINT)ASSET_TYPE::LENGTH];

public:
    void Init();
    void CreateDefaultMesh();
    void CreateDefaultTexture();
    void CreateDefaultMaterial();
    void CreateDefaultGraphicShader();
    void CreateDefaultComputeShader();

public:
    template<typename T>
    Ptr<T> Load(const std::wstring& key, const std::wstring& relativePath);

    template<typename T>
    Ptr<T> FindAsset(const std::wstring& key);

    template<typename T>
    void AddAsset(const std::wstring& key, Ptr<T> asset);

    Singleton(CAssetManager)
};

template<typename T>
ASSET_TYPE GetAssetType()
{
    if constexpr (std::is_same_v<T, CMesh>)
    {
        return ASSET_TYPE::MESH;
    }
    if constexpr (std::is_same_v<T, CGraphicShader>)
    {
        return ASSET_TYPE::GRAPHICS_SHADER;
    }
    if constexpr (std::is_same_v<T, CComputeShader>)
    {
        return ASSET_TYPE::COMPUTE_SHADER;
    }
    if constexpr (std::is_same_v<T, CTexture>)
    {
        return ASSET_TYPE::TEXTURE;
    }
    if constexpr (std::is_same_v<T, CMaterial>)
    {
        return ASSET_TYPE::MATERIAL;
    }
}

template<typename T>
inline Ptr<T> CAssetManager::Load(const std::wstring& key, const std::wstring& relativePath)
{
    Ptr<CAsset> pAsset = FindAsset<T>(key).Get();
    if (pAsset.Get() != nullptr)
    {
        return (T*)pAsset.Get();
    }

    pAsset = new T;
    std::wstring path = CPathManager::GetInstance()->GetContentPath();
    path += relativePath;
    if (FAILED(pAsset->Load(path)))
    {
        MessageBox(nullptr, path.c_str(), L"에셋 로딩 실패", MB_OK);
        return nullptr;
    }

    AddAsset<T>(key, (T*)pAsset.Get());

    return (T*)pAsset.Get();
}

template<typename T>
inline Ptr<T> CAssetManager::FindAsset(const std::wstring& key)
{
    ASSET_TYPE type = GetAssetType<T>();

    std::map<std::wstring, Ptr<CAsset>>::iterator iter = m_assets[(UINT)type].find(key);

    if (iter == m_assets[(UINT)type].end())
    {
        return nullptr;
    }
#ifdef _DEBUG
    T* pAsset = dynamic_cast<T*>(iter->second.Get());
    return pAsset;
#else
    return (T*)iter->second.Get();
#endif
}

template<typename T>
inline void CAssetManager::AddAsset(const std::wstring& key, Ptr<T> asset)
{
    Ptr<T> pFindAsset = FindAsset<T>(key);

    assert(pFindAsset.Get() == nullptr);

    ASSET_TYPE type = GetAssetType<T>();

    m_assets[(UINT)type].insert(std::make_pair(key, asset.Get()));
    asset->m_key = key;
}
