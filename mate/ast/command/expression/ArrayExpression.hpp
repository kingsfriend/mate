#ifndef MATE_ARRAy_EXPRESSION_HH
    #define MATE_ARRAy_EXPRESSION_HH

#include "PrimaryExpression.hpp"

namespace mate
{
class ArrayExpression : public PrimaryExpression
{
  private:
    std::vector<Expression *> values;

  public:
    ArrayExpression();
    ArrayExpression(std::vector<Expression *> values);
    ~ArrayExpression();

    static const CommandType CMD_TYPE = CMD_EXP_PRIM_ARRAY;
    static const PrimaryExpressionType PRIM_EXP_TYPE = PRIM_ARRAY;

    void push(Expression * val);
    JsonArrayNode *executeAsArray(Interpreter* interpreter);
    JsonNode *execute(Interpreter* interpreter);
};

} // mate

#endif //MATE_ARRAy_EXPRESSION_HH
