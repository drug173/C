#include "digittostring.h"

string DigitToString(double  digit)
{
    stringstream stringStr1;
    string str;
    stringStr1 << digit;
    stringStr1 >> str;
    return  str;
}
