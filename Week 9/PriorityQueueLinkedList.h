#pragma once
#include <cassert>

// Class declaration
template <class T> class LinkIterator;
template <class T> class PriorityQueueLinkedList;

// Define a node
template<class T>
class LinkNode // Each Node instance holds the data of the list
{
public:
	// Give access to the private member variables
	friend class LinkIterator<T>;
	friend class PriorityQueueLinkedList<T>;
private:
	T m_data;
	LinkNode* m_next;
	LinkNode* m_previous;
};

// Define our iterator
// This is used to access, manipulate and traverse our linked list
template <class T>
class LinkIterator
{
public:
	friend class PriorityQueueLinkedList<T>; // New Addition

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
	// Decremental operator (--) -- Prefix and Postfix
	void operator--() // prefix
	{
		assert(m_node != NULL);
		m_node = m_node->m_previous;
	}
	void operator--(int) // postfix
	{
		assert(m_node != NULL);
		m_node = m_node->m_previous;
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
	bool isValid()
	{
		return (m_node != NULL);
	}
private:
	LinkNode<T>* m_node; // Points to a node in the linked list
};

template <class T>
class PriorityQueueLinkedList
{
public:
	PriorityQueueLinkedList() : m_size(0), m_root(0), m_lastNode(0) {}
	~PriorityQueueLinkedList()
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
	// ----------------------END POSITION FUNCTIONS----------------------
	// ----------------------PRIORITY QUEUE FUNCTIONS--------------------
	void insert_Before(LinkIterator<T>& it, T newData)
	{
		assert(it.m_node != NULL);

		LinkNode<T>* node = new LinkNode<T>;
		assert(node != NULL);

		node->m_data = newData;
		node->m_next = it.m_node;
		node->m_previous = it.m_node->m_previous;

		if (node->m_previous != NULL)
		{
			// Point the previous node to the new node
			node->m_previous->m_next = node;
		}
		it.m_node->m_previous = node;

		// Check to see if the iterator was pointing to the root
		if (it.m_node == m_root)
		{
			m_root = node;
		}

		m_size++;
	}
	void Insert_After(LinkIterator<T>& it, T newData)
	{
		assert(it.m_node != NULL);

		LinkNode<T>* node = new LinkNode<T>;
		assert(node != NULL);

		node->m_data = newData;
		node->m_next = it.m_node->m_next;
		node->m_previous = it.m_node;

		if (node->m_next != NULL)
		{
			node->m_next->m_previous = node;
		}

		it.m_node->m_next = node;

		if (it.m_node == m_lastNode)
		{
			m_lastNode = node;
		}

		m_size++;
	}
	// ----------------------LINKED LIST OPERATIONS----------------------
	void Push_Front(T newData) // Pushes to the front of the linked list
	{
		// Create a new node (new root node)
		LinkNode<T>* node = new LinkNode<T>;
		assert(node != NULL);
		node->m_data = newData;
		node->m_next = NULL;
		node->m_previous = NULL;

		// Linked list is populated by at least 1 item (so first node is filled)
		if (m_root != NULL)
		{
			// the new node's next pointer points to the old root (first) node
			node->m_next = m_root;
			// the first (root) node's previous pointer points to the new node
			// this positions the new node in front of the original first node
			m_root->m_previous = node;
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

		// if there is a first node (if there are nodes in the linked list)
		if (m_root != NULL)
		{
			// set the first node's previous node to NULL
			m_root->m_previous = NULL;
		}
		else
		{
			// set the last node to NULL
			m_lastNode = NULL;
		}

		// the original 1st node that is pointed by temp is going to be deleted
		delete temp;
		temp = NULL;

		// check to ensure m_size (size counter) doesn't become negative
		// reduces the number of nodes accounted for (after one is deleted)
		m_size = (m_size == 0 ? m_size : m_size - 1);
	}

	// Push creates a new Node instance that stores the new data and adds it to the pointer chain of instances
	void Push(T newData)
	{
		// Create a standalone LinkNode object
		// Creates a new node to store data
		LinkNode<T>* node = new LinkNode<T>;
		assert(node != NULL);
		node->m_data = newData; // stores the data in new node
		node->m_next = NULL;
		node->m_previous = NULL;

		// Add new LinkNode to the existing PriorityQueueLinkedList
		if (m_lastNode != NULL) // Linked list is populated. Push to the end of the list
		{
			// if there are nodes before the new node pushed to the back
			// makes the last node's next pointer point to the node
			// and makes the new node's previous point to the original last node
			// positioning the new node at the back of the list
			m_lastNode->m_next = node;
			node->m_previous = m_lastNode;
		}
		else // An empty link list
		{
			// if empty link list, the node becomes (is referenced by) both the first node and the last node
			m_root = node;
		}
		// in either case, the new node will always be the last node
		m_lastNode = node;

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
			// a temporary node pointer (prevNode) holds the 2nd to last node
			LinkNode<T>* prevNode = m_lastNode->m_previous;


			// sets the 2nd to last node next pointer to NULL (prevents dangling pointer)
			prevNode->m_next = NULL;
			// "Pop()" delete the original last node
			delete m_lastNode;
			// sets the 2nd to last node to be new last node (by making last node pointer point to it)
			m_lastNode = prevNode;
			// sets the prevNode to point away from pointing to last node (set to NULL)
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