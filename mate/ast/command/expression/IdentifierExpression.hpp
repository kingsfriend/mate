#ifndef MATE_IDENTIFIER_EXPRESSION_HH
    #define MATE_IDENTIFIER_EXPRESSION_HH
    
    #include "PrimaryExpression.hpp"
    
    namespace mate
    {
        class IdentifierExpression : public PrimaryExpression
        {
        private:
            std::string identifier;

        public:
            IdentifierExpression(std::string identifier);
            ~IdentifierExpression();

            static const CommandType CMD_TYPE = CMD_EXP_PRIM_INDENTFIER;
            static const PrimaryExpressionType PRIM_EXP_TYPE = PRIM_INDENTIFIER;
            JsonNode *execute(Interpreter* interpreter);
            void val(std::string v1);

          protected:
            IdentifierExpression();
        };
        
    } // mate

#endif //MATE_IDENTIFIER_EXPRESSION_HH
