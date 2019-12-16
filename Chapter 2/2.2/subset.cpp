/*
ID: misha2
TASK: subset
LANG: C++                 
*/

#include <iostream>
#include <fstream>
#include <set>
#include <vector>

using namespace std;

set<vector<int> > seqs;

void solve(int MAX, int cur, int curSum, int *out){
    if(cur > MAX){//BASE CASE
        if(curSum*2 == (MAX)*(MAX+1)/2){ //If the sums are the same (MAX choose 2)
            (*out)++; 
        }
    }
    else{
        if(curSum*2 > (MAX)*(MAX+1)/2) return;
        else{
            solve(MAX, cur+1, curSum + cur, out); //Included in first set
            solve(MAX, cur+1, curSum, out); //Not Included in first set
        }
    }
}

int main() {
    ofstream fout ("subset.out");
    ifstream fin ("subset.in");

    int n;
    fin >> n;

    int s = 0;
    solve(n, 1, 0, &s);

    fout << s/2 << endl;

    return 0;
}