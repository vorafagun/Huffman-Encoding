#include <iostream>
#include "LempelZiv.h"
#include "impoExpo.h"
using namespace std;


LempelZiv::LempelZiv(){
    bitIndex = 7;
    original_code = "";
    encoded_code = "";
    decoded_code = "";
}
void LempelZiv::setBitIndex(int x){
    bitIndex= x;
}
void LempelZiv::setOrgCode(string s){
    original_code = s;
}
void LempelZiv::setEncCode(string s){
    encoded_code = s;
}
string LempelZiv::getEncCode(){
    vector<string> output_code = encode(original_code);
    for (int i = 0; i < output_code.size(); i++) {

        encoded_code += output_code[i];
    }
    return encoded_code;
}
string LempelZiv::getDecCode(){
    decode(encoded_code);
    return decoded_code;
}
void LempelZiv::displayCodeWord(){
    cout << "Codewords: ";
    vector<string> output_code = encode(original_code);
    for (int i = 0; i < output_code.size(); i++) {
        cout << bin2dec(output_code[i]) << " ";
    }
}
string LempelZiv::dec2bin(int decimal, int bitLength){
    string binary;
    int r;
    while(decimal>=1){
        r = decimal%2;
        if(r)
            binary.insert(0,"1");
        else
            binary.insert(0,"0");
        decimal /= 2;
    }
    while(binary.size()<bitLength){
        binary.insert(0,"0");
    }
    return binary;
}
int LempelZiv::bin2dec(string binary){
    int decimal = 0;
    for(int i=0; i<binary.length(); i++){
        decimal += (binary[i]-'0')*pow(2,binary.length()-i-1);
    }
    return decimal;
}
vector<string> LempelZiv::encoding(){

    cout << "\nDictionary: " << endl;
    unordered_map<string, int> table;
    for (int i = 0; i <= 127; i++){
        string ch = "";
        ch += char(i);
        table[ch] = i;
    }

    string p = "", c = "";
    p += original_code[0];
    int code = 128;
    vector<string> output_code;
    cout << "String\tOutput_Code\tAddition\n";
    for (int i = 0; i < original_code.length(); i++) {
        if (i != original_code.length() - 1)
            c += original_code[i + 1];
        if (table.find(p + c) != table.end()) {
            p = p + c;
        }
        else {
            cout << p << "\t" << table[p] << "\t\t"
                 << p + c << "\t" << code << endl;
            output_code.push_back(dec2bin(table[p],8));
            table[p + c] = code;
            code++;
            updateBitIndex(code);
            p = c;
        }
        c = "";
    }
    cout << p << "\t" << table[p] << endl;
    output_code.push_back(dec2bin(table[p],8));
    return output_code;
}
vector<string> LempelZiv::encode(string s1){
    unordered_map<string, int> table;
    for (int i = 0; i <= 127; i++){
        string ch = "";
        ch += char(i);
        table[ch] = i;
    }

    string p = "", c = "";
    p += s1[0];
    int code = 128;
    vector<string> output_code;
    for (int i = 0; i < s1.length(); i++) {
        if (i != s1.length() - 1)
            c += s1[i + 1];
        if (table.find(p + c) != table.end()) {
            p = p + c;
        }
        else {
            output_code.push_back(dec2bin(table[p],8));
            table[p + c] = code;
            code++;
            updateBitIndex(code);
            p = c;
        }
        c = "";
    }
    output_code.push_back(dec2bin(table[p],8));
    return output_code;
}
void LempelZiv::decoding(){

    vector<string> op;
    string sub="";
    for(int i=0; i<=encoded_code.length(); i++){
        if(i%bitIndex==0 && i!=0) {

            op.push_back(sub);
            sub = "";
        }
        sub += encoded_code[i];
    }
    unordered_map<int, string> table1;
    for (int i = 0; i <= 127; i++) {
        string ch = "";
        ch += char(i);
        table1[i] = ch;
    }
    int old = bin2dec(op[0]), n;
    string s = table1[old];
    string c = "";
    c += s[0];

    decoded_code.append(s);
    int count = 128;
    for (int i = 0; i < op.size() - 1; i++) {
        n = bin2dec(op[i + 1]);
        if (table1.find(n) == table1.end()) {
            s = table1[old];
            s = s + c;
        }
        else {
            s = table1[n];
        }

        decoded_code.append(s);
        c = "";
        c += s[0];
        table1[count] = table1[old] + c;
        count++;
        old = n;
    }
}
void LempelZiv::decode(string msg){
    decoded_code = "";
    vector<string> op;
    string sub="";
    for(int i=0; i<=msg.length(); i++){
        if(i%bitIndex==0 && i!=0) {

            op.push_back(sub);
            sub = "";
        }
        sub += msg[i];
    }
    unordered_map<int, string> table1;
    for (int i = 0; i <= 127; i++) {
        string ch = "";
        ch += char(i);
        table1[i] = ch;
    }
    int old = bin2dec(op[0]), n;
    string s = table1[old];
    string c = "";
    c += s[0];

    decoded_code.append(s);
    int count = 128;
    for (int i = 0; i < op.size() - 1; i++) {
        n = bin2dec(op[i + 1]);
        if (table1.find(n) == table1.end()) {
            s = table1[old];
            s = s + c;
        }
        else {
            s = table1[n];
        }
        decoded_code.append(s);
        c = "";
        c += s[0];
        table1[count] = table1[old] + c;
        count++;
        old = n;
    }
}
void LempelZiv::updateBitIndex(int x){
    bitIndex = log2(x)+1;
}

void LempelZiv::displayCompressRatio(){
    float cr = encoded_code.length()/(float)(original_code.length()*8);
    cout << "Compressed ratio: "<< cr*100 << "%" << endl;
}
