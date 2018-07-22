#ifndef MATE_SCRIPT_INTERPRETER_H
#define MATE_SCRIPT_INTERPRETER_H

#include <vector>
#include <iostream>
#include <fstream>

#include "../ast/context/Context.hpp"
#include "../ast/command/Command.hpp"
#include "../ast/Interpreter.hpp"

#include "LangScanner.hpp"
#include "LangParser.hpp"

namespace mate {

class Command;

class LangInterpreter : public Interpreter
{
public:
    LangInterpreter();
    LangInterpreter(std::istream* new_in);
    LangInterpreter(std::istream *new_in, std::ostream *new_os);
    LangInterpreter(ContextStack *contextStack);
    LangInterpreter(ContextStack *contextStack, std::istream *new_in);
    LangInterpreter(ContextStack *contextStack, std::istream *new_in, std::ostream *new_os);

    int parse();
    void echo(const std::string s);
    void switchInputStream(std::istream *is, std::ostream *os);

    LangScanner *getScanner();
    LangParser *getParser();

    friend class LangParser;
    friend class LangScanner;
    
private:
    LangScanner* scanner;
    LangParser* parser;
};

}

#endif // MATE_SCRIPT_INTERPRETER_H
