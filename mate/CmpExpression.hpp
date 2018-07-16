#ifndef MATE_CMP_EXPRESSION_HH
    #define MATE_CMP_EXPRESSION_HH
    
    #include "Expression.hpp"
    
    namespace mate
    {
        enum CmpType{
            CMP_OP_EQ,
            CMP_OP_NE,
            CMP_OP_LE,
            CMP_OP_LE_OR_EQ,
            CMP_OP_GR,
            CMP_OP_GR_OR_EQ
        };
        
        class CmpExpression : public Expression
        {
        public:
            ~CmpExpression();
            CmpExpression(CmpType op);

            static const CommandType CMD_TYPE = CMD_CMP;
            static const ExpressionType EXP_TYPE = EXP_CMP;

            virtual JsonBoolNode *executeAsBool()=0;
            JsonNode *execute();

        protected:
          CmpType op;
        };

        class CmpNumExp : public CmpExpression
        {
          private:
            JsonNumberNode *p1;
            JsonNumberNode *p2;

          public:
            ~CmpNumExp();
            CmpNumExp(CmpType op, JsonNumberNode *p1, JsonNumberNode *p2);
            CmpNumExp(CmpType op, double v1, double v2);

            static const CommandType CMD_TYPE = CMD_CMP_NUM;

            JsonBoolNode *executeAsBool();
            void param1(double v1);
            void param2(double v1);
        };

        class CmpBoolExp : public CmpExpression
        {
        private:
          JsonBoolNode *p1;
          JsonBoolNode *p2;

        public:
            ~CmpBoolExp();
            CmpBoolExp(CmpType op, JsonBoolNode *p1, JsonBoolNode *p2);
            CmpBoolExp(CmpType op, bool v1, bool v2);

            static const CommandType CMD_TYPE = CMD_CMP_BOOL;
            
            JsonBoolNode *executeAsBool();
            void param1(bool v1);
            void param2(bool v1);
        };

        class CmpDateExp : public CmpExpression
        {
          private:
            JsonDateNode *p1;
            JsonDateNode *p2;

          public:
            ~CmpDateExp();
            CmpDateExp(CmpType op, JsonDateNode *p1, JsonDateNode *p2);
            CmpDateExp(CmpType op, time_t v1, time_t v2);

            static const CommandType CMD_TYPE = CMD_CMP_DATE;

            JsonBoolNode *executeAsBool();
            void param1(time_t v1);
            void param2(time_t v1);
        };

        class CmpStringExp : public CmpExpression
        {
          private:
            JsonStringNode *p1;
            JsonStringNode *p2;

          public:
            ~CmpStringExp();
            CmpStringExp(CmpType op, JsonStringNode *p1, JsonStringNode *p2);
            CmpStringExp(CmpType op, std::string v1, std::string v2);

            static const CommandType CMD_TYPE = CMD_CMP_STRING;

            JsonBoolNode *executeAsBool();
            void param1(std::string v1);
            void param2(std::string v1);
        };

    } // mate

#endif //MATE_CMP_EXPRESSION_HH
