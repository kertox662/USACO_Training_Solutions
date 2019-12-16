/*
ID: misha2
TASK: ride
LANG: C++                 
*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    ofstream fout ("ride.out");
    ifstream fin ("ride.in");
    string comet, group;
    fin >> comet >> group;
    int cP = 1, gP = 1;
    for(char c : comet){
        if(c != '\n')
            cP *= c - 64; //64 is the char code for first character - 1 (so first character is 1)
    }
    for(char c : group){
        if(c != '\n')
            gP *= c - 64;
    }
    
    fout << (cP%47 == gP%47 ? "GO" : "STAY") << endl; //Checks if both are the same remainder

    return 0;
}