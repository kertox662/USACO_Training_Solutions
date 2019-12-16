/*
ID: misha2
TASK: combo
LANG: C++                 
*/

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

void nextComb(int *comb, int nSet){ //Gives the next combination, if it doesn't overflow into next digit, it stops
    bool next = true;
    for(int i = 0; i < 3; i++){
        if(next){
            (comb[i] %= nSet)++;
            if(comb[i] != 1) next = false;
        } else break;
    }
}

bool isValid(int *comb, int *ref, int n){ //checks if within a range the reference lock
    for(int i = 0; i < 3; i++){
        if(abs(ref[i] - comb[i]) > 2 && abs(max(ref[i], comb[i]) - min(ref[i],comb[i]) - n) > 2) return false;
    }
    return true;
}

void printComb(int *comb){
    for(int i = 0; i < 3; i++){
        cout << comb[i] << ' ';
    }
    cout << endl;
}

int main() {
    ofstream fout ("combo.out");
    ifstream fin ("combo.in");

    int n;
    fin >> n;
    int farm[3], master[3];
    for(int i = 0; i < 3; i++){
        fin >> farm[i];
    }
    for(int i = 0; i < 3; i++){
        fin >> master[i];
    }

    int comb[3] = {1,1,1};

    int s = 0;
    for(int i = 0; i < n*n*n; i++){ //For each combo, (n^3 of them) check validity
        if(isValid(comb, farm, n) || isValid(comb,master,n)) {
            s++;
        nextComb(comb, n); //Get next combo
    }

    fout << s << endl;

    return 0;
}