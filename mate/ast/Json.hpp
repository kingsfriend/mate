#ifndef Json_NODE_201807_HH
#define Json_NODE_201807_HH

#include <string>
#include <iterator>
#include <algorithm>
#include <vector>
#include <map>
#include <iostream>
#include <sstream>
#include <ctime>

namespace mate
{
    enum NodeType
    {
        Bool,
        Number,
        String,
        Date,
        Object,
        Array,
        Undefined
    };

    class JsonArrayNode;

    class JsonNode
    {
    public:
        static const NodeType TYPE = Undefined;
        static const JsonNode UNDEFINED();
        
        NodeType getType();
        virtual std::string toQuotedString();
        virtual std::string toString();
        virtual bool equals(JsonNode *node);

      protected:
        JsonNode();
    };

    class JsonBoolNode : public JsonNode
    {
    public:
        static const NodeType TYPE = Bool;
        static const JsonBoolNode BOOL_NODE_TRUE;
        static const JsonBoolNode BOOL_NODE_FALSE;
        
        JsonBoolNode(const bool &v);
        JsonBoolNode();
        ~JsonBoolNode();

        bool val();
        void val(const bool &v);
        std::string toString();
        static JsonNode *doCast(JsonNode *node);
        bool equals(JsonNode *node);

      private:
        bool value;
    };

    class JsonStringNode : public JsonNode
    {
    public:
        static const NodeType TYPE = String;
        JsonStringNode(const std::string &v);
        JsonStringNode();
        ~JsonStringNode();

        std::string val();
        void val(const std::string &v);
        std::string toQuotedString();
        std::string toString();
        static JsonNode *doCast(JsonNode *node);
        static std::string reverse(std::string s);
        std::string reverse();
        bool equals(JsonNode *node);

      private:
        std::string value;
    };

    class JsonDateNode : public JsonNode
    {
    public:
        static const NodeType TYPE = Date;
        JsonDateNode(const time_t &v);
        JsonDateNode();
        ~JsonDateNode();
        time_t val();
        void val(const time_t &v);
        std::string toString();
        static JsonNode *doCast(JsonNode *node);
        std::string format(std::string format);
        static  std::string format(JsonDateNode node, std::string format);
        static JsonDateNode now ();
        int sec();
        int min();
        int hour();
        int day();
        int month();
        int year();
        int weekDay();
        int yearDay();
        bool equals(JsonNode *node);
        
    private:
      time_t value;
      tm *ltm;
    };

    class JsonNumberNode : public JsonNode
    {
    public:
        static const NodeType TYPE = Number;
        ~JsonNumberNode();
        JsonNumberNode(const double &v);
        JsonNumberNode();
        double val();
        void val(const double &v);
        std::string toString();
        static JsonNode *doCast(JsonNode *node);
        bool equals(JsonNode *node);

      private:
        double value;
    };

    class JsonObjectNode : public JsonNode
    {
    public:
        static const NodeType TYPE = Object;
        ~JsonObjectNode();
        JsonObjectNode();
        JsonObjectNode(std::map<const std::string, JsonNode *> vals);
        std::string toString();
        JsonObjectNode* clone();
        JsonArrayNode* toArray();
        static JsonNode *doCast(JsonNode *node);
        void push(const std::string &k, JsonNode *node);
        void val(std::map<const std::string, JsonNode *> vals);
        int size();
        bool empty();

        JsonNode *get(const std::string k);
        std::map<const std::string, JsonNode *> getValues();
        bool equals(JsonNode *node);

      private:
        NodeType type;
        std::map<const std::string, JsonNode *> values;
    };

    class JsonArrayNode : public JsonNode
    {
    public:
        static const NodeType TYPE = Array;
        static JsonNode *doCast(JsonNode *node);
        ~JsonArrayNode();
        JsonArrayNode();
        JsonArrayNode(std::vector<JsonNode *> vals);
        JsonArrayNode *clone();
        JsonObjectNode *toObject();
        std::string toString();
        void push(JsonNode *node);
        bool empty();
        int size();
        void val(std::vector<JsonNode *> vals);

        JsonNode *get(int i);

        std::vector<JsonNode *> getValues();
        bool equals(JsonNode *node);

      private:
        NodeType type;
        std::vector<JsonNode *> values;
    };

    class KeyJsonNodePair{
    public:
        std::string key;
        JsonNode *value;
        KeyJsonNodePair(){
            value = NULL;
        }
        KeyJsonNodePair(std::string key, JsonNode *value) : key(key), value(value) {}
    };
} // namespace mate

#endif //Json_NODE_201807_HH
