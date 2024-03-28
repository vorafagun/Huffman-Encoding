#include <iostream>
#include "Huffman.h"
#include "impoExpo.h"
using namespace std;

void Huffman::setCode(string s){
    code = s;
}

string Huffman::getDecCode(){
    return decoded_code;
}

string Huffman::getEncCode(){
    return encoded_code;
}

void Huffman::countFreq(){
    for(int i=0; i<code.size(); i++){
        freqTable[code[i]]++;
    }
}

void Huffman::buildTree(){
    for(auto i: freqTable){
        S_Node* newNode = new S_Node(i.first, i.second);
        minFreqVec.push_back(newNode);
        //sortVec2Min(minFreqVec);
    }
    sortVec2Min(minFreqVec);

    while(minFreqVec.size()!=1){
        S_Node* l = minFreqVec.back();
        minFreqVec.pop_back();
        S_Node* r = minFreqVec.back();
        minFreqVec.pop_back();
        S_Node* newNode = new S_Node;
        newNode->symbol = '*';
        newNode->freq = l->freq + r->freq;
        newNode->left = l;
        newNode->right = r;
        minFreqVec.push_back(newNode);
        sortVec2Min(minFreqVec);
    }
    S_Node* root = minFreqVec.back();
    minFreqVec.pop_back();
    displayLevelOrder(root);
    encode(root,"");
    EncCode();
    decode(root,encoded_code);
}

void Huffman::cbuildTree(){
    for(auto i: freqTable){
        S_Node* newNode = new S_Node(i.first, i.second);
        minFreqVec.push_back(newNode);
        sortVec2Min(minFreqVec);
    }
    while(minFreqVec.size()!=1){
        S_Node* l = minFreqVec.back();
        minFreqVec.pop_back();
        S_Node* r = minFreqVec.back();
        minFreqVec.pop_back();
        S_Node* newNode = new S_Node;
        newNode->symbol = '*';
        newNode->freq = l->freq + r->freq;
        newNode->left = l;
        newNode->right = r;
        minFreqVec.push_back(newNode);
        sortVec2Min(minFreqVec);
    }
    S_Node* root = minFreqVec.back();
    minFreqVec.pop_back();
    encode(root,"");
    EncCode();
    decode(root,encoded_code);
}

void Huffman::encode(S_Node* r, string s){
    if(r== NULL)
        return;
    if (!r->left && !r->right) {
        enBitsTable[r->symbol] = s;
    }
    encode(r->left, s + "0");
    encode(r->right, s + "1");
}

void Huffman::decode(S_Node* r, string s){
    S_Node* curr = r;
    string str = "";
    for(int i=0; i<s.length(); i++){
        if(s[i]=='0')
            curr = curr->left;
        else
            curr = curr->right;
        if(curr->left== NULL && curr->right==NULL){
            str += curr->symbol;
            curr = r;
        }
    }
    decoded_code = str;
}

void Huffman::sortVec2Min(vector<S_Node*> &v){
    for(int i=0; i<v.size()-1; i++){
        for(int j=i+1; j<v.size(); j++){
            if(v[i]->freq < v[j]->freq){
                S_Node* temp = v[i];
                v[i] = v[j];
                v[j] = temp;
            }
        }
    }
}

void Huffman::displayFreq(){
    cout << "Frequency table:" << endl;
    for(auto i: freqTable){
        cout << i.first << "-" << i.second << endl;
    }
    cout << endl;
}

void Huffman::displayEncBits(){
    cout << "Huffman encoded bits:" << endl;
    for(auto i: enBitsTable){
        cout << i.first << "-" << i.second << endl;
    }
}

void Huffman::displayOrgCode(){
    cout << "Original message:" << endl;
    cout << code << endl;
    }

void Huffman::EncCode(){
    string str = "";
    for(int i=0; i<code.size(); i++){
        str += enBitsTable[code[i]];
    }
    encoded_code = str;
}

void Huffman::displayEncCode(){
    cout << "Encoded message:" << endl;
    cout << encoded_code << endl;
    cout << "Size of encoded message: " << encoded_code.length() << endl;
}

void Huffman::displayDecCode(){
    cout << "Decoded message:" << endl;
    cout << decoded_code << endl;
}

void Huffman::displayLevelOrder(S_Node* r){
    if(r == nullptr){
        return;
    }
    queue<S_Node*> q;
    q.push(r);
    q.push(nullptr);
    cout << "Level order of Huffman tree:" << endl;
    while(!q.empty()){
        S_Node* node = q.front();
        q.pop();
        if(node != nullptr){
            cout << node->symbol << "-" << node->freq << " ";
            if(node->right)
                q.push(node->right);
            if(node->left)
                q.push(node->left);
        }
        else if(!q.empty() && node==nullptr){
            q.push(nullptr);
            cout << endl;
        }
    }
    cout << endl;
}

void Huffman::displayCompressRatio(){
    float cr = encoded_code.length()/(float)(code.length()*8);
    cout << "Compressed ratio: "<< cr*100 << "%" << endl;
}
