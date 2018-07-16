#include "Json.hpp"

namespace mate
{
// JsonNode ----------------------------

JsonNode::JsonNode() {}

NodeType JsonNode::getType(){
    return TYPE;
}
std::string JsonNode::toString(){
    return "undefined";
}

bool JsonNode::equals(JsonNode* node){
    return false;
}

// JsonBoolNode ----------------------------

const JsonBoolNode JsonBoolNode::BOOL_NODE_TRUE = new JsonBoolNode(true);
const JsonBoolNode JsonBoolNode::BOOL_NODE_FALSE = new JsonBoolNode(false);

JsonBoolNode::JsonBoolNode(const bool &v){
    this->value = v;
}

JsonBoolNode::~JsonBoolNode() {}

JsonBoolNode::JsonBoolNode() {}

bool JsonBoolNode::val(){
    return this->value;
}

void JsonBoolNode::val(const bool &v){
    this->value = v;
}
std::string JsonBoolNode::toString(){
    return value ? "true" : "false";
}

bool JsonBoolNode::equals(JsonNode* node){
    if(node->TYPE == Bool){
        return value == ((JsonBoolNode*) node)->val();
    }
    return false;
}

// JsonStringNode ----------------------------

JsonStringNode::~JsonStringNode() {}

JsonStringNode::JsonStringNode() {}

JsonStringNode::JsonStringNode(const std::string &v){
    this->value = v;
}

std::string JsonStringNode::val(){
    return this->value;
}

void JsonStringNode::val(const std::string &v){
    this->value = v;
}

std::string JsonStringNode::toString(){
    std::string str = "\"" + this->value + "\"";
    return str;
}

std::string JsonStringNode::reverse(std::string s){
    std::string copy(s);
    std::reverse(copy.begin(), copy.end());
    return copy;
}

std::string JsonStringNode::reverse(){
    return reverse(value);
}

bool JsonStringNode::equals(JsonNode *node){ 
    if (node->TYPE == String){
        return value == ((JsonStringNode *)node)->val();
    }
    return false;
}

// JsonDateNode ----------------------------

JsonDateNode::~JsonDateNode(){}

JsonDateNode::JsonDateNode(const time_t &v){
    this->value = v;
    ltm = localtime(&value);
}

JsonDateNode::JsonDateNode(){
    this->value = now().val();
    ltm = localtime(&value);
}

time_t JsonDateNode::val(){
    return this->value;
}

void JsonDateNode::val(const time_t &v){
    this->value = v;
    ltm = localtime(&value);
}

std::string JsonDateNode::toString(){
    std::string str = ctime(&value);
    str.erase(std::remove(str.begin(), str.end(), '\n'), str.end());
    return "\"" + str + "\"";
}

std::string JsonDateNode::format(std::string format){
    return JsonDateNode::format(*this, format);
}

std::string JsonDateNode::format(JsonDateNode node, std::string format){
    char buffer[256];
    std::strftime(buffer, sizeof(buffer), format.c_str(), node.ltm);
    std::string bufferString(buffer);
    return "\"" + bufferString + "\"";
}

JsonDateNode JsonDateNode::now(){
    return JsonDateNode(time(0));
}

int JsonDateNode::sec() { 
    return ltm->tm_sec; 
}

int JsonDateNode::min() { 
    return ltm->tm_min; 
}

int JsonDateNode::hour() { 
    return ltm->tm_hour; 
}

int JsonDateNode::day() { 
    return ltm->tm_mday; 
}

int JsonDateNode::month() { 
    return ltm->tm_mon; 
}

int JsonDateNode::year() { 
    return ltm->tm_year; 
}

int JsonDateNode::weekDay() { 
    return ltm->tm_wday; 
}

int JsonDateNode::yearDay() { 
    return ltm->tm_yday; 
}

bool JsonDateNode::equals(JsonNode *node){ 
    if (node->TYPE == Date){
        return value == ((JsonDateNode *)node)->val();
    }
    return false;
}



// JsonNumberNode ----------------------------

JsonNumberNode::~JsonNumberNode(){}

JsonNumberNode::JsonNumberNode(const double &v){
    this->value = v;
}
JsonNumberNode::JsonNumberNode(){
    this->value = 0;
}
double JsonNumberNode::val(){
    return this->value;
}
void JsonNumberNode::val(const double &v){
    this->value = v;
}
std::string JsonNumberNode::toString(){
    std::ostringstream strs;
    strs << this->value;
    std::string str = strs.str();
    return str;
}

bool JsonNumberNode::equals(JsonNode *node){ 
    if (node->TYPE == Number){
        return value == ((JsonNumberNode *)node)->val();
    }
    return false;
}

// JsonObjectNode ----------------------------

JsonObjectNode::~JsonObjectNode(){}

JsonObjectNode::JsonObjectNode(){}

std::string JsonObjectNode::toString(){
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
void JsonObjectNode::push(const std::string &k, JsonDateNode *node){
    values.insert(make_pair(k, node));
}

void JsonObjectNode::push(const std::string &k, JsonBoolNode *node){
    values.insert(make_pair(k, node));
}

void JsonObjectNode::push(const std::string &k, JsonStringNode *node){
    values.insert(make_pair(k, node));
}

void JsonObjectNode::push(const std::string &k, JsonNumberNode *node){
    values.insert(make_pair(k, node));
}

void JsonObjectNode::push(const std::string &k, JsonArrayNode *node){
    values.insert(make_pair(k, node));
}

void JsonObjectNode::push(const std::string &k, JsonObjectNode *node){
    if (node == this){
        std::cout << "EXCEP: CANNOT PUSH AN OBJECT TO ITSELF \n";
    }else{
        values.insert(make_pair(k, node));
    }
}
void JsonObjectNode::setValues(std::map<const std::string, JsonNode *> vals){
    values = vals;
}

int JsonObjectNode::size(){
    return values.size();
}

JsonNode *JsonObjectNode::get(const std::string k){
    std::map<const std::string, JsonNode *>::const_iterator pos = values.find(k);
    if (pos == values.end())    {
        return NULL;
    }else{
        return pos->second;
    }
}

std::map<const std::string, JsonNode *> JsonObjectNode::getValues(){
    return values;
}

bool JsonObjectNode::equals(JsonNode *node){ 
    if (node->TYPE == Object){
        std::map<const std::string, JsonNode *> vals = values;
        std::map<const std::string, JsonNode *> nodeVals = ((JsonObjectNode *)node)->getValues();
        if(vals.size()==nodeVals.size()){
            bool r = true;
            std::map<const std::string, JsonNode *>::iterator it;
            std::map<const std::string, JsonNode *>::iterator itNode;
            for (it = vals.begin(), itNode = nodeVals.begin(); it != vals.end(); it++, itNode++){
                r = r && ((it->first == itNode->first) && (it->second->equals(itNode->second)));
            }
            return r;
        }
    }
    return false;
}

// JsonArrayNode ----------------------------

JsonArrayNode::~JsonArrayNode(){}

JsonArrayNode::JsonArrayNode(){}

std::string JsonArrayNode::toString(){
    std::vector<JsonNode *> vals = this->values;
    std::string str = "[";
    if (!vals.empty()){
        int i;
        int loopLimit = vals.size() - 1;
        for (i = 0; i < loopLimit; i++)        {
            str += vals[i]->toString() + ",";
        }
        str += vals[i]->toString();
    }
    str += "]";
    return str;
}
void JsonArrayNode::push(JsonDateNode *node){
    values.push_back(node);
}
void JsonArrayNode::push(JsonBoolNode *node){
    values.push_back(node);
}
void JsonArrayNode::push(JsonStringNode *node){
    values.push_back(node);
}
void JsonArrayNode::push(JsonNumberNode *node){
    values.push_back(node);
}
void JsonArrayNode::push(JsonObjectNode *node){
    values.push_back(node);
}
void JsonArrayNode::push(JsonArrayNode *node){
    values.push_back(node);
}

int JsonArrayNode::size(){
    return values.size();
}

JsonNode *JsonArrayNode::get(int i){
    return values[i];
}

std::vector<JsonNode *> JsonArrayNode::getValues(){
    return values;
}

bool JsonArrayNode::equals(JsonNode *node){ 
    if (node->TYPE == Array){
        std::vector<JsonNode *> vals = values;
        std::vector<JsonNode *> nodeVals = ((JsonArrayNode *)node)->getValues();
        if(vals.size()==nodeVals.size()){
            bool r = true;
            int i;
            int loopLimit = vals.size() - 1;
            for (i = 0; i < loopLimit; i++){
                r = r && (vals[i]->equals(nodeVals[i]));
            }
            return r;
        }
    }
    return false;
}

} // namespace mate