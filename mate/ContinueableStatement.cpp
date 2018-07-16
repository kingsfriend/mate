#include "ContinueableStatement.hpp"

namespace mate
{
// ContinueCommand ----------------------

ContinueCommand::~ContinueCommand(){}
ContinueCommand::ContinueCommand(ContinueableStatement *continueStm)
    : statement(continueStm) {}

ContinueCommand::ContinueCommand (){
    statement = NULL;
}


JsonNode* ContinueCommand::execute(){
    if(statement!=NULL){
        statement->setContinued(true);
    }
    return  NULL;
}

// ContinueableStatement ----------------------

ContinueableStatement::~ContinueableStatement(){}
ContinueableStatement::ContinueableStatement(){}

ContinueableStatement::ContinueableStatement(ConditionExpression *condition)
    : BreakableStatement(condition){}

void ContinueableStatement::setContinued(bool v){
    continued = v;
}

bool ContinueableStatement::isContinued(){
    return continued;
}

// WhileStatement ----------------------

WhileStatement::~WhileStatement(){}
WhileStatement::WhileStatement(ConditionExpression *condition) 
    : ContinueableStatement(condition) {}

WhileStatement::WhileStatement(ConditionExpression *condition, std::vector<Command *> commands) 
    : ContinueableStatement(condition), commands(commands){}


JsonNode *WhileStatement::execute(){
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

// ForStatement ----------------------

ForStatement::~ForStatement(){}
ForStatement::ForStatement(std::vector<Expression *> expInits, std::vector<Expression *> expIncrs, std::vector<ConditionExpression *> expConds){}
ForStatement::ForStatement(std::vector<Expression *> expInits, std::vector<Expression *> expIncrs, std::vector<ConditionExpression *> expConds, std::vector<Command *> commands){}

std::vector<Expression *> ForStatement::getExpInit(){
    return expInits;
}
std::vector<Expression *> ForStatement::getExpIncr(){
    return expIncrs;
}
std::vector<ConditionExpression *> ForStatement::getExpCond(){
    return expConds;
}
std::vector<Command *> ForStatement::getCommands(){
    return commands;
}
void ForStatement::setExpInit(std::vector<Expression *> expInits){
    this->expInits = expInits;
}
void ForStatement::setExpIncr(std::vector<Expression *> expIncrs){
    this->expIncrs = expIncrs;
}
void ForStatement::setExpCond(std::vector<ConditionExpression *> expConds){
    this->expConds = expConds;
}
void ForStatement::setCommands(std::vector<Command *> commands){
    this->commands = commands;
}

bool ForStatement::valuateConditions(){
        bool valuation = true;
    if (!expConds.empty()){
        int i, loopLimit = expConds.size();
        for (i = 0; i < loopLimit; i++){
            valuation = valuation && expConds[i]->executeAsBool();
        }
    }
    return valuation;
}

void ForStatement::executeIncrs(){
    if (!expIncrs.empty()){
        int i, loopLimit = expIncrs.size();
        for (i = 0; i < loopLimit; i++){
            expIncrs[i]->execute();
        }
    }
}

void ForStatement::executeInits(){
    if (!expInits.empty()){
        int i, loopLimit = expInits.size();
        for (i = 0; i < loopLimit; i++){
            expInits[i]->execute();
        }
    }
}

JsonNode *ForStatement::execute(){
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

// ForeachStatement ----------------------

ForeachStatement::~ForeachStatement(){}

ForeachStatement::ForeachStatement(JsonArrayNode *array, JsonNode *item)
    : array(array), currentItem(item){
        currentItemIndex = 0;
    }
ForeachStatement::ForeachStatement(JsonArrayNode *array, JsonNode *item, std::vector<Command *> commands)
    : array(array), currentItem(item), commands(commands) {
        currentItemIndex = 0;
    }
ForeachStatement::ForeachStatement(JsonArrayNode *array, JsonNode *item, std::vector<Command *> commands, std::vector<Command *> emptyCommands)
    : array(array), currentItem(item), commands(commands), emptyCommands(emptyCommands) {
        currentItemIndex = 0;
    }

bool ForeachStatement::updateCurrentItem(){
    if(array!=NULL || currentItemIndex < array->size()>0){
        currentItem = array->get(++currentItemIndex);
        return true;
    }
    return false;
}

void ForeachStatement::resetIndex(){
    currentItem = NULL;
    currentItemIndex = 0;
}

JsonNode *ForeachStatement::execute(){
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