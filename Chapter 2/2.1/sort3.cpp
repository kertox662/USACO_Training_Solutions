/*
ID: misha2
TASK: sort3
LANG: C++                 
*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void swap(int n[], int a, int b){
    int temp = n[a];
    n[a] = n[b];
    n[b] = temp;
}

int main() {
    ofstream fout ("sort3.out");
    ifstream fin ("sort3.in");

    int n;
    fin >> n;
    int nums[n];
    for(int i = 0; i < n; i++){
        fin >> nums[i];
    }


    int amounts[3] = {0,0,0};
    for(int i = 0; i < n; i++){
        amounts[nums[i] - 1]++;
    }

    // cout << "HERE5" << endl;

    // cout << amounts[0] << endl;
    // cout << amounts[1] << endl;
    // cout << amounts[2] << endl;
    
    int first[ amounts[0] ], second[ amounts[1] ], third[ amounts[2] ];
    int i = 0;
    
    // cout << "HERE1" << endl;
    for(;i<amounts[0]; i++){
        first[i] = nums[i];
    }

    for(;i<amounts[0] + amounts[1];i++){
        second[i - amounts[0]] = nums[i];
    }


    for(;i<amounts[0] + amounts[1] + amounts[2] ;i++){
        third[i - amounts[0] - amounts[1]] = nums[i];
    }

    int nSwap = 0;

    for(i = 0; i < amounts[0]; i++){
        if(first[i] != 1){

            if(first[i] == 2){
                for(int j = 0; j < amounts[1]; j++){
                    if(second[j] == 1){
                        first[i] = 1;
                        second[j] = 2;
                        nSwap++;
                        break;
                    }
                }
            }

            else{
                for(int j = 0; j < amounts[2]; j++){
                    if(third[j] == 1){
                        first[i] = 1;
                        third[j] = 3;
                        nSwap++;
                        break;
                    }
                }
            }
        }
    }

    for(i = 0; i < amounts[1]; i++){
        if(second[i] != 2){
            if(second[i] == 3){
                for(int j = 0; j < amounts[2]; j++){
                    if(third[j] == 2){
                        second[i] = 2;
                        third[j] = 3;
                        nSwap++;
                        break;
                    }
                }
            }
        }
    }

    int numDif = 0;
    for(int i = 0; i < amounts[0]; i++){
        if(first[i] != 1) numDif++;
    }

    fout << (nSwap + (numDif*2)) << endl;


    // for(int i : first) cout << i << ' ';
    // cout << endl;
    // for(int i : second) cout << i << ' ';
    // cout << endl;
    // for(int i : third) cout << i << ' ';
    // cout << endl;
}