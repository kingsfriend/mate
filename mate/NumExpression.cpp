#include "NumExpression.hpp"

namespace mate
{
// NumExpression ----------------------

NumExpression::NumExpression(JsonNumberNode *op1)
    : op1(op1) {}
NumExpression::NumExpression(double d) {
    op1 = new JsonNumberNode(d);
}
NumExpression::NumExpression(){}

NumExpression::~NumExpression(){}

JsonNumberNode *NumExpression::executeAsNum() {
    return op1;
}

JsonNode* NumExpression::execute(){
    return executeAsNum();
}
void NumExpression::update(){
    executeAsNum();
}

// UnaryNumberExp ----------------------

UnaryNumberExp::UnaryNumberExp(UnaryNumberExpType expType, NumExpression *op)
    : op1(op), expType(expType) {}

UnaryNumberExp::~UnaryNumberExp() {}

    JsonNumberNode *UnaryNumberExp::executeAsNum(){
        double v = op1->executeAsNum()->val();
        switch (expType)
        {
        case EXP_UN_NUM_INC:
            v++;
            break;
        case EXP_UN_NUM_DEC:
            v--;
            break;
        }
        JsonNumberNode *r = new JsonNumberNode(v);
        return r;
    }

    JsonNode* UnaryNumberExp::execute(){
        return executeAsNum();
    }

    void UnaryNumberExp::update(){
        executeAsNum();
    }

    // BinaryNumberExp ----------------------

    BinaryNumberExp::BinaryNumberExp(BinaryNumberExpType expType, NumExpression* op1, NumExpression* op2)
        : op1(op1), op2(op2), expType(expType) {}

    BinaryNumberExp::~BinaryNumberExp() {}

    JsonNumberNode* BinaryNumberExp::executeAsNum(){
        double v1 = op1->executeAsNum()->val();
        double v2 = op2->executeAsNum()->val();
        double v;
        
        switch (expType)
        {
        case EXP_BI_NUM_MUL:
            v = v1 * v2;
            break;
        case EXP_BI_NUM_DIV:
            v = v1 / v2;
            break;
        case EXP_BI_NUM_MOD:
            v = std::fmod(v1, v2);
            break;
        case EXP_BI_NUM_ADD:
            v = v1 + v2;
            break;
        case EXP_BI_NUM_SUB:
            v = v1 - v2;
            break;
        }
        JsonNumberNode* r = new JsonNumberNode(v);
        return r;
    }

    JsonNode *BinaryNumberExp::execute()
    {
        return executeAsNum();
    }

    void BinaryNumberExp::update()
    {
        executeAsNum();
    }

    // BinaryNumberExp ----------------------

} // namespace mate