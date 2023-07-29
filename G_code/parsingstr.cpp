#include "parsingstr.h"

extern double maxCoordinate;
extern double minCoordinate;
extern bool flag;

///Получает числа из строки  по заданной координате (ищем мин макс)
void ParsingStr(string s, regex reg){


    /// вектор символов представляющих числа
    //vector<char> buff;
    /// вектор  чисел в строке
    vector<string> digitStr;
   // string b;
    //stringstream stringStr1;
    double d;
    vector<double> digit;

    digitStr = ParsingDigit(s,reg);
    if (digitStr.empty()){
        return;
    }
     for (string in : digitStr){
        d = StringToDigit(in);
         digit.push_back(d);
     }


     if(!digit.empty()){
       int sizeDigit= digit.size();



       //ищем максимальное и минимальное значение координат
         max1(digit,sizeDigit);
     }


}



//ищет максимальное и минимальное числа из массива
void max1 ( vector<double> valMas,int N){

    if(flag==false){
        maxCoordinate = valMas[0];
        minCoordinate = valMas[0];
        flag=true;
    }
    for(int i = 0; i < N; i++){
        if( valMas[i] > maxCoordinate){
            maxCoordinate = valMas[i];
        }
        if( valMas[i] < minCoordinate){
            minCoordinate = valMas[i];
        }
    }


}

