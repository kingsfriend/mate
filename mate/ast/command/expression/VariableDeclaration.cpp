#include "VariableDeclaration.hpp"

namespace mate
{
// VariableDeclaration ----------------------

VariableDeclaration::~VariableDeclaration(){}

VariableDeclaration::VariableDeclaration(NodeType dataType, std::vector<JsonPair> vals) 
    : dataType(dataType), values(vals){}

void VariableDeclaration::push(JsonPair val){
    values.push_back(val);
}

JsonNode *VariableDeclaration::execute(Interpreter* interpreter) {
    int i, loopLimit = values.size();
    std::ostringstream s;
    for (i = 0; i < loopLimit; i++){
        const std::string key = values[i].key;
        JsonNode *val;
        Expression *exp = values[i].value;
        JsonNode *valuatedExp;
        if(exp != NULL){
            valuatedExp = exp->execute(interpreter);
        }
        switch (dataType)
        {
        case  Bool:
            val = JsonBoolNode::doCast(valuatedExp);
            break;
        case  Number:
            val = JsonNumberNode::doCast(valuatedExp);
            break;
        case  String:
            val = JsonStringNode::doCast(valuatedExp);
            break;
        case  Date:
            val = JsonDateNode::doCast(valuatedExp);
            break;
        case  Object:
            val = JsonObjectNode::doCast(valuatedExp);
            break;
        case  Array:
            val = JsonArrayNode::doCast(valuatedExp);
            break;
        default:
            break;
        }
        interpreter->context()->put(key, val);
    }
    return NULL;
}

} // namespace mate