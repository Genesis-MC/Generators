
#include <iostream>
#define _WIN32 1

#include "headers/generator.hpp"
#include "headers/cnsl.h"
#include <string>
// took me a while to search why doesnt work just to forget i have to include ()
const char* HowToUse = R"(
HOW TO USE
Press The `Enter` Key to skip something
this system treats everything as lowercase except technical name
Warnings are suggestions
Errors are errors you should follow what they say

)";
int main()
{
  cnsl::print_colored_reset(HowToUse, ConsoleColorAttributes::Yellow_FG);
  Generator generator;
  generator.start();
}
