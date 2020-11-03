#pragma once
#pragma once
#include <cassert>

// Class declaration
template <class T> class LinkIterator;
template <class T> class DoubleEndedLinkedList;

// Define a node
template<class T>
class LinkNode // Each Node instance holds the data of the list
{
public:
	// Give access to the private member variables
	friend class LinkIterator<T>;
	friend class DoubleEndedLinkedList<T>;
private:
	T m_data;
	LinkNode* m_next;
};

// Define our iterator
// This is used to access, manipulate and traverse our linked list
template <class T>
class LinkIterator
{
public:
	LinkIterator()
	{
		// sets the iterators node pointer to NULL
		m_node = NULL;
	}
	~LinkIterator() {}
	// OVERLOADED OPERATORS

	// Assignment operator (=)
	void operator=(LinkNode<T>* node)
	{
		// Assignment operator sets the instances node pointer to the address you assign the instance to
		m_node = node;
	}
	// Dereferencing operator (*)
	T& operator*()
	{
		// dereference operator returns the dereferenced instance's node pointer
		assert(m_node != NULL);
		return m_node->m_data;
	}
	// Incremental operator (++) -- Prefix and Postfix
	void operator++() // no parameters -> prefix
	{
		assert(m_node != NULL);
		m_node = m_node->m_next;
	}
	void operator++(int) // a parameter -> postfix
	{
		// assigns the instance's node pointer next pointer to be pointed to by the instance's node pointer
		assert(m_node != NULL);
		m_node = m_node->m_next;
	}
	// Comparison operator (!= & ==)
	bool operator!=(LinkNode<T>* node)
	{
		// != operator determines if the iterator instance's node pointer is not the same as the other pointer
		return (m_node != node);
	}
	bool operator==(LinkNode<T>* node)
	{
		return (m_node == node);
	}
private:
	LinkNode<T>* m_node; // Points to a node in the linked list
};

// Double Ended Linked Lists allow you to push and pop nodes from the front and the back of the list
template <class T>
class DoubleEndedLinkedList
{
public:
	DoubleEndedLinkedList() : m_size(0), m_root(0), m_lastNode(0) {}
	~DoubleEndedLinkedList()
	{
		while (m_root)
		{
			Pop();
		}
	}
	// POSITIONING FUNCTIONS
	// Begin() returns the address of the first node on the linked list
	LinkNode<T>* Begin()
	{
		assert(m_root != NULL);
		return m_root;
	}
	// End() returns the address of the last node on the linked list
	LinkNode<T>* End()
	{
		return NULL;
	}
	LinkNode<T>* Last()
	{
		return m_lastNode;
	}
	// END POSITION FUNCTIONS
	// LINKED LIST OPERATIONS
	void Push_Front(T newData) // Pushes to the front of the linked list
	{
		// Create a new node (new root node)
		LinkNode<T>* node = new LinkNode<T>;
		assert(node != NULL);
		node->m_data = newData;
		node->m_next = NULL;

		// Linked list is populated by at least 1 item (so first node is filled)
		if (m_root != NULL)
		{
			// the new node's next pointer points to the old root (first) node
			node->m_next = m_root;
			// the new node become the first node (root pointer points to the new node)
			m_root = node;
		}
		else // An empty link list
		{
			m_root = node;
			m_lastNode = node;
		}

		m_size++;
	}

	void Pop_Front()
	{
		assert(m_root != NULL);
		// We are eventually deleting the contents of temp
		// the temp node pointer points to the original 1st node
		LinkNode<T>* temp = m_root;

		// the 2nd to 1st node becomes the new 1st node (root pointer points to the 2nd node)
		m_root = m_root->m_next;
		// the original 1st node memory gets deleted
		delete temp;
		temp = NULL;

		// BOOK ERROR!
		// Check to see if the list is empty
		// if the original 1st node was the only node, then the Linked list is empty
		if (m_root == NULL)
		{
			m_lastNode = NULL;
		}
		// check to ensure m_size (size counter) doesn't become negative
		// reduces the number of nodes accounted for (after one is deleted)
		m_size = (m_size == 0 ? m_size : m_size - 1);
	}

	void Push(T newData) // Push creates a new Node instance to add to the pointer chain of instances
	{
		// Create a standalone LinkNode object
		// Creates a new node to store data
		LinkNode<T>* node = new LinkNode<T>;
		assert(node != NULL);
		node->m_data = newData; // stores the data in that node
		node->m_next = NULL;

		// Add new LinkNode to the existing DoubleEndedLinkedList
		if (m_lastNode != NULL) // Linked list is populated. Push to the end of the list
		{
			// if there are nodes before the new pushed node,
			// retargets the last node pointer to the new node that is pushed
			// so the new node is the last node
			// makes the former last node's next pointer point to the new node
			m_lastNode->m_next = node;
			m_lastNode = node;
		}
		else // An empty link list
		{
			// if empty link list, the node becomes (is referenced by) both the first node and the last node
			m_root = node;
			m_lastNode = node;
		}
		// increases the size of the node list (linked list) after pushing a new node
		m_size++;
	}

	void Pop()
	{
		assert(m_root != NULL);

		// if the (root) first node is the last node (no other node comes after)
		if (m_root->m_next == NULL)
		{
			delete m_root;
			// sets the first (root) and last node pointer to NULL
			m_root = NULL;
			m_lastNode = NULL;
		}
		else // Linked list has more items (last node being popped isn't the first (root) node)
		{
			// a temporary node pointer (prevNode) holds the address of the first (root) node
			LinkNode<T>* prevNode = m_root;

			// Traverse the linked list until we reach the end
			// the temporary node pointer (prevNode) acts as a linked list iterator to get to the last node
			// this temporary iterator is used in the while loop to find the 2nd to last node
			while (prevNode->m_next != NULL && prevNode->m_next != m_lastNode)
			{
				prevNode = prevNode->m_next;
			}

			// The previous while loop simply positions the pointer to the 2nd last node of the list
			// "Pop()" delete the last node
			delete m_lastNode;
			// sets the 2nd to last node next pointer to NULL (prevents dangling pointer)
			prevNode->m_next = NULL;
			// sets the 2nd to last node to be new last node (by making last node pointer point to it)
			m_lastNode = prevNode;

			prevNode = NULL;
		}
		// Prevent negative sizes
		m_size = (m_size == 0 ? m_size : m_size - 1);
	}

	int GetSize()
	{
		return m_size;
	}
private:
	int m_size; // Holds the size of the linked list
	LinkNode<T>* m_root; // Points to the root (first node) of the linked list
	LinkNode<T>* m_lastNode; // Points to the last node of the linked list
};