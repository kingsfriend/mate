#include "ValuationCommand.hpp"

namespace mate
{
// ValuationCommand ----------------------

const std::string ValuationCommand::VALUATION_NULL = "<null>";

ValuationCommand::ValuationCommand(Expression *exp) 
    : exp(exp) {
        defExp = NULL;
    }

ValuationCommand::ValuationCommand(Expression *exp, Expression *defExp)
    : exp(exp), defExp(defExp) {}

ValuationCommand::~ValuationCommand(){}

JsonNode *ValuationCommand::execute(Interpreter* interpreter){
    JsonNode *node = NULL;
    if (exp != NULL){
        node = exp->execute(interpreter);
    }
    if(node==NULL && defExp!=NULL){
        node = defExp->execute(interpreter);
    }
    if(node!=NULL){
        interpreter->echo(node->toString());
        return NULL;
    }
    interpreter->echo(VALUATION_NULL);
    return NULL;
}

} // namespace mate