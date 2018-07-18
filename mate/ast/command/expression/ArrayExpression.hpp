#ifndef MATE_ARRAy_EXPRESSION_HH
    #define MATE_ARRAy_EXPRESSION_HH

#include "PrimaryExpression.hpp"

namespace mate
{
class ArrayExpression : public PrimaryExpression
{
  private:
    JsonArrayNode *value;

  public:
    ArrayExpression(JsonArrayNode *value);
    ArrayExpression(std::vector<JsonNode *> v);
    ~ArrayExpression();
    ArrayExpression();

    static const CommandType CMD_TYPE = CMD_EXP_PRIM_ARRAY;
    static const PrimaryExpressionType PRIM_EXP_TYPE = PRIM_ARRAY;
    JsonArrayNode *executeAsString(Interpreter *interpreter);
    JsonNode *execute(Interpreter* interpreter);
    void val(std::vector<JsonNode *> v1);
};

} // mate

#endif //MATE_ARRAy_EXPRESSION_HH
