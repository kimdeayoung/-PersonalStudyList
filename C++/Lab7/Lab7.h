#pragma once

#include <iostream>
#include <vector>
#include <map>

namespace lab7
{
	template <typename K, class V>
	std::map<K, V> ConvertVectorsToMap(const std::vector<K>& keys, const std::vector<V>& values)
	{
		std::map<K, V> m;
		typename std::vector<K>::const_iterator keyIter = keys.begin();
		typename std::vector<V>::const_iterator valueIter = values.begin();

		unsigned int loopCount = keys.size() < values.size() ? keys.size() : values.size();
		for (unsigned int i = 0; i < loopCount; ++i)
		{
			m.insert(std::pair<K, V>(*keyIter++, *valueIter++));
		}

		return m;
	}

	template <typename K, class V>
	std::vector<K> GetKeys(const std::map<K, V>& m)
	{
		std::vector<K> v;
		typename std::map<K, V>::const_iterator iter = m.begin();

		while (iter != m.end())
		{
			v.push_back(iter->first);
			++iter;
		}

		return v;
	}

	template <typename K, class V>
	std::vector<V> GetValues(const std::map<K, V>& m)
	{
		std::vector<V> v;
		typename std::map<K, V>::const_iterator iter = m.begin();

		while (iter != m.end())
		{
			v.push_back(iter->second);
			++iter;
		}
		return v;
	}

	template <typename T>
	std::vector<T> Reverse(const std::vector<T>& v)
	{
		std::vector<T> rv;
		typename std::vector<T>::const_reverse_iterator reverseIter = v.rbegin();

		while (reverseIter != v.rend())
		{
			rv.push_back(*reverseIter++);
		}

		return rv;
	}

	template <typename T>
	std::vector<T> operator+(const std::vector<T>& v1, const std::vector<T>& v2)
	{
		std::vector<T> combined;

		for (typename std::vector<T>::const_iterator iter = v1.begin(); iter != v1.end(); ++iter)
		{
			if (std::find(combined.begin(), combined.end(), *iter) == combined.end())
			{
				combined.push_back(*iter);
			}
		}
		for (typename std::vector<T>::const_iterator iter = v2.begin(); iter != v2.end(); ++iter)
		{
			if (std::find(combined.begin(), combined.end(), *iter) == combined.end())
			{
				combined.push_back(*iter);
			}
		}

		return combined;
	}

	template <typename K, class V>
	std::map<K, V> operator+(const std::map<K, V>& m1, const std::map<K, V>& m2)
	{
		std::map<K, V> combined;
		
		for (typename std::map<K, V>::const_iterator iter = m1.begin(); iter != m1.end(); ++iter)
		{
			combined.insert(std::pair<K, V>(iter->first, iter->second));
		}
		for (typename std::map<K, V>::const_iterator iter = m2.begin(); iter != m2.end(); ++iter)
		{
			combined.insert(std::pair<K, V>(iter->first, iter->second));
		}
		return combined;
	}

	template<typename T>
	std::ostream& operator<<(std::ostream& os, const std::vector<T>& v)
	{
		if (v.empty())
		{
			return os;
		}

		typename std::vector<T>::const_iterator iter = v.begin();
		os << *iter++;
		while (iter != v.end())
		{
			os << ", " << *iter++;
		}
		return os;
	}

	template <typename K, class V>
	std::ostream& operator<<(std::ostream& os, const std::map<K, V>& m)
	{
		if (m.empty())
		{
			return os;
		}

		typename std::map<K, V>::const_iterator iter = m.begin();
		while (iter != m.end())
		{
			os << "{ " << iter->first << ", " << iter->second << " }" << std::endl;
			++iter;
		}
		return os;
	}
}