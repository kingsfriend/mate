#include "AssignmentExpression.hpp"

namespace mate
{
// AssignmentExpression ----------------------

const std::string AssignmentExpression::VALUATION_NULL = "<undefined>";

AssignmentExpression::~AssignmentExpression(){}

AssignmentExpression::AssignmentExpression(std::string varKey) : varKey(varKey), exp(NULL) {}

AssignmentExpression::AssignmentExpression(std::string varKey, Expression *exp) 
    : varKey(varKey), exp(exp) {}

JsonNode *AssignmentExpression::execute(Interpreter* interpreter){
    JsonNode *node = exp->execute(interpreter);
    interpreter->context()->set(varKey, node);
    return node;
}

} // namespace mate