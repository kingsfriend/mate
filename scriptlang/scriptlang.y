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

%token MAGICESC END
%token BREAK CASE CONTINUE DEFAULT DEFINE EMPTY ELSE ELSEIF FOR FOREACH IF INCLUDE NAMESPACE NEWLINE REQUIRE SECTION SWITCH WHILE 
%token IDENTIFIER NUMBER STRING_LITERAL WHITESPACE WCOLON WLBRACKET WRBRACKET
%token INC_OP DEC_OP AND_OP OR_OP LE_OP GE_OP EQ_OP NE_OP L_OP G_OP 


%start script
%%
script:
    WHITESPACE define_directive
    | WHITESPACE define_directive commands
    | WHITESPACE require_directives define_directive commands
    | WHITESPACE namespace WHITESPACE define_directive commands
    | WHITESPACE namespace require_directives define_directive commands
    | define_directive
    | define_directive commands
    | require_directives define_directive commands
    | namespace define_directive commands
    | namespace require_directives define_directive commands
;
require_directives:
    require_directive
    | require_directive require_directives
;
require_directive:
    REQUIRE WLBRACKET full_class_name WCOLON IDENTIFIER WRBRACKET
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
    | DEFINE WLBRACKET class_name WCOLON full_class_name WRBRACKET
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
;
tokenword:
    IDENTIFIER | NUMBER | STRING_LITERAL | WHITESPACE | WCOLON
    | INC_OP | DEC_OP | AND_OP | OR_OP | LE_OP | GE_OP | EQ_OP | NE_OP | L_OP | G_OP
    | ';' | ',' | '=' | ']' | '.' | '&' | '[' | '!' | '~' | '-' | '+' | '*' | '/' | '%' | '^' | '|' | WRBRACKET | '}' | '?' | '{' | WLBRACKET
;
valuation:
    '@' WLBRACKET expression WRBRACKET {
        fprintf(yyout, "<val>");
    }
    | '@' WLBRACKET expression ',' default_value WRBRACKET {
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
    SWITCH WLBRACKET expression ',' expression WRBRACKET
    | SWITCH WLBRACKET expression ',' expression WRBRACKET commands
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
    | section_directive
;
section_directive:
    SECTION WLBRACKET IDENTIFIER WRBRACKET end_block
    | SECTION WLBRACKET IDENTIFIER WRBRACKET commands end_block
;
include_directive:
    INCLUDE WLBRACKET template_name WRBRACKET
;
loop_directive:
    BREAK
    | CONTINUE 
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
	| STRING_LITERAL
	| WLBRACKET expression WRBRACKET
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

