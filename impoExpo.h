#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

class ImpoExpoFuncs{
public:
    void exportTxt(string output_text, string file_name);
    string importTxt(string file_name);
};
