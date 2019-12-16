/*
ID: misha2
TASK: crypt1
LANG: C++                 
*/

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

int find(int *a, int size, int n){
    for(int i = 0; i < size; i++){
        if (a[i] == n) return i;
    }
    return -1;
}

bool validChars(string s, int *set, int size){
    if (s[0] == '0') return false;
    for(char c:s){
        if(find(set, size, c - 48) == -1) 
            return false;
    }
    return true;
}

bool isValid(int *set, int *comb, int size){
    int top = set[comb[0]] + set[comb[1]] * 10 + set[comb[2]] * 100;
    int p1 = top * set[comb[3]];
    int p2 = top * set[comb[4]];
    if(p1 >= 1000 || p2 >= 1000) return false;
    int p3 = p1 + p2 * 10;

    if( validChars(to_string(p1),set,size) && validChars(to_string(p2),set,size) && validChars(to_string(p3),set,size))
        return true;

    return false;
}


void nextComb(int *comb, int nSet){
    bool next = true;
    for(int i = 0; i < 5; i++){
        if(next){
            ++comb[i] %= nSet;
            if(comb[i] != 0) next = false;
        } else break;
    }
}

void printComb(int *set, int *comb){
    for(int i = 0; i < 5; i++){
        cout << set[comb[i]] << ' ';
    }
    cout << endl;
}


int main() {
    ofstream fout ("crypt1.out");
    ifstream fin ("crypt1.in");

    int n;
    fin >> n;
    int set[n];
    for(int i = 0; i < n; i++){
        fin >> set[i];
    }
    sort(set, set+n);

    int comb[5] = {0,0,0,0,0};
    int s = 0;
    for(int i = 0; i < n*n*n*n*n; i++){//For each combo, get next combo and check validity
        nextComb(comb, n);
        if(isValid(set, comb, n)) {
            s++;
        };
    }

    fout << s << endl;
    // cout << s << endl;

    return 0;
}