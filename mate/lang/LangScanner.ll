/* Definition section */
D			[0-9]
L			[a-zA-Z_]
W 			[ \t\v\n\f]
E			[Ee][+-]?{D}+

%{
/* C code to be copied verbatim */
    #include <iostream>
	#include <cstdlib>
	#include "LangScanner.hpp"
	#include "LangParser.hpp"
	#include "location.hh"

	#include "LangInterpreter.hpp"
	#include "../ast/Json.hpp"

	#define yyterminate() mate::LangParser::make_END(mate::location());
	#define YY_USER_ACTION {m_driver.increaseLocation(yyleng); m_driver.setCurrentLine(yylineno);}

	
%}
%option nodefault
%option noyywrap
%option c++
%option yyclass="LangScanner"
%option prefix="Mate_"
%option yylineno

%%

"as" { 
	// cout << "Scanner: AS" << endl;
	return mate::LangParser::make_AS(mate::location()); 
}
"break" {
	// cout << "Scanner: BREAK" << endl;
	return mate::LangParser::make_BREAK(mate::location()); 
}
"case" {
	// cout << "Scanner: CASE" << endl;
	return mate::LangParser::make_CASE(mate::location()); 
}
"class" {
	// cout << "Scanner: CLASS" << endl;
	return mate::LangParser::make_CLASS(mate::location()); 
}
"continue" {
	// cout << "Scanner: CONTINUE" << endl;
	return mate::LangParser::make_CONTINUE(mate::location()); 
}
"default" {
	// cout << "Scanner: DEFAULT" << endl;
	return mate::LangParser::make_DEFAULT(mate::location()); 
}
"empty" {
	// cout << "Scanner: EMPTY" << endl;
	return mate::LangParser::make_EMPTY(mate::location()); 
}
"else" {
	// cout << "Scanner: ELSE" << endl;
	return mate::LangParser::make_ELSE(mate::location()); 
}
"elseif" {
	// cout << "Scanner: ELSEIF" << endl;
	return mate::LangParser::make_ELSE(mate::location()); 
}
"final" {
	// cout << "Scanner: FINAL" << endl;
	return mate::LangParser::make_FINAL(mate::location()); 
}
"for" {
	// cout << "Scanner: FOR" << endl;
	return mate::LangParser::make_FOR(mate::location()); 
}
"foreach" {
	// cout << "Scanner: FOREACH" << endl;
	return mate::LangParser::make_FOREACH(mate::location()); 
}
"if" {
	// cout << "Scanner: IF" << endl;
	return mate::LangParser::make_IF(mate::location()); 
}
"in" { 
	// cout << "Scanner: IN" << endl;
	return mate::LangParser::make_IN(mate::location()); 
}
"internal" {
	// cout << "Scanner: INTERNAL" << endl;
	return mate::LangParser::make_INTERNAL(mate::location()); 
}
"namespace" {
	// cout << "Scanner: NAMESPACE" << endl;
	return mate::LangParser::make_NAMESPACE(mate::location()); 
}
"public" {
	// cout << "Scanner: PUBLIC" << endl;
	return mate::LangParser::make_PUBLIC(mate::location()); 
}
"static" {
	// cout << "Scanner: STATIC" << endl;
	return mate::LangParser::make_STATIC(mate::location()); 
}
"switch" {
	// cout << "Scanner: SWITCH" << endl;
	return mate::LangParser::make_SWITCH(mate::location()); 
}
"use" {
	// cout << "Scanner: USE" << endl;
	return mate::LangParser::make_USE(mate::location()); 
}
"while" {
	// cout << "Scanner: WHILE" << endl;
	return mate::LangParser::make_WHILE(mate::location()); 
}


