#include "StringExpression.hpp"

namespace mate
{
// StringExpression ----------------------

StringExpression::StringExpression(JsonStringNode *op1)
    : op1(op1) {}
StringExpression::StringExpression(std::string v) {
    op1 = new JsonStringNode(v);
}
StringExpression::StringExpression(){}

StringExpression::~StringExpression(){}

JsonStringNode *StringExpression::executeAsString() {
    return op1;
}

JsonNode* StringExpression::execute(){
    return executeAsString();
}
void StringExpression::update(){
    executeAsString();
}

void StringExpression::val1(std::string v1){
    op1->val(v1);
}

// UnaryStringExp ----------------------

UnaryStringExp::UnaryStringExp(UnaryStringExpType expType, StringExpression *op)
    : op1(op), expType(expType) {}

UnaryStringExp::~UnaryStringExp() {}

    JsonStringNode *UnaryStringExp::executeAsString(){
        std::string v1 = op1->executeAsString()->val();
        std::string v;
        switch (expType)
        {
        case EXP_UN_STR_PREF_PLUS:
            v = v1;
            break;
        case EXP_UN_STR_PREF_MINUS:
            v = JsonStringNode::reverse(v1);
            break;
        }
        val1(v1);
        JsonStringNode *r = new JsonStringNode(v);
        return r;
    }

    JsonNode* UnaryStringExp::execute(){
        return executeAsString();
    }

    void UnaryStringExp::update(){
        executeAsString();
    }

    void UnaryStringExp::val1(std::string v1){
        op1->val1(v1);
    }

    // BinaryStringExp ----------------------

    BinaryStringExp::BinaryStringExp(BinaryStringExpType expType, StringExpression* op1, StringExpression* op2)
        : op1(op1), op2(op2), expType(expType) {}

    BinaryStringExp::~BinaryStringExp() {}

    JsonStringNode* BinaryStringExp::executeAsString(){
        std::string v1 = op1->executeAsString()->val();
        std::string v2 = op2->executeAsString()->val();
        std::string v;
        
        switch (expType)
        {
        case EXP_BI_STR_ASSIGN:
            v = (v1 = v2);
            break;
        case EXP_BI_STR_ASSIGN_ADD:
            v = (v1 += v2);
            break;
        case EXP_BI_STR_ASSIGN_SUB:
            v = (v1 = JsonStringNode::reverse(v2));
            break;
        case EXP_BI_STR_ADD:
            v = v1 + v2;
            break;
        case EXP_BI_STR_SUB:
            v = v1 + JsonStringNode::reverse(v2);
            break;
        }
        val1(v1);
        JsonStringNode* r = new JsonStringNode(v);
        return r;
    }

    JsonNode *BinaryStringExp::execute(){
        return executeAsString();
    }

    void BinaryStringExp::update(){
        executeAsString();
    }

    void BinaryStringExp::val1(std::string v1){
        op1->val1(v1);
    }

    void BinaryStringExp::val2(std::string v2){
        op2->val1(v2);
    }

} // namespace mate