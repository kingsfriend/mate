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
    #include <map>
    #include <utility>
    #include <stdint.h>
    #include "../ast/Json.hpp"
    #include "../ast/error/Log.hpp"
    #include "../ast/command/EchoCommand.hpp"
    #include "../ast/command/ValuationCommand.hpp"
    #include "../ast/command/ValuationCommand.hpp"
    
    #include "../ast/command/expression/ArrayExpression.hpp"
    #include "../ast/command/expression/AssignmentExpression.hpp"
    #include "../ast/command/expression/BoolExpression.hpp"
    #include "../ast/command/expression/DateExpression.hpp"
    #include "../ast/command/expression/Expression.hpp"
    #include "../ast/command/expression/IdentifierExpression.hpp"
    #include "../ast/command/expression/KeyExpressionPair.hpp"
    #include "../ast/command/expression/NumExpression.hpp"
    #include "../ast/command/expression/ObjectExpression.hpp"
    #include "../ast/command/expression/PrimaryExpression.hpp"
    #include "../ast/command/expression/StringExpression.hpp"
    #include "../ast/command/expression/ValueAssignmentExpression.hpp"
    #include "../ast/command/expression/VariableDeclaration.hpp"

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
%token REQUIRE
%token SWITCH
%token USE
%token VAR
%token VAL
%token WHILE

%token <std::string> BASE_DATA_TYPE
%token <std::string> BOOL_CONST
%token <std::string> CHAR
%token <std::string> IDENTIFIER
%token <std::string> NUMBER
%token <std::string> PARAM
%token <std::string> STRING_LITERAL
%token <std::string> UNDEFINED
%token <std::string> AS
%token <std::string> WHITESPACE
%token <std::string> COMMA
%token <std::string> SEMICOLON
%token <std::string> COLON
%token <std::string> LBRACE
%token <std::string> QUESTION
%token <std::string> RBRACE
%token <std::string> LBRACKET
%token <std::string> RBRACKET
%token <std::string> LANGLE_BRACKET
%token <std::string> RANGLE_BRACKET

%token <std::string> ASSIGN
%token <std::string> MUL_ASSIGN
%token <std::string> DIV_ASSIGN
%token <std::string> MOD_ASSIGN
%token <std::string> ADD_ASSIGN
%token <std::string> SUB_ASSIGN
%token <std::string> AND_ASSIGN
%token <std::string> XOR_ASSIGN
%token <std::string> OR_ASSIGN
%token <std::string> EXC_ASSIGN

%token <std::string> MUL_SIGN
%token <std::string> DIV_SIGN
%token <std::string> MOD_SIGN
%token <std::string> ADD_SIGN
%token <std::string> SUB_SIGN
%token <std::string> AND_SIGN
%token <std::string> XOR_SIGN
%token <std::string> OR_SIGN

%token <std::string> INC_OP
%token <std::string> DEC_OP
%token <std::string> AND_OP
%token <std::string> OR_OP

%token <std::string> AND_LOGIC
%token <std::string> EXC_LOGIC
%token <std::string> OR_LOGIC

%token <std::string> LE_CMP
%token <std::string> GE_CMP
%token <std::string> EQ_CMP
%token <std::string> NE_CMP
%token <std::string> L_CMP
%token <std::string> G_CMP

%token <std::string> PERIOD

%type <EchoCommand*> fileword
%type <ValuationCommand*> valuation
%type <std::string> tokenword

%type <Expression*> expression
%type <AssignmentExpression*> assignment_expression
%type <IdentifierExpression*> identifier_expression
%type <std::vector<AssignmentExpression*>> assignment_expression_list
%type <PrimaryExpression*> primary_expression
%type <std::vector<Expression*>> expression_list
%type <NumExpression*> number_expression
%type <StringExpression*> string_expression
%type <BoolExpression*> bool_expression
%type <ArrayExpression*> array_expression
%type <ObjectExpression*> object_expression
%type <ValueAssignmentExpression*> value_assignment
%type <NodeType> data_type
%type <KeyExpressionPair> key_value_expression
%type <std::map<const std::string, Expression *>> key_value_expression_list

%type <VariableDeclaration*> var_directive
%type <VariableDeclaration*> variable_declaration
%type <std::vector<KeyExpressionPair>> variable_init_list
%type <KeyExpressionPair> variable_init

