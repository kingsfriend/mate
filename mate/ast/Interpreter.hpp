#ifndef MATE_INTERPRETER_H
#define MATE_INTERPRETER_H

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

#include "ContextStack.hpp"
#include "Command.hpp"

namespace mate {

class Command;

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

    void clear();
    ContextStack *ctxStack();

protected:
    ContextStack* contextStack;
    std::istream *new_in;
    std::ostream *new_os;
    unsigned int location;

protected:
    void increaseLocation(unsigned int loc);
    unsigned int getLocation() const;
};

}

#endif // MATE_INTERPRETER_H
