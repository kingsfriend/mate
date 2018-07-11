#include "Json.hh"

#include <iostream>
#include <sstream>

using namespace json;
int main(int argc, char const *argv[])
{
    std::vector<JsonNode*> values;

    JsonStringNode jsString("test");
    JsonNumberNode jsNumber(18e+2);
    JsonObjectNode jsObject;
    JsonObjectNode jsObject1;
    JsonObjectNode jsObject2(json::Array);

    jsObject1.push(jsNumber.usingKey("num"));
    jsObject1.push(jsString.usingKey("str"));

    jsObject.push(jsNumber.usingKey("num"));
    jsObject.push(jsString.usingKey("str"));
    jsObject.push(jsObject1.usingKey("obj"));
    
    jsObject2.push(&jsObject1);
    jsObject.push(jsObject2.usingKey("array"));

    std::cout << jsString.toString() << "\n";
    std::cout << jsNumber.toString() << "\n";
    std::cout << jsObject.toString() << "\n";
    std::cout << jsObject1.toString() << "\n";
    std::cout << jsObject2.toString() << "\n";
    return 0;
}
