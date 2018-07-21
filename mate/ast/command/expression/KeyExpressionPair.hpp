#ifndef MATE_KEY_EXPRESSION_PAIR_HH
#define MATE_KEY_EXPRESSION_PAIR_HH
    #include <string>
    #include "Expression.hpp"
namespace mate
{
    class KeyExpressionPair{
    public:
        std::string key;
        Expression *value;
        KeyExpressionPair(){
            value = NULL;
        }
        KeyExpressionPair(std::string key ,Expression *value ): key(key), value(value){}
    };

} // namespace mate

#endif //MATE_KEY_EXPRESSION_PAIR_HH
