#include "JsonInterpreter.hpp"

#include <sstream>

namespace mate
{

JsonInterpreter::JsonInterpreter(){
    scanner = new JsonScanner(*this);
    parser = new JsonParser(*scanner, *this);

}
JsonInterpreter::JsonInterpreter(std::istream *new_in){
    scanner = new JsonScanner(*this, new_in);
    parser = new JsonParser(*scanner, *this);
}
JsonInterpreter::JsonInterpreter(std::istream *new_in, std::ostream *new_os){
        scanner = new JsonScanner(*this, new_in, new_os);
        parser = new JsonParser(*scanner, *this);
}

int JsonInterpreter::parse() {
    location = 0;
    return parser->parse();
}

void JsonInterpreter::echo(const std::string s){
    scanner->echo(s);
}

JsonScanner *JsonInterpreter::getScanner(){
    return scanner;
}
JsonParser *JsonInterpreter::getParser(){
    return parser;
}

void JsonInterpreter::increaseLocation(unsigned int loc){
    location += loc;
}
unsigned int JsonInterpreter::getLocation() const{
    return location;
}
JsonObjectNode JsonInterpreter::getObject(){
    return obj;
}
void JsonInterpreter::setObject(JsonObjectNode object){
    obj = object;
}

void JsonInterpreter::setCurrentLine(unsigned int line) {
    currentLine = line;
}

unsigned int JsonInterpreter::getCurrentLine() const {
    return currentLine;
}
}
