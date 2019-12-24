/*
ID: misha2
TASK: fact4
LANG: C++                 
*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    ofstream fout ("fact4.out");
    ifstream fin ("fact4.in");

    int n;
    fin >> n;

    int f = 1;
    for(int i = 2; i <= n; i++){
        if(i%10 == 0) 
            f *= (i/10);
        else
            f *= i;
        while(f % 10 == 0) f /= 10;
        f %= 1000;
    }
    fout << f%10 << endl;

    return 0;
}