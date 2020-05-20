
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

#define GET_COLOR_STR(_bk, _font) "color "#_bk#_font
#define SET_CONSOLE_COLOR(_bk, _font) system(GET_COLOR_STR(_bk, _font))


#endif
