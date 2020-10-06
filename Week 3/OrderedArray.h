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
	~OrderedArray()
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
		//			by finding the index of the value greater than val
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
		// Call to the binarySearch recursive function
		// Binary Search: searchKey, initial lowerbound, initial upperbound
		return binarySearch(searchKey, 0, m_numElements - 1);
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
	int GetSize() { return m_numElements; }
	int GetMaxSize() { return m_maxSize; }
	int GetGrowSize() { return m_growSize; }

	void SetGrowSize(int val)
	{
		assert(val >= 0);
		m_growSize = val;
	}
private:
	// Recursive Binary Search
	int binarySearch(T searchKey, int lowerBound, int upperBound)
	{
		assert(m_array != NULL);
		assert(lowerBound >= 0);
		assert(upperBound < m_numElements);

		// Bitwise divide by 2
		int current = (lowerBound + upperBound) >> 1;
		// Did we find the searchKey at current
		if (m_array[current] == searchKey)
		{
			// we found the searchkey in the array. Return the index
			return current;
		}
		// Have we searched the entire array?
		else if (lowerBound > upperBound)
		{
			// did not find searchKey within m_array
			return -1;
		}
		// which half is searchKey in?
		else
		{
			if (m_array[current] < searchKey)
			{
				// Search the upper half of the array
				return binarySearch(searchKey, current + 1, upperBound);
			}
			else
			{
				// Search the lower half of the array
				return binarySearch(searchKey, lowerBound, current - 1);
			}
		}
		return -1;
	}
	// Expand
	bool Expand()
	{
		if (m_growSize <= 0)
		{
			return false;
		}
		T* temp = new T[m_maxSize + m_growSize];
		assert(temp != NULL);
		// Copy the values of the original array (m_array) to the new array (temp)
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