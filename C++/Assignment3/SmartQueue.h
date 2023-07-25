#pragma once

#include <limits>
#include <queue>

namespace assignment3
{
	template <typename T>
	class SmartQueue
	{
	public:
		SmartQueue();
		~SmartQueue();

		void Enqueue(T value);
		T Peek();
		T Dequeue();
		T GetMax();
		T GetMin();
		double GetAverage();
		T GetSum();
		double GetVariance();
		double GetStandardDeviation();
		unsigned int GetCount();
	private:
		std::queue<T> mQueue;

		double mSquareSum;
		T mAccumulateValue;
		double mAverage;
	};

	template<typename T>
	SmartQueue<T>::SmartQueue()
		: mSquareSum(0), mAccumulateValue(0), mAverage(0)
	{
	}

	template<typename T>
	SmartQueue<T>::~SmartQueue()
	{
	}

	template<typename T>
	void SmartQueue<T>::Enqueue(T value)
	{
		mQueue.push(value);

		mAccumulateValue += value;
		mAverage = static_cast<double>(mAccumulateValue) / mQueue.size();
		mSquareSum += value * value;
	}

	template<typename T>
	T SmartQueue<T>::Peek()
	{
		return mQueue.front();
	}

	template<typename T>
	T SmartQueue<T>::Dequeue()
	{
		T value = mQueue.front();
		mQueue.pop();

		mAccumulateValue -= value;
		mAverage = static_cast<double>(mAccumulateValue) / mQueue.size();
		mSquareSum -= value * value;

		return value;
	}

	template<typename T>
	T SmartQueue<T>::GetMax()
	{
		if (mQueue.empty())
		{
			return std::numeric_limits<T>::lowest();
		}

		T maxValue = std::numeric_limits<T>::lowest();
		std::queue<T> copyedQueue;
		while (mQueue.empty() == false)
		{
			maxValue = maxValue < mQueue.front() ? mQueue.front() : maxValue;
			copyedQueue.push(mQueue.front());
			mQueue.pop();
		}

		while (copyedQueue.empty() == false)
		{
			mQueue.push(copyedQueue.front());
			copyedQueue.pop();
		}

		return maxValue;
	}

	template<typename T>
	T SmartQueue<T>::GetMin()
	{
		if (mQueue.empty())
		{
			return std::numeric_limits<T>::max();
		}

		T minValue = std::numeric_limits<T>::max();
		std::queue<T> copyedQueue;

		while (mQueue.empty() == false)
		{
			minValue = minValue > mQueue.front() ? mQueue.front() : minValue;
			copyedQueue.push(mQueue.front());
			mQueue.pop();
		}

		while (copyedQueue.empty() == false)
		{
			mQueue.push(copyedQueue.front());
			copyedQueue.pop();
		}

		return minValue;
	}

	template<typename T>
	double SmartQueue<T>::GetAverage()
	{
		return mAverage;
	}

	template<typename T>
	T SmartQueue<T>::GetSum()
	{
		return mAccumulateValue;
	}

	template<typename T>
	double SmartQueue<T>::GetVariance()
	{
		double result = static_cast<double>(mSquareSum) / mQueue.size() - pow(mAverage, 2);
		return result;
	}

	template<typename T>
	double SmartQueue<T>::GetStandardDeviation()
	{
		return sqrt(GetVariance());
	}

	template<typename T>
	unsigned int SmartQueue<T>::GetCount()
	{
		return mQueue.size();
	}
}

