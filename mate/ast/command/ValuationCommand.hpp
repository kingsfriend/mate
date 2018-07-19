#ifndef MATE_VALUATION_COMMAND_HH
    #define MATE_VALUATION_COMMAND_HH
    
    #include <string>
    #include "Command.hpp"
    #include "expression/Expression.hpp"
    
    namespace mate
    {
        
        class ValuationCommand : public Command
        {
        private:
            Expression* exp;
            Expression* defExp;
        public:
            ~ValuationCommand();
            ValuationCommand(Expression *exp);
            ValuationCommand(Expression *exp, Expression *defaultExp);

            static const CommandType CMD_TYPE = CMD_VALUATION;
            static const std::string VALUATION_NULL;

            JsonNode *execute(Interpreter* interpreter);
        };
        
    } // mate

#endif //MATE_VALUATION_COMMAND_HH
