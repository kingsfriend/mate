#include "Command.hpp"

namespace mate
{
    const CommandType Command::TYPE = BASE;
    
    Command::Command(Context ctx): context(ctx){

    }


    Command::~Command(){
        
    }

    std::string Command::execute(Context ctx){

    }

    std::string Command::execute(){

    }

    std::string Command::toString(){

    }
}