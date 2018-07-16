#ifndef MATE_COMMAND_BLOCK_HH
    #define MATE_COMMAND_BLOCK_HH
    
    #include "../Command.hpp"
    
    namespace mate
    {
        enum BlockType{
            BLOCK,
            BLOCK_STRING,
            BLOCK_NUM,
            BLOCK_DATE,
            BLOCK_CMP,
            BLOCK_BOOL,
            BLOCK_,
        };

        class CommandBlock : public Command
        {
        public:
          ~CommandBlock();

          static const CommandType CMD_TYPE = CMD_BLOCK;
          static const BlockType BLOCK_TYPE = BLOCK;

        protected:
          CommandBlock();
        };
        
    } // mate

#endif //MATE_COMMAND_BLOCK_HH
