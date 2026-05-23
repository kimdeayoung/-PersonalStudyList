#include "pch.h"
#include "CConstBuffer.h"
#include "CDevice.h"

CConstBuffer::CConstBuffer()
	: m_bufferDesc{},
	m_type(CONST_BUFFER_TYPE::LENGTH)
{

}

CConstBuffer::~CConstBuffer()
{

}

int CConstBuffer::Create(size_t bufferSize, CONST_BUFFER_TYPE type)
{
	m_type = type;

	m_bufferDesc.ByteWidth = bufferSize;
	m_bufferDesc.MiscFlags = 0;

	// 버퍼의 용도 설정
	m_bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	// 버퍼가 생성 된 후 CPU에 접근해서 GPU에 있는 데이터를 덮어 쓰기가 가능하도록 설정
	m_bufferDesc.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
	m_bufferDesc.Usage = D3D11_USAGE_DYNAMIC;

	ID3D11Device* device = CDevice::GetInstance()->GetDevice();
	if (FAILED(device->CreateBuffer(&m_bufferDesc, nullptr, m_constantBuffer.GetAddressOf())))
	{
		return E_FAIL;
	}

	return S_OK;
}

void CConstBuffer::SetData(void* data)
{
	ID3D11DeviceContext* context = CDevice::GetInstance()->GetDeviceContext();

	//System Memory의 값을 Gpu 메모리로 전달 (CPUAccessFlags = D3D10_CPU_ACCESS_WRITE; 인 경우에만 가능)
	//Map 함수를 사용하여 GPU메모리에 매핑된 데이터 개체를 받고 난 후 해당 개체에 데이터를 셋업
	// 즉시 되는 것은 아니며 로직상 추후 GPU 메모리로 전달, 데이터 전달 후 UnMap
	D3D11_MAPPED_SUBRESOURCE subResource = {};
	context->Map(m_constantBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &subResource);

	memcpy(subResource.pData, data, m_bufferDesc.ByteWidth);
	context->Unmap(m_constantBuffer.Get(), 0);
}

void CConstBuffer::Binding()
{
	//ConstantBuffer 데이터의 경우 특정 셰이더 시점에만 값이 유효함(셰이더 동작이 바뀌면 값이 전부 초기화)
	//필요시 각 셰이더 시점마다 데이터들을 세팅해 줘야함 (아마 나중에 최적화 할땐 이거 타입별로 필요한 데이터별로 쪼개서 관리하는 식으로 하면 좋을듯)

	ID3D11DeviceContext* context = CDevice::GetInstance()->GetDeviceContext();
	context->VSSetConstantBuffers((UINT)m_type, 1, m_constantBuffer.GetAddressOf());
	context->PSSetConstantBuffers((UINT)m_type, 1, m_constantBuffer.GetAddressOf());
	context->DSSetConstantBuffers((UINT)m_type, 1, m_constantBuffer.GetAddressOf());
	context->HSSetConstantBuffers((UINT)m_type, 1, m_constantBuffer.GetAddressOf());
	context->GSSetConstantBuffers((UINT)m_type, 1, m_constantBuffer.GetAddressOf());
}
