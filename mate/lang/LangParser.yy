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
%token <int> INTEGER
%token <bool> TRUE FALSE 
%token <NodeType> BOOL_TYPE NUMBER_TYPE STRING_TYPE DATE_TYPE OBJECT_TYPE ARRAY_TYPE VOID_TYPE
%token NULL_CONST

%token AS BREAK CASE CLASS CONTINUE DEFAULT EMPTY ELSE ELSEIF FINAL FOR FOREACH IF IN PUBLIC NAMESPACE INTERNAL RETURN STATIC SWITCH USE WHILE
%token LBRACKET RBRACKET LBRACE RBRACE LANGLE_BRACKET RANGLE_BRACKET MATCH_ANY
%token COMMA SEMICOLON COLON PERIOD

%token QUESTION MAGIC

%token <std::string> UNDEFINED


%token CMP_NE CMP_EQ 
%token CMP_GE CMP_LE CMP_GT CMP_LT 


%token OP_OR
%token OP_AND


%right ASSIGN ASSIGN_MUL ASSIGN_DIV ASSIGN_MOD ASSIGN_PLS ASSIGN_MIN

%nonassoc OP_INC OP_DEC OP_NEG

%left OP_PLS OP_MIN
%left OP_MUL OP_DIV OP_MOD 

%nonassoc EXP_UNARY
%nonassoc EXP_POSTFIX
%nonassoc EXP_PRIMARY




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
    constructor_header compound_statement
;
constructor_header:
    IDENTIFIER LBRACKET RBRACKET
    | IDENTIFIER LBRACKET method_params RBRACKET
    | member_visibility IDENTIFIER LBRACKET RBRACKET
    | member_visibility IDENTIFIER LBRACKET method_params RBRACKET
;
class_method:
    method_header compound_statement
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
compound_statement: 
    LBRACE statements RBRACE
    | LBRACE declarations RBRACE
    | LBRACE declarations statements RBRACE
;
declarations:
    declaration
    | declaration declarations
;
declaration:
	data_type init_declarators SEMICOLON
;
init_declarators:
    init_declarator
	| init_declarator COMMA init_declarators
;
init_declarator:
    IDENTIFIER
	| IDENTIFIER ASSIGN initializer
;
initializer:
    assignment_expression
;
statements:
    statement
    | statement statements
;
statement:
    expression_statement
    | jump_statement
    | compound_statement
;
jump_statement:
    return_statement;
    | continue_statement
    | break_statement
;
return_statement:
	RETURN SEMICOLON
	| RETURN expression SEMICOLON
;
continue_statement:
	CONTINUE SEMICOLON
    | CONTINUE LBRACKET INTEGER RBRACKET SEMICOLON
;
break_statement:
	BREAK SEMICOLON
    | BREAK LBRACKET INTEGER RBRACKET SEMICOLON
;
expression_statement:
    SEMICOLON
    | expression SEMICOLON
;
expression:
    assignment_expression
	| expression COMMA assignment_expression
;
assignment_expression:
    conditional_expression
	| unary_expression assignment_operator assignment_expression
;
assignment_operator:
    ASSIGN
    | ASSIGN_MUL
    | ASSIGN_DIV
    | ASSIGN_MOD
    | ASSIGN_PLS
    | ASSIGN_MIN
;
conditional_expression:
    logical_or_expression
	| logical_or_expression QUESTION expression COLON conditional_expression
;
logical_or_expression:
    logical_and_expression
	| logical_or_expression OP_OR logical_and_expression
;
logical_and_expression:
    equality_expression
	| logical_and_expression OP_AND equality_expression
;
equality_expression:
    relational_expression
	| equality_expression CMP_EQ relational_expression
	| equality_expression CMP_NE relational_expression
;
relational_expression:
    arithmetic_expression
	| relational_expression CMP_LT arithmetic_expression
	| relational_expression CMP_GT arithmetic_expression
	| relational_expression CMP_LE arithmetic_expression
	| relational_expression CMP_GE arithmetic_expression
;
arithmetic_expression:
    additive_expression
;
additive_expression:
    multiplicative_expression
	| additive_expression OP_PLS multiplicative_expression
	| additive_expression OP_MIN multiplicative_expression
;
multiplicative_expression:
    unary_expression
	| multiplicative_expression OP_MUL unary_expression
	| multiplicative_expression OP_DIV unary_expression
	| multiplicative_expression OP_MOD unary_expression
;
unary_expression:
    postfix_expression
	| OP_PLS unary_expression %prec EXP_UNARY
	| OP_MIN unary_expression %prec EXP_UNARY
	| OP_INC unary_expression
	| OP_DEC unary_expression
;
postfix_expression:
	primary_expression
	| postfix_expression LANGLE_BRACKET expression RANGLE_BRACKET
	| postfix_expression LBRACKET RBRACKET
    | postfix_expression LBRACKET argument_expression_list RBRACKET
	| postfix_expression PERIOD IDENTIFIER
	| postfix_expression OP_INC %prec EXP_POSTFIX
	| postfix_expression OP_DEC %prec EXP_POSTFIX
;
argument_expression_list:
    assignment_expression
	| argument_expression_list COMMA assignment_expression
;
primary_expression:
    IDENTIFIER
	| STRING_LITERAL
	| VALUABLE_STRING
	| NULL_CONST
	| number_type
    | boolean_const
    | json_array 
    | json_object 
    | LBRACKET expression RBRACKET %prec EXP_PRIMARY
;
number_type:
    INTEGER
    | NUMBER
;
boolean_const:
	TRUE
	| FALSE
;
json_array:
    LANGLE_BRACKET RANGLE_BRACKET
    | LANGLE_BRACKET primary_expression_list RANGLE_BRACKET
;
json_object:
    LBRACE RBRACE
    | LBRACE primary_expression_pair_list RBRACE
;
primary_expression_list:
    primary_expression
    | primary_expression COMMA primary_expression_list
;
primary_expression_pair:
    IDENTIFIER COLON primary_expression
;
primary_expression_pair_list:
    primary_expression_pair
    | primary_expression_pair COMMA primary_expression_pair_list
;

%%
void mate::LangParser::error(const location &loc , const std::string &message) {
    cout << "Error: " << message << " [line " << driver.getCurrentLine() << "]" << endl << "Error location: " << driver.getLocation() << endl;
}

