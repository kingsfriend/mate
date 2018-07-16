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
        Object,
        Number,
        Bool,
        String,
        Array,
        Date,
        Undefined
    };

    class JsonArrayNode;

    class JsonNode
    {
    public:
        static const NodeType TYPE = Undefined;
        static const JsonNode UNDEFINED();
        
        NodeType getType();
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
        bool equals(JsonNode* node);

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
        std::string toString();
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
        std::string toString();
        void push(const std::string &k, JsonDateNode *node);
        void push(const std::string &k, JsonBoolNode *node);
        void push(const std::string &k, JsonStringNode *node);
        void push(const std::string &k, JsonNumberNode *node);
        void push(const std::string &k, JsonArrayNode *node);
        void push(const std::string &k, JsonObjectNode *node);
        void setValues(std::map<const std::string, JsonNode *> vals);
        int size();

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
        ~JsonArrayNode();
        JsonArrayNode();
        std::string toString();
        void push(JsonDateNode *node);
        void push(JsonBoolNode *node);
        void push(JsonStringNode *node);
        void push(JsonNumberNode *node);
        void push(JsonObjectNode *node);
        void push(JsonArrayNode *node);
        int size();

        JsonNode *get(int i);

        std::vector<JsonNode *> getValues();
        bool equals(JsonNode *node);

      private:
        NodeType type;
        std::vector<JsonNode *> values;
    };
} // namespace mate

#endif //Json_NODE_201807_HH
