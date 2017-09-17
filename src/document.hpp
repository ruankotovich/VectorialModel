#include <map>
#include <unordered_map>

struct Document {
    int id;
    int totalWordsCount;
    std::map<std::string, int> wordAmount;
    std::map<std::string, double> tfMap;
    void calculateTF();
};