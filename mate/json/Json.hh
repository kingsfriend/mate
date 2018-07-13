#ifndef Json_NODE_201807_HH
#define Json_NODE_201807_HH

#include <string>
#include <iterator>
#include <vector>
#include <map>
#include <iostream>
#include <sstream>

namespace mate
{
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

        class JsonArrayNode;

        class JsonNode
        {
        public:
            static const NodeType TYPE = Undefined;
            NodeType getType()
            {
                return TYPE;
            }
            virtual std::string toString()
            {
                return "undefined";
            }
            static std::string separator()
            {
                return ":";
            }

        protected:
            JsonNode() {}
        };

        class JsonStringNode : public JsonNode
        {
        public:
            static const NodeType TYPE = String;
            JsonStringNode(const std::string &v)
            {
                this->value = v;
            }
            JsonStringNode() {}

            std::string val()
            {
                return this->value;
            }
            void val(const std::string &v)
            {
                this->value = v;
            }
            std::string toString()
            {
                std::string str = "\"" + this->value + "\"";
                return str;
            }

        private:
            std::string value;
        };

        class JsonNumberNode : public JsonNode
        {
        public:
            static const NodeType TYPE = Number;
            JsonNumberNode(const double &v)
            {
                this->value = v;
            }
            JsonNumberNode()
            {
                this->value = 0;
            }
            double val()
            {
                return this->value;
            }
            void val(const double &v)
            {
                this->value = v;
            }
            std::string toString()
            {
                std::ostringstream strs;
                strs << this->value;
                std::string str = strs.str();
                return str;
            }

        private:
            double value;
        };

        class JsonObjectNode : public JsonNode
        {
        public:
            static const NodeType TYPE = Object;
            JsonObjectNode()
            {
            }
            std::string toString()
            {
                std::map<const std::string, JsonNode *> vals = this->values;
                std::string str = "{";
                if (!vals.empty())
                {
                    std::map<const std::string, JsonNode *>::reverse_iterator it;
                    for (it = vals.rbegin(); it != vals.rend(); it++)
                    {
                        str += it->first + ":" + it->second->toString() + ",";
                    }
                    str.erase(str.size() - 1);
                }
                str += "}";
                return str;
            }
            void push(const std::string &k, JsonStringNode *node)
            {
                values.insert(make_pair(k, node));
            }
            void push(const std::string &k, JsonNumberNode *node)
            {
                values.insert(make_pair(k, node));
            }
            void push(const std::string &k, JsonArrayNode *node)
            {
                values.insert(make_pair(k, node));
            }
            void push(const std::string &k, JsonObjectNode *node)
            {
                if (node == this)
                {
                    std::cout << "EXCEP: CANNOT PUSH AN OBJECT TO ITSELF \n";
                }
                else
                {
                    values.insert(make_pair(k, node));
                }
            }
            void setValues(std::map<const std::string, JsonNode *> vals)
            {
                values = vals;
            }
            JsonNode *get(const std::string k)
            {
                std::map<const std::string, JsonNode *>::const_iterator pos = values.find(k);
                if (pos == values.end())
                {
                    return NULL;
                }
                else
                {
                    return pos->second;
                }
            }
            std::map<const std::string, JsonNode *> getValues()
            {
                return values;
            }

        private:
            NodeType type;
            std::map<const std::string, JsonNode *> values;
        };

        class JsonArrayNode : public JsonNode
        {
        public:
            static const NodeType TYPE = Array;
            JsonArrayNode()
            {
            }
            std::string toString()
            {
                std::vector<JsonNode *> vals = this->values;
                std::string str = "[";
                if (!vals.empty())
                {
                    int i;
                    int loopLimit = vals.size() - 1;
                    for (i = 0; i < loopLimit; i++)
                    {
                        str += vals[i]->toString() + ",";
                    }
                    str += vals[i]->toString();
                }
                str += "]";
                return str;
            }
            void push(JsonStringNode *node)
            {
                values.push_back(node);
            }
            void push(JsonNumberNode *node)
            {
                values.push_back(node);
            }
            void push(JsonObjectNode *node)
            {
                values.push_back(node);
            }
            void push(JsonArrayNode *node)
            {
                values.push_back(node);
            }

            JsonNode *get(int i)
            {
                return values[i];
            }

            std::vector<JsonNode *> getValues()
            {
                return values;
            }

        private:
            NodeType type;
            std::vector<JsonNode *> values;
        };
    } // namespace json
} // namespace mate

#endif //Json_NODE_201807_HH
