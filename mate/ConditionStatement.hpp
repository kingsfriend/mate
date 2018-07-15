#ifndef MATE_CONDITION_STATEMENT_HH
    #define MATE_CONDITION_STATEMENT_HH
    
    #include "BoolExpression.hpp"
    
    namespace mate
    {
        
        class ConditionExpression : public BoolExpression
        {
        private:
            BoolExpression* boolExp;
            ConditionExpression* condExp;
            BinaryBoolExpType type;

          public:
            ConditionExpression(BoolExpression *boolExp);
            ConditionExpression(BoolExpression *boolExp, BinaryBoolExpType type, ConditionExpression *condExp);
            ~ConditionExpression();

            static const BoolExpressionType BOOL_EXP_TYPE = BOOL_EXP_COND;
            static ConditionExpression* TRUE_CONDITION;
            static ConditionExpression* FALSE_CONDITION;

            JsonBoolNode *executeAsBool();

        };
        
        enum ConditionStatementType{
            COND_STM,
            COND_STM_IF,
            COND_STM_SWITCH,
            COND_STM_FOR,
            COND_STM_FOREACH,
            COND_STM_WHILE,
        };

        class ConditionStatement : public Command
        {
        public:
            ~ConditionStatement();
            ConditionStatement(ConditionExpression* condition);

            static const CommandType CMD_TYPE = CMD_COND_EXP;
            static const ConditionStatementType COND_STM_TYPE = COND_STM;

            bool valuateCondition();

        protected:
            ConditionExpression* condition;
        };

        class IfStatement : public ConditionStatement
        {
          private:
            ConditionExpression* condition;
            IfStatement* nextBlok; // ELSEIF or ELSE section
            std::vector<Command*> commandes;

          public:
            ~IfStatement();
            IfStatement(); // for else section
            IfStatement(ConditionExpression *condition);
            IfStatement(ConditionExpression *condition, std::vector<Command *> commandes);
            IfStatement(ConditionExpression *condition, std::vector<Command *> commandes, IfStatement *nextBlok);

            static const CommandType CMD_TYPE = CMD_COND_STM_IF;
            static const ConditionStatementType COND_STM_TYPE = COND_STM_IF;

            JsonNode* execute();
        };

    } // mate

#endif //MATE_CONDITION_STATEMENT_HH
