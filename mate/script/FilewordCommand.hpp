#ifndef MATE_FILEWORD_COMMAND_HH
    #define MATE_FILEWORD_COMMAND_HH
    
    #include <string>
    #include "../ast/Command.hpp"
    
    namespace mate
    {
        
        class FilewordCommand : public Command
        {
        private:
            std::string word;
        public:
            ~FilewordCommand();
            FilewordCommand(std::string word);

            static const CommandType CMD_TYPE = CMD_FILEWORD;

            JsonNode *execute();
        };
        
    } // mate

#endif //MATE_FILEWORD_COMMAND_HH