%start script
%%
script:
    header_directives define_directive
    | WHITESPACE  namespace header_directives define_directive
    | namespace header_directives define_directive
    | define_directive
;
header_directives:
    WHITESPACE
    | require_directive
    | require_directive header_directives
    | use_directive
    | use_directive header_directives
    | var_directive {
        driver.executeCommand($1);
    }
    | var_directive{
        driver.executeCommand($1);
    } header_directives
    | value_assignment{
        driver.executeCommand($1);
    }
    | value_assignment{
        driver.executeCommand($1);
    } header_directives
;
require_directive:
    REQUIRE LBRACKET variable_declaration RBRACKET
;
var_directive:
    VAR LBRACKET variable_declaration RBRACKET{
        $$ = $3;
    }
;
variable_declaration:
    data_type WHITESPACE variable_init_list{
        $$ = new VariableDeclaration($1,$3);
    }
;
use_directive:
    USE LBRACKET use_stms RBRACKET
;
use_stms:
    data_type
    | data_type AS IDENTIFIER
    | data_type COMMA use_stms
    | data_type AS IDENTIFIER COMMA use_stms
;
namespace:
    NAMESPACE LBRACKET IDENTIFIER RBRACKET
;
data_type:
    BASE_DATA_TYPE{
        if($1=="Bool"){
            $$ = Bool;
        }else if($1=="Number"){
            $$ = Number;
        }else if($1=="String"){
            $$ = String;
        }else if($1=="Date"){
            $$ = Date;
        }else if($1=="Object"){
            $$ = Object;
        }else if($1=="Array"){
            $$ = Array;
        }else{
            $$ = Undefined;
        }
    }
;
define_directive:
    DEFINE LBRACKET IDENTIFIER RBRACKET
    | DEFINE LBRACKET IDENTIFIER RBRACKET commands
;
value_assignment:
    VAL LBRACKET assignment_expression_list RBRACKET{
        $$ = new ValueAssignmentExpression($3);
    }
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
        driver.executeCommand($1);
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
    IDENTIFIER { $$ =  $1; } | PERIOD { $$ =  $1; }
    | NUMBER { $$ =  $1; } | ASSIGN { $$ =  $1; } | WHITESPACE { $$ =  $1; } | COLON { $$ =  $1; } | COMMA { $$ =  $1; } | LBRACE { $$ =  $1; } | RBRACE { $$ =  $1; } | RBRACKET { $$ =  $1; } | LBRACKET { $$ =  $1; }
    | INC_OP { $$ =  $1; } | DEC_OP { $$ =  $1; } | AND_OP { $$ =  $1; } | OR_OP { $$ =  $1; } | LE_CMP { $$ =  $1; } | GE_CMP { $$ =  $1; } | EQ_CMP { $$ =  $1; } | NE_CMP { $$ =  $1; } | L_CMP { $$ =  $1; } | G_CMP { $$ =  $1; }
    | CHAR { $$ =  $1; }
    | UNDEFINED { $$ =  $1; } | BASE_DATA_TYPE { $$ =  $1; }
;
valuation:
    MAGIC LBRACKET expression RBRACKET {
        Expression* exp;
        $$ = new ValuationCommand($3);
    }
    | MAGIC LBRACKET expression COMMA expression RBRACKET{
        Expression* exp;
        $$ = new ValuationCommand($3, $5);
    }
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
    IF LBRACKET expression RBRACKET
    | IF LBRACKET expression RBRACKET commands
;
elseif_blocks:
    elseif_block
    | elseif_block elseif_blocks
;
elseif_block:
    ELSEIF LBRACKET expression RBRACKET
    | ELSEIF LBRACKET expression RBRACKET commands
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
    SWITCH LBRACKET expression COMMA expression RBRACKET
    | SWITCH LBRACKET expression COMMA expression RBRACKET commands
;
case_blocks:
    case_block
    | case_block case_blocks
;
case_block:
    CASE LBRACKET expression RBRACKET
    | CASE LBRACKET expression RBRACKET commands
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
    WHILE LBRACKET expression RBRACKET end_block
    | WHILE LBRACKET expression RBRACKET commands end_block
;
for_loop:
    FOR LBRACKET expression_statement expression_statement expression RBRACKET end_block
    | FOR LBRACKET expression_statement expression_statement expression RBRACKET commands end_block
