#include <iostream>
#include <iostream>
#include <fstream>

#include "../../mate/script/ScriptScanner.hpp"
#include "../../mate/script/ScriptParser.hpp"
#include "../../mate/script/ScriptInterpreter.hpp"

using namespace mate;
using namespace std;

int main(int argc, char **argv) {
    ifstream inStream;
    ofstream outStream;
    
    inStream.open ("test/script/Family.ms");
    outStream.open ("test/script/output/Family.out");
    
    ScriptInterpreter i(&inStream, &outStream);
    int res = i.parse();

    inStream.close();
    outStream.close();

    cout << "Parse complete. Result = " << res << endl;
    return 0;
}
