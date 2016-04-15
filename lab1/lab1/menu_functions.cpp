#include "menu_functions.h"
#include "templates.cpp"

void mainMenu()
{
	int mainMenuID = 1;
	int isExit = 1;//flag to exit: 1->continue, 0->exit					  
	char *menuText[] = { "int","char", "float", "double", "long", "change color", "EXIT" };
	printMenu("MAIN MENU", menuText, sizeof(menuText) / sizeof(*menuText), mainMenuID, 1);
		printf("\n%s", "Press F1 for open help\n");
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
			//	system("cls");
				printMenu("MAIN MENU", menuText, sizeof(menuText) / sizeof(*menuText), mainMenuID, 1);
				break;
			case escape:
				isExit = 0;
				break;
			case F1_key:
				printHelp();
				system("cls");
				printMenu("MAIN MENU", menuText, sizeof(menuText) / sizeof(*menuText), mainMenuID, 1);
				break;
			default:
				break;
			}
			printMenu("MAIN MENU", menuText, sizeof(menuText) / sizeof(*menuText), mainMenuID, 0);
		}
		catch (int errID) {
			printErrorDescrption(errID);
			system("cls");
			printMenu("MAIN MENU", menuText, sizeof(menuText) / sizeof(*menuText), mainMenuID, 1);
		}
	}
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
	system("cls");
	int a;
	char b;
	float c;
	double d;
	long e;
	switch (menuID)
	{
	case 1:
		printf("int: ");
		if (!scanf("%d", &a))
			throw 1;
		a = editMenu(a, menuID);
		break;
	case 2:
		printf("char: ");
		if (scanf("%c", &b) == 0)
			throw 1;
		b = editMenu(b, menuID);
		break;
	case 3:
		printf("float: ");
		if (scanf("%f", &c) == 0)
			throw 1;
		printf("readed: %f\n", c);
		c = editMenu(c, menuID);
		break;
	case 4:
		printf("double: ");
		if (scanf("%lf", &d) == 0)
			throw 1;
		d = editMenu(d, menuID);
		break;
	case 5:
		printf("long: ");
		if (scanf("%d", &e) == 0)
			throw 1;
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
