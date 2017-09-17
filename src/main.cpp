#include "docollection.hpp"
#include "parser.hpp"

using namespace std;

int main()
{
    Parser parser;
    parser.setFile("cfc/cf74");
    Docollection collection;

    Document* document = parser.parseNext();
    while (document->id != -1) {
        cout << document->id << " " << document->totalWordsCount << endl;
        collection += document = parser.parseNext();
    }
}
