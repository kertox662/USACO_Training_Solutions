/*
ID: misha2
TASK: stamps
LANG: C++                 
*/

#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>
#define MAX_MAIL 2000001
#define MAX_VAL 50
#define INF 205

using namespace std;

int maxOnEnvelope, numTypes;
int valS[MAX_VAL], stamps[MAX_MAIL + 10000];

int main() {
    ofstream fout ("stamps.out");
    ifstream fin ("stamps.in");

    fin >> maxOnEnvelope >> numTypes;
    for(int i = 0; i < numTypes; i++) fin >> valS[i];
    
    fill_n(stamps, MAX_MAIL+10000, INF);

    for(int i = 0; i < numTypes; i++){
        stamps[valS[i]] = 1;
    }
    int i;
    for(i = 1; i < MAX_MAIL; i++){
        int numWays = stamps[i];
        if(numWays > maxOnEnvelope) break;
        for(int j = 0; j < numTypes; j++){
            int next = i + valS[j];
            stamps[next] = min(stamps[next], numWays+1);
        }
    }
    i--;

    cout << "OUT" << endl;
    cout << i << endl;
    fout << i << endl;
    return 0;
}