#include "ScriptInterpreter.hpp"

#include <sstream>

namespace mate
{

ScriptInterpreter::ScriptInterpreter(){
    scanner = new ScriptScanner(*this);
    parser = new ScriptParser(*scanner, *this);

}
ScriptInterpreter::ScriptInterpreter(std::istream *new_in) : Interpreter(new_in){
    scanner = new ScriptScanner(*this, new_in);
    parser = new ScriptParser(*scanner, *this);
}
ScriptInterpreter::ScriptInterpreter(std::istream *new_in, std::ostream *new_os)
    : Interpreter(new_in,new_os){
        scanner = new ScriptScanner(*this, new_in, new_os);
        parser = new ScriptParser(*scanner, *this);
}

ScriptInterpreter::ScriptInterpreter(ContextStack *contextStack)
    : Interpreter(contextStack){

}
ScriptInterpreter::ScriptInterpreter(ContextStack *contextStack, std::istream *new_in)
    : Interpreter(contextStack, new_in){

}
ScriptInterpreter::ScriptInterpreter(ContextStack *contextStack, std::istream *new_in, std::ostream *new_os)
    : Interpreter(contextStack, new_in, new_os){

}

int ScriptInterpreter::parse() {
    location = 0;
    return parser->parse();
}

void ScriptInterpreter::echo(const std::string s){
    scanner->echo(s);
}

void ScriptInterpreter::switchInputStream(std::istream *is, std::ostream *os){
    new_in = is;
    new_os = os;
    scanner->switch_streams(is, os);
    clearAll();    
}

ScriptScanner *ScriptInterpreter::getScanner(){
    return scanner;
}
ScriptParser *ScriptInterpreter::getParser(){
    return parser;
}
}