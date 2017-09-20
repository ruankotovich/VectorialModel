#pragma once
#include <iostream>
#include <map>
#include <unordered_map>

struct Document {
    int id;
    int totalWordsCount;
    std::unordered_map<std::string, int> wordAmountOnDocument;
    std::unordered_map<std::string, double> tfMap;
    void calculateTF();
    void addWord(const std::string& word);
    Document();
    double operator^(const Document*);
};
