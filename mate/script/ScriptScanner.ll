/* Definition section */
D			[0-9]
L			[a-zA-Z_]
W 			[ \t\v\n\f]
E			[Ee][+-]?{D}+

%{
/* C code to be copied verbatim */
    #include <iostream>
	#include <cstdlib>
	#include "ScriptScanner.hpp"
	#include "ScriptParser.hpp"
	#include "location.hh"

	#include "ScriptInterpreter.hpp"

	#define yyterminate() mate::ScriptParser::make_END(mate::location());
	#define YY_USER_ACTION m_driver.increaseLocation(yyleng);

	
%}
%option nodefault
%option noyywrap
%option c++
%option yyclass="ScriptScanner"
%option prefix="Mate_"

%s CONTENT_SECTION

%%

"@/*"([^*]|\*+[^*/])*\*+"/" { 
	cout << "Scanner: MULTICOMMENT [" << yytext << "]" << endl;
}

"@//"[^\n]*\n { 
	cout << "Scanner: INLINECOMMENT [" << yytext << "]" << endl;

 }
"@@" { 
	cout << "Scanner: MAGICESC [\" @@ \"]" << endl;
	return mate::ScriptParser::make_MAGICESC(mate::location()); 
}
"@\\" { 
	cout << "Scanner: NEWLINE [\" @\\ \"]" << endl;
	return mate::ScriptParser::make_NEWLINE(mate::location()); 
}
"@"{W} { 
	cout << "Scanner: MAGIC SPACE [\" @{W} \"]" << endl;
}
"@\\"[\r]?\n { 
	cout << "Scanner: NEWLINE [\" @\\[\\r]?\\n \"]" << endl;
	return mate::ScriptParser::make_NEWLINE(mate::location()); 
}

"@break" {
	cout << "Scanner: @break" << endl;
	return mate::ScriptParser::make_BREAK(mate::location()); 
}
"@case" {
	cout << "Scanner: @case" << endl;
	return mate::ScriptParser::make_CASE(mate::location()); 
}
"@continue" {
	cout << "Scanner: @continue" << endl;
	return mate::ScriptParser::make_CONTINUE(mate::location()); 
}
"@default" {
	cout << "Scanner: @default" << endl;
	return mate::ScriptParser::make_DEFAULT(mate::location()); 
}
"@define" {
	cout << "Scanner: @define" << endl;
	BEGIN(CONTENT_SECTION); 
	return mate::ScriptParser::make_DEFINE(mate::location()); 
}
"@empty" {
	cout << "Scanner: @empty" << endl;
	return mate::ScriptParser::make_EMPTY(mate::location()); 
}
"@else" {
	cout << "Scanner: @else" << endl;
	return mate::ScriptParser::make_ELSE(mate::location()); 
}
"@elseif" {
	cout << "Scanner: @elseif" << endl;
	return mate::ScriptParser::make_ELSE(mate::location()); 
}
"@end"{W}? {
	cout << "Scanner: @end" << endl;
	return mate::ScriptParser::make_BLOCKEND(mate::location()); 
}
"@for" {
	cout << "Scanner: @for" << endl;
	return mate::ScriptParser::make_FOR(mate::location()); 
}
"@foreach" {
	cout << "Scanner: @foreach" << endl;
	return mate::ScriptParser::make_FOREACH(mate::location()); 
}
"@if" {
	cout << "Scanner: @if" << endl;
	return mate::ScriptParser::make_IF(mate::location()); 
}
"@include" {
	cout << "Scanner: @include" << endl;
	return mate::ScriptParser::make_INCLUDE(mate::location()); 
}
"@namespace" {
	cout << "Scanner: @namespace" << endl;
	return mate::ScriptParser::make_NAMESPACE(mate::location()); 
}
"@require" {
	cout << "Scanner: @require" << endl;
	return mate::ScriptParser::make_REQUIRE(mate::location()); 
}
"@switch" {
	cout << "Scanner: @switch" << endl;
	return mate::ScriptParser::make_SWITCH(mate::location()); 
}
"@use" {
	cout << "Scanner: @use" << endl;
	return mate::ScriptParser::make_USE(mate::location()); 
}
"@while" {
	cout << "Scanner: @while" << endl;
	return mate::ScriptParser::make_WHILE(mate::location()); 
}
	

