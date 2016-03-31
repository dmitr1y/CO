#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <iomanip>
#include <intrin.h>
#include <stdio.h>

struct binNumber
{
	int sign;
	int mantissa;
	int order;
};

enum keybordKeys
{
	escape = 27,
	enter = 13,
	left = 75,
	right = 77,
	up = 72,
	down = 80,
	home = 71,
	end = 79,
	F1_key = 59
};

template <typename T>
T setBitState(T, int, int, bool);
template <typename T>
T choiseBinMenu(T, int);
template<typename T>
T setRangeBitState(const T, int, int, bool, int);
template<typename T>
T editMenu(const T, int);
template<typename T>
void printBinNumber(const T, int);
template<typename T>
T choiseEditMenu(int, T, int);
void printLine(int);
void printBitNumbers(int);
bool choiseInputType(int);
void printErrorDescrption(int);
void setColorForTypes(int, int);
void colorMenu();
void setNumberColor(binNumber, int);
void printColorMenu(int, int);
bool choiseColor(int, int);
void printSubColorMenu(int);
void setMenuColor(int, int, int);
void printHelp();
void printBinNumberRecurs(char *, int);
void clearStr(COORD);
void printMenu(char*, char **, int, int, bool);
void printMenuFrame(char *, int);

template<typename T>
void printBinNumberWithMask(const T, int, int);

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
	//printMainMenu(0);//init menu
	char *menuText[] = { "int","char", "float", "double", "long", "change color", "EXIT" };
	printMenu("MAIN MENU",menuText, sizeof(menuText) / sizeof(*menuText), 1, 1);
//	printf("%s", "Press F1 for open help\n");
	int keyCode;
	while (isExit != 0)
	{
		keyCode = _getch();
		try {
			switch (keyCode) {
			case home:
				mainMenuID = 1;
				break;
			case end:
				mainMenuID = 7;
				break;
			case up:
				mainMenuID--;
				if (mainMenuID < 1)
					mainMenuID = 7;
				break;
			case down:
				mainMenuID++;
				if (mainMenuID > 7)
					mainMenuID = 1;
				break;
			case enter:
				isExit = choiseInputType(mainMenuID);
				//printMainMenu(0);
				printMenu("MAIN MENU", menuText, sizeof(menuText) / sizeof(*menuText), mainMenuID, 1);
				break;
			case escape:
				isExit = 0;
				break;
			case F1_key:
				printHelp();
				break;
			default:
				break;
			}
			//printMainMenu(mainMenuID);
			printMenu("MAIN MENU", menuText, sizeof(menuText) / sizeof(*menuText), mainMenuID, 0);
		}
		catch (int errID) {
			printErrorDescrption(errID);
		}
	}
	//	system("pause>>void");
	return 0;
}

void clearStr(COORD pos)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsole, pos);
	for (int i = 0; i < 25; i++)
		printf(" ");
	SetConsoleCursorPosition(hConsole, pos);
}

void printMenu(char *menuName, char **textArr, int arrLength, int menuID, bool isInit)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	if (isInit == true)
	{
		system("cls");
		printMenuFrame(menuName, arrLength);
		for (int i = 0; i < arrLength; i++)
		{
			if (i == (menuID - 1))
				SetConsoleTextAttribute(hConsole, (WORD)((5 << 3) | 15));
			printf("| %s\n", textArr[i]);
			SetConsoleTextAttribute(hConsole, (WORD)((15 << 4) | 0));
		}
	}
	else
	{
		pos.X = 0;
		pos.Y = menuID + 2;
		clearStr(pos);// del midle line
		SetConsoleTextAttribute(hConsole, (WORD)((5 << 3) | 15));
		printf("| %s\n", textArr[menuID - 1]);
		SetConsoleTextAttribute(hConsole, (WORD)((15 << 4) | 0));
		menuID--;
		if (menuID < 1)
			menuID = arrLength;
		pos.Y = menuID + 2;
		clearStr(pos); //del top line 
		printf("| %s\n", textArr[menuID - 1]);
		menuID += 2;
		if (menuID > arrLength)
			if ((arrLength - menuID+1) < 0)
				menuID = 2;
			else
				menuID = 1;
		pos.Y = menuID + 2;
		clearStr(pos);// del bottom line
		printf("| %s\n", textArr[menuID - 1]);
		pos.Y = arrLength+4;
		SetConsoleCursorPosition(hConsole, pos);
	}
}

