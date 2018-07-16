#ifndef MATE_COMMAND_HH
    #define MATE_COMMAND_HH

    #include <memory>
    #include "Json.hpp"
    
    namespace mate{
    enum CommandType
    {
        CMD_BASE,
        CMD_EXP,
        CMD_EXP_NUM,
        CMD_EXP_BOOL,
        CMD_EXP_STR,
        CMD_EXP_DATE,
        CMD_BLOCK,
        CMD_CMP,
        CMD_CMP_BOOL,
        CMD_CMP_DATE,
        CMD_CMP_NUM,
        CMD_CMP_STRING,
        CMD_COND_EXP,
        CMD_COND_BLOCK_IF,
        CMD_BREAK,
        CMD_BREAK_EXP,
        CMD_BREAK_BLOCK_SWITCH,
        CMD_BREAK_BLOCK_CASE,
        CMD_BREAK_BLOCK_DEFAULT,
        CMD_CONTINUE,
        CMD_CONTINUE_EXP,
        CMD_CONTINUE_BLOCK_WHILE,
        CMD_CONTINUE_BLOCK_FOR,
        CMD_CONTINUE_BLOCK_FOREACH,
        CMD_ECHO,
    };

    class Context;
    class Command
    {
      private:
      public:
        static const CommandType CMD_TYPE = CMD_BASE;

        std::string toString();

        virtual JsonNode *execute() = 0;

        Command();
        ~Command();

        };
        
    }

#endif //MATE_COMMAND_HH
