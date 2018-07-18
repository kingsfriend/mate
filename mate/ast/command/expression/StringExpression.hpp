#ifndef MATE_STR_EXPRESSION_HH
    #define MATE_STR_EXPRESSION_HH

#include "PrimaryExpression.hpp"

namespace mate
{
class StringExpression : public PrimaryExpression
{
  private:
    JsonStringNode *op1;

  public:
    StringExpression(JsonStringNode *op1);
    StringExpression(std::string v);
    ~StringExpression();

    static const CommandType CMD_TYPE = CMD_EXP_PRIM_STR;
    static const PrimaryExpressionType PRIM_EXP_TYPE = PRIM_STRING;
    JsonStringNode *executeAsString(Interpreter *interpreter);
    JsonNode *execute(Interpreter* interpreter);
    void val1(std::string v1);

  protected:
    StringExpression();
};

} // mate

#endif //MATE_STR_EXPRESSION_HH
