#include "Context.hpp"

namespace mate {
    Context::Context(){}
    
    Context::~Context(){}

    unsigned int Context::nextKey(){
        
    }
    unsigned int Context::getKey(){

    }
    
    Context* Context::getParent(){

    }
    void Context::setParent(Context* c){

    }
    
    void Context::setChild(Context* c){

    }
    Context* Context::getChild(){

    }

    void Context::put(const std::string, JsonNode* var){

    }
    void Context::set(const std::string, JsonNode* var){

    }
    JsonNode* Context::get(const std::string){

    }
    void Context::remove(const std::string){

    }
    void Context::clear(){

    }
}