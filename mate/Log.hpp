#ifndef MATE_INTERPRETER_H
#define MATE_INTERPRETER_H

#include <iostream>
#include <string>

namespace mate
{

class Log
{
public:
    ~Log();
    static void e(std::string tag, std::string msg){
        std::cout << "Error: " << tag << " <" << msg <<">" << std::endl;
    }
    static void i(std::string tag, std::string msg){
        std::cout << "Info: " << tag << " <" << msg <<">" << std::endl;
    }
    static void d(std::string tag, std::string msg){
        std::cout << "Debug: " << tag << " <" << msg <<">" << std::endl;
    }
private:
    Log();
};

} // namespace mate

#endif // MATE_INTERPRETER_H
