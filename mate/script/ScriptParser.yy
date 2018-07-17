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

%token MAGICESC NEWLINE BLOCKEND

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
%token WHILE

%token <std::string> IDENTIFIER
%token <std::string> INTEGER
%token <std::string> NUMBER
%token <std::string> STRING_LITERAL
%token <std::string> WAS
%token <std::string> WEQUAL
%token <std::string> WHITESPACE
%token <std::string> WCOMMA
%token <std::string> WCOLON
%token <std::string> WLBRACE
%token <std::string> WRBRACE
%token <std::string> WLBRACKET
%token <std::string> WRBRACKET

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
;
require_directive:
    REQUIRE WLBRACKET full_class_name WHITESPACE identifier_list WRBRACKET
;
use_directive:
    USE WLBRACKET use_stms WRBRACKET
;
use_stms:
    full_class_name
    | full_class_name WAS IDENTIFIER
    | full_class_name WCOMMA use_stms
    | full_class_name WAS IDENTIFIER WCOMMA use_stms
;
namespace:
    NAMESPACE WLBRACKET IDENTIFIER WRBRACKET
;
class_name:
    IDENTIFIER
;
full_class_name:
    class_name
    | class_name '.' full_class_name
;
define_directive:
    DEFINE WLBRACKET class_name WRBRACKET
;
commands:  
    command 
    | command commands
;
command:
    fileword{ 
        driver.executeCommand($1);
    }
    | valuation
    | alternative
    | loop
    | command_directive
;
fileword: 
    tokenword{
        $$ = new EchoCommand($1);   
    }
    | MAGICESC{
        std::string magicesc = "@@";
        $$ = new EchoCommand(magicesc);   
    }
    | NEWLINE{
        std::string newline = "\n";
        $$ = new EchoCommand(newline);   
    }
;
tokenword:
    IDENTIFIER { $$ =  $1; } | PARAM { $$ =  $1; }
    | INTEGER { $$ =  $1; } | NUMBER { $$ =  $1; } | STRING_LITERAL { $$ =  $1; } | WEQUAL { $$ =  $1; } | WHITESPACE { $$ =  $1; } | WCOLON { $$ =  $1; } | WCOMMA { $$ =  $1; } | WLBRACE { $$ =  $1; } | WRBRACE { $$ =  $1; } | WRBRACKET { $$ =  $1; } | WLBRACKET { $$ =  $1; }
    | INC_OP { $$ =  $1; } | DEC_OP { $$ =  $1; } | AND_OP { $$ =  $1; } | OR_OP { $$ =  $1; } | LE_OP { $$ =  $1; } | GE_OP { $$ =  $1; } | EQ_OP { $$ =  $1; } | NE_OP { $$ =  $1; } | L_OP { $$ =  $1; } | G_OP { $$ =  $1; }
    | CHAR { $$ =  $1; }
;
valuation:
    '@' WLBRACKET expression WRBRACKET
    | '@' WLBRACKET expression WCOMMA default_value WRBRACKET
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
    BREAK WHITESPACE
    | CONTINUE WHITESPACE
    | BREAK WLBRACKET INTEGER WRBRACKET
    | CONTINUE WLBRACKET INTEGER WRBRACKET
;
template_name:
    IDENTIFIER
;
expression:
    primary_expression
;
expression_statement:
    ';'
	| expression ';'
;
primary_expression: 
    IDENTIFIER
	| NUMBER
	| INTEGER
	| STRING_LITERAL
	| WLBRACKET expression WRBRACKET
;
identifier_list: 
    IDENTIFIER
	| IDENTIFIER WCOMMA identifier_list
;
end_block:
    BLOCKEND WHITESPACE
;
%%

void mate::ScriptParser::error(const location &loc , const std::string &message) {
    cout << "Error: " << message << endl << "Error location: " << driver.getLocation() << endl;
}

