#ifndef MATE_BASE_COMMAND_HH
    #define MATE_BASE_COMMAND_HH

    #include <memory>
    #include "Context.hpp"
    #include "Json.hpp"
    
    namespace mate{
    enum CommandType
    {
        CMD_BASE,
        CMD_EXP_NUM,
        CMD_EXP_BOOL,
        CMD_EXP_STR,
        CMD_EXP_DATE,
        CMD_CMP,
        CMD_CMP_BOOL,
        CMD_CMP_DATE,
        CMD_CMP_NUM,
        CMD_CMP_STRING
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
