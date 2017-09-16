#pragma once
#include <fstream>
#include <iostream>
#include <queue>

enum class CursorClass {
    PAPER_NUMBER, //PN
    RECORD_NUMBER, //RN
    ACESSION_NUMBER, //AN
    AUTHORS, //AU
    TITLE, //TI
    SOURCE, //SO
    MAJOR_SUBJECTS, //MJ
    MINOR_SUBJECTS, //MN
    AB_EX, //AB or EX
    REFERENCES, //RF
    CITATIONS, // CT
    NOTHING
};

class Parser {
    std::ifstream m_currentStream;
    CursorClass m_currentClass;

public:
    void setFile(const std::string&);
    void parseNext();
    Parser();
};
