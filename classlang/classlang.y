%{ 
    #include <stdio.h>
    #include <stdlib.h>

    extern int yylex();
    extern int yyparse();
    extern int input();
    extern FILE* yyin;
    extern FILE* yyout;
    extern char* yytext;

    void yyerror(const char* s);
    void classlangy_echo(const char* s, const char*ctx);
    void classlangy_disableEcho();
    void classlangy_enableEcho();
    int classlangy_canEcho =1;
    
    /* DEBUG ------------------*/
        int i=0;
    /* ------------------------*/

%}

%define parse.trace

%token  AS BREAK CASE CLASS CONTINUE DEFAULT EMPTY ELSE ELSEIF EXTENDS END FOR FOREACH 
        IF IMPLEMENTS INTERFACE NAMESPACE SWITCH USE WHILE 
%token  WITHESPACE IDENTIFIER INTEGER NUMBER STRING_LITERAL 
        WCOLON WLBRACKET WLBRACE WRBRACE WRBRACKET WRBRACKET WCOMMA WEQUAL 
%token  INC_OP DEC_OP AND_OP OR_OP LE_OP GE_OP EQ_OP NE_OP L_OP G_OP 

%start  class_file

%%
class_file:
    
;
%%

int main() {
    yyin=fopen("./classlang-input.txt","r");
    yyout=fopen("./classlang-output.txt","w+");
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
void classlangy_echo(const char* s,const char* ctx) {
    i++;
    printf("%d %s > \"%s\" [%d]\n",i,ctx,s,classlangy_canEcho);
    if(classlangy_canEcho>0){
	    fprintf(yyout, "%s", s);
    }
}
void classlangy_disableEcho() {
    classlangy_canEcho=0;
}
void classlangy_enableEcho() {
    classlangy_canEcho=1;
}

