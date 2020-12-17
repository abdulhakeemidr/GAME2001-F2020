#pragma once
#include <vector>
#include <stack>
#include <queue>
#include <cassert>

using namespace std;

// Describe a single vertex
template <class T>
class GraphVertex
{
public:
	GraphVertex() : m_node(NULL) {}
	GraphVertex(T node) : m_node(node) { }

	T GetNode() { return m_node; }
private:
	T m_node;
};

// Describe the graph as a whole
template <class T>
class Graph
{
public:
	Graph(int numVerts) : m_maxVerts(numVerts), m_adjMatrix(NULL), m_vertVisits(NULL), m_vertices(NULL)
	{
		assert(numVerts > 0);

		m_vertices.reserve(m_maxVerts);

		m_adjMatrix = new char* [m_maxVerts];	// Instantiates my 2D array as a whole
		assert(m_adjMatrix != NULL);

		m_vertVisits = new char[m_maxVerts];
		assert(m_vertVisits != NULL);

		memset(m_vertVisits, 0, m_maxVerts);

		for (int i = 0; i < m_maxVerts; i++)
		{
			m_adjMatrix[i] = new char[m_maxVerts];	// A single array instantiation
			assert(m_adjMatrix[i] != NULL);

			memset(m_adjMatrix[i], 0, m_maxVerts);
		}
	}
	~Graph()
	{
		if (m_adjMatrix != NULL)
		{
			for (int i = 0; i < m_maxVerts; i++)
			{
				if (m_adjMatrix[i] != NULL)
				{
					delete[] m_adjMatrix[i];
					m_adjMatrix[i] = NULL;
				}
			}

			delete[] m_adjMatrix;
			m_adjMatrix = NULL;
		}

		if (m_vertVisits != NULL)
		{
			delete[] m_vertVisits;
			m_vertVisits = NULL;
		}
	}
	bool push(T node)
	{
		if ((int)m_vertices.size() >= m_maxVerts)
		{
			// Not enough space to push a new vertex
			return false;
		}

		// We do have space to push a new vertex
		m_vertices.push_back(GraphVertex<T>(node));
		return true;
	}
	// Nondirectional
	void attachEdge(int index1, int index2)
	{
		assert(m_adjMatrix != NULL);

		// Fill out the adjacency  matrix to mark a connected vertex
		// Nondirectional edge (2 way)
		m_adjMatrix[index1][index2] = 1;
		m_adjMatrix[index2][index1] = 1;
	}
	void attachDirectedEdge(int index1, int index2)
	{
		assert(m_adjMatrix != NULL);

		// Fill ou tthe adjacency matrix to mark a connected vertex
		// Directional
		m_adjMatrix[index1][index2] = 1;
	}
	int getNextUnvisitedVertex(int index)
	{
		assert(m_adjMatrix != NULL);
		assert(m_vertVisits != NULL);

		// Traverse through all vertices in the graph (potentially)
		for (int i = 0; i < (int)m_vertices.size(); i++)
		{
			// Check if a connection between "index" and "i" exists
			// Check if the vertex at "i" has not already been checked
			if (m_adjMatrix[index][i] == 1 && m_vertVisits[i] == 0)
			{
				return i;
			}
		}

		// All adjacent vertices have been visited.
		return -1;
	}

	// Traverse down a path until destination is reached or no path is found.
	// Stack gets popped back until another path is found
	bool DepthFirstSearch(int startIndex, int endIndex)
	{
		assert(m_adjMatrix != NULL);
		assert(m_vertVisits != NULL);

		// We've visited our first vertex
		m_vertVisits[startIndex] = 1;

		// FOR OUTPUT PURPOSES ONLY
		cout << m_vertices[startIndex].GetNode();

		stack<int> searchStack;
		int vert = 0;

		// Push the visited vertex onto the stack
		searchStack.push(startIndex);

		// When the stack is empty OR we have found our destination, we are done.
		while (searchStack.empty() != true)
		{
			vert = getNextUnvisitedVertex(searchStack.top());

			if (vert == -1)
			{
				searchStack.pop();
			}
			else
			{
				// New unvisited vertex found!
				m_vertVisits[vert] = 1;

				// FOR OUTPUT PURPOSES ONLY
				cout << m_vertices[vert].GetNode();

				searchStack.push(vert);
			}

			if (vert == endIndex)
			{
				// Found my destination
				memset(m_vertVisits, 0, m_maxVerts);
				return true;
			}
		}

		memset(m_vertVisits, 0, m_maxVerts); // "Reset"
		return false;	// Path to destination not found from startIndex
	}

	// Search all adjacent vertices first before moving on.
	// Queue data structured used
	bool BreadthFirstSearch(int startIndex, int endIndex)
	{
		assert(m_adjMatrix != NULL);
		assert(m_vertVisits != NULL);

		// We are visitng our first vertex
		m_vertVisits[startIndex] = 1;

		// FOR OUTPUT PURPOSES
		cout << m_vertices[startIndex].GetNode();

		queue<int> searchQueue;
		int vert1 = 0, vert2 = 0;

		// Push our visited vertex to the queue

		searchQueue.push(startIndex);

		// Keep traversing until our searchQueue is empty OR we find our destination
		while (searchQueue.empty() != true)
		{
			// Save the front of the queue to vert1
			vert1 = searchQueue.front();
			searchQueue.pop();

			// Have we reached our destination?
			if (vert1 == endIndex)
			{
				// Destination found!
				memset(m_vertVisits, 0, m_maxVerts);
				return true;
			}

			// Get all adjacent verticies
			while ((vert2 = getNextUnvisitedVertex(vert1)) != -1)
			{
				// Mark vert2 as visited
				m_vertVisits[vert2] = 1;

				// FOR OUTPUT PURPOSES
				cout << m_vertices[vert2].GetNode();

				searchQueue.push(vert2);
			}
		}

		memset(m_vertVisits, 0, m_maxVerts);
		return false;
	}

private:
	vector<GraphVertex<T>> m_vertices;	// Graph object (array)
	int m_maxVerts;	// Max number of vertices allowed

	char** m_adjMatrix;		// Pointer to a 2D array ( Adjacency Matrix )
	char* m_vertVisits;		// Pointer to an array ( Vertices visited )
};