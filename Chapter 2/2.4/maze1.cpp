/*
ID: misha2
TASK: maze1
LANG: C++                 
*/

#include <iostream>
#include <fstream>
#include <queue>
#include <cmath>
#define HUGENUM 1000000000

using namespace std;

int main() {
    ofstream fout ("maze1.out");
    ifstream fin ("maze1.in");
    int w,h;
    fin >> w >> h;
    char maze[2*h+1][2*w+1];
    int conn[h][w];
    int paths1[h][w], paths2[h][w];
    pair<int,int> exit1, exit2;
    bool foundExit1 = false;
    
    for(int i = 0; i < h; i++){
        for(int j = 0; j < w; j++){
                paths1[i][j] = HUGENUM;
                paths2[i][j] = HUGENUM;
        }
    }

    for(int i = 0; i < (2*h+1) * (2*w+1); i++){
        char c; 
        fin.get(c);
        if(c == '\n') fin.get(c);
        maze[i/(2*w+1)][i % (2*w+1)] = c;
    }

    for(int i = 1; i <= 2*h-1; i+=2){
        for(int j = 1; j <= 2*w-1; j+=2){
            int conns = 0;

            if(maze[i-1][j] == ' '){
                if(i-1 == 0){
                    if(!foundExit1){
                        exit1 = {-1,j/2};
                        foundExit1 = true;
                    } else exit2 = {-1,j/2};
                }
                else conns += 1;
            }

            if(maze[i][j+1] == ' '){
                if(j+1 == 2*w){
                    if(!foundExit1){
                        exit1 = {i/2,w};
                        foundExit1 = true;
                    } else exit2 = {i/2,w};
                }
                else conns+=2;
            }
            if(maze[i+1][j] == ' '){
                if(i+1 == 2*h){
                    if(!foundExit1){
                        exit1 = {h,j/2};
                        foundExit1 = true;
                    } else exit2 = {h,j/2};
                }
                else conns += 4;
            }

            if(maze[i][j-1] == ' '){
                if(j-1 == 0){
                    if(!foundExit1){
                        exit1 = {i/2,-1};
                        foundExit1 = true;
                    } else exit2 = {i/2,-1};
                }
                else conns+=8;
            }

            conn[i/2][j/2] = conns;
        }
    }

    queue<pair<int,int> > q1,q2;

    if(exit1.first < 0){
        q1.push({0, exit1.second});
        paths1[0][exit1.second] = 1;
    }
    else if(exit1.first >= h){
        q1.push({h-1, exit1.second});
        paths1[h-1][exit1.second] = 1;
    }
    else if(exit1.second < 0){
        q1.push({exit1.first, 0});
        paths1[exit1.first][0] = 1;
    } 
    else if(exit1.second >= w){
        q1.push({exit1.first, w-1});
        paths1[exit1.first][w-1] = 1;
    }


    if(exit2.first < 0){
        q2.push({0, exit2.second});
        paths2[0][exit2.second] = 1;
    }
    else if(exit2.first >= h){
        q2.push({h-1, exit2.second});
        paths2[h-1][exit2.second] = 1;
    }
    else if(exit2.second < 0){
        q2.push({exit2.first, 0});
        paths2[exit2.first][0] = 1;
    } 
    else if(exit2.second >= w){
        q2.push({exit2.first, w-1});
        paths2[exit2.first][w-1] = 1;
    }

    while (!q1.empty()){
        pair<int,int> curPos = q1.front();
        int y = curPos.first, x = curPos.second;
        int dir = conn[y][x], steps = paths1[y][x];
        if(dir&1){
            int y2 = y-1, x2 = x;
            if(paths1[y2][x2] == HUGENUM){
                paths1[y2][x2] = steps+1;
                q1.push({y2,x2});
            }
        }
        if(dir&2){
            int y2 = y, x2 = x+1;
            if(paths1[y2][x2] == HUGENUM){
                paths1[y2][x2] = steps+1;
                q1.push({y2,x2});
            }
        }
        if(dir&4){
            int y2 = y+1, x2 = x;
            if(paths1[y2][x2] == HUGENUM){
                paths1[y2][x2] = steps+1;
                q1.push({y2,x2});
            }
        }
        if(dir&8){
            int y2 = y, x2 = x-1;
            if(paths1[y2][x2] == HUGENUM){
                paths1[y2][x2] = steps+1;
                q1.push({y2,x2});
            }
        }
        q1.pop();
    }

    while (!q2.empty()){
        pair<int,int> curPos = q2.front();
        int y = curPos.first, x = curPos.second;
        int dir = conn[y][x], steps = paths2[y][x];
        if(dir&1){
            int y2 = y-1, x2 = x;
            if(paths2[y2][x2] == HUGENUM){
                paths2[y2][x2] = steps+1;
                q2.push({y2,x2});
            }
        }
        if(dir&2){
            int y2 = y, x2 = x+1;
            if(paths2[y2][x2] == HUGENUM){
                paths2[y2][x2] = steps+1;
                q2.push({y2,x2});
            }
        }
        if(dir&4){
            int y2 = y+1, x2 = x;
            if(paths2[y2][x2] == HUGENUM){
                paths2[y2][x2] = steps+1;
                q2.push({y2,x2});
            }
        }
        if(dir&8){
            int y2 = y, x2 = x-1;
            if(paths2[y2][x2] == HUGENUM){
                paths2[y2][x2] = steps+1;
                q2.push({y2,x2});
            }
        }
        q2.pop();
    }

    int m = 0;
    for(int i = 0; i < h; i++){
        for(int j = 0; j < w; j++){
            m = max(m, min(paths1[i][j], paths2[i][j]));
        }
    }

    if(m == HUGENUM) m = 0;
    fout << m << endl;

    return 0;
}