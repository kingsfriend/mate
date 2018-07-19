#include "ObjectExpression.hpp"

namespace mate
{
// ObjectExpression ----------------------

ObjectExpression::ObjectExpression(std::map<const std::string, Expression *> vals)
    : values(vals) {}

ObjectExpression::ObjectExpression(){}

ObjectExpression::~ObjectExpression(){}

JsonObjectNode *ObjectExpression::executeAsObject(Interpreter* interpreter) {
    JsonObjectNode* node= new JsonObjectNode();
    std::map<const std::string, Expression *>::iterator it;
    for (it = values.begin(); it != values.end(); ++it){
        node->push(it->first, it->second->execute(interpreter));
    }
    return node;
}

JsonNode* ObjectExpression::execute(Interpreter* interpreter){
    return executeAsObject(interpreter);
}
void ObjectExpression::push(const std::string &k, Expression *val){
    values.insert(make_pair(k, val));
}

} // namespace mate