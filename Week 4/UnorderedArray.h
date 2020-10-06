#pragma once
#include <cassert>

template<class T>
class UnorderedArray
{
public:
	// Constructor
	UnorderedArray(int size, int growBy = 1) :
		m_array(NULL), m_maxSize(0), m_growSize(0), m_numElements(0)
	{
		if (size)
		{
			m_maxSize = size;
			m_array = new T[m_maxSize]; // Dynamically allocating an array to m_maxSize
			memset(m_array, 0, sizeof(T) * m_maxSize); // Explicitly allocating memory based on type T

			m_growSize = ((growBy > 0) ? growBy : 0);
		}
	}
	// Destructor
	~UnorderedArray()
	{
		if (m_array != NULL)
		{
			delete[] m_array;
			m_array = NULL;
		}
	}
	// Insertions
	// Fast insertion for UnorderedArray -- Big-O is O(1)
	void push(T val)
	{
		assert(m_array != NULL); // Debugging purposes
		if (m_numElements >= m_maxSize)
		{
			Expand();
		}
		// My array has space for the new value
		m_array[m_numElements] = val;
		m_numElements++;
	}
	// Deletion
	// Remove the last item inserted into the array
	void pop()
	{
		if (m_numElements > 0)
		{
			m_numElements--;
		}
	}
	// Remove an item given an index
	// (Almost) Brute-force execution -- Big-O = O(N)
	void remove(int index)
	{
		assert(m_array != NULL);
		if (index >= m_numElements)
		{
			return; 
		}

		for (int i = index; i < m_numElements; i++)
		{
			if (i + 1 < m_numElements)
			{
				m_array[i] = m_array[i + 1];
			}
		}
		m_numElements--;
	}
	// Searching (Linear search) -- Big O = O(N)
	int search(T val)
	{
		assert(m_array != NULL);

		// Brute force search
		for (int i = 0; i < m_numElements; i++)
		{
			if (m_array[i] == val)
			{
				return i;
			}
		}
		return -1;
	}
	// ------SORTING ALGORITHMS --------------
	// Bubble Sort -- Big O = O(N^2)
	void BubbleSort()
	{

	}
	// Overload the [] operator
	T& operator[](int index)
	{
		assert(m_array != NULL && index < m_numElements);
		return m_array[index];
	}
	// Clear -- Big O = O(1)
	void clear()
	{
		m_numElements = 0;
	}
	// Gets and Sets
	int GetSize() return m_numElements;
	int GetMaxSize() return m_maxSize;
	int GetGrowSize() return m_growSize;

	void SetGrowSize(int val)
	{
		assert(val >= 0);
		m_growSize = val;
	}
private:
	// Expansion
	bool Expand()
	{
		if (m_growSize <= 0)
		{
			return false;
		}
		// Create the new array
		T* temp = new T[m_maxSize + m_growSize];
		assert(temp != NULL);
		// Copy the contents of the original array (m_array) to the new array (temp)
		memcpy(temp, m_array, sizeof(T) * m_maxSize);
		// Delete the old array
		delete[] m_array;
		// Clean up variable assignments
		m_array = temp;
		temp = NULL;
		m_maxSize += m_growSize;

		return true;
	}
private:
	// Variables
	T* m_array; // pointer to the beginning of the array
	int m_maxSize; // max size of the array
	int m_growSize; // amount the array can grow through expansion
	int m_numElements; // Number of items currently in my array
};