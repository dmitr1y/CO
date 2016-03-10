#include <iostream>
#include <conio.h>
#include <Windows.h>

struct binNumber
{
	int sign;
	int mantiss;
	int order;
};



void PrintMenu(int);
template <typename T>
T PrintBinNumber(T, int, int,int);
void printLine(int);
bool ChoiseInputType(int);
void printErrDescrp(int);
int colorForBin(int , int );
void colorMenu();
void changeColor(binNumber, int);
void printColorMenu(int,int);
bool ChoiseColor(int);
void printSubColorMenu(int);

binNumber posInt, posFloat, posDouble, posLong;
int MenuPoint = 1;
binNumber color;

int main() {
	posInt.sign = 31;
	posInt.order = 30;
	posInt.mantiss = -1;
	posDouble.sign = 63;
	posDouble.order = 62;
	posDouble.mantiss = 51;
	posFloat.sign = 31;
	posFloat.order = 30;
	posFloat.mantiss = 22;
	posLong = posInt;
	color.mantiss = color.order = color.sign = 15;//default color: black
	system("color F0");
	int isExit = 1;//flag to exit: 1->continue, 0->exit	
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
			MenuPoint = 7;
			break;
		case 72:
			//up
			MenuPoint--;
			if (MenuPoint < 1)
				MenuPoint = 7;
			break;
		case 80:
			//down
			MenuPoint++;
			if (MenuPoint > 7)
				MenuPoint = 1;
			break;
		case 13:
			//enter
			try {
				isExit = ChoiseInputType(MenuPoint);
			}
			catch (int errCode) {						
				printErrDescrp(errCode);				
			}
			//printf("Flush stdin\n");
			while (getchar() != '\n');		
			break;
		case 27:
			//esc
			isExit = 0;
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
	system("cls");
	printf("%s%s%s","===============================\n",
		":::::::::::::MENU::::::::::::::\n",
			"===============================\n");
	switch (number)
	{
	case 1:
		SetConsoleTextAttribute(hConsole, (WORD)((8 << 4) | 15));
		printf("%s","-> 1 - int\n");
		SetConsoleTextAttribute(hConsole, (WORD)((15 << 4) | 0));
		printf("%s%s%s%s%s%s","|| 2 - char\n",
			"|| 3 - float\n",
			"|| 4 - double\n",
			"|| 5 - long\n",
			"|| 6 - change color\n",
			"|| 7 - exit\n");
		break;
	case 2:
		printf("%s","|| 1 - int\n");
		SetConsoleTextAttribute(hConsole, (WORD)((8 << 4) | 15));
		printf("%s", "-> 2 - char\n");
		SetConsoleTextAttribute(hConsole, (WORD)((15 << 4) | 0));
		printf("%s%s%s%s%s", "|| 3 - float\n",
			"|| 4 - double\n",
			"|| 5 - long\n",
			"|| 6 - change color\n",
			"|| 7 - exit\n");
		break;
	case 3:
		printf("%s%s", "|| 1 - int\n",
			"|| 2 - char\n");
		SetConsoleTextAttribute(hConsole, (WORD)((8 << 4) | 15));
		printf("%s", "-> 3 - float\n");
		SetConsoleTextAttribute(hConsole, (WORD)((15 << 4) | 0));
		printf("%s%s%s%s", "|| 4 - double\n",
			"|| 5 - long\n",
			"|| 6 - change color\n",
			"|| 7 - exit\n");
		break;
	case 4:
		printf("%s%s%s", "|| 1 - int\n",
			"|| 2 - char\n",
			 "|| 3 - float\n");
		SetConsoleTextAttribute(hConsole, (WORD)((8 << 4) | 15));
		printf("%s", "-> 4 - double\n");
		SetConsoleTextAttribute(hConsole, (WORD)((15 << 4) | 0));
		printf("%s%s%s", "|| 5 - long\n",
			"|| 6 - change color\n",
			"|| 7 - exit\n");
		break;
	case 5:
		printf("%s%s%s%s", "|| 1 - int\n",
			"|| 2 - char\n",
			"|| 3 - float\n",
			"|| 4 - double\n");
		SetConsoleTextAttribute(hConsole, (WORD)((8 << 4) | 15));
		printf("%s", "-> 5 - long\n");
		SetConsoleTextAttribute(hConsole, (WORD)((15 << 4) | 0));
		printf("%s%s", "|| 6 - change color\n",
			"|| 7 - exit\n");
		break;
	case 6:
		printf("%s%s%s%s%s", "|| 1 - int\n",
			"|| 2 - char\n",
			"|| 3 - float\n",
			"|| 4 - double\n",
			"|| 5 - long\n");
		SetConsoleTextAttribute(hConsole, (WORD)((8 << 4) | 15));
		printf("%s", "-> 6 - change color\n");
		SetConsoleTextAttribute(hConsole, (WORD)((15 << 4) | 0));
		printf("%s", "|| 7 - exit\n");
		break;
	case 7:
		printf("%s%s%s%s%s%s", "|| 1 - int\n",
			"|| 2 - char\n",
			"|| 3 - float\n",
			"|| 4 - double\n",
			"|| 5 - long\n",
			"|| 6 - change color\n");
		SetConsoleTextAttribute(hConsole, (WORD)((8 << 4) | 15));
		printf("%s", "-> 7 - exit\n");
		SetConsoleTextAttribute(hConsole, (WORD)((15 << 4) | 0));
		break;
	default:
		break;
	}
	printf("%s", "===============================\n");
}

