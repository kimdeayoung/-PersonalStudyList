#include <cassert>
#include <iostream>
#include "TimeSheet.h"


// 202109 lab3 test cases by seolbeen

void TestAddTime()
{
	lab3::TimeSheet m("mong", 3);
	assert(m.GetTotalTime() == 0);

	m.AddTime(5);
	assert(m.GetTotalTime() == 5);

	m.AddTime(1);
	assert(m.GetTotalTime() == 6);

	m.AddTime(0);
	assert(m.GetTotalTime() == 6);

	m.AddTime(-1);
	assert(m.GetTotalTime() == 6);

	m.AddTime(11);
	assert(m.GetTotalTime() == 6);

	m.AddTime(12);
	assert(m.GetTotalTime() == 6);

	m.AddTime(10);
	assert(m.GetTotalTime() == 16);

	m.AddTime(5);
	assert(m.GetTotalTime() == 16);
}

void TestGetTimeEntry()
{
	lab3::TimeSheet s("shell", 5);
	assert(s.GetTimeEntry(-1) == -1);
	assert(s.GetTimeEntry(0) == -1);
	assert(s.GetTimeEntry(1) == -1);
	assert(s.GetTimeEntry(2) == -1);
	assert(s.GetTimeEntry(3) == -1);
	assert(s.GetTimeEntry(4) == -1);
	assert(s.GetTimeEntry(5) == -1);

	s.AddTime(0);
	assert(s.GetTimeEntry(-1) == -1);
	assert(s.GetTimeEntry(0) == -1);
	assert(s.GetTimeEntry(1) == -1);
	assert(s.GetTimeEntry(2) == -1);
	assert(s.GetTimeEntry(3) == -1);
	assert(s.GetTimeEntry(4) == -1);
	assert(s.GetTimeEntry(5) == -1);

	s.AddTime(2);
	assert(s.GetTimeEntry(-1) == -1);
	assert(s.GetTimeEntry(0) == 2);
	assert(s.GetTimeEntry(1) == -1);
	assert(s.GetTimeEntry(2) == -1);
	assert(s.GetTimeEntry(3) == -1);
	assert(s.GetTimeEntry(4) == -1);
	assert(s.GetTimeEntry(5) == -1);

	s.AddTime(4);
	assert(s.GetTimeEntry(-1) == -1);
	assert(s.GetTimeEntry(0) == 2);
	assert(s.GetTimeEntry(1) == 4);
	assert(s.GetTimeEntry(2) == -1);
	assert(s.GetTimeEntry(3) == -1);
	assert(s.GetTimeEntry(4) == -1);
	assert(s.GetTimeEntry(5) == -1);

	s.AddTime(6);
	assert(s.GetTimeEntry(-1) == -1);
	assert(s.GetTimeEntry(0) == 2);
	assert(s.GetTimeEntry(1) == 4);
	assert(s.GetTimeEntry(2) == 6);
	assert(s.GetTimeEntry(3) == -1);
	assert(s.GetTimeEntry(4) == -1);
	assert(s.GetTimeEntry(5) == -1);

	s.AddTime(-1000);
	assert(s.GetTimeEntry(-1) == -1);
	assert(s.GetTimeEntry(0) == 2);
	assert(s.GetTimeEntry(1) == 4);
	assert(s.GetTimeEntry(2) == 6);
	assert(s.GetTimeEntry(3) == -1);
	assert(s.GetTimeEntry(4) == -1);
	assert(s.GetTimeEntry(5) == -1);

	s.AddTime(8);
	assert(s.GetTimeEntry(-1) == -1);
	assert(s.GetTimeEntry(0) == 2);
	assert(s.GetTimeEntry(1) == 4);
	assert(s.GetTimeEntry(2) == 6);
	assert(s.GetTimeEntry(3) == 8);
	assert(s.GetTimeEntry(4) == -1);
	assert(s.GetTimeEntry(5) == -1);

	s.AddTime(10);
	assert(s.GetTimeEntry(-1) == -1);
	assert(s.GetTimeEntry(0) == 2);
	assert(s.GetTimeEntry(1) == 4);
	assert(s.GetTimeEntry(2) == 6);
	assert(s.GetTimeEntry(3) == 8);
	assert(s.GetTimeEntry(4) == 10);
	assert(s.GetTimeEntry(5) == -1);

	s.AddTime(1000);
	assert(s.GetTimeEntry(-1) == -1);
	assert(s.GetTimeEntry(0) == 2);
	assert(s.GetTimeEntry(1) == 4);
	assert(s.GetTimeEntry(2) == 6);
	assert(s.GetTimeEntry(3) == 8);
	assert(s.GetTimeEntry(4) == 10);
	assert(s.GetTimeEntry(5) == -1);
}

