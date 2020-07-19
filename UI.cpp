#include "UI.h"

COORD orgCursorPos = { 0, 0 }; 
HANDLE hConsoleOutput = NULL;
HWND hConsoleWnd = NULL;

void mainConsoleUI(int argc, char* argv[])
{
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE); 
    hConsoleWnd = GetConsoleWindow(); 
    SET_CONSOLE_COLOR(BLACK_COLOR, WHITE_COLOR); 
    if (argc > 1)
    {
        for (int i = 1; i < argc; ++i)
        {
            if (strlen(argv[i]) == 2 && argv[i][0] == '-' && argv[i][1] == 'v') //显示版本信息
            {
                std::cout << about << std::endl;
                continue;
            }
            else if (strlen(argv[i]) == 2 && argv[i][0] == '-' && argv[i][1] == 'o')    //播放主音乐
            {
                system("cls");
                SET_CONSOLE_COLOR(RED_COLOR, LIGHTYELLO_COLOR);
                for (int i = 0; i < sizeof(mainsong) / sizeof(song); ++i)
                {
                    std::cout << mainsong[i].str;
                    std::flush(std::cout); 
                    Beep(mainsong[i].tune, static_cast<int>(mainsong[i].pause * pai));
                }
                std::cout << std::endl;
                SET_CONSOLE_COLOR(BLACK_COLOR, WHITE_COLOR);
                system("cls");
                continue;
            }
            inputSong.clear();
            std::cout << parsing << argv[i] << "..." << std::endl;
            switch (readSong(argv[i]))
            {
            case FILE_NOT_EXIST:
                std::cerr << file_not_exist << argv[i] << std::endl;
                break;
            case GRAMMAR_MISTAKE:
                std::cerr << parse_failed << argv[i] << std::endl;
                break;
            default:

                //播放音乐
                std::cout << std::endl << parsed << argv[i] << '!' << std::endl;
                SetConsoleCursorPosition(hConsoleOutput, orgCursorPos); 
                SET_ATTR_COLOR(ATTR_BLACK_COLOR, ATTR_GRAY_COLOR); 
                size_t len = inputSong.size(); 
                for (size_t i = 0; i < len; ++i)
                {
                    std::cout << inputSong[i].str;
                    std::flush(std::cout);
                    Beep(inputSong[i].tune, static_cast<int>(inputSong[i].pause * pai));
                }
                SET_ATTR_COLOR(ATTR_BLACK_COLOR, ATTR_WHITE_COLOR); 
                std::cout << std::endl << std::endl;
            }
        }

    }
    else
    {
        char choice;
        std::string src; 
        while (true)
        {
            std::cout << start << std::endl;
            std::cin >> choice;
            std::cin.ignore(200, '\n');
            if (choice == 'A' || choice == 'a')
            {
                std::cout << please_input;
                std::flush(std::cout);
                std::cin >> src;
                std::cin.clear();
                std::cin.ignore(65535, '\n');
                inputSong.clear();
                std::cout << parsing << src << "..." << std::endl;
                switch (readSong(src.c_str()))
                {
                case FILE_NOT_EXIST:
                    std::cerr << file_not_exist << src.c_str() << std::endl;
                    break;
                case GRAMMAR_MISTAKE:
                    std::cerr << parse_failed << src.c_str() << std::endl;
                    break;
                default:

                    //播放音乐
                    std::cout << std::endl << parsed << src << '!' << std::endl;
                    SetConsoleCursorPosition(hConsoleOutput, orgCursorPos);
                    SET_ATTR_COLOR(ATTR_BLACK_COLOR, ATTR_GRAY_COLOR);
                    size_t len = inputSong.size();
                    for (size_t i = 0; i < len; ++i)
                    {
                        std::cout << inputSong[i].str;
                        std::flush(std::cout);
                        Beep(inputSong[i].tune, static_cast<int>(inputSong[i].pause * pai));
                    }
                    SET_ATTR_COLOR(ATTR_BLACK_COLOR, ATTR_WHITE_COLOR);
                    std::cout << std::endl << std::endl;
                }
            }
            /*else if (choice == 'B' || choice == 'b')
            {
                system("cls");
                SET_CONSOLE_COLOR(RED_COLOR, LIGHTYELLO_COLOR);
                for (int i = 0; i < sizeof(mainsong) / sizeof(song); ++i)
                {
                    std::cout << mainsong[i].str;
                    std::flush(std::cout);
                    Beep(mainsong[i].tune, static_cast<int>(mainsong[i].pause * pai));
                }
                std::cout << std::endl;
                SET_CONSOLE_COLOR(BLACK_COLOR, WHITE_COLOR);
            }*/
            else if (choice == 'B' || choice == 'b')
            {
                system("cls");
                std::cout << about << std::endl;
            }
            else if (choice == 'C' || choice == 'c') break;
            else std::cout << illegal << std::endl;
        }
    }
    CloseHandle(hConsoleOutput); 
}

void justParsedFormat(char tune, int numOfPai, int perPai, int speed)
{
    std::cout << std::endl << 'C' << std::endl << numOfPai << '/' << perPai << std::endl << "Speed: " << speed << " beats/min" << std::endl; 
}

void justPushedTune()
{
    if (inputSong.size() == 1)
    {
        CONSOLE_SCREEN_BUFFER_INFO nowScreenBufferInfo; 
        std::cout << std::endl; 
        GetConsoleScreenBufferInfo(hConsoleOutput, &nowScreenBufferInfo); 
        orgCursorPos = nowScreenBufferInfo.dwCursorPosition; 
    }
    std::cout << inputSong[inputSong.size() - 1].str << std::flush; 
}

