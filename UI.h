#ifndef UI_H

#define UI_H

#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <cstring>
#include "color.h"
#include "str.h"
#include "song.h"

extern COORD orgCursorPos; 
extern HANDLE hConsoleOutput; 
extern HWND hConsoleWnd; 

void justParsedFormat(char app, char tune, int numOfPai, int perPai, int speed); 

void justPushedTune(); 

void mainConsoleUI(int argc, char* argv[]);

#endif // !ifndef UI_H

