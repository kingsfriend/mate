#ifndef MATE_BREAKABLE_BLOCK_HH
    #define MATE_BREAKABLE_BLOCK_HH

    #include "ConditionalBlock.hpp"

    namespace mate
    {
        class BreakableBlock;
        class CaseBlock;
        class DefaultBlock;

        class BreakCommand : public Command
        {
        private:
            double level;
            BreakableBlock* block;
        public:
            BreakCommand();
            BreakCommand(BreakableBlock *block);
            ~BreakCommand();

            static const CommandType CMD_TYPE = CMD_BREAK;

            BreakableBlock *getBlock();
            void setBlock(BreakableBlock *stm);

            JsonNode *execute(Interpreter* interpreter);
        };

        enum BreakableBlockType{
            BREAK_BLOCK,
            BREAK_BLOCK_SWITCH,
            BREAK_BLOCK_CASE,
            BREAK_BLOCK_DEFAULT,
            BREAK_BLOCK_FOR,
            BREAK_BLOCK_FOREACH,
            BREAK_BLOCK_WHILE,
        };

        class BreakableBlock : public ConditionalBlock{
        private:
            bool broken;

        public:
            static const CommandType CMD_TYPE = CMD_BREAK_EXP;
            static const BreakableBlockType BREAK_BLOCK_TYPE = BREAK_BLOCK;
            
            ~BreakableBlock();
            BreakableBlock();
            BreakableBlock(ConditionExpression *condition);

            void setBroken(bool v);
            bool isBroken();
        };

        class SwitchBlock : public BreakableBlock{
        private:
            JsonNode* baseNode;
            std::vector<CaseBlock*> caseStms;
            DefaultBlock* defaultStm;

        public:
            static const CommandType CMD_TYPE = CMD_BREAK_BLOCK_SWITCH;
            static const BreakableBlockType BREAK_BLOCK_TYPE = BREAK_BLOCK_SWITCH;
            
            ~SwitchBlock();
            SwitchBlock(JsonNode *baseNode); 
            SwitchBlock(JsonNode *baseNode, std::vector<CaseBlock*> caseStms);
            SwitchBlock(JsonNode *baseNode, std::vector<CaseBlock *> caseStms, DefaultBlock *defaultStm);
            SwitchBlock(JsonNode *baseNode, DefaultBlock *defaultStm);

            JsonNode* getBaseNode();
            JsonNode *execute(Interpreter* interpreter);
        };

        class CaseBlock : public BreakableBlock {
        private:
            SwitchBlock *switchStm;
            JsonNode* compareNode;
            std::vector<Command*> commands;

        public:
            static const CommandType CMD_TYPE = CMD_BREAK_BLOCK_CASE;
            static const BreakableBlockType BREAK_BLOCK_TYPE = BREAK_BLOCK_CASE;
            
            ~CaseBlock();
            CaseBlock(JsonNode *compareNode);
            CaseBlock(JsonNode *compareNode, std::vector<Command*> commands);

            void setSwitchStm(SwitchBlock *switchStm);
            JsonNode *execute(Interpreter* interpreter);

        };

        class DefaultBlock : public BreakableBlock {
        private:
            SwitchBlock *switchStm;
            std::vector<Command*> commands;

        public:
            static const CommandType CMD_TYPE = CMD_BREAK_BLOCK_DEFAULT;
            static const BreakableBlockType BREAK_BLOCK_TYPE = BREAK_BLOCK_DEFAULT;
            
            ~DefaultBlock();
            DefaultBlock(); 
            DefaultBlock(std::vector<Command*> commands);

            void setSwitch(SwitchBlock *switchStm);
            JsonNode *execute(Interpreter* interpreter);
        };

    } // mate

#endif //MATE_BREAKABLE_BLOCK_HH
