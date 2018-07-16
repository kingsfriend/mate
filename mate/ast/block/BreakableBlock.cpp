#include "BreakableBlock.hpp"

namespace mate
{
// BreakCommand ----------------------

BreakCommand::~BreakCommand(){}
BreakCommand::BreakCommand(BreakableBlock* block)
    : block(block){}

BreakCommand::BreakCommand (){
    level = 0;
    block = NULL;
}

JsonNode *BreakCommand::execute(Interpreter* interpreter)
{
    if(block!=NULL){
        block->setBroken(true);
    }
    return  NULL;
}

// BreakableBlock ----------------------

BreakableBlock::~BreakableBlock(){}

BreakableBlock::BreakableBlock(): ConditionalBlock(NULL){}


BreakableBlock::BreakableBlock(ConditionExpression *condition) : ConditionalBlock(condition) {}

void BreakableBlock::setBroken(bool v){
    broken = v;
}

bool BreakableBlock::isBroken(){
    return broken;
}

// SwitchBlock ----------------------

SwitchBlock::~SwitchBlock(){}
SwitchBlock::SwitchBlock(JsonNode *baseNode): baseNode(baseNode){}

SwitchBlock::SwitchBlock(JsonNode *baseNode, std::vector<CaseBlock *> caseStms): baseNode(baseNode), caseStms(caseStms){
    int i, loopLimit = caseStms.size();
    for(i=0; i<loopLimit;i++){
        caseStms[i]->setSwitchStm(this);
    }
    defaultStm = NULL;
}

SwitchBlock::SwitchBlock(JsonNode *baseNode, DefaultBlock *defaultStm) : baseNode(baseNode), defaultStm(defaultStm) {
    if (defaultStm!=NULL){
        defaultStm->setSwitch(this);
    }
}

SwitchBlock::SwitchBlock(JsonNode *baseNode, std::vector<CaseBlock *> caseStms, DefaultBlock *defaultStm) : baseNode(baseNode), caseStms(caseStms), defaultStm(defaultStm) {
    int i, loopLimit = caseStms.size();
    for(i=0; i<loopLimit;i++){
        caseStms[i]->setSwitchStm(this);
    }
    if (defaultStm!=NULL){
        defaultStm->setSwitch(this);
    }
}

JsonNode *SwitchBlock::getBaseNode(){
    return baseNode;
}

JsonNode *SwitchBlock::execute(Interpreter* interpreter){
    if (!caseStms.empty()){
        int i, loopLimit = caseStms.size();
        setBroken(false);
        for (i = 0; i < loopLimit; i++)        {
            if (isBroken()){
                break;
            }else{
                caseStms[i]->execute(interpreter);
            }
        }
    }
    if (!isBroken()){
        if (defaultStm!=NULL&&!isBroken()){
            defaultStm->execute(interpreter);
        }
    }
    return NULL;
}

// CaseBlock ----------------------

CaseBlock::~CaseBlock(){}

CaseBlock::CaseBlock(JsonNode *compareNode): compareNode(compareNode){}

CaseBlock::CaseBlock(JsonNode *compareNode, std::vector<Command *> commands) 
    : compareNode(compareNode), commands(commands){}

void CaseBlock::setSwitchStm(SwitchBlock *v){
    switchStm = v;
}
JsonNode *CaseBlock::execute(Interpreter* interpreter){
    if(switchStm!=NULL){
        JsonNode *baseNode = switchStm->getBaseNode();
        JsonNode *cmpNode ;
        
        if( ((baseNode == cmpNode) && (baseNode== NULL)) || ((baseNode== NULL) && (baseNode->equals(cmpNode))) ){
            int i, loopLimit = commands.size();
            setBroken(false);
            for(i=0; i<loopLimit;i++){
                if(isBroken()){
                    break;
                }else{
                    Command* cmd = commands[i];
                    cmd->execute(interpreter);
                    if(cmd->CMD_TYPE==CMD_BREAK){
                        break;
                    }
                }
            }
        }
    }
    return NULL;
}

// DefaultBlock ----------------------

DefaultBlock::~DefaultBlock(){}
DefaultBlock::DefaultBlock(){}
DefaultBlock::DefaultBlock(std::vector<Command *> commands){

}

void DefaultBlock::setSwitch(SwitchBlock *v){
    switchStm = v;
}
JsonNode *DefaultBlock::execute(Interpreter* interpreter){
    int i, loopLimit = commands.size();
    setBroken(false);
    for(i=0; i<loopLimit;i++){
        if(isBroken()){
            break;
        }else{
            Command* cmd = commands[i];
            cmd->execute(interpreter);
            if(cmd->CMD_TYPE==CMD_BREAK){
                break;
            }
        }
    }
    return NULL;
}

} // namespace mate