bool ChoiseInputType(int param)
{
	/*
	1-int
	2-char
	3-float
	4-double
	5-long
	*/
	int startPos, endPos;
	startPos = endPos = -1;//default
	int a;
	char b;
	float c;
	double d;
	long e;
	PrintMenu(MenuPoint);
	int x;
	switch (param)
	{
	case 1:
		printf("int: ");
		if (!scanf("%d", &a))
			throw 1;
		printf("readed: %d\n", a);
		x = PrintBinNumber(a, param, startPos, endPos);
		std::cout << "CHANGED:" << x << "\n";
		PrintBinNumber(x, param, startPos, endPos);
		break;
	case 2:
		printf("char: ");
		if(!scanf("%c", &b))
			throw 1;
		printf("readed: %c\n", b);
		PrintBinNumber(b, param, startPos, endPos);
		break;
	case 3:
		printf("float: ");
		if(!scanf("%f", &c))
			throw 1;
		printf("readed: %f\n", c);
		PrintBinNumber(c, param, startPos, endPos);
		break;
	case 4:
		printf("double: ");
		if(!scanf("%lf", &d))
			throw 1;
		printf("readed: %lf\n", d);
		PrintBinNumber(d, param, startPos, endPos);
		break;
	case 5:
		printf("long: ");
		if(!scanf("%d", &e))
			throw 1;
		printf("readed: %d\n", e);
		PrintBinNumber(e, param, startPos, endPos);
		break;
	case 6:
		colorMenu();
		break;
	case 7:
		//exit
		return false;
		break;
	default:
		throw 2;
		break;
	}
	system("pause");
	return true;
}

template<typename T>
T PrintBinNumber(const T arg, int typeID, int startPos, int endPos)
{
	/* TypeID:
	1-int
	2-char
	3-float
	4-double
	5-long
	*/	
	char *pointer = (char*)&arg;	
	if (startPos==-1 && endPos==-1)
	{
		//nothing to do
	}
	else
	{
		if (startPos<0 || endPos>(8*sizeof(T)-1))
		{
			//ERR: bad value
		}
		//change from to on state:
		printf("%s", "change on: ");
	}
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
	for (int i = 0,count= sizeof(T)*8-1; i < sizeof(T); i++, pointer--)
	{
		for (int j = 7; j >= 0; j--, count--)
		{
			colorForBin(typeID, count);
			printf("%d", (((*pointer) >> j) & 0x01));
			if (!(((*pointer) >> j) & 0x01))
			{
				(*pointer) |= 0x01<<j;
			}
			else
			{
				(*pointer) ^= 0x01 << j;
			}
		}
		printf(" ");
	}
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, (WORD)((15 << 4) | 0));
	printLine(sizeof(T));
	return arg;
};

void printLine(int MenuPointByte)
{
	printf("\n");
	for (int i = MenuPointByte * 8+3; i > 0; i--)
		printf("%s", "-");
	printf("\n");
}

void printErrDescrp(int errCode)
{
	printf("ERROR CODE: %d [",errCode);
	switch (errCode)
	{
	case 1:
		printf("%s", "invalid input");
		break;
	case 2:
		printf("%s", "incorrect choice");
		break;
	default:
		printf("%s", "unknown");
		break;
	}
	printf("%s", "]\n");
	system("pause");
}

