#include <iostream>
#include <iostream>
#include <fstream>

#include "../../mate/script/ScriptScanner.hpp"
#include "../../mate/script/ScriptParser.hpp"
#include "../../mate/script/ScriptInterpreter.hpp"

#include "../../mate/ast/Json.hpp"

using namespace mate;
using namespace std;

int main(int argc, char **argv) {
    ifstream inStream;
    ofstream outStream;

    JsonStringNode jsStr1("Pierre");
    JsonStringNode jsStr2("Cedric");
    JsonStringNode jsStr3("Cecile");
    JsonStringNode jsStr4("Mate programming lang");
    JsonStringNode jsStr5("test");
    JsonNumberNode jsNum1(132);
    JsonNumberNode jsNum2(150);
    JsonBoolNode   jsBool1(true);
    JsonBoolNode   jsBool2(false);

    inStream.open ("test/script/Family.ms");
    outStream.open ("test/script/output/Family.out");
    
    ScriptInterpreter i(&inStream, &outStream);
    i.context()->put("var1",&jsStr1);
    i.context()->put("var2",&jsStr2);
    i.context()->put("var3",&jsStr3);
    i.context()->put("var4",&jsStr4);
    i.context()->put("var5",&jsStr5);
    i.context()->put("var6",&jsNum1);
    i.context()->put("var7",&jsNum2);
    i.context()->put("var8",&jsBool1);
    i.context()->put("var9",&jsBool2);
    int res = i.parse();

    inStream.close();
    outStream.close();

    cout << "Parse complete. Result = " << res << endl;
    return 0;
}
