#include "docollection.hpp"
#include "parser.hpp"

using namespace std;

int main()
{
    Parser parser;
    parser.setFile("cfc/test");
    Docollection collection;

    Document* document = parser.parseNext();

    while (document) {
        // cout << document->id << " " << document->totalWordsCount << endl;
        if (document->id == -1) {
            break;
        }
        document->calculateTF();
        collection += document;
        document = parser.parseNext();
    }
    collection.calculateIDF();
    collection.calculateTFIDF();

    for (auto& document : collection.tfidfMap) {
        auto& wordSet = document.second;
        std::cout << "--- Document # " << document.first << '\n';
        for (auto& wordAndTFIDF : wordSet) {
            std::cout << wordAndTFIDF.first << " -> " << wordAndTFIDF.second << '\n';
        }
    }
}