int colorForBin(int typeID, int count)
{
	switch (typeID)
	{
	case 1:
		changeColor(posInt, count);
		break;
	case 2:
		changeColor(posInt, count);
		break;
	case 3:
		changeColor(posFloat, count);
		break;
	case 4:
		changeColor(posDouble, count);
		break;
	case 5:
		changeColor(posLong, count);
		break;
	default:
		break;
	}
	return 0;
}

void changeColor(binNumber pos, int count)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	if (count==pos.sign)
		SetConsoleTextAttribute(hConsole, (WORD)((color.sign << 4) | 0));
	if (count<=pos.order && count >pos.mantiss)
		SetConsoleTextAttribute(hConsole, (WORD)((color.order << 4) | 0));
	if (count <= pos.mantiss && count >= 0)
		SetConsoleTextAttribute(hConsole, (WORD)((color.mantiss << 4) | 0));
}

void colorMenu()
{
	int MenuID = 1;
	int isExit = 1;	
	int SubID = 1;
	char symbol;	
	printColorMenu(1,1);	
	//symbol = _getch();
	while ((isExit != 0) && ((symbol = _getch()) != 0))
	{
		system("cls");
		switch (symbol) {
		case 75:
			//left
			SubID--;
			if (SubID < 1)
				SubID = 3;
			break;
		case 77:
			//right
			SubID++;
			if (SubID > 3)
				SubID = 1;
			break;
		case 71:
			//home
			MenuID = 1;
			break;
		case 79:
			//end
			MenuID = 6;
			break;
		case 72:
			//up
			MenuID--;
			if (MenuID < 1)
				MenuID = 6;
			break;
		case 80:
			//down
			MenuID++;
			if (MenuID > 6)
				MenuID = 1;
			break;
		case 13:
			//enter
			try {
				int tmp;
				switch (SubID)
				{
				case 2:
					tmp = MenuID + 10;
					break;
				case 3:
					tmp = MenuID + 20;
					break;
				default:
					tmp = MenuID;
					break;
				}
				isExit = ChoiseColor(tmp);
			}
			catch (int errCode) {
				printErrDescrp(errCode);
				while (getchar() != '\n') {}
				printf("Flush stdin\n");
			}
			break;
		case 27:
			//esc
			isExit = 0;
			break;
		default:
			break;
		}
		printColorMenu(MenuID, SubID);
	}
}

