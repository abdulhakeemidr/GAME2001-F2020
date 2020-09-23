// "Generic" classes or functions
// Compare 2 numbers. Return smallest. Return largest
#include <iostream>
using namespace std;

// Check 2 "things". Return the smallest
template <class T>
T min_func(T lVal, T RVal)
{
	if (lVal > RVal)
	{
		return RVal;
	}
	return lVal;
}

// Check 2 "things". Return the largest
template <class T>
T max_func(T lVal, T rVal)
{
	if (lVal < rVal)
	{
		return rVal;
	}

	return lVal;
}

// implement a template class here
template <class T>
class TemplateClass
{
public:
	TemplateClass(T val)
	{
		m_val = val;
	}

	// MISSING SOMETHING HERE
	bool operator<(TemplateClass& rval)
	{
		return m_val < rval.GetVal();
	}

	bool operator>(TemplateClass& rval)
	{
		return m_val > rval.GetVal();
	}

	T GetVal()
	{
		return m_val;
	}
private:
	T m_val;
};

// Main
int main()
{
	cout << "Template Example" << endl << endl;
	cout << "Min = " << min_func(30, 26) << endl;
	cout << "Max = " << max_func(36.1, 43.6) << endl;

	// Create 2 "TemplateClass" objects and compare them
	// 1. Two instances of a templace class are created and the template class constructor parameters
	// is specified to take in an int [ TemplateClass<int>("integer value here") ]
	// 2. Since the two instances are passed as arguments to the template function [max_func()],
	// the function turns into a function that returns the instance of that template class
	// 3. The max_func function now determines the instance that holds the largest m_val variable 
	// stored in it by using the classes overloaded < operator
	// 4. the function max_func() returns a copy of the instance that carries the largest m_val variable
	// 5. max_func().GetVal() means that the instance that gets return has its GetVal function called which
	// returns the m_val variable that is the datatype specified by the constructor when you created the instance
	// m_val is an int variable
	cout << "Max (objects) = " << max_func(TemplateClass<int>(7), TemplateClass<int>(4)).GetVal();

	return 0;
}