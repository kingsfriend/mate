#include "../../mate/Json.hpp"
#include "../../mate/BoolExpression.hpp"
#include "../../mate/DateExpression.hpp"
#include "../../mate/NumExpression.hpp"
#include "../../mate/StringExpression.hpp"

#include <iostream>
#include <sstream>
#include <string>

using namespace mate;
int main(int argc, char const *argv[])
{

    JsonStringNode jsString("test");
    JsonNumberNode jsNumber1(132);
    JsonNumberNode jsNumber2(150);
    JsonNumberNode* sumResult;
    JsonBoolNode jsBool(true);
    JsonObjectNode jsObject;
    JsonObjectNode jsObject1;
    JsonArrayNode jsArray;
    JsonArrayNode jsArray1;

    std::string now(JsonDateNode::now().toString());
    std::cout << "Now : " << now << "\n";

    std::string str("bonjour");
    std::string reverse;
    reverse = JsonStringNode::reverse(str);
    std::cout << "Reverse : " << str << " => " << reverse << "\n";

    NumExpression numExp1(&jsNumber1);
    NumExpression numExp2(100);

    BinaryNumberExp sum(EXP_BI_NUM_ADD, &numExp1, &numExp2);

    sumResult = sum.executeAsNum();

    jsObject1.push("num1", &jsNumber1);
    jsObject1.push("num2", &jsNumber2);
    jsObject1.push("sum", sumResult);
    jsObject1.push("str", &jsString);
    jsObject1.push("bool", &jsBool);

    jsObject.push("num", &jsNumber1);
    jsObject.push("str", &jsString);
    jsObject.push("obj", &jsObject1);
    jsObject.push("arry", &jsArray1);

    jsArray.push(&jsBool);
    jsArray.push(&jsNumber1);
    jsArray.push(&jsString);
    jsArray.push(&jsObject);
    jsArray.push(&jsArray1);

    std::cout << "jsString : " << jsString.toString() << "\n";
    std::cout << "jsObject : " << jsObject.toString() << "\n";
    std::cout << "jsObject1 : " << jsObject1.toString() << "\n";
    std::cout << "jsObject1[str] : " << jsObject1.get("str")->toString() << "\n";
    std::cout << "jsArray : " << jsArray.toString() << "\n";
    std::cout << "jsArray[2] : " << jsArray.get(2)->toString() << "\n";
    return 0;
}