void printMenuFrame(char *menuName, int menuLength)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = pos.Y = 0;
	SetConsoleCursorPosition(hConsole, pos);
	for (int i = 0; i < strlen(menuName) + 6; i++)
		printf("%c", ':');
	printf("\n");
	printf(":: %s ::\n", menuName);
	for (int i = 0; i < strlen(menuName) + 6; i++)
		printf("%s", ":");
	printf("\n");
	pos.Y = menuLength + 3;
	SetConsoleCursorPosition(hConsole, pos);
	for (int i = 0; i < strlen(menuName) + 6; i++)
		printf("%c", ':');
	printf("\n");
	pos.Y = 3;
	SetConsoleCursorPosition(hConsole, pos);
}

bool choiseInputType(int menuID)
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
	switch (menuID)
	{
	case 1:
		printf("int: ");
		if (!scanf_s("%d", &a))
			throw 1;
		//printf("readed: %d\n", a);
		a = editMenu(a, menuID);
		break;
	case 2:
		printf("char: ");
		if (scanf_s("%c", &b) == 0)
			throw 1;
		//printf("readed: %c\n", b);
		b = editMenu(b, menuID);
		break;
	case 3:
		printf("float: ");
		if (scanf_s("%f", &c) == 0)
			throw 1;
		printf("readed: %f\n", c);
		c = editMenu(c, menuID);
		break;
	case 4:
		printf("double: ");
		if (scanf_s("%lf", &d) == 0)
			throw 1;
		//printf("readed: %lf\n", d);
		d = editMenu(d, menuID);
		break;
	case 5:
		printf("long: ");
		if (scanf_s("%d", &e) == 0)
			throw 1;
		//printf("readed: %d\n", e);
		e = editMenu(e, menuID);
		break;
	case 6:
		colorMenu();
		break;
	case 7:
		//exit
		return false;
	default:
		throw 2;
		break;
	}
	return true;
}

template<typename T>
T choiseBinMenu(T number, int typeID)
{
	int isExit = 1;
	int keyCode;
	bool isInverse = false;
	int binSize;
	binSize = sizeof(number) * 8;
	binMenuID = binSize - 1;
	setBitState(number, typeID, binSize - 1, false);
	while (isExit != 0)
	{
		keyCode = _getch();
		isInverse = false;
		system("cls");
		switch (keyCode) {
		case left:
			binMenuID++;
			if (binMenuID > (binSize - 1))
				binMenuID = 0;
			break;
		case right:
			binMenuID--;
			if (binMenuID < 0)
				binMenuID = binSize - 1;
			break;
		case enter:
			isInverse = true;
			break;
		case escape:
			isExit = 0;
			break;
		default:
			break;
		}
		number = setBitState(number, typeID, binMenuID, isInverse);
	}
	return number;
};

template<typename T>
T setBitState(const T number, int typeID, int binMenuID, bool isInverse)
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
	pointer += sizeof(T) - 1;
	for (int i = 0, count = sizeof(T) * 8 - 1; i < sizeof(T); i++, pointer--)
	{
		for (int j = 7; j >= 0; j--, count--)
		{
			setMenuColor(count, typeID, binMenuID);
			if (isInverse == true && binMenuID == count)
				(*pointer) ^= 0x01 << j;
			printf("%d", (((*pointer) >> j) & 0x01));
		}
		SetConsoleTextAttribute(hConsole, (WORD)((15 << 4) | 0));
		printf(" ");
	}
	printLine(sizeof(T));
	std::cout << "current number: " << std::setprecision(18) << number << "\n";
	return number;
}

template<typename T>
void printBinNumberWithMask(const T number, int startBit, int endBit)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	char *pointer = (char*)&number;
	printLine(sizeof(T));
	printBitNumbers(sizeof(T));
	pointer += sizeof(T) - 1;
	//printBinNumberRecurs(pointer, sizeof(T));
	for (int i = 0, count = sizeof(T) * 8 - 1; i < sizeof(T); i++, pointer--)
	{
		for (int j = 7; j >= 0; j--, count--)
		{
			if (endBit >= count && startBit <= count)
				SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 15));
			else
				SetConsoleTextAttribute(hConsole, (WORD)((15 << 4) | 0));
			printf("%d", (((*pointer) >> j) & 0x01));
		}
		SetConsoleTextAttribute(hConsole, (WORD)((15 << 4) | 0));
		printf(" ");
	}
	printLine(sizeof(T));
}

template<typename T>
void printBinNumber(const T number, int typeID)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	char *pointer = (char*)&number;
	printLine(sizeof(T));
	printBitNumbers(sizeof(T));
	pointer += sizeof(T) - 1;
	for (int i = 0, count = sizeof(T) * 8 - 1; i < sizeof(T); i++, pointer--)
	{
		for (int j = 7; j >= 0; j--, count--)
		{
			setColorForTypes(typeID, count);
			printf("%d", (((*pointer) >> j) & 0x01));
		}
		SetConsoleTextAttribute(hConsole, (WORD)((15 << 4) | 0));
		printf(" ");
	}
	printLine(sizeof(T));
	_getch();
}

