#include "document.hpp"
#include <map>
#include <set>

struct Docollection {
    std::map<int, Document> documentsById;
    std::map<std::string, std::set<int>> documentsByWord;
    // document count is supposed to be extracted by attemping `documentById.size()`
};