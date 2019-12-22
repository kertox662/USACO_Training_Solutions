/*
ID: misha2
TASK: ttwo
LANG: C++                 
*/

#include <iostream>
#include <fstream>
#include <set>
#include <tuple>

using namespace std;

enum direction{
    NORTH,
    EAST,
    SOUTH,
    WEST
};

char grid[12][12];

tuple<int,int,int> fPos = {0,0,0}, cPos = {0,0,0};
set<tuple<int,int,int,int,int,int> > states;

tuple<int,int,int> update(tuple<int,int,int> pos){
    pair<int,int> loc = {get<0>(pos), get<1>(pos)};
    int dir = get<2>(pos);
    if(dir == NORTH){
        pair<int,int> nextPos = {loc.first-1, loc.second};
        if(grid[nextPos.first][nextPos.second] == '*') dir = EAST;
        else loc = nextPos;

    } else if(dir == EAST){
        pair<int,int> nextPos = {loc.first, loc.second+1};
        if(grid[nextPos.first][nextPos.second] == '*') dir = SOUTH;
        else loc = nextPos;

    } else if(dir == SOUTH){
        pair<int,int> nextPos = {loc.first+1, loc.second};
        if(grid[nextPos.first][nextPos.second] == '*') dir = WEST;
        else loc = nextPos;

    }else if(dir == WEST){
        pair<int,int> nextPos = {loc.first, loc.second-1};
        if(grid[nextPos.first][nextPos.second] == '*') dir = NORTH;
        else loc = nextPos;

    }

    return tuple_cat(loc, tie(dir));
}

int main() {
    ofstream fout ("ttwo.out");
    ifstream fin ("ttwo.in");

    for(int i = 0; i < 12; i++){
        for(int j = 0; j < 12; j++){
            grid[i][j] = '*';
        }
    }

    for(int i = 1; i <= 10; i++){
        for(int j = 1; j <= 10; j++){
            char c;
            fin >> c;
            if(c == 'F'){
                fPos = {i,j,NORTH};
                c = '.';
            } else if(c == 'C'){
                cPos = {i,j,NORTH};
                c = '.';
            }
            grid[i][j] = c;
        }
    }


    int nMoves = 0;
    bool reachedCows = false;
    while(states.find(tuple_cat(fPos, cPos)) == states.end()){
        states.insert(tuple_cat(fPos, cPos));
        fPos = update(fPos);
        cPos = update(cPos);
        nMoves++;
        pair<int,int> fLoc = {get<0>(fPos),get<1>(fPos)}, cLoc = {get<0>(cPos),get<1>(cPos)};
        if(fLoc == cLoc){
            reachedCows = true;
            break;
        }
    }

    if(reachedCows) fout << nMoves << endl;
    else fout << 0 << endl;

    return 0;
}