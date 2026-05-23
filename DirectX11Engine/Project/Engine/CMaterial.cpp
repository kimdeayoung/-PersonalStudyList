#include "pch.h"
#include "CMaterial.h"

#include "CDevice.h"
#include "CConstBuffer.h"

CMaterial::CMaterial()
	: CAsset(ASSET_TYPE::MATERIAL)
{
}

CMaterial::~CMaterial()
{
}

void CMaterial::Binding()
{
	for (int i = 0; i < TEXTURE_PARAM::LENGTH; ++i)
	{
		if (m_texture[i] == nullptr)
		{
			//현재 재질에 Texture 데이터가 불필요할 경우 기존에 사용된 텍스쳐 데이터를 초기화(찌꺼기 제거)
			CTexture::Clear(i);
			continue;
		}

		m_texture[i]->Binding(i);
	}

	if (m_shader.Get() != nullptr)
	{
		m_shader->Binding();
	}

	CConstBuffer* constBuffer = CDevice::GetInstance()->GetConstBuffer(CONST_BUFFER_TYPE::MATERIAL);
	constBuffer->SetData(&m_constValue);
	constBuffer->Binding();
}