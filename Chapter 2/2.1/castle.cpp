/*
ID: misha2
TASK: castle
LANG: C++                 
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <algorithm>
#include <map>
#include <string>

using namespace std;

int curComp = 1;
int w, h;

vector< vector<int> > house, components;
set<pair<int,int> > conns;
vector<int> roomSizes;
vector< pair<int,int> > largest;


void floodFill(int x, int y){
    components[y][x] = curComp;
    if(roomSizes.size() == curComp) roomSizes.push_back(0);

    roomSizes[curComp]++;

    for(int dir = 1; dir <= 8; dir <<= 1){
        bool wall = ((dir & house[y][x]) == dir);
        int a,b;
        switch(dir){
            case 1:
                a = -1;
                b = 0;
                break;
            case 2:
                a = 0;
                b = -1;
                break;
            case 4:
                a = 1;
                b = 0;
                break;
            case 8:
                a = 0;
                b = 1;
        }
        int newX = x + a, newY = y + b;
        if(!(newX < 0 || newY < 0 || newX >= w || newY >= h)){
            if(wall){
                if(components[newY][newX] != 0 && components[newY][newX] != curComp){
                    int comp1 = components[y][x], comp2 = components[newY][newX];
                    pair<int, int> p(min(comp1, comp2), max(comp1,comp2));
                    conns.insert(p);
                }
            }
            else{
                if(components[newY][newX] == 0)
                    floodFill(newX, newY);
            }
        }

    }
}

int largestRoom(){
    int m = 0;
    for(int i : roomSizes) m = max(m, i);
    return m;
}

int largestCombinedRoom(){
    int m = 0;
    for(auto p : conns) {
        m = max(m, roomSizes[p.first] + roomSizes[p.second]);
    };

    for(auto p : conns){
        if(roomSizes[p.first] + roomSizes[p.second] == m) 
            largest.push_back(p);
    }

    return m;
}

string outOptimalWall(){
    map<int, vector<int> > paths;
    set<int> lookFor;
    for(auto p : largest){
        lookFor.insert(p.first);
        lookFor.insert(p.second);
        paths[p.first].push_back(p.second);
        paths[p.second].push_back(p.first);
    }

    for(int i = 0; i < w; i++){
        for(int j = h-1; j >= 0; j--){
            if(lookFor.find(components[j][i]) != lookFor.end()){
                vector<int> curPaths = paths[components[j][i]];
                if(j != 0){
                    if(find(curPaths.begin(), curPaths.end(), components[j-1][i]) != curPaths.end()){
                        return to_string(j + 1) + ' ' + to_string(i + 1) + " N";
                    }
                }
                if(i < w-1){
                    if(find(curPaths.begin(), curPaths.end(), components[j][i+1]) != curPaths.end()){
                        
                        return to_string(j + 1) + ' ' + to_string(i + 1) + " E";
                    }
                }
            }
        }
    }
    return "";
}

int main()
{
    ofstream fout("castle.out");
    ifstream fin("castle.in");

    fin >> w >> h;

    //Input and Setup
    for (int i = 0; i < h; i++){

        house.push_back(vector<int>(w));
        components.push_back(vector<int>(w));

        for (int j = 0; j < w; j++){
            fin >> house[i][j];
        }
    }

    roomSizes.push_back(0);


    //Flood Fill house to find rooms
    for (int y = 0; y < h; y++){
        for (int x = 0; x < w; x++){
            if (components[y][x] == 0){
                floodFill(x, y);
                curComp++;
            }
        }
    }

    for(int i = 0; i < h; i++){
        for(int b : components[i]) cout << b << ' ';
        cout << endl;
    }
    cout << endl;
    for(int s : roomSizes) cout << s << ' ';
    cout << endl;
    cout << endl;
    for(auto p : conns) cout << p.first << ',' << p.second << " | ";
    cout << endl;

    fout << roomSizes.size() - 1 << endl;
    fout << largestRoom() << endl;
    fout << largestCombinedRoom() << endl;
    fout << outOptimalWall() << endl;


    
}