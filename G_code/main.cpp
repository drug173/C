#include <iostream>
#include "copyfile.h"
#include <fstream>
#include <string>

using namespace std;



int main()
{
    string fileName;
   cout << "Path to file: " << endl;
   cin >> fileName;
   //fileName = "D:\\qqq";
   ActionCopy(fileName);
    cout<< "copying completed - "<< fileName<<endl;
    return 0;
}
