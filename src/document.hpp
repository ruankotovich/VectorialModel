#include <map>

struct Document {
    int id;
    int totalWordsCount;
    std::map<std::string, int> wordAmountOnDocument;
};