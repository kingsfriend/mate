#ifndef MATE_BOOL_EXPRESSION_HH
    #define MATE_BOOL_EXPRESSION_HH
    
    #include "PrimaryExpression.hpp"
    
    namespace mate
    {
        class BoolExpression : public PrimaryExpression
        {
        private:
            JsonBoolNode* op1;

        public:
            BoolExpression(JsonBoolNode *op1);
            BoolExpression(bool v);
            ~BoolExpression();

            static const CommandType CMD_TYPE = CMD_EXP_PRIM_BOOL;
            static const PrimaryExpressionType PRIM_EXP_TYPE = PRIM_BOOL;
            static BoolExpression* BOOL_EXP_TRUE;
            static BoolExpression* BOOL_EXP_FALSE;
            JsonBoolNode *executeAsBool(Interpreter *interpreter);
            JsonNode *execute(Interpreter* interpreter);
            void val1(bool v1);

          protected:
            BoolExpression();
        };
        
    } // mate

#endif //MATE_BOOL_EXPRESSION_HH
