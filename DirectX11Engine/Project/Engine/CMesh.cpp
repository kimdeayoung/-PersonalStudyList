#include "pch.h"
#include "CMesh.h"
#include "CDevice.h"

CMesh::CMesh()
	: CAsset(ASSET_TYPE::MESH)
	, m_vertexBufferDesc{}
	, m_vertexCount(0)
	, m_vertexSysMem(nullptr)
	, m_indexBufferDesc{}
	, m_indexCount(0)
	, m_indexSysMem(nullptr)
{
}

CMesh::~CMesh()
{
	if (m_vertexSysMem != nullptr)
	{
		delete[] m_vertexSysMem;
		m_vertexSysMem = nullptr;
	}

	if (m_indexSysMem != nullptr)
	{
		delete[] m_indexSysMem;
		m_indexSysMem = nullptr;
	}
}

int CMesh::Create(Vertex* vertexSysMem, size_t vertexCount, UINT* indexSysMem, size_t indexCount)
{
	
	ID3D11Device* device = CDevice::GetInstance()->GetDevice();

	{
		m_vertexCount = (UINT)vertexCount;

		m_vertexBufferDesc.ByteWidth = sizeof(Vertex) * m_vertexCount;
		m_vertexBufferDesc.MiscFlags = 0;

		// 버퍼의 용도 설정
		m_vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		// 버퍼가 생성 된 후 CPU에 접근해서 GPU에 있는 데이터를 덮어 쓰기가 가능하도록 설정
		m_vertexBufferDesc.CPUAccessFlags = 0;
		m_vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;

		D3D11_SUBRESOURCE_DATA subResourceData;
		subResourceData.pSysMem = vertexSysMem;

		if (FAILED(device->CreateBuffer(&m_vertexBufferDesc, &subResourceData, m_vertexBuffer.GetAddressOf())))
		{
			return E_FAIL;
		}
	}

	{
		m_indexCount = (UINT)indexCount;

		m_indexBufferDesc.ByteWidth = sizeof(UINT) * m_indexCount;
		m_indexBufferDesc.MiscFlags = 0;

		// 버퍼의 용도 설정
		m_indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;

		// 인덱스 버퍼는 수정될 이유가 없어서 기본 설정(읽기 쓰기 불가능)
		m_indexBufferDesc.CPUAccessFlags = 0;
		m_indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;

		D3D11_SUBRESOURCE_DATA subResourceData;
		subResourceData.pSysMem = indexSysMem;

		if (FAILED(device->CreateBuffer(&m_indexBufferDesc, &subResourceData, m_indexBuffer.GetAddressOf())))
		{
			return E_FAIL;
		}
	}
	
	m_vertexSysMem = new Vertex[vertexCount];
	memcpy(m_vertexSysMem, vertexSysMem, sizeof(Vertex) * vertexCount);

	m_indexSysMem = new UINT[indexCount];
	memcpy(m_indexSysMem, indexSysMem, sizeof(UINT) * indexCount);

	return S_OK;
}

void CMesh::Binding()
{
	ID3D11DeviceContext* context = CDevice::GetInstance()->GetDeviceContext();

	UINT stride = sizeof(Vertex);
	UINT offset = 0;

	context->IASetVertexBuffers(0, 1, m_vertexBuffer.GetAddressOf(), &stride, &offset);
	context->IASetIndexBuffer(m_indexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
}

void CMesh::Render()
{
	Binding();

	ID3D11DeviceContext* context = CDevice::GetInstance()->GetDeviceContext();
	context->DrawIndexed(m_indexCount, 0, 0);
}
