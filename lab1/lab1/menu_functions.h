#pragma once
#include "binNumber.h"
#include "global_data.h"
#include "output_funtions.h"
#include "keybord_keys.h"

#include <iostream>
#include <conio.h>

void mainMenu();
bool choiseInputType(int);//int menuID
void colorMenu();
bool choiseColor(int, int); // int typeID, int pos
void setColorForTypes(int, int); //int menuID, int colorID
