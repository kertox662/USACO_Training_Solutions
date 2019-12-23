/*
ID: misha2
TASK: humble
LANG: C++                 
*/

#include <iostream>
#include <fstream>
#include <set>
#include <climits>
#define MAX_PRIMES 100

using namespace std;

int N, humMax, primes[MAX_PRIMES];
set<long long> hum;

int main() {
    ofstream fout ("humble.out");
    ifstream fin ("humble.in");

    fin >> N >> humMax;
    for(int i = 0; i < N; i++){
        fin >> primes[i];
        hum.insert(primes[i]);
    }

    for(long n = 1; n < humMax; n++){
        long long f = *hum.begin();
        for(int i = 0; i < N; i++){
            long long a = f * primes[i];
            if(hum.size() >= humMax - n + 1){
                if(a < *hum.rbegin())
                    hum.insert(a);
            } else {
                hum.insert(a);
            }
        }
        hum.erase(hum.begin());
        while(hum.size() > humMax - n){
            hum.erase(--hum.end());
        }
    }
    long m = *hum.begin();

    // OUTPUT
    cout << "OUT" << endl;
    cout << m << endl;
    fout << m << endl;

    return 0;
}