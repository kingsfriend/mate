%skeleton "lalr1.cc" /* -*- C++ -*- */
%require "3.0"
%defines
%define parser_class_name { ScriptParser }

%define api.token.constructor
%define api.value.type variant
%define parse.assert
%define api.namespace { mate }
%code requires
{
    #include <iostream>
    #include <string>
    #include <vector>
    #include <stdint.h>
    #include "../ast/command/EchoCommand.hpp"
    #include "../ast/command/ValuationCommand.hpp"
    #include "../ast/command/ValuationCommand.hpp"

    using namespace std;

    namespace mate {
        class ScriptScanner;
        class ScriptInterpreter;
    }
}

%code top
{
    #include <iostream>
    #include "ScriptScanner.hpp"
    #include "ScriptParser.hpp"
    #include "ScriptInterpreter.hpp"
    #include "location.hh"

    
    using namespace mate;
    
    static mate::ScriptParser::symbol_type yylex(mate::ScriptScanner &scanner, mate::ScriptInterpreter &driver) {
        return scanner.nextToken();
    }
}

%lex-param { mate::ScriptScanner &scanner }
%lex-param { mate::ScriptInterpreter &driver }
%parse-param { mate::ScriptScanner &scanner }
%parse-param { mate::ScriptInterpreter &driver }
%locations
%define parse.trace
%define parse.error verbose

%define api.token.prefix {TOKEN_}

%token END 0 "end of file"

%token MAGIC MAGICESC NEWLINE BLOCKEND

%token <std::string> BASE_DATA_TYPE

%token BREAK
%token CASE
%token CONTINUE
%token DEFAULT
%token DEFINE
%token EMPTY
%token ELSE
%token ELSEIF
%token FOR
%token FOREACH
%token IF
%token INCLUDE
%token NAMESPACE
%token <std::string> PARAM
%token REQUIRE
%token SWITCH
%token USE
%token VAR
%token VAL
%token WHILE

%token <std::string> UNDEFINED

%token <std::string> IDENTIFIER
%token <std::string> NUMBER
%token <std::string> STRING_LITERAL
%token <std::string> WAS
%token <std::string> WEQUAL
%token <std::string> WHITESPACE
%token <std::string> WCOMMA
%token <std::string> WSEMICOLON
%token <std::string> WCOLON
%token <std::string> WLBRACE
%token <std::string> WRBRACE
%token <std::string> WLBRACKET
%token <std::string> WRBRACKET
%token <std::string> WLANGLE_BRACKET
%token <std::string> WRANGLE_BRACKET

%token <std::string> INC_OP
%token <std::string> DEC_OP
%token <std::string> AND_OP
%token <std::string> OR_OP
%token <std::string> LE_OP
%token <std::string> GE_OP
%token <std::string> EQ_OP
%token <std::string> NE_OP
%token <std::string> L_OP
%token <std::string> G_OP
%token <std::string> CHAR

%type <EchoCommand*> fileword
%type <ValuationCommand*> valuation
%type <std::string> tokenword

%start script
%%
script:
    header_directives define_directive
    | header_directives define_directive commands
    | WHITESPACE namespace header_directives define_directive commands
    | namespace header_directives define_directive commands
    | define_directive commands
;
header_directives:
    WHITESPACE
    | require_directive
    | require_directive header_directives
    | use_directive
    | use_directive header_directives
    | var_directive
    | var_directive header_directives
    | value_assignment
    | value_assignment header_directives
;
require_directive:
    REQUIRE WLBRACKET var_declaration WRBRACKET
;
var_directive:
    VAR WLBRACKET var_declaration WRBRACKET
;
var_declaration:
    data_type WHITESPACE identifier_init_list
;
use_directive:
    USE WLBRACKET use_stms WRBRACKET
;
use_stms:
    data_type
    | data_type WAS IDENTIFIER
    | data_type WCOMMA use_stms
    | data_type WAS IDENTIFIER WCOMMA use_stms
;
namespace:
    NAMESPACE WLBRACKET IDENTIFIER WRBRACKET
;
data_type:
    BASE_DATA_TYPE
    | IDENTIFIER
;
define_directive:
    DEFINE WLBRACKET data_type WRBRACKET
;
value_assignment:
    VAL WLBRACKET assignment_expression_list WRBRACKET
;
commands:  
    command 
    | command commands
;
command:
    fileword{ 
        driver.executeCommand($1);
    }
    | valuation{
        driver.executeCommand($1);
    }
    | value_assignment{
        cout << "Parser: ALTERNATIVE" << endl;
    }
    | alternative{
        cout << "Parser: ALTERNATIVE" << endl;
    }
    | loop{
        cout << "Parser: LOOP" << endl;
    }
    | command_directive{
        cout << "Parser: COMMAND_DIRECTIVE" << endl;
    }
;
fileword: 
    tokenword{
        $$ = new EchoCommand($1);   
    }
    | MAGICESC{
        std::string magicesc = "@";
        $$ = new EchoCommand(magicesc);   
    }
    | NEWLINE{
        std::string newline = "\n";
        $$ = new EchoCommand(newline);   
    }