"Bool" {
	// cout << "Scanner: BOOL_TYPE" << endl;
	return mate::LangParser::make_BOOL_TYPE(Bool, mate::location()); 
}
"Number" {
	// cout << "Scanner: NUMBER_TYPE" << endl;
	return mate::LangParser::make_NUMBER_TYPE(Bool, mate::location()); 
}
"String" {
	// cout << "Scanner: STRING_TYPE" << endl;
	return mate::LangParser::make_STRING_TYPE(Bool, mate::location()); 
}
"Date" {
	// cout << "Scanner: DATE_TYPE" << endl;
	return mate::LangParser::make_DATE_TYPE(Bool, mate::location()); 
}
"Object" {
	// cout << "Scanner: OBJECT_TYPE" << endl;
	return mate::LangParser::make_OBJECT_TYPE(Bool, mate::location()); 
}
"Array" {
	// cout << "Scanner: ARRAY_TYPE" << endl;
	return mate::LangParser::make_ARRAY_TYPE(Bool, mate::location()); 
}
"Void" {
	// cout << "Scanner: VOID_TYPE" << endl;
	return mate::LangParser::make_VOID_TYPE(Void, mate::location()); 
}
"true" {
	// cout << "Scanner: TRUE" << endl;
	return mate::LangParser::make_TRUE(true, mate::location()); 
}
"false" {
	// cout << "Scanner: FALSE" << endl;
	return mate::LangParser::make_FALSE(false, mate::location()); 
}


((L?\"(\\.|[^\\"])*\"))|((L?'(\\.|[^\'])*')) { // "
	std::string str(yytext, yyleng);
	str.erase(0,1);
	str.erase(str.size()-1);
	// cout << "Scanner: STRING_LITERAL " << str << endl;
	return mate::LangParser::make_STRING_LITERAL(str, mate::location()); 
}
("@"(L?\"(\\.|[^\\"])*\"))|("@"(L?'(\\.|[^\'])*')) { // "
	std::string str(yytext, yyleng);
	str.erase(0,2);
	str.erase(str.size()-1);
	// cout << "Scanner: VALUABLE_STRING " << str << endl;
	return mate::LangParser::make_VALUABLE_STRING(str, mate::location()); 
}


{W}+ { 
	// cout << "Scanner: WHITESPACE" << endl;
	// Ignored
}
{L}({L}|{D})* { 
	// cout << "Scanner: IDENTIFIER" << endl;
	return mate::LangParser::make_IDENTIFIER(std::string(yytext, yyleng), mate::location()); 
}
{D}+("."{D}*({E}))? { 
	// cout << "Scanner: NUMBER" << endl;
	std::string strVal = std::string(yytext, yyleng);
	double val = atof(strVal.c_str());;
	return mate::LangParser::make_NUMBER(val, mate::location()); 
}


"(" { 
	// cout << "Scanner: LBRACKET" << endl;
	return mate::LangParser::make_LBRACKET(mate::location());
}
")" { 
	// cout << "Scanner: RBRACKET" << endl;
	return mate::LangParser::make_RBRACKET(mate::location());
}
"{" { 
	// cout << "Scanner: LBRACE" << endl;
	return mate::LangParser::make_LBRACE(mate::location());
}
"}" { 
	// cout << "Scanner: RBRACE" << endl;
	return mate::LangParser::make_RBRACE(mate::location());
}
"[" { 
	// cout << "Scanner: LANGLE_BRACKET" << endl;
	return mate::LangParser::make_LANGLE_BRACKET(mate::location()); 
}
"]" { 
	// cout << "Scanner: RANGLE_BRACKET" << endl;
	return mate::LangParser::make_RANGLE_BRACKET(mate::location()); 
}


".*" { 
	// cout << "Scanner: MATCH_ANY" << endl;
	return mate::LangParser::make_MATCH_ANY(mate::location());
}

"." { 
	// cout << "Scanner: PERIOD" << endl;
	return mate::LangParser::make_PERIOD(mate::location());
}
"," { 
	// cout << "Scanner: COMMA" << endl;
	return mate::LangParser::make_COMMA(mate::location());
}
";" { 
	// cout << "Scanner: SEMICOLON" << endl;
	return mate::LangParser::make_SEMICOLON(mate::location());
}
":" { 
	// cout << "Scanner: COLON" << endl;
	return mate::LangParser::make_COLON(mate::location());
}



"/*"([^*]|\*+[^*/])*\*+"/" { 
	// cout << "Scanner: MULTICOMMENT [" << yytext << "]" << endl;
}
"//"[^\n]*\n { 
	// cout << "Scanner: INLINECOMMENT [" << yytext << "]" << endl;
 }

. { 
	cout << "Scanner: UNDEFINED \"" << YYText() << "\"" << endl;
	return mate::LangParser::make_UNDEFINED(std::string(yytext, yyleng), mate::location()); 
}
<<EOF>> { 
	return mate::LangParser::make_END(mate::location());
}
%%

/*** C Code section { ***/