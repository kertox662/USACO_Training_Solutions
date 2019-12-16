/*
ID: misha2
TASK: milk2
LANG: C++                 
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int max(int a, int b){
    return (a > b)?a:b;
}

int min(int a, int b){
    return (a < b)?a:b;
}

struct interval{
    int start, end;

    bool isWithin(int t){
        return (t >= start && t <= end);
    }

    bool isWithin(interval i){
        return i.start <= start && i.end >= end;
    }

    bool overLap(interval i){
        return isWithin(i.start) || isWithin(i.end);
    }

    int duration(){
        return end - start;
    }

    int gap(interval i){
        return max(i.start - end, start - i.end);
    }
};

bool earlier(interval i, interval j){
    return i.start < j.start;
}

vector<interval> congregate(vector<interval> f){ //Intersects all intervals so that it shows the total interval in which is it being milked
    vector<interval> ints;
    ints.push_back(f[0]);
    for(int i = 1; i < f.size(); i++){ //for each interval
        bool didOverlap = false; //Will store if we had and overlap
        for(int j = 0; j < ints.size(); j++){ //Checks if it overlaps with any intervals in ints
            if(f[i].overLap(ints[j])){
                ints[j].start = min(ints[j].start, f[i].start); //Updates the overlapped interval
                ints[j].end = max(ints[j].end, f[i].end);
                didOverlap = true;
            }
            else if(f[i].isWithin(ints[j])){ //If an interval completely contains a different one
                didOverlap = true;
            }
            else if(ints[j].isWithin(f[i])){ //If the oppositite intervals comepletely contains
                ints[j] = f[i];
                didOverlap = true;
            }
        }

        if(!didOverlap) ints.push_back(f[i]); //If did not overlap, then it means it's mutually exlusive in time
    }
    return ints;
}

int main() {
    ofstream fout ("milk2.out");
    ifstream fin ("milk2.in");

    int n;
    fin >> n;
    vector<interval> f(n), prev;
    for(int i = 0; i < n; i++){
        int s, e;
        fin >> s >> e;
        f[i] = (interval){s,e};
    }

    do{ //Repeat this until congregating doesn't do anything anymore
        prev = f;
        f = congregate(f);
    }while(prev.size() != f.size());

    sort(f.begin(), f.end(), earlier); //Sort by time so we can calc times

    int milking = 0, nMilking = 0;
    for(int i = 0; i < f.size(); i++){
        interval it = f[i];
        milking = max(milking, it.duration()); //Checks for max milking duration
        if (i < f.size() - 1)
            nMilking = max(nMilking, it.gap(f[i+1])); //Checks for max non-milking duration
    }

    fout << milking << ' ' << nMilking << endl;
    return 0;
}