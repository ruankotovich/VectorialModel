#pragma once
#include <map>
#include <unordered_map>

struct Document {
    int id;
    int totalWordsCount;
    std::map<std::string, int> wordAmountOnDocument;
    std::map<std::string, double> tfMap;
    void calculateTF();
    void addWord(const std::string& word);
    Document();
};
