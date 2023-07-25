#pragma once
#include <limits>

namespace lab8
{
	template <typename T, size_t N>
	class FixedVector
	{
	public:
		FixedVector();
		virtual ~FixedVector() = default;

		bool Add(const T& value);
		bool Remove(const T& value);
		const T& Get(unsigned int index) const;
		T& operator[](unsigned int index);
		int GetIndex(const T& value) const;
		size_t GetSize() const;
		size_t GetCapacity() const;
	private:
		T mData[N];
		size_t mSize;
	};

	template<typename T, size_t N>
	FixedVector<T, N>::FixedVector()
		: mSize(0)
	{
	}

	template<typename T, size_t N>
	bool FixedVector<T, N>::Add(const T& value)
	{
		if (N <= mSize)
		{
			return false;
		}

		mData[mSize++] = value;
		return true;
	}

	template<typename T, size_t N>
	bool FixedVector<T, N>::Remove(const T& value)
	{
		int index = GetIndex(value);
		if (index == -1)
		{
			return false;
		}

		unsigned int removeIndex = static_cast<unsigned int>(index);
		for (unsigned int i = removeIndex; i < mSize; ++i)
		{
			mData[i] = mData[i + 1];
		}
		--mSize;
		return true;
	}

	template<typename T, size_t N>
	const T& FixedVector<T, N>::Get(unsigned int index) const
	{
		return mData[index];
	}

	template<typename T, size_t N>
	T& FixedVector<T, N>::operator[](unsigned int index)
	{
		return mData[index];
	}

	template<typename T, size_t N>
	int FixedVector<T, N>::GetIndex(const T& value) const
	{
		int size = static_cast<int>(mSize);
		int findIndex = size;
		for (int i = 0; i < size; ++i)
		{
			if (mData[i] == value)
			{
				findIndex = i;
				break;
			}
		}

		if (findIndex == size)
		{
			return -1;
		}
		else
		{
			return findIndex;
		}
	}

	template<typename T, size_t N>
	size_t FixedVector<T, N>::GetSize() const
	{
		return mSize;
	}

	template<typename T, size_t N>
	size_t FixedVector<T, N>::GetCapacity() const
	{
		return N;
	}
}