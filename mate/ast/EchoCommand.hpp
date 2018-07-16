#ifndef MATE_ECHO_COMMAND_HH
    #define MATE_ECHO_COMMAND_HH
    
    #include <string>
    #include "Command.hpp"
    
    namespace mate
    {
        
        class EchoCommand : public Command
        {
        private:
            std::string word;
        public:
            ~EchoCommand();
            EchoCommand(std::string word);

            static const CommandType CMD_TYPE = CMD_ECHO;

            JsonNode *execute();
        };
        
    } // mate

#endif //MATE_ECHO_COMMAND_HH
