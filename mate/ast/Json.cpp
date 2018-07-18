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

JsonNode *JsonBoolNode::doCast(JsonNode *node){
    JsonBoolNode* returnNode = new JsonBoolNode(true);
    
    JsonBoolNode *boolNode;
    JsonNumberNode *numberNode;
    JsonStringNode *stringNode;
    JsonDateNode *dateNode;
    JsonObjectNode *objectNode;
    JsonArrayNode *arrayNode;
    if (node != NULL)
    {
        switch (node->getType())
        {
        case  Bool:
            boolNode = (JsonBoolNode *)node;
            returnNode->val(boolNode->val());
            break;
        case  Number:
            numberNode = (JsonNumberNode *)node;
            returnNode->val(numberNode->val()!=0);
            break;
        case  String:
            stringNode = (JsonStringNode *)node;
            returnNode->val(!stringNode->val().empty());
            break;
        case  Date:
            dateNode = (JsonDateNode *)node;
            returnNode->val(dateNode->val()!=0);
            break;
        case  Object:
            objectNode = (JsonObjectNode *)node;
            returnNode->val(!stringNode->val().empty());
            break;
        case  Array:
            arrayNode = (JsonArrayNode *)node;
            returnNode->val(!arrayNode->empty());
            break;
        default:
            break;
        }
    }
    return returnNode;
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
    std::string str = this->value;
    return str;
}

JsonNode *JsonStringNode::doCast(JsonNode *node)
{
    JsonStringNode *returnNode = new JsonStringNode();

    if (node != NULL){
        if(node->getType() == String){
            returnNode->val(node->toString());
        }else{
            JsonStringNode* stringNode = (JsonStringNode *)node;
            returnNode->val(stringNode->val());
        }
    }
    return returnNode;
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

JsonNode *JsonDateNode::doCast(JsonNode *node){
    JsonDateNode *returnNode = new JsonDateNode(0);
    JsonNumberNode *numberNode;
    if (node != NULL&&node->getType() == Number){
        numberNode = (JsonNumberNode *)node;
        returnNode->val(numberNode->val() != 0);
    }
    return returnNode;
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

JsonNode *JsonNumberNode::doCast(JsonNode *node)
{
    JsonNumberNode *returnNode = new JsonNumberNode(true);

    JsonBoolNode *boolNode;
    JsonNumberNode *numberNode;
    JsonStringNode *stringNode;
    JsonDateNode *dateNode;
    JsonObjectNode *objectNode;
    JsonArrayNode *arrayNode;
    if (node != NULL)
    {
        switch (node->getType())
        {
        case Bool:
            boolNode = (JsonBoolNode *)node;
            returnNode->val(boolNode->val());
            break;
        case Number:
            numberNode = (JsonNumberNode *)node;
            returnNode->val(numberNode->val() != 0);
            break;
        case String:
            stringNode = (JsonStringNode *)node;
            returnNode->val(stringNode->val().size());
            break;
        case Date:
            dateNode = (JsonDateNode *)node;
            returnNode->val(dateNode->val());
            break;
        case Object:
            objectNode = (JsonObjectNode *)node;
            returnNode->val(!stringNode->val().size());
            break;
        case Array:
            arrayNode = (JsonArrayNode *)node;
            returnNode->val(!arrayNode->size());
            break;
        default:
            break;
        }
    }
    return returnNode;
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

JsonObjectNode::JsonObjectNode(std::map<const std::string, JsonNode *> vals)
    : values(vals) {}

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

JsonNode *JsonObjectNode::doCast(JsonNode *node)
{
    JsonObjectNode *returnNode = new JsonObjectNode();

    JsonBoolNode *boolNode;
    JsonNumberNode *numberNode;
    JsonStringNode *stringNode;
    JsonDateNode *dateNode;
    JsonObjectNode *objectNode;
    JsonArrayNode *arrayNode;
    if (node != NULL)
    {
        switch (node->getType())
        {
        case Bool:
            boolNode = (JsonBoolNode *)node;
            returnNode->push("value", boolNode);
            break;
        case Number:
            numberNode = (JsonNumberNode *)node;
            returnNode->push("value", numberNode);
            break;
        case String:
            stringNode = (JsonStringNode *)node;
            returnNode->push("value", stringNode);
            break;
        case Date:
            dateNode = (JsonDateNode *)node;
            returnNode->push("value", dateNode);
            break;
        case Object:
            objectNode = (JsonObjectNode *)node;
            delete returnNode;
            returnNode = NULL;
            returnNode = objectNode->clone();
            break;
        case Array:
            arrayNode = (JsonArrayNode *)node;
            delete returnNode;
            returnNode = NULL;
            returnNode = arrayNode->toObject();
            break;
        default:
            break;
        }
    }
    return returnNode;
}

JsonObjectNode *JsonObjectNode::clone(){
    JsonObjectNode *node = new JsonObjectNode(this->values);
    return node;
}

JsonArrayNode *JsonObjectNode::toArray(){ 
    std::vector<JsonNode *> vals;
    std::map<const std::string, JsonNode *>::iterator it;
    for (it = values.begin(); it != values.end(); ++it){
        vals.push_back(it->second);
    }
    JsonArrayNode *node = new JsonArrayNode(vals);
    return node;
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
void JsonObjectNode::val(std::map<const std::string, JsonNode *> vals){
    values = vals;
}

int JsonObjectNode::size(){
    return values.size();
}

bool JsonObjectNode::empty(){
    return values.empty();
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

JsonArrayNode::JsonArrayNode(std::vector<JsonNode *> vals)
    : values(vals) {}

JsonArrayNode *JsonArrayNode::clone(){
    JsonArrayNode *node = new JsonArrayNode(values);
    return node;
}

JsonObjectNode *JsonArrayNode::toObject(){
    std::map<const std::string, JsonNode *> vals;
    int i, loopLimit = values.size();
    std::ostringstream s;
    for(i=0;i<loopLimit;i++){
        s << "value" << i;
        vals[s.str()] = values[i];
    }
    JsonObjectNode *node = new JsonObjectNode(vals);
    return node;
}

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
JsonNode *JsonArrayNode::doCast(JsonNode *node){
    JsonArrayNode *returnNode = new JsonArrayNode();

    JsonBoolNode *boolNode;
    JsonNumberNode *numberNode;
    JsonStringNode *stringNode;
    JsonDateNode *dateNode;
    JsonObjectNode *objectNode;
    JsonArrayNode *arrayNode;
    if (node != NULL)
    {
        switch (node->getType())
        {
        case Bool:
            boolNode = (JsonBoolNode *)node;
            returnNode->push(boolNode);
            break;
        case Number:
            numberNode = (JsonNumberNode *)node;
            returnNode->push(numberNode);
            break;
        case String:
            stringNode = (JsonStringNode *)node;
            returnNode->push(stringNode);
            break;
        case Date:
            dateNode = (JsonDateNode *)node;
            returnNode->push(dateNode);
            break;
        case Object:
            objectNode = (JsonObjectNode *)node;
            delete returnNode;
            returnNode = NULL;
            returnNode = objectNode->toArray();
            break;
        case Array:
            arrayNode = (JsonArrayNode *)node;
            delete returnNode;
            returnNode = NULL;
            returnNode = arrayNode->clone();
            break;
        default:
            break;
        }
    }
    return returnNode;
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

void JsonArrayNode::val(std::vector<JsonNode *> vals){
    values = vals;
}

bool JsonArrayNode::empty(){
    return values.empty();
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