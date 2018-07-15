#ifndef MATE_CONDITION_STATEMENT_HH
    #define MATE_CONDITION_STATEMENT_HH
    
    #include "BoolExpression.hpp"
    
    namespace mate
    {
        enum ConditionExpressionType{
            COND_EXP
        };
        
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
        ConditionExpression* ConditionExpression::TRUE_CONDITION = new ConditionExpression(BoolExpression::BOOL_EXP_TRUE);
        ConditionExpression* ConditionExpression::FALSE_CONDITION = new  ConditionExpression(BoolExpression::BOOL_EXP_FALSE);
        
        enum ConditionStatementType{
            COND_STM,
            COND_STM_IF
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

        class IfCondStm : public ConditionStatement
        {
          private:
            ConditionExpression* condition;
            IfCondStm* nextBlok; // ELSEIF or ELSE section
            std::vector<Command*> commandes;

          public:
            ~IfCondStm();
            IfCondStm(); // for else section
            IfCondStm(ConditionExpression *condition);
            IfCondStm(ConditionExpression *condition, std::vector<Command *> commandes);
            IfCondStm(ConditionExpression *condition, std::vector<Command *> commandes, IfCondStm *nextBlok);

            static const CommandType CMD_TYPE = CMD_COND_STM_IF;
            static const ConditionStatementType COND_STM_TYPE = COND_STM_IF;

            JsonNode* execute();
        };

    } // mate

#endif //MATE_CONDITION_STATEMENT_HH
