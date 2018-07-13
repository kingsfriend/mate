#ifndef MATE_BASE_COMMAND_HH
    #define MATE_BASE_COMMAND_HH

#include "Context.hpp"

    namespace mate{
        enum CommandType
        {
            BASE
        };
        
        class Command
        {
        private:
            Context context;

        public:
            static const CommandType TYPE;
            static std::string execute(Context ctx);
            static std::string toString();

            virtual std::string execute();

            Command(Context ctx);
            ~Command();

        };
        
    }

#endif //MATE_BASE_COMMAND_HH