void TestGetTotalTime()
{
	lab3::TimeSheet m("mong", 5);
	assert(m.GetTotalTime() == 0);

	m.AddTime(-1);
	assert(m.GetTotalTime() == 0);

	m.AddTime(0);
	assert(m.GetTotalTime() == 0);

	m.AddTime(1);
	assert(m.GetTotalTime() == 1);

	m.AddTime(2);
	assert(m.GetTotalTime() == 3);

	m.AddTime(3);
	assert(m.GetTotalTime() == 6);

	m.AddTime(10);
	assert(m.GetTotalTime() == 16);

	m.AddTime(11);
	assert(m.GetTotalTime() == 16);

	m.AddTime(12);
	assert(m.GetTotalTime() == 16);

	m.AddTime(9);
	assert(m.GetTotalTime() == 25);

	m.AddTime(9);
	assert(m.GetTotalTime() == 25);
}

void TestGetAverageTime()
{
	lab3::TimeSheet s("shell", 10);
	assert(s.GetAverageTime() == 0.f);

	s.AddTime(-1);
	assert(s.GetAverageTime() == 0.f);

	s.AddTime(0);
	assert(s.GetAverageTime() == 0.f);

	s.AddTime(11);
	assert(s.GetAverageTime() == 0.f);

	s.AddTime(12);
	assert(s.GetAverageTime() == 0.f);

	int nums[] = { 4, 7, 6, 5, 1, 2, -1, -1, -1, 4, 7, 6, 5, 1, 2 };
	float sum = 0.f;
	float average = 0.f;
	unsigned int count = 0;

	for (int i = 0; i < 15; i++)
	{
		if (nums[i] >= 1 &&
			nums[i] <= 12 &&
			count < 10)
		{
			sum += nums[i];
			average = sum / ++count;
		}

		s.AddTime(nums[i]);
		assert(s.GetAverageTime() == average);
	}
}

void TestGetStandardDeviation()
{
	// Values used in assert are calculated here:
	// https://www.calculator.net/standard-deviation-calculator.html

	lab3::TimeSheet s("shell", 10);
	assert(s.GetStandardDeviation() == 0.f);

	s.AddTime(-1);
	s.AddTime(0);
	s.AddTime(11);
	s.AddTime(12);
	assert(s.GetStandardDeviation() == 0.f);

	s.AddTime(4);
	s.AddTime(7);
	s.AddTime(6);
	s.AddTime(5);
	s.AddTime(1);
	s.AddTime(2);
	assert(fabs(2.1147629234083f - s.GetStandardDeviation()) < 0.00001f);

	s.AddTime(-1);
	s.AddTime(0);
	s.AddTime(11);
	s.AddTime(12);
	assert(fabs(2.1147629234083f - s.GetStandardDeviation()) < 0.00001f);

	s.AddTime(7);
	s.AddTime(8);
	assert(fabs(2.3452078799117f - s.GetStandardDeviation()) < 0.00001f);

	s.AddTime(9);
	s.AddTime(10);
	assert(fabs(2.7730849247724f - s.GetStandardDeviation()) < 0.00001f);

	s.AddTime(10);
	s.AddTime(10);
	s.AddTime(10);
	s.AddTime(10);
	assert(fabs(2.7730849247724f - s.GetStandardDeviation()) < 0.00001f);
}

