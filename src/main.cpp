#include "docollection.hpp"
#include "parser.hpp"
#include <queue>
using namespace std;

int main()
{
    Parser parser;
    Docollection collection;
    std::queue<string> documentQueue;

    documentQueue.push("cfc/cf74");
    documentQueue.push("cfc/cf75");
    documentQueue.push("cfc/cf76");
    documentQueue.push("cfc/cf77");
    documentQueue.push("cfc/cf78");
    documentQueue.push("cfc/cf79");

    while (!documentQueue.empty()) {

        parser.setFile(documentQueue.front());
        documentQueue.pop();

        Document* document = parser.parseNext();

        while (document) {
            if (document->id == -1) {
                break;
            }
            document->calculateTF();
            collection += document;
            document = parser.parseNext();
        }
        collection.calculateIDF();
        collection.calculateTFIDF();

        // for (auto& document : collection.tfidfMap) {
        //     auto& wordSet = document.second;
        //     std::cout << "--- Document # " << document.first << '\n';
        //     for (auto& wordAndTFIDF : wordSet) {
        //         std::cout << wordAndTFIDF.first << " -> " << wordAndTFIDF.second << '\n';
        //     }
        // }
    }
}
