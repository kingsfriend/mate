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
	#define YY_USER_ACTION {m_driver.increaseLocation(yyleng); m_driver.setCurrentLine(yylineno);}

	
%}
%option nodefault
%option noyywrap
%option c++
%option yyclass="ScriptScanner"
%option prefix="Mate_"
%option yylineno

%s CONTENT_SECTION

%%

"@" { 
	// cout << "Scanner: MAGIC [\" @ \"]" << endl;
	return mate::ScriptParser::make_MAGIC(mate::location()); 
}
"@/*"([^*]|\*+[^*/])*\*+"/" { 
	// cout << "Scanner: MULTICOMMENT [" << yytext << "]" << endl;
}

"@//"[^\n]*\n { 
	// cout << "Scanner: INLINECOMMENT [" << yytext << "]" << endl;
 }
"@@" { 
	// cout << "Scanner: MAGICESC [\" @@ \"]" << endl;
	return mate::ScriptParser::make_MAGICESC(mate::location()); 
}
"@\\" { 
	// cout << "Scanner: NEWLINE [\" @\\ \"]" << endl;
	return mate::ScriptParser::make_NEWLINE(mate::location()); 
}
"@"{W} { 
	// cout << "Scanner: MAGIC SPACE [\" @{W} \"]" << endl;
}
"@\\"[\r]?\n { 
	// cout << "Scanner: NEWLINE [\" @\\[\\r]?\\n \"]" << endl;
	return mate::ScriptParser::make_NEWLINE(mate::location()); 
}

"@break" {
	// cout << "Scanner: @break" << endl;
	return mate::ScriptParser::make_BREAK(mate::location()); 
}
"@case" {
	// cout << "Scanner: @case" << endl;
	return mate::ScriptParser::make_CASE(mate::location()); 
}
"@continue" {
	// cout << "Scanner: @continue" << endl;
	return mate::ScriptParser::make_CONTINUE(mate::location()); 
}
"@default" {
	// cout << "Scanner: @default" << endl;
	return mate::ScriptParser::make_DEFAULT(mate::location()); 
}
"@define" {
	// cout << "Scanner: @define" << endl;
	BEGIN(CONTENT_SECTION); 
	return mate::ScriptParser::make_DEFINE(mate::location()); 
}
"@empty" {
	// cout << "Scanner: @empty" << endl;
	return mate::ScriptParser::make_EMPTY(mate::location()); 
}
"@else" {
	// cout << "Scanner: @else" << endl;
	return mate::ScriptParser::make_ELSE(mate::location()); 
}
"@elseif" {
	// cout << "Scanner: @elseif" << endl;
	return mate::ScriptParser::make_ELSE(mate::location()); 
}
"@end"{W}? {
	// cout << "Scanner: @end" << endl;
	return mate::ScriptParser::make_BLOCKEND(mate::location()); 
}
"@for" {
	// cout << "Scanner: @for" << endl;
	return mate::ScriptParser::make_FOR(mate::location()); 
}
"@foreach" {
	// cout << "Scanner: @foreach" << endl;
	return mate::ScriptParser::make_FOREACH(mate::location()); 
}
"@if" {
	// cout << "Scanner: @if" << endl;
	return mate::ScriptParser::make_IF(mate::location()); 
}
"@include" {
	// cout << "Scanner: @include" << endl;
	return mate::ScriptParser::make_INCLUDE(mate::location()); 
}
"@namespace" {
	// cout << "Scanner: @namespace" << endl;
	return mate::ScriptParser::make_NAMESPACE(mate::location()); 
}
"@require" {
	// cout << "Scanner: @require" << endl;
	return mate::ScriptParser::make_REQUIRE(mate::location()); 
}
"@switch" {
	// cout << "Scanner: @switch" << endl;
	return mate::ScriptParser::make_SWITCH(mate::location()); 
}
"@use" {
	// cout << "Scanner: @use" << endl;
	return mate::ScriptParser::make_USE(mate::location()); 
}
"@value" {
	// cout << "Scanner: @value" << endl;
	return mate::ScriptParser::make_VAL(mate::location()); 
}
"@var" {
	// cout << "Scanner: @var" << endl;
	return mate::ScriptParser::make_VAR(mate::location()); 
}
"@while" {
	// cout << "Scanner: @while" << endl;
	return mate::ScriptParser::make_WHILE(mate::location()); 
}
	


	
("Bool")|("Number")|("String")|("Date")|("Object")|("Array") {
	// cout << "Scanner: @while" << endl;
	return mate::ScriptParser::make_BASE_DATA_TYPE(std::string(yytext, yyleng), mate::location()); 
}
	
("true")|("false") {
	// cout << "Scanner: @while" << endl;
	return mate::ScriptParser::make_BOOL_CONST(std::string(yytext, yyleng), mate::location()); 
}

