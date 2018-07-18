#ifndef MATE_COMMAND_HH
    #define MATE_COMMAND_HH

    #include <memory>
    #include "../Json.hpp"
    #include "../Interpreter.hpp"
    
    namespace mate{
    enum CommandType
    {
        CMD_BASE,
        CMD_EXP,
        CMD_ECHO,
        CMD_VALUATION,
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
