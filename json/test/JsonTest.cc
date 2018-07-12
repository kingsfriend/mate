#include "../Json.hh"

#include <iostream>
#include <sstream>

using namespace json;
int main(int argc, char const *argv[])
{

    JsonStringNode jsString("test");
    JsonNumberNode jsNumber(18e+2);
    JsonObjectNode jsObject;
    JsonObjectNode jsObject1;
    JsonArrayNode jsArray;
    JsonArrayNode jsArray1;

    jsObject1.push("num", &jsNumber);
    jsObject1.push("str", &jsString);

    jsObject.push("num", &jsNumber);
    jsObject.push("str", &jsString);
    jsObject.push("obj", &jsObject1);
    jsObject.push("arry", &jsArray1);

    jsArray.push(&jsNumber);
    jsArray.push(&jsString);
    jsArray.push(&jsObject);
    jsArray.push(&jsArray1);

    std::cout << "jsString : " << jsString.toString() << "\n";
    std::cout << "jsNumber : " << jsNumber.toString() << "\n";
    std::cout << "jsObject : " << jsObject.toString() << "\n";
    std::cout << "jsObject1 : " << jsObject1.toString() << "\n";
    std::cout << "jsObject1[str] : " << jsObject1.get("str")->toString() << "\n";
    std::cout << "jsArray : " << jsArray.toString() << "\n";
    std::cout << "jsArray[2] : " << jsArray.get(2)->toString() << "\n";
    return 0;
}
