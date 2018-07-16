#ifndef MATE_EXPRESSION_HH
    #define MATE_EXPRESSION_HH
    
    #include <cmath>
    #include <memory>
    #include <stdlib.h>
    #include <ctime>
    #include "Command.hpp"
    #include "Json.hpp"
    
    namespace mate
    {
        enum ExpressionType{
            EXP,
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

#endif //MATE_EXPRESSION_HH
