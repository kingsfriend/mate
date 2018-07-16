#ifndef MATE_BREAKABLE_STATEMENT_HH
    #define MATE_BREAKABLE_STATEMENT_HH

    #include "ConditionalStatement.hpp"

    namespace mate
    {
        class BreakableStatement;
        class CaseStatement;
        class DefaultStatement;

        class BreakCommand : public Command
        {
        private:
            double level;
            BreakableStatement* statement;
        public:
            BreakCommand();
            BreakCommand(BreakableStatement *statement);
            ~BreakCommand();

            static const CommandType CMD_TYPE = CMD_BREAK;

            BreakableStatement *getStatement();
            void setStatement(BreakableStatement *stm);

            JsonNode *execute();
        };

        enum BreakableStatementType{
            BREAK_STM,
            BREAK_STM_SWITCH,
            BREAK_STM_CASE,
            BREAK_STM_DEFAULT,
            BREAK_STM_FOR,
            BREAK_STM_FOREACH,
            BREAK_STM_WHILE,
        };

        class BreakableStatement : public ConditionalStatement{
        private:
            bool broken;

        public:
            static const CommandType CMD_TYPE = CMD_BREAK_EXP;
            static const BreakableStatementType BREAK_STM_TYPE = BREAK_STM;
            
            ~BreakableStatement();
            BreakableStatement();
            BreakableStatement(ConditionExpression *condition);

            void setBroken(bool v);
            bool isBroken();
        };

        class SwitchStatement : public BreakableStatement{
        private:
            JsonNode* baseNode;
            std::vector<CaseStatement*> caseStms;
            DefaultStatement* defaultStm;

        public:
            static const CommandType CMD_TYPE = CMD_BREAK_STM_SWITCH;
            static const BreakableStatementType BREAK_STM_TYPE = BREAK_STM_SWITCH;
            
            ~SwitchStatement();
            SwitchStatement(JsonNode *baseNode); 
            SwitchStatement(JsonNode *baseNode, std::vector<CaseStatement*> caseStms);
            SwitchStatement(JsonNode *baseNode, std::vector<CaseStatement *> caseStms, DefaultStatement *defaultStm);
            SwitchStatement(JsonNode *baseNode, DefaultStatement *defaultStm);

            JsonNode* getBaseNode();
            JsonNode* execute();
        };

        class CaseStatement : public BreakableStatement {
        private:
            SwitchStatement *switchStm;
            JsonNode* compareNode;
            std::vector<Command*> commands;

        public:
            static const CommandType CMD_TYPE = CMD_BREAK_STM_CASE;
            static const BreakableStatementType BREAK_STM_TYPE = BREAK_STM_CASE;
            
            ~CaseStatement();
            CaseStatement(JsonNode *compareNode);
            CaseStatement(JsonNode *compareNode, std::vector<Command*> commands);

            void setSwitchStm(SwitchStatement *switchStm);
            JsonNode* execute();

        };

        class DefaultStatement : public BreakableStatement {
        private:
            SwitchStatement *switchStm;
            std::vector<Command*> commands;

        public:
            static const CommandType CMD_TYPE = CMD_BREAK_STM_DEFAULT;
            static const BreakableStatementType BREAK_STM_TYPE = BREAK_STM_DEFAULT;
            
            ~DefaultStatement();
            DefaultStatement(); 
            DefaultStatement(std::vector<Command*> commands);

            void setSwitch(SwitchStatement *switchStm);
            JsonNode* execute();
        };

    } // mate

#endif //MATE_BREAKABLE_STATEMENT_HH
