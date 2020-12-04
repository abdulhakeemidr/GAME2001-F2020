#pragma once
#include <cassert>
#include "UnorderedArray.h"

// This takes the functionality of the UnorderedArray (via an instance of UnorderedArray)
// And uses it to build functionality of a Stack Array class
template<class T>
class Stack
{
public:
	// Constructor
	Stack(int size, int growBy = 1)
	{
		assert(size > 0 && growBy >= 0); // Input validation
		m_container = new UnorderedArray<T>(size, growBy); // Initialize UnorderedArray
		assert(m_container != NULL);
	}
	// Destructor
	~Stack()
	{
		if (m_container != NULL)
		{
			delete m_container;
			m_container = NULL;
		}
	}
	//-----------------STACK FUNCTIONS--------------------//
	void push(T val)
	{
		assert(m_container != NULL);
		m_container->push(val); //pushes value into Unordered array
	}

	void pop()
	{
		assert(m_container != NULL);
		m_container->pop(); // pops value from Unordered array
	}

	const T& top()
	{
		assert(m_container != NULL);
		// Derefence our pointer to the UnorderedArray object (to get the object itself)
		// Subtracts GetSize() (the size of array) - 1 to get the index of the top array
		//Then use array notation to return the top element of the array
		return (*m_container)[m_container->GetSize() - 1];
	}
	//----------------END STACK FUNCTIONS-----------------//
	int GetSize()
	{
		assert(m_container != NULL);
		return m_container->GetSize();
	}
	int GetMaxSize()
	{
		assert(m_container != NULL);
		return m_container->GetMaxSize();
	}
	bool isEmpty()
	{
		assert(m_container != NULL);
		return (m_container->GetSize() == 0);
	}
private:
	// Variables
	UnorderedArray<T>* m_container;
};