#include "ValueAssignmentExpression.hpp"

namespace mate
{
// ValueAssignmentExpression ----------------------

const std::string ValueAssignmentExpression::VALUATION_NULL = "<undefined>";

ValueAssignmentExpression::~ValueAssignmentExpression(){}

ValueAssignmentExpression::ValueAssignmentExpression(){}

ValueAssignmentExpression::ValueAssignmentExpression(std::vector<AssignmentExpression *> values) 
    : values(values) {}

JsonNode *ValueAssignmentExpression::execute(Interpreter* interpreter){
    int i, loopLimit = values.size();
    std::ostringstream s;
    for (i = 0; i < loopLimit; i++){
        values[i]->execute(interpreter);
    }
    return NULL;
}

void ValueAssignmentExpression::push(AssignmentExpression * val){
    values.push_back(val);  
}


} // namespace mate