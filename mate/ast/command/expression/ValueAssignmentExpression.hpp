#ifndef MATE_VALUE_ASSIGNMENT_EXPRESSION_HH
    #define MATE_VALUE_ASSIGNMENT_EXPRESSION_HH
    
    #include <string>
    #include "AssignmentExpression.hpp"
    
    namespace mate
    {
        
        class ValueAssignmentExpression : public Expression
        {
        private:
            std::vector<AssignmentExpression *> values;
        public:
            ~ValueAssignmentExpression();
            ValueAssignmentExpression();
            ValueAssignmentExpression(std::vector<AssignmentExpression *> values);

            static const CommandType CMD_TYPE = CMD_EXP_VAL_ASSIGN;
            static const ExpressionType EXP_TYPE = EXP_VAL_ASSIGN;
            static const std::string VALUATION_NULL;

            void push(AssignmentExpression * val);
            JsonNode *execute(Interpreter* interpreter);
        };
        
    } // mate

#endif //MATE_VALUE_ASSIGNMENT_EXPRESSION_HH
