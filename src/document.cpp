#include "document.hpp"

// TF(t) = (Number of times term t appears in a document) / (Total number of terms in the document).
void Document::calculateTF()
{
    for (auto& word : wordAmount) {
        tfMap.emplace(std::piecewise_construct, std::forward_as_tuple(word.first), std::forward_as_tuple(word.second / totalWordsCount));
    }
}