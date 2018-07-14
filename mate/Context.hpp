#ifndef MATE_CONTEXT_HH
#define MATE_CONTEXT_HH

#include <map>
#include <string>
#include "Json.hpp"

using namespace std;
namespace mate
{
    enum ContextType{
        ISOLATED,
        NAVIGABLE
    };
    class Context
    {
    public:
        Context();
        ~Context();
        static unsigned int nextKey();
        static unsigned int getKey();
        
        Context* getParent();
        void setParent(Context* c);
        
        void setChild(Context* c);
        Context* getChild();

        void put(const std::string, JsonNode* var);
        void set(const std::string, JsonNode* var);
        JsonNode* get(const std::string);
        void remove(const std::string);
        void clear();

      private:
        Context* parent;
        Context* child;
        ContextType type;
        std::map<const std::string, JsonNode*> vars;
        unsigned int id;
    
    private:
        static unsigned int contextCount;
    };

} // mate

#endif //MATE_CONTEXT_HH
