#pragma once
#include "Singleton.h"

enum class KEY
{
	W, S, A, D,
	Z, X, C, V,
	R, T, Y, U, I, O, P,

	_0, _1, _2, _3, _4, _5, _6, _7, _8, _9,

	NUM0, NUM1, NUM2, NUM3, NUM4,
	NUM5, NUM6, NUM7, NUM8, NUM9,

	LEFT,
	RIGHT,
	UP,
	DOWN,

	LB_MOUSE,
	RB_MOUSE,

	ENTER,
	ESC,
	SPACE,
	LSHILFT,
	ALT,
	CTRL,

	LENGTH,
};


enum class KEY_STATE
{
	TAP,
	PRESSED,
	RELEASED,
	NONE,
};

struct KeyInfo
{
	KEY_STATE   State;
	bool        PrevPressed;
};

class CKeyManager :
	public CSingleton<CKeyManager>
{
private:
	std::vector<KeyInfo>   m_vecKey;
	Vector2 m_curMousePos;
	Vector2 m_prevMousePos;
	Vector2 m_dragDirection;

public:
	void Init();
	void Update();

public:
	KEY_STATE GetKeyState(KEY key) { return m_vecKey[(UINT)key].State; }

	Vector2 GetCurMousePos() { return m_curMousePos; }
	Vector2 GetPrevMousePos() { return m_prevMousePos; }
	Vector2 GetDragDirection() { return m_dragDirection; }

	Singleton(CKeyManager);
};

