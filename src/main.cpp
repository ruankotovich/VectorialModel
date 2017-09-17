#include "parser.hpp"

using namespace std;

int main()
{
    Parser parser;
    parser.setFile("cfc/cf74");

    Document document = parser.parseNext();
    while(document.id != -1) {
        cout << document.id << endl;
        document = parser.parseNext();
    }
}
