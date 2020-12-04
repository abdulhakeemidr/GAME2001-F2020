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
		assert(m_array != NULL);

		T temp;

		for (int k = m_numElements - 1; k > 0; k--)
		{
			// Comparing 2 adjacent elements
			for (int i = 0; i < k; i++)
			{
				if (m_array[i] > m_array[i + 1])
				{
					// Swap the elements
					temp = m_array[i];
					m_array[i] = m_array[i + 1];
					m_array[i + 1] = temp;
				}
			}
		}
	}
	// Selection Sort -- Big-O = O(N^2)
	/*void SelectionSort()
	{
		assert(m_array != NULL);
		T temp;
		int min = 0;

		for (int k = 0; k < m_numElements - 1; k++)
		{
			min = k;

			// Iterate through the array to find the smallest value
			if (int i = k + 1; i < m_numElements; i++)
			{
				if (m_array[i] < m_array[min])
				{
					// Store the index to the smallest element
					min = i;
				}
			}
			// Swapping the lowest element with the lowest available index
			if (m_array[k] > m_array[min])
			{
				// Swap
				temp = m_array[k];
				m_array[k] = m_array[min];
				m_array[min] = temp;
			}
		}
	}*/
	void SelectionSort()
	{
		assert(m_array != NULL);

		T temp;
		int min = 0;

		// The lowest position to swap the smallest element too....
		for (int k = 0; k < m_numElements - 1; k++)
		{
			min = k;

			// Iterate through the array to find the smallest value
			for (int i = k + 1; i < m_numElements; i++)
			{
				if (m_array[i] < m_array[min])
				{
					// Store the index to the smallest element
					min = i;
				}
			}

			// Swapping of the lowest element with the lowest available index
			if (m_array[k] > m_array[min])
			{
				// Swap
				temp = m_array[k];
				m_array[k] = m_array[min];
				m_array[min] = temp;
			}
		}
	}
	// Insertion Sort -- Big - O = O(N^2)
	void InsertionSort()
	{
		assert(m_array != NULL);

		T temp;
		int i = 0;

		for (int k = 1; k < m_numElements; k++)
		{
			temp = m_array[k];
			i = k;

			// Shifting of elements if necessary. Create a space for an element
			// to be inserted in the correct location
			while (i > 0 && m_array[i - 1] >= temp)
			{
				// Push elements to the right
				m_array[i] = m_array[i + 1];
				i--;
			}
			// Place the held item in the correct location
			m_array[i] = temp;
		}
	}
	// Merge Sort -- Big - O = O(N * log (N) )
	void MergeSort()
	{
		assert(m_array != NULL);

		T* tempArray = new T[m_numElements];
		assert(tempArray != NULL);
		MergeSort(tempArray, 0, m_numElements - 1);
		delete[] tempArray;
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
	int GetSize() { return m_numElements; }
	int GetMaxSize() { return m_maxSize; }
	int GetGrowSize() { return m_growSize; }

	void SetGrowSize(int val)
	{
		assert(val >= 0);
		m_growSize = val;
	}
private:
	// Recursive Merge Sort
	void MergeSort(T* tempArray, int lowerBound, int upperBound)
	{
		// Base Case
		if (lowerBound == upperBound)
		{
			return;
		}

		// Determine the middle of the array
		int mid = (lowerBound + upperBound) >> 1; // Bit shift version of divide by 2

		MergeSort(tempArray, lowerBound, mid); // lower half of merge sort array
		MergeSort(tempArray, mid + 1, upperBound); // upper half of merge sort array

		// Merge
		Merge(tempArray, lowerBound, mid + 1, upperBound);
	}
	void Merge(T* tempArray, int low, int mid, int upper)
	{
		// lowerBound, mid+1, upperBound
		int tempLow = low, tempMid = mid - 1;
		int index = 0;

		while (low <= tempMid && mid <= upper)
		{
			// lower of the 2 values is smaller, move it tp the tempArray
			if (m_array[low] < m_array[mid])
			{
				tempArray[index++] = m_array[low++];
				// or low++;
				// index++; after, the same thing
			}
			else
			{
				tempArray[index++] = m_array[mid++];
			}
		}

		while (low <= tempMid)
		{
			tempArray[mid++] = m_array[low++];
		}
		while (mid <= tempMid)
		{
			tempArray[index++] = m_array[mid++];
		}

		// Place the stored tempArray into the main array in the correct locations
		for (int i = 0; i < upper - tempLow + 1; i++)
		{
			m_array[tempLow + i] = tempArray[i];
		}
	}
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