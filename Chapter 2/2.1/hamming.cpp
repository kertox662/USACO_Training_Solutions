/*
ID: misha2
TASK: hamming
LANG: C++                 
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int hamming(int a, int b){
    int n = 0;
    int x = a^b;
    for(int i = 1; i < 1 << 8; i <<= 1){
        if(x & i) n++;
    }
    return n;
}

vector<int> calcHamming(int a, int N, int B, int D){
    vector<int> n;
    n.push_back(a);
    for(int i = a+1; i < 1 << B && n.size() < N; i++){
        bool valid = true;
        for(int j = 0; j < n.size(); j++){
            if(hamming(i, n[j]) < D){
                valid = false;
                break;
            }
        }
        if(valid) n.push_back(i);
    }
    return n;
}

int main() {
    ofstream fout ("hamming.out");
    ifstream fin ("hamming.in");

    int N,B,D;
    fin >> N >> B >> D;

    vector<int> seq;

    for(int i = 0; i < 1 << (B); i++){
        seq = calcHamming(i, N, B, D);
        if(seq.size() >= N) break;
    }

    for(int i = 0; i < N; i++){
        fout << seq[i];
        if( ( (i+1) %10) && i != N-1) fout << ' ';
        if( !( (i+1)%10 ) && i != N - 1) fout << endl;
    }
    fout << endl;

    return 0;
}