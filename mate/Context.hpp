#ifndef MATE_CONTEXT_HH
#define MATE_CONTEXT_HH

#include <map>
#include <iterator>
#include <string>
#include "Json.hpp"

using namespace std;
namespace mate
{
    enum ContextType{
        CONTEXT_ISOLATED,
        CONTEXT_NAVIGABLE
    };
    class Context{
    private:
        ContextType type;
        std::map<const std::string, JsonNode*> vars;
        unsigned int id;
        bool breakFlag;
        bool continueFlag;
        bool lastGetSucceed;
    
    public:
        Context();
        Context(ContextType type);
        ~Context();
        
        bool succeed();
        bool hasBreak();
        bool hasContinue();
        void clearBreak();
        void clearContinue();
        void doBreak();
        void doContinue();

        bool put(const std::string, JsonNode *var);
        bool set(const std::string, JsonNode* var);
        JsonNode* get(const std::string);
        bool containt(const std::string);
        bool remove(const std::string);
        void clear();

        ContextType getType();


    };

} // mate

#endif //MATE_CONTEXT_HH
