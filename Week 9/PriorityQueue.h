#pragma once

#include "PriorityQueueLinkedList.h"

template<class T, class CMP>
class PriorityQueue
{
public:
	PriorityQueue(int size)
	{
		assert(size > 0);
		m_size = size;
	}
	~PriorityQueue() {}
	// Priority queue functions
	void push(T val)
	{
		assert(m_elements.GetSize() < m_size);

		// if there are no T objects stored in the linked list
		if (m_elements.GetSize() == 0)
		{
			// if the list is empty
			// it creates a new node and pushes the value into it
			m_elements.Push(val);
		}
		else
		{
			LinkIterator<T> it;
			it = m_elements.Begin();

			CMP cmp;	// Placeholder for the comparisons we will be making

			// while the iterator points to a non-empty linked node
			while (it.isValid())	// Move iterator to the correct spot (or null)
			{
				// uses a comparison class to see if new T val is placed 
				// before or after the iterators current linked node
				if (cmp(val, *it))
				{
					// if the new T val is placed before, it breaks out of the while loop
					break;
				}

				// new T val cant be placed before, so the iterator goes to the next linked node
				// and that is compared to T val
				it++;
			}

			if (it.isValid())
			{
				// Inserts the new T object into a link node before the iterators link node
				// This is because val object has been compared with
				// the object stored in the iterators current link node
				// And it determines that the priority number is less than the iterator objects priority number
				// or the ID number is less than the iterator objects ID number
				m_elements.insert_Before(it, val);
 			}
			else
			{
				// If both the priority and ID number are bigger than all 
				// the objects numbers stored in the linked list,
				// Then the new T object is stored as the lastNode
				m_elements.Push(val);
			}
		}
	}
	void pop()
	{
		m_elements.Pop_Front();
	}
	T& front()
	{
		LinkIterator<T> it;
		it = m_elements.Begin();

		return *it;
	}
	T& back()
	{
		LinkIterator<T> it;
		it = m_elements.Last();

		return *it;
	}
	// Helper functions
	int GetSize()
	{
		return m_elements.GetSize();
	}
	int GetMaxSize()
	{
		return m_size;
	}
	bool isEmpty()
	{
		return (m_elements.GetSize() == 0);
	}
	void Resize(int size)
	{
		assert(size > 0);
		m_size = size;
	}
private:
	PriorityQueueLinkedList<T> m_elements;
	int m_size;
};