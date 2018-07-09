/* Definition section */
D			[0-9]
L			[a-zA-Z_]
W 			[ \t\v\n\f]
E			[Ee][+-]?{D}+

%{
/* C code to be copied verbatim */
    #include "scriptlang.tab.h"
    
    extern void scriptlangy_echo(const char* s, const char*ctx, int line, int column);
    
    const char* FLEX_TAG = "[(f)lex] scriptlang.l\0";
	int scriptlangl_column = 1;
	int scriptlangl_nextColumn = 1;
    

	void scriptlangl_count();
    void scriptlangl_multiLineComment();
    void scriptlangl_singleLineomment();

%}
/* This tells flex to read only one input file */
%option noyywrap yylineno header-file="scriptlang.l.h"
%s CONTENT_SECTION

%%

"@/*"			    { scriptlangl_count(); scriptlangl_multiLineComment(); }
"@//"			    { scriptlangl_count(); scriptlangl_singleLineomment(); }
"@@"                { scriptlangl_count(); return(MAGICESC); }
"@\\"               { scriptlangl_count(); return(NEWLINE); }
"@"{W}              { scriptlangl_count(); }
"@\\"[\r]?\n        { scriptlangl_count(); return(NEWLINE); }

"@break"    	    { scriptlangl_count(); return(BREAK); }
"@case"			    { scriptlangl_count(); return(CASE); }
"@continue"		    { scriptlangl_count(); return(CONTINUE); }
"@default"		    { scriptlangl_count(); return(DEFAULT); }
"@define"			{ BEGIN(CONTENT_SECTION); scriptlangl_count(); return(DEFINE); }
"@empty"			{ scriptlangl_count(); return(EMPTY); }
"@else"			    { scriptlangl_count(); return(ELSE); }
"@elseif"			{ scriptlangl_count(); return(ELSE); }
"@end"			    { scriptlangl_count(); return(END); }
"@for"			    { scriptlangl_count(); return(FOR); }
"@foreach"			{ scriptlangl_count(); return(FOREACH); }
"@if"			    { scriptlangl_count(); return(IF); }
"@include"			{ scriptlangl_count(); return(INCLUDE); }
"@namespace"		{ scriptlangl_count(); return(NAMESPACE); }
"@require"			{ scriptlangl_count(); return(REQUIRE); }
"@switch"		    { scriptlangl_count(); return(SWITCH); }
"@use"		    	{ scriptlangl_count(); return(USE); }
"@while"			{ scriptlangl_count(); return(WHILE); }
	

"++"				{ scriptlangl_count(); return(INC_OP); }
"--"				{ scriptlangl_count(); return(DEC_OP); }
"&&"				{ scriptlangl_count(); return(AND_OP); }
"||"				{ scriptlangl_count(); return(OR_OP); }
"<="				{ scriptlangl_count(); return(LE_OP); }
">="				{ scriptlangl_count(); return(GE_OP); }
"=="				{ scriptlangl_count(); return(EQ_OP); }
"!="				{ scriptlangl_count(); return(NE_OP); }
"<"		    		{ scriptlangl_count(); return(L_OP); }
">"		    		{ scriptlangl_count(); return(G_OP); }

"@"             	{ scriptlangl_count(); return('@'); }
";"			    	{ scriptlangl_count(); return(';'); }
"]"     			{ scriptlangl_count(); return(']'); }
"."			    	{ scriptlangl_count(); return('.'); }
"&"			    	{ scriptlangl_count(); return('&'); }
"["     			{ scriptlangl_count(); return('['); }
"!"			    	{ scriptlangl_count(); return('!'); }
"~"			    	{ scriptlangl_count(); return('~'); }
"-"			    	{ scriptlangl_count(); return('-'); }
"+"			    	{ scriptlangl_count(); return('+'); }
"*"			    	{ scriptlangl_count(); return('*'); }
"/"			    	{ scriptlangl_count(); return('/'); }
"%"			    	{ scriptlangl_count(); return('%'); }
"^"			    	{ scriptlangl_count(); return('^'); }
"|"			    	{ scriptlangl_count(); return('|'); }
"?"			    	{ scriptlangl_count(); return('?'); }


L?\"(\\.|[^\\"])*\"							{ scriptlangl_count(); return(STRING_LITERAL); }

{L}({L}|{D})*	    						{ scriptlangl_count(); return(IDENTIFIER); }
{D}+		        						{ scriptlangl_count(); return(INTEGER); }
{D}+"."{D}*({E})		    				{ scriptlangl_count(); return(NUMBER); }
{W}+										{ scriptlangl_count(); return(WHITESPACE); }
{W}*":"{W}* 								{ scriptlangl_count(); return(WCOLON);}
{W}*"("{W}* 								{ scriptlangl_count(); return(WLBRACKET);}
{W}*"{"{W}* 								{ scriptlangl_count(); return(WLBRACE);}
{W}*"}"{W}* 								{ scriptlangl_count(); return(WRBRACE);}
<CONTENT_SECTION>{W}*")"([ \t\v\f])*\n		{ scriptlangl_count(); return(WRBRACKET);}
<CONTENT_SECTION>{W}*")" 					{ scriptlangl_count(); return(WRBRACKET);}
<INITIAL>{W}*")"{W}*						{ scriptlangl_count(); return(WRBRACKET);}
{W}*","{W}* 								{ scriptlangl_count(); return(WCOMMA);}
{W}*"="{W}* 								{ scriptlangl_count(); return(WEQUAL);}
{W}*"@as"{W}* 	    						{ scriptlangl_count(); return(WAS); }
"@"{L}({L}|{D})*	    					{ scriptlangl_count(); return(PARAM); }

.              								{ scriptlangy_echo(yytext,FLEX_TAG, yylineno, scriptlangl_column); }

%%

/*** C Code section { ***/
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
	scriptlangl_column = scriptlangl_nextColumn;

loop:
	while ((c = input()) != '*' && c != 0){
		putchar(c);
		scriptlangl_nextColumn++;
		if (c == '\n'){
			scriptlangl_nextColumn = 1;
		}
	}

	if ((c1 = input()) != '/' && c != 0)
	{
		unput(c1);
		scriptlangl_nextColumn--;
		goto loop;
	}

	if (c != 0){
		putchar(c1);
		scriptlangl_column++;
	}
}



void scriptlangl_count()
{
	int i;
	scriptlangl_column = scriptlangl_nextColumn;
	for (i = 0; yytext[i] != '\0'; i++)
		if (yytext[i] == '\n')
			scriptlangl_nextColumn = 1;
		else if (yytext[i] == '\t')
			scriptlangl_nextColumn += 8 - (scriptlangl_nextColumn % 8);
		else
			scriptlangl_nextColumn++;
}
