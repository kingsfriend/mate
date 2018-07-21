#ifndef JSON_SCANNER_H
    #define JSON_SCANNER_H 

    #if !defined(yyFlexLexerOnce)
        #undef yyFlexLexer
        #define yyFlexLexer Mate_FlexLexer 
        #include <FlexLexer.h>
    #endif

    #undef YY_DECL
    #define YY_DECL mate::JsonParser::symbol_type mate::JsonScanner::nextToken()

#include <cstdio>
#include "JsonParser.hpp"

namespace mate
{

    // Forward declare JsonInterpreter to avoid include. Header is added in implementation file.
    class JsonInterpreter;

    class JsonScanner : public yyFlexLexer
    {
        public:
            JsonScanner(JsonInterpreter &driver) : m_driver(driver) {}
            JsonScanner(JsonInterpreter &driver, istream *new_in) : yyFlexLexer(new_in), m_driver(driver) {}
            JsonScanner(JsonInterpreter &driver, istream *new_in, std::ostream *new_os) : yyFlexLexer(new_in, new_os), m_driver(driver) {}
            virtual ~JsonScanner() {}
            virtual mate::JsonParser::symbol_type nextToken();
            void echo(const std::string s)
            {
                yyout << s;
            }

          private:
            JsonInterpreter &m_driver;
    };

}

#endif