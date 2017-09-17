#include "document.hpp"
#include <cmath>
#include <map>
#include <set>
#include <unordered_map>

// document count is supposed to be extracted by attemping `documentById.size()`
struct Docollection {
    std::map<int, Document> documentsById;
    std::map<std::string, std::set<int>> documentsByWord;
    std::map<std::string, double> itfMap;
    std::map<int, std::map<std::string, double>> tfidfMap;
    void calculateIDF();
    void calculateTFIDF();
    void operator<<(Document&); //insert document;
};