#ifndef MATE_VARIABLE_DECLARATION_HH
    #define MATE_VARIABLE_DECLARATION_HH

#include "Expression.hpp"
#include "KeyExpressionPair.hpp"
#include "../../Json.hpp"

namespace mate
{
class VariableDeclaration : public Expression
{
  private:
    std::vector<KeyExpressionPair> values;
    NodeType dataType;

  public:
    VariableDeclaration(NodeType dataType, std::vector<KeyExpressionPair> values);
    ~VariableDeclaration();

    static const CommandType CMD_TYPE = CMD_EXP_VAR_DECLARATION;
    static const ExpressionType PRIM_EXP_TYPE = EXP_VAR_DECLARATION;

    void push(KeyExpressionPair val);
    JsonArrayNode *executeAsArray(Interpreter* interpreter);
    JsonNode *execute(Interpreter* interpreter);
};

} // mate

#endif //MATE_VARIABLE_DECLARATION_HH
