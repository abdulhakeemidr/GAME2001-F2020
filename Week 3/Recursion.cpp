#include <iostream>
using namespace std;

// Print down from a given number until we reach 1
void PrintNumReverse(int x)
{
	// Base Case
	if (x <= 0)
	{
		return;
	}
	//////////

	// The actual work this function has to do
	cout << " " << x;
	// Tail Recursion
	PrintNumReverse(x - 1);
}

/*
int main()
{
	cout << "Recursion Example" << endl;
	cout << "Here is a recursive call: " << endl;

	// Call a recursive function
	PrintNumReverse(3);
	return 0;
}*/