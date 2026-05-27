#pragma once

#define Singleton(Type)		private:\
								Type();\
								Type(const Type& other) = delete;\
							public:\
								~Type();\
								friend class CSingleton<Type>;

#define KEY_CHECK(Key, State) CKeyManager::GetInstance()->GetKeyState(Key) == State
#define KEY_TAB(Key) KEY_CHECK(Key, KEY_STATE::TAP)
#define KEY_PRESSED(Key) KEY_CHECK(Key, KEY_STATE::PRESSED)
#define KEY_RELEASED(Key) KEY_CHECK(Key, KEY_STATE::RELEASED)
#define KEY_NONE(Key) KEY_CHECK(Key, KEY_STATE::NONE)

#define DT CTimeManager::GetInstance()->GetDeltaTime()

#define MAX_LAYER 32