#include "StringExpression.hpp"

namespace mate
{
// StringExpression ----------------------

StringExpression::StringExpression(JsonStringNode *op1)
    : op1(op1) {}
StringExpression::StringExpression(std::string v) {
    op1 = new JsonStringNode(v);
}
StringExpression::StringExpression(){}

StringExpression::~StringExpression(){}

JsonStringNode *StringExpression::executeAsString(Interpreter* interpreter) {
    return op1;
}

JsonNode* StringExpression::execute(Interpreter* interpreter){
    return executeAsString(interpreter);
}

void StringExpression::val1(std::string v1){
    op1->val(v1);
}

} // namespace mate