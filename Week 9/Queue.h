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
	int GetSize()
	{
		return m_elements.GetSize();
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
	DoublyLinkedList<T> m_elements;
	int m_size;
};