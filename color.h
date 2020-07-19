
#ifndef COLOR_H

#define COLOR_H

#define BLACK_COLOR 0
#define DARKBLUE_COLOR 1
#define GREEN_COLOR 2
#define LIGHTBLUE_COLOR 3
#define RED_COLOR 4
#define PERPLE_COLOR 5
#define YELLO_COLOR 6
#define LIGHTGRAY_COLOR 7
#define GRAY_COLOR 8
#define BLUE_COLOR 9
#define LIGHTGREEN_COLOR a
#define LIGHTLIGHTBLUE_COLOR b
#define LIGHTRED_COLOR c
#define LIGHTPURPLE_COLOR d
#define LIGHTYELLO_COLOR e
#define WHITE_COLOR f

#define ATTR_BLACK_COLOR 0x0
#define ATTR_DARKBLUE_COLOR 0x1
#define ATTR_GREEN_COLOR 0x2
#define ATTR_LIGHTBLUE_COLOR 0x3
#define ATTR_RED_COLOR 0x4
#define ATTR_PERPLE_COLOR 0x5
#define ATTR_YELLO_COLOR 0x6
#define ATTR_LIGHTGRAY_COLOR 0x7
#define ATTR_GRAY_COLOR 0x8
#define ATTR_BLUE_COLOR 0x9
#define ATTR_LIGHTGREEN_COLOR 0xa
#define ATTR_LIGHTLIGHTBLUE_COLOR 0xb
#define ATTR_LIGHTRED_COLOR 0xc
#define ATTR_LIGHTPURPLE_COLOR 0xd
#define ATTR_LIGHTYELLO_COLOR 0xe
#define ATTR_WHITE_COLOR 0xf

#define GET_COLOR_STR(_bk, _font) "color "#_bk#_font
#define SET_CONSOLE_COLOR(_bk, _font) system(GET_COLOR_STR(_bk, _font))

#define SET_ATTR_COLOR(_bk, _font) SetConsoleTextAttribute(hConsoleOutput, ((_bk) << (sizeof(WORD) * 8 / 2)) + (_font))


#endif
