#pragma once

#include <memory>
#include <vector>

namespace assignment4
{
	template<typename T>
	class TreeNode;

	template<typename T>
	class BinarySearchTree final
	{
	public:
		void Insert(std::unique_ptr<T> data);
		bool Search(const T& data);
		bool Delete(const T& data);
		const std::weak_ptr<TreeNode<T>> GetRootNode() const;

		static std::vector<T> TraverseInOrder(const std::shared_ptr<TreeNode<T>> startNode);
	private:
		std::shared_ptr<TreeNode<T>> findInsertParentRecursive(const std::shared_ptr<TreeNode<T>> node, const T* data);
		std::shared_ptr<TreeNode<T>> findNodeRecursive(const std::shared_ptr<TreeNode<T>> node, const T& data);
		void replaceNode(std::shared_ptr<TreeNode<T>> deleteNode, std::shared_ptr<TreeNode<T>> replaceNode);
		std::shared_ptr<TreeNode<T>> findSuccessor(const std::shared_ptr<TreeNode<T>> node);
		static void insertTreeDataInOrderRecursive(std::vector<T>& vector, const std::shared_ptr<TreeNode<T>> node);

		std::shared_ptr<TreeNode<T>> mRootNode;
	};

	template<typename T>
	void BinarySearchTree<T>::Insert(std::unique_ptr<T> data)
	{
		if (mRootNode)
		{
			std::shared_ptr<TreeNode<T>> parent = findInsertParentRecursive(mRootNode, data.get());
			if (*(parent->Data) < *data)
			{
				parent->Right = std::make_shared<TreeNode<T>>(parent, std::move(data));
			}
			else
			{
				parent->Left = std::make_shared<TreeNode<T>>(parent, std::move(data));
			}
		}
		else
		{
			mRootNode = std::make_shared<TreeNode<T>>(std::move(data));
		}
	}

	template<typename T>
	const std::weak_ptr<TreeNode<T>> BinarySearchTree<T>::GetRootNode() const
	{
		return mRootNode;
	}

	template<typename T>
	bool BinarySearchTree<T>::Search(const T& data)
	{
		std::shared_ptr<TreeNode<T>> node = findNodeRecursive(mRootNode, data);
		return node != nullptr;
	}

	template<typename T>
	bool BinarySearchTree<T>::Delete(const T& data)
	{
		std::shared_ptr<TreeNode<T>> node = findNodeRecursive(mRootNode, data);
		if (node)
		{
			if (node->Left == nullptr)
			{
				replaceNode(node, node->Right);
			}
			else if (node->Right == nullptr)
			{
				replaceNode(node, node->Left);
			}
			else
			{
				std::shared_ptr<TreeNode<T>> successorNode = findSuccessor(node);

				if (successorNode->Parent.lock() != node)
				{
					replaceNode(successorNode, successorNode->Right);
					successorNode->Right = node->Right;
					successorNode->Right->Parent = successorNode;
				}
				replaceNode(node, successorNode);
				successorNode->Left = node->Left;
				successorNode->Left->Parent = successorNode;
			}
			return true;
		}
		return false;
	}

	template<typename T>
	std::vector<T> BinarySearchTree<T>::TraverseInOrder(const std::shared_ptr<TreeNode<T>> startNode)
	{
		std::vector<T> v;
		if (startNode != nullptr)
		{
			insertTreeDataInOrderRecursive(v, startNode);
		}
		return v;
	}

	template<typename T>
	std::shared_ptr<TreeNode<T>> BinarySearchTree<T>::findInsertParentRecursive(const std::shared_ptr<TreeNode<T>> node, const T* data)
	{
		if (node)
		{
			if (*(node->Data) < *data)
			{
				if (node->Right == nullptr)
				{
					return node;
				}
				else
				{
					return findInsertParentRecursive(node->Right, data);
				}
			}
			else
			{
				if (node->Left == nullptr)
				{
					return node;
				}
				else
				{
					return findInsertParentRecursive(node->Left, data);
				}
			}
		}

		return node;
	}

	template<typename T>
	std::shared_ptr<TreeNode<T>> BinarySearchTree<T>::findNodeRecursive(const std::shared_ptr<TreeNode<T>> node, const T& data)
	{
		if (node)
		{
			if (*(node->Data) == data)
			{
				return node;
			}
			else if (*(node->Data) < data)
			{
				return findNodeRecursive(node->Right, data);
			}
			else
			{
				return findNodeRecursive(node->Left, data);
			}
		}

		return nullptr;
	}

	template<typename T>
	void BinarySearchTree<T>::replaceNode(std::shared_ptr<TreeNode<T>> deleteNode, std::shared_ptr<TreeNode<T>> replaceNode)
	{
		if (deleteNode->Parent.expired())
		{
			mRootNode = replaceNode;
			return;
		}

		std::shared_ptr<TreeNode<T>> parentNode = deleteNode->Parent.lock();
		if (parentNode->Left == deleteNode)
		{
			parentNode->Left = replaceNode;
		}
		else if (parentNode->Right == deleteNode)
		{
			parentNode->Right = replaceNode;
		}

		if (replaceNode != nullptr)
		{
			replaceNode->Parent = parentNode;
		}
	}

	template<typename T>
	std::shared_ptr<TreeNode<T>> BinarySearchTree<T>::findSuccessor(const std::shared_ptr<TreeNode<T>> node)
	{
		std::shared_ptr<TreeNode<T>> successorNode = nullptr;
		if (node->Right != nullptr)
		{
			successorNode = node->Right;
			while (successorNode->Left != nullptr)
			{
				successorNode = successorNode->Left;
			}
		}

		return successorNode;
	}

	template<typename T>
	void BinarySearchTree<T>::insertTreeDataInOrderRecursive(std::vector<T>& vector, const std::shared_ptr<TreeNode<T>> node)
	{
		if (node->Left != nullptr)
		{
			insertTreeDataInOrderRecursive(vector, node->Left);
		}
		vector.push_back(*(node->Data.get()));
		if (node->Right != nullptr)
		{
			insertTreeDataInOrderRecursive(vector, node->Right);
		}
	}
}
