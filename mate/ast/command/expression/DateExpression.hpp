#ifndef MATE_DATE_EXPRESSION_HH
    #define MATE_DATE_EXPRESSION_HH
    
    #include "PrimaryExpression.hpp"
    
    namespace mate
    {
        class DateExpression : public PrimaryExpression
        {
        private:
            JsonDateNode* op1;

        public:
            DateExpression(JsonDateNode *op1);
            DateExpression(time_t v);
            ~DateExpression();

            static const CommandType CMD_TYPE = CMD_EXP_PRIM_DATE;
            static const PrimaryExpressionType PRIM_EXP_TYPE = PRIM_DATE;
            JsonDateNode *executeAsDate(Interpreter *interpreter);
            JsonNode *execute(Interpreter* interpreter);
            void val1(time_t v1);

          protected:
            DateExpression();
        };

        
    } // mate

#endif //MATE_DATE_EXPRESSION_HH
