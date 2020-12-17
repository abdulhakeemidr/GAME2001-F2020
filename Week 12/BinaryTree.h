#pragma once
#include <iostream>
using namespace std;

// Template declaration
template<typename T>
class BinaryTree;

template<typename T>
class Node
{
	friend class BinaryTree<T>;

public:
	// Constructor
	Node(T key) : m_key(key), m_left(NULL), m_right(NULL) { }

	// Destructor
	~Node()
	{
		if (m_left != NULL)
		{
			delete m_left;
			m_left = NULL;
		}

		if (m_right != NULL)
		{
			delete m_right;
			m_right = NULL;
		}
	}

	// Get Key
	T GetKey()
	{
		return m_key;
	}
private:
	T m_key;
	Node* m_left, * m_right;
};

template<typename T>
class BinaryTree
{
public:
	// Constructor
	BinaryTree() : m_root(NULL) {}
	// Destructor
	~BinaryTree()
	{
		if (m_root != NULL)
		{
			delete m_root;
			m_root = NULL;
		}
	}
	/* --------------- PUSH ---------------------- */
	// Check if the root exists
	// Traverse left or right of the nodes based on the key
	// Attach the new node
	bool push(T key)
	{
		// Create the new node to be added to the tree
		Node<T>* newNode = new Node<T>(key);

		// Check if the root does not exist
		if (m_root == NULL)
		{
			// Root does not exists. newNode will become the root
			m_root = newNode;
		}
		else
		{
			// Root exists. Traverse down the tree
			Node<T>* parentNode = NULL;
			Node<T>* currentNode = m_root;

			// Traversal
			while (1)
			{
				parentNode = currentNode;

				// Manage duplicates
				// IN THIS IMPLEMENTATION...no duplicates allowed.
				if (key == currentNode->GetKey())
				{
					// Duplicate found! Delete newNode
					delete newNode;
					return false;
				}

				// Do I traverse left or right?
				if (key < currentNode->GetKey())
				{
					// Go left
					currentNode = currentNode->m_left;

					if (currentNode == NULL)
					{
						// This is where the newNode must go
						parentNode->m_left = newNode;
						return true;
					}
				}
				else
				{
					// Go right
					currentNode = currentNode->m_right;

					if (currentNode == NULL)
					{
						// This is where the newNode must go
						parentNode->m_right = newNode;
						return true;
					}
				}
			}
		}

		return true;
	}
	/* -------------- SEARCH ---------------- */
	// Check if the root exists
	// Traverse until key is found or not found
	bool search(T key)
	{
		if (m_root == NULL)
		{
			return false;
		}

		// Node pointer used to traverse through the tree
		Node<T>* currentNode = m_root;

		while (currentNode->GetKey() != key)
		{
			// Left vs right
			if (key < currentNode->GetKey())
			{
				// Left
				currentNode = currentNode->m_left;
			}
			else
			{
				// Right
				currentNode = currentNode->m_right;
			}

			// Did not find the key in the tree
			if (currentNode == NULL)
			{
				return false;
			}
		}

		// Search key exists in the tree
		return true;
	}
	/* -------------- REMOVE ------------- */
	// Check if the root exists
	// 1. No children
	// 2. One child
	// 3. Two children
	void remove(T key)
	{
		// Check if the root does not exist
		if (m_root == NULL)
		{
			return;
		}

		Node<T>* parent = m_root;
		Node<T>* node = m_root;
		bool isLeftNode = false;

		// Traverse and find the key to be removed
		while (node->GetKey() != key)
		{
			parent = node;

			// Left vs right
			if (key < node->GetKey())
			{
				// Left
				node = node->m_left;
				isLeftNode = true;
			}
			else
			{
				node = node->m_right;
				isLeftNode = false;
			}

			// Node not found. Get out of here
			if (node == NULL)
			{
				return;
			}
		}
		// ---------------------- Removal Work ------------------------
		// 1. No children
		if (node->m_left == NULL && node->m_right == NULL)
		{
			// No children
			// Is this the root node?
			if (node = m_root)
			{
				// This is the root node!
				m_root = NULL;
			}
			else if (isLeftNode)
			{
				// This is the left side of the parent node
				parent->m_left = NULL;
			}
			else
			{
				// This is the right side of the parent node
				parent->m_right = NULL;
			}
		}
		else if (node->m_left == NULL) // 2a. One child (right exists)
		{
			if (node == m_root)
			{
				// Right node i now the new root node
				m_root = node->m_right;
			}
			else if (isLeftNode)
			{
				// Child is to the left of the parent
				parent->m_left = node->m_right;
			}
			else
			{
				// Child is to the right of the parent
				parent->m_right = node->m_right;
			}
		}
		else if (node->m_right == NULL) // 2a. One child (left exists)
		{
			if (node == m_root)
			{
				// Right node i now the new root node
				m_root = node->m_left;
			}
			else if (isLeftNode)
			{
				// Child is to the left of the parent
				parent->m_left = node->m_left;
			}
			else
			{
				// Child is to the right of the parent
				parent->m_right = node->m_left;
			}
		}
		else // Two Children
		{
			Node<T>* tempNode = node->m_right;
			Node<T>* successor = node;
			Node<T>* successorParent = node;

			// Traversal down the right of the node to be deleted while also hanging a left
			while (tempNode != NULL)
			{
				successorParent = successor;
				successor = tempNode;
				tempNode = tempNode->m_left;
			}

			if (successor != node->m_right)
			{
				successorParent->m_left = successor->m_right;
				successor->m_right = node->m_right;
			}

			// Assign the successor to the node to be removed
			// Check the root
			if (node == m_root)
			{
				m_root = successor;
			}
			else if (isLeftNode)
			{
				node = parent->m_left;
				parent->m_left = successor;
			}
			else
			{
				node = parent->m_right;
				parent->m_right = successor;
			}

			successor->m_left = node->m_left;
		}

		node->m_left = NULL;
		node->m_right = NULL;
		delete node;
	}
	// Display (Pre, Post, In) (interface)
	void DisplayPreOrder()
	{
		DisplayPreOrder(m_root);
	}
	void DisplayPostOrder()
	{
		DisplayPostOrder(m_root);
	}
	void DisplayInOrder()
	{
		DisplayInOrder(m_root);
	}
private:
	// Display (implementation)
	// PreOrder - NODE, LEFT CHILD, RIGHT CHILD
	void DisplayPreOrder(Node<T>* node)
	{
		if (node != NULL)
		{
			cout << node->GetKey() << " ";

			DisplayPreOrder(node->m_left);
			DisplayPreOrder(node->m_right);
		}
	}
	// PostOrder - LEFT CHILD, RIGHT CHILD, NODE
	void DisplayPostOrder(Node<T>* node)
	{
		if (node != NULL)
		{
			DisplayPostOrder(node->m_left);
			DisplayPostOrder(node->m_right);

			cout << node->GetKey() << " ";
		}
	}
	// InOrder - LEFT CHILD, NODE, RIGHT CHILD
	void DisplayInOrder(Node<T>* node)
	{
		if (node != NULL)
		{
			DisplayInOrder(node->m_left);

			cout << node->GetKey() << " ";

			DisplayInOrder(node->m_right);
		}
	}
private:
	Node<T>* m_root;
};