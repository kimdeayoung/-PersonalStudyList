#pragma once
#include "Singleton.h"

enum class Key
{
    W,
    S,
    A,
    D,

    _0,
    _1,
    _2,
    _3,
    _4,
    _5,
    _6,
    _7,
    _8,
    _9,

    LEFT,
    RIGHT,
    UP,
    DOWN,

    ENTER,
    ESCAPE,
    SPACE,
    LSHIFT,
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
    KEY_STATE state;
    bool prevPressed;
};

class KeyManager :
    public CSingleton<KeyManager>
{
private:
    std::vector<KeyInfo> m_keyInfos;

public:
    void Init();
    void Tick();

    Singleton(KeyManager)
};

