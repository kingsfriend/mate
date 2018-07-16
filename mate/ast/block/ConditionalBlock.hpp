#ifndef MATE_CONDITION_BLOCK_HH
    #define MATE_CONDITION_BLOCK_HH
    
    #include "../expression/BoolExpression.hpp"
    
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
        
        enum ConditionalBlockType{
            COND_BLOCK,
            COND_BLOCK_IF,
            COND_BLOCK_SWITCH,
            COND_BLOCK_FOR,
            COND_BLOCK_FOREACH,
            COND_BLOCK_WHILE,
        };

        class ConditionalBlock : public Command
        {
        public:
            ~ConditionalBlock();
            ConditionalBlock(ConditionExpression* condition);

            static const CommandType CMD_TYPE = CMD_COND_EXP;
            static const ConditionalBlockType COND_BLOCK_TYPE = COND_BLOCK;

            bool valuateCondition();

        protected:
            ConditionExpression* condition;
        };

        class IfBlock : public ConditionalBlock
        {
          private:
            IfBlock* nextBlok; // ELSEIF or ELSE section
            std::vector<Command*> commandes;

          public:
            ~IfBlock();
            IfBlock(); // for else section
            IfBlock(ConditionExpression *condition);
            IfBlock(ConditionExpression *condition, std::vector<Command *> commandes);
            IfBlock(ConditionExpression *condition, std::vector<Command *> commandes, IfBlock *nextBlok);

            static const CommandType CMD_TYPE = CMD_COND_BLOCK_IF;
            static const ConditionalBlockType COND_BLOCK_TYPE = COND_BLOCK_IF;

            JsonNode* execute();
        };

    } // mate

#endif //MATE_CONDITION_BLOCK_HH
