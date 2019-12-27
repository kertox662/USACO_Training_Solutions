/*
ID: misha2
TASK: rockers
LANG: C++                 
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int maximum = 0;
int numSongs, numDisks, diskLength;

void simulate(vector<int> songs, int numFull, int curLength, int curSongs){
    if(maximum == numSongs) return;
    if(songs.size() == 0 || numFull == numDisks){
        maximum = max(maximum, curSongs);
        return;
    }
    int nextLength = songs[0];
    songs.erase(songs.begin());

    if(curLength + nextLength < diskLength){
        simulate(songs, numFull, curLength + nextLength, curSongs+1); //Song is added to the current disk and the disk continues
    }
    else if(curLength + nextLength == diskLength){
        simulate(songs, numFull+1, 0, curSongs+1); //Song is added and a new disk is started
    }

    else{
        if(numFull < numDisks - 1 && nextLength < diskLength){
            simulate(songs, numFull + 1, nextLength, curSongs+1); //Song is added onto a new disk
        }
        else if(numFull < numDisks - 2 && nextLength == diskLength){
            simulate(songs, numFull+2, 0, curSongs+1);
        }
    }

    simulate(songs, numFull, curLength, curSongs); //Song not added
    
}

int main() {
    ofstream fout ("rockers.out");
    ifstream fin ("rockers.in");
    fin >> numSongs >> diskLength >> numDisks;
    vector<int> songs;
    for(int i = 0; i < numSongs; i++){
        int s;
        fin >> s;
        songs.push_back(s);
    }

    simulate(songs,0,0,0);

    //OUT//
    cout << maximum << endl;
    fout << maximum << endl;

    return 0;
}