/*
ID: misha2
TASK: inflate
LANG: C++                 
*/

#include <iostream>
#include <fstream>
#include <map>
#include <cmath>
#include <algorithm>
#define MAX_CAT 10000

using namespace std;

map<int,int> maxP;
pair<int,int> categories[MAX_CAT];
int timeLimit,M;

bool sortCat(pair<int,int> a, pair<int,int> b){
    double dA = ((double)a.first) / a.second;
    double dB = ((double)b.first) / b.second;
    return (dA > dB);
}

int main() {
    ofstream fout ("inflate.out");
    ifstream fin ("inflate.in");
    fin >> timeLimit >> M;
    for(int i = 0; i < M; i++){
        int p,m;
        fin >> p >> m;
        categories[i] = {p,m};
    }

    sort(categories, categories + M, sortCat);

    for(int i = 1; i <= timeLimit; i++){
        int maxPoints = 0;
        for(int j = 0; j < M; j++){
            int points = 0;
            pair<int,int> p = categories[j];
            if(p.second <= i){
                points += p.first;
                int timeLeft = i - p.second;
                points += maxP[timeLeft];
            }
            if(points >= maxPoints){
                maxPoints = points;
            } else break;
            // maxPoints = max(points, maxPoints);
        }
        maxP[i] = maxPoints;
    }

    fout << maxP[timeLimit] << endl;
    
    return 0;
}