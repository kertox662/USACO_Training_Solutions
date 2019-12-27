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
#define MAXC 26
#define MAXR 30
#define MAXPIECE 780
#define INF 20000

using namespace std;

// array<array<array<int, MAXR>, MAXC>, MAXPIECE> boards;
// const array<array<int, MAXC*MAXR>, MAXC*MAXR> dists = 


// array<array<array<array<int, MAXC>, MAXR>, MAXC>, MAXR> boards 



array<pair<int,int>, MAXPIECE> pieces;
int width, height, numPiece;

array<pair<int,int>, 8> moves = {{{-2,-1}, {-1,-2}, {-2,1}, {-1,2}, {1,2}, {2,1}, {1,-2}, {2,-1}}};

int main() {
    ofstream fout ("camelot.out");
    ifstream fin ("camelot.in");

    fin >> height >> width;
    int i;

    for(i = 0; ; i++){
        char c;
        int r;
        fin >> c >> r;
        if(i > 0 && pieces[i-1] == pair<int,int>{r-1,c-65}) break;
        pieces[i] = {r-1,c-65};
    }
    numPiece = i;

    // for(int i = 0; i < MAXR; i++){
    //     for(int j = 0; j < MAXC; j++){
    //         queue<pair<pair<int,int>,int> > squareQ;
    //         set<pair<int,int> > visited;
    //         squareQ.push({{i,j},0});
    //         while(!squareQ.empty()){
    //             auto p = squareQ.front();
    //             squareQ.pop();
    //             visited.insert(p.first);
    //             int r = p.first.first, c = p.first.second, dist = p.second;
    //             boards[i][j][r][c] = dist;
    //             for(pair<int,int> m : moves){
    //                 int dr = m.first, dc = m.second;
    //                 if(r + dr >= 0 && r + dr < MAXR)
    //             }
    //         }
    //     }
    // }

    //BOARD GEN FROM 780x780 BOARD
    // cout << '{';
    // for(int i = 0; i < MAXR; i++){
    //     cout << '{';
    //     for(int j = 0; j < MAXC; j++){
    //         cout << '{';
    //         for(int i2 = 0; i2 < MAXR; i2++){
    //             cout << '{';
    //             for(int j2 = 0; j2 < MAXC; j2++){
    //                 cout << dists[i*MAXC + j][i2 * MAXC + j2];
    //                 if(j2 != MAXC-1) cout << ',';
    //             }
    //             cout << '}';
    //             if(i2 != MAXR - 1) cout << ',';
    //         }
    //         cout << '}';
    //         if(j != MAXC-1) cout << ',';
    //     }
    //     cout << '}';
    //     if(i!=MAXR-1)cout << ',';
    // }
    // cout << '}' <<';' << endl;

    cout << boards[0][0][29][25] << endl;

    return 0;
}