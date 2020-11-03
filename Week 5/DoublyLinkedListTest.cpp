#include <iostream>
#include "DoublyLinkedList.h"

using namespace std;

int main()
{
	cout << "Doubly Linked List Example" << endl << endl;

	DoublyLinkedList<int> lList;

	lList.Push(101);
	lList.Push_Front(102);
	lList.Pop();
	lList.Push(201);
	lList.Push_Front(301);
	lList.Push(801);
	lList.Push(401);
	lList.Push(1);
	lList.Pop();
	lList.Pop_Front();
	lList.Push(701);

	LinkIterator<int> it;

	for (it = lList.Begin(); it != lList.End(); it++)
	{
		cout << " " << *it;
	}

	cout << endl << endl;

	for (it = lList.Last(); it != NULL; it--)
	{
		cout << " " << *it;
	}

	cout << endl << endl;

	return 0;
}