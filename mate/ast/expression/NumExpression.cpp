#include "NumExpression.hpp"

namespace mate
{
// NumExpression ----------------------

NumExpression::NumExpression(JsonNumberNode *op1)
    : op1(op1) {}
NumExpression::NumExpression(double v) {
    op1 = new JsonNumberNode(v);
}
NumExpression::NumExpression(){}

NumExpression::~NumExpression(){}

JsonNumberNode *NumExpression::executeAsNum() {
    return op1;
}

JsonNode* NumExpression::execute(){
    return executeAsNum();
}

void NumExpression::val1(double v1){
    op1->val(v1);
}

// UnaryNumberExp ----------------------

UnaryNumberExp::UnaryNumberExp(UnaryNumberExpType expType, NumExpression *op)
    : op1(op), expType(expType) {}

UnaryNumberExp::~UnaryNumberExp() {}

    JsonNumberNode *UnaryNumberExp::executeAsNum(){
        double v1 = op1->executeAsNum()->val();
        double v;
        switch (expType)
        {
        case EXP_UN_NUM_PREF_PLUS:
            v = v1;
            break;
        case EXP_UN_NUM_PREF_MINUS:
            v = -v1;
            break;
        case EXP_UN_NUM_POST_INC:
            v = v1++;
            break;
        case EXP_UN_NUM_POST_DEC:
            v = v1--;
            break;
        case EXP_UN_NUM_PREF_INC:
            v = ++v1;
            break;
        case EXP_UN_NUM_PREF_DEC:
            v = --v1;
            break;
        }
        val1(v1);
        JsonNumberNode *r = new JsonNumberNode(v);
        return r;
    }

    JsonNode* UnaryNumberExp::execute(){
        return executeAsNum();
    }

    void UnaryNumberExp::val1(double v1){
        op1->val1(v1);
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
        case EXP_BI_NUM_ASSIGN:
            v = (v1 = v2);
            break;
        case EXP_BI_NUM_ASSIGN_MUL:
            v = (v1 *= v2);
            break;
        case EXP_BI_NUM_ASSIGN_DIV:
            v = (v1 /= v2);
            break;
        case EXP_BI_NUM_ASSIGN_ADD:
            v = (v1 += v2);
            break;
        case EXP_BI_NUM_ASSIGN_SUB:
            v = (v1 -= v2);
            break;
        case EXP_BI_NUM_ASSIGN_MOD:
            v = (v1 = std::fmod(v1, v2));
            break;
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
        val1(v1);
        JsonNumberNode* r = new JsonNumberNode(v);
        return r;
    }

    JsonNode *BinaryNumberExp::execute(){
        return executeAsNum();
    }

    void BinaryNumberExp::val1(double v1){
        op1->val1(v1);
    }

    void BinaryNumberExp::val2(double v2){
        op2->val1(v2);
    }

} // namespace mate