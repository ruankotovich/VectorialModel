#include "parser.hpp"

void Parser::setFile(const std::string& file)
{
    this->m_currentStream = std::ifstream(file);
}

void Parser::parseNext()
{
}

Parser::Parser()
    : m_currentClass(CursorClass::NOTHING)
{
}