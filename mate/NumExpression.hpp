#ifndef MATE_NUM_EXPRESSION_HH
    #define MATE_NUM_EXPRESSION_HH
    
    #include <cmath>
    #include <memory>
    #include <stdlib.h>
    #include "Command.hpp"
    #include "Json.hpp"
    
    namespace mate
    {
        enum NumExpressionType{
            NUM_EXP_BINARY,
            NUM_EXP_UNARY,
            NUM_EXP_JSON_NODE
        };
        enum UnaryNumberExpType{
            EXP_UN_NUM_INC,
            EXP_UN_NUM_DEC
        };
        
        class NumExpression : public Command
        {
        private:
            JsonNumberNode* op1;

        public:
            NumExpression(JsonNumberNode *op1);
            NumExpression(double d);
            ~NumExpression();

            static const CommandType COMMAND_TYPE = CMD_NUM_EXP;
            static const NumExpressionType NUM_EXP_TYPE = NUM_EXP_JSON_NODE;
            JsonNumberNode *executeAsNum();
            JsonNode *execute();
            void update();

          protected:
            NumExpression();
        };

        class UnaryNumberExp : public NumExpression
        {
        private:
            NumExpression* op1;
            UnaryNumberExpType expType;
        public:
            UnaryNumberExp(UnaryNumberExpType expType, NumExpression *op1);
            ~UnaryNumberExp();

            static const NumExpressionType NUM_EXP_TYPE = NUM_EXP_UNARY;
            JsonNumberNode *executeAsNum();
            JsonNode* execute();
            void update();
        };
        
        enum BinaryNumberExpType{
            EXP_BI_NUM_MUL,
            EXP_BI_NUM_DIV,
            EXP_BI_NUM_MOD,
            EXP_BI_NUM_ADD,
            EXP_BI_NUM_SUB
        };
        class BinaryNumberExp : public NumExpression
        {
        private:
            NumExpression* op1;
            NumExpression *op2;
            BinaryNumberExpType expType;

          public:
            BinaryNumberExp(BinaryNumberExpType expType, NumExpression* op1, NumExpression* op2);
            ~BinaryNumberExp();

            static const NumExpressionType NUM_EXP_TYPE = NUM_EXP_BINARY;
            JsonNumberNode *executeAsNum();
            JsonNode *execute();
            void update();
        };
        
        
        
    } // mate

#endif //MATE_NUM_EXPRESSION_HH
