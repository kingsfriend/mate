#ifndef MATE_SCRIPT_INTERPRETER_H
#define MATE_SCRIPT_INTERPRETER_H

#include <vector>
#include <iostream>
#include <fstream>

#include "../ast/Context.hpp"
#include "../ast/Command.hpp"
#include "../ast/Interpreter.hpp"

#include "ScriptScanner.hpp"
#include "ScriptParser.hpp"

namespace mate {

class Command;

class ScriptInterpreter : public Interpreter
{
public:
    ScriptInterpreter();
    ScriptInterpreter(std::istream* new_in);
    ScriptInterpreter(std::istream *new_in, std::ostream *new_os);
    ScriptInterpreter(ContextStack *contextStack);
    ScriptInterpreter(ContextStack *contextStack, std::istream *new_in);
    ScriptInterpreter(ContextStack *contextStack, std::istream *new_in, std::ostream *new_os);

    int parse();
    void echo(const std::string s);
    void switchInputStream(std::istream *is, std::ostream *os);

    ScriptScanner *getScanner();
    ScriptParser *getParser();

    friend class ScriptParser;
    friend class ScriptScanner;
    
private:
    ScriptScanner* scanner;
    ScriptParser* parser;
};

}

#endif // MATE_SCRIPT_INTERPRETER_H
