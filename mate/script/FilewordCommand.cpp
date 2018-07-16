#include "FilewordCommand.hpp"

namespace mate
{
// FilewordCommand ----------------------

FilewordCommand::FilewordCommand(std::string word) : word(word) {}

FilewordCommand::~FilewordCommand(){}

JsonNode *FilewordCommand::execute(){

    return NULL;
}

} // namespace mate