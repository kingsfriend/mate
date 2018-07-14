#ifndef MATE_BOOL_EXPRESSION_HH
    #define MATE_BOOL_EXPRESSION_HH
    
    #include <cmath>
    #include <memory>
    #include <stdlib.h>
    #include "Command.hpp"
    #include "Json.hpp"
    
    namespace mate
    {
        enum BoolExpressionType{
            BOOL_EXP_BINARY,
            BOOL_EXP_UNARY,
            BOOL_EXP_JSON_NODE
        };
        enum UnaryBoolExpType{
            EXP_UN_BOOL_NOT
        };
        
        class BoolExpression : public Command
        {
        private:
            JsonBoolNode* op1;

        public:
            BoolExpression(JsonBoolNode *op1);
            BoolExpression(bool v);
            ~BoolExpression();

            static const CommandType COMMAND_TYPE = CMD_BOOL_EXP;
            static const BoolExpressionType BOOL_EXP_TYPE = BOOL_EXP_JSON_NODE;
            JsonBoolNode *executeAsNum();
            JsonNode *execute();
            void update();
            void val1(bool v1);

          protected:
            BoolExpression();
        };

        class UnaryBoolExp : public BoolExpression
        {
        private:
            BoolExpression* op1;
            UnaryBoolExpType expType;
        public:
            UnaryBoolExp(UnaryBoolExpType expType, BoolExpression *op1);
            ~UnaryBoolExp();

            static const BoolExpressionType BOOL_EXP_TYPE = BOOL_EXP_UNARY;
            JsonBoolNode *executeAsNum();
            JsonNode* execute();
            void update();
            void val1(double v1);
        };

        enum BinaryBoolExpType{
            EXP_BI_BOOL_ASSIGN,
            EXP_BI_BOOL_ASSIGN_AND,
            EXP_BI_BOOL_ASSIGN_OR,
            EXP_BI_BOOL_ASSIGN_XOR,
            EXP_BI_BOOL_AND,
            EXP_BI_BOOL_OR,
            EXP_BI_BOOL_XOR
        };
        class BinaryBoolExp : public BoolExpression
        {
        private:
            BoolExpression* op1;
            BoolExpression *op2;
            BinaryBoolExpType expType;

          public:
            BinaryBoolExp(BinaryBoolExpType expType, BoolExpression* op1, BoolExpression* op2);
            ~BinaryBoolExp();

            static const BoolExpressionType BOOL_EXP_TYPE = BOOL_EXP_BINARY;
            JsonBoolNode *executeAsNum();
            JsonNode *execute();
            void update();
            void val1(double v1);
            void val2(bool v2);
        };
        
        
        
    } // mate

#endif //MATE_BOOL_EXPRESSION_HH