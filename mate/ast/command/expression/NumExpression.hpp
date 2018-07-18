#ifndef MATE_NUM_EXPRESSION_HH
    #define MATE_NUM_EXPRESSION_HH
    
    #include "PrimaryExpression.hpp"
    
    namespace mate
    {
        class NumExpression : public PrimaryExpression
        {
        private:
            JsonNumberNode* op1;

        public:
            NumExpression(JsonNumberNode *op1);
            NumExpression(double v);
            ~NumExpression();

            static const CommandType CMD_TYPE = CMD_EXP_PRIM_NUM;
            static const PrimaryExpressionType PRIM_EXP_TYPE = PRIM_NUMBER;
            JsonNumberNode *executeAsNum(Interpreter *interpreter);
            JsonNode *execute(Interpreter* interpreter);
            void val1(double v1);

          protected:
            NumExpression();
        };
    } // mate

#endif //MATE_NUM_EXPRESSION_HH
