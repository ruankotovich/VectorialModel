#include "parser.hpp"

void Parser::setFile(const std::string& file)
{
    this->m_currentStream = std::ifstream(file);
}

void Parser::parseNext()
{
}

void Parser::clearLine(std::string& s)
{
    // drop off the stopwords

    // tip taken on https://stackoverflow.com/questions/6319872/how-to-strip-all-non-alphanumeric-characters-from-a-string-in-c

    for (std::string::size_type i = 0; (i = s.find("-", i)) != std::string::npos;) {
        s.replace(i, 1, " ");
        ++i;
    }

    s.erase(std::remove_if(s.begin(), s.end(), [](char x) { return !(std::isalpha(x) || std::isspace(x)); }), s.end());
    std::transform(s.begin(), s.end(), s.begin(), ::tolower);
}

CursorClass Parser::classifyLine(const std::string& line)
{
    if (line.size() > 0) {
        std::string lineClassString = line.substr(0, 1);

        if (lineClassString == " ") {
            return CursorClass::NOTHING;
        }

        if (lineClassString == "PN") {
            return CursorClass::PAPER_NUMBER;
        }

        if (lineClassString == "RN") {
            return CursorClass::RECORD_NUMBER;
        }

        if (lineClassString == "AN") {
            return CursorClass::ACESSION_NUMBER;
        }

        if (lineClassString == "AU") {
            return CursorClass::AUTHORS;
        }

        if (lineClassString == "TI") {
            return CursorClass::TITLE;
        }

        if (lineClassString == "SO") {
            return CursorClass::SOURCE;
        }

        if (lineClassString == "MJ") {
            return CursorClass::MAJOR_SUBJECTS;
        }

        if (lineClassString == "MN") {
            return CursorClass::MINOR_SUBJECTS;
        }

        if (lineClassString == "AB") {
            return CursorClass::AB_EX;
        }

        if (lineClassString == "EX") {
            return CursorClass::AB_EX;
        }

        if (lineClassString == "RF") {
            return CursorClass::REFERENCES;
        }

        if (lineClassString == "CT") {
            return CursorClass::CITATIONS;
        }

        return CursorClass::NOTHING;
    }

    return CursorClass::BLANK;
}

Parser::Parser()
    : m_currentClass(CursorClass::NOTHING)
{
}