void printBinNumberRecurs(char *pointer, int size)
{
	static int j = 7;
	if (size>0)
	{
		if (j >= 0) {
			std::cout << (((*pointer) >> j) & 1);
			j--;
		}
		else {
			printf(" ");
			j = 7;
			size--;
			pointer--;
		}
		printBinNumberRecurs(pointer, size);
	}
}

template<typename T>
T setRangeBitState(const T number, int startBit, int endBit, bool state, int typeID)
{
	long long tmp = NULL;
	system("cls");
	char *pointer = (char*)&tmp + sizeof(T) - 1;
	if (startBit < 0 || startBit >= (8 * sizeof(T)) || endBit < 0 || endBit >= (8 * sizeof(T)))
		throw 7;
	std::cout << "source NUMBER: " << number << "\n";
	printf("start bit: %d\nend bit: %d\nstate: %d\n\n", startBit, endBit, state);
	for (int count = 8 * sizeof(T) - 1, i = sizeof(T) - 1; i >= 0; i--, pointer--)
		//generate mask
		for (int j = 7; j >= 0; j--, count--)
			if (endBit >= count && startBit <= count)
				(*pointer) |= 1 << j;
	if (state == 0)
		tmp = ~tmp;
	printf("%s", "source NUMBER:");
	printBinNumberWithMask(number, startBit, endBit);
	printf("\n%s", "MASK:");
	printBinNumberWithMask(static_cast<T>(tmp), startBit, endBit);
	printf("\n%s", "result NUMBER:");
	if (state == 1)
		tmp |= static_cast<long long>(number);
	else
		tmp = static_cast<long long>(number)& tmp;
	printBinNumberWithMask(static_cast<T>(tmp), startBit, endBit);
	std::cout << "\nresult NUMBER: " << tmp << "\nsize: "<<sizeof(tmp);
	_getch();
	return static_cast<T>(tmp);
}

template<typename T>
T editMenu(const T number, int typeID)
{
	T tmp = number;
	char *menuText[] = { "bitmap edit", "edit bit range","output bitmap" };
	int editMenuID = 1;
	int isExit = 1;
	int keyCode;
	printMenu("EDIT MENU", menuText, sizeof(menuText) / sizeof(*menuText), editMenuID, 1);
	while (isExit != 0)
	{
		keyCode = _getch();
		switch (keyCode) {
		case up:
			editMenuID--;
			if (editMenuID < 1)
				editMenuID = 3;
			break;
		case down:
			editMenuID++;
			if (editMenuID > 3)
				editMenuID = 1;
			break;
		case enter:
			tmp = choiseEditMenu(editMenuID, tmp, typeID);
			printMenu("EDIT MENU", menuText, sizeof(menuText) / sizeof(*menuText), editMenuID, 1);
			break;
		case escape:
			isExit = 0;
			break;
		default:
			break;
		}
		printMenu("EDIT MENU", menuText, sizeof(menuText) / sizeof(*menuText), editMenuID, 0);
	}
	return tmp;
}

template<typename T>
T choiseEditMenu(int menuID, T number, int typeID)
{
	int startBit;
	int endBit;
	int state;
	switch (menuID)
	{
	case 1:
		number = choiseBinMenu(number, typeID);
		break;
	case 2:
		printf("%s", "input:\nstart bit: ");
		scanf_s("%d", &startBit);
		printf("%s", "end bit: ");
		scanf_s("%d", &endBit);
		printf("%s", "state: ");
		scanf_s("%d", &state);
		if (state != 0 && state != 1)
			return number;
		number = setRangeBitState(number, startBit, endBit, state, typeID);
		break;
	case 3:
		printBinNumber(number, typeID);
		break;
	default:
		return false;
	}
	return number;
}

void printBitNumbers(int typeSize)
{
	for (int i = typeSize * 8 - 1, j = 7; i >= 0; i--, j--)
	{
		printf("%d", j % 10);
		if (j == 0)
		{
			printf(" ");
			j = 8;
		}
	}
	printf("\n");
}

void printLine(int bytesCount)
{
	printf("\n");
	for (int i = bytesCount * 8 + bytesCount; i > 0; i--)
		printf("%s", "-");
	printf("\n");
}

void printErrorDescrption(int errCode)
{
	printf("ERROR CODE: %d [", errCode);
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
	case 7:
		printf("%s", "wrong range");
		break;
	default:
		printf("%s", "unknown");
		break;
	}
	printf("%s", "]\n");
	system("pause");
}

