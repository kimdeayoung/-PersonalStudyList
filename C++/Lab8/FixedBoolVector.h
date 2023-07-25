#pragma once

namespace lab8
{
	template<size_t N>
	class FixedVector<bool, N>
	{
	public:
		FixedVector();
		virtual ~FixedVector() = default;

		bool Add(const bool& value);
		bool Remove(const bool& value);
		const bool Get(unsigned int index);
		const bool operator[](unsigned int index);
		int GetIndex(const bool& value);
		size_t GetSize() const;
		size_t GetCapacity() const;
	private:
		unsigned int getDataArrIndex(unsigned int index);

		enum { MAX_SIZE = 32 };
		int mData[N / MAX_SIZE + 1];
		size_t mSize;
	};

	template<size_t N>
	FixedVector<bool, N>::FixedVector()
		: mSize(0)
	{
	}

	template<size_t N>
	bool FixedVector<bool, N>::Add(const bool& value)
	{
		if (N <= mSize)
		{
			return false;
		}
		
		unsigned int arrIndex = getDataArrIndex(mSize);
		if (value)
		{
			mData[arrIndex] |= (1 << mSize++);
		}
		else
		{
			mData[arrIndex] &= ~(1 << mSize++);
		}

		return true;
	}

	template<size_t N>
	bool FixedVector<bool, N>::Remove(const bool& value)
	{
		int index = GetIndex(value);
		if (index == -1)
		{
			return false;
		}

		unsigned int dataArrIndex = getDataArrIndex(index);
		unsigned int findIndex = static_cast<unsigned int>(index);
		unsigned int loopCount = static_cast<unsigned int>(index);

		for (unsigned int i = dataArrIndex; i <= getDataArrIndex(mSize); ++i)
		{
			while (findIndex < MAX_SIZE - 1)
			{
				bool data = mData[i] & (1 << (findIndex + 1));
				if (data)
				{
					mData[i] |= (1 << findIndex);
				}
				else
				{
					mData[i] &= ~(1 << findIndex);
				}
				++findIndex;

				if (mSize <= ++loopCount)
				{
					--mSize;
					return true;
				}
			}

			bool data = mData[i + 1] & 1;
			if (data)
			{
				mData[i] |= (1 << findIndex);
			}
			else
			{
				mData[i] &= ~(1 << findIndex);
			}
			++loopCount;
			findIndex = 0;
		}
		--mSize;
		return true;
	}

	template<size_t N>
	const bool FixedVector<bool, N>::Get(unsigned int index)
	{
		int value = mData[getDataArrIndex(index)];
		return value & (1 << (index % MAX_SIZE));
	}

	template<size_t N>
	const bool FixedVector<bool, N>::operator[](unsigned int index)
	{
		return Get(index);
	}

	template<size_t N>
	int FixedVector<bool, N>::GetIndex(const bool& value) 
	{
		unsigned int findIndex = 0;
		for (unsigned int i = 0; i <= getDataArrIndex(mSize); ++i)
		{
			int dataValue = mData[i];
			unsigned int index = 0;
			while (index < MAX_SIZE)
			{
				bool data = dataValue & (1 << index++);
				if (findIndex >= mSize)
				{
					return -1;
				}
				if (data == value)
				{
					return findIndex;
				}
				++findIndex;
			}
		}

		return -1;
	}

	template<size_t N>
	size_t FixedVector<bool, N>::GetSize() const
	{
		return mSize;
	}

	template<size_t N>
	size_t FixedVector<bool, N>::GetCapacity() const
	{
		return N;
	}

	template<size_t N>
	unsigned int FixedVector<bool, N>::getDataArrIndex(unsigned int index)
	{
		return index / MAX_SIZE;
	}
}