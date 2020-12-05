#pragma once
#include <cassert>

#define QUICKSORT_CUTOFF 4

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
			m_array = new T[m_maxSize];	// Dynamically allocating an array to m_maxSize
			memset(m_array, 0, sizeof(T) * m_maxSize);	// Explicitly allocating memory based on the type T

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
		assert(m_array != NULL);	// Debugging purposes

		if (m_numElements >= m_maxSize)
		{
			Expand();
		}

		// My array has space for the new value
		m_array[m_numElements] = val;
		m_numElements++;
	}
	// Deletion (2 ways)
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
	// Searching (Linear serach) -- Big O = 
	int search(T val)
	{
		assert(m_array != NULL);

		// Brute-force search
		for (int i = 0; i < m_numElements; i++)
		{
			if (m_array[i] == val)
			{
				return i;
			}
		}

		return -1;
	}
	// ----------- SORTING ALGORITHMS -------------------
	// --------------- PARTITIONING ---------------------
	void SwapElements(int index1, int index2)
	{
		assert(index1 >= 0 && index1 < m_numElements);
		assert(index2 >= 0 && index2 < m_numElements);
		assert(m_array != NULL);

		T temp = m_array[index1];
		m_array[index1] = m_array[index2];
		m_array[index2] = temp;
	}
	void QuickSort()
	{
		QuickSort(0, m_numElements - 1);
	}

	/*
	int Partition(T pivot)
	{
		return Partition(0, m_numElements - 1, pivot);
	}
	int Partition(int lIndex, int rIndex, T pivot)
	{
		int currentLeft = lIndex;
		int currentRight = rIndex;
		while (1)
		{
			// Traverse from left to right
			while (currentLeft < rIndex && m_array[currentLeft] < pivot)
			{
				// m_array[currentLeft] is small than the pivot
				// Increment by one
				currentLeft++;
			}
			// Traverse from right to left
			while (currentRight > lIndex && m_array[currentRight] > pivot)
			{
				currentRight--;
			}
			if (currentLeft >= currentRight)
			{
				// Done with partitioning
				break;
			}
			// Swap elements
			SwapElements(currentLeft, currentRight);
		}
		// Returns position of the pivot
		return currentLeft;
	}
	*/

	void Shellsort()
	{
		assert(m_array != NULL);
		T temp;
		int i = 0, k = 0;

		// Define our gap value using the Knuth method
		int seq = 1;

		while (seq <= m_numElements / 3)
		{
			// Knuth: h = h * 3 + 1
			seq = seq * 3 + 1;
		}

		// Start sorting now!
		while (seq > 0)
		{
			for (k = seq; k < m_numElements; k++)
			{
				temp = m_array[k];	// Stores m_array[k] in temp
				i = k;

				// We want to compare 2 values with a gap of "seq"
				while (i > seq - 1 && m_array[i - seq] >= temp)
				{
					// We need to swap the 2 compared values
					m_array[i] = m_array[i - seq];
					i -= seq;
				}

				m_array[i] = temp;
			}

			// "Inverse" of Knuth formula
			seq = (seq - 1) / 3;
		}
	}

	// Bubble Sort -- Big = O(N^2)
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
	// Insertion Sort -- Big-O = O(N^2)
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
			// to be inserted in the correct location.
			while (i > 0 && m_array[i - 1] >= temp)
			{
				// Push elements to the right;
				m_array[i] = m_array[i - 1];
				i--;
			}

			// Place the item in the correct lcation
			m_array[i] = temp;
		}
	}
	// Merge Sort -- Big-O = O(N logN)
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
	// Clear - Big O = O(1)
	void clear()
	{
		m_numElements = 0;
	}
	// Gets and Sets
	int GetSize()
	{
		return m_numElements;
	}
	int GetMaxSize()
	{
		return m_maxSize;
	}
	int GetGrowSize()
	{
		return m_growSize;
	}
	void SetGrowSize(int val)
	{
		assert(val >= 0);
		m_growSize = val;
	}
private:
	void QuickSort(int lVal, int rVal)
	{
		// Check whether I have enough items to do a quick sort
		// If not, do an InsertionSort instead
		if ((rVal - lVal + 1) < QUICKSORT_CUTOFF)
		{
			// Not enough items
			InsertionSort(lVal, rVal);
			return;
		}

		int center = (lVal + rVal) / 2;

		// Order left, center and right
		if (m_array[lVal] > m_array[center])
		{
			SwapElements(lVal, center);
		}
		if (m_array[lVal] > m_array[rVal])
		{
			SwapElements(lVal, rVal);
		}
		if (m_array[center] > m_array[rVal])
		{
			SwapElements(center, rVal);
		}

		int pivotIndex = Partition(lVal, rVal, center);

		QuickSort(lVal, pivotIndex - 1);	// Quicksort the left half
		QuickSort(pivotIndex, rVal);		// Quicksort the right half
	}

	int Partition(int lIndex, int rIndex, int pivot)
	{
		while (1)
		{
			while (m_array[++lIndex] < m_array[pivot]);
			while (m_array[--rIndex] > m_array[pivot]);

			if (lIndex >= rIndex)
			{
				// Done partitioning
				break;
			}

			SwapElements(lIndex, rIndex);
		}

		return lIndex;	// Where the pivot point is on the array
	}

	void InsertionSort(int lVal, int rVal)
	{
		assert(m_array != NULL);

		T temp;
		int i = 0;

		for (int k = lVal + 1; k <= rVal; k++)
		{
			temp = m_array[k];
			i = k;

			// Shifting of elements if necessary. Create a space for an element
			// to be inserted in the correct location.
			while (i > lVal && m_array[i - 1] >= temp)
			{
				// Push elements to the right;
				m_array[i] = m_array[i - 1];
				i--;
			}

			// Place the item in the correct lcation
			m_array[i] = temp;
		}
	}

	// Recursive Merge Sort
	void MergeSort(T* tempArray, int lowerBound, int upperBound)
	{
		// Base case
		if (lowerBound == upperBound)
		{
			return;
		}

		// Determine the middle of the array
		int mid = (lowerBound + upperBound) >> 1;

		MergeSort(tempArray, lowerBound, mid);		// Lower half MergeSort
		MergeSort(tempArray, mid + 1, upperBound);	// Upper half MergeSort

		// Merge
		Merge(tempArray, lowerBound, mid + 1, upperBound);
	}
	void Merge(T* tempArray, int low, int mid, int upper)
	{
		// LowerBound, Mid+1, Upperbound
		int tempLow = low, tempMid = mid - 1;
		int index = 0;

		while (low <= tempMid && mid <= upper)
		{
			// Lower of the 2 values is smaller, move it to the tempArray
			if (m_array[low] < m_array[mid])
			{
				tempArray[index++] = m_array[low++];
			}
			else
			{
				tempArray[index++] = m_array[mid++];
			}
		}

		while (low <= tempMid)
		{
			tempArray[index++] = m_array[low++];
		}
		while (mid <= upper)
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

		// Copy the contents of the original array to the new array
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
	T* m_array;			// Pointer to the beginning of the array

	int m_maxSize;		// Maximum size of my array
	int m_growSize;		// Amount the array can grow through expansion
	int m_numElements;	// Number of items currently in my array
};