void TestGetName()
{
	lab3::TimeSheet m("mong", 3);
	lab3::TimeSheet s("shell", 3);

	assert(m.GetName() == "mong");
	assert(s.GetName() == "shell");
	assert(m.GetName() != s.GetName());
}

void TestCopyConstructor()
{
	lab3::TimeSheet m("mong", 5);
	m.AddTime(1);
	m.AddTime(2);
	m.AddTime(3);

	lab3::TimeSheet m2 = m;

	assert(m.GetName() == m2.GetName());
	assert(m.GetTimeEntry(0) == m2.GetTimeEntry(0));
	assert(m.GetTimeEntry(1) == m2.GetTimeEntry(1));
	assert(m.GetTimeEntry(2) == m2.GetTimeEntry(2));
	assert(m.GetTimeEntry(3) == m2.GetTimeEntry(3));
	assert(m.GetTimeEntry(4) == m2.GetTimeEntry(4));
	assert(m.GetTotalTime() == m2.GetTotalTime());
	assert(m.GetAverageTime() == m2.GetAverageTime());
	assert(m.GetStandardDeviation() == m2.GetStandardDeviation());

	m.AddTime(4);

	assert(m.GetTimeEntry(0) == m2.GetTimeEntry(0));
	assert(m.GetTimeEntry(1) == m2.GetTimeEntry(1));
	assert(m.GetTimeEntry(2) == m2.GetTimeEntry(2));
	assert(m.GetTimeEntry(3) != m2.GetTimeEntry(3));
	assert(m.GetTimeEntry(4) == m2.GetTimeEntry(4));
	assert(m.GetTotalTime() != m2.GetTotalTime());
	assert(m.GetAverageTime() != m2.GetAverageTime());
	assert(m.GetStandardDeviation() != m2.GetStandardDeviation());

	m2.AddTime(5);

	assert(m.GetTimeEntry(0) == m2.GetTimeEntry(0));
	assert(m.GetTimeEntry(1) == m2.GetTimeEntry(1));
	assert(m.GetTimeEntry(2) == m2.GetTimeEntry(2));
	assert(m.GetTimeEntry(3) != m2.GetTimeEntry(3));
	assert(m.GetTimeEntry(4) == m2.GetTimeEntry(4));
	assert(m.GetTotalTime() != m2.GetTotalTime());
	assert(m.GetAverageTime() != m2.GetAverageTime());
	assert(m.GetStandardDeviation() != m2.GetStandardDeviation());
}

void TestAssignmentOperator()
{
	lab3::TimeSheet m("mong", 3);
	m.AddTime(1);
	m.AddTime(2);
	m.AddTime(3);

	lab3::TimeSheet s("shell", 5);
	s.AddTime(2);
	s.AddTime(4);
	s.AddTime(6);
	s.AddTime(8);
	s.AddTime(10);

	assert(m.GetName() == "mong");
	assert(m.GetTimeEntry(0) == 1);
	assert(m.GetTimeEntry(1) == 2);
	assert(m.GetTimeEntry(2) == 3);
	assert(m.GetTimeEntry(3) == -1);
	assert(m.GetTimeEntry(4) == -1);

	m = m;

	assert(m.GetName() == "mong");
	assert(m.GetTimeEntry(0) == 1);
	assert(m.GetTimeEntry(1) == 2);
	assert(m.GetTimeEntry(2) == 3);
	assert(m.GetTimeEntry(3) == -1);
	assert(m.GetTimeEntry(4) == -1);

	m = s;

	assert(m.GetName() == "shell");
	assert(m.GetTimeEntry(0) == 2);
	assert(m.GetTimeEntry(1) == 4);
	assert(m.GetTimeEntry(2) == 6);
	assert(m.GetTimeEntry(3) == 8);
	assert(m.GetTimeEntry(4) == 10);
}

int main()
{
	TestAddTime();
	TestGetTimeEntry();
	TestGetTotalTime();
	TestGetAverageTime();
	TestGetStandardDeviation();
	TestGetName();
	TestCopyConstructor();
	TestAssignmentOperator();

	return 0;
}