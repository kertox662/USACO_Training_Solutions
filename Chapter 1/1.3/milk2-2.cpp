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

bool earlyEnd(interval i, interval j){
    return i.end < j.end;
}

vector<interval> congregate(vector<interval> f){
    vector<interval> ints;
    ints.push_back(f[0]);
    for(int i = 1; i < f.size(); i++){
        bool didOverlap = false;
        for(int j = 0; j < ints.size(); j++){
            if(f[i].overLap(ints[j])){
                ints[j].start = min(ints[j].start, f[i].start);
                ints[j].end = max(ints[j].end, f[i].end);
                didOverlap = true;
            }
            else if(f[i].isWithin(ints[j])){
                didOverlap = true;
            }
            else if(ints[j].isWithin(f[i])){
                ints[j] = f[i];
                didOverlap = true;
            }
        }

        if(!didOverlap) ints.push_back(f[i]);
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

    do{
        prev = f;
        f = congregate(f);
    }while(prev.size() != f.size());

    sort(f.begin(), f.end(), earlier);
    sort(prev.begin(), prev.end(), earlyEnd);
    int start = f[0].start, end = prev[prev.size() - 1].end;
    
    int milking = 0, nMilking = 0;
    int currentSum = 0;
    bool isMilking = true;
    for(int i = start; i < end; i++){
        bool foundOverlap = false;
        for(auto it = f.begin(); it != f.end();){
            interval j = *it;
            if(j.end < i){
                f.erase(it);
                continue;
            }

            if(j.isWithin(i)){
                foundOverlap = true;
                break;
            }
            it++;
        }

        if(foundOverlap != isMilking){
            currentSum = 0;
            isMilking = foundOverlap;
        }

        currentSum++;
        if(isMilking){
            milking = max(milking, currentSum);
        } else{
            nMilking = max(nMilking, currentSum);
        }
    }
    for(interval i: prev) cout << i.start << ' ' << i.end << ' ' << i.duration() << endl;
    fout << milking << ' ' << nMilking << endl;
    return 0;
}