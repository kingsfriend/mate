%skeleton "lalr1.cc" /* -*- C++ -*- */
%require "3.0"
%defines
%define parser_class_name { LangParser }

%define api.token.constructor
%define api.value.type variant
%define parse.assert
%define api.namespace { mate }
%code requires
{
    #include <iostream>
    #include <string>
    #include <vector>
    #include <map>
    #include <utility>
    #include <stdint.h>
	#include "../ast/Json.hpp"

    using namespace std;

    namespace mate {
        class LangScanner;
        class LangInterpreter;
    }
}

%code top
{
    #include <iostream>
    #include "LangScanner.hpp"
    #include "LangParser.hpp"
    #include "LangInterpreter.hpp"
    #include "location.hh"

    
    using namespace mate;
    
    static mate::LangParser::symbol_type yylex(mate::LangScanner &scanner, mate::LangInterpreter &driver) {
        return scanner.nextToken();
    }
}

%lex-param { mate::LangScanner &scanner }
%lex-param { mate::LangInterpreter &driver }
%parse-param { mate::LangScanner &scanner }
%parse-param { mate::LangInterpreter &driver }
%locations
%define parse.trace
%define parse.error verbose

%define api.token.prefix {TOKEN_}

%token END 0 "end of file"


%token <std::string> IDENTIFIER
%token <std::string> STRING_LITERAL VALUABLE_STRING
%token <double> NUMBER
%token <NodeType> BOOL_TYPE NUMBER_TYPE STRING_TYPE DATE_TYPE OBJECT_TYPE ARRAY_TYPE VOID_TYPE
%token <bool> TRUE FALSE 


%token AS BREAK CASE CLASS CONTINUE DEFAULT EMPTY ELSE ELSEIF FINAL FOR FOREACH IF IN PUBLIC NAMESPACE INTERNAL STATIC SWITCH USE WHILE

%token LBRACKET RBRACKET LBRACE RBRACE LANGLE_BRACKET RANGLE_BRACKET MATCH_ANY

%token COMMA SEMICOLON COLON PERIOD

%token <std::string> UNDEFINED

%start lang
%%

lang:
    namespace_directive use_directives main_class_definition
    | use_directives main_class_definition
    | main_class_definition
;
namespace_directive:
    NAMESPACE namespace SEMICOLON
;
namespace:
    IDENTIFIER
;
use_directives:
    use_directive
    | use_directive use_directives
;
use_directive:
    USE full_namespace SEMICOLON
    | USE full_namespace MATCH_ANY SEMICOLON
;
full_namespace:
    namespace
    | namespace PERIOD full_namespace
;
main_class_definition:
    class_definition
;
class_definition:
    CLASS class_identifier LBRACE class_members RBRACE
;
class_identifier:
    IDENTIFIER
;
member_visibility:
    PUBLIC
    | INTERNAL
;
member_modifier:
    STATIC
    | FINAL
;
visibility_or_modifier:
    member_modifier
    | member_visibility
;
visibility_or_modifiers:
    visibility_or_modifier
    | visibility_or_modifier visibility_or_modifiers
;
class_members:
    class_member
    | class_member class_members
;
class_member:
    class_field
    | class_constructor
    | class_method
;
class_field:
    data_type IDENTIFIER
    | visibility_or_modifiers data_type IDENTIFIER
;
class_constructor:
    constructor_header code_blok
;
constructor_header:
    IDENTIFIER LBRACKET RBRACKET
    | IDENTIFIER LBRACKET method_params RBRACKET
    | member_visibility IDENTIFIER LBRACKET RBRACKET
    | member_visibility IDENTIFIER LBRACKET method_params RBRACKET
;
class_method:
    method_header code_blok
;
method_header:
    data_type IDENTIFIER LBRACKET RBRACKET
    | data_type IDENTIFIER LBRACKET method_params RBRACKET
    | visibility_or_modifiers data_type IDENTIFIER LBRACKET RBRACKET
    | visibility_or_modifiers data_type IDENTIFIER LBRACKET method_params RBRACKET
;
data_type:
    BOOL_TYPE
    | NUMBER_TYPE
    | DATE_TYPE
    | STRING_TYPE
    | ARRAY_TYPE
    | OBJECT_TYPE
    | VOID_TYPE
;
method_params:
    method_param
    | method_param method_params
;
method_param:
    data_type IDENTIFIER
;
code_blok: LBRACE RBRACE
%%

void mate::LangParser::error(const location &loc , const std::string &message) {
    cout << "Error: " << message << " [line " << driver.getCurrentLine() << "]" << endl << "Error location: " << driver.getLocation() << endl;
}

