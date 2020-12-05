#pragma once
#include <string>
using namespace std;

// HashItems are what will be stored in the Hashtable
template<class T>
class HashItem
{
public:
	HashItem() : m_key("") { }
	~HashItem() { }

	// Gets and sets
	string GetKey() { return m_key; }
	void SetKey(string k) { m_key = k; }

	T GetObject() { return m_obj; }
	void SetObj(T obj) { m_obj = obj; }

	// Overload operator 
	// Equivalence operator
	bool operator==(HashItem& item)	// Allow us to compare 2 HashItem's with each other
	{
		if (m_key == item.GetKey())
		{
			return true;
		}

		return false;
	}

	// Assignment operator
	void operator=(HashItem item)
	{
		m_key = item.GetKey();
		m_obj = item.GetObject();
	}
private:
	string m_key; // m_key holds the hashing value
	T m_obj; // m_obj stores the value the HashItem holds
};

template<class T>
class HashTable
{
public:
	// Constructor and Destructor
	HashTable(int size) : m_size(0), m_totalItems(0)
	{
		if (size > 0) // Input validation
		{
			// Gets the prime number just above the value (size) that is passed
			// ensures the size passed (m_size) is always be an odd value
			m_size = GetNextPrimeNum(size);
			m_table = new HashItem<T>[m_size];
		}
	}
	~HashTable()
	{
		if (m_table != NULL)
		{
			delete[] m_table;
			m_table = NULL;
		}
	}
	// Private functions
private:
	bool isNumPrime(int val)
	{
		// Checks if val is divisible by i
		for (int i = 2; (i * i) <= val; i++) 
		{
			// Any value (i) that leaves no remainder (divisible by i)
			// the function returns false
			if ((val % i) == 0)
			{
				return false;
			}
		}

		return true;
	}

	// Gets the next prime number above the passed value (val)
	int GetNextPrimeNum(int val)
	{
		int i;

		for (i = val + 1; ; i++) // "Infinite" for loop
		{
			if (isNumPrime(i))	// Checks if 'i' is a prime number
			{
				break;
			}
		}

		return i;
	}
	// Public functions
public:
	// Insert
	bool Insert(T& obj)
	{
		// Check if the table is full
		if (m_totalItems == m_size)
		{
			// Expand the table. But that's expensive
			return false;
		}

		int hash = HashFunction(obj);

		// -------- LINEAR PROBING -------
		// Checks to see if there is a key already stored in there (i.e. if(it is NOT "") )
		while (m_table[hash].GetKey() != "")
		{
			// This is the essence of Linear Probing
			// the hash Index value jumps linearly (adds 1) until it finds an empty hash Index memory address
			hash++;
			// Ensures the value of the hash doesn't go above the size of the table (m_size)
			hash %= m_size;	// "Safe guard". Wrap around the front of the hash table if I reach the end
		}

		// Insert the item into the table
		m_table[hash].SetKey(obj.GetHashString());
		m_table[hash].SetObj(obj);

		// Increment total items
		m_totalItems++;

		return true;
	}
	// Delete
	void Delete(T& obj)
	{
		int hash = HashFunction(obj);
		int originalHash = hash;

		while (m_table[hash].GetKey() != "")
		{
			// The key the HashItem has is the same as the objects HashString
			// i.e. if the object's value you are searching for is in the Hashtable
			if (m_table[hash].GetKey() == obj.GetHashString())
			{
				// Delete the key from the Hashtable
				m_table[hash].SetKey("");
				// Decrease the total number of items stored
				m_totalItems--;

				return;
			}

			// Linear Probing -> Checks through each hash linearly
			hash++;
			hash %= m_size;		// Wrapping

			// if the hash returns back to the beginning
			if (originalHash == hash)
			{
				return;
			}
		}
	}
	// Finds the HashItem with hashString and stores it in the memory address passed into obj
	bool Find(string hashString, T* obj)
	{
		int hash = HashFunction(hashString);
		int originalHash = hash;

		// Find only checks to see if the original hash of the key (hashString) is empty
		// Doesnt work well if there are two identical keys stored in the hashtable and the first is deleted
		// Because it only checks if the first key is stored
		while (m_table[hash].GetKey() != "")
		{
			// Compare current hash value index to hash string parameter
			if (m_table[hash].GetKey() == hashString)
			{
				// Found the object!
				if (obj != NULL)
				{
					*obj = m_table[hash].GetObject();

					return true;
				}
			}

			// Linear probing
			hash++;
			hash %= m_size;

			if (originalHash == hash)
			{
				return false;
			}
		}
	}

	// HashFunction takes the object and gets the string member using obj.GetHashString()
	int HashFunction(T& obj)
	{
		// returns the function below (HashFunction(string&) )
		return HashFunction(obj.GetHashString());
	}
	int HashFunction(const string& HashString)
	{
		int hash = 0;

		// Iterate through each character of the HashString and accumulate its value
		for (int i = 0; i < HashString.length(); i++)
		{
			hash += HashString[i];
		}

		return hash % m_size;	// Constrain our hash value to 0 up to m_size
	}
	int GetSize()
	{
		return m_size;
	}
	int GetTotalItems()
	{
		return m_totalItems;
	}
private:
	HashItem<T>* m_table;	// Defines a pointer to the beginning of an array
	int m_size, m_totalItems;	// Size of the hash table and total items in the hash table
};