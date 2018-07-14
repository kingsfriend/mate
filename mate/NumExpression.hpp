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
            EXP_UN_NUM_PREF_PLUS,
            EXP_UN_NUM_PREF_MINUS,
            EXP_UN_NUM_POST_INC,
            EXP_UN_NUM_POST_DEC,
            EXP_UN_NUM_PREF_INC,
            EXP_UN_NUM_PREF_DEC
        };
        
        class NumExpression : public Command
        {
        private:
            JsonNumberNode* op1;

        public:
            NumExpression(JsonNumberNode *op1);
            NumExpression(double v);
            ~NumExpression();

            static const CommandType COMMAND_TYPE = CMD_NUM_EXP;
            static const NumExpressionType NUM_EXP_TYPE = NUM_EXP_JSON_NODE;
            JsonNumberNode *executeAsNum();
            JsonNode *execute();
            void update();
            void val1(double v1);

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
            void val1(double v1);
        };

        enum BinaryNumberExpType{
            EXP_BI_NUM_ASSIGN,
            EXP_BI_NUM_ASSIGN_MUL,
            EXP_BI_NUM_ASSIGN_DIV,
            EXP_BI_NUM_ASSIGN_ADD,
            EXP_BI_NUM_ASSIGN_SUB,
            EXP_BI_NUM_ASSIGN_MOD,
            EXP_BI_NUM_MUL,
            EXP_BI_NUM_DIV,
            EXP_BI_NUM_ADD,
            EXP_BI_NUM_SUB,
            EXP_BI_NUM_MOD
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
            void val1(double v1);
            void val2(double v2);
        };
        
        
        
    } // mate

#endif //MATE_NUM_EXPRESSION_HH
