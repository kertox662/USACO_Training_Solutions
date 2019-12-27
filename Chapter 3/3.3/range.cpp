/*
ID: misha2
TASK: range
LANG: C++                 
*/

#include <iostream>
#include <fstream>
#include <map>
#define MAX_SIDE 250

using namespace std;

int side;
int field[MAX_SIDE][MAX_SIDE];
map<int,int> sizes;

int main() {
    ofstream fout ("range.out");
    ifstream fin ("range.in");
    fin >> side;
    for(int i = 0; i < side; i++){
        for(int j = 0; j < side; j++){
            char c;
            fin >> c;
            if(c == '0')
                field[i][j] = 0;
            else
                field[i][j] = 1;
        }
    }

    for(int s = 2; s <= side; s++){
        bool lastRowValid = false;
        for(int r = 0; r <= side-s; r++){
            bool rowValid = true;
            bool lastColValid = false;
            if(!lastRowValid){
                for(int c = 0; c <= side-s; c++){
                    bool valid = true;
                    // cout << r << ',' << c << endl;
                    if(!lastColValid){
                        for(int i = 0; i < s && valid; i++){
                            for(int j = 0; j < s && valid; j++){
                                if(!field[r+i][c+j]){
                                    valid = false;
                                    rowValid = false;
                                }
                            }
                        }
                        
                    }
                    else{
                        for(int i = 0; i < s && valid; i++){
                            if(!field[r+i][c + s - 1]){
                                valid = false;
                                rowValid = false;
                            }
                        }
                    }
                    if(valid) sizes[s]++;
                    lastColValid = valid;
                }
            }
            else{
                for(int c = 0; c <= side-s; c++){
                    bool valid = true;
                    // cout << r << ',' << c << endl;
                    if(!lastColValid){
                        for(int j = 0; j < s && valid; j++){
                            if(!field[r+s-1][c+j]){
                                valid = false;
                                rowValid = false;
                            }
                        }
                    }
                    else{
                        if(!field[r + s - 1][c + s - 1]){
                            valid = false;
                            rowValid = false;
                        }
                    }
                    if(valid) sizes[s]++;
                    lastColValid = valid;
                }
            }
            lastRowValid = rowValid;
        }
    }

    for(int i = 2; i <= side; i++){
        if(sizes[i] == 0) break;
        // cout << i << ' ' << sizes[i] << endl;
        fout << i << ' ' << sizes[i] << endl;
    }

    return 0;
}