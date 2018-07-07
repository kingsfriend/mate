/* Definition section */
D			[0-9]
L			[a-zA-Z_]
W 			[ \t\v\n\f]
E			[Ee][+-]?{D}+

%{
/* C code to be copied verbatim */
    #include "classlang.tab.h"
    
    extern void classlangy_echo(const char* s, const char*ctx);
    
    const char* FLEX_TAG = "[(f)lex] classlang.l\0";
    void count();
    void classlangl_multiLineComment();
    void classlangl_singleLineomment();
%}
/* This tells flex to read only one input file */
%option noyywrap
%s CONTENT_SECTION

%%

"/*"			    { classlangl_multiLineComment(); }
"//"			    { classlangl_singleLineomment(); }

"as"    	   	 	{ count(); return(AS); }
"break"    	   	 	{ count(); return(BREAK); }
"case"			    { count(); return(CASE); }
"class"				{ count(); return(CLASS); }
"continue"		    { count(); return(CONTINUE); }
"default"		    { count(); return(DEFAULT); }
"empty"				{ count(); return(EMPTY); }
"else"			    { count(); return(ELSE); }
"elseif"			{ count(); return(ELSE); }
"extends"			{ count(); return(EXTENDS); }
"end"			    { count(); return(END); }
"for"			    { count(); return(FOR); }
"foreach"			{ count(); return(FOREACH); }
"if"			    { count(); return(IF); }
"implements"		{ count(); return(IMPLEMENTS); }
"interface"			{ count(); return(INTERFACE); }
"namespace"			{ count(); return(NAMESPACE); }
"switch"		    { count(); return(SWITCH); }
"use"		    	{ count(); return(USE); }
"while"				{ count(); return(WHILE); }
	

"++"				{ count(); return(INC_OP); }
"--"				{ count(); return(DEC_OP); }
"&&"				{ count(); return(AND_OP); }
"||"				{ count(); return(OR_OP); }
"<="				{ count(); return(LE_OP); }
">="				{ count(); return(GE_OP); }
"=="				{ count(); return(EQ_OP); }
"!="				{ count(); return(NE_OP); }
"<"		    		{ count(); return(L_OP); }
">"		    		{ count(); return(G_OP); }

"@"             	{ count(); return('@'); }
";"			    	{ count(); return(';'); }
"]"     			{ count(); return(']'); }
"."			    	{ count(); return('.'); }
"&"			    	{ count(); return('&'); }
"["     			{ count(); return('['); }
"!"			    	{ count(); return('!'); }
"~"			    	{ count(); return('~'); }
"-"			    	{ count(); return('-'); }
"+"			    	{ count(); return('+'); }
"*"			    	{ count(); return('*'); }
"/"			    	{ count(); return('/'); }
"%"			    	{ count(); return('%'); }
"^"			    	{ count(); return('^'); }
"|"			    	{ count(); return('|'); }
"?"			    	{ count(); return('?'); }



{W}+										{ count(); return(WITHESPACE); }
{L}({L}|{D})*	    						{ count(); return(IDENTIFIER); }
{D}+		        						{ count(); return(INTEGER); }
{D}+"."{D}*({E})		    				{ count(); return(NUMBER); }
L?\"(\\.|[^\\"])*\"							{ count(); return(STRING_LITERAL); }
{W}*":"{W}* 								{ count(); return(WCOLON);}
{W}*"("{W}* 								{ count(); return(WLBRACKET);}
{W}*"{"{W}* 								{ count(); return(WLBRACE);}
{W}*"}"{W}* 								{ count(); return(WRBRACE);}
{W}*")"{W}*				 					{ count(); return(WRBRACKET);}
{W}*","{W}* 								{ count(); return(WCOMMA);}
{W}*"="{W}* 								{ count(); return(WEQUAL);}

.              								{ classlangy_echo(yytext,FLEX_TAG); }

%%

/*** C Code section ***/
void classlangl_singleLineomment(){
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
void classlangl_multiLineComment()
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
