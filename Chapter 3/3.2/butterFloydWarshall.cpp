/*
ID: misha2
TASK: butter
LANG: C++                 
*/

#include <iostream>
#include <fstream>
#define MAX_PAST 801
#define MAX_COW 500
#define INF 10000000

int past[MAX_PAST][MAX_PAST], nPast, nPath;
int cows[MAX_COW], nCow;

using namespace std;

int main() {
    ofstream fout ("butter.out");
    ifstream fin ("butter.in");

    fin >> nCow >> nPast >> nPath;
    for(int i = 0; i < nCow; i++){
        fin >> cows[i];
    }
    for(int i = 1; i <= nPast; i++){
        for(int j = 1; j<= nPast;j++){
            if(i == j) past[i][i] = 0;
            else past[i][j] = INF;
        }
    }

    for(int i = 0; i < nPath; i++){
        int a,b, cost;
        fin >> a >> b >> cost;
        past[a][b] = cost;
        past[b][a] = cost;
    }

    for(int mid = 1; mid <= nPast; mid++){
        for(int i = 1; i <= nPast; i++){
            for(int j = i+1; j <= nPast; j++){
                if(i==j)continue;
                if(past[i][mid] + past[mid][j] < past[i][j]){
                    past[i][j] = past[i][mid] + past[mid][j];
                    past[j][i] = past[i][mid] + past[mid][j];
                }
                
            }
        }
    }

    int minDist = (1 << 30);
    for(int i = 1; i <= nPast; i++){
        int curDist = 0;
        for(int c = 0; c < nCow; c++){
            curDist += past[i][cows[c]];
        }
        if(curDist < minDist) minDist = curDist;
    }

    //OUT//
    cout << minDist << endl;
    fout << minDist << endl;

    return 0;
}