#include "DateExpression.hpp"

namespace mate
{
// DateExpression ----------------------

DateExpression::DateExpression(JsonDateNode *op1)
    : op1(op1) {}
DateExpression::DateExpression(time_t v) {
    op1 = new JsonDateNode(v);
}
DateExpression::DateExpression(){}

DateExpression::~DateExpression(){}

JsonDateNode *DateExpression::executeAsDate() {
    return op1;
}

JsonNode* DateExpression::execute(){
    return executeAsDate();
}
void DateExpression::update(){
    executeAsDate();
}

void DateExpression::val1(time_t v1){
    op1->val(v1);
}

// UnaryDateExp ----------------------

UnaryDateExp::UnaryDateExp(UnaryDateExpType expType, DateExpression *op)
    : op1(op), expType(expType) {}

UnaryDateExp::~UnaryDateExp() {}

    JsonDateNode *UnaryDateExp::executeAsDate(){
        time_t v1 = op1->executeAsDate()->val();
        time_t v;
        switch (expType)
        {
        case EXP_UN_DATE_PREF_PLUS:
            v = v1;
            break;
        case EXP_UN_DATE_PREF_MINUS:
            v = -v1;
            break;
        }
        val1(v1);
        JsonDateNode *r = new JsonDateNode(v);
        return r;
    }

    JsonNode* UnaryDateExp::execute(){
        return executeAsDate();
    }

    void UnaryDateExp::update(){
        executeAsDate();
    }

    void UnaryDateExp::val1(time_t v1){
        op1->val1(v1);
    }

    // BinaryDateExp ----------------------

    BinaryDateExp::BinaryDateExp(BinaryDateExpType expType, DateExpression* op1, DateExpression* op2)
        : op1(op1), op2(op2), expType(expType) {}

    BinaryDateExp::~BinaryDateExp() {}

    JsonDateNode* BinaryDateExp::executeAsDate(){
        time_t v1 = op1->executeAsDate()->val();
        time_t v2 = op2->executeAsDate()->val();
        time_t v;
        
        switch (expType)
        {
        case EXP_BI_DATE_ASSIGN:
            v = (v1 = v2);
            break;
        case EXP_BI_DATE_ASSIGN_ADD:
            v = (v1 += v2);
            break;
        case EXP_BI_DATE_ASSIGN_SUB:
            v = (v1 -= v2);
            break;
        case EXP_BI_DATE_ADD:
            v = v1 + v2;
            break;
        case EXP_BI_DATE_SUB:
            v = v1 - v2;
            break;
        }
        val1(v1);
        JsonDateNode* r = new JsonDateNode(v);
        return r;
    }

    JsonNode *BinaryDateExp::execute(){
        return executeAsDate();
    }

    void BinaryDateExp::update(){
        executeAsDate();
    }

    void BinaryDateExp::val1(time_t v1){
        op1->val1(v1);
    }

    void BinaryDateExp::val2(time_t v2){
        op2->val1(v2);
    }

} // namespace mate