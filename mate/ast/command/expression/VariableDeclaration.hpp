#ifndef MATE_VARIABLE_DECLARATION_HH
    #define MATE_VARIABLE_DECLARATION_HH

#include "Expression.hpp"
#include "JsonPair.hpp"
#include "../../Json.hpp"

namespace mate
{
class VariableDeclaration : public Expression
{
  private:
    std::vector<JsonPair> values;
    NodeType dataType;

  public:
    VariableDeclaration(NodeType dataType, std::vector<JsonPair> values);
    ~VariableDeclaration();

    static const CommandType CMD_TYPE = CMD_EXP_VAR_DECLARATION;
    static const ExpressionType PRIM_EXP_TYPE = EXP_VAR_DECLARATION;

    void push(JsonPair val);
    JsonArrayNode *executeAsArray(Interpreter* interpreter);
    JsonNode *execute(Interpreter* interpreter);
};

} // mate

#endif //MATE_VARIABLE_DECLARATION_HH
