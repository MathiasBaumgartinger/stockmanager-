// ConsoleApplication5.cpp: Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "stdafx.h"
#include <string>
#include <iostream>

using namespace std;

int hashTryIt(string acronym)
{
	int hash;
	int sum = 0;
	for (int i = 0; acronym[i] != '\0'; i++)
	{
		sum += acronym[i];
	}

	hash = sum % 100;

	return hash;
}

class item
{
public:
	string key;
	string name;
};

class hashTable
{
public: 
	item storage[300];
private:

protected:

};


int main()
{
	string acronym;
	string name;
	hashTable table;
	

	cin >> acronym;
	cin >> name;
	table.storage[hashTryIt(acronym)].key = acronym;
	table.storage[hashTryIt(acronym)].name = name;
	
	
	
	cout << table.storage[2].name << endl;
	cin >> name;

    return 0;
}

