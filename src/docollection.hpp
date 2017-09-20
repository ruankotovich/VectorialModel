#pragma once
#include "document.hpp"
#include "query.hpp"
#include <algorithm>
#include <cmath>
#include <fstream>
#include <iomanip> // std::setprecision
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>

struct QueryComparator_t {
    bool operator()(const std::pair<int, double>& f, const std::pair<int, double>& s)
    {
        return f.second < s.second;
    }
};

// document count is supposed to be extracted by attemping `documentById.size()`
struct Docollection {
    std::unordered_map<int, Document*> documentsById;
    std::unordered_map<std::string, std::set<int>> documentsByWord;
    std::unordered_map<std::string, double> idfMap;
    std::unordered_map<int, std::unordered_map<std::string, double>> tfidfMap;
    void calculateIDF();
    void calculateTFIDF();
    double calculateSimilarity(const Query&, const Document*);
    void operator+=(Document*); //insert document;
    std::unordered_map<std::string, double> calculateSpecificTFIDF(const Document*);
    std::priority_queue<std::pair<int, double>, std::vector<std::pair<int, double>>, QueryComparator_t> performQuery(const Query&);

private:
    void clearLine(std::string& s);
};
