/*
ID: misha2
TASK: zerosum
LANG: C++                 
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int n;
char symbs[3] = {' ', '+', '-'};

using namespace std;

int pow(int b, int p){
    int r = 1;
    for(int i = 1; i <= p; i++){
        r *= b;
    }
    return r;
}

vector<int> interpret(vector<int> c){
    vector<int> r = {1};
    int last = 0;
    for(int i = 0; i < n-1; i++){
        switch(c[i]){
            case 0:
                if(r[last] < 0){
                    r[last] = r[last]*10 - (i+2);
                } else{
                    r[last] = r[last]*10 + (i+2);
                }
                break;
            case 1:
                r.push_back(i+2);
                last++;
                break;
            case 2:
                r.push_back(-i-2);
                last++;
                break;
        }
    }
    return r;
}

int sumV(vector<int> c){
    int s = 0;
    for(int i : c) s+=i;
    return s;
}

bool checkComb(vector<int> c){
    return (sumV(interpret(c)) == 0);
}

void printComb(vector<int> c){
    cout << 1;
    for(int i = 0; i < n-1; i++){
        cout << symbs[c[i]] << i + 2;
    }
    cout << endl;
}

vector<int> nextComb(vector<int> c){
    for(int i = c.size()-1; i >= 0; i--){
        ++c[i] %= 3;
        if(c[i] != 0) break;
    }
    return c;
}

int main() {
    ofstream fout ("zerosum.out");
    ifstream fin ("zerosum.in");

    fin >> n;
    vector<int> comb(n-1);
    int limit = pow(3,n-1);

    // vector<int> c = {1,2,1,0,2,0};
    // for(int i : interpret(c)) cout << i << ' ';

    for(int i = 0; i < limit; i++){
        if(checkComb(comb)){
            fout << 1;
            for(int i = 0; i < n-1; i++){
                fout << symbs[comb[i]] << i + 2;
            }
            fout << endl;
        }
        comb = nextComb(comb);
    }

    return 0;
}