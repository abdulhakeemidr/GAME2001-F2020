#include <iostream>
#include "Queue.h"
#include "Deque.h"
using namespace std;

int main()
{
	cout << "Queue Data Structure Example " << endl << endl;

	// Create and populate our queue
	const int SIZE = 5;
	//Queue<int> intQueue(SIZE);
	Deque<int> intDeque(SIZE);

	for (int i = 0; i < SIZE; i++)
	{
		intDeque.push_front(10 + i);
	}

	cout << "Queue Contents (Size - " << intDeque.GetSize() << ") :";
	while (intDeque.isEmpty() == false)
	{
		cout << " Front: " << intDeque.front();
		cout << " Back: " << intDeque.back();
		cout << endl;
		intDeque.pop_front();
	}

	cout << endl << endl;

	if (intDeque.isEmpty() == true)
	{
		cout << "The int queue is empty " << endl << endl;
	}
	else
	{
		cout << "The int queue is NOT empty " << endl << endl;
	}

	return 0;
}