("@"(L?\"(\\.|[^\\"])*\"))|("@"(L?'(\\.|[^\'])*')) { // "
	std::string str(yytext, yyleng);
	str.erase(0,2);
	str.erase(str.size()-1);
	// cout << "Scanner: STRING_LITERAL " << str << endl;
	return mate::ScriptParser::make_STRING_LITERAL(str, mate::location()); 
}

{L}({L}|{D})* { 
	// cout << "Scanner: IDENTIFIER" << endl;
	return mate::ScriptParser::make_IDENTIFIER(std::string(yytext, yyleng), mate::location()); 
}
{D}+("."{D}*({E}))? { 
	// cout << "Scanner: NUMBER" << endl;
	return mate::ScriptParser::make_NUMBER(std::string(yytext, yyleng), mate::location()); 
}
{W}+ { 
	// cout << "Scanner: WHITESPACE" << endl;
	return mate::ScriptParser::make_WHITESPACE(std::string(yytext, yyleng), mate::location()); 
}
{W}*":"{W}* { 
	// cout << "Scanner: COLON" << endl;
	return mate::ScriptParser::make_COLON(std::string(yytext, yyleng), mate::location());
}
{W}*"("{W}* { 
	// cout << "Scanner: LBRACKET" << endl;
	return mate::ScriptParser::make_LBRACKET(std::string(yytext, yyleng), mate::location());
}
{W}*"{"{W}* { 
	// cout << "Scanner: LBRACE" << endl;
	return mate::ScriptParser::make_LBRACE(std::string(yytext, yyleng), mate::location());
}
{W}*"}"{W}* { 
	// cout << "Scanner: RBRACE" << endl;
	return mate::ScriptParser::make_RBRACE(std::string(yytext, yyleng), mate::location());
}
<CONTENT_SECTION>{W}*")"([ \t\v\f])*\n { 
	// cout << "Scanner: RBRACKET" << endl;
	return mate::ScriptParser::make_RBRACKET(std::string(yytext, yyleng), mate::location());
}
<CONTENT_SECTION>{W}*")" { 
	// cout << "Scanner: RBRACKET" << endl;
	return mate::ScriptParser::make_RBRACKET(std::string(yytext, yyleng), mate::location());
}
<INITIAL>{W}*")"{W}* { 
	// cout << "Scanner: RBRACKET" << endl;
	return mate::ScriptParser::make_RBRACKET(std::string(yytext, yyleng), mate::location());
}
{W}*","{W}* { 
	// cout << "Scanner: COMMA" << endl;
	return mate::ScriptParser::make_COMMA(std::string(yytext, yyleng), mate::location());
}
{W}*";"{W}* { 
	// cout << "Scanner: SEMICOLON" << endl;
	return mate::ScriptParser::make_SEMICOLON(std::string(yytext, yyleng), mate::location());
}
{W}*"@as"{W}* { 
	// cout << "Scanner: AS" << endl;
	return mate::ScriptParser::make_AS(std::string(yytext, yyleng), mate::location()); 
}
{W}*"["{W}* { 
	// cout << "Scanner: [" << endl;
	return mate::ScriptParser::make_LANGLE_BRACKET(std::string(yytext, yyleng), mate::location()); 
}
{W}*"]"{W}* { 
	// cout << "Scanner: ]" << endl;
	return mate::ScriptParser::make_RANGLE_BRACKET(std::string(yytext, yyleng), mate::location()); 
}

