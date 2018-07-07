/* Definition section */
D			[0-9]
L			[a-zA-Z_]
W 			[ \t\v\n\f]
E			[Ee][+-]?{D}+

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
%s CONTENT_SECTION

%%

"@/*"			    { scriptlangl_multiLineComment(); }
"@//"			    { scriptlangl_singleLineomment(); }
"@@"                { count(); return(MAGICESC); }
"@\\"               { count(); return(NEWLINE); }
"@"{W}              { count(); }
"@\\"[\r]?\n        { count(); return(NEWLINE); }

"@break"    	    { count(); return(BREAK); }
"@case"			    { count(); return(CASE); }
"@continue"		    { count(); return(CONTINUE); }
"@default"		    { count(); return(DEFAULT); }
"@define"			{ BEGIN(CONTENT_SECTION); count(); return(DEFINE); }
"@empty"			{ count(); return(EMPTY); }
"@else"			    { count(); return(ELSE); }
"@elseif"			{ count(); return(ELSE); }
"@end"			    { count(); return(END); }
"@for"			    { count(); return(FOR); }
"@foreach"			{ count(); return(FOREACH); }
"@if"			    { count(); return(IF); }
"@include"			{ count(); return(INCLUDE); }
"@namespace"		{ count(); return(NAMESPACE); }
"@require"			{ count(); return(REQUIRE); }
"@switch"		    { count(); return(SWITCH); }
"@use"		    	{ count(); return(USE); }
"@while"			{ count(); return(WHILE); }
	

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


L?\"(\\.|[^\\"])*\"							{ count(); return(STRING_LITERAL); }

{L}({L}|{D})*	    						{ count(); return(IDENTIFIER); }
{D}+		        						{ count(); return(INTEGER); }
{D}+"."{D}*({E})		    				{ count(); return(NUMBER); }
{W}+										{ count(); return(WHITESPACE); }
{W}*":"{W}* 								{ count(); return(WCOLON);}
{W}*"("{W}* 								{ count(); return(WLBRACKET);}
{W}*"{"{W}* 								{ count(); return(WLBRACE);}
{W}*"}"{W}* 								{ count(); return(WRBRACE);}
<CONTENT_SECTION>{W}*")"([ \t\v\f])*\n		{ count(); return(WRBRACKET);}
<CONTENT_SECTION>{W}*")" 					{ count(); return(WRBRACKET);}
<INITIAL>{W}*")"{W}*						{ count(); return(WRBRACKET);}
{W}*","{W}* 								{ count(); return(WCOMMA);}
{W}*"="{W}* 								{ count(); return(WEQUAL);}
{W}*"@as"{W}* 	    						{ count(); return(WAS); }
"@"{L}({L}|{D})*	    					{ count(); return(PARAM); }

.              				{ scriptlangy_echo(yytext,FLEX_TAG); }

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