;
foreach_loop:
    foreach_block end_block
    | foreach_block empty_block end_block
;
foreach_block:
    FOREACH LBRACKET IDENTIFIER RBRACKET
    | FOREACH LBRACKET IDENTIFIER COLON expression RBRACKET commands
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
    INCLUDE LBRACKET template_name RBRACKET
    | INCLUDE LBRACKET template_name COMMA LBRACE RBRACE RBRACKET
    | INCLUDE LBRACKET template_name COMMA LBRACE param_init_list RBRACE RBRACKET
;
param_init_list:
    param_init
    | param_init COMMA param_init_list
;
param_init:
    PARAM ASSIGN expression
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
variable_init: 
    IDENTIFIER{
        KeyExpressionPair jsPair($1, NULL);
        $$ = jsPair;
    }
    | IDENTIFIER ASSIGN expression{
        KeyExpressionPair jsPair($1, $3);
        $$ = jsPair;
    }
;
variable_init_list: 
    variable_init{
        std::vector<KeyExpressionPair> vect;
        $$ = vect;
        $$.push_back($1);
    }
	| variable_init COMMA variable_init_list{
        std::vector<KeyExpressionPair> &arg3 = $3;
        arg3.push_back($1);
        $$ = arg3;
    }
;
expression:
    assignment_expression{
        $$ = (Expression*) $1;
    }
    | primary_expression{
        $$ = (Expression*) $1;
    }
;
assignment_expression:
    IDENTIFIER ASSIGN expression{
        $$ = new AssignmentExpression($1, $3);
    }
;
assignment_expression_list:
    assignment_expression{
        std::vector<AssignmentExpression*> vect;
        $$ = vect;
        $$.push_back($1);
    }
    | assignment_expression COMMA assignment_expression_list{
        std::vector<AssignmentExpression*> &arg3 = $3;
        arg3.push_back($1);
        $$ = arg3;
    }
;
primary_expression: 
    identifier_expression{
        $$ = (PrimaryExpression*)$1;
    }
	| number_expression{
        $$ = (PrimaryExpression*)$1;
    }
	| string_expression{
        $$ = (PrimaryExpression*)$1;
    }
	| bool_expression{
        $$ = (PrimaryExpression*)$1;
    }
	| array_expression{
        $$ = (PrimaryExpression*)$1;
    }
	| object_expression{
        $$ = (PrimaryExpression*)$1;
    }
;
identifier_expression:
    IDENTIFIER{
        $$ = new IdentifierExpression($1);
    }
;
number_expression:
    NUMBER{
        double val = atof($1.c_str());
        $$ = new NumExpression(val);
    }
;
string_expression:
	STRING_LITERAL{
        $$ = new StringExpression($1);
    }
;
bool_expression:
	BOOL_CONST{
        $$ = new BoolExpression($1=="true");
    }
;
array_expression:
    LANGLE_BRACKET RANGLE_BRACKET {
        $$ = new ArrayExpression();
    }
    | LANGLE_BRACKET expression_list RANGLE_BRACKET {
        $$ = new ArrayExpression($2);
    }
;
object_expression:
    LBRACE RBRACE{
        $$ = new ObjectExpression();
    }
    | LBRACE key_value_expression_list RBRACE{
        $$ = new ObjectExpression($2);
    }
;
expression_list:
    expression{
        std::vector<Expression*> arg;
        arg.push_back($1);
        $$ = arg;
    }
    | expression COMMA expression_list{
        std::vector<Expression*> arg3 = $3;
        arg3.push_back($1);
        $$ = arg3;
    }
;
key_value_expression:
    IDENTIFIER COLON expression{
        KeyExpressionPair p($1, $3);
        $$ = p;
    }
;
key_value_expression_list:
    key_value_expression{
        std::map<const std::string, Expression*> m;
        $$ = m;
        $$.insert(std::make_pair($1.key, $1.value));
    }
    | key_value_expression COMMA key_value_expression_list{
        std::map<const std::string, Expression *> &arg3 = $3;
        arg3.insert(std::make_pair($1.key, $1.value));
        $$ = arg3;
    }
;
end_block:
    BLOCKEND WHITESPACE
;
%%

void mate::ScriptParser::error(const location &loc , const std::string &message) {
    cout << "Error: " << message << " [line " << driver.getCurrentLine() << "]" << endl << "Error location: " << driver.getLocation() << endl;
}

