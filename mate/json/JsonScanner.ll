/* Definition section */
D			[0-9]
L			[a-zA-Z_]
W 			[ \t\v\n\f]
E			[Ee][+-]?{D}+

%{
/* C code to be copied verbatim */
    #include <iostream>
	#include <cstdlib>
	#include <string>
	#include "JsonScanner.hpp"
	#include "JsonParser.hpp"
	#include "location.hh"

	#include "JsonInterpreter.hpp"

	#define yyterminate() mate::JsonParser::make_END(mate::location());
	#define YY_USER_ACTION {m_driver.increaseLocation(yyleng); m_driver.setCurrentLine(yylineno);}

	
%}
%option nodefault
%option noyywrap
%option c++
%option yyclass="JsonScanner"
%option prefix="Mate_"
%option yylineno

%s CONTENT_SECTION

%%


("true")|("false") {
	bool val = std::string(yytext, yyleng) == "true";
	// cout << "Scanner: BOOL" << val << endl;
	return mate::JsonParser::make_BOOL(val, mate::location()); 
}

(L?\"(\\.|[^\\"])*\")|(L?'(\\.|[^\'])*') { // "
	std::string str(yytext, yyleng);
	str.erase(0,1);
	str.erase(str.size()-1);
	// cout << "Scanner: STRING" << str << endl;
	return mate::JsonParser::make_STRING(str, mate::location()); 
}

{D}+("."{D}*({E}))? { 
	// cout << "Scanner: NUMBER" << endl;
	std::string strVal = std::string(yytext, yyleng);
	double val = atof(strVal.c_str());;
	return mate::JsonParser::make_NUMBER(val, mate::location()); 
}
{W}+ { 
	// cout << "Scanner: WHITESPACE" << endl;
}
"null" { 
	// cout << "Scanner: NULL" << endl;
	return mate::JsonParser::make_NULL(mate::location());
}
":" { 
	// cout << "Scanner: COLON" << endl;
	return mate::JsonParser::make_COLON(mate::location());
}
"{" { 
	// cout << "Scanner: LBRACE" << endl;
	return mate::JsonParser::make_LBRACE(mate::location());
}
"}" { 
	// cout << "Scanner: RBRACE" << endl;
	return mate::JsonParser::make_RBRACE(mate::location());
}
"," { 
	// cout << "Scanner: COMMA" << endl;
	return mate::JsonParser::make_COMMA(mate::location());
}
"[" { 
	// cout << "Scanner: [" << endl;
	return mate::JsonParser::make_LANGLE_BRACKET(mate::location()); 
}
"]" { 
	// cout << "Scanner: ]" << endl;
	return mate::JsonParser::make_RANGLE_BRACKET(mate::location()); 
}

. { 
	// cout << "Scanner: UNDEFINED \"" << YYText() << "\"" << endl;
	return mate::JsonParser::make_UNDEFINED(std::string(yytext, yyleng), mate::location()); 
}

<<EOF>> { 
	return mate::JsonParser::make_END(mate::location());
}
%%

/*** C Code section { ***/