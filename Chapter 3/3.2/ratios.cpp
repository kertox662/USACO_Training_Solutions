/*
ID: misha2
TASK: ratios
LANG: C++                 
*/

#include <iostream>
#include <fstream>
#include <array>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;

array<array<int,3>, 3> feeds;
array<int, 3> goal;

int checkMethod = 0;

bool isValid(array<int,3> coeff){
    array<int, 3> curState = {coeff[0] * feeds[0][0] + coeff[1] * feeds[1][0] + coeff[2] * feeds[2][0],
                              coeff[0] * feeds[0][1] + coeff[1] * feeds[1][1] + coeff[2] * feeds[2][1],
                              coeff[0] * feeds[0][2] + coeff[1] * feeds[1][2] + coeff[2] * feeds[2][2]
                             };
        
    int mult = curState[checkMethod] / goal[checkMethod];
    bool valid = true;
    for(int i = 0; i < 3; i++){
        if(mult * goal[i] != curState[i]){
            valid = false;
            break;
        }
    }
    return valid;
}

bool sumCompare(array<int,3> a, array<int,3> b){
    int sumA = a[0] + a[1] + a[2];
    int sumB = b[0] + b[1] + b[2];
    return sumA < sumB;
}

int main() {
    ofstream fout ("ratios.out");
    ifstream fin ("ratios.in");
    
    fin >> goal[0] >> goal[1] >> goal[2];
    for(int i = 0; i < 3; i++){
        fin >> feeds[i][0] >> feeds[i][1] >> feeds[i][2];
    }

    if(goal == array<int,3>{0,0,0}){
        fout << 0 << ' ' << 0 << ' ' << 0 << ' ' << 0 << endl;
        return 0;
    }

    int checkMethod = 0;
    if(goal[0] != 0) checkMethod = 0;
    else if(goal[1] != 0) checkMethod = 1;
    else checkMethod = 2;

    set<array<int,3> > valid;

    for(int i = 0; i <= 99; i++){
        for(int j = 0; j <= 99; j++){
            for(int k = 0; k <= 99; k++){
                if(i == 0 && j == 0 && k == 0) continue;
                if(isValid({i,j,k})){
                    valid.insert({i,j,k});
                }
            }
        }
    }

    vector<array<int,3> > validV(valid.begin(), valid.end());
    if(validV.size() == 0){
        cout << "NONE" << endl;
        fout << "NONE" << endl;
        return 0;
    }
    sort(validV.begin(), validV.end(), sumCompare);

    array<int, 3> valState = {validV[0][0] * feeds[0][0] + validV[0][1] * feeds[1][0] + validV[0][2] * feeds[2][0],
                              validV[0][0] * feeds[0][1] + validV[0][1] * feeds[1][1] + validV[0][2] * feeds[2][1],
                              validV[0][0] * feeds[0][2] + validV[0][1] * feeds[1][2] + validV[0][2] * feeds[2][2]
                             };
    int mult = valState[checkMethod] / goal[checkMethod];

    //OUT//
    for(int i : validV[0]){
        cout << i << ' ';
        fout << i << ' ';
    }
    cout << mult << endl;
    fout << mult << endl;

    return 0;
}