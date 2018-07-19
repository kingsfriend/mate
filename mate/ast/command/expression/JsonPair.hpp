#ifndef MATE_PAIR_HH
#define MATE_PAIR_HH
    #include <string>
    #include "Expression.hpp"
namespace mate
{
    class JsonPair{
    public:
        std::string key;
        Expression *value;
        JsonPair(){
            value = NULL;
        }
        JsonPair(std::string key ,Expression *value ): key(key), value(value){}
    };

} // namespace mate

#endif //MATE_PAIR_HH
