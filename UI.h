#ifndef UI_H

#define UI_H

#define WIN32_LEAN_AND_MEAN

#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <mmsystem.h>
#include <cstring>
#include <thread>
#include "color.h"
#include "str.h"
#include "song.h"

#pragma comment(lib, "WinMM.lib")

extern COORD orgCursorPos; 
extern HANDLE hConsoleOutput; 
extern HWND hConsoleWnd; 

void justParsedFormat(char app, char tune, int numOfPai, int perPai, int speed); 

void justPushedTune(); 

void mainConsoleUI(int argc, char* argv[]);

#endif // !ifndef UI_H

