/*
ID: misha2
TASK: milk
LANG: C++                 
*/

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <array>

using namespace std;

/*STRATEGY:
Greedy algorithm
Sorts milk costs in ascending order (lowest to highest)
Takes from cheaper milk until we have enough.
Calculate the cost along the way
*/

int* getCost(int *a, int *b){
    return (a[0] < b[0])?a:b;
}

int main() {
    ofstream fout ("milk.out");
    ifstream fin ("milk.in");
    int needed, farmers;
    fin >> needed >> farmers;
    array<int, 2> costs[farmers];

    for(int i = 0; i < farmers; i++){
        fin >> costs[i][0] >> costs[i][1];
    }

    sort(costs, costs+farmers);

    int cost = 0;

    for(int i = 0; i < farmers && needed > 0; i++){
        auto farmer = costs[i];
        int bought = min(farmer[1], needed);
        cost += bought * farmer[0];
        needed -= bought;
    }

    fout << cost << endl;

    return 0;
}