#include "parser.hpp"

void Parser::setFile(const std::string& file)
{
    currentStream = std::ifstream(file);
}

void Parser::parseNext()
{
  
}