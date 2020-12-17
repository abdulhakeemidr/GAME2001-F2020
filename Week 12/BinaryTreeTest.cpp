#include <iostream>
#include "BinaryTree.h"

using namespace std;

int main(int args, char** argc)
{
    cout << "Binary Trees" << endl;
    cout << endl;

    BinaryTree<int> binaryTree;

    binaryTree.push(20); //step 1 result -> root node of tree
    binaryTree.push(10); //step 2 result -> left child of root node
    binaryTree.push(12); //step 3 result -> right child of step 2 node
    binaryTree.push(27); //step 4 result -> right child of root node
    binaryTree.push(9);  //step 5 result -> left child of step 2 node
    binaryTree.push(50); //step 6 result -> right child of step 4 node
    binaryTree.push(33); //step 7 result -> left child of step 6 node
    binaryTree.push(6);  //step 8 result -> left child of step 5 node

    binaryTree.remove(27);

    if (binaryTree.search(20) == true)
        cout << "The key 20 found!" << endl;
    else
        cout << "The key 20 NOT found!" << endl;

    if (binaryTree.search(14) == true)
        cout << "The key 14 found!" << endl;
    else
        cout << "The key 14 NOT found!" << endl;

    if (binaryTree.search(27) == true)
        cout << "The key 27 found!" << endl;
    else
        cout << "The key 27 NOT found!" << endl;

    cout << endl;

    cout << " Pre-order: ";
    binaryTree.DisplayPreOrder();
    cout << endl;

    cout << "Post-order: ";
    binaryTree.DisplayPostOrder();
    cout << endl;

    cout << "  In-order: ";
    binaryTree.DisplayInOrder();
    cout << endl << endl;

    return 1;
}