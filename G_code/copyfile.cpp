#include "copyfile.h"

extern bool flag;
extern double maxCoordinate;
extern double minCoordinate;


///Копирует файл с добавлением в конец исходного файла
void ActionCopy(string nameFile){

    flag = false;
    string nameFile2 = "E:\\testXYZ.txt";
    cout << nameFile2 << endl;
    string strLine;
    string line;
    double minX, maxX, minY, maxY;
    ofstream out2;          // поток для записи
    out2.open(nameFile2); // окрываем файл для записи c начала
    ofstream out3;          // поток для дозаписизаписи
    out3.open(nameFile2, std::ios::app); // окрываем файл для дозаписи
    ifstream in;       // поток для чтения
    in.open(nameFile); // окрываем файл для чтения

    in.clear();
    in.seekg(0L);

    //regex re("-?[0-9]+[.]*[0-9]*");
    regex rY(R"([Y][-+]?\d*\.?\d+(?:[eE][-+]?\d+)?)");
    regex rX(R"([X][-+]?\d*\.?\d+(?:[eE][-+]?\d+)?)");
    regex re1("(M05|M02)");// вывод файла без изменений
    regex re2("(%|M05|M02)"); // вывод  плоскость YZ
    regex re3("(^%)"); // вывод  плоскость XZ
// копируем  исходный файл в новый файл  "C://testХYZ.txt"
    if (in.is_open())
       {
           while (getline(in, line))
           {
              if(regex_match(line, re1)){
                   break;
              }
                out2 << line << endl;

           }
     }

    out2.close();            // закрываем файл
    in.clear();
    in.seekg(0L);

     //ищем  максимальное  и  минимальное значения  соответствующей координаты  X
    if (in.is_open())
       {

           while (getline(in, line))
           {
               ParsingStr(line,rX);
           }
           minX = minCoordinate;
           maxX = maxCoordinate;
           /// смещение по Х
           maxX= (maxCoordinate - minCoordinate) / 2;
           flag = false;
     }
    else{
        perror("Error occured while opening file");
    }
        in.clear();
        in.seekg(0L);

        //ищем  максимальное  и  минимальное значения  соответствующей координаты  Y
       if (in.is_open())
          {

              while (getline(in, line))
              {
                  ParsingStr(line,rY);
              }
              minY = minCoordinate;
              maxY = maxCoordinate;
              /// смещение по Y
              maxY= (maxCoordinate - minCoordinate) / 2;
              flag = false;
        }
       else{
           perror("Error occured while opening file");
       }
           in.clear();
           in.seekg(0L);

// преобразуем в плоскость YZ
    if (in.is_open())
       {
           while (getline(in, line))
           {

               if(regex_match(line, re2)){
                   continue;
               }
                //  преобразуем координату  в число и сдвигаем координату

              strLine = ConvertCoordinate(line, maxX, 'X');

              out3 <<  strLine << endl;
           }
     }

    in.clear();
    in.seekg(0L);
    out3.close();
    out3.open(nameFile2, std::ios::app);

// Преобразуем в плоскость  XZ
if (in.is_open())
{
    while (getline(in, line))
    {
        if(regex_match(line, re3)){
            continue;
        }
        //  преобразуем координату  в число и сдвигаем координату

      strLine = ConvertCoordinate(line, maxY, 'Y');

         out3 <<  strLine << endl;
    }
}

out3 << "%";
    in.close();             // закрываем файл
    out3.close();            // закрываем файл

};



