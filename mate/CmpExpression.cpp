#include "CmpExpression.hpp"

namespace mate
{
// CmpExpression ----------------------

CmpExpression::CmpExpression(CmpType op): op(op) {}

CmpExpression::~CmpExpression(){}

JsonNode* CmpExpression::execute(){
    return executeAsBool();
}

// CmpNumExp ----------------------

CmpNumExp::CmpNumExp(CmpType op, JsonNumberNode *p1, JsonNumberNode *p2)
    : CmpExpression(op), p1(p1), p2(p2) {}
CmpNumExp::CmpNumExp(CmpType op, double v1, double v2) : CmpExpression(op){
    p1 = new JsonNumberNode(v1);
    p2 = new JsonNumberNode(v2);
}

CmpNumExp::~CmpNumExp(){}

JsonBoolNode *CmpNumExp::executeAsBool()
{
    bool v;
    double v1 = p1->val();
    double v2 = p2->val();
    switch (op)
    {
    case CMP_OP_EQ:
        v = (v1 == v2);
        break;
    case CMP_OP_NE:
        v = (v1 != v2);
        break;
    case CMP_OP_LE:
        v = (v1 < v2);
        break;
    case CMP_OP_LE_OR_EQ:
        v = (v1 <= v2);
        break;
    case CMP_OP_GR:
        v = (v1 > v2);
        break;
    case CMP_OP_GR_OR_EQ:
        v = (v1 >= v2);
        break;
    }
    JsonBoolNode *r = new JsonBoolNode(v);
    return r;
}

void CmpNumExp::param1(double v1){
    p1->val(v1);
}

void CmpNumExp::param2(double v1){
    p2->val(v1);
}

// CmpBoolExp ----------------------

CmpBoolExp::CmpBoolExp(CmpType op, JsonBoolNode *p1, JsonBoolNode *p2)
    : CmpExpression(op), p1(p1), p2(p2) {}
CmpBoolExp::CmpBoolExp(CmpType op, bool v1, bool v2) : CmpExpression(op)
{
    p1 = new JsonBoolNode(v1);
    p2 = new JsonBoolNode(v2);
}

CmpBoolExp::~CmpBoolExp() {}

JsonBoolNode *CmpBoolExp::executeAsBool()
{
    bool v;
    bool v1 = p1->val();
    bool v2 = p2->val();
    switch (op)
    {
    case CMP_OP_EQ:
        v = (v1 == v2);
        break;
    case CMP_OP_NE:
        v = (v1 != v2);
        break;
    case CMP_OP_LE:
        v = (!v1 && v2);
        break;
    case CMP_OP_LE_OR_EQ:
        v = (v1 == v2) || (!v1 && v2);
        break;
    case CMP_OP_GR:
        v = (v1 && !v2);
        break;
    case CMP_OP_GR_OR_EQ:
        v = (v1 == v2) || (v1 && !v2);
        break;
    }
    JsonBoolNode *r = new JsonBoolNode(v);
    return r;
}

void CmpBoolExp::param1(bool v1)
{
    p1->val(v1);
}

void CmpBoolExp::param2(bool v1)
{
    p2->val(v1);
}

// CmpDateExp ----------------------

CmpDateExp::CmpDateExp(CmpType op, JsonDateNode *p1, JsonDateNode *p2)
    : CmpExpression(op), p1(p1), p2(p2) {}
CmpDateExp::CmpDateExp(CmpType op, time_t v1, time_t v2) : CmpExpression(op)
{
    p1 = new JsonDateNode(v1);
    p2 = new JsonDateNode(v2);
}

CmpDateExp::~CmpDateExp() {}

JsonBoolNode *CmpDateExp::executeAsBool()
{
    bool v;
    time_t v1 = p1->val();
    time_t v2 = p2->val();
    switch (op)
    {
    case CMP_OP_EQ:
        v = (v1 == v2);
        break;
    case CMP_OP_NE:
        v = (v1 != v2);
        break;
    case CMP_OP_LE:
        v = (v1 < v2);
        break;
    case CMP_OP_LE_OR_EQ:
        v = (v1 <= v2);
        break;
    case CMP_OP_GR:
        v = (v1 > v2);
        break;
    case CMP_OP_GR_OR_EQ:
        v = (v1 >= v2);
        break;
    }
    JsonBoolNode *r = new JsonBoolNode(v);
    return r;
}

void CmpDateExp::param1(time_t v1)
{
    p1->val(v1);
}

void CmpDateExp::param2(time_t v1)
{
    p2->val(v1);
}

// CmpStringExp ----------------------

CmpStringExp::CmpStringExp(CmpType op, JsonStringNode *p1, JsonStringNode *p2)
    : CmpExpression(op), p1(p1), p2(p2) {}
CmpStringExp::CmpStringExp(CmpType op, std::string v1, std::string v2) : CmpExpression(op)
{
    p1 = new JsonStringNode(v1);
    p2 = new JsonStringNode(v2);
}

CmpStringExp::~CmpStringExp() {}

JsonBoolNode *CmpStringExp::executeAsBool()
{
    bool v;
    std::string v1 = p1->val();
    std::string v2 = p2->val();
    switch (op)
    {
    case CMP_OP_EQ:
        v = (v1 == v2);
        break;
    case CMP_OP_NE:
        v = (v1 != v2);
        break;
    case CMP_OP_LE:
        v = (v1 < v2);
        break;
    case CMP_OP_LE_OR_EQ:
        v = (v1 <= v2);
        break;
    case CMP_OP_GR:
        v = (v1 > v2);
        break;
    case CMP_OP_GR_OR_EQ:
        v = (v1 >= v2);
        break;
    }
    JsonBoolNode *r = new JsonBoolNode(v);
    return r;
}

void CmpStringExp::param1(std::string v1)
{
    p1->val(v1);
}

void CmpStringExp::param2(std::string v1)
{
    p2->val(v1);
}

} // namespace mate