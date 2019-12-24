/*
ID: misha2
TASK: spin
LANG: C++                 
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <array>

using namespace std;

struct interval{
    int start, length;
};

array<vector<interval>, 5> wheels;
array<int, 5> speeds;

bool checkWheel(int degree, int wheel){
    vector<interval> w = wheels[wheel];
    bool valid = false;
    for(interval i : w){
        if(degree >= i.start && degree <= i.start + i.length){
            valid = true;
            break;
        }
        else if(degree+360 >= i.start && degree+360 <= i.start + i.length){
            valid = true;
            break;
        }
    }
    return valid;
}

int main() {
    ofstream fout ("spin.out");
    ifstream fin ("spin.in");

    for(int i = 0; i < 5; i++){
        fin >> speeds[i];
        int nWedge;
        fin >> nWedge;
        for(int j = 0; j < nWedge; j++){
            int start, interval;
            fin >> start >> interval;
            wheels[i].push_back({start,interval});
        }
    }

    // cout << checkWheel(60, 0) << endl;
    // for(auto w : wheels){
    //     cout << w.size() << '\t';
    //     for(auto i : w) cout << i.start << ':' << i.start+i.length << ' ';
    //     cout << endl;
    // }

    for(int i = 0;;i++){
        // cout << i << endl;
        for(int d = 0; d < 360; d++){
            bool valid = true;
            for(int w = 0; w < 5; w++){
                if(!checkWheel(d, w)){
                    valid = false;
                    // cout << w << " failed at " << d << endl;
                    break;
                }
            }
            if(valid){
                cout << i << " Seconds passed" << endl;
                fout << i << endl;
                return 0;
            }
        }
        for(int w = 0; w < 5; w++){
            for(int j = 0; j < wheels[w].size(); j++){
                wheels[w][j].start = (wheels[w][j].start + speeds[w]) % 360;
                // wheels[w][j].start %= 360;
            }
        }
        if(i >= 1000){
            fout << "none" << endl;
            return 0;
        }
    }

    return 0;
}