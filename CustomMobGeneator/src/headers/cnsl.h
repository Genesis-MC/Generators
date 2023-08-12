#pragma once
#include <iostream>
#ifndef _WIN32
#define _WIN32 0
#endif

#if _WIN32 == true
// God it took me so long to get the stupid colors you gotta appreciate that for such a useless program lol
#include <Windows.h>
enum ConsoleColorAttributes : unsigned short {
    Reset = 0,
    Black_FG = 0,
    Blue_FG = 1,
    Green_FG = 2,
    Cyan_FG = 3,
    Red_FG = 4,
    Magenta_FG = 5,
    Brown_FG = 6,
    Light_Gray_FG = 7,
    Dark_Gray_FG = 8,
    Light_Blue_FG = 9,
    Light_Green_FG = 10,
    Light_Cyan_FG = 11,
    Light_Red_FG = 12,
    Light_Magenta_FG = 13,
    Yellow_FG = 14,
    White_FG = 15,
    
    Black_BG = 0,
    Blue_BG = 16,
    Green_BG = 32,
    Cyan_BG = 48,
    Red_BG = 64,
    Magenta_BG = 80,
    Brown_BG = 96,
    Light_Gray_BG = 112,
    Dark_Gray_BG = 128,
    Light_Blue_BG = 144,
    Light_Green_BG = 160,
    Light_Cyan_BG = 176,
    Light_Red_BG = 192,
    Light_Magenta_BG = 208,
    Yellow_BG = 224,
    White_BG = 240,
    
   Bright_Black_BG = 0 | FOREGROUND_INTENSITY,
   Bright_Blue_BG = 16 | FOREGROUND_INTENSITY,
   Bright_Green_BG = 32 | FOREGROUND_INTENSITY,
   Bright_Cyan_BG = 48 | FOREGROUND_INTENSITY,
   Bright_Red_BG = 64 | FOREGROUND_INTENSITY,
   Bright_Magenta_BG = 80 | FOREGROUND_INTENSITY,
   Bright_Brown_BG = 96 | FOREGROUND_INTENSITY,
   Bright_Light_Gray_BG = 112 | FOREGROUND_INTENSITY,
   Bright_Dark_Gray_BG = 128 | FOREGROUND_INTENSITY,
   Bright_Light_Blue_BG = 144 | FOREGROUND_INTENSITY,
   Bright_Light_Green_BG = 160 | FOREGROUND_INTENSITY,
   Bright_Light_Cyan_BG = 176 | FOREGROUND_INTENSITY,
   Bright_Light_Red_BG = 192 | FOREGROUND_INTENSITY,
   Bright_Light_Magenta_BG = 208 | FOREGROUND_INTENSITY,
   Bright_Yellow_BG = 224 | FOREGROUND_INTENSITY,
   Bright_White_BG = 240 | FOREGROUND_INTENSITY,
   Bright_Black_FG = 0 | FOREGROUND_INTENSITY,
   Bright_Blue_FG = 1 | FOREGROUND_INTENSITY,
   Bright_Green_FG = 2 | FOREGROUND_INTENSITY,
   Bright_Cyan_FG = 3 | FOREGROUND_INTENSITY,
   Bright_Red_FG = 4 | FOREGROUND_INTENSITY,
   Bright_Magenta_FG = 5 | FOREGROUND_INTENSITY,
   Bright_Brown_FG = 6 | FOREGROUND_INTENSITY,
   Bright_Light_Gray_FG = 7 | FOREGROUND_INTENSITY,
   Bright_Dark_Gray_FG = 8 | FOREGROUND_INTENSITY,
   Bright_Light_Blue_FG = 9 | FOREGROUND_INTENSITY,
   Bright_Light_Green_FG = 10 | FOREGROUND_INTENSITY,
   Bright_Light_Cyan_FG = 11 | FOREGROUND_INTENSITY,
   Bright_Light_Red_FG = 12 | FOREGROUND_INTENSITY,
   Bright_Light_Magenta_FG = 13 | FOREGROUND_INTENSITY,
   Bright_Yellow_FG = 14 | FOREGROUND_INTENSITY,
   Bright_White_FG = 15 | FOREGROUND_INTENSITY,
   Intensity_FG = FOREGROUND_INTENSITY,
   Intensity_BG = BACKGROUND_INTENSITY,
   Reverse_F_G = COMMON_LVB_REVERSE_VIDEO,
};
#else
enum ConsoleColorAttributes {
    Reset = 0,
    Red_FGG = 11,
    Black_FG = 30,
    Black_BG = 40,
    Red_FG = 31,
    Red_BG = 41,
    Green_FG = 32,
    Green_BG = 42,
    Yellow_FG = 33,
    Yellow_BG = 43,
    Blue_FG = 34,
    Blue_BG = 44,
    Magenta_FG = 35,
    Magenta_BG = 45,
    Cyan_FG = 36,
    Cyan_BG = 46,
    White_FG = 37,
    White_BG = 47,

    Brown_FG = Black_FG,
    Light_Gray_FG = White_FG,
    Dark_Gray_FG = White_FG,
    Light_Blue_FG = Cyan_FG,
    Light_Green_FG = Green_FG,
    Light_Cyan_FG = Cyan_FG,
    Light_Red_FG = Red_FG,
    Light_Magenta_FG = Magenta_FG,

    Brown_BG = Black_BG,
    Light_Gray_BG = White_BG,
    Dark_Gray_BG = White_BG,
    Light_Blue_BG = Cyan_BG,
    Light_Green_BG = Green_BG,
    Light_Cyan_BG = Cyan_BG,
    Light_Red_BG = Red_BG,
    Light_Magenta_BG = Magenta_BG,
    
    Intensity_FG = 60,

    Bright_Black_FG = 90,
    Bright_Black_BG = 100,
    Bright_Red_FG = 91,
    Bright_Red_BG = 101,
    Bright_Green_FG = 92,
    Bright_Green_BG = 102,
    Bright_Yellow_FG = 93,
    Bright_Yellow_BG = 103,
    Bright_Blue_FG = 94,
    Bright_Blue_BG = 104,
    Bright_Magenta_FG = 95,
    Bright_Magenta_BG = 105,
    Bright_Cyan_FG = 96,
    Bright_Cyan_BG = 106,
    Bright_White_FG = 97,
    Bright_White_BG = 107,

    Bright_Brown_FG = Black_FG,
    Bright_Light_Gray_FG = White_FG,
    Bright_Dark_Gray_FG = White_FG,
    Bright_Light_Blue_FG = Cyan_FG,
    Bright_Light_Green_FG = Green_FG,
    Bright_Light_Cyan_FG = Cyan_FG,
    Bright_Light_Red_FG = Red_FG,
    Bright_Light_Magenta_FG = Magenta_FG,

    Bright_Brown_BG = Black_BG,
    Bright_Light_Gray_BG = White_BG,
    Bright_Dark_Gray_BG = White_BG,
    Bright_Light_Blue_BG = Cyan_BG,
    Bright_Light_Green_BG = Green_BG,
    Bright_Light_Cyan_BG = Cyan_BG,
    Bright_Light_Red_BG = Red_BG,
    Bright_Light_Magenta_BG = Magenta_BG
};
#endif

namespace cnsl {
    void clear();
    void print_colored(const char* x, ConsoleColorAttributes Color);
    void print_colored_reset(const char* x, ConsoleColorAttributes Color);
    void print_newline_colored_reset(const char* x, ConsoleColorAttributes Color);
    void color(ConsoleColorAttributes Color);
    void reset_color();
}