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

void hashTable(int hash)
{

}

class item
{
	string key;
	int value;
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
	string lol = "haha";
	std::cout << hashTryIt(lol) << endl;
	printf("%d", hashTryIt(lol));


	

    return 0;
}

