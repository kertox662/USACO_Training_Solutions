/*
ID: misha2
TASK: preface
LANG: C++                 
*/

#include <iostream>
#include <fstream>
#include <set>
#include <map>
#include <array>
#include <algorithm>


using namespace std;

char letter[7] {'I', 'V', 'X', 'L', 'C', 'D', 'M'};

map<int, array<int,7> > values
{
        {1, {1,0,0,0,0,0,0}},
        {4, {1,1,0,0,0,0,0}},
        {5, {0,1,0,0,0,0,0}},
        {9, {1,0,1,0,0,0,0}},
        {10,{0,0,1,0,0,0,0}},
        {40,{0,0,1,1,0,0,0}},
        {50,{0,0,0,1,0,0,0}},
        {90,{0,0,1,0,1,0,0}},
        {100,{0,0,0,0,1,0,0}},
        {400,{0,0,0,0,1,1,0}},
        {500,{0,0,0,0,0,1,0}},
        {900,{0,0,0,0,1,0,1}},
        {1000,{0,0,0,0,0,0,1}}
};

set<int> exist {1,4,5,9,10,40,50,90,100,400,500,900,1000};
array<int,13> base {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
int p;

array<int,7> addA(array<int,7> a, array<int,7> b){
    array<int,7> c;
    for(int i = 0; i < 7; i++) c[i] = a[i] + b[i];
    return c;
}

void find(int nS){
    int lowest = 0;
    int n = nS;
    array<int,7> nArray{0,0,0,0,0,0,0};
    while(exist.find(n) == exist.end()){
        for(int i = lowest; i < 13; i++){
            lowest = i;
            if(base[i] > n) continue;
            nArray = addA(nArray, values[base[i]]);
            n -= base[i];
            break;
        }
    }
    nArray = addA(nArray, values[n]);
    if(values.find(nS) == values.end() )
        values[nS] = nArray;
}


int main() {
    ofstream fout ("preface.out");
    ifstream fin ("preface.in");

    fin >> p;

    array<int,7> total{0,0,0,0,0,0,0};

    for(int i = 1; i <= p; i++){
        find(i);
        array<int,7> a = values[i];
        // cout << i << ':';
        // for(int i = 0; i < 7; i++) cout << a[i] << ' ';
        // cout << endl;
        total = addA(total, a);
    }

    for(int i = 0; i < 7; i++){
        if(total[i] != 0){
            fout << letter[i] << ' ' << total[i] << endl;
        }
    }


    return 0;
}