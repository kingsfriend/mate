#include "Context.hpp"

namespace mate {
    Context::Context(){
        this->breakFlag = false;
        this->continueFlag = false;
        this->type = CONTEXT_NAVIGABLE;
    }
    Context::Context(ContextType type){
        this->breakFlag = false;
        this->continueFlag = false;
        this->type = type;
    }
    
    Context::~Context(){}

    ContextType Context::getType(){
        return type;
    }

    bool Context::hasBreak(){
        return breakFlag;
    }

    bool Context::hasContinue(){
        return continueFlag;
    }

    void Context::clearBreak(){
        breakFlag = false;
    }
    
    void Context::clearContinue(){
        continueFlag = false;
    }

    void Context::doBreak(){
        breakFlag = true;
    }

    void Context::doContinue(){
        continueFlag = true;
    }

    bool Context::put(const std::string key, JsonNode* var){
        if (!containt(key)){
            vars[key]= var;
            return true;
        }
        return false;
    }

    bool Context::set(const std::string key, JsonNode* var){
        if (containt(key)){
            vars[key] = var;
            return true;
        }
        return false;
    }
    
    JsonNode* Context::get(const std::string key){
        JsonNode *node = NULL;
        if(containt(key)){
            return vars[key];
        }
        return node;
    }

    bool Context::containt(const std::string key){
        std::map<const std::string, JsonNode *>::iterator it = vars.find(key);
        return it != vars.end();
    }

    bool Context::remove(const std::string key){
        if (containt(key)){
            vars.erase(key);
            return true;
        }
        return false;
    }

    void Context::clear(){
        clearVars();
        clearCommands();
    }

    void Context::clearVars(){
        vars.clear();
    }

    void Context::clearCommands(){
        commands.clear();
    }

    void Context::addCommand(Command *cmd){
        commands.push_back(cmd) ;
    }

    void Context::execute(Interpreter *interpreter){
        int i;
        int loopLimit = commands.size();
        for (i = 0; i < loopLimit; i++){
            commands[i]->execute(interpreter);
        }
    }
}