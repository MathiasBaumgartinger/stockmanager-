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

class storage
{
public:
	string date;
	float open;
	float high;
	float low;
	float close;
	float adjClose;
	float volume;
};

class itemName
{
public:
	string key;
	class storage* toData;
};

class itemAcronym
{
public:
	string key;
	class itemName* toName;
};

class hashTable
{
public: 
	itemAcronym arrayAcronym[300];
	itemName arrayName[300];
	//storage data;
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
	table.arrayAcronym[hashTryIt(acronym)].key = acronym;
	table.arrayAcronym[hashTryIt(acronym)].toName = &(table.arrayName[hashTryIt(name)]);
	table.arrayName[hashTryIt(name)].key = name;
	storage storage; //sollte ja eigentlich erst zur laufzeit erstellt werden, 
	//um speicher zu sparen
	table.arrayName[hashTryIt(name)].toData = &storage;
	storage.high = 12.3914123;

	/*string test;
	cout << hashTryIt(test) << endl;
	int i = hashTryIt(test);*/

	cout << table.arrayAcronym[hashTryIt(acronym)].toName->toData->high << endl;


	//cout << table.arrayAcronym[2].name << endl;
	

    return 0;
}

