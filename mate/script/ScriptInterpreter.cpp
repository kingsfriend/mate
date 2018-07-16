#include "ScriptInterpreter.hpp"
#include "../Command.hpp"

#include <sstream>

using namespace mate;

ScriptInterpreter::ScriptInterpreter() :
     commands(),
    location(0)
{
    scanner = new ScriptScanner(*this);
    parser = new ScriptParser(*scanner, *this);
}
ScriptInterpreter::ScriptInterpreter(std::istream *new_in) :  commands(),
                                                             location(0)
{
    scanner = new ScriptScanner(*this, new_in);
    parser = new ScriptParser(*scanner, *this);
}
ScriptInterpreter::ScriptInterpreter(std::istream *new_in, std::ostream *new_os) :  commands(),
                                                                                   location(0)
{
    scanner = new ScriptScanner(*this, new_in, new_os);
    parser = new ScriptParser(*scanner, *this);
}

int ScriptInterpreter::parse() {
    location = 0;
    return parser->parse();
}

void ScriptInterpreter::clear() {
    location = 0;
     commands.clear();
}

std::string ScriptInterpreter::str() const {

}

void ScriptInterpreter::switchInputStream(std::istream *is, std::ostream *os){
    scanner->switch_streams(is, os);
     commands.clear();    
}

void ScriptInterpreter::addCommand(Command* cmd){
     commands.push_back(cmd);
}

void ScriptInterpreter::increaseLocation(unsigned int loc) {
    location += loc;
}

unsigned int ScriptInterpreter::getLocation() const {
    return location;
}
