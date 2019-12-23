/*
ID: misha2
TASK: stamps
LANG: C++                 
*/

#include <iostream>
#include <fstream>
// #include <set>
#include <algorithm>
#define MAX_MAIL 2000001
#define MAX_VAL 50
#define INF 205

using namespace std;

int maxS, numS;
int valS[MAX_VAL];
unsigned char stamps[MAX_MAIL];

void generate(int nPlaced, int val, int last = 0){
    if(nPlaced > maxS) return;
    for(int i = last; i < numS; i++){
        int ind = val + valS[i];
        if(stamps[ind] <= nPlaced) continue;
        stamps[ind] = nPlaced;
        generate(nPlaced + 1, ind, i);
    }
}

bool revSort(int a, int b){
    return (a > b);
}

int main() {
    ofstream fout ("stamps.out");
    ifstream fin ("stamps.in");

    fin >> maxS >> numS;
    for(int i = 0; i < numS; i++) fin >> valS[i];
    fill_n(stamps, MAX_MAIL, INF);
    
    sort(valS, valS + numS, revSort);
    generate(1,0);

    int i;
    for(i = 1; i < MAX_MAIL; i++){
        if(stamps[i] > maxS){
            i--;
            break;
        }
    }

    cout << "OUT" << endl;
    cout << i << endl;
    fout << i << endl;
    return 0;
}