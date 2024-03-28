#include <iostream>
#include "Huffman.h"
#include "LempelZiv.h"
#include "impoExpo.h"
#include <string>
using namespace std;

int main(){
    ImpoExpoFuncs io;

    cout << "========================== WELCOME TO SOURCE CODING ==========================" << endl;
    cout << "\n\n";
    cout << "[1] RUN DEFAULT DRIVER CODE\n" << endl;
    cout << "[2] RUN CUSTOM DRIVER CODE\n" << endl;

    int ch, ch2, ch3;

    cout << "Your choice: ";
    cin >> ch;
    cout << "\n\n\n";

    switch(ch){

        case 1:
            {
            cout << "//----------------------Huffman coding----------------------//" << endl;
            cout << endl;

            string source_code = io.importTxt("HuffOrgCode.txt");
            Huffman h1;

            cout << "Original Message: " << source_code << endl;
            h1.setCode(source_code);

            cout << "\n\n";

            h1.countFreq();
            h1.displayFreq();
            h1.buildTree();

            cout << endl;

            h1.displayEncBits();
            string s = h1.getEncCode();

            cout << "\n\nCompressing..." << endl;
            cout << "[][][][][][][][][][][][][][][][][][][]...99% done";
            cout << "\n\nEncoded Message: " << s << endl;

            s = h1.getDecCode();

            cout << "\n\nExtracting..." << endl;
            cout << "[][][][][][][][][][][][][][][][][][][]...99% done";
            cout << "\n\nDecoded Message: " << s << endl;

            io.exportTxt(s,"HuffDecMssg.txt");

            cout << "\n\n\n//----------------------Lempel-Ziv Coding----------------------//" << endl;

            LempelZiv l1;
            s = io.importTxt("LzwOrgcode.txt");

            cout << endl;
            cout << "Original Message: " << s;
            cout << endl;

            l1.setOrgCode(s);

            cout << endl;

            l1.encoding();

            cout << endl;

            l1.displayCodeWord();
            s = l1.getEncCode();
            io.exportTxt(s,"LzwEncCode.txt");

            cout << "\n\n\nCompressing..." << endl;
            cout << "[][][][][][][][][][][][][][][][][][][]...99% done";
            cout << "\n\nEncoded Message: " << s;

            s = io.importTxt("LzwEncMsg.txt");
            l1.setEncCode(s);
            l1.decoding();
            s = l1.getDecCode();

            cout << "\n\n\nExtracting..." << endl;
            cout << "[][][][][][][][][][][][][][][][][][][]...99% done";
            cout << "\n\nDecoded Message: " << s << endl;

            io.exportTxt(s, "LzwDecCode.txt");

            cout << "\n\n";
            break;
        }

        case 2:
            {
            cout << "Select compression technique" << endl;
            cout << "1-Huffman Coding" << endl;
            cout << "2-Lempel-Ziv Coding" << endl;
            cout << "Your choice: ";
            cin >> ch2;

            if(ch2==1){
                cout << "\n\n//----------------------Huffman coding----------------------//" << endl;
                cout << "\n\nWhat would you like to do?" << endl;
                cout << "1-Encode" << endl;
                cout << "2-Decode" << endl;
                cout << "Your choice: ";
                cin >> ch3;

                Huffman h2;

                if(ch3 == 1){
                    string filename , filename2;

                    cout << "\n\nEnter name of the file you would like to to encode:" << endl;
                    cin >> filename;

                    string source_code = io.importTxt(filename);

                    h2.setCode(source_code);
                    h2.countFreq();
                    h2.cbuildTree();

                    cout << "\n\nCompressing..." << endl;
                    cout << "[][][][][][][][][][][][][][][][][][][]...99% done" << endl;
                    cout << "\n\nEncoded Successfully\n" << endl;

                    string s = h2.getEncCode();
                    h2.displayCompressRatio();

                    cout << "\nEnter an filename for the encoded message:"<< endl;
                    cin >> filename2;

                    filename2.append(".txt");
                    io.exportTxt(s,filename2);
                }

                else if(ch3 == 2){
                    cout << "\nThis function cannot be accessed due to unavailability of Huffman tree" << endl;
                }

                else
                    cout << "\nInvalid option" << endl;

            }

            else if(ch2==2){
                cout << "\n\n//----------------------Lempel-Ziv Coding----------------------//" << endl;
                cout << "\n\nWhat would you like to do?" << endl;
                cout << "1-Encode" << endl;
                cout << "2-Decode" << endl;
                cout << "Your choice: ";
                cin >> ch3;

                LempelZiv l2;

                if(ch3 == 1){
                    string filename , filename2;

                    cout << "\n\nEnter name of the file you would like to encode:" << endl;
                    cin >> filename;

                    string source_code = io.importTxt(filename);

                    l2.setOrgCode(source_code);
                    l2.encode(source_code);

                    cout << "\n\nCompressing..." << endl;
                    cout << "[][][][][][][][][][][][][][][][][][][]...99% done" << endl;
                    cout << "\n\nEncoded Successfully\n" << endl;

                    string s = l2.getEncCode();
                    l2.displayCompressRatio();

                    cout << "\nEnter an filename for the encoded message:"<< endl;
                    cin >> filename2;

                    filename2.append(".txt");
                    io.exportTxt(s,filename2);
                }

                else if(ch3 == 2){
                    string filename , filename2;
                    int bitIndex;

                    cout << "\n\nEnter the name of file you want to decode:" << endl;
                    cin >> filename;

                    string source_code = io.importTxt(filename);

                    cout << "\nEnter bitindex:" << endl;
                    cin >> bitIndex;

                    l2.setBitIndex(bitIndex);
                    l2.setEncCode(source_code);
                    l2.decode(source_code);

                    cout << "\n\nExtracting..." << endl;
                    cout << "[][][][][][][][][][][][][][][][][][][]...99% done" << endl;
                    cout << "\nDecoded Successfully\n" << endl;

                    string s = l2.getDecCode();

                    cout << "\nEnter the name of file for decoded message:"<< endl;
                    cin >> filename2;

                    filename2.append(".txt");
                    io.exportTxt(s,filename2);


                }

                else
                    cout << "\nInvalid option" << endl;
            }

            else{
                cout << "\nInvalid option" << endl;
            }

            break;
        }

        default:
            cout << "Invalid option" << endl;
    }
}


