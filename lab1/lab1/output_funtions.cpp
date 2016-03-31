#include "output_funtions.h"
#include "templates.h"

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
			if ((arrLength - menuID + 1) < 0)
				menuID = 2;
			else
				menuID = 1;
		pos.Y = menuID + 2;
		clearStr(pos);// del bottom line
		printf("| %s\n", textArr[menuID - 1]);
		pos.Y = arrLength + 5;
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