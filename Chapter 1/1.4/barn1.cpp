/*
ID: misha2
TASK: barn1
LANG: C++                 
*/

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>


using namespace std;

vector<int> removeMax(vector<int> v){ //Finds max and removes it from vector
    if(v.size() == 0) return v;
    int ind = -1, m = 0;
    for(int i = 0; i < v.size(); i++){
        if(max(v[i], m) == v[i]){
            m = v[i];
            ind = i;
        }
    }
    v.erase(v.begin() + ind);
    return v;
}

int sumVector(vector<int> v){ //Adds up vector intervals
    int s = 0;
    for(auto it = v.begin(); it != v.end(); it++){
        s += *it;
    }
    return s;
}


int main() {
    ofstream fout ("barn1.out");
    ifstream fin ("barn1.in");
    
    int boards, stalls, cows;
    fin >> boards >> stalls >> cows;
    int sNum[cows];
    for(int i = 0; i < cows; i++){
        fin >> sNum[i];
    }

    sort(sNum, sNum + cows);
    vector<int> intervals;

    int lastCow = 0, interval = 1;
    for(int i = 1; i < cows; i++){
        if(sNum[i] - sNum[lastCow] == 1){//If cows are adjacent, increase cow Interval
            interval++;
        } else{
            intervals.push_back(interval); //Push back cow interval
            intervals.push_back(sNum[i] - sNum[lastCow] - 1); //Push back gap
            interval = 1;
        }

        lastCow = i;
    }
    intervals.push_back(interval); //Push back last cow

    vector<int> gaps, cow;

    for(int i = 0; i < intervals.size(); i+=2){//Cow vector
        cow.push_back(intervals[i]);
    }
    for(int i = 1; i < intervals.size(); i+=2){//Gaps vector
        gaps.push_back(intervals[i]);
    }

    int m = 201; //Don't think I use these
    int ind = -1;

    for(int i = 0; i < boards - 1; i++){ //Remove gaps equal to number of boards - 1 (since it is assumed a board currently spans all of the stalls)
        gaps = removeMax(gaps);
    }

    fout << sumVector(cow) + sumVector(gaps) << endl; //Sums vectors and outputs

    return 0;
}