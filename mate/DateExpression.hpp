#ifndef MATE_DATE_EXPRESSION_HH
    #define MATE_DATE_EXPRESSION_HH
    
    #include <cmath>
    #include <memory>
    #include <stdlib.h>
    #include <ctime>
    #include "Command.hpp"
    #include "Json.hpp"
    
    namespace mate
    {
        enum DateExpressionType{
            DATE_EXP_BINARY,
            DATE_EXP_UNARY,
            DATE_EXP_JSON_NODE
        };
        enum UnaryDateExpType{
            EXP_UN_DATE_PREF_PLUS,
            EXP_UN_DATE_PREF_MINUS
        };
        
        class DateExpression : public Command
        {
        private:
            JsonDateNode* op1;

        public:
            DateExpression(JsonDateNode *op1);
            DateExpression(time_t v);
            ~DateExpression();

            static const CommandType COMMAND_TYPE = CMD_DATE_EXP;
            static const DateExpressionType DATE_EXP_TYPE = DATE_EXP_JSON_NODE;
            JsonDateNode *executeAsDate();
            JsonNode *execute();
            void update();
            void val1(time_t v1);

          protected:
            DateExpression();
        };

        class UnaryDateExp : public DateExpression
        {
        private:
            DateExpression* op1;
            UnaryDateExpType expType;
        public:
            UnaryDateExp(UnaryDateExpType expType, DateExpression *op1);
            ~UnaryDateExp();

            static const DateExpressionType DATE_EXP_TYPE = DATE_EXP_UNARY;
            JsonDateNode *executeAsDate();
            JsonNode* execute();
            void update();
            void val1(time_t v1);
        };

        enum BinaryDateExpType{
            EXP_BI_DATE_ASSIGN,
            EXP_BI_DATE_ASSIGN_ADD,
            EXP_BI_DATE_ASSIGN_SUB,
            EXP_BI_DATE_ADD,
            EXP_BI_DATE_SUB
        };
        class BinaryDateExp : public DateExpression
        {
        private:
            DateExpression* op1;
            DateExpression *op2;
            BinaryDateExpType expType;

          public:
            BinaryDateExp(BinaryDateExpType expType, DateExpression* op1, DateExpression* op2);
            ~BinaryDateExp();

            static const DateExpressionType DATE_EXP_TYPE = DATE_EXP_BINARY;
            JsonDateNode *executeAsDate();
            JsonNode *execute();
            void update();
            void val1(time_t v1);
            void val2(time_t v2);
        };
        
        
        
    } // mate

#endif //MATE_DATE_EXPRESSION_HH
