#ifndef MATE_BASE_COMMAND_HH
    #define MATE_BASE_COMMAND_HH

    #include <memory>
    #include "Context.hpp"
    #include "Json.hpp"
    
    namespace mate{
    enum CommandType
    {
        CMD_BASE,
        CMD_NUM_EXP,
        CMD_BOOL_EXP,
        CMD_STR_EXP
    };

    class Command
    {
      private:
      public:
        static const CommandType CMD_TYPE = CMD_BASE;

        std::string toString();

        virtual JsonNode *execute() = 0;
        virtual void update() = 0;

        Command();
        ~Command();

        };
        
    }

#endif //MATE_BASE_COMMAND_HH
