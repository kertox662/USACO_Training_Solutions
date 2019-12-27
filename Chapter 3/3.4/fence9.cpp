/*
ID: misha2
TASK: fence9
LANG: C++                 
*/

#include <iostream>
#include <fstream>
#include <cmath>
#define MAXCOORDS 32001
#define INF 200000

using namespace std;

int n,m,p;
const double tolerance = 0.0000001;

int gcd(int a, int b){
    if(a == 0 || b == 0) return 0;
    if(a%b == 0) return b;
    return gcd(b, a%b);
}

int main() {
    ofstream fout ("fence9.out");
    ifstream fin ("fence9.in");
    fin >> n >> m >> p;

    int gcd1 = gcd(m,n), gcd2 = gcd(m, abs(p-n));

    pair<int,int> slope1,slope2;
    double bVal = 0;

    if(gcd1 == 0)
        slope1 = {INF,1};
    else
        slope1 = {m/gcd1, n/gcd1};
    
    if(gcd2 == 0) slope2 = {-INF,1};
    else{
        slope2 = {m/gcd2, abs(p-n)/gcd2};
        if(p > n) slope2.first = -slope2.first;
    }
    if(slope2 != pair<int,int>{INF,1}){
        bVal = -(double)slope2.first / slope2.second * p;
    }

    int lattice = 0;

    for(int i = 1; i < m; i++){
        double leftBound = (double)slope1.second / slope1.first * i;
        double rightBound = ((double)i - bVal) / ((double)slope2.first) * slope2.second;
        int leftBoundInt = ceil(leftBound);
        if(leftBoundInt == (int)leftBound) leftBoundInt++;
        int rightBoundInt = floor(rightBound);
        if(rightBound - rightBoundInt < tolerance) rightBoundInt--;
        for(int x = leftBoundInt; x <= rightBoundInt; x++){
            lattice++;
        }
    }

    cout << lattice << endl;
    fout << lattice << endl;

    return 0;
}