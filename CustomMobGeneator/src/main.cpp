
#include <iostream>
#define _WIN32 1

#include "headers/generator.hpp"
#include "headers/cnsl.hpp"
#include <string>
// took me a while to search why doesnt work just to forget i have to include ()
const char* HowToUse = R"(
HOW TO USE
Press The `Enter` Key to skip something
this system treats everything as lowercase except technical name
Warnings are suggestions you should really follow them
Errors show how bad you are at making entities :skull:
Put a '#' before biome requirements or dimension or block requirements and you will get a tag (group)
Skipping is better than specifying anything as false
)";
int main()
{
  cnsl::print_colored_reset(HowToUse, ConsoleColorAttributes::Yellow_FG);
  Generator generator;
  generator.start();
}
