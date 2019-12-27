/*
ID: misha2
TASK: game1
LANG: C++                 
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <map>
#include <queue>

using namespace std;

vector<int> pieces;
map<vector<int>,pair<int,int> > maxAmount;

int numPiece;

int main() {
    ofstream fout ("game1.out");
    ifstream fin ("game1.in");

    fin >> numPiece;
    for(int i = 0; i < numPiece; i++){
        int p;
        fin >> p;
        pieces.push_back(p);
    }

    queue<vector<int> > checkState;

    int whenPlayer1 = pieces.size()%2;

    for(int i = 1; i <= numPiece; i++){
        for(int j = 0; j+i <= numPiece; j++){
            vector<int> next(pieces.begin() + j, pieces.begin()+i + j);
            checkState.push(next);
        }
    }

    while(!checkState.empty()){
        vector<int> v = checkState.front();
        pair<int,int> score;
        if(v.size() == 1){
            if(whenPlayer1) score = {v[0],0};
            else score = {0,v[0]};
            maxAmount[v] = score;
            checkState.pop();
            continue;
        }

        vector<int> v1 = checkState.front();
        vector<int> v2 = checkState.front();
        checkState.pop();
        v1.erase(v1.begin());
        v2.pop_back();

        pair<int,int> score1 = maxAmount[v1], score2 = maxAmount[v2];

        if(v.size()%2 == whenPlayer1){//Player 1's turn
            if(score1.first + v[0] > score2.first + v.back()){
                score = {score1.first + v[0], score1.second};
            }
            else if(score1.first + v[0] < score2.first + v.back()){
                score = {score2.first + v.back(), score2.second};
            } else{
                if(score1.second >= score2.second){
                    score = {score1.first + v[0], score1.second};
                }
                else score = {score2.first + v.back(), score2.second};
            }

        }
        else{ //Player 2's turn
            if(score1.second + v[0] > score2.second + v.back()){
                score = {score1.first, score1.second + v[0]};
            }
            else if(score1.second + v[0] < score2.second + v.back()){
                score = {score2.first, score2.second + v.back()};
            } else{
                if(score1.first >= score2.first){
                    score = {score1.first, score1.second + v[0]};
                }
                else score = {score2.first, score2.second+ v.back()};
            }
        }

        maxAmount[v] = score;
    }

    pair<int,int> finalScore = maxAmount[pieces];

    cout << finalScore.first << ' ' << finalScore.second << endl;
    fout << finalScore.first << ' ' << finalScore.second << endl;

    return 0;
}