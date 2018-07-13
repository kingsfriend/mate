#ifndef SCRIPT_SCANNER_H
    #define SCRIPT_SCANNER_H 

    #if !defined(yyFlexLexerOnce)
        #undef yyFlexLexer
        #define yyFlexLexer Mate_FlexLexer 
        #include <FlexLexer.h>
    #endif

    #undef YY_DECL
    #define YY_DECL mate::ScriptParser::symbol_type mate::ScriptScanner::nextToken()

#include <cstdio>
#include "ScriptParser.hpp"

namespace mate
{

    // Forward declare ScriptInterpreter to avoid include. Header is added in implementation file.
    class ScriptInterpreter;

    class ScriptScanner : public yyFlexLexer
    {
        public:
            ScriptScanner(ScriptInterpreter &driver) : m_driver(driver) {}
            ScriptScanner(ScriptInterpreter &driver, istream *new_in) : yyFlexLexer(new_in), m_driver(driver) {}
            ScriptScanner(ScriptInterpreter &driver, istream *new_in, std::ostream *new_os) : yyFlexLexer(new_in, new_os), m_driver(driver) {}
            virtual ~ScriptScanner() {}
            virtual mate::ScriptParser::symbol_type nextToken();
            void echo(const std::string s)
            {
                yyout << s;
            }

          private:
            ScriptInterpreter &m_driver;
    };

}

#endif