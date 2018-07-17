#ifndef MATE_ERROR_HH
#define MATE_ERROR_HH

#include <iostream>
#include <string>

namespace mate
{

class Error
{
public:
    ~Error();
    static void e(std::string tag, std::string msg){
        std::cout << "<> " << tag << " : " << msg << std::endl;
    }
    static void i(std::string tag, std::string msg){
        std::cout << "<Info> " << tag << " : " << msg << std::endl;
    }
    static void d(std::string tag, std::string msg){
        std::cout << "<Debug> " << tag << " : " << msg << std::endl;
    }
private:
    Error();
};

} // namespace mate

#endif // MATE_ERROR_HH
