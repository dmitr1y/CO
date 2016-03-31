#include "binNumber.h"
#include "global_data.h"

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
	std::cout << "\nresult NUMBER: " << tmp << "\nsize: " << sizeof(tmp);
	_getch();
	return static_cast<T>(tmp);
}

template<typename T>
T choiseBinMenu(T number, int typeID)
{
	int isExit = 1;
	int keyCode;
	bool isInverse = false;
	int binSize;
	binSize = sizeof(number) * 8;
	int binMenuID = binSize - 1;
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