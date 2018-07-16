#include "BoolExpression.hpp"

namespace mate
{
// BoolExpression ----------------------
BoolExpression *BoolExpression::BOOL_EXP_TRUE = new BoolExpression(true);
BoolExpression *BoolExpression::BOOL_EXP_FALSE = new BoolExpression(false);

BoolExpression::BoolExpression(JsonBoolNode *op1)
    : op1(op1) {}
BoolExpression::BoolExpression(bool v) {
    op1 = new JsonBoolNode(v);
}
BoolExpression::BoolExpression(){}

BoolExpression::~BoolExpression(){}

JsonBoolNode *BoolExpression::executeAsBool(Interpreter* interpreter) {
    return op1;
}

JsonNode* BoolExpression::execute(Interpreter* interpreter){
    return executeAsBool(interpreter);
}

void BoolExpression::val1(bool v1){
    op1->val(v1);
}

// UnaryBoolExp ----------------------

UnaryBoolExp::UnaryBoolExp(UnaryBoolExpType expType, BoolExpression *op)
    : op1(op), expType(expType) {}

UnaryBoolExp::~UnaryBoolExp() {}

    JsonBoolNode *UnaryBoolExp::executeAsBool(Interpreter* interpreter){
        bool v1 = op1->executeAsBool(interpreter)->val();
        bool v;
        switch (expType)
        {
        case EXP_UN_BOOL_NOT:
            v = !v1;
            break;
        }
        val1(v1);
        JsonBoolNode *r = new JsonBoolNode(v);
        return r;
    }

    JsonNode* UnaryBoolExp::execute(Interpreter* interpreter){
        return executeAsBool(interpreter);
    }

    void UnaryBoolExp::val1(double v1){
        op1->val1(v1);
    }

    // BinaryBoolExp ----------------------

    BinaryBoolExp::BinaryBoolExp(BinaryBoolExpType expType, BoolExpression* op1, BoolExpression* op2)
        : op1(op1), op2(op2), expType(expType) {}

    BinaryBoolExp::~BinaryBoolExp() {}

    JsonBoolNode* BinaryBoolExp::executeAsBool(Interpreter* interpreter){
        bool v1 = op1->executeAsBool(interpreter)->val();
        bool v2 = op2->executeAsBool(interpreter)->val();
        bool v;
        
        switch (expType)
        {
        case EXP_BI_BOOL_ASSIGN:
            v = (v1 = v2);
            break;
        case EXP_BI_BOOL_ASSIGN_AND:
            v = (v1 &= v2);
            break;
        case EXP_BI_BOOL_ASSIGN_OR:
            v = (v1 |= v2);
            break;
        case EXP_BI_BOOL_ASSIGN_XOR:
            v = (v1 ^= v2);
            break;
        case EXP_BI_BOOL_AND:
            v = (v1 & v2);
            break;
        case EXP_BI_BOOL_OR:
            v = (v1 | v2);
            break;
        case EXP_BI_BOOL_XOR:
            v = v1 ^ v2;
            break;
        case EXP_BI_BOOL_UNDEFINED:
            v = false;
            break;
        }
        val1(v1);
        JsonBoolNode* r = new JsonBoolNode(v);
        return r;
    }

    JsonNode *BinaryBoolExp::execute(Interpreter* interpreter){
        return executeAsBool(interpreter);
    }

    void BinaryBoolExp::val1(double v1){
        op1->val1(v1);
    }

    void BinaryBoolExp::val2(bool v2){
        op2->val1(v2);
    }

} // namespace mate