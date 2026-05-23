#include "pch.h"
#include "CAssetManager.h"
#include "CPathManager.h"
#include "CDevice.h"

void CAssetManager::Init()
{
	CreateDefaultMesh();

	CreateDefaultTexture();

	CreateDefaultGraphicShader();
	CreateDefaultComputeShader();

	CreateDefaultMaterial();
}

void CAssetManager::CreateDefaultMesh()
{
	Vertex vertex;

	std::vector<Vertex> vertexes;
	std::vector<UINT> indexes;

	vertex.position = Vector3(-0.5, 0.5f, 0.f);
	vertex.color = Vector4(1.f, 0.f, 0.f, 1.f);
	vertex.uv = Vector2(0.f, 0.f);
	vertexes.push_back(vertex);

	vertex.position = Vector3(0.5f, 0.5f, 0.f);
	vertex.color = Vector4(0.f, 1.f, 0.f, 1.f);
	vertex.uv = Vector2(1.f, 0.f);
	vertexes.push_back(vertex);

	vertex.position = Vector3(0.5f, -0.5f, 0.f);
	vertex.color = Vector4(0.f, 0.f, 1.f, 1.f);
	vertex.uv = Vector2(1.f, 1.f);
	vertexes.push_back(vertex);

	vertex.position = Vector3(-0.5, -0.5f, 0.f);
	vertex.color = Vector4(0.f, 1.f, 0.f, 1.f);
	vertex.uv = Vector2(0.f, 1.f);
	vertexes.push_back(vertex);

	{
		indexes.push_back(0);
		indexes.push_back(2);
		indexes.push_back(3);

		indexes.push_back(0);
		indexes.push_back(1);
		indexes.push_back(2);

		Ptr<CMesh> rectMesh(new CMesh());
		rectMesh->Create(vertexes.data(), (UINT)vertexes.size(), indexes.data(), (UINT)indexes.size());
		AddAsset<CMesh>(L"RectMesh", rectMesh);
	}
	
	indexes.clear();

	{
		indexes.push_back(0);
		indexes.push_back(1);
		indexes.push_back(2);
		indexes.push_back(3);
		indexes.push_back(0);

		Ptr<CMesh> rectMesh(new CMesh());
		rectMesh->Create(vertexes.data(), (UINT)vertexes.size(), indexes.data(), (UINT)indexes.size());
		AddAsset<CMesh>(L"RectMesh_Debug", rectMesh);
	}

	vertexes.clear();

	{
		Vertex vertex;
		vertex.position = Vector3(0, 0, 0);
		vertex.color = Vector4(1.f, 1.f, 1.f, 1.f);
		vertexes.push_back(vertex);
	}

	float radius = 0.5f;
	UINT slice = 40;
	float angleStep = (2 * DirectX::XM_PI) / slice;

	float angle = 0.f;

	for (UINT i = 0; i <= slice; ++i)
	{
		Vertex vertex;
		vertex.position = Vector3(cosf(angle) * radius, sinf(angle) * radius, 0);
		vertex.color = Vector4(1.f, 1.f, 1.f, 1.f);

		vertexes.push_back(vertex);
		angle += angleStep;

		indexes.push_back(0);
		indexes.push_back(i + 2);
		indexes.push_back(i + 1);
	}

	for (UINT i = 0; i < slice; ++i)
	{
		indexes.push_back(0);
		indexes.push_back(i + 2);
		indexes.push_back(i + 1);
	}

	Ptr<CMesh> circleMesh(new CMesh());
	circleMesh->Create(vertexes.data(), (UINT)vertexes.size(), indexes.data(), (UINT)indexes.size());
	AddAsset(L"CircleMesh", circleMesh);
}

void CAssetManager::CreateDefaultTexture()
{
	Load<CTexture>(L"background", L"texture\\background.png");
}

void CAssetManager::CreateDefaultMaterial()
{
	{
		Ptr<CMaterial> material(new CMaterial);
		material->SetName(L"StdMat");
		material->SetShader(FindAsset<CGraphicShader>(L"Std2DShader"));

		AddAsset<CMaterial>(L"StdMat", material);
	}
	
	{
		Ptr<CMaterial> material(new CMaterial);
		material->SetName(L"DebugShapeMat");
		material->SetShader(FindAsset<CGraphicShader>(L"DebugShape"));

		AddAsset<CMaterial>(L"DebugShapeMat", material);
	}
}

void CAssetManager::CreateDefaultGraphicShader()
{
	std::wstring path = CPathManager::GetInstance()->GetContentPath();

	{
		Ptr<CGraphicShader> pShader(new CGraphicShader);
		pShader->CreateVertexShader(path + L"shader\\Std2D.fx", "VS_Std2D");
		pShader->CreatePixelShader(path + L"shader\\Std2D.fx", "PS_Std2D");

		AddAsset<CGraphicShader>(L"Std2DShader", pShader);
	}
	
	{
		Ptr<CGraphicShader> pShader(new CGraphicShader);
		pShader->CreateVertexShader(path + L"shader\\Debug.fx", "VS_DebugShape");
		pShader->CreatePixelShader(path + L"shader\\Debug.fx", "PS_DebugShape");
		pShader->SetRasterizerType(RASTERIZER_STATE_TYPE::CULL_NONE);
		pShader->SetTopologyType(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);

		AddAsset<CGraphicShader>(L"DebugShape", pShader);
	}
}

void CAssetManager::CreateDefaultComputeShader()
{
}
