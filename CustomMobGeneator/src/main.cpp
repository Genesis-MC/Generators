
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
Put a hash tag '#' before biome requirements or dimension or block requirements and you will get a biome tag 
(requires some manual stuff first to work)
Skipping is better than specifying anything as false
)";
int main()
{
  cnsl::print_colored_reset(HowToUse, ConsoleColorAttributes::Yellow_FG);
  Generator generator;
  generator.start();
}
