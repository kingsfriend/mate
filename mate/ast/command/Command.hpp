#ifndef MATE_COMMAND_HH
    #define MATE_COMMAND_HH

    #include <memory>
    #include "../Json.hpp"
    #include "../Interpreter.hpp"
    
    namespace mate{
    enum CommandType
    {
        CMD_BASE,
        CMD_ECHO,
        CMD_VALUATION,
        CMD_EXP,
        CMD_EXP_ASSIGN,
        CMD_EXP_PRIM,
        CMD_EXP_PRIM_CAST,
        CMD_EXP_PRIM_NUM,
        CMD_EXP_PRIM_STR,
        CMD_EXP_PRIM_DATE,
        CMD_EXP_PRIM_BOOL,
        CMD_EXP_PRIM_INDENTFIER,
        CMD_EXP_PRIM_ARRAY,
        CMD_EXP_PRIM_OBJECT,
        CMD_EXP_VAL_ASSIGN,
        CMD_EXP_VAR_DECLARATION,
        CMD_EXP_UNARY,
    };

    class Interpreter;
    class Context;
    class Command
    {
      private:
      public:
        static const CommandType CMD_TYPE = CMD_BASE;

        std::string toString();

        virtual JsonNode *execute(Interpreter* interpreter) = 0;

        Command();
        ~Command();

        };
        
    }

#endif //MATE_COMMAND_HH
