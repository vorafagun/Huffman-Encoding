#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_map>
#include "S_Node.h"
using namespace std;

class Huffman{
    string code;
    string encoded_code;
    string decoded_code;
    unordered_map<char, int> freqTable;
    unordered_map<char, string> enBitsTable;
    vector<S_Node*> minFreqVec;
public:
    void setCode(string s);
    string getEncCode();
    string getDecCode();
    void countFreq();
    void buildTree();
    void cbuildTree();
    void encode(S_Node* r, string s);
    void decode(S_Node* r, string s);
    void sortVec2Min(vector<S_Node*> &v);
    void displayFreq();
    void displayEncBits();
    void displayOrgCode();
    void EncCode();
    void displayEncCode();
    void displayDecCode();
    void displayLevelOrder(S_Node* r);
    void displayCompressRatio();

};

