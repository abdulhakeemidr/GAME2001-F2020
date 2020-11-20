#pragma once
#include "DoublyLinkedList.h"

template<class T>
class Deque
{
public:
	Deque(int size)
	{
		assert(size > 0);
		m_size = size;
	}
	~Deque() {}
	// -------------DEQUE FUNCTIONS -----------
	void push_front(T val)
	{
		if (m_elements.GetSize() < m_size)
		{
			m_elements.Push_Front(val);
		}
	}
	void pop_front()
	{
		m_elements.Pop();
	}
	void push_back(T val)
	{
		if (m_elements.GetSize() < m_size)
		{
			m_elements.Push(val);
		}
	}
	void pop_back()
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