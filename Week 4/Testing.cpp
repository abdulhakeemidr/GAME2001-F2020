#include <iostream>
#include "UnorderedArray.h"

using namespace std;

int main()
{
	cout << "Selection Sort Algorithm" << endl;

	UnorderedArray<int> array(5);
	array.push(80);
	array.push(64);
	array.push(99);
	array.push(76);
	array.push(5);

	cout << "Before sort: ";
	for (int i = 0; i < array.GetSize(); i++)
	{
		cout << " " << array[i];
	}

	cout << endl;

	array.SelectionSort();

	cout << "After sort: ";
	for (int i = 0; i < array.GetSize(); i++)
	{
		cout << " " << array[i];
	}

	cout << endl << endl;

	return 0;
}