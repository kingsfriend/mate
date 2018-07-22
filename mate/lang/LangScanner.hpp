#ifndef SCRIPT_SCANNER_H
    #define SCRIPT_SCANNER_H 

    #if !defined(yyFlexLexerOnce)
        #undef yyFlexLexer
        #define yyFlexLexer Mate_FlexLexer 
        #include <FlexLexer.h>
    #endif

    #undef YY_DECL
    #define YY_DECL mate::LangParser::symbol_type mate::LangScanner::nextToken()

#include <cstdio>
#include "LangParser.hpp"

namespace mate
{

    // Forward declare LangInterpreter to avoid include. Header is added in implementation file.
    class LangInterpreter;

    class LangScanner : public yyFlexLexer
    {
        public:
            LangScanner(LangInterpreter &driver) : m_driver(driver) {}
            LangScanner(LangInterpreter &driver, istream *new_in) : yyFlexLexer(new_in), m_driver(driver) {}
            LangScanner(LangInterpreter &driver, istream *new_in, std::ostream *new_os) : yyFlexLexer(new_in, new_os), m_driver(driver) {}
            virtual ~LangScanner() {}
            virtual mate::LangParser::symbol_type nextToken();
            void echo(const std::string s)
            {
                yyout << s;
            }

          private:
            LangInterpreter &m_driver;
    };

}

#endif