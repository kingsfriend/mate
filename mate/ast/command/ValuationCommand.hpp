#ifndef MATE_VALUATION_COMMAND_HH
    #define MATE_VALUATION_COMMAND_HH
    
    #include <string>
    #include "Command.hpp"
    
    namespace mate
    {
        
        class ValuationCommand : public Command
        {
        private:
            std::string varKey;
        public:
            ~ValuationCommand();
            ValuationCommand(std::string varKey);

            static const CommandType CMD_TYPE = CMD_VALUATION;
            static const std::string VALUATION_NULL;

            JsonNode *execute(Interpreter* interpreter);
        };
        
    } // mate

#endif //MATE_VALUATION_COMMAND_HH
