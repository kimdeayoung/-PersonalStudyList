#pragma once

template<typename T>
class CSingleton
{
private:
	typedef void(*DESTROY)(void);

private:
	static T* m_This;
public:
	static T* GetInstance()
	{
		if (m_This == nullptr)
		{
			m_This = new T;
		}
		return m_This;
	}

	static void Destroy()
	{
		if (m_This != nullptr)
		{
			delete m_This;
			m_This = nullptr;
		}
	}

protected:
	CSingleton() 
	{
		atexit((DESTROY)&CSingleton<T>::Destroy);
	}
	CSingleton(const CSingleton& other) = delete;
	~CSingleton() {}
};

template<typename T>
T* CSingleton<T>::m_This = nullptr;