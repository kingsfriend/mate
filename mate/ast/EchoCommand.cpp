#include "EchoCommand.hpp"

namespace mate
{
// EchoCommand ----------------------

EchoCommand::EchoCommand(std::string word) : word(word) {}

EchoCommand::~EchoCommand(){}

JsonNode *EchoCommand::execute(Interpreter* interpreter){

    return NULL;
}

} // namespace mate