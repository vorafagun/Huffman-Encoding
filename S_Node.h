#ifndef FINAL_PROJECT_S_NODE_H
#define FINAL_PROJECT_S_NODE_H

struct S_Node{
    char symbol;
    int freq;
    S_Node* left;
    S_Node* right;
    S_Node(){
        left = nullptr;
        right = nullptr;
    }
    S_Node(char s, int f){
        symbol = s;
        freq = f;
        left = nullptr;
        right = nullptr;
    }
};

#endif
