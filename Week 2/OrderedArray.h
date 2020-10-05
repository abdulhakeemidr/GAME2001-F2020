#pragma once
#include <cassert>

template <class T>
class OrderedArray
{
public:
	// Constructor
	OrderedArray(int size, int growBy = 1) :
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
	// Insertion -- Big O = O(N)
	int push(T val)
	{
		assert(m_array != NULL);
		if (m_numElements >= m_maxSize)
		{
			Expand();
		}
		int i, k;
		// Step 1: Find the index to insert val
		for (i = 0; i < m_numElements; i++)
		{
			if (m_array[i] > val)
			{
				break;
			}
		}
		// Step 2: Shift everything to the right of the indexx forward by one
		for (k = m_numElements; k > i; k--) // Moving backwards through the array starting at m_numElements
		{
			m_array[k] = m_array[k - 1];
		}
		// Step 3: Insert val to index
		m_array[i] = val;

		m_numElements++;
		return i;
	}
	// Deletion
	// Remove the last item in the array
	void pop()
	{
		if (m_numElements > 0)
		{
			m_numElements--;
		}
	}
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
	// Searching -- Binary Search -- Big O = O(log N)
	int search(T searchKey)
	{
		assert(m_array != NULL);
		// Helper variables
		int lowerBound = 0;
		int upperBound = m_numElements - 1;
		int current = 0;

		while (1)	// <-- Replaced with recursion
		{
			current = (lowerBound + upperBound) >> 1; // Preview of Bitwise operations.
			// The (>> 1) means divide by 2

			// Binary search steps:
			// Step 1: Check if the middle is the value we are looking for
			if (m_array[current] == searchKey)
			{
				// Found the item in the middle of the array. Return the index of the item
				return current;
			}
			// Step 2: Check that we've searched the whole array. Can't find the item
			else if (lowerBound > upperBound)
			{
				return -1;
			}
			else
			{
				// Step 3: Check which half of the array the value is in searchKey value's range
				if (m_array[current] < searchKey)
				{
					lowerBound = current + 1;
				}
				else
				{
					upperBound = current - 1;
				}
			}
		}
		return -1;
	}
	// Overloaded [] operator
	const T& operator[](int index)
	{
		assert(m_array != NULL && index < m_numElements);
		return m_array[index];
	}
	// Clear
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
	// Expand
	bool Expand()
	{
		if (m_growSize <= 0)
		{
			return false;
		}
		T* temp = new T[m_maxSize + m_growSize];
		assert(temp != NULL);
		memcpy(temp, m_array, sizeof(T) * m_maxSize);
		delete[] m_array;
		m_array = temp;
		temp = NULL;
		m_maxSize += m_growSize;

		return true;
	}
private:
	// Variables
	T* m_array; // Pointer to the beginning of the array
	int m_maxSize; // Max number of items in the array
	int m_growSize; // How large the array will grow by
	int m_numElements; // Number of elements currently in the array
};