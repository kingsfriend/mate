/*** Definition section ***/
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
"@@"            { return MAGICESC; }
"@/*"			{ scriptlangl_multiLineComment(); }
"@//"			{ scriptlangl_singleLineomment(); }
"@"             { return MAGIC; }

"break"			{ count(); return(BREAK); }
"case"			{ count(); return(CASE); }

[ \t\v\n\f]		{ count(); return(WHITESPACE); }
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
