#ifndef MATE_EXPRESSION_COMMAND_HH
    #define MATE_EXPRESSION_COMMAND_HH
    
    #include <cmath>
    #include <memory>
    #include <string>
    #include <stdlib.h>
    #include <ctime>
    #include "../Command.hpp"
    #include "../Json.hpp"
    
    namespace mate
    {
        enum ExpressionType{
            EXP,
            EXP_STRING,
            EXP_NUM,
            EXP_DATE,
            EXP_CMP,
            EXP_BOOL,
            EXP_,
        };
        
        class Expression : public Command
        {
        public:
            ~Expression();

            static const CommandType CMD_TYPE = CMD_EXP;
            static const ExpressionType DATE_EXP_TYPE = EXP;

        protected:
            Expression();
        };
        
    } // mate

#endif //MATE_EXPRESSION_COMMAND_HH
