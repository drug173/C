#include "parsingdigit.h"



/// из строки получает  вектор с координатами
vector<string> ParsingDigit(string str, regex reg)
{
    vector<string> vec;

    for(std::sregex_iterator i = std::sregex_iterator(str.begin(), str.end(), reg);
                            i != std::sregex_iterator();
                            ++i)
   {
       std::smatch m = *i;
       vec.push_back(m.str());
   }

    return vec;
}
