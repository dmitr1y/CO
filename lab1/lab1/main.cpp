#include <iostream>
#include <conio.h>
#include <Windows.h>

using namespace std;
void PrintMenu(int);
template <typename T>
void PrintBinNumber(T);
void PrintBin(char);
void printLine(int);
bool ChoiseInputType(int );
int MenuPoint = 1;

int main() {
	system("color F0");
	int isExit = 1;//flag to exit program
	PrintMenu(1);//init menu
	char symbol = _getch();
	while (isExit && (symbol = _getch()))
	{
		system("cls");
		switch (symbol) {
		case 71:
			//home
			MenuPoint = 1;
			break;
		case 79:
			//end
			MenuPoint = 6;
			break;
		case 72:
			//up
			MenuPoint--;
			if (MenuPoint < 1)
				MenuPoint = 6;
			break;
		case 80:
			//down
			MenuPoint++;
			if (MenuPoint > 6)
				MenuPoint = 1;
			break;
		case 13:
			//enter
			isExit = ChoiseInputType(MenuPoint);
			break;
		default:
			break;
		}
		PrintMenu(MenuPoint);
	}
	return 0;
}

void PrintMenu(int number)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	cout << "===============================" << endl
		<< ":::::::::::::MENU::::::::::::::" << endl
		<< "===============================" << endl;
	switch (number)
	{
	case 1:
		SetConsoleTextAttribute(hConsole, (WORD)((8 << 4) | 15));
		cout << "-> " << "1 - int" << endl;
		SetConsoleTextAttribute(hConsole, (WORD)((15 << 4) | 0));
		cout << "|| " << "2 - char" << endl
			<< "|| " << "3 - float" << endl
			<< "|| " << "4 - double" << endl
			<< "|| " << "5 - long" << endl
			<< "|| " << "6 - exit" << endl;
		break;
	case 2:
		cout << "|| " << "1 - int" << endl;
		SetConsoleTextAttribute(hConsole, (WORD)((8 << 4) | 15));
		cout << "-> " << "2 - char" << endl;
		SetConsoleTextAttribute(hConsole, (WORD)((15 << 4) | 0));
		cout << "|| " << "3 - float" << endl
			<< "|| " << "4 - double" << endl
			<< "|| " << "5 - long" << endl
			<< "|| " << "6 - exit" << endl;
		break;
	case 3:
		cout << "|| " << "1 - int" << endl
			<< "|| " << "2 - char" << endl;
		SetConsoleTextAttribute(hConsole, (WORD)((8 << 4) | 15));
		cout << "-> " << "3 - float" << endl;
		SetConsoleTextAttribute(hConsole, (WORD)((15 << 4) | 0));
		cout << "|| " << "4 - double" << endl
			<< "|| " << "5 - long" << endl
			<< "|| " << "6 - exit" << endl;
		break;
	case 4:
		cout << "|| " << "1 - int" << endl
			<< "|| " << "2 - char" << endl
			<< "|| " << "3 - float" << endl;
		SetConsoleTextAttribute(hConsole, (WORD)((8 << 4) | 15));
		cout << "-> " << "4 - double" << endl;
		SetConsoleTextAttribute(hConsole, (WORD)((15 << 4) | 0));
		cout << "|| " << "5 - long" << endl
			<< "|| " << "6 - exit" << endl;
		break;
	case 5:
		cout << "|| " << "1 - int" << endl
			<< "|| " << "2 - char" << endl
			<< "|| " << "3 - float" << endl
			<< "|| " << "4 - double" << endl;
		SetConsoleTextAttribute(hConsole, (WORD)((8 << 4) | 15));
		cout << "-> " << "5 - long" << endl;
		SetConsoleTextAttribute(hConsole, (WORD)((15 << 4) | 0));
		cout << "|| " << "6 - exit" << endl;
		break;
	case 6:
		cout << "|| " << "1 - int" << endl
			<< "|| " << "2 - char" << endl
			<< "|| " << "3 - float" << endl
			<< "|| " << "4 - double" << endl
			<< "|| " << "5 - long" << endl;
		SetConsoleTextAttribute(hConsole, (WORD)((8 << 4) | 15));
		cout << "-> " << "6 - exit" << endl;
		SetConsoleTextAttribute(hConsole, (WORD)((15 << 4) | 0));
		break;
	default:
		break;
	}
	cout << "===============================" << endl;
}

bool ChoiseInputType(int param)
{
	int a;
	char b;
	float c;
	double d;
	long e;
	PrintMenu(MenuPoint);
	switch (param)
	{
	case 1:
		cout << "int: ";
		scanf("%d", &a);
		PrintBinNumber(a);
		break;
	case 2:
		cout << "char: ";
		scanf("%c", &b);
		PrintBinNumber(b);
		break;
	case 3:
		cout << "float: ";
		scanf("%f", &c);
		PrintBinNumber(c);
		break;
	case 4:
		cout << "double: ";
		scanf("%f", &d);
		PrintBinNumber(d);
		break;
	case 5:
		cout << "long: ";
		scanf("%d", &e);
		PrintBinNumber(e);
		break;
	case 6:
		//exit
		return false;
		break;
	default:
		break;
	}
	return true;
}

template<typename T>
void PrintBinNumber(const T arg)
{
	char *pointer = (char*)&arg;	
	cout << "size: " << sizeof(T) << "bytes" << endl;
	printLine(sizeof(T));
	for (int i = 0; i < sizeof(T) * 8; i++)
	{
		if (i<10)
			cout << "0";
		cout << i << "|";
	}
	printLine(sizeof(T));
	for (int i = 0; i < sizeof(T); i++, pointer++)
		PrintBin(*pointer);
	printLine(sizeof(T));
	return;
};

void PrintBin(char number)
{
	for (int i = 0; i < 8; i++)
	{
		cout << " " << (number & 0x01) << "|";
		number >>= 1;
	}
}

void printLine(int MenuPointByte)
{
	cout << endl;
	for (int i = MenuPointByte * 8; i > 0; i--)
		cout << "---";
	cout << endl;
}
