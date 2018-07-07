%{ 
    #include <stdio.h>
    #include <stdlib.h>

    extern int yylex();
    extern int yyparse();
    extern int input();
	extern void scriptlangl_removeWhitespaces();
    extern FILE* yyin;
    extern FILE* yyout;
    extern char* yytext;

    void yyerror(const char* s);
    void scriptlangy_echo(const char* s, const char*ctx);
    void scriptlangy_disableEcho();
    void scriptlangy_enableEcho();
    int scriptlangy_canEcho =1;
    
    /* DEBUG ------------------*/
        int i=0;
    /* ------------------------*/

%}

%define parse.trace

%token MAGICESC NEWLINE END
%token BREAK CASE CONTINUE DEFAULT DEFINE EMPTY ELSE ELSEIF FOR FOREACH IF INCLUDE NAMESPACE PARAM REQUIRE SWITCH USE WHILE 
%token IDENTIFIER INTEGER NUMBER STRING_LITERAL WAS WEQUAL WHITESPACE WCOMMA WCOLON WLBRACE WRBRACE WLBRACKET WRBRACKET
%token INC_OP DEC_OP AND_OP OR_OP LE_OP GE_OP EQ_OP NE_OP L_OP G_OP 


%start script
%%
script:
    header_directives define_directive
    | header_directives define_directive commands
    | WHITESPACE namespace header_directives define_directive commands
    | namespace header_directives define_directive commands
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
    | class_name '.' class_name
;
define_directive:
    DEFINE WLBRACKET class_name WRBRACKET
;
commands:  
    command 
    | commands command
;
command:
    fileword
    | valuation
    | alternative
    | loop
    | command_directive
;
fileword: 
    tokenword { scriptlangy_echo(yytext,"fileword.tokenword"); }
    | MAGICESC { scriptlangy_echo("@","fileword.MAGICESC"); }
    | NEWLINE { scriptlangy_echo("\n","fileword.MAGICESC"); }
;
tokenword:
    IDENTIFIER | INTEGER | PARAM | NUMBER | STRING_LITERAL | WEQUAL | WHITESPACE | WCOLON | WCOMMA | WLBRACE | WRBRACE | WRBRACKET | WLBRACKET
    | INC_OP | DEC_OP | AND_OP | OR_OP | LE_OP | GE_OP | EQ_OP | NE_OP | L_OP | G_OP
    | ';' | '=' | ']' | '.' | '&' | '[' | '!' | '~' | '-' | '+' | '*' | '/' | '%' | '^' | '|' | '}' | '?' | '{'
;
valuation:
    '@' WLBRACKET expression WRBRACKET {
        fprintf(yyout, "<val>");
    }
    | '@' WLBRACKET expression WCOMMA default_value WRBRACKET {
        fprintf(yyout, "<val>");
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
    END WHITESPACE
;
%%

int main() {
    yyin=fopen("./scriptlang-input.txt","r");
    yyout=fopen("./scriptlang-output.txt","w+");
    int token = 0;

    do { 
		yyparse();
	} while(!feof(yyin));
    
    fclose(yyout);
	return 0;

}

void yyerror(const char* s) {
	fprintf(stderr, "> Parse error: %s\n", s);
	exit(1);
}
void scriptlangy_echo(const char* s,const char* ctx) {
    i++;
    printf("%d %s > \"%s\" [%d]\n",i,ctx,s,scriptlangy_canEcho);
    if(scriptlangy_canEcho>0){
	    fprintf(yyout, "%s", s);
    }
}
void scriptlangy_disableEcho() {
    scriptlangy_canEcho=0;
}
void scriptlangy_enableEcho() {
    scriptlangy_canEcho=1;
}

