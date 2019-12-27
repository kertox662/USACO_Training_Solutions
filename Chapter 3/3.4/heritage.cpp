/*
ID: misha2
TASK: heritage
LANG: C++                 
*/

#include <iostream>
#include <fstream>
#include <map>
#include <string>

using namespace std;

struct cow{
    char letter;
    cow *left, *right;
};

map<char, cow> tree;

string inOrder, preOrder;
ofstream fout;

char makeTree(string io, string po){
    if(io == "" || po == "") 
        return '-';
    char root = po[0];
    tree[root] = {root, nullptr, nullptr};
    if(po.size() > 1){
        int rootPos = io.find(root);

        string leftTreeIO = io.substr(0,rootPos);
        string rightTreeIO = io.substr(rootPos+1, io.length() - rootPos -1);
        string leftTreePO = po.substr(1,leftTreeIO.length());
        string rightTreePO = po.substr(1 + leftTreeIO.length(), rightTreeIO.length());

        char leftChild = '-', rightChild = '-';

        if(leftTreeIO.length() > 0){
            leftChild = makeTree(leftTreeIO, leftTreePO);
        }
        if(rightTreeIO.length() > 0){
            rightChild = makeTree(rightTreeIO, rightTreePO);
        }
        
        if(leftChild != '-'){
            tree[root].left = &tree[leftChild];
        }
        if(rightChild != '-'){
            tree[root].right = &tree[rightChild];
        }
    }
    return root;
}

void printPostOrder(char root){
    if(tree[root].left)
        printPostOrder(tree[root].left->letter);
    if(tree[root].right)
        printPostOrder(tree[root].right->letter);
    cout << root;
    fout << root;
}

int main() {
    fout = ofstream("heritage.out");
    ifstream fin ("heritage.in");

    fin >> inOrder >> preOrder;

    char root = makeTree(inOrder, preOrder);
    printPostOrder(root);
    cout << endl;
    fout << endl;

    return 0;
}