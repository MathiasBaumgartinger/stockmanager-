// ConsoleApplication5.cpp: Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "stdafx.h"
#include <string>
#include <iostream>

using namespace std;

int hashTryIt(string acronym, int hashLength)
{
	int hash;
	int sum = 0;
	for (int i = 0; acronym[i] != '\0'; i++)
	{
		sum += acronym[i];
	}

	hash = sum % hashLength;           //hashLength

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

/*class itemName
{
public:
	string key = "";
	class storage* toData = NULL;
};

class itemAcronym
{
public:
	string key = "";
	class itemName* toName = NULL;
};*/

class tableForData {
public: 
	string acronym = "";
	string name = "";
	string sin = "";
	class storage* toData = NULL;
	bool deleted = false;
	//storage data;
private:

protected:

};


class tableAcroFromName {
public:
	string name = "";
	class tableForData* toAcro = NULL;
	bool deleted = false;
};


void searchCheck(string nameOrAcro, int hashLength, int increment, int *searchSpot, bool *searchEnd) {
	
	*searchSpot = (hashTryIt(nameOrAcro, hashLength) + (increment*increment));

	if (*searchSpot >= hashLength) {     //hashLength
		*searchSpot %= hashLength;		//hashLength
	}

	if (increment > (hashLength * 10)) {                     //hashLength related
		cout << "error: search timeout; hashtable is too full" << endl;
		*searchEnd = true;
	}

}


int main()
{
	string acronym;
	string name;
	string sin;
	tableForData dataTable[11];  //hashLength
	tableAcroFromName acroNameTable[11];  //hashLength
	int hashLength = 11;
	string action;
	string selectOption;
	int increment;
	int searchSpot;
	tableForData* acronymSpot;
	int selectedStock = -1;
	bool searchEnd = false;
	
	
	cout << "Welcome to Stockmanager-" << endl;
	cout << "Type \"back\" to return to main menu." << endl << endl;

	while (action != "8") {
		cout << endl;
		cout << "Please select an action:" << endl;
		cout << "1: ADD" << endl;
		cout << "2: DEL" << endl;
		cout << "3: IMPORT" << endl;
		cout << "4: SEARCH" << endl;
		cout << "5: PLOT" << endl;
		cout << "6: SAVE" << endl;
		cout << "7: LOAD" << endl;
		cout << "8: CLEANUP" << endl;
		cout << "9: QUIT" << endl;
		cout << "Enter digit: ";
		cin >> action;
		cout << endl;
		

		if (action < "1" || action > "9") {
			cout << "" << endl;
			cout << "Invalid action digit" << endl;
			cout << "" << endl;
		}


		else if (action == "1") {
			name = "";
			acronym = "";
			sin = "";

			cout << "Enter stock name: ";
			cin >> name;
			if (name!="back") {
				cout << "Enter stock acronym: ";
				cin >> acronym;
				if (acronym != "back") {
					cout << "Enter stock SIN: ";
					cin >> sin;
				}
			}

			increment = 0;
			searchEnd = false;

			if (name == "back" || acronym == "back" || sin == "back") {
				searchEnd = true;
			}

			while (searchEnd == false) {
				searchCheck(acronym, hashLength, increment, &searchSpot, &searchEnd);


				if (dataTable[searchSpot].deleted == true || dataTable[searchSpot].acronym == "") {
					cout << "test: spot found at position ";
					cout << searchSpot << endl;
					dataTable[searchSpot].deleted = false;
					dataTable[searchSpot].acronym = acronym;
					dataTable[searchSpot].name = name;
					dataTable[searchSpot].sin = sin;
					acronymSpot = &dataTable[searchSpot];
					selectedStock = searchSpot;
					searchEnd = true;
				}
				else if (dataTable[searchSpot].acronym == acronym) {
					cout << "\"" << acronym << "\" already exists" << endl;
					searchEnd = true;
				}
				else {
					cout << "test: spot NOT found" << endl;
				}
				increment++;
			}



			//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!kopierter code!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

			/*increment = 0;
			searchEnd = false;

			if (name == "back" || acronym == "back" || sin == "back") {
				searchEnd = true;
			}

			while (searchEnd == false) {
				searchSpot = (hashTryIt(name, hashLength) + (increment*increment));

				if (searchSpot >= hashLength) {     //hashLength
					searchSpot %= hashLength;		//hashLength
				}

				if (increment > (hashLength * 10)) {                     //hashLength related
					cout << "error: search timeout; hashtable is too full" << endl;
					searchEnd = true;
				}

				else if (acroNameTable[searchSpot].deleted == true || acroNameTable[searchSpot].name == "") {
					cout << "test: spot found at position ";
					cout << searchSpot << endl;
					acroNameTable[searchSpot].deleted = false;
					acroNameTable[searchSpot].name = name;
					acroNameTable[searchSpot].toAcro = acronymSpot;
					searchEnd = true;
				}*/
				/*else if (acroNameTable[searchSpot].name == name) {
					cout << "\"" << acronym << "\" already exists" << endl;
					searchEnd = true;
				}*/
				/*else {
					cout << "test: spot NOT found" << endl;
				}
				increment++;
			}*/


			//alter code bis ende action 1

			/*table[hashTryIt(acronym, hashLength)].arrayAcronym.key = acronym;
			table[hashTryIt(acronym, hashLength)].arrayAcronym.toName = &(table[hashTryIt(name, hashLength)].arrayName);
			table[hashTryIt(name, hashLength)].arrayName.key = name;
			storage storage; //sollte ja eigentlich erst zur laufzeit erstellt werden, 
							 //um speicher zu sparen
			table[hashTryIt(name, hashLength)].arrayName.toData = &storage;
			storage.high = 12.3914123;*/

			/*string test;
			cout << hashTryIt(test) << endl;
			int i = hashTryIt(test);*/

			/*cout << table[hashTryIt(acronym, hashLength)].arrayAcronym.toName->toData->high << endl;
			//cout << table.arrayAcronym[2].name << endl;*/
		}


		else if (action == "2") {
			name = "";
			acronym = "";
			cout << "Enter stock acronym: ";
			cin >> acronym;

			//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!kopierter code!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

			increment = 0;
			searchEnd = false;

			if (acronym == "back") {
				searchEnd = true;
			}

			while (searchEnd == false) {
				searchSpot = (hashTryIt(acronym, hashLength) + (increment*increment));

				if (searchSpot >= hashLength) {     //hashLength
					searchSpot %= hashLength;		//hashLength
				}

				if (increment > (hashLength * 10)) {                     //hashLength related
					cout << "error: search timeout; hashtable is too full" << endl;
					searchEnd = true;
				}

				else if (dataTable[searchSpot].deleted == false) {
					if (dataTable[searchSpot].acronym == "") {
						cout << "\"" << acronym << "\" not found" << endl;
						searchEnd = true;
					}
					else if (dataTable[searchSpot].acronym == acronym) {
						cout << "test: spot found at position " << searchSpot << endl;
						dataTable[searchSpot].deleted = true;
						cout << "stock \"" << dataTable[searchSpot].name << "\" deleted" << endl;
						searchEnd = true;
					}
				}

				increment++;
			}

		}


		else if (action == "3") {
			if (selectedStock >= 0 && selectedStock < hashLength) {
				cout << "Import data for \"" << dataTable[selectedStock].name << "\"?" << endl;
				cout << "Not yet implemented..." << endl;
			}
			else {
				cout << "No stock selected. Please use SEARCH to select stock" << endl;
			}
		}


		else if (action == "4") {
			name = "";
			acronym = "";
			cout <<"What information would you like to enter?" << endl;
			cout << "1: Name" << endl;
			cout << "2: Acronym" << endl;
			cout << "Enter digit:" << endl;
			cin >> selectOption;

			if (selectOption != "1" && selectOption != "2") {
				if (selectOption != "back") {
					cout << "" << endl;
					cout << "Invalid input" << endl;
					cout << "" << endl;
				}
			}
			else {
				if (selectOption == "1") {
					cout << "Enter stock name: ";
					cin >> name;



				}

				if (selectOption == "2") {
					cout << "Enter stock acronym: ";
					cin >> acronym;
				

					//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!kopierter code!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

					increment = 0;
					searchEnd = false;

					if (acronym == "back") {
						searchEnd = true;
					}

					while (searchEnd == false) {
						searchSpot = (hashTryIt(acronym, hashLength) + (increment*increment));

						if (searchSpot >= hashLength) {     //hashLength
							searchSpot %= hashLength;		//hashLength
						}

						if (increment > (hashLength * 10)) {                     //hashLength related
							cout << "error: search timeout; hashtable is too full" << endl;
							searchEnd = true;
						}

						else if (dataTable[searchSpot].deleted == false) {
							if (dataTable[searchSpot].acronym == "") {
								cout << "\"" << acronym << "\" not found" << endl;
								searchEnd = true;
							}
							else if (dataTable[searchSpot].acronym == acronym) {
								cout << "test: spot found at position ";
								cout << searchSpot << endl;
								cout << "name is \"" << dataTable[searchSpot].name << "\"" << endl;
								cout << "acronym is \"" << dataTable[searchSpot].acronym << "\"" << endl;
								cout << "SIN is \"" << dataTable[searchSpot].sin << "\"" << endl;
								selectedStock = searchSpot;
								searchEnd = true;
							}
						}

						increment++;
					}
				}
			}

		}


		else if (action == "5") {
			if (selectedStock >= 0 && selectedStock < hashLength) {
				cout << "Plot \"" << dataTable[selectedStock].name << "\"?" << endl;
				cout << "Not yet implemented..." << endl;
			}
			else {
				cout << "No stock selected. Please use SEARCH to select stock" << endl;
			}
		}


		else if (action == "8") {
			// clean up table by reentering all values
		}


		else if (action == "9") {
			break;
		}
	}
	
	return 0;
	
	

    
}

