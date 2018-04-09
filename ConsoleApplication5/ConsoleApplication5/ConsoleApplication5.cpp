// ConsoleApplication5.cpp: Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "stdafx.h"
#include <string>
#include <iostream>
#include <fstream>

using namespace std;


int hashIt(string key, int hashLength)
{
	int hash = 0, a = 31416, b = 27183;
	for (unsigned int i = 0; i < key.length(); i++)
	{
		hash = (a * hash + key[i]) % hashLength;
		a = a * b % (hashLength - 1);
	}

	return hash;
}

class storage
{
public:
	string date[30];
	double open[30];
	double high[30];
	double low[30];
	double close[30];
	double adjClose[30];
	int volume[30];
	bool empty = true;
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
	class tableAcroFromName* toName = NULL;
	bool deleted = false;
	storage data;
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
	
	*searchSpot = (hashIt(nameOrAcro, hashLength) + (increment*increment));

	if (*searchSpot >= hashLength) {     //hashLength
		*searchSpot %= hashLength;		//hashLength
	}

	if (increment > (hashLength * 10)) {                     //hashLength related
		cout << "error: search timeout; hashtable is too full" << endl;
		*searchEnd = true;
	}

}

void importData(class tableForData **selectedStock) {
	cout << "In order to import for a stock, please give path and filename to csv for \""
		<< (*selectedStock)->name << "\" stock." << endl;

	string fileDirectory;
	cin >> fileDirectory;

	ifstream file(fileDirectory + ".csv");
	string input = "";
	string temp[7];

	if (!file.is_open()) cerr << "ERROR: File not opened" << endl;
	


	int lineNumber = 0;
	if (file.is_open()) {
		while (getline(file, input)) {
			lineNumber++;
			if (lineNumber >= 1) {
				for (int i = 0; i < 30 && file.good(); i++) {
					for (int c = 0; c < 6; c++) {
						getline(file, temp[c], ',');
					}
					getline(file, temp[6], '\n');					
					(*selectedStock)->data.date[i] = temp[0];					
					(*selectedStock)->data.open[i] = stof(temp[1]);
					(*selectedStock)->data.high[i] = stof(temp[2]);
					(*selectedStock)->data.low[i] = stof(temp[3]);
					(*selectedStock)->data.close[i] = stof(temp[4]);
					(*selectedStock)->data.adjClose[i] = stof(temp[5]);
					(*selectedStock)->data.volume[i] = stoi(temp[6]);
					(*selectedStock)->data.empty = false;
					
				}
			}
		}

	}
	file.close();

	//To test - a print

	for (int i = 0; i < 30 && (*selectedStock)->data.date[i] != ""; i++) {
		cout << i << ": " << endl;
		cout << (*selectedStock)->data.date[i] << ";  "
			<< (*selectedStock)->data.open[i] << ";  "
			<< (*selectedStock)->data.high[i] << ";  "
			<< (*selectedStock)->data.low[i] << ";  "
			<< (*selectedStock)->data.close[i] << ";  "
			<< (*selectedStock)->data.adjClose[i] << ";  "
			<< (*selectedStock)->data.volume[i] << ";  "
			<< (*selectedStock)->data.empty << endl;

	}
	
}



