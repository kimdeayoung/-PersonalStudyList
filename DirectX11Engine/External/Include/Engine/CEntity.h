#pragma once

class CEntity
{
private:
	static UINT g_nextInstanceID;

private:
	std::wstring m_name;
	UINT m_instanceID;

public:
	const std::wstring& GetName() { return m_name; }
	void SetName(const std::wstring& name) { m_name = name; }

	UINT GetInstanceID() { return m_instanceID; }

	//virtual CEntity* Clone() = 0;

public:
	CEntity();
	CEntity(const CEntity& other);
	virtual ~CEntity();
};

