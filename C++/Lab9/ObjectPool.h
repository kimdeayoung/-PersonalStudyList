#pragma once
#include <queue>

namespace lab9
{
	template <typename T>
	class ObjectPool final
	{
	public:
		ObjectPool(size_t maxPoolSize);
		~ObjectPool();

		ObjectPool(const ObjectPool&) = delete;
		ObjectPool& operator=(const ObjectPool&) = delete;

		T* Get();
		void Return(T* object);
		size_t GetFreeObjectCount() const;
		size_t GetMaxFreeObjectCount() const;
	private:
		size_t mMaxPoolSize;
		std::queue<T*> mObjectQueue;
	};

	template <typename T>
	ObjectPool<T>::ObjectPool(size_t maxPoolSize)
		: mMaxPoolSize(maxPoolSize)
	{
	}

	template <typename T>
	ObjectPool<T>::~ObjectPool()
	{
		while (mObjectQueue.empty() == false)
		{
			T* object = mObjectQueue.front();
			mObjectQueue.pop();
			delete object;
		}
	}

	template <typename T>
	T* ObjectPool<T>::Get()
	{
		T* object = nullptr;
		if (mObjectQueue.empty())
		{
			object = new T();
		}
		else
		{
			object = mObjectQueue.front();
			mObjectQueue.pop();
		}
		
		return object;
	}

	template <typename T>
	void ObjectPool<T>::Return(T* object)
	{
		if (mObjectQueue.size() < mMaxPoolSize)
		{
			mObjectQueue.push(object);
		}
		else
		{
			delete object;
		}
	}

	template <typename T>
	size_t ObjectPool<T>::GetFreeObjectCount() const
	{
		return mObjectQueue.size();
	}

	template <typename T>
	size_t ObjectPool<T>::GetMaxFreeObjectCount() const
	{
		return mMaxPoolSize;
	}
}
