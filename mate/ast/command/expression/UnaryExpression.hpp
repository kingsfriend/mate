#ifndef MATE_UNARY_EXPRESSION_HH
    #define MATE_UNARY_EXPRESSION_HH
    
    #include <string>
    #include "Expression.hpp"
    
    namespace mate
    {
    enum UnaryOperator
    {
        UNARY_NEG_OP,
        UNARY_SUB_OP,
        UNARY_ADD_OP,
    }; 
    class UnaryExpression : public Expression{
      private:
        std::string varKey;
        Expression *exp;

      public:
        ~UnaryExpression();
        UnaryExpression(std::string varKey);
        UnaryExpression(std::string varKey, Expression *exp);

        static const CommandType CMD_TYPE = CMD_EXP_UNARY;
        static const ExpressionType EXP_TYPE = EXP_UNARY;
        static const std::string VALUATION_NULL;

        JsonNode *execute(Interpreter *interpreter);
        };
        
    } // mate

#endif //MATE_UNARY_EXPRESSION_HH
