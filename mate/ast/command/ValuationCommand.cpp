#include "ValuationCommand.hpp"

namespace mate
{
// ValuationCommand ----------------------

const std::string ValuationCommand::VALUATION_NULL = "<undefined>";

ValuationCommand::ValuationCommand(std::string varKey) : varKey(varKey) {}

ValuationCommand::~ValuationCommand(){}

JsonNode *ValuationCommand::execute(Interpreter* interpreter){
    JsonNode *val = interpreter->context()->get(varKey);
    if(val!=NULL){
        interpreter->echo(val->toString());
    }else{
        interpreter->echo(VALUATION_NULL);
    }
    return NULL;
}

} // namespace mate