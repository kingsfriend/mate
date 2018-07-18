#include "ObjectExpression.hpp"

namespace mate
{
// ObjectExpression ----------------------

ObjectExpression::ObjectExpression(JsonObjectNode *value)
    : value(value) {}
ObjectExpression::ObjectExpression(std::map<const std::string, JsonNode *> v) {
    value = new JsonObjectNode(v);
}
ObjectExpression::ObjectExpression(){
    value = new JsonObjectNode();
}

ObjectExpression::~ObjectExpression(){}

JsonObjectNode *ObjectExpression::executeAsString(Interpreter* interpreter) {
    return value;
}

JsonNode* ObjectExpression::execute(Interpreter* interpreter){
    return executeAsString(interpreter);
}

void ObjectExpression::val(std::map<const std::string, JsonNode *> v1){
    value->val(v1);
}

} // namespace mate