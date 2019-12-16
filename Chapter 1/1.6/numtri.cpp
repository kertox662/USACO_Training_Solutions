/*
ID: misha2
TASK: numtri
LANG: C++                 
*/

#include <iostream>
#include <cmath>
#include <fstream>

int tSum(int x){
    if(x > 1)
        return x + tSum(x - 1);
    return x;
}

using namespace std;
/*STRATEGY:
Bottom up approach (Dynamic)
Calculate the 2nd row from the bottom, since we know that those are constant
Calculate each row above that going from the bottom
*/

int main(){
    ofstream fout ("numtri.out");
    ifstream fin ("numtri.in");
    int layers;
    fin >> layers;
    int tSums[layers];
    int t = tSum(layers);
    int triangle[t], sums[t];
    for(int i = 0; i <= layers; i++){
        tSums[i] = tSum(i);
    }

    for(int i = 0; i < layers; i++){
        for(int j = 0; j < i+1; j++){
            fin >> triangle[tSum(i) + j];
        }
    }

    for(int i = layers - 1; i >= 0; i--){
        for(int j = 0; j <= i; j++){
            if(i == layers - 1) sums[tSums[i] + j] = triangle[tSums[i] + j];
            else{
                sums[tSums[i] + j] = triangle[tSums[i] + j] + std::max(sums[tSums[i + 1] + j], sums[tSums[i + 1] + j + 1]);
            }

        }
    }
    fout << sums[0] << std::endl;
    return 0;
}
