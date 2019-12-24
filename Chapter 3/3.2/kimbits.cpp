/*
ID: misha2
TASK: kimbits
LANG: C++                 
*/

#include <iostream>
#include <fstream>
#include <string>
#define MAXBITS 32

using namespace std;

long long diff[MAXBITS][MAXBITS*2];

int main() {
    ofstream fout ("kimbits.out");
    ifstream fin ("kimbits.in");
    int bits, maxActive;
    unsigned int I;
    fin >> bits >> maxActive >> I;


    for(int i = 0; i < MAXBITS*2; i++){
        diff[0][i] = i+1;
    }
    for(int j = 1; j < maxActive + 1; j++){
        diff[j][0] = 1;
        for(int i = 1; i < bits; i++){
            diff[j][i] = diff[j][i-1] + diff[j-1][i-1];
        }
    }
    //PRINT DIFFERENCE TABLE
    // for(int i = 0; i < maxActive + 1; i++){
    //     for(int j = 0; j < bits; j++) cout << diff[i][j] << ' ';
    //     cout << endl;
    // }

    bits--;
    maxActive--;
    I--;

    string s = "";
    while(bits >= 0){
        if(maxActive >= 0 && diff[maxActive][bits] <= I){
            s += "1";
            I -= diff[maxActive][bits];
            maxActive--;
        } else{
            s+="0";
        }
        bits--;
    }

    fout << s << endl;

    return 0;
}