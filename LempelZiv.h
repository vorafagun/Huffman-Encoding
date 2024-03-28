#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <math.h>
using namespace std;

//AABABBBABAABABBBABBABB
class LempelZiv{
    int bitIndex;
    string original_code;
    string encoded_code;
    string decoded_code;
    public:
        LempelZiv();
        void setBitIndex(int x);
        void setOrgCode(string s);
        void setEncCode(string s);
        string getEncCode();
        string getDecCode();
        void displayCodeWord();
        string dec2bin(int decimal, int bitLength);
        int bin2dec(string binary);
        vector<string> encoding();
        vector<string> encode(string s1);
        void decoding();
        void decode(string msg);
        void updateBitIndex(int x);
        void displayCompressRatio();
};


