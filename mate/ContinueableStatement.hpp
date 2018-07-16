#ifndef MATE_CONTINUEABLE_STATEMENT_HH
    #define MATE_CONTINUEABLE_STATEMENT_HH

    #include "BreakableStatement.hpp"
    #include "Expression.hpp"

    namespace mate
    {
        class ContinueableStatement;
        class CaseStatement;
        class DefaultStatement;

        class ContinueCommand : public Command
        {
        private:
            ContinueableStatement *statement;

        public:
            ContinueCommand();
            ContinueCommand(ContinueableStatement *statement);
            ~ContinueCommand();

            static const CommandType CMD_TYPE = CMD_CONTINUE;

            ContinueableStatement *getStatement();
            void setStatement(ContinueableStatement *stm);

            JsonNode *execute();
        };

        enum ContinueableStatementType{
            CONTINUE_STM,
            CONTINUE_STM_WHILE,
            CONTINUE_STM_FOR,
            CONTINUE_STM_FOREACH
        };

        class ContinueableStatement : public BreakableStatement
        {
        private:
            bool continued;
            
        public:
            static const CommandType CMD_TYPE = CMD_CONTINUE_EXP;
            static const ContinueableStatementType CONTINUE_STM_TYPE = CONTINUE_STM;
            
            ~ContinueableStatement();
            ContinueableStatement();
            ContinueableStatement(ConditionExpression *condition);

            void setContinued(bool v);
            bool isContinued();
        };

        class WhileStatement : public ContinueableStatement
        {
        private:
            std::vector<Command*> commands;

        public:
            static const CommandType CMD_TYPE = CMD_CONTINUE_STM_WHILE;
            static const ContinueableStatementType CONTINUE_STM_TYPE = CONTINUE_STM_WHILE;
            
            ~WhileStatement();
            WhileStatement(ConditionExpression *condition);
            WhileStatement(ConditionExpression *condition, std::vector<Command *> commands);

            JsonNode* execute();
        };

        class ForStatement : public ContinueableStatement{
        private:
            std::vector<Expression*> expInits;
            std::vector<Expression*> expIncrs;
            std::vector<ConditionExpression*> expConds;
            std::vector<Command*> commands;

          public:
            static const CommandType CMD_TYPE = CMD_CONTINUE_STM_WHILE;
            static const ContinueableStatementType CONTINUE_STM_TYPE = CONTINUE_STM_WHILE;
            
            ~ForStatement();
            ForStatement(std::vector<Expression*> expInits, std::vector<Expression*> expIncrs, std::vector<ConditionExpression*> expConds);
            ForStatement(std::vector<Expression*> expInits, std::vector<Expression*> expIncrs, std::vector<ConditionExpression*> expConds, std::vector<Command*> commands);

            std::vector<Expression *> getExpInit();
            std::vector<Expression *> getExpIncr();
            std::vector<ConditionExpression *> getExpCond();
            std::vector<Command *> getCommands();

            void setExpInit(std::vector<Expression *> expInits);
            void setExpIncr(std::vector<Expression *> expIncrs);
            void setExpCond(std::vector<ConditionExpression *> expConds);
            void setCommands(std::vector<Command *> commands);

            bool valuateConditions();
            void executeIncrs();
            void executeInits();
            JsonNode* execute();
        };

        class ForeachStatement : public ContinueableStatement{
        private:
            int currentItemIndex;
            JsonNode* currentItem;
            JsonArrayNode* array;
            std::vector<Command*> commands;
            std::vector<Command*> emptyCommands;

        public:
            static const CommandType CMD_TYPE = CMD_CONTINUE_STM_FOREACH;
            static const ContinueableStatementType CONTINUE_STM_TYPE = CONTINUE_STM_FOREACH;
            
            ~ForeachStatement();
            ForeachStatement(JsonArrayNode* array, JsonNode* item);
            ForeachStatement(JsonArrayNode *array, JsonNode *item, std::vector<Command *> commands);
            ForeachStatement(JsonArrayNode *array, JsonNode *item, std::vector<Command *> commands, std::vector<Command *> emptyCommands);

            JsonNode* execute();
        protected:
            bool updateCurrentItem();
            void resetIndex();
        };

    } // mate

#endif //MATE_CONTINUEABLE_STATEMENT_HH
