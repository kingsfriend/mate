#ifndef MATE_INTERPRETER_H
#define MATE_INTERPRETER_H

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

#include "context/ContextStack.hpp"
#include "context/Context.hpp"
#include "command/Command.hpp"

namespace mate {

class Command;
class Context;
class ContextStack;
class Interpreter
{
public:
    ~Interpreter();
    Interpreter();
    Interpreter(ContextStack *contextStack);
    Interpreter(std::istream* new_in);
    Interpreter(ContextStack *contextStack, std::istream *new_in);
    Interpreter(std::istream *new_in, std::ostream *new_os);
    Interpreter(ContextStack *contextStack, std::istream *new_in, std::ostream *new_os);

    virtual int parse()=0;
    virtual void echo(const std::string s) = 0;
    virtual void switchInputStream(std::istream *is, std::ostream *os) = 0;

    void clearAll();
    ContextStack *ctxStack();
    Context *context();
    void execute();
    void addCommand(Command *cmd);
    JsonNode* executeCommand(Command *cmd);

    protected : ContextStack *contextStack;
    std::istream *new_in;
    std::ostream *new_os;
    unsigned int location;

protected:
    void increaseLocation(unsigned int loc);
    unsigned int getLocation() const;
};

}

#endif // MATE_INTERPRETER_H
