#ifndef MATE_JSON_INTERPRETER_H
#define MATE_JSON_INTERPRETER_H

#include <vector>
#include <iostream>
#include <fstream>

#include "JsonScanner.hpp"
#include "JsonParser.hpp"
#include "../ast/Json.hpp"

namespace mate {

class Command;

class JsonInterpreter
{
public:
    JsonInterpreter();
    JsonInterpreter(std::istream* new_in);
    JsonInterpreter(std::istream *new_in, std::ostream *new_os);

    int parse();
    void echo(const std::string s);
    unsigned int getLocation() const;

    JsonObjectNode getObject();
    void setObject(JsonObjectNode object);

    JsonScanner *getScanner();
    JsonParser *getParser();
    unsigned int getCurrentLine() const;

    friend class JsonParser;
    friend class JsonScanner;

private:
    JsonObjectNode obj;
    JsonScanner *scanner;
    JsonParser *parser;
    unsigned int location;
    unsigned int currentLine;

private:
    void increaseLocation(unsigned int loc);
    void setCurrentLine(unsigned int loc);
};

}

#endif // MATE_JSONNTERPRETER_H
