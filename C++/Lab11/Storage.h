#pragma once

#include <memory>

namespace lab11
{
	template<typename T>
	class Storage
	{
	public:
		Storage(unsigned int length);
		Storage(unsigned int length, const T& initialValue);

		Storage(const Storage<T>& other);
		Storage<T>& operator= (const Storage<T>& other);
		bool operator== (const Storage<T>& other);

		Storage(Storage&& other);
		Storage<T>& operator= (Storage&& other);

		bool Update(unsigned int index, const T& data);
		const std::unique_ptr<T[]>& GetData() const;
		unsigned int GetSize() const;
	private:
		std::unique_ptr<T[]> mStorage;
		unsigned int mLength;
	};

	template<typename T>
	Storage<T>::Storage(unsigned int length)
		: mStorage(std::make_unique<T[]>(length)), mLength(length)
	{
		memset(mStorage.get(), 0, sizeof(T) * length);
	}

	template<typename T>
	Storage<T>::Storage(unsigned int length, const T& initialValue)
		: mStorage(std::make_unique<T[]>(length)), mLength(length)
	{
		for (unsigned int i = 0; i < length; ++i)
		{
			mStorage[i] = initialValue;
		}
	}

	template<typename T>
	Storage<T>::Storage(const Storage<T>& other)
		: mStorage(std::make_unique<T[]>(other.mLength)), mLength(other.mLength)
	{
		for (unsigned int i = 0; i < other.mLength; ++i)
		{
			mStorage[i] = other.mStorage[i];
		}
	}

	template<typename T>
	Storage<T>& Storage<T>::operator=(const Storage<T>& other)
	{
		if (*this == other)
		{
			return *this;
		}

		if (mStorage)
		{
			mStorage.reset();
		}

		mStorage = std::make_unique<T[]>(other.mLength);
		for (unsigned int i = 0; i < other.mLength; ++i)
		{
			mStorage[i] = other.mStorage[i];
		}
		mLength = other.mLength;
		return *this;
	}

	template<typename T>
	bool Storage<T>::operator==(const Storage<T>& other)
	{
		if (mLength != other.mLength)
		{
			return false;
		}

		else if (memcmp(mStorage.get(), other.mStorage.get(), sizeof(T) * mLength) != 0)
		{
			return false;
		}
		return true;
	}

	template<typename T>
	Storage<T>::Storage(Storage&& other)
		: mStorage(std::move(other.mStorage)), mLength(other.mLength)
	{
		other.mLength = 0;
	}

	template<typename T>
	Storage<T>& Storage<T>::operator= (Storage&& other)
	{
		if (this != &other)
		{
			if (mStorage)
			{
				mStorage.reset();
			}

			mStorage = std::move(other.mStorage);
			mLength = other.mLength;

			other.mLength = 0;
		}
		return *this;
	}

	template<typename T>
	bool Storage<T>::Update(unsigned int index, const T& data)
	{
		if (index < mLength)
		{
			mStorage[index] = data;
			return true;
		}
		return false;
	}

	template<typename T>
	const std::unique_ptr<T[]>& Storage<T>::GetData() const
	{
		return mStorage;
	}

	template<typename T>
	unsigned int Storage<T>::GetSize() const
	{
		return mLength;
	}
}