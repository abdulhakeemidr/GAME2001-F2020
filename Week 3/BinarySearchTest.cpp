#include <iostream>
#include "OrderedArray.h"
using namespace std;

int main()
{
	cout << "Recursive Binary Search Example" << endl;
	OrderedArray<int> array(3);

	// Test expansion of array
	array.push(43);
	array.push(6);
	array.push(23);
	array.push(94);
	array.push(17);
	array.push(83);
	array.push(44);
	array.push(28);

	cout << "Ordered array contents: ";

	for (int i = 0; i < array.GetSize(); i++)
	{
		cout << " " << array[i];
	}

	// Test the search
	cout << endl << endl;
	cout << "Search for 43 was found at index" << endl << endl;
	cout << array.search(43) << endl << endl;
}