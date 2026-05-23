#pragma once
#include "CAsset.h"

#include "assets.h"

class CMaterial :
	public CAsset
{
private:
	MaterialConst m_constValue;

	Ptr<CGraphicShader> m_shader;
	Ptr<CTexture> m_texture[TEXTURE_PARAM::LENGTH];

public:
	Ptr<CGraphicShader> GetGraphicShader() { return m_shader; }
	void SetShader(Ptr<CGraphicShader> shader) { m_shader = shader; }

	template<typename T>
	void SetScalarParam(SCALAR_PARAM param, const T& value);
	void SetTexture(TEXTURE_PARAM param, Ptr<CTexture> texture) { m_texture[param] = texture; }

public:
	void Binding();

	virtual int Load(const std::wstring& path) { return S_OK; }
	virtual int Save(const std::wstring& path) { return S_OK; }

public:
	CMaterial();
	~CMaterial();
};

template<typename T>
inline void CMaterial::SetScalarParam(SCALAR_PARAM param, const T& value)
{
	if constexpr (std::is_same_v<T, int>)
	{
		assert(param >= INT_0 && param <= INT_3);
		m_constValue.intValue[param - INT_0] = value;
	}
	else if constexpr (std::is_same_v<T, float>)
	{
		assert(param >= FLOAT_0 && param <= FLOAT_3);
		m_constValue.floatValue[param - FLOAT_0] = value;
	}
	else if constexpr (std::is_same_v<T, Vector2>)
	{
		assert(param >= VECTOR2_0 && param <= VECTOR2_3);
		m_constValue.vec2Value[param - VECTOR2_0] = value;
	}
	else if constexpr (std::is_same_v<T, Vector4>)
	{
		assert(param >= VECTOR4_0 && param <= VECTOR4_3);
		m_constValue.vec4Value[param - VECTOR4_0] = value;
	}
	else if constexpr (std::is_same_v<T, Matrix>)
	{
		assert(param >= MATRIX_0 && param <= MATRIX_3);
		m_constValue.matrixValue[param - MATRIX_0] = value;
	}
}
