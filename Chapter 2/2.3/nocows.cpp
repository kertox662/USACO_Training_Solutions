/*
ID: misha2
TASK: nocows
LANG: C++                 
*/

#include <iostream>
#include <fstream>
#include <map>
#include <cmath>
#define MOD 9901

using namespace std;

int N,K;
map<pair<int,int>, long long> nTree;

int main() {
    ofstream fout ("nocows.out");
    ifstream fin ("nocows.in");

    nTree[{1,1}] = 1;

    fin >> N >> K;
    for(int k = 2; k<=K; k++){
        //for(int n = 2 * k - 1; n < 1 << k && n <= (N - 2 * (K-k)); n+=2){
        for(int n = 1; n <= N; n+=2){
            long long total = 0;
            for(int i = 1; i <= n-i-1; i+=2){
                int c = (i != n-1-i)?2:1;
                total += c*nTree[{i, k-1}] * nTree[{n-i-1,k-2}];
                total += c*nTree[{i, k-2}] * nTree[{n-i-1,k-1}];
                total += c*nTree[{i, k-1}] * nTree[{n-i-1,k-1}];
            }
            nTree[{n,k}] = total%MOD;
            // cout << n << ' ' << k << ' ' << nTree[{n,k}]%MOD << endl;
            
        }
        for(int i = 1; i <= N; i+=2){
            nTree[{i,k-1}] += nTree[{i,k-2}];
            nTree[{i,k-1}] %= MOD;
            // cout << i <<' '<< k <<' '<< nTree[{i,k-1}] << endl;
        }
    }

    fout << nTree[{N,K}] % MOD << endl;

    return 0;
}