#include <iostream>

using namespace std;

template <typename T>
void PrintBinNumberf(T);
void PrintBin(char);

int main()
{
	int a;
	char b;
	float c;
	float d = 15.3;
	long e;
	cout << "input: ";
	PrintBinNumberf(d);
	system("pause");
	return 0;
}

template<typename T>
void PrintBinNumberf(const T arg)
{
	char *pointer = (char*)&arg;

	for (int i = 0; i < sizeof(T); i++, pointer++)
	{
		PrintBin(*pointer);
	}
	cout << endl;
};

void PrintBin(char number)
{
	for (int i = 0; i < 8; i++)
	{
		cout << (number & 0x01);
		number >>= 1;
	}
}

void menu() {
	short int choice;
	cout << "==============================" << endl
		<< "+++++++++++++MENU++++++++++++++"
		<< "==============================" << endl
		<< "|| " << "1 - int" << endl
		<< "|| " << "2 - char" << endl
		<< "|| " << "3 - float" << endl
		<< "|| " << "4 - double" << endl
		<< "|| " << "5 - long" << endl
		<< "==============================" << endl;
	cout << "you choice: ";
	switch (choice)
	{
	default:
		break;
	}

}