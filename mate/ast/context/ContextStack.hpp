#ifndef MATE_CONTEXT_STACK_HH
#define MATE_CONTEXT_STACK_HH

#include <stack>
#include "Context.hpp"
#include "../Interpreter.hpp"
#include "../command/Command.hpp"

using namespace std;
namespace mate
{
    class Command;
    class Context;
    class Interpreter;
    class ContextStack
    {
    public:
        ContextStack();
        ~ContextStack();
        
        Context *newContext();
        Context *context();
        int size();
        bool empty();
        void clearLastContext();
        bool succeed();
        void clearAllContexts();

        void clearContext();
        void clearContextVars();
        void clearContextCommands();

        bool putVal(const std::string, JsonNode *var);
        bool setVal(const std::string, JsonNode* var);
        JsonNode* getVal(const std::string);

      private:
        stack<Context *> contextStack;
        bool lastGetSucceed;
    };

} // mate

#endif //MATE_CONTEXT_STACK_HH
