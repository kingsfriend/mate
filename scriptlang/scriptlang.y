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

%token MAGIC MAGICESC
%token WHITESPACE
%token BREAK CASE

%start script
%%
script:
    /* empty */ 
   commands
;
commands:  
    command 
    | commands command
;
command:
    fileword
    | MAGIC
;
fileword: 
    tokenword { scriptlangy_echo(yytext,"fileword.MAGICESC"); }
    | MAGICESC { scriptlangy_echo("@","fileword.MAGICESC"); }
;
tokenword:
    BREAK
    | CASE
    | WHITESPACE
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
