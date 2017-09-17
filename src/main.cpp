#include "docollection.hpp"
#include "parser.hpp"

using namespace std;

int main()
{
    Parser parser;
    parser.setFile("cfc/cf74");
    Docollection collection;

    Document* document = parser.parseNext();

    while (document) {
        if (document->id == -1) {
            break;
        }
        collection += document;
        cout << document->id << " " << document->totalWordsCount << endl;
        document = parser.parseNext();
    }
}
