#include "Lab6.h"
#include <limits>

namespace lab6
{
	int Sum(const std::vector<int>& v)
	{
		int result = 0;
		if (v.empty())
		{
			return result;
		}

		std::vector<int>::const_iterator iter = v.begin();
		while (iter != v.end())
		{
			result += *iter++;
		}

		return result;
	}

	int Min(const std::vector<int>& v)
	{
		int result = std::numeric_limits<int>::max();
		if (v.empty())
		{
			return result;
		}

		std::vector<int>::const_iterator iter = v.begin();
		while (iter != v.end())
		{
			if (result > *iter)
			{
				result = *iter;
			}
			iter++;
		}

		return result;
	}

	int Max(const std::vector<int>& v)
	{
		int result = std::numeric_limits<int>::lowest();
		if (v.empty())
		{
			return result;
		}

		std::vector<int>::const_iterator iter = v.begin();
		while (iter != v.end())
		{
			if (result < *iter)
			{
				result = *iter;
			}
			iter++;
		}

		return result;
	}

	float Average(const std::vector<int>& v)
	{
		if (v.empty())
		{
			return 0.0f;
		}

		return static_cast<float>(Sum(v)) / v.size();
	}

	int NumberWithMaxOccurrence(const std::vector<int>& v)
	{
		if (v.empty())
		{
			return 0;
		}

		std::vector<int> numberCounts = std::vector<int>();
		numberCounts.reserve(v.size());
		numberCounts.assign(v.size(), 1);

		unsigned int higerIndex = 0;

		std::vector<int>::const_iterator iter1 = v.begin();
		while (iter1 != v.end())
		{
			std::vector<int>::const_iterator iter2 = v.begin();
			unsigned int index = 0;
			while (iter1 != iter2)
			{
				if (*iter1 == *iter2)
				{
					numberCounts[index] += 1;
					if (numberCounts[higerIndex] < numberCounts[index])
					{
						higerIndex = index;
					}
					break;
				}

				++index;
				++iter2;
			}

			++iter1;
		}
		return v[higerIndex];
	}

	void SortDescending(std::vector<int>& v)
	{
		if (v.empty())
		{
			return;
		}

		QuickSortRecursive(v, 0, v.size() - 1);
	}

	void QuickSortRecursive(std::vector<int>& v, int left, int right)
	{
		if (left >= right)
		{
			return;
		}

		int pivot = v[right];

		int swapIndex = left;
		for (int i = left; i < right; ++i)
		{
			if (v[i] > pivot)
			{
				SwapVectorData(v, swapIndex++, i);
			}
		}

		SwapVectorData(v, swapIndex, right);

		QuickSortRecursive(v, left, swapIndex - 1);
		QuickSortRecursive(v, swapIndex + 1, right);
	}

	void SwapVectorData(std::vector<int>& v, unsigned int index1, unsigned int index2)
	{
		int swapValue = v[index1];
		v[index1] = v[index2];
		v[index2] = swapValue;
	}
}