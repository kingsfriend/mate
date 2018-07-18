#ifndef MATE_OBJECT_EXPRESSION_HH
    #define MATE_OBJECT_EXPRESSION_HH

#include "PrimaryExpression.hpp"

namespace mate
{
class ObjectExpression : public PrimaryExpression
{
  private:
    JsonObjectNode *value;

  public:
    ObjectExpression(JsonObjectNode *value);
    ObjectExpression(std::map<const std::string, JsonNode *> v);
    ObjectExpression();
    ~ObjectExpression();

    static const CommandType CMD_TYPE = CMD_EXP_PRIM_OBJECT;
    static const PrimaryExpressionType PRIM_EXP_TYPE = PRIM_OBJECT;
    JsonObjectNode *executeAsString(Interpreter *interpreter);
    JsonNode *execute(Interpreter* interpreter);
    void val(std::map<const std::string, JsonNode *> v1);
};

} // mate

#endif //MATE_OBJECT_EXPRESSION_HH
