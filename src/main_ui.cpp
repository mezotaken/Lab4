#include "polynom.h"
using namespace std;

char main_menu()
{
	system("cls");
	char res;
	cout << "1. \n";
	cout << "2. \n";
	cout << "3. Exit\n\n";

	cout << "\n\n";
	cout << "Choose menu item: ";
	cin >> res;
	return res;
}

int main()
{
	char pmenu;
	do {
		pmenu = main_menu();

		switch (pmenu)
		{
		case '1':
		{
			system("cls");
			system("pause");
			break;
		}

		case '2':
		{
			system("cls");
			system("pause");
			break;
		}
		case '3': break;
		}
	} while (pmenu != '3');
	return 0;
}