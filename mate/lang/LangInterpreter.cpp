#include "LangInterpreter.hpp"

#include <sstream>

namespace mate
{

LangInterpreter::LangInterpreter(){
    scanner = new LangScanner(*this);
    parser = new LangParser(*scanner, *this);

}
LangInterpreter::LangInterpreter(std::istream *new_in) : Interpreter(new_in){
    scanner = new LangScanner(*this, new_in);
    parser = new LangParser(*scanner, *this);
}
LangInterpreter::LangInterpreter(std::istream *new_in, std::ostream *new_os)
    : Interpreter(new_in,new_os){
        scanner = new LangScanner(*this, new_in, new_os);
        parser = new LangParser(*scanner, *this);
}

LangInterpreter::LangInterpreter(ContextStack *contextStack)
    : Interpreter(contextStack){

}
LangInterpreter::LangInterpreter(ContextStack *contextStack, std::istream *new_in)
    : Interpreter(contextStack, new_in){

}
LangInterpreter::LangInterpreter(ContextStack *contextStack, std::istream *new_in, std::ostream *new_os)
    : Interpreter(contextStack, new_in, new_os){

}

int LangInterpreter::parse() {
    location = 0;
    return parser->parse();
}

void LangInterpreter::echo(const std::string s){
    scanner->echo(s);
}

void LangInterpreter::switchInputStream(std::istream *is, std::ostream *os){
    new_in = is;
    new_os = os;
    scanner->switch_streams(is, os);
    clearAll();    
}

LangScanner *LangInterpreter::getScanner(){
    return scanner;
}
LangParser *LangInterpreter::getParser(){
    return parser;
}
}