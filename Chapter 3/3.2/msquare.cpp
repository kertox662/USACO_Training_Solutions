/*
ID: misha2
TASK: msquare
LANG: C++                 
*/

#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <set>
#include <queue>
#include <map>
#define MAXSTATES 42320

using namespace std;

set< array<array<int, 4>, 2> > visited;

array<array<int,4>, 2> target, base = {{
                                    {1,2,3,4},
                                    {8,7,6,5}
                                    }};

queue<string> toCheck;
map<string, array<array<int,4>, 2> > config;

string answer = "N";

array<array<int,4>, 2> simulate(array<array<int,4>, 2> a, char t){
    switch(t){
        case 'A': //Row Swap Transform
            for(int i = 0; i < 4; i++){
                int temp = a[0][i];
                a[0][i] = a[1][i];
                a[1][i] = temp;
            }
            break;

        case 'B': //Shift Transform
            for(int j = 0; j < 2; j++){
                int temp = a[j][3];
                for(int i = 3; i > 0; i--){
                    a[j][i] = a[j][i-1];
                }
                a[j][0] = temp;
            }
            break;

        case 'C': //Rotate Transform
            int temp = a[1][2];
            a[1][2] = a[0][2];
            a[0][2] = a[0][1];
            a[0][1] = a[1][1];
            a[1][1] = temp;
            break;
    }
    return a;
}

void getAnswer(string state){
    array<array<int,4>, 2> init = config[state];
    for(char c : "ABC"){
        array<array<int,4>, 2> sim = simulate(init, c);
        if(visited.find(sim) == visited.end()){
            visited.insert(sim);
            config[state+c] = sim;
            toCheck.push(state+c);
            if(sim == target){
                answer = state+c;
                return;
            }
        }
    }
}

int main() {
    ofstream fout ("msquare.out");
    ifstream fin ("msquare.in");

    for(int i = 0; i < 4; i++){
        int in;
        fin >> in;
        target[0][i] = in;
    }
    for(int i = 3; i >= 0; i--){
        int in;
        fin >> in;
        target[1][i] = in;
    }

    config[""] = base;
    toCheck.push("");

    //Special case if the target is initial state
    if(base == target){
        fout << 0 << endl << endl;;
        return 0;
    }

    //Get the answer (Simulate until find)
    while(answer == "N"){
        string next = toCheck.front();
        getAnswer(next);
        toCheck.pop();
    }

    //OUT//
    fout << answer.length();
    for(int i = 0; i < answer.length(); i++){
        if(i%60 == 0) fout << endl;
        fout << answer[i];
    }
    if(answer.length()%60) fout << endl;

    return 0;
}