void printColorMenu(int menuID,int subID)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	system("cls");
	printf("%s%s%s", "===============================\n",
		"::::::::::COLOR MENU:::::::::::\n",
		"===============================\n");
	printSubColorMenu(subID);
	switch (menuID)
	{
	case 1:
		printf("%s", "-> 1 - ");	SetConsoleTextAttribute(hConsole, (WORD)((10 << 4) | 0));
		printf("%s", "green\n"); SetConsoleTextAttribute(hConsole, (WORD)((15 << 4) | 0));
		printf("%s", "|| 2 - "); SetConsoleTextAttribute(hConsole, (WORD)((11 << 4) | 0));
		printf("%s", "blue\n"); SetConsoleTextAttribute(hConsole, (WORD)((15 << 4) | 0));
		printf("%s", "|| 3 - "); SetConsoleTextAttribute(hConsole, (WORD)((12 << 4) | 0));
		printf("%s", "red\n"); SetConsoleTextAttribute(hConsole, (WORD)((15 << 4) | 0));
		printf("%s", "|| 4 - "); SetConsoleTextAttribute(hConsole, (WORD)((14 << 4) | 0));
		printf("%s", "yellow\n"); SetConsoleTextAttribute(hConsole, (WORD)((15 << 4) | 0));
		printf("%s", "|| 5 - "); SetConsoleTextAttribute(hConsole, (WORD)((15 << 4) | 0));
		printf("%s", "white\n"); SetConsoleTextAttribute(hConsole, (WORD)((15 << 4) | 0));
		printf("%s", "|| 6 - ");
		printf("%s", "MAIN MENU\n");
		break;
	case 2:
		printf("%s", "|| 1 - ");	SetConsoleTextAttribute(hConsole, (WORD)((10 << 4) | 0));
		printf("%s", "green\n"); SetConsoleTextAttribute(hConsole, (WORD)((15 << 4) | 0));
		printf("%s", "-> 2 - "); SetConsoleTextAttribute(hConsole, (WORD)((11 << 4) | 0));
		printf("%s", "blue\n"); SetConsoleTextAttribute(hConsole, (WORD)((15 << 4) | 0));
		printf("%s", "|| 3 - "); SetConsoleTextAttribute(hConsole, (WORD)((12 << 4) | 0));
		printf("%s", "red\n"); SetConsoleTextAttribute(hConsole, (WORD)((15 << 4) | 0));
		printf("%s", "|| 4 - "); SetConsoleTextAttribute(hConsole, (WORD)((14 << 4) | 0));
		printf("%s", "yellow\n"); SetConsoleTextAttribute(hConsole, (WORD)((15 << 4) | 0));
		printf("%s", "|| 5 - "); SetConsoleTextAttribute(hConsole, (WORD)((15 << 4) | 0));
		printf("%s", "white\n"); SetConsoleTextAttribute(hConsole, (WORD)((15 << 4) | 0));
		printf("%s", "|| 6 - ");
		printf("%s", "MAIN MENU\n");
		break;
	case 3:
		printf("%s", "|| 1 - ");	SetConsoleTextAttribute(hConsole, (WORD)((10 << 4) | 0));
		printf("%s", "green\n"); SetConsoleTextAttribute(hConsole, (WORD)((15 << 4) | 0));
		printf("%s", "|| 2 - "); SetConsoleTextAttribute(hConsole, (WORD)((11 << 4) | 0));
		printf("%s", "blue\n"); SetConsoleTextAttribute(hConsole, (WORD)((15 << 4) | 0));
		printf("%s", "-> 3 - "); SetConsoleTextAttribute(hConsole, (WORD)((12 << 4) | 0));
		printf("%s", "red\n"); SetConsoleTextAttribute(hConsole, (WORD)((15 << 4) | 0));
		printf("%s", "|| 4 - "); SetConsoleTextAttribute(hConsole, (WORD)((14 << 4) | 0));
		printf("%s", "yellow\n"); SetConsoleTextAttribute(hConsole, (WORD)((15 << 4) | 0));
		printf("%s", "|| 5 - "); SetConsoleTextAttribute(hConsole, (WORD)((15 << 4) | 0));
		printf("%s", "white\n"); SetConsoleTextAttribute(hConsole, (WORD)((15 << 4) | 0));
		printf("%s", "|| 6 - ");
		printf("%s", "MAIN MENU\n");
		break;
	case 4:
		printf("%s", "|| 1 - ");	SetConsoleTextAttribute(hConsole, (WORD)((10 << 4) | 0));
		printf("%s", "green\n"); SetConsoleTextAttribute(hConsole, (WORD)((15 << 4) | 0));
		printf("%s", "|| 2 - "); SetConsoleTextAttribute(hConsole, (WORD)((11 << 4) | 0));
		printf("%s", "blue\n"); SetConsoleTextAttribute(hConsole, (WORD)((15 << 4) | 0));
		printf("%s", "|| 3 - "); SetConsoleTextAttribute(hConsole, (WORD)((12 << 4) | 0));
		printf("%s", "red\n"); SetConsoleTextAttribute(hConsole, (WORD)((15 << 4) | 0));
		printf("%s", "-> 4 - "); SetConsoleTextAttribute(hConsole, (WORD)((14 << 4) | 0));
		printf("%s", "yellow\n"); SetConsoleTextAttribute(hConsole, (WORD)((15 << 4) | 0));
		printf("%s", "|| 5 - "); SetConsoleTextAttribute(hConsole, (WORD)((15 << 4) | 0));
		printf("%s", "white\n"); SetConsoleTextAttribute(hConsole, (WORD)((15 << 4) | 0));
		printf("%s", "|| 6 - ");
		printf("%s", "MAIN MENU\n");
		break;
	case 5:
		printf("%s", "|| 1 - ");	SetConsoleTextAttribute(hConsole, (WORD)((10 << 4) | 0));
		printf("%s", "green\n"); SetConsoleTextAttribute(hConsole, (WORD)((15 << 4) | 0));
		printf("%s", "|| 2 - "); SetConsoleTextAttribute(hConsole, (WORD)((11 << 4) | 0));
		printf("%s", "blue\n"); SetConsoleTextAttribute(hConsole, (WORD)((15 << 4) | 0));
		printf("%s", "|| 3 - "); SetConsoleTextAttribute(hConsole, (WORD)((12 << 4) | 0));
		printf("%s", "red\n"); SetConsoleTextAttribute(hConsole, (WORD)((15 << 4) | 0));
		printf("%s", "|| 4 - "); SetConsoleTextAttribute(hConsole, (WORD)((14 << 4) | 0));
		printf("%s", "yellow\n"); SetConsoleTextAttribute(hConsole, (WORD)((15 << 4) | 0));
		printf("%s", "-> 5 - "); SetConsoleTextAttribute(hConsole, (WORD)((15 << 4) | 0));
		printf("%s", "white\n"); SetConsoleTextAttribute(hConsole, (WORD)((15 << 4) | 0));
		printf("%s", "|| 6 - ");
		printf("%s", "MAIN MENU\n");
		break;
	case 6:
		printf("%s", "|| 1 - ");	SetConsoleTextAttribute(hConsole, (WORD)((10 << 4) | 0));
		printf("%s", "green\n"); SetConsoleTextAttribute(hConsole, (WORD)((15 << 4) | 0));
		printf("%s", "|| 2 - "); SetConsoleTextAttribute(hConsole, (WORD)((11 << 4) | 0));
		printf("%s", "blue\n"); SetConsoleTextAttribute(hConsole, (WORD)((15 << 4) | 0));
		printf("%s", "|| 3 - "); SetConsoleTextAttribute(hConsole, (WORD)((12 << 4) | 0));
		printf("%s", "red\n"); SetConsoleTextAttribute(hConsole, (WORD)((15 << 4) | 0));
		printf("%s", "|| 4 - "); SetConsoleTextAttribute(hConsole, (WORD)((14 << 4) | 0));
		printf("%s", "yellow\n"); SetConsoleTextAttribute(hConsole, (WORD)((15 << 4) | 0));
		printf("%s", "|| 5 - "); SetConsoleTextAttribute(hConsole, (WORD)((15 << 4) | 0));
		printf("%s", "white\n"); SetConsoleTextAttribute(hConsole, (WORD)((15 << 4) | 0));
		printf("%s", "-> 6 - ");
		printf("%s", "MAIN MENU\n");
		break;
	default:
		break;
	}
	printf("%s", "===============================\n");
}

