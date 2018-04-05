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
	itemAcronym arrayAcronym;
	itemName arrayName;
	bool deleted = true;
	//storage data;
private:

protected:

};


int main()
{
	string acronym;
	string name;
	hashTable table[300];
	int action = 0;
	int increment;
	bool spot_found = false;
	
	cout << "Welcome to Stockmanager-" << endl;

	while (action != 8) {
		cout << "Please select an action:" << endl;
		cout << "1: ADD" << endl;
		cout << "2: DEL" << endl;
		cout << "3: IMPORT" << endl;
		cout << "4: SEARCH" << endl;
		cout << "5: PLOT" << endl;
		cout << "6: SAVE" << endl;
		cout << "7: LOAD" << endl;
		cout << "8: QUIT" << endl;
		cout << "Enter action digit: ";
		cin >> action;

		if (action == 1) {
			cout << "Enter stock acronym: ";
			cin >> acronym;
			cout << "Enter stock name: ";
			cin >> name;

			increment = 0;
			spot_found = false;

			while (spot_found == false) {
				if (table[hashTryIt(acronym) + (increment*increment)].deleted == false) {
					cout << "test: spot NOT found" << endl;
				}
				else {
					cout << "test: spot found" << endl;
					table[hashTryIt(acronym) + (increment*increment)].deleted = false;
					spot_found = true;
				}
				increment++;
			}


			table[hashTryIt(acronym)].arrayAcronym.key = acronym;
			table[hashTryIt(acronym)].arrayAcronym.toName = &(table[hashTryIt(name)].arrayName);
			table[hashTryIt(name)].arrayName.key = name;
			storage storage; //sollte ja eigentlich erst zur laufzeit erstellt werden, 
							 //um speicher zu sparen
			table[hashTryIt(name)].arrayName.toData = &storage;
			storage.high = 12.3914123;

			/*string test;
			cout << hashTryIt(test) << endl;
			int i = hashTryIt(test);*/

			cout << table[hashTryIt(acronym)].arrayAcronym.toName->toData->high << endl;
			//cout << table.arrayAcronym[2].name << endl;
		}
	}
	
	return 0;
	
	

    
}

