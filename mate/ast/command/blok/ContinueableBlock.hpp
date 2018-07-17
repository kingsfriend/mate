#ifndef MATE_CONTINUEABLE_BLOCK_HH
    #define MATE_CONTINUEABLE_BLOCK_HH

    #include "BreakableBlock.hpp"
    #include "../expression/ExpressionCommand.hpp"

    namespace mate
    {
        class ContinueableBlock;
        class CaseBlock;
        class DefaultBlock;

        class ContinueCommand : public Command
        {
        private:
            ContinueableBlock *block;

        public:
            ContinueCommand();
            ContinueCommand(ContinueableBlock *block);
            ~ContinueCommand();

            static const CommandType CMD_TYPE = CMD_CONTINUE;

            ContinueableBlock *getBlock();
            void setBlock(ContinueableBlock *stm);

            JsonNode *execute(Interpreter* interpreter);
        };

        enum ContinueableBlockType{
            CONTINUE_BLOCK,
            CONTINUE_BLOCK_WHILE,
            CONTINUE_BLOCK_FOR,
            CONTINUE_BLOCK_FOREACH
        };

        class ContinueableBlock : public BreakableBlock
        {
        private:
            bool continued;
            
        public:
            static const CommandType CMD_TYPE = CMD_CONTINUE_EXP;
            static const ContinueableBlockType CONTINUE_BLOCK_TYPE = CONTINUE_BLOCK;
            
            ~ContinueableBlock();
            ContinueableBlock();
            ContinueableBlock(ConditionExpression *condition);

            void setContinued(bool v);
            bool isContinued();
        };

        class WhileBlock : public ContinueableBlock
        {
        private:
            std::vector<Command*> commands;

        public:
            static const CommandType CMD_TYPE = CMD_CONTINUE_BLOCK_WHILE;
            static const ContinueableBlockType CONTINUE_BLOCK_TYPE = CONTINUE_BLOCK_WHILE;
            
            ~WhileBlock();
            WhileBlock(ConditionExpression *condition);
            WhileBlock(ConditionExpression *condition, std::vector<Command *> commands);

            JsonNode *execute(Interpreter* interpreter);
        };

        class ForBlock : public ContinueableBlock{
        private:
            std::vector<Expression*> expInits;
            std::vector<Expression*> expIncrs;
            std::vector<ConditionExpression*> expConds;
            std::vector<Command*> commands;

          public:
            static const CommandType CMD_TYPE = CMD_CONTINUE_BLOCK_WHILE;
            static const ContinueableBlockType CONTINUE_BLOCK_TYPE = CONTINUE_BLOCK_WHILE;
            
            ~ForBlock();
            ForBlock(std::vector<Expression*> expInits, std::vector<Expression*> expIncrs, std::vector<ConditionExpression*> expConds);
            ForBlock(std::vector<Expression*> expInits, std::vector<Expression*> expIncrs, std::vector<ConditionExpression*> expConds, std::vector<Command*> commands);

            std::vector<Expression *> getExpInit();
            std::vector<Expression *> getExpIncr();
            std::vector<ConditionExpression *> getExpCond();
            std::vector<Command *> getCommands();

            void setExpInit(std::vector<Expression *> expInits);
            void setExpIncr(std::vector<Expression *> expIncrs);
            void setExpCond(std::vector<ConditionExpression *> expConds);
            void setCommands(std::vector<Command *> commands);

            bool valuateConditions(Interpreter* interpreter);
            void executeIncrs(Interpreter* interpreter);
            void executeInits(Interpreter* interpreter);
            JsonNode *execute(Interpreter* interpreter);
        };

        class ForeachBlock : public ContinueableBlock{
        private:
            int currentItemIndex;
            JsonNode* currentItem;
            JsonArrayNode* array;
            std::vector<Command*> commands;
            std::vector<Command*> emptyCommands;

        public:
            static const CommandType CMD_TYPE = CMD_CONTINUE_BLOCK_FOREACH;
            static const ContinueableBlockType CONTINUE_BLOCK_TYPE = CONTINUE_BLOCK_FOREACH;
            
            ~ForeachBlock();
            ForeachBlock(JsonArrayNode* array, JsonNode* item);
            ForeachBlock(JsonArrayNode *array, JsonNode *item, std::vector<Command *> commands);
            ForeachBlock(JsonArrayNode *array, JsonNode *item, std::vector<Command *> commands, std::vector<Command *> emptyCommands);

            JsonNode *execute(Interpreter* interpreter);
        protected:
            bool updateCurrentItem();
            void resetIndex();
        };

    } // mate

#endif //MATE_CONTINUEABLE_BLOCK_HH
