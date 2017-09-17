#include "parser.hpp"
#include <iostream>
#include <sstream>

void Parser::setFile(const std::string& file)
{
    this->m_currentStream = std::ifstream(file, std::ifstream::in);
}

Document* Parser::parseNext()
{
    Document* document = new Document();

    if (this->m_currentStream.is_open()) {
        std::string line;
        std::string block = "";
        std::string authors = "";

        while (std::getline(this->m_currentStream, line)) {
            auto classify = classifyLine(line);

            std::istringstream buffer(line);
            std::string code;
            buffer >> code;

            if (classify == CursorClass::REFERENCES) {
                clearLine(block);

                buffer = std::istringstream(authors);
                std::string word;
                while (buffer >> word) {
                    document->addWord(word);
                }

                buffer = std::istringstream(block);
                while (buffer >> word) {
                    document->addWord(word);
                }

                while (std::getline(this->m_currentStream, line)) {
                    classify = classifyLine(line);
                    if (classify == CursorClass::BLANK)
                        return document;
                }
            }

            if (classify == CursorClass::PAPER_NUMBER) {
                buffer >> document->id;
            }

            std::string remaining;
            getline(buffer, remaining);

            if (classify == CursorClass::AUTHORS) {
                authors += remaining;
            } else
                block += remaining;
        }

    } else
        std::cout << "not open"
                  << "\n";

    return document;
}

void Parser::clearLine(std::string& s)
{
    for (std::string::size_type i = 0; (i = s.find("-", i)) != std::string::npos;) {
        s.replace(i, 1, " ");
        ++i;
    }
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
    if (line.size() > 1) {
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
