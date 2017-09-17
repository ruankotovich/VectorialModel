#include "docollection.hpp"

void Docollection::operator<<(Document& document)
{
  documentsById.insert({ document.id, document });

  // retrieves and insert all the words of this document on the documents by word map
  for (auto& word : document.wordAmount) {
    this->documentsByWord[word.first].emplace(document.id);
  }
}

// IDF(t) = log_e(Total number of documents / Number of documents with term t in it).
void Docollection::calculateIDF()
{
  for (auto& word : documentsByWord) {
    itfMap.emplace(std::piecewise_construct, std::forward_as_tuple(word.first), std::forward_as_tuple(log(((float)documentsById.size() / (float)word.second.size()))));
  }
}

void Docollection::calculateTFIDF()
{
  for (auto& document : documentsById) {
    for (auto& word : document.second.tfMap) {
      tfidfMap[document.first].emplace(
        std::piecewise_construct,
        std::forward_as_tuple(word.first),
        std::forward_as_tuple(word.second * itfMap[word.first])
      );
    }
  }
}
