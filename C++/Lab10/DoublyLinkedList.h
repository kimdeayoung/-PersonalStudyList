#pragma once

#include <memory>

namespace lab10
{
	template<typename T>
	class Node;

	template<typename T>
	class DoublyLinkedList
	{
	public:
		DoublyLinkedList();
		void Insert(std::unique_ptr<T> data);
		void Insert(std::unique_ptr<T> data, unsigned int index);
		bool Delete(const T& data);
		bool Search(const T& data) const;

		std::shared_ptr<Node<T>> operator[](unsigned int index) const;
		unsigned int GetLength() const;

	private:
		std::shared_ptr<Node<T>> mRoot;
		std::shared_ptr<Node<T>> mTail;
		unsigned int mLength;
	};

	template<typename T>
	DoublyLinkedList<T>::DoublyLinkedList()
		: mLength(0)
	{
	}

	template<typename T>
	void DoublyLinkedList<T>::Insert(std::unique_ptr<T> data)
	{
		Insert(std::move(data), mLength);
	}

	template<typename T>
	void DoublyLinkedList<T>::Insert(std::unique_ptr<T> data, unsigned int index)
	{
		if (mRoot == nullptr)
		{
			mRoot = std::make_shared<Node<T>>(std::move(data));
			mTail = mRoot;
		}
		else
		{
			if (index < mLength)
			{
				if (index == 0)
				{
					std::shared_ptr<Node<T>> newNode = std::make_shared<Node<T>>(std::move(data));
					newNode->Next = mRoot;
					mRoot->Previous = newNode;
					mRoot = newNode;
				}
				else
				{
					unsigned int count = 0;
					std::shared_ptr<Node<T>> node = mRoot;
					while (++count < index)
					{
						node = node->Next;
					}

					std::shared_ptr<Node<T>> newNode = std::make_shared<Node<T>>(std::move(data), node);
					newNode->Next = node->Next;
					node->Next->Previous = newNode;
					node->Next = newNode;
				}
			}
			else
			{
				std::shared_ptr<Node<T>> newNode = std::make_shared<Node<T>>(std::move(data), mTail);
				mTail.get()->Next = newNode;
				mTail = newNode;
			}
		}
		++mLength;
	}

	template<typename T>
	bool DoublyLinkedList<T>::Delete(const T& data)
	{
		unsigned int count = 0;
		std::shared_ptr<Node<T>> node = mRoot;
		while (count++ < mLength)
		{
			if (*(node->Data) == data)
			{
				if (node->Previous.expired())
				{
					mRoot = node->Next;
					if (mTail == node)
					{
						mTail = nullptr;
					}
				}
				else
				{
					node->Previous.lock()->Next = node->Next;

					if (mTail == node)
					{
						mTail = node->Previous.lock();
					}
				}
				
				if (node->Next != nullptr)
				{
					node->Next->Previous = node->Previous.lock();
				}
				
				--mLength;
				return true;
			}
			node = node->Next;
		}

		return false;
	}

	template<typename T>
	bool DoublyLinkedList<T>::Search(const T& data) const
	{
		unsigned int count = 0;
		std::shared_ptr<Node<T>> node = mRoot;
		while (count++ < mLength)
		{
			if (*(node->Data.get()) == data)
			{
				return true;
			}
			node = node->Next;
		}
		return false;
	}

	template<typename T>
	std::shared_ptr<Node<T>> DoublyLinkedList<T>::operator[](unsigned int index) const
	{
		if (index >= mLength)
		{
			return nullptr;
		}

		unsigned int count = 0;
		std::shared_ptr<Node<T>> node = mRoot;
		while (count++ < index)
		{
			node = node->Next;
		}
		return node;
	}

	template<typename T>
	unsigned int DoublyLinkedList<T>::GetLength() const
	{
		return mLength;
	}
}