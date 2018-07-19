#include "ArrayExpression.hpp"

namespace mate
{
// ArrayExpression ----------------------


ArrayExpression::ArrayExpression(std::vector<Expression *> vals) 
    : values(vals){}

ArrayExpression::ArrayExpression(){}

ArrayExpression::~ArrayExpression(){}

void ArrayExpression::push(Expression *val){
    values.push_back(val);
}

JsonArrayNode *ArrayExpression::executeAsArray(Interpreter* interpreter) {
    int i, loopLimit = values.size();
    JsonArrayNode* node= new JsonArrayNode();
    std::ostringstream s;
    for (i = 0; i < loopLimit; i++){
        node->push(values[i]->execute(interpreter));
    }
    return node;
}

JsonNode* ArrayExpression::execute(Interpreter* interpreter){
    return executeAsArray(interpreter);
}

} // namespace mate