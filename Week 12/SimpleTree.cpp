#include <iostream>
using namespace std;

class Node
{
public:
	// constructor accepts a node to be stored in the node instance
	Node(int obj) : m_object(obj), m_next(NULL), m_prev(NULL), m_child(NULL)
	{
		cout << "Node created!" << endl;
	}

	~Node()
	{
		m_prev = NULL;

		if (m_child != NULL)
		{
			// I HAVE CHILDREN!!!
			delete m_child;
		}

		if (m_next != NULL)
		{
			// I HAVE SIBLINGS!!!
			delete m_next;
		}

		m_child = NULL;
		m_next = NULL;

		cout << "Node: " << m_object << " destroyed" << endl;
	}

	// Adds a child to the node
	Node* AddChild(Node* node)
	{
		// Check if there are no child nodes
		if (m_child == NULL)
		{
			// No child node
			// child node is added and referenced by
			// the parent node's m_child pointer variable
			m_child = node;
		}
		else
		{
			// Since the child already exists, we add the new child
			// to become the existing child's sibling node
			// So it is next to the original child and still a child
			// of the parent node
			m_child->AddSibling(node);
		}

		return node;
	}
	Node* AddSibling(Node* node)
	{
		// Temporary iterator created that points to child's next node
		Node* ptr = m_next;

		// if there is no next (no sibling node)
		if (m_next == NULL)
		{
			// No more siblings. Add my node
			m_next = node;
			node->m_prev = this;
		}
		else
		{
			// "ptr" iterator moves across the siblings
			// until it finds a sibling with no child node after
			while (ptr->m_next != NULL)
			{
				ptr = ptr->m_next;
			}

			// Add new sibling to the end of siblings
			ptr->m_next = node;
			// make the new sibling point to the last sibling with
			// its prev pointer
			node->m_prev = ptr;
		}

		return node;
	}
	// "Recursively" display each node of the tree
	void DisplayTree()
	{
		cout << m_object;

		// Does this node have siblings?
		if (m_next != NULL)
		{
			cout << " ";
			// displays the contents of the tree starting from the "m_next" node
			// to that node's children and to the children's children
			m_next->DisplayTree();
			// This is a recursive loop
			// displays all the m_next (all the sibling nodes) until the last sibling node
			// and then moves on to display (starting from) the last siblings child nodes
		}

		// Does this node have children?
		if (m_child != NULL)
		{
			cout << endl;
			// displays the contents of the tree starting from the "m_child" node
			// to that node's children and to the children's children
			m_child->DisplayTree();
		}
	}
	// SLOW! Linear search
	bool Search(int value)
	{
		// Pseudo base-case
		// Checks if current node has the object value
		if (m_object == value)
		{
			// I found my node!
			return true;
		}

		// I have not found my node. Check children, check siblings.
		// Check children
		if (m_child != NULL)
		{
			if (m_child->Search(value) == true)
			{
				return true;
			}
		}

		// Check siblings
		if (m_next != NULL)
		{
			// I have siblings
			if (m_next->Search(value) == true)
			{
				return true;
			}
		}

		// Did not find the value being search
		return false;
	}
private:
	int m_object; // The value stored in each node instance

	// m_next are for right side sibling nodes
	// m_prev are for left side sibling nodes 
	// m_child are for children nodes
	Node* m_next, * m_prev, * m_child;
};

int main(int args, char* arg[])
{
	cout << "Simple Tree Data Structure"
		<< endl << endl;
	// Manually create the tree...
	// Creates a root of a tree (leaf node)
	Node* root = new Node(1);
	// Creates a root of another tree (leaf node 2)
	Node* subTree1 = new Node(3);
	// Two seperate trees have been created

	// a child node has been added to the root of the first tree (called "root")
	root->AddChild(new Node(2))->AddChild(new Node(8));
	// a child node has been added to the root of the second tree (called "subTree1")
	subTree1->AddChild(new Node(5));
	// a child node has been added to the root of the second tree (called "subTree1")
	subTree1->AddChild(new Node(6));

	// The root of the second tree (subTree1) is now the child node of the
	// root of the first tree ("root")
	// so the second tree is a child of the first tree
	root->AddChild(subTree1);

	// another child node has been added to the root of the first tree ("node")
	// Modified AddChild() function to return the node it added
	// This allows me to follow up by adding a child node to the added child node
	// Added 4 as a child to root node and 7 as a child to "4" new node
	root->AddChild(new Node(4))->AddChild(new Node(7));
	cout << endl;
	// Display the tree...
	cout << "Tree contents by level:" << endl;

	// displays the contents of the tree starting from the "root" node
	// to that node's children and to the children's children
	root->DisplayTree();
	cout << endl << endl;
	// Test searching...
	cout << "Searching for node 5: ";
	// Searches for the node that has the value 5 stored in it
	if (root->Search(5) == true)
		cout << "Node Found!" << endl;
	else
		cout << "Node NOT Found!" << endl;
	cout << "Searching for node 9: ";
	// Searches for the node that has the value 9 stored in it
	if (root->Search(9) == true)
		cout << "Node Found!" << endl;
	else
		cout << "Node NOT Found!" << endl;
	cout << endl;
	// Deleting a node calls the Node destructor that deletes the node and its children
	// Deleting the root node will delete the entire tree starting from
	// the child nodes attached to the bottom of the tree
	delete root;
	cout << endl << endl;
	return 1;
}