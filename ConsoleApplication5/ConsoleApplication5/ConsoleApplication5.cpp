// ConsoleApplication5.cpp: Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "stdafx.h"
#include <string>
#include <iostream>
#include <fstream>

using namespace std;


int hashIt(string key, int hashLength) //appropriate hash for strings
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

	if (increment > (hashLength * 1000)) {                     //hashLength related
		cerr << "error: search timeout; hashtable might be too full" << endl;
		*searchEnd = true;
	}

}

int parseDate(const std::string &input) { //Gives us two nice comparable numbers
	int month;
	int day;
	int year;
	if (sscanf_s(input.c_str(), "%d/%d/%d", &month, &day, &year) != 3) {
		return NULL;
	}
	else {
		// check values to avoid int overflow if you can be bothered
		return 10000 * year + 100 * month + day;
	}
}

void importData(class tableForData **selectedStock) {
	cout << "In order to import for a stock, please give path and filename to csv for \""
		<< (*selectedStock)->name << "\" stock." << endl;

	string fileDirectory;
	cin >> fileDirectory; //file directory gets read

	ifstream file(fileDirectory + ".csv"); //adding .csv to open the file
	string input = "";
	string temp[7];

	if (!file.is_open()) cerr << "ERROR: File not opened" << endl; //error if file cant open



	int lineNumber = 0;
	if (file.is_open()) {
		while (getline(file, input)) {
			lineNumber++; //line number is important cause first line of csv file is unimportant
			if (lineNumber >= 1) {
				bool newDataChecker = true;
				//Parse input makes the date string to a number with structure yyyymmdd so it is nice to compare
				int yearNew = parseDate(input); 
				int yearOld = parseDate((*selectedStock)->data.date[0]);

				//This checks if the data is actually new data 
				if (yearNew > yearOld || (*selectedStock)->data.date[0] == "") { bool newDataChecker = true; } 
				else { cerr << "No new data given!" << endl; return; }

				//Now reading the files
				for (int i = 0; i < 30 && file.good() && newDataChecker == true; i++) {
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

}


void plot(class tableForData **selectedStock) {
	int lowest = (*selectedStock)->data.close[0];
	int highest = (*selectedStock)->data.close[0];
	char out[50][30] = {};

	//For loops so the graph can be plotted in the right angle
	for (int i = 1; i < 30 && (*selectedStock)->data.close[i] != NULL; i++) {
		if ((*selectedStock)->data.close[i] < lowest && (*selectedStock)->data.close[i] >= 0) {
			lowest = (*selectedStock)->data.close[i];
		}
		else if ((*selectedStock)->data.close[i] > highest && (*selectedStock)->data.close[i] >= 0) {
			highest = (*selectedStock)->data.close[i];
		}
	}
	for (int i = 0; i < 30 && (*selectedStock)->data.close[i] != NULL; i++) {
		int j;
		float n;
		for (j = lowest; j < (*selectedStock)->data.close[i]; j++) {
			out[(j - lowest)][i] = '#';
		}
	}
	//Doesnt print a '#' for every +1, so it doesnt take so much space
	for (int y = highest - lowest; y >= 0; y--) {
		cout << lowest + y;
		if (lowest + y <= 999) {
			cout << " ";
		}
		if (lowest + y <= 99) {
			cout << " ";
		}
		if (lowest + y <= 9) {
			cout << " ";
		}

		for (int x = 0; x < 30; x++) {
			cout << out[y][x];
		}
		cout << endl;
	}
}



int main()
{
	const int hashLength = 1200;
	string acronym;
	string name;
	string sin;
	static tableForData dataTable[hashLength];  //hashLength
	static tableAcroFromName acroNameTable[hashLength];  //hashLength
	string action;
	string selectOption;
	int increment;
	int searchSpot;
	tableForData* selectedStock = NULL;
	bool searchEnd = false;

	cout << "Welcome to Stockoverflow" << endl;
	cout << "Type \"back\" to return to main menu." << endl << endl;

	//Menu
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

		//Input must be between 1 and 9
		if (action < "1" || action > "9") {
			cout << "" << endl;
			cout << "Invalid action digit" << endl;
			cout << "" << endl;
		}

		//Add
		else if (action == "1") {
			name = "";
			acronym = "";
			sin = "";

			//getting var-inputs
			cout << "ADD: Enter stock name: ";
			cin >> name;
			if (name != "back") {
				cout << "Enter stock acronym: ";
				cin >> acronym;
				if (acronym != "back") { //back is always option to go to point before
					cout << "Enter stock SIN: ";
					cin >> sin;
				}
			}

			for (int i = 0; i < 2; i++) { 

				increment = 0;
				searchEnd = false;

				if (name == "back" || acronym == "back" || sin == "back") { //back is always option to go to point before
					searchEnd = true;
				}

				//Putting all stuff in the hash tables
				while (searchEnd == false) {
					if (i == 0) {
						searchCheck(acronym, hashLength, increment, &searchSpot, &searchEnd); //finding the search spot and potential overflow error

						//Checking if the dataTable deleted flag is set or the field is empty
						if (dataTable[searchSpot].deleted == true || dataTable[searchSpot].acronym == "") { 
							dataTable[searchSpot].deleted = false;
							dataTable[searchSpot].acronym = acronym;
							dataTable[searchSpot].name = name;
							dataTable[searchSpot].sin = sin;
							selectedStock = &dataTable[searchSpot];
							searchEnd = true;
						}
						else if (dataTable[searchSpot].acronym == acronym) { //if existent => end
							cout << "\"" << acronym << "\" already exists" << endl;
							i++;
							searchEnd = true;
						}
					}
					else { 
						searchCheck(name, hashLength, increment, &searchSpot, &searchEnd);

						//Checking if the dataTable deleted flag is set or the field is empty
						if (acroNameTable[searchSpot].deleted == true || acroNameTable[searchSpot].name == "") {
							acroNameTable[searchSpot].deleted = false;
							acroNameTable[searchSpot].name = name;
							acroNameTable[searchSpot].toAcro = selectedStock;
							acroNameTable[searchSpot].toAcro->toName = &acroNameTable[searchSpot];
							searchEnd = true;
						}
						else if (acroNameTable[searchSpot].name == name) { //if existent => end
							cout << "\"" << name << "\" already exists" << endl;
							searchEnd = true;
						}
					}

					increment++;
				}

			}


		}

		//DELETE
		else if (action == "2") {
			
			name = "";
			acronym = "";
			//Menu for searching with name or acronym
			cout << "DEL: What information would you like to enter?" << endl;
			cout << "1: Name" << endl;
			cout << "2: Acronym" << endl;
			cout << "Enter digit: ";
			cin >> selectOption;

			//if not 1 or 2 its invalid
			if (selectOption != "1" && selectOption != "2") {
				if (selectOption != "back") {
					cout << "" << endl;
					cout << "Invalid input" << endl;
					cout << "" << endl;
				}
			}
			else { 
				if (selectOption == "1") { //1 for name
					cout << "Enter stock name: ";
					cin >> name;


					increment = 0;
					searchEnd = false;

					if (acronym == "back") {
						searchEnd = true;
					}

					//deleting
					while (searchEnd == false) {
						searchCheck(name, hashLength, increment, &searchSpot, &searchEnd);

						if (acroNameTable[searchSpot].deleted == false) {
							if (acroNameTable[searchSpot].name == "") {
								cout << "\"" << name << "\" not found" << endl;
								searchEnd = true;
							}
							else if (acroNameTable[searchSpot].name == name) {
								acroNameTable[searchSpot].deleted = true;
								acroNameTable[searchSpot].toAcro->deleted = true;
								cout << "stock \"" << acroNameTable[searchSpot].name << "\" deleted" << endl;
								searchEnd = true;
							}
						}

						increment++;
					}

				}
				else if (selectOption == "2") { // 2 for acronym
					cout << "Enter stock acronym: ";
					cin >> acronym;

					increment = 0;
					searchEnd = false;

					if (acronym == "back") {
						searchEnd = true;
					}

					//deleting
					while (searchEnd == false) {
						searchCheck(acronym, hashLength, increment, &searchSpot, &searchEnd);

						if (dataTable[searchSpot].deleted == false) {
							if (dataTable[searchSpot].acronym == "") {
								cout << "\"" << acronym << "\" not found" << endl;
								searchEnd = true;
							}
							else if (dataTable[searchSpot].acronym == acronym) {
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

		//Import
		else if (action == "3") {
			if (selectedStock != NULL) { //if no stock is selected (default when added/searched) you cant import
				importData(&selectedStock); //import function
			}
			else {
				cout << "IMPORT: No stock selected. Please use SEARCH to select stock" << endl;
			}
		}

		//Searching
		else if (action == "4") {
			name = "";
			acronym = "";
			//Menu for searching with name or acronym
			cout << "SEARCH: What information would you like to enter?" << endl;
			cout << "1: Name" << endl;
			cout << "2: Acronym" << endl;
			cout << "Enter digit: ";
			cin >> selectOption;

			//not valid if there is no 1 or 2
			if (selectOption != "1" && selectOption != "2") {
				if (selectOption != "back") {
					cout << "" << endl;
					cout << "Invalid input" << endl;
					cout << "" << endl;
				}
			}
			else { // 1 for name
				if (selectOption == "1") {
					cout << "Enter stock name: ";
					cin >> name;


					increment = 0;
					searchEnd = false;

					if (name == "back") {
						searchEnd = true;
					}

					//finding
					while (searchEnd == false) {
						searchCheck(name, hashLength, increment, &searchSpot, &searchEnd);

						if (acroNameTable[searchSpot].deleted == false) {
							if (acroNameTable[searchSpot].name == "") {
								cout << "\"" << name << "\" not found" << endl;
								searchEnd = true;
							}
							else if (acroNameTable[searchSpot].name == name) {
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

				else if (selectOption == "2") { // 2 for acronym
					cout << "Enter stock acronym: ";
					cin >> acronym;


					increment = 0;
					searchEnd = false;

					if (acronym == "back") {
						searchEnd = true;
					}

					//finding
					while (searchEnd == false) {

						searchCheck(acronym, hashLength, increment, &searchSpot, &searchEnd);

						if (dataTable[searchSpot].deleted == false) {
							if (dataTable[searchSpot].acronym == "") {
								cout << "\"" << acronym << "\" not found" << endl;
								searchEnd = true;
							}
							else if (dataTable[searchSpot].acronym == acronym) {
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

		//PLOT
		else if (action == "5") {
			if (selectedStock != NULL) { //if no stock is selected (default when added/searched) you cant import
				plot(&selectedStock);
			}
			else {
				cout << "No stock selected. Please use SEARCH to select stock" << endl; 
			}
		}


		else if (action == "6") {

			//Asking for the later filename
			cout << "How do you want to name your file?" << endl;
			string fileName;
			cin >> fileName;

			ofstream myfile;
			myfile.open(fileName + ".txt"); //Saved as text-file so adding .txt
			for (int i = 0; i < hashLength; i++) { // i<hashLength so all data gets iterated
				if (dataTable[i].data.date[0] != "" && dataTable[i].deleted == false) { //if no data is set, or the deleted flag is set, we dont want to store the data
					//writing the acronym, name and sin in file
					myfile << dataTable[i].acronym << endl;
					myfile << dataTable[i].name << endl;
					myfile << dataTable[i].sin << endl;
					//iterating through the data part
					for (int j = 0; j < 30; j++) {
						if (dataTable[i].data.date[j] != "") {
					
							myfile << dataTable[i].data.date[j] << ",";
							myfile << dataTable[i].data.open[j] << ",";
							myfile << dataTable[i].data.high[j] << ",";
							myfile << dataTable[i].data.low[j] << ",";
							myfile << dataTable[i].data.close[j] << ",";
							myfile << dataTable[i].data.adjClose[j] << ",";
							myfile << dataTable[i].data.volume[j] << endl;

						}
					}
					myfile << "stockended," << endl; //"stockend," gets added for the later import method
				}
			}
			myfile << "file_end"; //also for the import method, we want to know if the file has ended
			myfile.close();
			cout << "File saved." << endl;
		}

		//Load
		else if (action == "7") {

			//Asking for the file we want to load
			cout << "Name the path and file you want to load, please." << endl;

			string fileDirectory;
			cin >> fileDirectory;

			ifstream file(fileDirectory + ".txt"); //adding .txt because the save method makes txt files
			string input = "";
			string temp[7];

			if (!file.is_open()) cerr << "ERROR: File not opened" << endl; // if it cant be oppened error

		newStockReached: //Altough spaghetti is not good, we needed it here :( 
			int lineNumber = 0;
			if (file.is_open()) {
				while (lineNumber < 36) { //Line number because the first 3 parsing-elements differ from the rest 36 because we wanted to be safe(max data 30 + sin+acro+name + file_end + stockended
					if (lineNumber < 2) { //The first three elements differ (acronym, name, sin)
						getline(file, acronym, '\n');
						if (acronym == "file_end") { //Checking if the file has ended
							break;
						}
						getline(file, name, '\n');
						getline(file, sin, '\n');

						//adding function sadly not in a function :( 
						for (int i = 0; i < 2; i++) {

							increment = 0;
							searchEnd = false;

							if (name == "back" || acronym == "back" || sin == "back") {
								searchEnd = true;
							}

							while (searchEnd == false) {
								if (i == 0) {
									searchCheck(acronym, hashLength, increment, &searchSpot, &searchEnd);

									if (dataTable[searchSpot].deleted == true || dataTable[searchSpot].acronym == "") {
										
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
								}
								else {
									searchCheck(name, hashLength, increment, &searchSpot, &searchEnd);

									if (acroNameTable[searchSpot].deleted == true || acroNameTable[searchSpot].name == "") {
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
								}
								increment++;
							}
						}
						lineNumber = 2; //setting linenumber to 2 because it is the 3rd line (0-2)
					}
					else { //if the line number is higher we want to store the data

						//iterating through data
						for (int i = 0; i < 30 && file.good(); i++) {
							for (int c = 0; c < 6; c++) {
								getline(file, temp[c], ',');
								if (temp[c] == "stockended") { //check if we face a stockended, if so we go back to the anchor top
									getline(file, temp[c], '\n'); //needed to get the newline out of the way to properly read
									goto newStockReached; //line nubmer gets reset on top
								}
							}
							//last line is not seperated by ',' thats why it has to be handled extra
							getline(file, temp[6], '\n');
							//if (temp[6] == "stockended") { goto newStockReached; }
							//saving
							selectedStock->data.date[i] = temp[0];
							selectedStock->data.open[i] = stof(temp[1]);
							selectedStock->data.high[i] = stof(temp[2]);
							selectedStock->data.low[i] = stof(temp[3]);
							selectedStock->data.close[i] = stof(temp[4]);
							selectedStock->data.adjClose[i] = stof(temp[5]);
							selectedStock->data.volume[i] = stoi(temp[6]);
							selectedStock->data.empty = false;
							lineNumber++;

						}
					}
					//lineNumber = 0;
				}
				file.close();
			}
			cout << "File loaded." << endl;
		}

		// a smart cleanuper we thought could be useful =)
		else if (action == "8") {
			cout << "CLEANUP: Undeleted values have been reorganized." << endl;

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

			for (int i = 0; i < hashLength; i++) {
				if (tempTableData[i].deleted != true && tempTableData[i].acronym != "") {
					acronym = tempTableData[i].acronym;
					name = tempTableData[i].name;
					sin = tempTableData[i].sin;


					for (int i = 0; i < 2; i++) {

						increment = 0;
						searchEnd = false;

						if (name == "back" || acronym == "back" || sin == "back") {
							searchEnd = true;
						}

						while (searchEnd == false) {
							if (i == 0) {
								searchCheck(acronym, hashLength, increment, &searchSpot, &searchEnd);

								if (dataTable[searchSpot].deleted == true || dataTable[searchSpot].acronym == "") {
									dataTable[searchSpot].deleted = false;
									dataTable[searchSpot].acronym = acronym;
									dataTable[searchSpot].name = name;
									dataTable[searchSpot].sin = sin;
									selectedStock = &dataTable[searchSpot];
									searchEnd = true;
								}
								else if (dataTable[searchSpot].acronym == acronym) {
									searchEnd = true;
								}
							}
							else {
								searchCheck(name, hashLength, increment, &searchSpot, &searchEnd);
								if (acroNameTable[searchSpot].deleted == true || acroNameTable[searchSpot].name == "") {
									acroNameTable[searchSpot].deleted = false;
									acroNameTable[searchSpot].name = name;
									acroNameTable[searchSpot].toAcro = selectedStock;
									acroNameTable[searchSpot].toAcro->toName = &acroNameTable[searchSpot];
									searchEnd = true;
								}
								else if (acroNameTable[searchSpot].name == name) {
									searchEnd = true;
								}
							}
							increment++;
						}

					}

				}

			}

		}

	}
	return 0;

}