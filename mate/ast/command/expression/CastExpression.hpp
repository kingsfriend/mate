#ifndef MATE_CAST_EXPRESSION_HH
    #define MATE_CAST_EXPRESSION_HH

#include "PrimaryExpression.hpp"

namespace mate
{

    class CastExpression : public PrimaryExpression
    {
    private:
        NodeType toType;
        JsonNode *fromNode;

    public:
        ~CastExpression();
        CastExpression(NodeType toType, JsonNode* fromNode);

        static const CommandType CMD_TYPE = CMD_EXP_PRIM_CAST;
        static const PrimaryExpressionType PRIM_TYPE = PRIM_CAST;
        JsonNode *execute(Interpreter *interpreter);
    };
    
} // mate

#endif //MATE_CAST_EXPRESSION_HH
