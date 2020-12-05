#include <iostream>
#include "UnorderedArray.h"

using namespace std;


int main(int args, char* arg[])
{
    cout << "Shellsort Algorithm" << endl << endl;

    const int size = 500;
    int i = 0;

    UnorderedArray<int> array(size);

    for (i = 0; i < size; i++)
        array.push(rand() % 100);

    cout << "Before shellsort sort:";

    for (i = 0; i < size; i++)
        cout << " " << array[i];

    cout << endl;

    array.Shellsort();

    cout << endl;

    cout << " After shellsort sort:";

    for (i = 0; i < size; i++)
        cout << " " << array[i];

    cout << endl << endl;
    return 1;
}