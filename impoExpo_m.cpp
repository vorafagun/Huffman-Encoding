#include <iostream>
#include "Huffman.h"
#include "impoExpo.h"
using namespace std;

void ImpoExpoFuncs::exportTxt(string output_text, string file_name){
        ofstream myfile (file_name);
        if (myfile.is_open()){
            for(int i = 0; i < output_text.size(); i ++){
                myfile << output_text[i];
            }
            myfile.close();
        }
        else
            cout << "Unable to open file" << endl;
    }

string ImpoExpoFuncs::importTxt(string file_name){
        ifstream file (file_name);
        if(file.is_open()){

            string input_text = "",line;
            while(getline(file,line)){
                input_text.append(line);
            }
            file.close();
            return input_text;
        }
        else
            cout << "Unable to open file" << endl;
        return "Error!";
}
