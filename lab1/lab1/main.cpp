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
	int isExit = 1;//flag to exit: 1->continue, 0->exit
//	system("cls");
	PrintMenu(1);//init menu
	char symbol;
	while ((isExit!=0) && ((symbol = _getch())!=0))
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
			try {
				isExit = ChoiseInputType(MenuPoint);
			}
			catch (int errCode) {
				printf("ERR(%d): Invalid input \n", errCode);
				while (getchar() != '\n'){}
				printf("Flush stdin\n");
			}
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
	printf("%s%s%s","===============================\n",
		":::::::::::::MENU::::::::::::::\n",
			"===============================\n");
	switch (number)
	{
	case 1:
		SetConsoleTextAttribute(hConsole, (WORD)((8 << 4) | 15));
		printf("%s","-> 1 - int\n");
		SetConsoleTextAttribute(hConsole, (WORD)((15 << 4) | 0));
		printf("%s%s%s%s%s","|| 2 - char\n",
			"|| 3 - float\n",
			"|| 4 - double\n",
			"|| 5 - long\n",
			"|| 6 - exit\n");
		break;
	case 2:
		printf("%s","|| 1 - int\n");
		SetConsoleTextAttribute(hConsole, (WORD)((8 << 4) | 15));
		printf("%s", "-> 2 - char\n");
		SetConsoleTextAttribute(hConsole, (WORD)((15 << 4) | 0));
		printf("%s%s%s%s", "|| 3 - float\n",
			"|| 4 - double\n",
			"|| 5 - long\n",
			"|| 6 - exit\n");
		break;
	case 3:
		printf("%s%s", "|| 1 - int\n",
			"|| 2 - char\n");
		SetConsoleTextAttribute(hConsole, (WORD)((8 << 4) | 15));
		printf("%s", "-> 3 - float\n");
		SetConsoleTextAttribute(hConsole, (WORD)((15 << 4) | 0));
		printf("%s%s%s", "|| 4 - double\n",
			"|| 5 - long\n",
			"|| 6 - exit\n");
		break;
	case 4:
		printf("%s%s%s", "|| 1 - int\n",
			"|| 2 - char\n",
			 "|| 3 - float\n");
		SetConsoleTextAttribute(hConsole, (WORD)((8 << 4) | 15));
		printf("%s", "-> 4 - double\n");
		SetConsoleTextAttribute(hConsole, (WORD)((15 << 4) | 0));
		printf("%s%s", "|| 5 - long\n",
			"|| 6 - exit\n");
		break;
	case 5:
		printf("%s%s%s%s", "|| 1 - int\n",
			"|| 2 - char\n",
			"|| 3 - float\n",
			"|| 4 - double\n");
		SetConsoleTextAttribute(hConsole, (WORD)((8 << 4) | 15));
		printf("%s", "-> 5 - long\n");
		SetConsoleTextAttribute(hConsole, (WORD)((15 << 4) | 0));
		printf("%s", "|| 6 - exit\n");
		break;
	case 6:
		printf("%s%s%s%s%s", "|| 1 - int\n",
			"|| 2 - char\n",
			"|| 3 - float\n",
			"|| 4 - double\n",
			"|| 5 - long\n");
		SetConsoleTextAttribute(hConsole, (WORD)((8 << 4) | 15));
		printf("%s", "-> 6 - exit\n");
		SetConsoleTextAttribute(hConsole, (WORD)((15 << 4) | 0));
		break;
	default:
		break;
	}
	printf("%s", "===============================\n");
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
		printf("int: ");
		if (!scanf("%d", &a))
			throw 1;
		PrintBinNumber(a);
		break;
	case 2:
		printf("char: ");
		if(!scanf("%c", &b))
			throw 1;
		PrintBinNumber(b);
		break;
	case 3:
		printf("float: ");
		if(!scanf("%f", &c))
			throw 1;
		PrintBinNumber(c);
		break;
	case 4:
		printf("double: ");
		if(!scanf("%lf", &d))
			throw 1;
		printf("%lf", d);
		PrintBinNumber(d);
		break;
	case 5:
		printf("long: ");
		if(!scanf("%d", &e))
			throw 1;
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
	printf("size: %d bytes \n" ,sizeof(T));
	printLine(sizeof(T));
	for (int i = sizeof(T) * 8-1, j=7; i >=0 ; i--, j--)
	{
		printf("%d", j%10);
		if (!j)
		{
			printf(" ");
			j = 8;
		}
	}
	printf("\n");
	pointer += sizeof(T)-1;
	for (int i = 0; i < sizeof(T); i++, pointer--)
		PrintBin(*pointer);
	printLine(sizeof(T));
};

void PrintBin(char number)
{
	for (int i = 8; i >0; i--)
		printf("%d", ((number >> i) & 0x01));
	printf(" ");
}

void printLine(int MenuPointByte)
{
	printf("\n");
	for (int i = MenuPointByte * 8+3; i > 0; i--)
		printf("%s", "-");
	printf("\n");
}
