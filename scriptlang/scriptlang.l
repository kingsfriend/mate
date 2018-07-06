/* Definition section */
D			[0-9]
L			[a-zA-Z_]

%{
/* C code to be copied verbatim */
    #include "scriptlang.tab.h"
    
    extern void scriptlangy_echo(const char* s, const char*ctx);
    
    const char* FLEX_TAG = "[(f)lex] scriptlang.l\0";
    void count();
    void scriptlangl_multiLineComment();
    void scriptlangl_singleLineomment();
%}
/* This tells flex to read only one input file */
%option noyywrap

%%
"@/*"			    { scriptlangl_multiLineComment(); }
"@//"			    { scriptlangl_singleLineomment(); }
"@@"                { count(); return(MAGICESC); }

"@break"    	    { count(); return(BREAK); }
"@case"			    { count(); return(CASE); }
"@continue"		    { count(); return(CONTINUE); }
"@default"		    { count(); return(DEFAULT); }
"@do"		    { count(); return(DO); }
"@empty"			{ count(); return(EMPTY); }
"@else"			    { count(); return(ELSE); }
"@elseif"			{ count(); return(ELSE); }
"@end"			    { count(); return(END); }
"@enum"			    { count(); return(ENUM); }
"@for"			    { count(); return(FOR); }
"@foreach"			    { count(); return(FOREACH); }
"@if"			    { count(); return(IF); }
"@switch"		    { count(); return(SWITCH); }
"@while"			    { count(); return(WHILE); }


{L}({L}|{D})*	    { count(); return(IDENTIFIER); }
{D}+?		        { count(); return(NUMBER); }

L?\"(\\.|[^\\"])*\"	{ count(); return(STRING_LITERAL); }
[ \t\v\n\f]		    { count(); return(WHITESPACE); }

"++"			{ count(); return(INC_OP); }
"--"			{ count(); return(DEC_OP); }
"&&"			{ count(); return(AND_OP); }
"||"			{ count(); return(OR_OP); }
"<="			{ count(); return(LE_OP); }
">="			{ count(); return(GE_OP); }
"=="			{ count(); return(EQ_OP); }
"!="			{ count(); return(NE_OP); }
"<"		    	{ count(); return(L_OP); }
">"		    	{ count(); return(G_OP); }

"@"             { count(); return('@'); }
";"			    { count(); return(';'); }
","			    { count(); return(','); }
":"			    { count(); return(':'); }
"="			    { count(); return('='); }
"]"     		{ count(); return(']'); }
"."			    { count(); return('.'); }
"&"			    { count(); return('&'); }
"["     		{ count(); return('['); }
"!"			    { count(); return('!'); }
"~"			    { count(); return('~'); }
"-"			    { count(); return('-'); }
"+"			    { count(); return('+'); }
"*"			    { count(); return('*'); }
"/"			    { count(); return('/'); }
"%"			    { count(); return('%'); }
"^"			    { count(); return('^'); }
"|"			    { count(); return('|'); }
")"			    { count(); return(')'); }
"}"		        { count(); return('}'); }
"?"			    { count(); return('?'); }
"{"     		{ count(); return('{'); }
"("			    { count(); return('('); }

.               { scriptlangy_echo(yytext,FLEX_TAG); }
%%

/*** C Code section ***/
void scriptlangl_singleLineomment(){
    char c, c1;

    while ((c = input()) != '\n' && c != 0){
        c1 = c;
        putchar(c);
    }
    if(c1=='\r')
        unput(c1);
    if(c=='\n')
        unput(c);
}
void scriptlangl_multiLineComment()
{
	char c, c1;

loop:
	while ((c = input()) != '*' && c != 0)
		putchar(c);

	if ((c1 = input()) != '/' && c != 0)
	{
		unput(c1);
		goto loop;
	}

	if (c != 0)
		putchar(c1);
}


int column = 0;

void count()
{
	int i;

	for (i = 0; yytext[i] != '\0'; i++)
		if (yytext[i] == '\n')
			column = 0;
		else if (yytext[i] == '\t')
			column += 8 - (column % 8);
		else
			column++;
}
