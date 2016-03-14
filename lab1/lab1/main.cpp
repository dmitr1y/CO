#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <iomanip>

struct binNumber
{
	int sign;
	int mantissa;
	int order;
};

//if (GetAsyncKeyState(VK_SHIFT)&&GetAsyncKeyState(VK_F1))
//{
//	std::cout << "SHIFT + F1" << "\n";
//}

void printMainMenu(int);
template <typename T>
T printBinNumber(T, int, int, bool);
template <typename T>
T choiseBinMenu(T, int);
void printLine(int);
void printBitNumbers(int);
bool choiseInputType(int);
void printErrorDescrption(int);
int setColorForTypes(int, int);
void colorMenu();
void setNumberColor(binNumber, int);
void printColorMenu(int, int);
bool choiseColor(int);
void printSubColorMenu(int);
void setMenuColor(int, int);

binNumber posInt, posFloat, posDouble, posLong;//position sign,order & mantissa for different types
int mainMenuID = 1; //initial 1 point of Main menu
int binMenuID = 0;//initial 0 for bits number
binNumber color; //colors for sign,order & mantissa

int main() {
	posInt.sign = 31;
	posInt.order = 30;
	posInt.mantissa = -1;
	posDouble.sign = 63;
	posDouble.order = 62;
	posDouble.mantissa = 51;
	posFloat.sign = 31;
	posFloat.order = 30;
	posFloat.mantissa = 22;
	posLong = posInt;
	color.mantissa = color.order = color.sign = 15;//default color: black
	system("color F0");
	int isExit = 1;//flag to exit: 1->continue, 0->exit	
	try {
		printMainMenu(1);//init menu
	}
	catch (int errID) {
		printErrorDescrption(errID);
	}
	char symbol;
	while ((isExit!=0) && ((symbol = _getch())!=0))
	{
		system("cls");
		switch (symbol) {
		case 71:
			//home
			mainMenuID = 1;
			break;
		case 79:
			//end
			mainMenuID = 7;
			break;
		case 72:
			//up
			mainMenuID--;
			if (mainMenuID < 1)
				mainMenuID = 7;
			break;
		case 80:
			//down
			mainMenuID++;
			if (mainMenuID > 7)
				mainMenuID = 1;
			break;
		case 13:
			//enter
			try {
				isExit = choiseInputType(mainMenuID);
			}
			catch (int errID) {						
				printErrorDescrption(errID);				
			}			
			break;
		case 27:
			//esc
			isExit = 0;
			break;
		default:
			break;
		}
		try {
			printMainMenu(mainMenuID);
		}
		catch (int errID) {
			printErrorDescrption(errID);
		}
	}
	return 0;
}

void printMainMenu(int number)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	char *menuText[] = { "1 - int","2 - char", "3 - float", "4 - double", "5 - long", "6 - change color", "7 - exit" };
	system("cls");
	printf("%s%s%s", "===============================\n",
		":::::::::::::MENU::::::::::::::\n",
		"===============================\n");
	for (int i = 0; i < 7; i++)
	{
		if ((number - 1) == i) {
			printf("->");
			SetConsoleTextAttribute(hConsole, (WORD)((8 << 4) | 15));
		}
		else
			printf("| ");
		printf("%s\n", menuText[i]);
		SetConsoleTextAttribute(hConsole, (WORD)((15 << 4) | 0));
	}
	printf("%s", "===============================\n");
}

