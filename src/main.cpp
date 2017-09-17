#include "parser.hpp"

int main()
{
    Parser parser;
    std::string test = "Ru#an Gab-r.1ie@l Gat.o- Barro!!@#!@$!@%!@%s";
    parser.clearLine(test);
    std::cout << test;
}