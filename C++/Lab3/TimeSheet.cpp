#include "TimeSheet.h"

namespace lab3
{
	TimeSheet::TimeSheet(const char* name, unsigned int maxEntries)
		: mEntries(0), mMaxEntries(maxEntries)
	{
		mName = std::string(name);
		mTimes = new int[mMaxEntries];
	}

	TimeSheet::TimeSheet(const TimeSheet& rhs)
		: mEntries(rhs.mEntries), mMaxEntries(rhs.mMaxEntries)
	{
		mName = std::string(rhs.mName);
		mTimes = new int[mMaxEntries];

		int* timesPtr = mTimes;
		int* rhsTimesPtr = rhs.mTimes;
		for (unsigned int i = 0; i < rhs.mEntries; ++i)
		{
			*timesPtr++ = *rhsTimesPtr++;
		}
	}

	TimeSheet::~TimeSheet()
	{
		mName.clear();
		delete[] mTimes;
	}

	void TimeSheet::AddTime(int timeInHours)
	{
		if (mEntries < mMaxEntries)
		{
			if (timeInHours >= 1 && timeInHours <= 10)
			{
				*(mTimes + mEntries++) = timeInHours;
			}
		}
	}

	int TimeSheet::GetTimeEntry(unsigned int index) const
	{
		if (mEntries <= index)
		{
			return -1;
		}

		return *(mTimes + index);
	}

	int TimeSheet::GetTotalTime() const
	{
		int totalTime = 0;

		int* timesPtr = mTimes;
		for (unsigned int i = 0; i < mEntries; ++i)
		{
			totalTime += *timesPtr++;
		}
		return totalTime;
	}

	float TimeSheet::GetAverageTime() const
	{
		if (mEntries == 0)
		{
			return 0.0f;
		}

		return static_cast<float>(GetTotalTime()) / mEntries;
	}

	float TimeSheet::GetStandardDeviation() const
	{
		float standardDeviation = 0.0f;

		float average = GetAverageTime();
		if (average == 0.0f)
		{
			return 0.0f;
		}

		int* timesPtr = mTimes;
		for (unsigned int i = 0; i < mEntries; ++i)
		{
			float value = static_cast<float>(*timesPtr++) - average;
			standardDeviation += value * value;
		}

		standardDeviation /= mEntries;
		return static_cast<float>(sqrt(standardDeviation));
	}

	const std::string& TimeSheet::GetName() const
	{
		return mName;
	}

	bool TimeSheet::operator==(const TimeSheet& rhs) const
	{
		if (mName != rhs.mName)
		{
			return false;
		}
		else if (mEntries != rhs.mEntries)
		{
			return false;
		}
		else if (mMaxEntries != rhs.mMaxEntries)
		{
			return false;
		}

		int* timesPtr = mTimes;
		int* rhsTimesPtr = rhs.mTimes;
		for (unsigned int i = 0; i < rhs.mEntries; ++i)
		{
			if (*timesPtr++ != *rhsTimesPtr++)
			{
				return false;
			}
		}

		return true;
	}

	TimeSheet& TimeSheet::operator=(const TimeSheet& rhs)
	{
		if (*this == rhs)
		{
			return *this;
		}

		mName = rhs.mName;
		mEntries = rhs.mEntries;
		mMaxEntries = rhs.mMaxEntries;

		delete[] mTimes;
		mTimes = new int[mMaxEntries];
		int* timesPtr = mTimes;
		int* rhsTimesPtr = rhs.mTimes;
		for (unsigned int i = 0; i < rhs.mEntries; ++i)
		{
			*timesPtr++ = *rhsTimesPtr++;
		}

		return *this;
	}
}