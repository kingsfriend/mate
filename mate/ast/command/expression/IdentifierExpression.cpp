#include "IdentifierExpression.hpp"

namespace mate
{
// IdentifierExpression ----------------------

IdentifierExpression::IdentifierExpression(std::string identifier)
    : identifier(identifier) {}

IdentifierExpression::IdentifierExpression(){}

IdentifierExpression::~IdentifierExpression(){}


JsonNode* IdentifierExpression::execute(Interpreter* interpreter){
    JsonNode *val = interpreter->context()->get(identifier);
    return val;
}

void IdentifierExpression::val(std::string v){
    identifier = v;
}

} // namespace mate