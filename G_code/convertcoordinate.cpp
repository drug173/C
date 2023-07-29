#include "convertcoordinate.h"



extern double maxCoordinate;
extern double minCoordinate;

/// конвертирует  координаты, сдвигает по осям
string ConvertCoordinate(string s, double shift, char coordinate)
{

    string str, str2;
    double digit;
    /// найдена соответсвующая координата
    bool flag2 = false;
    int sizeStr = s.size();

    for(int i = 0; i < sizeStr; i++){

//////////////////////////
        if(s[i] == 'X' || s[i] == 'Y' || s[i] == 'Z'){


        if(s[i] == coordinate){

            flag2 = true;

            str += "Z";
            i++;
            while (i < sizeStr && (isdigit(s[i]) || s[i] == '.' || s[i] == '-' || s[i] == ' ')){
                str2+=(s[i]);
                i++;
            }
            digit = StringToDigit(str2);
            digit = digit + shift -3;         // смещение по Z
            str2 = DigitToString(digit);
            str+=str2;
            str+=" ";
            str2 = "";
            i--;
            continue;
        }
        if (s[i] == 'Z'){
         str += coordinate;
           i++;
           while (i < sizeStr && (isdigit(s[i]) || s[i] == '.' || s[i] == '-' || s[i] == ' ')){
               str2+=(s[i]);
               i++;
           }
           digit = StringToDigit(str2);
           digit = digit + shift +3;         // смещение по coordinate
           str2 = DigitToString(digit);
           str+=str2;
           str+=" ";
           str2 = "";
           i--;
           continue;
        }


        if ( ((s[i] == 'X') || (s[i] == 'Y'))){
         str += s[i];
           i++;
           while (i < sizeStr && (isdigit(s[i]) || s[i] == '.' || s[i] == '-' || s[i] == ' ')){
               str2+=(s[i]);
               i++;
           }
           digit = StringToDigit(str2);
           //digit = digit;         // смещение по coordinate
           str2 = DigitToString(digit);
           str+=str2;
           str+=" ";
           str2 = "";
           i--;
           continue;
        }

    }

           str+=(s[i]);




 //////////////////

/*
        if((flag2 == true) && (isdigit(s[i]) || s[i] == ' '|| s[i] == '.'|| s[i] == '-' )){

            str2+=(s[i]);
        }
        else if (flag2== true){
            digit = StringToDigit(str2);
            digit = digit + shift -3;         // смещение по Z
            str2 = DigitToString(digit);
            str+=str2;
            str+=" ";
            flag2 = false;
        }

        if(flag2 ==true && i == sizeStr - 1){
            digit = StringToDigit(str2);
            digit = digit + shift -3;         // смещение по Z
            str2 = DigitToString(digit);
            str+=str2;
            str2="";
            str+=" ";
            flag2 = false;
        }


        if(s[i] != coordinate && flag2 == false) {
            if( s[i] == 'Z'){
                str += coordinate;
            }else if(!isdigit(s[i])){
                str +=(s[i]);
            }
            else{



            }
        }
        else if(flag2 == false){
            flag2 = true;
            if(s[i] == coordinate){
                str += "Z";
            }
            else{
             str+=(s[i]);
            }
        }


*/
    }

        return str;
}