bool choiseInputType(int param)
{
	/*
	1-int
	2-char
	3-float
	4-double
	5-long
	6-color menu
	*/
	int a;
	char b;
	float c;
	double d;
	long e;
	printMainMenu(mainMenuID);
	switch (param)
	{
	case 1:
		printf("int: ");
		if (!scanf_s("%d", &a))
			throw 1;
		printf("readed: %d\n", a);
		a = choiseBinMenu(a, param);
		break;
	case 2:
		printf("char: ");
		if (!scanf_s("%c", &b))
			throw 1;
		printf("readed: %c\n", b);
		b = choiseBinMenu(b, param);
		break;
	case 3:
		printf("float: ");
		if (!scanf_s("%f", &c))
			throw 1;
		printf("readed: %f\n", c);
		c = choiseBinMenu(c, param);
		break;
	case 4:
		printf("double: ");
		if (!scanf_s("%lf", &d))
			throw 1;
		printf("readed: %lf\n", d);
		d = choiseBinMenu(d, param);
		break;
	case 5:
		printf("long: ");
		if (!scanf_s("%d", &e))
			throw 1;
		printf("readed: %d\n", e);
		e = choiseBinMenu(e, param);
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
	return true;
}

template<typename T>
T choiseBinMenu(T number, int param)
{
	int isExit = 1;
	char symbol;
	bool isInverse = false;
	int binSize;
	binSize = sizeof(number) * 8;
	binMenuID = binSize - 1;
	printBinNumber(number, param, binSize - 1, false);
	while ((isExit != 0) && ((symbol = _getch()) != 0))
	{
		isInverse = false;
		system("cls");
		switch (symbol) {
		case 75:
			//left
			binMenuID++;
			if (binMenuID > (binSize - 1))
				binMenuID = 0;
			break;
		case 77:
			//right
			binMenuID--;
			if (binMenuID < 0)
				binMenuID = binSize - 1;;
			break;
		case 13:
			//enter
			isInverse = true;
			break;
		case 27:
			//esc
			isExit = 0;
			break;
		default:
			break;
		}
		number = printBinNumber(number, param, binMenuID, isInverse);
	}
	return number;
};

template<typename T>
T printBinNumber(const T number, int typeID, int startPos, bool isInverse)
{
	/* TypeID:
	1-int
	2-char
	3-float
	4-double
	5-long
	*/	
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	char *pointer = (char*)&number;	
	printf("size: %d bytes \n", sizeof(T));
	printLine(sizeof(T));
	printBitNumbers(sizeof(T));
	pointer += sizeof(T)-1;
	for (int i = 0, count = sizeof(T) * 8 - 1; i < sizeof(T); i++, pointer--)
	{
		for (int j = 7; j >= 0; j--, count--)
		{
			setMenuColor(count, typeID);
			if (isInverse == true && binMenuID == count)
				(*pointer) ^= 0x01 << j;
			printf("%d", (((*pointer) >> j) & 0x01));
		}
		SetConsoleTextAttribute(hConsole, (WORD)((15 << 4) | 0));
		printf(" ");
	}
	SetConsoleTextAttribute(hConsole, (WORD)((15 << 4) | 0));
	printLine(sizeof(T));
	std::cout << "current number: " << std::setprecision(18) << number << "\n";
	return number;
}

void printBitNumbers(int typeSize)
{
	for (int i = typeSize * 8 - 1, j = 7; i >= 0; i--, j--)
	{
		printf("%d", j % 10);
		if (!j)
		{
			printf(" ");
			j = 8;
		}
	}
	printf("\n");
}

void printLine(int mainMenuIDByte)
{
	printf("\n");
	for (int i = mainMenuIDByte * 8+3; i > 0; i--)
		printf("%s", "-");
	printf("\n");
}

void printErrorDescrption(int errCode)
{
	printf("ERROR CODE: %d [",errCode);
	switch (errCode)
	{
	case 1:
		printf("%s", "invalid input: attempt to flush stdin");
		while (getchar() != '\n');
		break;
	case 2:
		printf("%s", "incorrect choice");
		break;
	case 3:
		printf("%s", "color not found: setting default color");
		break;
	case 4:		
		printf("%s", "subColorMenu ID not found");
		break;
	case 5:
		printf("%s", "mainMenu ID not found");
		break;
	case 6:		
		printf("%s", "colorMenu ID not found");
		break;
	default:
		printf("%s", "unknown");
		break;
	}
	printf("%s", "]\n");
	system("pause");
}

int setColorForTypes(int typeID, int count)
{
	switch (typeID)
	{
	case 1:
		setNumberColor(posInt, count);
		break;
	case 2:
		setNumberColor(posInt, count);
		break;
	case 3:
		setNumberColor(posFloat, count);
		break;
	case 4:
		setNumberColor(posDouble, count);
		break;
	case 5:
		setNumberColor(posLong, count);
		break;
	default:
		break;
	}
	return 0;
}

void setNumberColor(binNumber pos, int count)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, (WORD)((15 << 4) | 0));
	if (count==pos.sign)
		SetConsoleTextAttribute(hConsole, (WORD)((color.sign << 4) | 0));
	if (count<=pos.order && count >pos.mantissa)
		SetConsoleTextAttribute(hConsole, (WORD)((color.order << 4) | 0));
	if (count <= pos.mantissa && count >= 0)
		SetConsoleTextAttribute(hConsole, (WORD)((color.mantissa << 4) | 0));
}

void setMenuColor(int pos, int typeID)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	if (pos== binMenuID)
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 15));
	else
		setColorForTypes(typeID, pos);
}

void colorMenu()
{
	int MenuID = 1;
	int isExit = 1;	
	int SubID = 1;
	int tmp;
	char symbol;	
	try {
		printColorMenu(1, 1);
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
					isExit = choiseColor(tmp);	
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
	catch (int errID) {
		printErrorDescrption(errID);
	}
}

void printColorMenu(int menuID, int subID)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	char *menuText[] = { "1 - green","2 - blue", "3 - red", "4 - yellow", "5 - white", "6 - MAIN MENU" };
	int arrColor[] = { 10,11,12,14,15,15 };
	system("cls");
	printf("%s%s%s", "===============================\n",
		"::::::::::COLOR MENU:::::::::::\n",
		"===============================\n");
	printSubColorMenu(subID);
	printf("%s", "===============================\n");
	for (int i = 0; i < 6; i++)
	{
		if ((menuID - 1) == i)
			printf("->");
		else
			printf("|");
		SetConsoleTextAttribute(hConsole, (WORD)((arrColor[i] << 4) | 0));
		printf("%s\n", menuText[i]);
		SetConsoleTextAttribute(hConsole, (WORD)((15 << 4) | 0));
	}
	printf("%s", "===============================\n");
}

bool choiseColor(int param)
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
		color.mantissa = 10;
		break;
	case 22:
		color.mantissa = 11;
		break;
	case 23:
		color.mantissa = 12;
		break;
	case 24:
		color.mantissa = 14;
		break;
	case 25:
		color.mantissa = 15;
		break;
	case 26:
		return false;
		break;
	default:
		color.mantissa = color.order=color.sign=15;
		throw 3;
		break;
	}
	return true;
}

void printSubColorMenu(int param)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	char *menuText[] = { "sign","order", "mantissa" };
	printf("%s", ":::");
	int arrColor[3];
	arrColor[0] = color.sign;
	arrColor[1] = color.order;
	arrColor[2] = color.mantissa;
	for (int i = 0; i < 3; i++)
	{
		SetConsoleTextAttribute(hConsole, (WORD)((arrColor[i] << 4) | 0));
		if ((param - 1) == i)
			printf("->");
		printf("%s", menuText[i]);
		if ((param - 1) == i)
			printf("<-");
	}
	SetConsoleTextAttribute(hConsole, (WORD)((15 << 4) | 0));
	printf("%s", ":::\n");
}