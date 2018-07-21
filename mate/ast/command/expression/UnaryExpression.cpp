#include "UnaryExpression.hpp"

namespace mate
{
// UnaryExpression ----------------------

const std::string UnaryExpression::VALUATION_NULL = "<undefined>";

UnaryExpression::~UnaryExpression(){}

UnaryExpression::UnaryExpression(std::string varKey) : varKey(varKey), exp(NULL) {}

UnaryExpression::UnaryExpression(std::string varKey, Expression *exp) 
    : varKey(varKey), exp(exp) {}

JsonNode *UnaryExpression::execute(Interpreter* interpreter){
    JsonNode *node = exp->execute(interpreter);
    interpreter->context()->set(varKey, node);
    return node;
}

} // namespace mate