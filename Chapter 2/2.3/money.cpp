/*
ID: misha2
TASK: money
LANG: C++                 
*/

#include <iostream>
#include <fstream>
#include <array>
#include <algorithm>
#include <map>
#include <set>

#define MAX_COINS 25

using namespace std;


array<int, MAX_COINS> coins;
int N, target;

map<long, long long> ways;
// int ways;

int main() {
    ofstream fout ("money.out");
    ifstream fin ("money.in");

    fin >> N >> target;
    for(int i = 0; i < N; i++){
        fin >> coins[i];
    }
    ways[0] = 1;

    sort(coins.begin(), coins.begin() + N);

    
    for(int i = 0; i < N; i++){
        int coinVal = coins[i];
        for(int j = 0; j+coinVal <= target; j++){
            ways[j + coinVal] += ways[j];
            // cout << j + coinVal << ' ' << ways[j+coinVal] << endl; 
        }
    }

    fout << ways[target] << endl;

    return 0;
}