{W}*"="{W}* { 
	// cout << "Scanner: ASSIGN" << endl;
	return mate::ScriptParser::make_ASSIGN(std::string(yytext, yyleng), mate::location());
}
{W}*"++"{W}* { 
	// cout << "Scanner: ++" << endl;
	return mate::ScriptParser::make_INC_OP(std::string(yytext, yyleng), mate::location()); 
}
{W}*"--"{W}* { 
	// cout << "Scanner: --" << endl;
	return mate::ScriptParser::make_DEC_OP(std::string(yytext, yyleng), mate::location()); 
}
{W}*"&&"{W}* { 
	// cout << "Scanner: &&" << endl;
	return mate::ScriptParser::make_AND_OP(std::string(yytext, yyleng), mate::location()); 
}
{W}*"||"{W}* { 
	// cout << "Scanner: ||" << endl;
	return mate::ScriptParser::make_OR_OP(std::string(yytext, yyleng), mate::location()); 
}
{W}*"<="{W}* { 
	// cout << "Scanner: <=" << endl;
	return mate::ScriptParser::make_LE_CMP(std::string(yytext, yyleng), mate::location()); 
}
{W}*">="{W}* { 
	// cout << "Scanner: >=" << endl;
	return mate::ScriptParser::make_GE_CMP(std::string(yytext, yyleng), mate::location()); 
}
{W}*"=="{W}* { 
	// cout << "Scanner: ==" << endl;
	return mate::ScriptParser::make_EQ_CMP(std::string(yytext, yyleng), mate::location()); 
}
{W}*"!="{W}* { 
	// cout << "Scanner: !=" << endl;
	return mate::ScriptParser::make_NE_CMP(std::string(yytext, yyleng), mate::location()); 
}
{W}*"<"{W}* { 
	// cout << "Scanner: <" << endl;
	return mate::ScriptParser::make_L_CMP(std::string(yytext, yyleng), mate::location()); 
}
{W}*">"{W}* { 
	// cout << "Scanner: >" << endl;
	return mate::ScriptParser::make_G_CMP(std::string(yytext, yyleng), mate::location()); 
}
{W}*"?"{W}* { 
	// cout << "Scanner: ?" << endl;
	return mate::ScriptParser::make_QUESTION(std::string(yytext, yyleng), mate::location()); 
}
{W}*"^"{W}* { 
	// cout << "Scanner: ^" << endl;
	return mate::ScriptParser::make_EXC_LOGIC(std::string(yytext, yyleng), mate::location()); 
}
{W}*"|"{W}* { 
	// cout << "Scanner: |" << endl;
	return mate::ScriptParser::make_OR_LOGIC(std::string(yytext, yyleng), mate::location()); 
}
{W}*"&"{W}* { 
	// cout << "Scanner: &" << endl;
	return mate::ScriptParser::make_AND_LOGIC(std::string(yytext, yyleng), mate::location()); 
}
{W}*"*"{W}* { 
	// cout << "Scanner: *" << endl;
	return mate::ScriptParser::make_MUL_SIGN(std::string(yytext, yyleng), mate::location()); 
}
{W}*"/"{W}* { 
	// cout << "Scanner: /" << endl;
	return mate::ScriptParser::make_DIV_SIGN(std::string(yytext, yyleng), mate::location()); 
}
{W}*"%"{W}* { 
	// cout << "Scanner: %" << endl;
	return mate::ScriptParser::make_MOD_SIGN(std::string(yytext, yyleng), mate::location()); 
}
{W}*"+"{W}* { 
	// cout << "Scanner: +" << endl;
	return mate::ScriptParser::make_ADD_SIGN(std::string(yytext, yyleng), mate::location()); 
}
{W}*"-"{W}* { 
	// cout << "Scanner: -" << endl;
	return mate::ScriptParser::make_SUB_SIGN(std::string(yytext, yyleng), mate::location()); 
}

{W}*"*="{W}* { 
	// cout << "Scanner: *" << endl;
	return mate::ScriptParser::make_MUL_ASSIGN(std::string(yytext, yyleng), mate::location()); 
}
{W}*"/="{W}* { 
	// cout << "Scanner: /" << endl;
	return mate::ScriptParser::make_DIV_ASSIGN(std::string(yytext, yyleng), mate::location()); 
}
{W}*"%="{W}* { 
	// cout << "Scanner: %" << endl;
	return mate::ScriptParser::make_MOD_ASSIGN(std::string(yytext, yyleng), mate::location()); 
}
{W}*"+="{W}* { 
	// cout << "Scanner: +" << endl;
	return mate::ScriptParser::make_ADD_ASSIGN(std::string(yytext, yyleng), mate::location()); 
}
{W}*"-="{W}* { 
	// cout << "Scanner: -" << endl;
	return mate::ScriptParser::make_SUB_ASSIGN(std::string(yytext, yyleng), mate::location()); 
}
{W}*"^="{W}* { 
	// cout << "Scanner: ^" << endl;
	return mate::ScriptParser::make_EXC_ASSIGN(std::string(yytext, yyleng), mate::location()); 
}
{W}*"|="{W}* { 
	// cout << "Scanner: |" << endl;
	return mate::ScriptParser::make_OR_ASSIGN(std::string(yytext, yyleng), mate::location()); 
}
{W}*"&="{W}* { 
	// cout << "Scanner: &" << endl;
	return mate::ScriptParser::make_AND_ASSIGN(std::string(yytext, yyleng), mate::location()); 
}
{W}*"."{W}* { 
	// cout << "Scanner: PERIOD" << endl;
	return mate::ScriptParser::make_PERIOD(std::string(yytext, yyleng), mate::location()); 
}
{W}*"!"{W}* { 
	// cout << "Scanner: !" << endl;
	return mate::ScriptParser::make_CHAR(std::string(yytext, yyleng), mate::location()); 
}
{W}*"~"{W}* { 
	// cout << "Scanner: ~" << endl;
	return mate::ScriptParser::make_CHAR(std::string(yytext, yyleng), mate::location()); 
}




"@"{L}({L}|{D})* { 
	// cout << "Scanner: PARAM" << endl;
	return mate::ScriptParser::make_PARAM(std::string(yytext, yyleng), mate::location()); 
}

. { 
	// cout << "Scanner: UNDEFINED \"" << YYText() << "\"" << endl;
	return mate::ScriptParser::make_UNDEFINED(std::string(yytext, yyleng), mate::location()); 
}

<<EOF>> { 
	return mate::ScriptParser::make_END(mate::location());
}
%%

/*** C Code section { ***/