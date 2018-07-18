#include "ArrayExpression.hpp"

namespace mate
{
// ArrayExpression ----------------------

ArrayExpression::ArrayExpression(JsonArrayNode *value)
    : value(value) {}
ArrayExpression::ArrayExpression(std::vector<JsonNode *> v) {
    value = new JsonArrayNode(v);
}
ArrayExpression::ArrayExpression(){
    value = new JsonArrayNode();
}

ArrayExpression::~ArrayExpression(){}

JsonArrayNode *ArrayExpression::executeAsString(Interpreter* interpreter) {
    return value;
}

JsonNode* ArrayExpression::execute(Interpreter* interpreter){
    return executeAsString(interpreter);
}

void ArrayExpression::val(std::vector<JsonNode *> v1){
    value->val(v1);
}

} // namespace mate