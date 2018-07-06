%{ 
    #include <stdio.h>
    #include <stdlib.h>

    extern int yylex();
    extern int yyparse();
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
%token BREAK CASE CONTINUE DEFAULT DO EMPTY ELSE ELSEIF ENUM FOR FOREACH IF SWITCH WHILE 
%token IDENTIFIER NUMBER STRING_LITERAL WHITESPACE 
%token INC_OP DEC_OP AND_OP OR_OP LE_OP GE_OP EQ_OP NE_OP L_OP G_OP 


%start script
%%
script:
      commands
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
;
fileword: 
    tokenword { scriptlangy_echo(yytext,"fileword.tokenword"); }
    | MAGICESC { scriptlangy_echo("@","fileword.MAGICESC"); }
;
tokenword:
    IDENTIFIER | NUMBER | STRING_LITERAL | WHITESPACE
    | INC_OP | DEC_OP | AND_OP | OR_OP | LE_OP | GE_OP | EQ_OP | NE_OP | L_OP | G_OP
    | ';' | ',' | ':' | '=' | ']' | '.' | '&' | '[' | '!' | '~' | '-' | '+' | '*' | '/' | '%' | '^' | '|' | ')' | '}' | '?' | '{' | '('
;
valuation:
    '@' '(' expression ')' {
        fprintf(yyout, "<val>");
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
    IF '(' expression ')'
    | IF '(' expression ')' commands
;
elseif_blocks:
    elseif_block
    | elseif_block elseif_blocks
;
elseif_block:
    ELSEIF '(' expression ')'
    | ELSEIF '(' expression ')' commands
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
    SWITCH '(' expression ',' expression')'
    | SWITCH '(' expression ',' expression ')' commands
;
case_blocks:
    case_block
    | case_block case_blocks
;
case_block:
    CASE '(' expression ')'
    | CASE '(' expression ')' commands
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
    WHILE '(' expression ')' end_block
    | WHILE '(' expression ')' commands end_block
;
for_loop:
    FOR '(' expression_statement expression_statement expression')' end_block
    | FOR '(' expression_statement expression_statement expression')' commands end_block
;

foreach_loop:
    foreach_block end_block
    | foreach_block empty_block end_block
;
foreach_block:
    FOREACH '(' IDENTIFIER ')'
    | FOREACH '(' IDENTIFIER ':' expression')' commands
;
empty_block:
    EMPTY
    | EMPTY commands
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
	| '(' expression ')'
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
