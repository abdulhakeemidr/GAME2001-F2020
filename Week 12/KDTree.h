#pragma once
#include <vector>
#include <cassert>

using namespace std;

template<class T>
class KdTree;

template<class T>
struct KdNode
{
    friend class KdTree<T>;

public:
    KdNode(vector<T>& key) : m_key(key), m_left(NULL),
        m_right(NULL)
    {

    }

    ~KdNode()
    {
        if (m_left != NULL)
        {
            delete m_left;
            m_left = NULL;
        }

        if (m_right != NULL)
        {
            delete m_right;
            m_right = NULL;
        }
    }

private:
    vector<T> m_key;
    KdNode* m_left;
    KdNode* m_right;
};

template<typename T>
class KdTree
{
public:
    KdTree(int depth) : m_root(0), m_depth(depth)
    {
        assert(depth > 0);
    }


    ~KdTree()
    {
        if (m_root != NULL)
        {
            delete m_root;
            m_root = NULL;
        }
    }

    void push(vector<T>& key)
    {
        KdNode<T>* newNode = new KdNode<T>(key);

        if (m_root == NULL)
        {
            m_root = newNode;
            return;
        }

        KdNode<T>* currentNode = m_root;
        KdNode<T>* parentNode = m_root;
        int level = 0;

        while (1)
        {
            parentNode = currentNode;

            if (key[level] < currentNode->m_key[level])
            {
                currentNode = currentNode->m_left;

                if (currentNode == NULL)
                {
                    parentNode->m_left = newNode;
                    return;
                }
            }
            else
            {
                currentNode = currentNode->m_right;

                if (currentNode == NULL)
                {
                    parentNode->m_right = newNode;
                    return;
                }
            }

            level++;

            if (level >= m_depth)
                level = 0;
        }
    }

    void displayRange(const vector<T>& low,
        const vector<T>& high)
    {
        displayRange(0, low, high, m_root);
    }

private:
    void displayRange(int level, const vector<T>& low,
        const vector<T>& high,
        KdNode<T>* node)
    {
        if (node != NULL)
        {
            int i;

            for (i = 0; i < m_depth; i++)
            {
                if (low[i] > node->m_key[i] || high[i] < node->m_key[i])
                    break;
            }

            if (i == m_depth)
            {
                cout << "(";

                for (int j = 0; j < m_depth; j++)
                {
                    cout << node->m_key[j];

                    if (j != m_depth - 1)
                        cout << ", ";
                }

                cout << ")" << endl;
            }

            level++;

            if (level >= m_depth)
                level = 0;

            if (low[level] <= node->m_key[level])
                displayRange(level, low, high, node->m_left);

            if (high[level] >= node->m_key[level])
                displayRange(level, low, high, node->m_right);
        }
    }

private:
    KdNode<T>* m_root;
    int m_depth;
};