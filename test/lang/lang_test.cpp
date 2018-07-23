#include <iostream>
#include <iostream>
#include <fstream>

#include "../../mate/lang/LangScanner.hpp"
#include "../../mate/lang/LangParser.hpp"
#include "../../mate/lang/LangInterpreter.hpp"

#include "../../mate/ast/Json.hpp"

using namespace mate;
using namespace std;

int main(int argc, char **argv) {
    ifstream inStream;
    ofstream outStream;

    inStream.open("test/lang/App.mc");
    outStream.open ("test/lang/output/App.out");
    
    LangInterpreter i(&inStream, &outStream);
    int res = i.parse();

    inStream.close();
    outStream.close();

    cout << "LANG Parse complete. Result = " << res << endl;
    return 0;
}
