#ifndef MATE_PRIMARY_EXPRESSION_HH
    #define MATE_PRIMARY_EXPRESSION_HH
    
    #include "Expression.hpp"
    
    namespace mate
    {
    enum PrimaryExpressionType
    {
        PRIM,
        PRIM_CAST,
        PRIM_NUMBER,
        PRIM_STRING,
        PRIM_DATE,
        PRIM_BOOL,
        PRIM_INDENTIFIER,
        PRIM_OBJECT,
        PRIM_ARRAY,
    };

    class PrimaryExpression : public Command{
      public:
        ~PrimaryExpression();

        static const CommandType CMD_TYPE = CMD_EXP_PRIM;
        static const ExpressionType EXP_TYPE = EXP_PRIMARY;
        static const PrimaryExpressionType PRIM_TYPE = PRIM;

      protected:
        PrimaryExpression();
        };
        
    } // mate

#endif //MATE_PRIMARY_EXPRESSION_HH
