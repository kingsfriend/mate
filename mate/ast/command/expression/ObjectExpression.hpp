#ifndef MATE_OBJECT_EXPRESSION_HH
    #define MATE_OBJECT_EXPRESSION_HH

#include "PrimaryExpression.hpp"

namespace mate
{
class ObjectExpression : public PrimaryExpression
{
  private:
    std::map<const std::string, Expression *> values;

  public:
    ObjectExpression(std::map<const std::string, Expression*> vals);
    ObjectExpression();
    ~ObjectExpression();

    static const CommandType CMD_TYPE = CMD_EXP_PRIM_OBJECT;
    static const PrimaryExpressionType PRIM_EXP_TYPE = PRIM_OBJECT;

    void push(const std::string &k, Expression *val);
    JsonObjectNode *executeAsObject(Interpreter *interpreter);
    JsonNode *execute(Interpreter* interpreter);
};

} // mate

#endif //MATE_OBJECT_EXPRESSION_HH
