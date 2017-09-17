#pragma once
#include "document.hpp"
#include <cmath>
#include <map>
#include <set>
#include <unordered_map>

// document count is supposed to be extracted by attemping `documentById.size()`
struct Docollection {
    std::unordered_map<int, Document*> documentsById;
    std::unordered_map<std::string, std::set<int>> documentsByWord;
    std::unordered_map<std::string, double> idfMap;
    std::unordered_map<int, std::unordered_map<std::string, double>> tfidfMap;
    void calculateIDF();
    void calculateTFIDF();
    void operator+=(Document*); //insert document;
};