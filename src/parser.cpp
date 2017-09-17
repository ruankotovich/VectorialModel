#include "parser.hpp"
#include <sstream>
#include <iostream>

void Parser::setFile(const std::string& file)
{
    this->m_currentStream = std::ifstream(file,  std::ifstream::in);
}

Document Parser::parseNext()
{
    Document document;

    if(this->m_currentStream.is_open()) {
        std::string line;
        CursorClass lastCursorClass;

        while(std::getline(this->m_currentStream,line)) {
            clearLine(line);
            std::istringstream buffer(line);
            auto classify = classifyLine(line);
            
            if(classify != CursorClass::NOTHING || classify != CursorClass::BLANK) {
                std::string code;
                buffer >> code;
            }

            if(classify == CursorClass::PAPER_NUMBER) {
                buffer >> document.id;
            }
            else {
                std::string word;
                while(buffer >> word) {
                    std::cout << word << std::endl;
                    document.addWord(word);
                }
            }
        }
        
    }
    else std::cout << "not open" << "\n";

    return document;
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
        std::string lineClassString = line.substr(0, 2);

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
