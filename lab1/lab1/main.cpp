#include <iostream>
#include <cstdlib>

using namespace std;

template <typename T>
void PrintBinNumberf(T);
void PrintBin(char);
void printLine(int);

int main()
{
	short int choice = 0;
	int a;
	bool isExit;
	char b;
	float c;
	double d ;
	long e;
	short int count=0;
	do
	{
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
		if (count >2)
		{
			count = 0;
			system("cls");
		}
		count++;
		isExit = 0;
		cout << "===============================" << endl
			<< "+++++++++++++MENU++++++++++++++" << endl
			<< "==============================" << endl
			<< "|| " << "1 - int" << endl
			<< "|| " << "2 - char" << endl
			<< "|| " << "3 - float" << endl
			<< "|| " << "4 - double" << endl
			<< "|| " << "5 - long" << endl
			<< "|| " << "0 - exit" << endl
			<< "==============================" << endl;
		cout << "you choice: ";
		cin >> choice;
		cout << "Input ";
		switch (choice)
		{
		case 1:
			cout << "int: ";
			cin >> a;
			PrintBinNumberf(a);

			break;
		case 2:
			cout << "char: ";
			cin >> b;
			PrintBinNumberf(b);
			break;
		case 3:
			cout << "float: ";
			cin >> c;
			PrintBinNumberf(c);
			break;
		case 4:
			cout << "double: ";
			cin >> d;
			PrintBinNumberf(d);
			break;
		case 5:
			cout << "long: ";
			cin >> e;
			PrintBinNumberf(e);
			break;
		case 0:
			isExit = 1;
			break;
		default:
			cout << "ERR: wrong choise" << endl;
			isExit = 1;
			break;
		}
	} while (!isExit);
	system("pause");
	return 0;
}

template<typename T>
void PrintBinNumberf(const T arg)
{
	char *pointer = (char*)&arg;
	cout << "size: " << sizeof(T) << "bytes"<<endl;
	printLine(sizeof(T));
	for (int i =0; i < sizeof(T) * 8 ; i++)
	{
		cout << i << "|";
		if (i<10)
		{
			cout << "0";
		}
	}
	printLine(sizeof(T));
	for (int i = 0; i < sizeof(T); i++, pointer++)
	{
		PrintBin(*pointer);
	}
	printLine(sizeof(T) );
	return;
};

void PrintBin(char number)
{
	for (int i = 0; i < 8; i++)
	{
		cout <<" "<< (number & 0x01)<<"|";
		number >>= 1;
	}
}

void printLine(int countByte)
{
	cout << endl;
	for (int i = countByte * 8; i >0; i--)
	{
		cout << "---";
	}
	cout << endl;
}