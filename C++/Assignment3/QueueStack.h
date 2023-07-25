#pragma once

#include <limits>
#include <queue>
#include <stack>

namespace assignment3
{
	template <typename T>
	class QueueStack
	{
	public:
		QueueStack(unsigned int maxStackSize);
		~QueueStack();

		void Enqueue(T value);
		T Peek();
		T Dequeue();
		T GetMax();
		T GetMin();
		double GetAverage();
		T GetSum();
		unsigned int GetCount();
		unsigned int GetStackCount();
	private:
		unsigned int mMaxStackSize;

		std::queue<std::stack<T>> mQueue;
		unsigned int mQueueDataCount;

		T mAccumulateValue;
		double mAverage;
	};

	template<typename T>
	QueueStack<T>::QueueStack(unsigned int maxStackSize)
		: mMaxStackSize(maxStackSize), mQueueDataCount(0), mAccumulateValue(0), mAverage(0)
	{
	}

	template<typename T>
	QueueStack<T>::~QueueStack()
	{
	}

	template<typename T>
	void QueueStack<T>::Enqueue(T value)
	{
		if (mMaxStackSize == 0)
		{
			return;
		}

		if (mQueue.empty())
		{
			mQueue.push(std::stack<T>());
		}
		else if (mQueue.back().size() >= mMaxStackSize)
		{
			mQueue.push(std::stack<T>());
		}
		mQueue.back().push(value);
		
		mAccumulateValue += value;
		++mQueueDataCount;
		mAverage = static_cast<double>(mAccumulateValue) / GetCount();
	}

	template<typename T>
	T QueueStack<T>::Peek()
	{
		return mQueue.front().top();
	}

	template<typename T>
	T QueueStack<T>::Dequeue()
	{
		T value = mQueue.front().top();
		mQueue.front().pop();
		
		if (mQueue.front().empty())
		{
			mQueue.pop();
		}

		mAccumulateValue -= value;
		--mQueueDataCount;
		mAverage = static_cast<double>(mAccumulateValue) / GetCount();

		return value;
	}

	template<typename T>
	T QueueStack<T>::GetMax()
	{
		if (mQueue.empty())
		{
			return std::numeric_limits<T>::lowest();
		}

		T maxValue = std::numeric_limits<T>::lowest();
		std::queue<std::stack<T>> copyedQueue;
		while (mQueue.empty() == false)
		{
			copyedQueue.push(std::stack<T>());
			std::stack<T> stack = mQueue.front();
			mQueue.pop();
			while (stack.empty() == false)
			{
				maxValue = maxValue < stack.top() ? stack.top() : maxValue;
				copyedQueue.back().push(stack.top());
				stack.pop();
			}
		}

		while (copyedQueue.empty() == false)
		{
			mQueue.push(std::stack<T>());
			std::stack<T> stack = copyedQueue.front();
			copyedQueue.pop();
			while (stack.empty() == false)
			{
				mQueue.back().push(stack.top());
				stack.pop();
			}
		}

		return maxValue;
	}

	template<typename T>
	T QueueStack<T>::GetMin()
	{
		if (mQueue.empty())
		{
			return std::numeric_limits<T>::max();
		}

		T minValue = std::numeric_limits<T>::max();
		std::queue<std::stack<T>> copyedQueue;
		while (mQueue.empty() == false)
		{
			copyedQueue.push(std::stack<T>());
			std::stack<T> stack = mQueue.front();
			mQueue.pop();
			while (stack.empty() == false)
			{
				minValue = minValue > stack.top() ? stack.top() : minValue;
				copyedQueue.back().push(stack.top());
				stack.pop();
			}
		}

		while (copyedQueue.empty() == false)
		{
			mQueue.push(std::stack<T>());
			std::stack<T> stack = copyedQueue.front();
			copyedQueue.pop();
			while (stack.empty() == false)
			{
				mQueue.back().push(stack.top());
				stack.pop();
			}
		}

		return minValue;
	}

	template<typename T>
	double QueueStack<T>::GetAverage()
	{
		return mAverage;
	}

	template<typename T>
	T QueueStack<T>::GetSum()
	{
		return mAccumulateValue;
	}

	template<typename T>
	unsigned int QueueStack<T>::GetCount()
	{
		return mQueueDataCount;
	}

	template<typename T>
	unsigned int QueueStack<T>::GetStackCount()
	{
		return mQueue.size();
	}
}

