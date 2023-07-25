#pragma once
#include <string>

namespace lab3
{
	class TimeSheet
	{
	public:
		TimeSheet(const char* name, unsigned int maxEntries);
		TimeSheet(const TimeSheet& rhs);
		~TimeSheet();

		void AddTime(int timeInHours);
		int GetTimeEntry(unsigned int index) const;
		int GetTotalTime() const;
		float GetAverageTime() const;
		float GetStandardDeviation() const;
		const std::string& GetName() const;
		bool operator==(const TimeSheet& rhs) const;
		TimeSheet& operator=(const TimeSheet& rhs);

	private:
		std::string mName;
		int* mTimes;

		unsigned int mEntries;
		unsigned int mMaxEntries;
	};
}