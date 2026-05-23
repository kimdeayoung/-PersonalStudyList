#pragma once

template<typename T>
class Ptr
{
private:
	T* m_asset;

public:
	T* Get() const { return m_asset; }
	T** GetAddressOf() const { return &m_asset; }

public:
	bool operator == (T* asset) const { return m_asset == asset; }
	bool operator != (T* asset) const { return m_asset != asset; }

	bool operator == (std::nullptr_t) const { return m_asset == nullptr; }
	bool operator != (std::nullptr_t) const { return m_asset != nullptr; }

	bool operator == (const Ptr<T>& asset) const
	{
		return m_asset == asset.m_asset;
	}

	bool operator != (const Ptr<T>& asset) const
	{
		return m_asset != asset.m_asset;
	}

	void operator = (T* asset)
	{
		if (m_asset != nullptr)
		{
			m_asset->Release();
		}

		m_asset = asset;

		if (m_asset != nullptr)
		{
			m_asset->AddRefCount();
		}
	}

	void operator = (const Ptr<T>& other)
	{
		if (m_asset != nullptr)
		{
			m_asset->Release();
		}

		m_asset = other.m_asset;

		if (m_asset != nullptr)
		{
			m_asset->AddRefCount();
		}
	}

	T* operator->()
	{
		return m_asset;
	}

public:
	Ptr()
		: m_asset(nullptr)
	{

	}

	Ptr(T* asset)
		: m_asset(asset)
	{
		if (m_asset != nullptr)
		{
			m_asset->AddRefCount();
		}
	}

	Ptr(const Ptr<T>& other)
		: m_asset(other.m_asset)
	{
		if (m_asset != nullptr)
		{
			m_asset->AddRefCount();
		}
	}

	~Ptr()
	{
		if (m_asset != nullptr)
		{
			m_asset->Release();
		}
	}
};

template<typename T>
bool operator == (void* asset, const Ptr<T>& ptr)
{
	return asset == ptr.Get();
}

template<typename T>
bool operator != (void* asset, const Ptr<T>& ptr)
{
	return asset != ptr.Get();
}