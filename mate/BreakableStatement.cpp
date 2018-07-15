#include "BreakableStatement.hpp"

namespace mate
{
// BreakCommand ----------------------

BreakCommand::~BreakCommand(){}
BreakCommand::BreakCommand(double level, BreakableStatement* breakStm)
    : breakLevel(level), breakStm(breakStm){}

BreakCommand::BreakCommand (){
    breakLevel = 0;
    breakStm = NULL;
}

BreakCommand::BreakCommand(double level) : breakLevel(level) {
    breakStm = NULL;
}

JsonNode* BreakCommand::execute(){
    int level = breakLevel;
    if(breakStm!=NULL && level>0){
        BreakableStatement* parent = breakStm->getParent();
        while(level>0&&parent!=NULL){
            parent->setBroken(true);
            parent = parent->getParent();
            level--;
        }
    }
    return  NULL;
}

// BreakableStatement ----------------------

BreakableStatement::~BreakableStatement(){}
BreakableStatement::BreakableStatement(){}
BreakableStatement::BreakableStatement(BreakableStatement *parent):parent(parent){}

void BreakableStatement::setBroken(bool v){
    broken = v;
}

void BreakableStatement::setParent(BreakableStatement *parent){
    parent = parent;
}


BreakableStatement* BreakableStatement::getParent(){
    return parent;
}

double BreakableStatement::isBroken(){
    return broken;
}

// SwitchStatement ----------------------

SwitchStatement::~SwitchStatement(){}
SwitchStatement::SwitchStatement(JsonNode *baseNode): baseNode(baseNode){}

SwitchStatement::SwitchStatement(JsonNode *baseNode, std::vector<CaseStatement *> caseStms): baseNode(baseNode), caseStms(caseStms){
    int i, loopLimit = caseStms.size();
    for(i=0; i<loopLimit;i++){
        caseStms[i]->setSwitchStm(this);
    }
    defaultStm = NULL;
}

SwitchStatement::SwitchStatement(JsonNode *baseNode, DefaultStatement *defaultStm) : baseNode(baseNode), defaultStm(defaultStm) {
    if (defaultStm!=NULL){
        defaultStm->setSwitch(this);
    }
}

SwitchStatement::SwitchStatement(JsonNode *baseNode, std::vector<CaseStatement *> caseStms, DefaultStatement *defaultStm) : baseNode(baseNode), caseStms(caseStms), defaultStm(defaultStm) {
    int i, loopLimit = caseStms.size();
    for(i=0; i<loopLimit;i++){
        caseStms[i]->setSwitchStm(this);
    }
    if (defaultStm!=NULL){
        defaultStm->setSwitch(this);
    }
}

JsonNode *SwitchStatement::getBaseNode(){
    return baseNode;
}

JsonNode *SwitchStatement::execute(){
    if (!caseStms.empty()){
        int i, loopLimit = caseStms.size();
        setBroken(false);
        for (i = 0; i < loopLimit; i++)
        {
            if (isBroken()){
                break;
            }else{
                caseStms[i]->execute();
            }
        }
    }
    if (!isBroken()){
        if (defaultStm!=NULL&&!isBroken()){
            defaultStm->execute();
        }
    }
    return NULL;
}

// CaseStatement ----------------------

CaseStatement::~CaseStatement(){}

CaseStatement::CaseStatement(JsonNode *compareNode): compareNode(compareNode){}

CaseStatement::CaseStatement(JsonNode *compareNode, std::vector<Command *> commands) 
    : compareNode(compareNode), commands(commands){}

void CaseStatement::setSwitchStm(SwitchStatement *v){
    switchStm = v;
}
JsonNode *CaseStatement::execute(){
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
                    cmd->execute();
                    if(cmd->CMD_TYPE==CMD_BREAK){
                        break;
                    }
                }
            }
        }
    }
    return NULL;
}

// DefaultStatement ----------------------

DefaultStatement::~DefaultStatement(){}
DefaultStatement::DefaultStatement(){}
DefaultStatement::DefaultStatement(std::vector<Command *> commands){

}

void DefaultStatement::setSwitch(SwitchStatement *v){
    switchStm = v;
}
JsonNode *DefaultStatement::execute(){
    int i, loopLimit = commands.size();
    setBroken(false);
    for(i=0; i<loopLimit;i++){
        if(isBroken()){
            break;
        }else{
            Command* cmd = commands[i];
            cmd->execute();
            if(cmd->CMD_TYPE==CMD_BREAK){
                break;
            }
        }
    }
    return NULL;
}

} // namespace mate