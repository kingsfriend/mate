#include "Interpreter.hpp"

namespace mate
{

Interpreter::~Interpreter(){}

Interpreter::Interpreter() {}

Interpreter::Interpreter(ContextStack *contextStack)
    : contextStack(contextStack){
        location = 0;
        new_in = NULL;
        new_os = NULL;
    }

Interpreter::Interpreter(std::istream *new_in)
    : new_in(new_in){
        location = 0;
        new_in = NULL;
        contextStack = new ContextStack();
    }

Interpreter::Interpreter(ContextStack *contextStack, std::istream *new_in)
    : contextStack(contextStack){
        location = 0;
        new_os = NULL;
    }

Interpreter::Interpreter(std::istream *new_in, std::ostream *new_os)
    : new_in(new_in), new_os(new_os){
        location = 0;
        contextStack = new ContextStack();
    }

Interpreter::Interpreter(ContextStack *contextStack, std::istream *new_in, std::ostream *new_os)
    : contextStack(contextStack), new_in(new_in), new_os(new_os){
        location = 0;
    }

void Interpreter::clear() {
    location = 0;
    ctxStack()->clearAll();
}


ContextStack * Interpreter::ctxStack(){
     return  contextStack;
}

void Interpreter::increaseLocation(unsigned int loc) {
    location += loc;
}

unsigned int Interpreter::getLocation() const {
    return location;
}

} // namespace mate
