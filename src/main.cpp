#include "docollection.hpp"
#include "parser.hpp"
#include <cstring>
#include <queue>
using namespace std;

int main(int argc, char* argv[])
{
    Parser parser;
    Docollection collection;
    std::queue<string> documentQueue;

    for (int i = 1; i < argc; i++) {
        documentQueue.push(argv[i]);
    }

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
    }

    // for (auto& document : collection.tfidfMap) {
    //     auto& wordSet = document.second;
    //     std::cout << "--- Document # " << document.first << '\n';
    //     for (auto& wordAndTFIDF : wordSet) {
    //         std::cout << wordAndTFIDF.first << " -> " << wordAndTFIDF.second << '\n';
    //     }
    // }

    parser.setFile("cfc/query");
    Query q = parser.nextQuery();
    while (q.id != -1) {
        std::cout << q.id << " - \"" << q.query << "\"\n";
        q = parser.nextQuery();
    }
}
