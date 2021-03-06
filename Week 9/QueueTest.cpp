#include <iostream>
#include "Queue.h"
using namespace std;

int main()
{
	cout << "Queue Data Structure Example " << endl << endl;

	// Create and populate our queue
	const int SIZE = 5;
	Queue<int> intQueue(SIZE);
	//Deque<int> intQueue(SIZE);

	for (int i = 0; i < SIZE; i++)
	{
		intQueue.push(10 + i);
	}

	cout << "Queue Contents (Size - " << intQueue.GetSize() << ") :";
	while (intQueue.isEmpty() == false)
	{
		// prints out the value of the first node to enter the list
		// first node of the list is the bottom node of the list
		cout << " " << intQueue.front();
		intQueue.pop();
	}

	cout << endl << endl;

	if (intQueue.isEmpty() == true)
	{
		cout << "The int queue is empty " << endl << endl;
	}
	else
	{
		cout << "The int queue is NOT empty " << endl << endl;
	}

	return 0;
}