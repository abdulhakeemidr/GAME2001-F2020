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

		if (m_elements.GetSize() == 0)
		{
			m_elements.Push(val);
		}
		else
		{
			LinkIterator<T> it;
			it = m_elements.Begin();

			CMP cmp;	// Placeholder for the comparisons we will be making

			while (it.isValid())	// Move iterator to the correct spot (or null)
			{
				if (cmp(val, *it))
				{
					break;
				}

				it++;
			}

			if (it.isValid())
			{
				m_elements.insert_Before(it, val);
			}
			else
			{
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