void add(string name, string acronym, string sin, int hashLength, tableForData **dataTable, tableForData **selectedStock, tableAcroFromName **acroNameTable) {
	int increment;
	bool searchEnd;
	int searchSpot;

	for (int i = 0; i<2; i++) {

		increment = 0;
		searchEnd = false;

		if (name == "back" || acronym == "back" || sin == "back") {
			searchEnd = true;
		}

		while (searchEnd == false) {
			if (i == 0) {
				searchCheck(acronym, hashLength, increment, &searchSpot, &searchEnd);

				if ((dataTable[searchSpot])->deleted == true || (dataTable[searchSpot])->acronym == "") {
					cout << "test: spot found at position ";
					cout << searchSpot << endl;
					(dataTable[searchSpot])->deleted = false;
					(dataTable[searchSpot])->acronym = acronym;
					(dataTable[searchSpot])->name = name;
					(dataTable[searchSpot])->sin = sin;
					selectedStock = &dataTable[searchSpot];
					searchEnd = true;
				}
				else if ((dataTable[searchSpot])->acronym == acronym) {
					cout << "\"" << acronym << "\" already exists" << endl;
					searchEnd = true;
				}
				else {
					cout << "test: spot NOT found" << endl;
				}
			}
			else {
				searchCheck(name, hashLength, increment, &searchSpot, &searchEnd);

				if ((acroNameTable[searchSpot])->deleted == true || (acroNameTable[searchSpot])->name == "") {
					cout << "test: spot found at position ";
					cout << searchSpot << endl;
					(acroNameTable[searchSpot])->deleted = false;
					(acroNameTable[searchSpot])->name = name;
					(acroNameTable[searchSpot])->toAcro = *selectedStock;
					(acroNameTable[searchSpot])->toAcro->toName = acroNameTable[searchSpot];
					searchEnd = true;
				}
				else if ((acroNameTable[searchSpot])->name == name) {
					cout << "\"" << acronym << "\" already exists" << endl;
					searchEnd = true;
				}
				else {
					cout << "test: spot NOT found" << endl;
				}
			}

			increment++;
		}

	}
}


