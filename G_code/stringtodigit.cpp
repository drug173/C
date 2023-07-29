#include "stringtodigit.h"


///из  строки получает  число
double StringToDigit(string str)
{
    double digit;
    string str2;
   stringstream stringStr1;
   regex reg(R"([-+]?\d*\.?\d+(?:[eE][-+]?\d+)?)");
    for(std::sregex_iterator i = std::sregex_iterator(str.begin(), str.end(), reg);
                            i != std::sregex_iterator();
                            ++i)
   {
       std::smatch m = *i;
       stringStr1 << m.str();
       stringStr1 >> digit;
   }


    return digit;
}
