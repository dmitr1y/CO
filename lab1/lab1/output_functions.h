#pragma once
#include "binNumber.h"
#include "global_data.h"
#include "menu_functions.h"

#include <Windows.h>
#include <iostream>
#include <conio.h>
#include <iomanip>
#include <intrin.h>
#include <stdio.h>

void printLine(int);
void printBitNumbers(int);
void printErrorDescrption(int);
void printColorMenu(int, int);
void printSubColorMenu(int);
void printHelp();
void printBinNumberRecurs(char *, int);
void clearStr(COORD);
void printMenu(char*, char **, int, int, bool);
void printMenuFrame(char *, int);
void setNumberColor(binNumber, int);
void setMenuColor(int, int, int);