int main()
{
	const int hashLength = 11;
	string acronym;
	string name;
	string sin;
	tableForData dataTable[hashLength];  //hashLength
	tableAcroFromName acroNameTable[hashLength];  //hashLength
	string action;
	string selectOption;
	int increment;
	int searchSpot;
	tableForData* selectedStock = NULL;
	bool searchEnd = false;
	
	cout << "Welcome to Stockmanager-" << endl;
	cout << "Type \"back\" to return to main menu." << endl << endl;

	while (action != "9") {
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

			cout << "ADD: Enter stock name: ";
			cin >> name;
			if (name!="back") {
				cout << "Enter stock acronym: ";
				cin >> acronym;
				if (acronym != "back") {
					cout << "Enter stock SIN: ";
					cin >> sin;
				}
			}

			tableForData * test = &(dataTable[0]);
			tableForData ** test2 = &test;
			tableAcroFromName * test3 = &(acroNameTable[0]);
			tableAcroFromName ** test4 = &test3;
			tableForData ** test5 = &selectedStock;

			add(name, acronym, sin, hashLength, test2, test5, test4);

			/*for (int i = 0; i<2; i++) {

				increment = 0;
				searchEnd = false;

				if (name == "back" || acronym == "back" || sin == "back") {
					searchEnd = true;
				}

				while (searchEnd == false) {
					if(i==0) {
						searchCheck(acronym, hashLength, increment, &searchSpot, &searchEnd);

						if (dataTable[searchSpot].deleted == true || dataTable[searchSpot].acronym == "") {
							cout << "test: spot found at position ";
							cout << searchSpot << endl;
							dataTable[searchSpot].deleted = false;
							dataTable[searchSpot].acronym = acronym;
							dataTable[searchSpot].name = name;
							dataTable[searchSpot].sin = sin;
							selectedStock = &dataTable[searchSpot];
							searchEnd = true;
						}
						else if (dataTable[searchSpot].acronym == acronym) {
							cout << "\"" << acronym << "\" already exists" << endl;
							searchEnd = true;
						}
						else {
							cout << "test: spot NOT found" << endl;
						}
					}
					else {
						searchCheck(name, hashLength, increment, &searchSpot, &searchEnd);

						if (acroNameTable[searchSpot].deleted == true || acroNameTable[searchSpot].name == "") {
							cout << "test: spot found at position ";
							cout << searchSpot << endl;
							acroNameTable[searchSpot].deleted = false;
							acroNameTable[searchSpot].name = name;
							acroNameTable[searchSpot].toAcro = selectedStock;
							acroNameTable[searchSpot].toAcro->toName = &acroNameTable[searchSpot];
							searchEnd = true;
						}
						else if (acroNameTable[searchSpot].name == name) {
							cout << "\"" << acronym << "\" already exists" << endl;
							searchEnd = true;
						}
						else {
							cout << "test: spot NOT found" << endl;
						}
					}
					
					increment++;
				}

			}*/

			
		}


		else if (action == "2") {

			//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!kopierter code!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

			name = "";
			acronym = "";
			cout << "DEL: What information would you like to enter?" << endl;
			cout << "1: Name" << endl;
			cout << "2: Acronym" << endl;
			cout << "Enter digit: ";
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

					//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!kopierter code!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

					increment = 0;
					searchEnd = false;

					if (acronym == "back") {
						searchEnd = true;
					}

					while (searchEnd == false) {
						searchCheck(name, hashLength, increment, &searchSpot, &searchEnd);           

						if (acroNameTable[searchSpot].deleted == false) {
							if (acroNameTable[searchSpot].name == "") {
								cout << "\"" << name << "\" not found" << endl;
								searchEnd = true;
							}
							else if (acroNameTable[searchSpot].name == name) {
								cout << "test: spot found at position " << searchSpot << endl;
								acroNameTable[searchSpot].deleted = true;
								acroNameTable[searchSpot].toAcro->deleted = true;
								cout << "stock \"" << acroNameTable[searchSpot].name << "\" deleted" << endl;
								searchEnd = true;
							}
						}

						increment++;
					}

				}
				else if (selectOption == "2") {
					cout << "Enter stock acronym: ";
					cin >> acronym;

					//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!kopierter code!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

					increment = 0;
					searchEnd = false;

					if (acronym == "back") {
						searchEnd = true;
					}

					while (searchEnd == false) {
						searchCheck(acronym, hashLength, increment, &searchSpot, &searchEnd);

						if (dataTable[searchSpot].deleted == false) {
							if (dataTable[searchSpot].acronym == "") {
								cout << "\"" << acronym << "\" not found" << endl;
								searchEnd = true;
							}
							else if (dataTable[searchSpot].acronym == acronym) {
								cout << "test: spot found at position " << searchSpot << endl;
								dataTable[searchSpot].deleted = true; 
								dataTable[searchSpot].toName->deleted = true;
								cout << "stock \"" << dataTable[searchSpot].name << "\" deleted" << endl;
								searchEnd = true;
							}
						}

						increment++;
					}
				}
			}
	

		}


		else if (action == "3") {
			if (selectedStock != NULL) {
				importData(&selectedStock);
			}
			else {
				cout << "IMPORT: No stock selected. Please use SEARCH to select stock" << endl;
			}
		}


		else if (action == "4") {
			name = "";
			acronym = "";
			cout <<"SEARCH: What information would you like to enter?" << endl;
			cout << "1: Name" << endl;
			cout << "2: Acronym" << endl;
			cout << "Enter digit: ";
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


					//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!kopierter code!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

					increment = 0;
					searchEnd = false;

					if (name == "back") {
						searchEnd = true;
					}

					while (searchEnd == false) {
						cout << "tick" << endl;

						searchCheck(name, hashLength, increment, &searchSpot, &searchEnd);

						if (acroNameTable[searchSpot].deleted == false) {
							if (acroNameTable[searchSpot].name == "") {
								cout << "\"" << name << "\" not found" << endl;
								searchEnd = true;
							}
							else if (acroNameTable[searchSpot].name == name) {
								cout << "test: spot found at position ";
								cout << searchSpot << endl;
								cout << "name is \"" << acroNameTable[searchSpot].toAcro->name << "\"" << endl;
								cout << "acronym is \"" << acroNameTable[searchSpot].toAcro->acronym << "\"" << endl;
								cout << "SIN is \"" << acroNameTable[searchSpot].toAcro->sin << "\"" << endl;
								selectedStock = acroNameTable[searchSpot].toAcro;                                 
								searchEnd = true;
							}
						}
						increment++;
					}


				}

				else if (selectOption == "2") {
					cout << "Enter stock acronym: ";
					cin >> acronym;
				

					//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!kopierter code!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

					increment = 0;
					searchEnd = false;

					if (acronym == "back") {
						searchEnd = true;
					}

					while (searchEnd == false) {
						cout << "tick" << endl;

						searchCheck(acronym, hashLength, increment, &searchSpot, &searchEnd);

						if (dataTable[searchSpot].deleted == false) {
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
								selectedStock = selectedStock = &dataTable[searchSpot];
								searchEnd = true;
							}
						}

						increment++;
					}
				}
			}

		}


		else if (action == "5") {
			if (selectedStock != NULL) {
				cout << "Plot \"" << selectedStock->name << "\"?" << endl;
				cout << "Not yet implemented..." << endl;
			}
			else {
				cout << "No stock selected. Please use SEARCH to select stock" << endl;
			}
		}


		else if (action == "6") {
			cout << "SAVE: Not yet implemented..." << endl;
		}


		else if (action == "7") {
			cout << "LOAD: Not yet implemented..." << endl;
		}


		else if (action == "8") {
			tableForData tempTableData[hashLength];
			tableAcroFromName tempTableAcroName[hashLength];

			for (int i = 0; i < hashLength; i++) {
				tempTableData[i] = dataTable[i];
				tempTableAcroName[i] = acroNameTable[i];

				dataTable[i].acronym = "";
				dataTable[i].name = "";
				dataTable[i].sin = "";
				dataTable[i].toName = NULL;
				dataTable[i].deleted = false;
				acroNameTable[i].name = "";
				acroNameTable[i].toAcro = NULL;
				acroNameTable[i].deleted = false;
			}
			
			
			for (int i=0; i < hashLength; i++) {                       //enter data into temporary tables
				if (tempTableData[i].deleted != true && tempTableData[i].acronym != "") {
					acronym = tempTableData[i].acronym;
					name = tempTableData[i].name;
					sin = tempTableData[i].sin;


					//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!kopierter code!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

					for (int i = 0; i<2; i++) {

						increment = 0;
						searchEnd = false;

						if (name == "back" || acronym == "back" || sin == "back") {
							searchEnd = true;
						}

						while (searchEnd == false) {
							if (i == 0) {
								searchCheck(acronym, hashLength, increment, &searchSpot, &searchEnd);

								if (dataTable[searchSpot].deleted == true || dataTable[searchSpot].acronym == "") {
									cout << "test: spot found at position ";
									cout << searchSpot << endl;
									dataTable[searchSpot].deleted = false;
									dataTable[searchSpot].acronym = acronym;
									dataTable[searchSpot].name = name;
									dataTable[searchSpot].sin = sin;
									selectedStock = &dataTable[searchSpot];
									searchEnd = true;
								}
								else if (dataTable[searchSpot].acronym == acronym) {
									cout << "\"" << acronym << "\" already exists" << endl;
									searchEnd = true;
								}
								else {
									cout << "test: spot NOT found" << endl;
								}
							}
							else {
								searchCheck(name, hashLength, increment, &searchSpot, &searchEnd);

								if (acroNameTable[searchSpot].deleted == true || acroNameTable[searchSpot].name == "") {
									cout << "test: spot found at position ";
									cout << searchSpot << endl;
									acroNameTable[searchSpot].deleted = false;
									acroNameTable[searchSpot].name = name;
									acroNameTable[searchSpot].toAcro = selectedStock;
									acroNameTable[searchSpot].toAcro->toName = &acroNameTable[searchSpot];
									searchEnd = true;
								}
								else if (acroNameTable[searchSpot].name == name) {
									cout << "\"" << acronym << "\" already exists" << endl;
									searchEnd = true;
								}
								else {
									cout << "test: spot NOT found" << endl;
								}
							}

							increment++;
						}

					}



				}	
			}

			cout << "CLEANUP: Undeleted values have been reorganized." << endl;
		}
	}
	
	return 0;
	
	

    
}