void setColorForTypes(int typeID, int pos)
{
	switch (typeID)
	{
	case 1:
		setNumberColor(posInt, pos);
		break;
	case 2:
		setNumberColor(posInt, pos);
		break;
	case 3:
		setNumberColor(posFloat, pos);
		break;
	case 4:
		setNumberColor(posDouble, pos);
		break;
	case 5:
		setNumberColor(posLong, pos);
		break;
	default:
		break;
	}
}

void setNumberColor(binNumber pos, int count)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, (WORD)((15 << 4) | 0));
	if (count == pos.sign)
		SetConsoleTextAttribute(hConsole, (WORD)((color.sign << 4) | 0));
	if (count <= pos.order && count > pos.mantissa)
		SetConsoleTextAttribute(hConsole, (WORD)((color.order << 4) | 0));
	if (count <= pos.mantissa && count >= 0)
		SetConsoleTextAttribute(hConsole, (WORD)((color.mantissa << 4) | 0));
}

void setMenuColor(int pos, int typeID, int menuID)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	if (pos == menuID)
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 15));
	else
		setColorForTypes(typeID, pos);
}

void colorMenu()
{
	int colorMenuID = 1;
	int isExit = 1;
	int subColorMenuID = 1;
	int keyCode;
	printColorMenu(1, 1);
	while (isExit != 0)
	{
		keyCode = _getch();
		switch (keyCode) {
		case left:
			subColorMenuID--;
			if (subColorMenuID < 1)
				subColorMenuID = 3;
			break;
		case right:
			subColorMenuID++;
			if (subColorMenuID > 3)
				subColorMenuID = 1;
			break;
		case home:
			colorMenuID = 1;
			break;
		case end:
			colorMenuID = 6;
			break;
		case up:
			colorMenuID--;
			if (colorMenuID < 1)
				colorMenuID = 6;
			break;
		case down:
			colorMenuID++;
			if (colorMenuID > 6)
				colorMenuID = 1;
			break;
		case enter:
			isExit = choiseColor(subColorMenuID, colorMenuID);
			break;
		case escape:
			isExit = 0;
			break;
		default:
			break;
		}
		printColorMenu(colorMenuID, subColorMenuID);
	}
}

void printColorMenu(int colorMenuID, int subColorMenuID)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	char *menuText[] = { "1 - green","2 - blue", "3 - red", "4 - yellow", "5 - white", "6 - MAIN MENU" };
	int arrColor[] = { 10,11,12,14,15,15 };
	system("cls");
	printf("%s%s%s", "===============================\n",
		"::::::::::COLOR MENU:::::::::::\n",
		"===============================\n");
	printSubColorMenu(subColorMenuID);
	printf("%s", "===============================\n");
	for (int i = 0; i < 6; i++)
	{
		if ((colorMenuID - 1) == i)
			printf("->");
		else
			printf("| ");
		SetConsoleTextAttribute(hConsole, (WORD)((arrColor[i] << 4) | 0));
		printf("%s\n", menuText[i]);
		SetConsoleTextAttribute(hConsole, (WORD)((15 << 4) | 0));
	}
	printf("%s", "===============================\n");
}

bool choiseColor(int menuID, int colorID)
{
	int arrColor[] = { 10,11,12,14,15 };
	if (colorID < 1 || colorID>5)
		return false;
	switch (menuID)
	{
	case 1:
		color.sign = arrColor[colorID - 1];
		break;
	case 2:
		color.order = arrColor[colorID - 1];
		break;
	case 3:
		color.mantissa = arrColor[colorID - 1];
		break;
	default:
		color.mantissa = color.order = color.sign = 15;
		throw 3;
		break;
	}
	return true;
}

void printSubColorMenu(int menuID)
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
		if ((menuID - 1) == i)
			printf("->");
		printf("%s", menuText[i]);
		if ((menuID - 1) == i)
			printf("<-");
	}
	SetConsoleTextAttribute(hConsole, (WORD)((15 << 4) | 0));
	printf("%s", ":::\n");
}

void printHelp()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	system("cls");
	char *arrKeys[] = { "F1", "up, down, left, right","home","end", "Enter", "Esc" };
	char *arrDescriptions[] = { "help", "use to select","go to the first menu item","go to the last menu item", "confirm the selection (or invert selected bit)", "exit the current menu" };
	printf("%s%s%s", "===============================\n",
		":::::::::::::HELP::::::::::::::\n",
		"===============================\n");
	for (int i = 0; i < 6; i++)
	{
		printf("| ");
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 15));
		printf("%s", arrKeys[i]);
		SetConsoleTextAttribute(hConsole, (WORD)((15 << 4) | 0));
		printf(" - %s\n", arrDescriptions[i]);
	}
	printf("%s", "===============================\n");
	system("pause");
}