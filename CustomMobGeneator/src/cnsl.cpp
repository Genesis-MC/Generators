#include "headers/cnsl.h"
#include "headers/string_utils.h"
#if _WIN32 == true
inline HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

namespace cnsl {
    void clear() {
        system("cls");
    }
    void print_colored(const char* x, ConsoleColorAttributes Color) {
        SetConsoleTextAttribute(hConsole, (short)Color);
        std::cout << x;
    }
    void print_colored_reset(const char* x, ConsoleColorAttributes Color) {
        SetConsoleTextAttribute(hConsole, (short)Color);
        std::cout << x;
        reset_color();
    }
    void color(ConsoleColorAttributes Color) {
        SetConsoleTextAttribute(hConsole, (short)Color);
    }
    void reset_color() {
        SetConsoleTextAttribute(hConsole, (short)ConsoleColorAttributes::White_FG);
    }
}
#else
namespace cnsl {
    void clear() {
        system("clear");
    }
    void print_colored(const char* x, ConsoleColorAttributes Color) {
        std::cout << "\033[" << Color << 'm' << x;
    }
    void print_colored_reset(const char* x, ConsoleColorAttributes Color) {
        std::cout << "\033[" << Color << 'm' << x;
        reset_color();
    }
    void color(ConsoleColorAttributes Color) {
        std::cout << "\033[" << Color << 'm';
    }
    void reset_color() {
        std::cout << "\033[0;" << ConsoleColorAttributes::White_FG << ';' << ConsoleColorAttributes::Black_BG << 'm';
    }
}
#endif