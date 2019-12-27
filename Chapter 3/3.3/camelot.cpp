/*
ID: misha2
TASK: camelot
LANG: C++                 
*/

#include <iostream>
#include <fstream>
#include <array>
#include <queue>
#include <set>
#include <cmath>
#define MAXC 26
#define MAXR 30
#define MAXPIECE 781
#define INF 20000

using namespace std;

// array<array<array<int, MAXR>, MAXC>, MAXPIECE> boards;
// const array<array<int, MAXC*MAXR>, MAXC*MAXR> dists = 


// array<array<array<array<int, MAXC>, MAXR>, MAXC>, MAXR> boards 



array<pair<int,int>, MAXPIECE> pieces;
int width, height, numPiece;

array< array<array<int, MAXC>, MAXR>, MAXPIECE> sumBoards;  


array<pair<int,int>, 8> moves = {{{-2,-1}, {-1,-2}, {-2,1}, {-1,2}, {1,2}, {2,1}, {1,-2}, {2,-1}}};

void makeSumBoards(){
    // array<array<int, MAXC>, MAXR> sumBoard;

    for(int p = 0; p < numPiece; p++){
        if(p == 0){
            for(int p2 = 1; p2 < numPiece; p2++){
                pair<int,int> piece = pieces[p2];
                for(int i = 0; i < height; i++){
                    for(int j = 0; j < width; j++){
                        sumBoards[p][i][j] += boards[i][j][piece.first][piece.second];
                    }
                }
            }
        } else{
            sumBoards[p] = sumBoards[0];
            pair<int,int> piece = pieces[p];
            for(int i = 0; i < height; i++){
                for(int j = 0; j < width; j++){
                    sumBoards[p][i][j] -= boards[i][j][piece.first][piece.second];
                }
            }
        }
    }
}

void calculateBoard(pair<int,int> start){
    int newBoard[height][width];
    for(int i = 0; i < height; i++)
        for(int j = 0; j < width; j++)
            newBoard[i][j] = INF;
    queue<pair<pair<int,int>, int> > toCheck;
    set<pair<int,int> > visited;

    toCheck.push({start, 0});
    visited.insert(start);
    while(!toCheck.empty()){
        auto p = toCheck.front();
        int i = p.first.first, j = p.first.second, d = p.second;
        toCheck.pop();
        newBoard[i][j] = d;
        for(auto m : moves){
            int y = i + m.first, x = j + m.second;
            if(y >= 0 && y < height && x >= 0 && x < width){
                if(visited.find({y,x}) != visited.end()) continue;
                toCheck.push({{y,x},d+1});
                visited.insert({y,x});
            }
        }
    }

    for(int i = 0; i < height; i++)
        for(int j = 0; j < width; j++){
            boards[start.first][start.second][i][j] = newBoard[i][j];
            boards[i][j][start.first][start.second] = newBoard[i][j];
        }
            
}

void regen(){
    if(width >= 2 && height >= 2){
        calculateBoard({1,width-2});
        calculateBoard({height-2, 1});
        calculateBoard({height-2, width-2});
    }
    if(width == 3){
        calculateBoard({0,1});
        calculateBoard({height-1,1});
    }
    if(height == 3){
        calculateBoard({1,0});
        calculateBoard({1,width-1});
    }
}

int main() {
    ofstream fout ("camelot.out");
    ifstream fin ("camelot.in");

    fin >> height >> width;
    int i;

    for(i = 0; ; i++){
        char c;
        int r;
        fin >> c >> r;
        if(i > 1 && pieces[i-1] == pair<int,int>{r-1,c-65}) break;
        pieces[i] = {r-1,c-65};
    }
    numPiece = i;

    regen();
    makeSumBoards();
    
    queue<pair<pair<int,int>, int> > kingPos;
    set<pair<int,int> > visitedKing;
    kingPos.push({pieces[0], 0});
    visitedKing.insert(pieces[0]);
    

    int minimum = INF;
    int lastMinFound = 0;
    while(!kingPos.empty()){
        auto pos = kingPos.front();
        int r = pos.first.first, c = pos.first.second, dist = pos.second;
        kingPos.pop();
        if(dist - lastMinFound >= 4) continue;

        bool kingNeedsKnight = true;
        for(int i = 1; i < numPiece; i++){
            if(pieces[i] == pair<int,int>{r,c}){
                kingNeedsKnight = false;
                break;
            }
        }
        
        if(kingNeedsKnight){
            if(sumBoards[0][r][c] + dist < minimum){//Knights Meet King at this position
                minimum = sumBoards[0][r][c] + dist;
                lastMinFound = dist;
            }
            for(int p = 1; p < numPiece; p++){ //A Knight picks up the King
                array<array<int, MAXC>, MAXR> a = sumBoards[p];
                int rp = pieces[p].first, cp = pieces[p].second;
                int minDist = INF;
                for(int y = 0; y < height; y++){
                    for(int x = 0; x < width; x++){
                        a[y][x] += boards[r][c][y][x];
                        if(a[y][x] < minDist) minDist = a[y][x];
                    }
                }
                minDist += boards[rp][cp][r][c] + dist;
                if(minDist < minimum){
                    minimum = minDist;
                    lastMinFound = dist;
                }
            }

            for(int i = -1; i <= 1; i++){
                for(int j = -1; j <= 1; j++){
                    if(i == 0 && j == 0)continue;
                    if(visitedKing.find({r+i, c+j}) != visitedKing.end()) continue;
                    if(r+i >= 0 && r+i < height && c+j >= 0 && c+j < width){
                        kingPos.push({{r + i, c+j},dist+1});
                        visitedKing.insert({r+i, c+j});
                    }
                }
            }
        } else{
            int oldMinimum = minimum;
            for(int i = 0; i < height; i++){
                for(int j = 0; j < width; j++){
                    minimum = min(minimum, sumBoards[0][i][j] + dist);
                }
            }
            if(minimum != oldMinimum) break;
        }

    }
    
    cout << minimum << endl;
    fout << minimum << endl;

    return 0;
}