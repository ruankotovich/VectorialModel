#include "docollection.hpp"

void Docollection::operator+=(Document* document)
{
    documentsById.insert({ document->id, document });

    // retrieves and insert all the words of this document on the documents by word map
    for (auto& word : document->wordAmountOnDocument) {
        this->documentsByWord[word.first].emplace(document->id);
    }
}

// IDF(t) = log_e(Total number of documents / Number of documents with term t in it).
void Docollection::calculateIDF()
{
    for (auto& word : documentsByWord) {
        idfMap.emplace(std::piecewise_construct,
            std::forward_as_tuple(word.first),
            std::forward_as_tuple((log(((double)documentsById.size() / (double)word.second.size()))) + 1.0f));
    }
}

void Docollection::calculateTFIDF()
{
    for (auto& document : documentsById) {
        for (auto& word : document.second->tfMap) {
            tfidfMap[document.first].emplace(
                std::piecewise_construct,
                std::forward_as_tuple(word.first),
                std::forward_as_tuple(word.second * idfMap[word.first]));
        }
    }
}

void Docollection::clearLine(std::string& s)
{
    for (std::string::size_type i = 0; (i = s.find("-", i)) != std::string::npos;) {
        s.replace(i, 1, " ");
        ++i;
    }

    s.erase(std::remove_if(s.begin(), s.end(), [](char x) { return !(std::isalpha(x) || std::isspace(x)); }), s.end());
    std::transform(s.begin(), s.end(), s.begin(), ::tolower);
}

std::unordered_map<std::string, double> Docollection::calculateSpecificTFIDF(const Document* document)
{
    std::unordered_map<std::string, double> tfidfMap;

    for (auto& word : document->tfMap) {
        tfidfMap.emplace(word.first, word.second * idfMap[word.first]);
    }

    return tfidfMap;
}

double Docollection::calculateSimilarity(const Query& query, const Document* document)
{

    /* build a new "document" for the query */
    Document queryDocument;
    std::string word;

    std::stringstream strstream(query.query);
    while (std::getline(strstream, word, ' ')) {
        clearLine(word);
        queryDocument.addWord(word);
    }

    /* calculate the TF for the "query document" */
    queryDocument.calculateTF();

    auto&& currentQueryTFIDF = calculateSpecificTFIDF(&queryDocument);
    auto& currentDocumentTFIDF = this->tfidfMap[document->id];

    double wid = 0, wiq = 0, sumWid2 = 0, sumWiq2 = 0;
    double sumWidXWiq = 0;

    /* verify which set is the smaller */
    // std::cout << " --- Calculating query for Document # " << document->id << "\n";
    if (currentQueryTFIDF.size() < currentDocumentTFIDF.size()) {

        for (auto& elementOnQuery : currentQueryTFIDF) {
            auto elementOnDocument = currentDocumentTFIDF[elementOnQuery.first];
            wid = elementOnDocument;
            wiq = elementOnQuery.second;
            sumWid2 += pow(wid, 2.0f);
            sumWiq2 += pow(wiq, 2.0f);
            sumWidXWiq += wid * wiq;
            // std::cout << "Current state : (wid : " << wid << ", wiq : " << wiq << ", sumWid2 : " << sumWid2 << ", sumWiq2 : " << sumWiq2 << ", sumWidXWiq : " << sumWidXWiq << ")\n";
        }

    } else {
        for (auto& elementOnDocument : currentDocumentTFIDF) {
            auto elementOnQuery = currentQueryTFIDF[elementOnDocument.first];
            wid = elementOnDocument.second;
            wiq = elementOnQuery;
            sumWid2 += pow(wid, 2.0f);
            sumWiq2 += pow(wiq, 2.0f);
            sumWidXWiq += wid * wiq;
            // std::cout << "Current state : (wid : " << wid << ", wiq : " << wiq << ", sumWid2 : " << sumWid2 << ", sumWiq2 : " << sumWiq2 << ", sumWidXWiq : " << sumWidXWiq << ")\n";
        }
    }

    // std::cout << "\nDocument # " << document->id << ": " << sumWidXWiq << " / "
    //           << "(" << sqrt(sumWid2) << "*" << sqrt(sumWiq2) << ")"
    //           << "\n\n";

    double downSide = (sqrt(sumWid2) * sqrt(sumWiq2));
    return downSide > 0 ? (sumWidXWiq / downSide) : 0.0f;
}

std::priority_queue<std::pair<int, double>, std::vector<std::pair<int, double>>, QueryComparator_t> Docollection::performQuery(const Query& query)
{
    std::priority_queue<std::pair<int, double>, std::vector<std::pair<int, double>>, QueryComparator_t> responseList;

    for (auto& document : documentsById) {
        responseList.push({ document.first, calculateSimilarity(query, document.second) });
    }

    return responseList;
}