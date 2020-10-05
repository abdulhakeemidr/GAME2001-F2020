// Factorial: Ex: 9! = 9 * 8 * 7 * 6 * 5 * 4 * 3 * 2 * 1
// Double Factorial (semi-factorial) 9!! = 9 * 7 * 5 * 3 * 1
#include <iostream>
#include <cassert>
using namespace std;

// Single factorial
int factorial(int x)
{
	assert(x >= 0);
	// Base Case
	if (x == 0)
	{
		// I know that 0! = 1
		return 1;
	}

	// Tail Recursion
	return(factorial(x - 1) * x);
}

// Double factorial
int doubleFactorial(int x)
{
	assert(x >= 0);
	// Base Case
	if (x == 0 || x == 1)
	{
		// I know 0! = 1
		return 1;
	}

	// Tail recursion
	return(doubleFactorial(x - 2) * x);
}

// main
int main()
{
	cout << "FACTORIALS" << endl;

	cout << "The factorial of 5: ";
	cout << factorial(5) << endl;

	cout << "The double factorial of 7 is ";
	cout << doubleFactorial(7) << endl;
	return 0;
}