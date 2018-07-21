#include <iostream>
#include <iostream>
#include <fstream>

#include "../../mate/json/JsonScanner.hpp"
#include "../../mate/json/JsonParser.hpp"
#include "../../mate/json/JsonInterpreter.hpp"

#include "../../mate/ast/Json.hpp"

using namespace mate;
int main(int argc, char const *argv[])
{
    ifstream inStream;
    inStream.open("test/json/test_glossary.json");

    JsonInterpreter i(&inStream);
    int res = i.parse();

    inStream.close();

    cout << "test_glossary.json content" << endl;
    cout << "-------------------------------------" << endl;
    cout << i.getObject().toString() << endl;
    cout << "-------------------------------------" << endl;
    cout << "JSON Parse complete. Result = " << res << endl;

    return 0;
}
