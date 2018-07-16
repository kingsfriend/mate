#include "ContinueableBlock.hpp"

namespace mate
{
// ContinueCommand ----------------------

ContinueCommand::~ContinueCommand(){}
ContinueCommand::ContinueCommand(ContinueableBlock *continueStm)
    : block(continueStm) {}

ContinueCommand::ContinueCommand (){
    block = NULL;
}


JsonNode* ContinueCommand::execute(){
    if(block!=NULL){
        block->setContinued(true);
    }
    return  NULL;
}

// ContinueableBlock ----------------------

ContinueableBlock::~ContinueableBlock(){}
ContinueableBlock::ContinueableBlock(){}

ContinueableBlock::ContinueableBlock(ConditionExpression *condition)
    : BreakableBlock(condition){}

void ContinueableBlock::setContinued(bool v){
    continued = v;
}

bool ContinueableBlock::isContinued(){
    return continued;
}

// WhileBlock ----------------------

WhileBlock::~WhileBlock(){}
WhileBlock::WhileBlock(ConditionExpression *condition) 
    : ContinueableBlock(condition) {}

WhileBlock::WhileBlock(ConditionExpression *condition, std::vector<Command *> commands) 
    : ContinueableBlock(condition), commands(commands){}


JsonNode *WhileBlock::execute(){
    if (!commands.empty()){
        int i, loopLimit = commands.size();
        setBroken(false);
        while(valuateCondition()){
            int i, loopLimit = commands.size();
            setContinued(false);
            for (i = 0; i < loopLimit; i++)        {
                if (isBroken() || isContinued()){
                    break;
                }else{
                    commands[i]->execute();
                }
            }
            if (isBroken()){
                break;
            }else if(isContinued()){
                continue;
            }
        }
    }
    return NULL;
}

// ForBlock ----------------------

ForBlock::~ForBlock(){}
ForBlock::ForBlock(std::vector<Expression *> expInits, std::vector<Expression *> expIncrs, std::vector<ConditionExpression *> expConds){}
ForBlock::ForBlock(std::vector<Expression *> expInits, std::vector<Expression *> expIncrs, std::vector<ConditionExpression *> expConds, std::vector<Command *> commands){}

std::vector<Expression *> ForBlock::getExpInit(){
    return expInits;
}
std::vector<Expression *> ForBlock::getExpIncr(){
    return expIncrs;
}
std::vector<ConditionExpression *> ForBlock::getExpCond(){
    return expConds;
}
std::vector<Command *> ForBlock::getCommands(){
    return commands;
}
void ForBlock::setExpInit(std::vector<Expression *> expInits){
    this->expInits = expInits;
}
void ForBlock::setExpIncr(std::vector<Expression *> expIncrs){
    this->expIncrs = expIncrs;
}
void ForBlock::setExpCond(std::vector<ConditionExpression *> expConds){
    this->expConds = expConds;
}
void ForBlock::setCommands(std::vector<Command *> commands){
    this->commands = commands;
}

bool ForBlock::valuateConditions(){
        bool valuation = true;
    if (!expConds.empty()){
        int i, loopLimit = expConds.size();
        for (i = 0; i < loopLimit; i++){
            valuation = valuation && expConds[i]->executeAsBool();
        }
    }
    return valuation;
}

void ForBlock::executeIncrs(){
    if (!expIncrs.empty()){
        int i, loopLimit = expIncrs.size();
        for (i = 0; i < loopLimit; i++){
            expIncrs[i]->execute();
        }
    }
}

void ForBlock::executeInits(){
    if (!expInits.empty()){
        int i, loopLimit = expInits.size();
        for (i = 0; i < loopLimit; i++){
            expInits[i]->execute();
        }
    }
}

JsonNode *ForBlock::execute(){
    if (!commands.empty()){
        int i, loopLimit = commands.size();
        setBroken(false);
        executeInits();
        while(valuateConditions()){
            int i, loopLimit = commands.size();
            setContinued(false);
            for (i = 0; i < loopLimit; i++)        {
                if (isBroken() || isContinued()){
                    break;
                }else{
                    commands[i]->execute();
                }
            }
            executeIncrs();
            if (isBroken()){
                break;
            }else if(isContinued()){
                continue;
            }
        }
    }
    return NULL;
}

// ForeachBlock ----------------------

ForeachBlock::~ForeachBlock(){}

ForeachBlock::ForeachBlock(JsonArrayNode *array, JsonNode *item)
    : array(array), currentItem(item){
        currentItemIndex = 0;
    }
ForeachBlock::ForeachBlock(JsonArrayNode *array, JsonNode *item, std::vector<Command *> commands)
    : array(array), currentItem(item), commands(commands) {
        currentItemIndex = 0;
    }
ForeachBlock::ForeachBlock(JsonArrayNode *array, JsonNode *item, std::vector<Command *> commands, std::vector<Command *> emptyCommands)
    : array(array), currentItem(item), commands(commands), emptyCommands(emptyCommands) {
        currentItemIndex = 0;
    }

bool ForeachBlock::updateCurrentItem(){
    if(array!=NULL || currentItemIndex < array->size()>0){
        currentItem = array->get(++currentItemIndex);
        return true;
    }
    return false;
}

void ForeachBlock::resetIndex(){
    currentItem = NULL;
    currentItemIndex = 0;
}

JsonNode *ForeachBlock::execute(){
    if (!commands.empty()){
        int i, loopLimit = commands.size();
        setBroken(false);
        resetIndex();
        while(updateCurrentItem()){
            int i, loopLimit = commands.size();
            setContinued(false);
            for (i = 0; i < loopLimit; i++)        {
                if (isBroken() || isContinued()){
                    break;
                }else{
                    commands[i]->execute();
                }
            }
            if (isBroken()){
                break;
            }else if(isContinued()){
                continue;
            }
        }
    }
    return NULL;
}


} // namespace mate