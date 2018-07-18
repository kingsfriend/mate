#ifndef MATE_ASSIGNMENT_EXPRESSION_HH
    #define MATE_ASSIGNMENT_EXPRESSION_HH
    
    #include <string>
    #include "Expression.hpp"
    
    namespace mate
    {
        
        class AssignmentExpression : public Expression
        {
        private:
            std::string varKey;
            Expression* exp;
        public:
            ~AssignmentExpression();
            AssignmentExpression(std::string varKey);
            AssignmentExpression(std::string varKey, Expression* exp);

            static const CommandType CMD_TYPE = CMD_EXP_ASSIGN;
            static const ExpressionType EXP_TYPE = EXP_ASSIGN;
            static const std::string VALUATION_NULL;

            JsonNode *execute(Interpreter* interpreter);
        };
        
    } // mate

#endif //MATE_ASSIGNMENT_EXPRESSION_HH
