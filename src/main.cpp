#include "parser.hpp"

int main()
{
    Parser parser;
    std::string test = "Ru#an Gabr.1ie@l Gat.o- Barro!!@#!@$!@%!@%s";
    parser.extractWords(test);
    std::cout << test;
}