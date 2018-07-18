#include "NumExpression.hpp"

namespace mate
{
// NumExpression ----------------------

NumExpression::NumExpression(JsonNumberNode *op1)
    : op1(op1) {}
NumExpression::NumExpression(double v) {
    op1 = new JsonNumberNode(v);
}
NumExpression::NumExpression(){}

NumExpression::~NumExpression(){}

JsonNumberNode *NumExpression::executeAsNum(Interpreter* interpreter) {
    return op1;
}

JsonNode* NumExpression::execute(Interpreter* interpreter){
    return executeAsNum(interpreter);
}

void NumExpression::val1(double v1){
    op1->val(v1);
}

} // namespace mate