"++" { 
	cout << "Scanner: ++" << endl;
	return mate::ScriptParser::make_INC_OP(std::string(yytext, yyleng), mate::location()); 
}
"--" { 
	cout << "Scanner: --" << endl;
	return mate::ScriptParser::make_DEC_OP(std::string(yytext, yyleng), mate::location()); 
}
"&&" { 
	cout << "Scanner: &&" << endl;
	return mate::ScriptParser::make_AND_OP(std::string(yytext, yyleng), mate::location()); 
}
"||" { 
	cout << "Scanner: ||" << endl;
	return mate::ScriptParser::make_OR_OP(std::string(yytext, yyleng), mate::location()); 
}
"<=" { 
	cout << "Scanner: <=" << endl;
	return mate::ScriptParser::make_LE_OP(std::string(yytext, yyleng), mate::location()); 
}
">=" { 
	cout << "Scanner: >=" << endl;
	return mate::ScriptParser::make_GE_OP(std::string(yytext, yyleng), mate::location()); 
}
"==" { 
	cout << "Scanner: ==" << endl;
	return mate::ScriptParser::make_EQ_OP(std::string(yytext, yyleng), mate::location()); 
}
"!=" { 
	cout << "Scanner: !=" << endl;
	return mate::ScriptParser::make_NE_OP(std::string(yytext, yyleng), mate::location()); 
}
"<" { 
	cout << "Scanner: <" << endl;
	return mate::ScriptParser::make_L_OP(std::string(yytext, yyleng), mate::location()); 
}
">" { 
	cout << "Scanner: >" << endl;
	return mate::ScriptParser::make_G_OP(std::string(yytext, yyleng), mate::location()); 
}


";" { 
	cout << "Scanner: ;" << endl;
	return mate::ScriptParser::make_CHAR(std::string(yytext, yyleng), mate::location()); 
}
"]" { 
	cout << "Scanner: ]" << endl;
	return mate::ScriptParser::make_CHAR(std::string(yytext, yyleng), mate::location()); 
}
"." { 
	cout << "Scanner: ." << endl;
	return mate::ScriptParser::make_CHAR(std::string(yytext, yyleng), mate::location()); 
}
"&" { 
	cout << "Scanner: &" << endl;
	return mate::ScriptParser::make_CHAR(std::string(yytext, yyleng), mate::location()); 
}
"[" { 
	cout << "Scanner: [" << endl;
	return mate::ScriptParser::make_CHAR(std::string(yytext, yyleng), mate::location()); 
}
"!" { 
	cout << "Scanner: !" << endl;
	return mate::ScriptParser::make_CHAR(std::string(yytext, yyleng), mate::location()); 
}
"~" { 
	cout << "Scanner: ~" << endl;
	return mate::ScriptParser::make_CHAR(std::string(yytext, yyleng), mate::location()); 
}
"-" { 
	cout << "Scanner: -" << endl;
	return mate::ScriptParser::make_CHAR(std::string(yytext, yyleng), mate::location()); 
}
"+" { 
	cout << "Scanner: +" << endl;
	return mate::ScriptParser::make_CHAR(std::string(yytext, yyleng), mate::location()); 
}
"*" { 
	cout << "Scanner: *" << endl;
	return mate::ScriptParser::make_CHAR(std::string(yytext, yyleng), mate::location()); 
}
"/" { 
	cout << "Scanner: /" << endl;
	return mate::ScriptParser::make_CHAR(std::string(yytext, yyleng), mate::location()); 
}
"%" { 
	cout << "Scanner: %" << endl;
	return mate::ScriptParser::make_CHAR(std::string(yytext, yyleng), mate::location()); 
}
"^" { 
	cout << "Scanner: ^" << endl;
	return mate::ScriptParser::make_CHAR(std::string(yytext, yyleng), mate::location()); 
}
"|" { 
	cout << "Scanner: |" << endl;
	return mate::ScriptParser::make_CHAR(std::string(yytext, yyleng), mate::location()); 
}
"?" { 
	cout << "Scanner: ?" << endl;
	return mate::ScriptParser::make_CHAR(std::string(yytext, yyleng), mate::location()); 
}


