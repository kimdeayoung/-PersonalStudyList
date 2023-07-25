#pragma once

#include "Struct.h"

#include <limits>
#include <stack>

namespace assignment3
{
	template <typename T>
	class SmartStack
	{
	public:
		SmartStack();
		~SmartStack();

		void Push(T value);
		T Pop();
		T Peek();
		T GetMax();
		T GetMin();
		double GetAverage();
		T GetSum();
		double GetVariance();
		double GetStandardDeviation();
		unsigned int GetCount();
	private:
		std::stack<T> mStack;
		std::stack<ExtremeValues<T>> mExtremeValueQueue;

		double mSquareSum;
		T mAccumulateValue;
		double mAverage;
	};

	template<typename T>
	SmartStack<T>::SmartStack()
		: mSquareSum(0), mAccumulateValue(0), mAverage(0)
	{
	}

	template<typename T>
	SmartStack<T>::~SmartStack()
	{
	}

	template<typename T>
	void SmartStack<T>::Push(T value)
	{
		mStack.push(value);

		mAccumulateValue += value;
		mAverage = static_cast<double>(mAccumulateValue) / mStack.size();
		mSquareSum += value * value;

		if (mExtremeValueQueue.empty())
		{
			ExtremeValues<T> values;
			values.minValue = value;
			values.maxValue = value;
			mExtremeValueQueue.push(values);
		}
		else
		{
			ExtremeValues<T> extremeValues = mExtremeValueQueue.top();

			ExtremeValues<T> values;
			values.minValue = value < extremeValues.minValue ? value : extremeValues.minValue;
			values.maxValue = value > extremeValues.maxValue ? value : extremeValues.maxValue;
			mExtremeValueQueue.push(values);
		}
	}

	template<typename T>
	T SmartStack<T>::Pop()
	{
		T value = mStack.top();
		mStack.pop();

		mAccumulateValue -= value;
		mAverage = static_cast<double>(mAccumulateValue) / mStack.size();
		mSquareSum -= value * value;

		mExtremeValueQueue.pop();

		return value;
	}

	template<typename T>
	T SmartStack<T>::Peek()
	{
		return mStack.top();
	}

	template<typename T>
	T SmartStack<T>::GetMax()
	{
		if (mExtremeValueQueue.empty())
		{
			return std::numeric_limits<T>::lowest();
		}

		ExtremeValues<T> extremeValues = mExtremeValueQueue.top();
		return extremeValues.maxValue;
	}

	template<typename T>
	T SmartStack<T>::GetMin()
	{
		if (mExtremeValueQueue.empty())
		{
			return std::numeric_limits<T>::max();
		}

		ExtremeValues<T> extremeValues = mExtremeValueQueue.top();
		return extremeValues.minValue;
	}

	template<typename T>
	double SmartStack<T>::GetAverage()
	{
		return mAverage;
	}

	template<typename T>
	T SmartStack<T>::GetSum()
	{
		return mAccumulateValue;
	}

	template<typename T>
	double SmartStack<T>::GetVariance()
	{
		double result = static_cast<double>(mSquareSum) / mStack.size() - pow(mAverage, 2);
		return result;
	}

	template<typename T>
	double SmartStack<T>::GetStandardDeviation()
	{
		return sqrt(GetVariance());
	}

	template<typename T>
	unsigned int SmartStack<T>::GetCount()
	{
		return mStack.size();
	}
}