bool ChoiseColor(int param)
{
	/*
	0X-sign
	1X-order
	2X-mantis
	*/
	switch (param)
	{
	case 1:		
		color.sign = 10;
		break;
	case 2:
		color.sign = 11;
		break;
	case 3:
		color.sign = 12;
		break;
	case 4:
		color.sign = 14;
		break;
	case 5:
		color.sign = 15;
		break;
	case 6:
		return false;
		break;
	case 11:
		color.order = 10;
		break;
	case 12:
		color.order = 11;
		break;
	case 13:
		color.order = 12;
		break;
	case 14:
		color.order = 14;
		break;
	case 15:
		color.order = 15;
		break;
	case 16:
		return false;
		break;
	case 21:
		color.mantiss = 10;
		break;
	case 22:
		color.mantiss = 11;
		break;
	case 23:
		color.mantiss = 12;
		break;
	case 24:
		color.mantiss = 14;
		break;
	case 25:
		color.mantiss = 15;
		break;
	case 26:
		return false;
		break;
	default:
		color.mantiss = color.order=color.sign=15;
		return false;
		break;
	}
	return true;
}

void printSubColorMenu(int param)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	printf("%s", ":::");
	switch (param)
	{
	case 1:	SetConsoleTextAttribute(hConsole, (WORD)((color.sign << 4) | 0));
		printf("%s", "->sign<- ");	SetConsoleTextAttribute(hConsole, (WORD)((color.order << 4) | 0));
		printf("%s", " order "); SetConsoleTextAttribute(hConsole, (WORD)((color.mantiss << 4) | 0));
		printf("%s", " mantissa");
		break;
	case 2:
		SetConsoleTextAttribute(hConsole, (WORD)((color.sign << 4) | 0));
		printf("%s", "sign ");	SetConsoleTextAttribute(hConsole, (WORD)((color.order << 4) | 0));
		printf("%s", " ->order<- "); SetConsoleTextAttribute(hConsole, (WORD)((color.mantiss << 4) | 0));
		printf("%s", " mantissa");
		break;
	case 3:
		SetConsoleTextAttribute(hConsole, (WORD)((color.sign << 4) | 0));
		printf("%s", "sign ");	SetConsoleTextAttribute(hConsole, (WORD)((color.order << 4) | 0));
		printf("%s", " order ");
		SetConsoleTextAttribute(hConsole, (WORD)((color.mantiss << 4) | 0));
		printf("%s", " ->mantissa<-"); 
		break;
	default:
		break;
	}
	SetConsoleTextAttribute(hConsole, (WORD)((15 << 4) | 0));
	printf("%s", ":::\n");
}