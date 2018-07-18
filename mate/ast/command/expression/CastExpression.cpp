#include "CastExpression.hpp"

namespace mate
{
// CastExpression ----------------------

CastExpression::~CastExpression(){}

CastExpression::CastExpression(NodeType toType, JsonNode *fromNode)
    :  toType(toType), fromNode(fromNode) {}

JsonNode *CastExpression::execute(Interpreter *interpreter){
    JsonNode *node;
    switch (toType)
    {
    case Bool:
        node = JsonBoolNode::doCast(fromNode);
        break;
    case Number:
        node = JsonNumberNode::doCast(fromNode);
        break;
    case String:
        node = JsonStringNode::doCast(fromNode);
        break;
    case Date:
        node = JsonDateNode::doCast(fromNode);
        break;
    case Object:
        node = JsonObjectNode::doCast(fromNode);
        break;
    case Array:
        node = JsonArrayNode::doCast(fromNode);
        break;
    default:
        break;
    }
    return node;
}

} // namespace mate