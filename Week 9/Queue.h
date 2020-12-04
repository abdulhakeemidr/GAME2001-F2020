#pragma once
#include "DoublyLinkedList.h"

template<class T>
class Queue
{
public:
	Queue(int size)
	{
		assert(size > 0);
		m_size = size;
	}
	~Queue() {}
	// -------------QUEUE FUNCTIONS -----------
	void push(T val)
	{
		if (m_elements.GetSize() < m_size)
		{
			m_elements.Push(val);
		}
	}
	void pop()
	{
		// Pops (ignores) the first node to enter the list
		// first node of the list is the bottom node of the list
		m_elements.Pop_Front();
	}
	T& front()
	{
		// Returns the value of the first node to enter the list 
		LinkIterator<T> it;
		it = m_elements.Begin();

		return *it;
	}
	T& back()
	{
		// Returns the value of the last node to enter the list 
		LinkIterator<T> it;
		it = m_elements.Last();

		return *it;
	}
	int GetSize()
	{
		// Gets the size of the list
		return m_elements.GetSize();
	}
	bool isEmpty()
	{
		// Determines if the list is empty
		return (m_elements.GetSize() == 0);
	}
	void Resize(int size)
	{
		assert(size > 0);
		m_size = size;
	}
private:
	DoublyLinkedList<T> m_elements;
	int m_size;
};