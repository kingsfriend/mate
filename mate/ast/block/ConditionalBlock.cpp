#include "ConditionalBlock.hpp"

namespace mate
{
// ConditionExpression ----------------------

ConditionExpression *ConditionExpression::TRUE_CONDITION = new ConditionExpression(BoolExpression::BOOL_EXP_TRUE);
ConditionExpression *ConditionExpression::FALSE_CONDITION = new ConditionExpression(BoolExpression::BOOL_EXP_FALSE);

ConditionExpression::ConditionExpression(BoolExpression *boolExp){
    this->boolExp = boolExp;
    this->type = EXP_BI_BOOL_UNDEFINED;
    this->condExp = NULL;
}
ConditionExpression::ConditionExpression(BoolExpression *boolExp, BinaryBoolExpType type, ConditionExpression *condExp){
    this->boolExp = boolExp;
    this->type = type;
    this->condExp = condExp;
}
ConditionExpression::~ConditionExpression(){}

JsonBoolNode *ConditionExpression::executeAsBool(){
    bool v1 = boolExp->executeAsBool()->val();
    bool v2 = false;
    bool v;
    JsonBoolNode* r;

    if(condExp!=NULL){
        v2 = condExp->executeAsBool()->val();
    }

    switch (type)
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
        r = new JsonBoolNode(v1);
        return r;
    }
    val1(v1);
    r = new JsonBoolNode(v);
    return r;
}

// ConditionalBlock ----------------------

ConditionalBlock::ConditionalBlock(ConditionExpression *condition) : condition(condition){}
ConditionalBlock::~ConditionalBlock(){}

bool ConditionalBlock::valuateCondition(){
    if (condition != NULL){
        return condition->executeAsBool();
    }
    return false;
}

// IfBlock ----------------------

IfBlock::IfBlock(ConditionExpression *condition) : ConditionalBlock(condition) {}
IfBlock::~IfBlock(){}

JsonNode* IfBlock::execute(){
    if(valuateCondition()){
        int i;
        int loopLimit = commandes.size();
        for (i = 0; i < loopLimit; i++){
            commandes[i]->execute();
        }
    }else if(nextBlok!=NULL && nextBlok->valuateCondition())
    {
        return nextBlok->execute();
    }
    return NULL;
}


} // namespace mate