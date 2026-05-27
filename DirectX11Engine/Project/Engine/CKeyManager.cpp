#include "pch.h"
#include "CKeyManager.h"

#include "CEngineBase.h"

UINT g_KeyValue[(UINT)KEY::LENGTH]
=
{
	'W', 'S', 'A', 'D',
	'Z', 'X', 'C', 'V',

	'R', 'T', 'Y', 'U', 'I','O', 'P',

	'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',

	VK_NUMPAD0, VK_NUMPAD1, VK_NUMPAD2, VK_NUMPAD3, VK_NUMPAD4,
	VK_NUMPAD5, VK_NUMPAD6, VK_NUMPAD7, VK_NUMPAD8, VK_NUMPAD9,

	VK_LEFT,
	VK_RIGHT,
	VK_UP,
	VK_DOWN,

	VK_LBUTTON,
	VK_RBUTTON,

	VK_RETURN,
	VK_ESCAPE,
	VK_SPACE,
	VK_LSHIFT,
	VK_MENU,
	VK_CONTROL,
};

CKeyManager::CKeyManager()
{

}

CKeyManager::~CKeyManager()
{

}

void CKeyManager::Init()
{
	for (int i = 0; i < (int)KEY::LENGTH; ++i)
	{
		KeyInfo keyInfo = {};
		keyInfo.State = KEY_STATE::NONE;
		keyInfo.PrevPressed = false;
		m_vecKey.push_back(keyInfo);
	}
}

void CKeyManager::Update()
{
	for (int i = 0; i < (int)KEY::LENGTH; ++i)
	{
		if (GetAsyncKeyState(g_KeyValue[i]) & 0x8001)
		{
			if (m_vecKey[i].PrevPressed)
			{
				m_vecKey[i].State = KEY_STATE::PRESSED;
			}
			else
			{
				m_vecKey[i].State = KEY_STATE::TAP;
			}

			m_vecKey[i].PrevPressed = true;
		}
		else
		{
			if (m_vecKey[i].PrevPressed)
			{
				m_vecKey[i].State = KEY_STATE::RELEASED;
			}
			else
			{
				m_vecKey[i].State = KEY_STATE::NONE;
			}

			m_vecKey[i].PrevPressed = false;
		}
	}

	POINT mousePos;
	GetCursorPos(&mousePos);
	ScreenToClient(CEngineBase::GetInstance()->GetMainHwnd(), &mousePos);

	m_prevMousePos = m_curMousePos;

	m_curMousePos = Vector2((float)mousePos.x, (float)mousePos.y);

	m_dragDirection = (m_curMousePos - m_prevMousePos);
	m_dragDirection.y = -m_dragDirection.y;
	m_dragDirection.Normalize();
}