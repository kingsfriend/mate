#include "DateExpression.hpp"

namespace mate
{
// DateExpression ----------------------

DateExpression::DateExpression(JsonDateNode *op1)
    : op1(op1) {}
DateExpression::DateExpression(time_t v) {
    op1 = new JsonDateNode(v);
}
DateExpression::DateExpression(){}

DateExpression::~DateExpression(){}

JsonDateNode *DateExpression::executeAsDate(Interpreter* interpreter) {
    return op1;
}

JsonNode* DateExpression::execute(Interpreter* interpreter){
    return executeAsDate(interpreter);
}

void DateExpression::val1(time_t v1){
    op1->val(v1);
}

// UnaryDateExp ----------------------

} // namespace mate