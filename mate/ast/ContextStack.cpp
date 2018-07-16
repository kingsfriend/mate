#include "ContextStack.hpp"

namespace mate {
    ContextStack::~ContextStack(){ 
        clearAll();
    }

    ContextStack::ContextStack(){
        contextStack.push(new Context());
        lastGetSucceed = false;
    }

    Context *ContextStack::newContext(){
        Context * ctx = new Context();
        contextStack.push(ctx);
        lastGetSucceed = false;
        return ctx;
    }

    Context *ContextStack::context(){
        if(empty()){
            contextStack.push(new Context());
        }
        return contextStack.top();
    }

    int ContextStack::size(){
        return  contextStack.size();
    }

    bool ContextStack::empty(){
        return  contextStack.empty();
    }

    void ContextStack::clearLast(){
        lastGetSucceed = false;
        if (size() > 1){
            Context *ctx = contextStack.top();
            contextStack.pop();
            delete ctx;
            ctx = NULL;
        }
    }

    void ContextStack::clearAll(){
        while(!empty()){
            Context *ctx = contextStack.top();
            contextStack.pop();
            delete ctx;
            ctx = NULL;
        }
    }

    bool ContextStack::succeed(){
        return lastGetSucceed;
    }

    bool ContextStack::putVal(const std::string key, JsonNode *var){
       return context()->put(key, var);
    }

    bool ContextStack::setVal(const std::string key, JsonNode *var){
       return context()->put(key, var);
    }

    JsonNode *ContextStack::getVal(const std::string key){
        JsonNode *val=NULL;
        std::stack<Context *> copy = contextStack;
        lastGetSucceed = false;
        while(!copy.empty()){
            Context *ctx = copy.top();
            if(ctx->containt(key)){
                val = ctx->get(key);
                lastGetSucceed = true;
                break;
            }else{
                if(ctx->getType()==CONTEXT_ISOLATED){
                    break;
                }
                copy.pop();
            }
        }
        return val;
    }

}