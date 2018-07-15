#ifndef MATE_STR_EXPRESSION_HH
    #define MATE_STR_EXPRESSION_HH
    
    #include <cmath>
    #include <memory>
    #include <string>
    #include <stdlib.h>
    #include "Command.hpp"
    #include "Json.hpp"
    
    namespace mate
    {
        enum StringExpressionType{
            STR_EXP_BINARY,
            STR_EXP_UNARY,
            STR_EXP_JSON_NODE
        };
        enum UnaryStringExpType{
            EXP_UN_STR_PREF_PLUS,
            EXP_UN_STR_PREF_MINUS
        };
        
        class StringExpression : public Command
        {
        private:
            JsonStringNode* op1;

        public:
            StringExpression(JsonStringNode *op1);
            StringExpression(std::string v);
            ~StringExpression();

            static const CommandType CMD_TYPE = CMD_EXP_STR;
            static const StringExpressionType STR_EXP_TYPE = STR_EXP_JSON_NODE;
            JsonStringNode *executeAsString();
            JsonNode *execute();
            void val1(std::string v1);

          protected:
            StringExpression();
        };

        class UnaryStringExp : public StringExpression
        {
        private:
            StringExpression* op1;
            UnaryStringExpType expType;
        public:
            UnaryStringExp(UnaryStringExpType expType, StringExpression *op1);
            ~UnaryStringExp();

            static const StringExpressionType STR_EXP_TYPE = STR_EXP_UNARY;
            JsonStringNode *executeAsString();
            JsonNode* execute();
            void val1(std::string v1);
        };

        enum BinaryStringExpType{
            EXP_BI_STR_ASSIGN,
            EXP_BI_STR_ASSIGN_ADD,
            EXP_BI_STR_ASSIGN_SUB,
            EXP_BI_STR_ADD,
            EXP_BI_STR_SUB,
        };
        class BinaryStringExp : public StringExpression
        {
        private:
            StringExpression* op1;
            StringExpression *op2;
            BinaryStringExpType expType;

          public:
            BinaryStringExp(BinaryStringExpType expType, StringExpression* op1, StringExpression* op2);
            ~BinaryStringExp();

            static const StringExpressionType STR_EXP_TYPE = STR_EXP_BINARY;
            JsonStringNode *executeAsString();
            JsonNode *execute();
            void val1(std::string v1);
            void val2(std::string v2);
        };
        
        
        
    } // mate

#endif //MATE_STR_EXPRESSION_HH
