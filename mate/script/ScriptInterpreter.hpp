#ifndef MATE_SCRIPT_INTERPRETER_H
#define MATE_SCRIPT_INTERPRETER_H

#include <vector>
#include <iostream>
#include <fstream>

#include "ScriptScanner.hpp"
#include "ScriptParser.hpp"
#include "../Context.hpp"

namespace mate {

class Command;

class ScriptInterpreter
{
public:
    ScriptInterpreter();
    ScriptInterpreter(std::istream* new_in);
    ScriptInterpreter(std::istream *new_in, std::ostream *new_os);

    int parse();
    void clear();
    void echo(const std::string s);

    std::string str() const;

    void switchInputStream(std::istream *is, std::ostream *os);

    friend class ScriptParser;
    friend class ScriptScanner;
    
private:
    void addCommand(const Command &cmd);
    void increaseLocation(unsigned int loc);
    unsigned int getLocation() const;
    
private:
    ScriptScanner* scanner;
    ScriptParser* parser;
    std::vector<Command>  commands;
    mate::Context context;
    unsigned int location;
};

}

#endif // MATE_SCRIPT_INTERPRETER_H
