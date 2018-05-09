#include "ord_table.h"
#include "hash_table.h"
#include "unord_table.h"
#include "polynom.h"
#include <iostream>
using namespace std;

char menu()
{
	system("cls");
	char res;
	cout << "1. Exit\n";

	cout << "\n\n";
	cout << "Choose menu item: ";
	cin >> res;
	return res;
}

void main() {
	char pmenu;
	do {
		pmenu = menu();

		switch (pmenu)
		{
		case '1': break;
		}
	} while (pmenu != '1');
}