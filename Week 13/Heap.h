#pragma once
#include <vector>

using namespace std;

template<class T>
class Heap
{
public:
	// Constructors
	Heap() {}
	// Allow minimum size to be specified
	Heap(int minSize)
	{
		// reserve a size of the vector set when a Heap instance
		// is initialized
		m_heap.reserve(minSize);
	}

	// Insert elements into the end of the array
	// "Bubble" up the value to the correct position
	void push(T key)
	{
		// Push to the back of the array (m_heap)
		m_heap.push_back(key);

		// Compare the inserted key with the parent node and swap if need be.
		// size() returns number of elements inside a vector array
		// Set "index" to point to the last element added to the vector array
		int index = (int)m_heap.size() - 1;
		// Store a copy of the last element in temp
		T temp = m_heap[index];
		// Find the parent index of any child index
		int parentIndex = (index - 1) / 2;

		// checks if the current index is greater than 0 (vector not empty) and
		// the new value inserted (temp) is greater than the 
		while (index > 0 && temp >= m_heap[parentIndex])
		{
			// Bubbling up through the heap
			m_heap[index] = m_heap[parentIndex];	// Sets the element at index equal to the element at parentIndex
			index = parentIndex;
			parentIndex = (index - 1) / 2;
		}

		// Set the pushed value into the correct location within the heap
		m_heap[index] = temp;
	}

	// Pop works top down
	// Remove the top element and replace it with the last element.
	// Propogate the new top element down through the heap
	// This ensure the highest value sits up top
	void pop()
	{
		int index = 0;

		// Replace the top element with the last element of the array. Pop off the last element
		m_heap[index] = m_heap[(int)m_heap.size() - 1];
		m_heap.pop_back();

		// Check if we still have a heap to propogate through
		if (m_heap.size() > 0)
		{
			// Restructuring the heap such that the largest item is at the top.

			T temp = m_heap[index];
			int currentIndex = 0, leftIndex = 0, rightIndex = 0;

			// Check which side of the node we are traversing down
			// Traversal
			while (index < (int)m_heap.size() / 2)
			{
				// Calculate the left index and right index of any element (if they exist)
				leftIndex = 2 * index + 1;	// Returns the left child index of any parent index
				rightIndex = leftIndex + 1;

				// Which side of the parent node are we going down?
				if (rightIndex < (int)m_heap.size() && m_heap[leftIndex] < m_heap[rightIndex])	// Going right?
				{
					// Traverse right
					currentIndex = rightIndex;
				}
				else
				{
					// Traverse left
					currentIndex = leftIndex;
				}

				// Is there a case where I need to exit out this loop early?
				// When my "temp" is greater that what my currentIndex is pointing too.
				if (temp >= m_heap[currentIndex])
				{
					break;
				}

				// ...otherwise, we have to iterate once again.
				// Set the value to move elements upwards through the tree
				m_heap[index] = m_heap[currentIndex];
				index = currentIndex;
			}

			// Assign the node (stored in temp) to the correct position
			m_heap[index] = temp;
		}
	}

	T peek()
	{
		return m_heap[0];
	}

	int size()
	{
		return (int)m_heap.size();
	}

private:
	// storing a vector array of heap data of T data type
	vector<T> m_heap;
};