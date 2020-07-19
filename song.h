
#ifndef SONG_H

#define SONG_H

#include "tune.h"
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <stack>
#include <cmath>
#include <functional>

void justPushedTune(); 
void justParsedFormat(char tune, int numOfPai, int perPai, int speed); 

#define INPUT_SUCCESS 0
#define FILE_NOT_EXIST 1
#define GRAMMAR_MISTAKE 2

#define LOW 0
#define MID 1
#define HIGH 2

#define DEFAULT_PAI 800

/***#define PUSH_TUNE() do {if (!stk.empty()) return GRAMMAR_MISTAKE;\
double len;\
if (length == HALF) len = 0.5;\
else if (length == QUARTER) len = 0.25;\
else len = length;\
if (prolong) len *= 1.5;\
if (height == MID) inputSong.push_back(song(middle[tuneTmp - '0'], len, ""));\
else if (height == HIGH) inputSong.push_back(song(high[tuneTmp - '0'], len, ""));\
else inputSong.push_back(song(low[tuneTmp - '0'], len, ""));\
tuneTmp = '9';\
height = MID;\
length = WHOLE;\
prolong = false; } while(false)*/

struct song
{
    int tune;
    double pause;
    std::string str;
    song(int _tune, double _pause, const char* const _str) : tune(_tune), pause(_pause), str(_str) {}
};

static song mainsong[]
{
    {mi1, 1, "〇"}, {so1, 2, "〇"}, {fa1, 1, "〇"}, {mi1, 1, "〇"}, {re1, 1.5, "〇"}, {mi1, 0.5, "〇"}, {fa1, 1, "〇"}, {zero, 0.5, "〇\n"},
    {fa1, 0.5, "〇"}, {mi1, 1.5, "〇"}, {mi1, 0.5, "〇"}, {re1, 1.5, "〇"}, {re1, 0.5, "〇"}, {do1, 3, "〇\n"},
    {so, 1, "Debout"}, {do1, 1.5, "! "}, {xi, 0.5, "Les "}, {re1, 0.5, "damnes"}, {do1, 0.5, " "}, {so, 0.5, "de "}, {mi, 0.5, "la "}, {la, 2, "terre"}, {fa, 1, "! "}, {zero, 0.5, "\n"}, //Debout! Les damnes de la terre
    {la, 0.5, "Debout"}, {re1, 1.5, "! "}, {do1, 0.5, "Les "}, {xi, 0.5, "forcats"}, {la, 0.5, " "}, {so, 0.5, "de "}, {fa, 0.5, "la "}, {mi, 3, "faim! \n"}, //Debout! Les forcats de la faim
    {so, 1, "La "}, {do1, 1.5, "raison"}, {xi, 0.5, " "}, {re1, 0.5, "tonne "}, {do1, 0.5, "en "}, {so, 0.5, "son "}, {mi, 0.5, "cratere"}, {la, 2, ". "}, {fa, 0.5, "\n"},     //La raison tonne son cratere
    {la, 0.5, ""}, {re1, 0.5, "C'est "}, {do1, 0.5, "l'eruption"}, {xi, 1, " "}, {re1, 1, ""}, {fa1, 1, "de "}, {xi, 1, "la "}, {do1, 2, "fin"}, {do1, 0.5, "! "}, {zero, 0.5, "\n"},  //C'est l'eruption de la fin
    {mi1, 0.5, "Du "}, {re1, 0.5, "passe"}, {xi, 2, " "}, {la, 0.5, "faisons"}, {xi, 0.5, " "}, {do1, 0.5, "table"}, {la, 0.5, " "}, {xi, 2, "rase. "}, {so, 0.5, "\n"},     //Du passe faisons table rase
    {so, 0.5, ""}, {sfa, 0.5, "Foule"}, {so, 0.5, " "}, {la, 1.5, "esclave! "}, {la, 0.5, "Debout"}, {re1, 1.5, "! "}, {do1, 0.5, "Debout"}, {xi, 2, "!"}, {xi, 0.5, " "}, {zero, 0.5, "\n"},     //Foule esclave, debout, debout
    {re1, 1, "Le "}, {re1, 1.5, "monde"}, {xi, 0.5, " "}, {so, 0.5, "va "}, {so, 0.5, "changer"}, {sfa, 0.5, " "}, {so, 0.5, "de "}, {mi1, 2, "base. "}, {do1, 0.5, "\n"},  //Le monde va changer de base
    {la, 0.5, "Nous "}, {xi, 0.5, "ne "}, {do1, 0.5, "sommes"}, {xi, 1, " "}, {re1, 1, "rien "}, {do1, 1, "soyons"}, {la, 1, " "}, {so, 2, "tout"}, {so, 0.5, "! "}, {zero, 0.5, "\n"}, //Nous ne sommes rien, soyons tout
    {mi1, 0.75, "C'est "}, {re1, 0.25, "la "}, {do1, 2, "lutte"}, {so, 1.5, " "}, {mi, 0.5, "finale"}, {la, 2, "."}, {fa, 0.5, " "}, {zero, 0.5, "\n"}, //C'est la lutte finale
    {re1, 0.75, "Groupons"}, {do1, 0.25, "-"}, {xi, 2, "nous "}, {la, 1, "et "}, {so, 1, "demain"}, {so, 2, "!"}, {so, 0.5, " "}, {zero, 0.5, "\n"}, //Groupons-nous et demain
    {so, 1, "L'Internationale"}, {mi1, 2, ""}, {re1, 1, ""}, {so, 1, ""}, {do1, 2, ""}, {xi, 1.5, " "}, //L'Internationale
    {xi, 0.5, "sera"}, {la, 1.5, " "}, {sso, 0.5, "le "}, {la, 1, "genre "}, {re1, 1, "humain"}, {re1, 2, "!"}, {re1, 0.5, " "}, {zero, 0.5, "\n"},    //sera le genre humain
    {mi1, 0.75, "C'est "}, {re1, 0.25, "la "}, {do1, 2, "lutte"}, {so, 1.5, " "}, {mi, 0.5, "finale"}, {la, 2, "."}, {fa, 0.5, " "}, {zero, 0.5, "\n"}, //C'est la lutte finale
    {re1, 0.75, "Groupons"}, {do1, 0.25, "-"}, {xi, 2, "nous "}, {la, 1, "et "}, {so, 1, "demain"}, {mi1, 3,"! \n"}, //Groupons-nous et demain
    {mi1, 1, "L'Internationale"}, {so1, 2, ""}, {fa1, 1, ""}, {mi1, 1, ""}, {re1, 1.5, ""}, {mi1, 0.5, ""}, {fa1, 1, ""}, {zero, 0.5, " "}, //L'Internationale
    {fa1, 0.5, "sera"}, {mi1, 1.5, " "}, {mi1, 0.5, "le "}, {re1, 1.5, "genre "}, {re1, 0.5, "humain! "}, {do1, 4, "\n"}, //Sera le genre humain
}; 

extern std::vector<song> inputSong; //读入歌曲

int readSong(const char* src);    //读入歌曲

extern int pai; //一个四分音符持续的毫秒数



#endif
