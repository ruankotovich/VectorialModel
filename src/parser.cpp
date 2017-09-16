#include "parser.hpp"

void Parser::setFile(const std::string& file)
{
    m_currentStream = std::ifstream(file);
}

void Parser::parseNext()
{

}