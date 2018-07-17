#ifndef MATE_LOG_HH
#define MATE_LOG_HH

#include <iostream>
#include <string>

namespace mate
{

class Log
{
public:
    ~Log();
    static void e(std::string tag, std::string msg){
        std::cout << "<Error> " << tag << " : " << msg << std::endl;
    }
    static void i(std::string tag, std::string msg){
        std::cout << "<Info> " << tag << " : " << msg << std::endl;
    }
    static void d(std::string tag, std::string msg){
        std::cout << "<Debug> " << tag << " : " << msg << std::endl;
    }
private:
    Log();
};

} // namespace mate

#endif // MATE_LOG_HH
