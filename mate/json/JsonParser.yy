%skeleton "lalr1.cc" /* -*- C++ -*- */
%require "3.0"
%defines
%define parser_class_name { JsonParser }

%define api.token.constructor
%define api.value.type variant
%define parse.assert
%define api.namespace { mate }
%code requires
{
    #include "../ast/Json.hpp"

    using namespace std;

    namespace mate {
        class JsonScanner;
        class JsonInterpreter;
    }
}

%code top
{
    #include <iostream>
    #include "JsonScanner.hpp"
    #include "JsonParser.hpp"
    #include "JsonInterpreter.hpp"
    #include "location.hh"

    
    using namespace mate;
    
    static mate::JsonParser::symbol_type yylex(mate::JsonScanner &scanner, mate::JsonInterpreter &driver) {
        return scanner.nextToken();
    }
}

%lex-param { mate::JsonScanner &scanner }
%lex-param { mate::JsonInterpreter &driver }
%parse-param { mate::JsonScanner &scanner }
%parse-param { mate::JsonInterpreter &driver }
%locations
%define parse.trace
%define parse.error verbose

%define api.token.prefix {TOKEN_}

%token END 0 "end of file"

%token <bool> BOOL
%token <double> NUMBER
%token <std::string> STRING
%token <std::string> UNDEFINED
%token NULL COLON LBRACE RBRACE COMMA LANGLE_BRACKET RANGLE_BRACKET

%type <JsonObjectNode*> json_object
%type <JsonArrayNode*> json_array
%type <JsonNode*> json_item
%type <std::vector<JsonNode *>> json_item_list
%type <KeyJsonNodePair> json_pair
%type <std::map<const std::string, JsonNode *>> json_pair_list

%start json
%%
json:
    json_object{
        driver.setObject(*$1);
    }
;
json_object:
    LBRACE RBRACE{
        $$ = new JsonObjectNode();
    }
    | LBRACE json_pair_list RBRACE{
        $$ = new JsonObjectNode($2);
    }
;
json_array:
    LANGLE_BRACKET RANGLE_BRACKET{
        $$ = new JsonArrayNode();
    }
    | LANGLE_BRACKET json_item_list RANGLE_BRACKET{
        $$ = new JsonArrayNode($2);
    }
;
json_item:
    BOOL{
        $$ = (JsonNode*) new JsonBoolNode($1);
    }
    | NUMBER{
        $$ = (JsonNode*) new JsonNumberNode($1);
    }
    | STRING{
        $$ = (JsonNode*) new JsonStringNode($1);
    }
    | NULL{
        $$ = NULL;
    }
    | json_array{
        $$ = (JsonNode*) $1;
    }
    | json_object{
        $$ = (JsonNode*) $1;
    }
;
json_item_list:
    json_item {
        $$ = std::vector<JsonNode *>();
        $$.push_back($1);
    }
    | json_item COMMA json_item_list{
        $$ = $3;
        $$.push_back($1);
    }
;
json_pair:
    STRING COLON json_item {
        $$ = KeyJsonNodePair($1,$3);
    }
;
json_pair_list:
    json_pair{
        $$ = std::map<const std::string, JsonNode *>();
        $$.insert(make_pair($1.key, $1.value));
    }
    | json_pair COMMA json_pair_list{
        $$ = $3;
        $$.insert(make_pair($1.key, $1.value));
    }
;

%%

void mate::JsonParser::error(const location &loc , const std::string &message) {
    cout << "Error: " << message << endl << "Error location: " << driver.getLocation() << endl;
}

