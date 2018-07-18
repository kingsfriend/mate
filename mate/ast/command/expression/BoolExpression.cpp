#include "BoolExpression.hpp"

namespace mate
{
// BoolExpression ----------------------
BoolExpression *BoolExpression::BOOL_EXP_TRUE = new BoolExpression(true);
BoolExpression *BoolExpression::BOOL_EXP_FALSE = new BoolExpression(false);

BoolExpression::BoolExpression(JsonBoolNode *op1)
    : op1(op1) {}
BoolExpression::BoolExpression(bool v) {
    op1 = new JsonBoolNode(v);
}
BoolExpression::BoolExpression(){}

BoolExpression::~BoolExpression(){}

JsonBoolNode *BoolExpression::executeAsBool(Interpreter* interpreter) {
    return op1;
}

JsonNode* BoolExpression::execute(Interpreter* interpreter){
    return executeAsBool(interpreter);
}

void BoolExpression::val1(bool v1){
    op1->val(v1);
}

} // namespace mate