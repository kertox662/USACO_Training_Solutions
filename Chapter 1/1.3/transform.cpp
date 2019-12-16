/*
ID: misha2
TASK: transform
LANG: C++                 
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

bool compare(vector< vector<char> >p, vector< vector<char> > f, int n){ //Checks if the two patterns match
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(p[i][j] != f[i][j]) return false;
        }
    }
    return true;
}

vector< vector<char> > rotate(vector< vector<char> > p, int n){ //Rotates pattern 90 degrees
    vector< vector<char> > temp;
    for(int i = 0; i < n; i++){
        temp.push_back(vector<char>(n));
    }

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            temp[j][n - 1 - i] = p[i][j];
        }
    }

    return temp;
}

vector< vector<char> > reflect(vector< vector<char> > p, int n){ //Reflects around vertical axis
    vector< vector<char> > temp;
    for(int i = 0; i < n; i++){
        temp.push_back(vector<char>(n));
        for(int j = 0; j < n; j++){
            temp[i][j] = p[i][n - 1 - j];
        }
    }
    return temp;
}

void print(vector< vector<char> > p){ //Prints pattern
    for(auto i:p){
        for(auto j:i) cout << j << ' ';
        cout << endl;
    }
}

vector< vector<char> > copy(vector< vector<char> > p, int n){ //Copies pattern over
        vector< vector<char> > temp;
    for(int i = 0; i < n; i++){
        temp.push_back(vector<char>(n));
        for(int j = 0; j < n; j++){
            temp[i][j] = p[i][j];
        }
    }
    return temp;
}


int main() {
    ofstream fout ("transform.out");
    ifstream fin ("transform.in");

    vector< vector<char> > grid, final;
    int n;
    fin >> n;
    for(int i = 0; i < n; i++){
        grid.push_back(vector<char>(n));
        final.push_back(vector<char>(n));
    }

    for(int i = 0; i < n; i++){ //Start pattern input
        string row;
        fin >> row;
        for(int j = 0; j < n; j++){
            grid[i][j] = row[j];
        }
    }

    for(int i = 0; i < n; i++){ //End pattern input
        string row;
        fin >> row;
        for(int j = 0; j < n; j++){
            final[i][j] = row[j];
        }
    }

    vector< vector<char> > cp = copy(grid, n); //Checks all rotations first
    for(int i = 1; i <= 3; i++){
        cp = rotate(cp, n);
        if(compare(cp, final, n)){
            fout << i << endl;
            return 0;
        }
    }

    cp = copy(grid, n); //Next, checks reflection
    cp = reflect(cp, n);
    if(compare(cp, final, n)){
        fout << 4 << endl;
        return 0;
    }

    for(int i = 1; i <= 3; i++){ //Reflection then Rotation
        cp = rotate(cp, n);
        if(compare(cp, final, n)){
            fout << 5 << endl;
            return 0;
        }
    }

    if(compare(grid, final, n)){ //See if already was valid
        fout << 6 << endl;
        return 0;
    }

    fout << 7 << endl; //If nothing works
    return 0;
}

