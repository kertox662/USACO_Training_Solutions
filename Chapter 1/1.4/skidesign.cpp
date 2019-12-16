/*
ID: misha2
TASK: skidesign
LANG: C++                 
*/

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

/*STRATEGY:
Iterate over all possible intervals that could have the accepatable difference
See which one yields the lowest cost
*/

int main() {
    ofstream fout ("skidesign.out");
    ifstream fin ("skidesign.in");

    int nHill;
    fin >> nHill;
    int hills[nHill];
    for(int i = 0; i < nHill; i++){
        fin >> hills[i];
    }

    sort(hills, hills + nHill);

    int minC = (1 << 30);
    for(int h = hills[0]; h <= hills[nHill - 1] - 17; h++){
        int c = 0;
        for(int i = 0; i < nHill; i++){
            int dif = hills[i] - h;
            if(dif > 0){
                dif -= 17;
            } else dif = abs(dif);

            if(dif <= 0) continue;

            dif *= dif;
            c += dif;
        }
        minC = min(c, minC);
    }

    cout << minC << endl;
    fout << minC << endl;

    return 0;
}