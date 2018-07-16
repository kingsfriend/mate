#include "Command.hpp"

namespace mate
{
    Command::Command(){}

    Command::~Command(){}

    std::string Command::toString(){
        std:: string r("{}");
        return r;
    }
}