;
tokenword:
    IDENTIFIER { $$ =  $1; }
    | NUMBER { $$ =  $1; } | WEQUAL { $$ =  $1; } | WHITESPACE { $$ =  $1; } | WCOLON { $$ =  $1; } | WCOMMA { $$ =  $1; } | WLBRACE { $$ =  $1; } | WRBRACE { $$ =  $1; } | WRBRACKET { $$ =  $1; } | WLBRACKET { $$ =  $1; }
    | INC_OP { $$ =  $1; } | DEC_OP { $$ =  $1; } | AND_OP { $$ =  $1; } | OR_OP { $$ =  $1; } | LE_OP { $$ =  $1; } | GE_OP { $$ =  $1; } | EQ_OP { $$ =  $1; } | NE_OP { $$ =  $1; } | L_OP { $$ =  $1; } | G_OP { $$ =  $1; }
    | CHAR { $$ =  $1; }
    | UNDEFINED { $$ =  $1; } | BASE_DATA_TYPE { $$ =  $1; }
;
valuation:
    MAGIC WLBRACKET expression WRBRACKET {
        std::string exp = "var1";
        $$ = new ValuationCommand(exp);
    }
    | MAGIC WLBRACKET expression WCOMMA default_value WRBRACKET{
        std::string exp = "var2";
        $$ = new ValuationCommand(exp);
    }
;
default_value:
    expression
;
alternative:
    if_alternative    
    | switch_alternative    
;
if_alternative:
    if_block end_block
    | if_block else_block end_block 
    | if_block elseif_blocks end_block
    | if_block elseif_blocks else_block end_block
;
if_block:
    IF WLBRACKET expression WRBRACKET
    | IF WLBRACKET expression WRBRACKET commands
;
elseif_blocks:
    elseif_block
    | elseif_block elseif_blocks
;
elseif_block:
    ELSEIF WLBRACKET expression WRBRACKET
    | ELSEIF WLBRACKET expression WRBRACKET commands
;
else_block:
    ELSE WHITESPACE
    | ELSE WHITESPACE commands
;
switch_alternative:
    switch_block end_block
    | switch_block default_block end_block
    | switch_block case_blocks end_block
    | switch_block case_blocks default_block end_block
;
switch_block:
    SWITCH WLBRACKET expression WCOMMA expression WRBRACKET
    | SWITCH WLBRACKET expression WCOMMA expression WRBRACKET commands
;
case_blocks:
    case_block
    | case_block case_blocks
;
case_block:
    CASE WLBRACKET expression WRBRACKET
    | CASE WLBRACKET expression WRBRACKET commands
;
default_block:
    DEFAULT WHITESPACE
    | DEFAULT WHITESPACE commands
;
loop:
    for_loop
    | foreach_loop
    | while_loop
;
while_loop:
    WHILE WLBRACKET expression WRBRACKET end_block
    | WHILE WLBRACKET expression WRBRACKET commands end_block
;
for_loop:
    FOR WLBRACKET expression_statement expression_statement expression WRBRACKET end_block
    | FOR WLBRACKET expression_statement expression_statement expression WRBRACKET commands end_block
;
foreach_loop:
    foreach_block end_block
    | foreach_block empty_block end_block
;
foreach_block:
    FOREACH WLBRACKET IDENTIFIER WRBRACKET
    | FOREACH WLBRACKET IDENTIFIER WCOLON expression WRBRACKET commands
;
empty_block:
    EMPTY
    | EMPTY commands
;
command_directive:
    include_directive
    | loop_directive
;
include_directive:
    INCLUDE WLBRACKET template_name WRBRACKET
    | INCLUDE WLBRACKET template_name WCOMMA WLBRACE WRBRACE WRBRACKET
    | INCLUDE WLBRACKET template_name WCOMMA WLBRACE param_init_list WRBRACE WRBRACKET
;
param_init_list:
    param_init
    | param_init WCOMMA param_init_list
;
param_init:
    PARAM WEQUAL expression
;
loop_directive:
    BREAK
    | CONTINUE
;
template_name:
    IDENTIFIER
;
expression_statement:
    ';'
	| expression ';'
;
identifier_init: 
    IDENTIFIER
    | IDENTIFIER WEQUAL expression
;
identifier_init_list: 
    identifier_init
	| identifier_init WCOMMA identifier_init_list
;
expression:
    primary_expression
    | assignment_expression
;
assignment_expression:
    IDENTIFIER WEQUAL expression
;
assignment_expression_list:
    assignment_expression
    | assignment_expression WCOMMA assignment_expression_list
;
primary_expression: 
    IDENTIFIER
	| NUMBER
	| STRING_LITERAL
	| WLBRACKET expression WRBRACKET
	| json_array
	| json_object
;
primary_expression_list:
    primary_expression
    | primary_expression WCOMMA primary_expression_list
;
json_array:
    WLANGLE_BRACKET WRANGLE_BRACKET
    | WLANGLE_BRACKET primary_expression_list WRANGLE_BRACKET
;
key_value_expression:
    IDENTIFIER WCOLON expression
;
key_value_expression_list:
    key_value_expression
    | key_value_expression WCOMMA key_value_expression_list
;
json_object:
    WLBRACE WRBRACE
    | WLBRACE key_value_expression_list WRBRACE
;
end_block:
    BLOCKEND WHITESPACE
;
%%

void mate::ScriptParser::error(const location &loc , const std::string &message) {
    cout << "Error: " << message << endl << "Error location: " << driver.getLocation() << endl;
}

