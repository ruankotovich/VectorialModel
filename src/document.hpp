#include <map>

struct Document {
    int id;
    int totalWordsCount;
    std::map<std::string, int> wordAmountOnDocument;
    std::map<std::string, double> tfMap;
    void calculateTF();

public:
    void addWord(const std::string& word) {
        auto tuple = wordAmountOnDocument.find(word);

        if(tuple == wordAmountOnDocument.end()) {
            wordAmountOnDocument.emplace(word, 1);
            totalWordsCount++;
        }
        else {
            wordAmountOnDocument[word]++;
        }
    }
};