L?\"(\\.|[^\\"])*\" { 
	cout << "Scanner: STRING_LITERAL" << endl;
	return mate::ScriptParser::make_STRING_LITERAL(std::string(yytext, yyleng), mate::location()); 
}

{L}({L}|{D})* { 
	cout << "Scanner: IDENTIFIER" << endl;
	return mate::ScriptParser::make_IDENTIFIER(std::string(yytext, yyleng), mate::location()); 
}
{D}+ { 
	cout << "Scanner: INTEGER" << endl;
	return mate::ScriptParser::make_INTEGER(std::string(yytext, yyleng), mate::location()); 
}
{D}+"."{D}*({E}) { 
	cout << "Scanner: NUMBER" << endl;
	return mate::ScriptParser::make_NUMBER(std::string(yytext, yyleng), mate::location()); 
}
{W}+ { 
	cout << "Scanner: WHITESPACE" << endl;
	return mate::ScriptParser::make_WHITESPACE(std::string(yytext, yyleng), mate::location()); 
}
{W}*":"{W}* { 
	cout << "Scanner: WCOLON" << endl;
	return mate::ScriptParser::make_WCOLON(std::string(yytext, yyleng), mate::location());
}
{W}*"("{W}* { 
	cout << "Scanner: WLBRACKET" << endl;
	return mate::ScriptParser::make_WLBRACKET(std::string(yytext, yyleng), mate::location());
}
{W}*"{"{W}* { 
	cout << "Scanner: WLBRACE" << endl;
	return mate::ScriptParser::make_WLBRACE(std::string(yytext, yyleng), mate::location());
}
{W}*"}"{W}* { 
	cout << "Scanner: WRBRACE" << endl;
	return mate::ScriptParser::make_WRBRACE(std::string(yytext, yyleng), mate::location());
}
<CONTENT_SECTION>{W}*")"([ \t\v\f])*\n { 
	cout << "Scanner: WRBRACKET" << endl;
	return mate::ScriptParser::make_WRBRACKET(std::string(yytext, yyleng), mate::location());
}
<CONTENT_SECTION>{W}*")" { 
	cout << "Scanner: WRBRACKET" << endl;
	return mate::ScriptParser::make_WRBRACKET(std::string(yytext, yyleng), mate::location());
}
<INITIAL>{W}*")"{W}* { 
	cout << "Scanner: WRBRACKET" << endl;
	return mate::ScriptParser::make_WRBRACKET(std::string(yytext, yyleng), mate::location());
}
{W}*","{W}* { 
	cout << "Scanner: WCOMMA" << endl;
	return mate::ScriptParser::make_WCOMMA(std::string(yytext, yyleng), mate::location());
}
{W}*"="{W}* { 
	cout << "Scanner: WEQUAL" << endl;
	return mate::ScriptParser::make_WEQUAL(std::string(yytext, yyleng), mate::location());
}
{W}*"@as"{W}* { 
	cout << "Scanner: WAS" << endl;
	return mate::ScriptParser::make_WAS(std::string(yytext, yyleng), mate::location()); 
}
"@"{L}({L}|{D})* { 
	cout << "Scanner: PARAM" << endl;
	return mate::ScriptParser::make_PARAM(std::string(yytext, yyleng), mate::location()); 
}

. { 
	cout << "Scanner: ?" << endl;
	printf("\"%s\"",YYText()); 
}

<<EOF>> { 
	return mate::ScriptParser::make_END(mate::location());
}
%%

/*** C Code section { ***/