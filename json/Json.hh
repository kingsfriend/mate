#ifndef Json_NODE_201807_HH
#define Json_NODE_201807_HH

    #include <string>
    #include <vector>
    #include <iostream>
    #include <sstream>
    using namespace std;

namespace json
{
enum NodeType
{
    Object,
    Number,
    String,
    Array,
    Undefined
};


class JsonNode
{
  public:
    static const NodeType TYPE = Undefined;
    JsonNode(const string &k)
    {
        this->key = k;
    }
    JsonNode() {}
    NodeType getType()
    {
        return TYPE;
    }
    string getKey()
    {
        return this->key;
    }
    virtual string toString()
    {
        return "undefined";
    }
    static string separator()
    {
        return ":";
    }
    bool nullKey()
    {
        return this->key.empty();
    }

  private:
    string key;
  protected:
    string getKeyWithSeparator()
    {
        return this->key + JsonNode::separator();
    }
        };

        class JsonStringNode : public JsonNode
        {
          public:
            static const NodeType TYPE = String;
            JsonStringNode(const string &k, const string &v) : JsonNode(k){
                this->value = v;
            }
            JsonStringNode(const string &v){
                this->value = v;
            }
            JsonStringNode(){}

            string getValue() { 
                return this->value;
            }
            JsonStringNode* usingKey(string k){
                return new JsonStringNode(k, value);
            }
            string toString(){
                string str = "\"" + this->value + "\"";
                if(this->nullKey()){
                    return str;
                }
                return this->getKeyWithSeparator() + str;
            }

          private:
            string value;
        };

        class JsonNumberNode : public JsonNode
        {
          public:
            static const NodeType TYPE = Number;
            JsonNumberNode(const string &k, const double &v) : JsonNode(k)
            {
                this->value = v;
            }
            JsonNumberNode(const double &v)
            {
                this->value = v;
            }
            JsonNumberNode(){
                this->value = 0;
            }
             double getValue()
            {
                return this->value;
            }
            string toString()
            {
                std::ostringstream strs;
                strs << this->value;
                std::string str = strs.str();
                if (this->nullKey())
                {
                    return str;
                }
                return this->getKeyWithSeparator() + str;
            }
            JsonNumberNode *usingKey(string k)
            {
                return new JsonNumberNode(k, value);
            }

          private:
            double value;
        };

        class JsonObjectNode : public JsonNode
        {
          public:
            JsonObjectNode(const std::string &k, NodeType t) : JsonNode(k)
            {
                type = t;
            }
            JsonObjectNode(const std::string &k) : JsonNode(k)
            {
                type = Object;
            }
            JsonObjectNode(NodeType t)
            {
                type = t;
            }
            JsonObjectNode()
            {
                type = Object;
            } 
            string toString(){
                if(type==Array){
                    return encloseWith("[","]");
                }else{
                    return encloseWith("{","}");
                }
            }
            string encloseWith(string start, string end)
            {
                std::vector<JsonNode*> vals = this->values;
                string str = start ;
                if(!vals.empty()){
                    int i=0;
                    int loopLimit = vals.size()-1;
                    for (i=0; i < loopLimit; i++)
                    {
                        str += vals[i]->toString() + ",";
                    }
                    str += vals[i]->toString() ;
                }
                str+=end;
                if (this->nullKey())
                {
                    return str;
                }
                return this->getKeyWithSeparator() + str;
            }
            void push(JsonStringNode* node){
                values.push_back(node);
            }
            void push(JsonNumberNode* node){
                values.push_back(node);
            }
            void push(JsonObjectNode* node){
                if (node == this){
                    std::cout << "EXCEP: CANNOT PUSH AN OBJECT TO ITSELF \n";
                }else{
                    values.push_back(node);
                }

            }
            JsonObjectNode *usingKey(string k)
            {
                JsonObjectNode *obj = new JsonObjectNode(k, type);
                obj->setValues(getValues());
                return obj;
            }

            void setValues(std::vector<JsonNode *> vals)
            {
                values = vals;
            }
            std::vector<JsonNode *> getValues()
            {
                return values;
            } 
            private : NodeType type;
            std::vector<JsonNode *> values;
        };

        
    }

#endif //Json_NODE_201807_HH
