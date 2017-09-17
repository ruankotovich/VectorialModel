#include "document.hpp"
#include <cmath>
#include <map>
#include <set>

// document count is supposed to be extracted by attemping `documentById.size()`
struct Docollection {
    std::map<int, Document> documentsById;
    std::map<std::string, std::set<int>> documentsByWord;
    std::map<std::string, double> itfMap;
    void calculateIDF();
    void operator<<(Document&); //insert document;
};