#include <iostream>
#include "LinearProbing.h"
// #include "SeperateChaining.h"

using namespace std;

class PlayerInfo
{
public:
	PlayerInfo() : name(""), score(0) { }
	PlayerInfo(string name, int score)
		: name(name), score(score)
	{}
	const string& GetHashString()
	{
		return name;
	}
	const string& GetName()
	{
		return name;
	}
	int GetScore()
	{
		return score;
	}
private:
	string name;
	int score;
};

int main()
{
	cout << "Linear Probing example" << endl << endl;
	// cout << "Separate Chaining example" << endl << endl;

	// Create and fill a hash table
	HashTable<PlayerInfo> hashTable(20);
	PlayerInfo p1("Joe", 11);
	PlayerInfo p2("Pete", 12);
	PlayerInfo p3("Neta", 2);
	PlayerInfo p4("Nate", 30);
	PlayerInfo p5("Jeff", 5);
	PlayerInfo p9("Joe", 12);
	PlayerInfo p10("Joe", 33);

	hashTable.Insert(p1);
	hashTable.Insert(p2);
	hashTable.Insert(p3);
	hashTable.Insert(p4);
	hashTable.Insert(p5);
	hashTable.Insert(p9);
	hashTable.Insert(p10);

	hashTable.Delete(p9);

	PlayerInfo p6;
	// Search for inserted items
	if (hashTable.Find("Joe", &p6))
	{
		cout << "Item: Joe has a score of " << p6.GetScore() << ". " << endl;
	}
	else
	{
		cout << "Item not found";
	}

	return 0;
}