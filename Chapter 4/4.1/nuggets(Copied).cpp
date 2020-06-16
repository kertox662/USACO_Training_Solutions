/*
ID: misha2
TASK: nuggets
LANG: C++                 
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#define MAX_BOX 256

using namespace std;

int N;

int gcd(int a, int b){
    if(a%b){
        return gcd(b,a%b);
    }
    return b;
}

void pruneBoxes(vector<int> &boxes){
    sort(boxes.begin(), boxes.end());
    for(int i = 0; i < boxes.size(); i++){
        for(int j = i+1; j < boxes.size();){
            int g = gcd(boxes[i], boxes[j]);
            if(g == boxes[i]){
                boxes.erase(boxes.begin()+j);
                continue;
            }
            j++;
        }
    }
}

int main() {
    ofstream fout ("nuggets.out");
    ifstream fin ("nuggets.in");

    vector<int> boxes;
    fin >> N;
    for(int i = 0; i < N; i++){
        int box;
        fin >> box;
        boxes.push_back(box);
    }
    pruneBoxes(boxes);
    int minBox = boxes[0];
    int largest = minBox-1;

    if(minBox == 1){
        fout << 0 << endl;
        cout << 0 << endl;
        return 0;
    }

    int boxGCD = boxes[0];
    for(int i = 1; i < boxes.size(); i++){
        boxGCD = gcd(boxes[i], boxGCD);
    }
    if(boxGCD != 1){
        fout << 0 << endl;
        cout << 0 << endl;
        return 0;
    }

    bool window[MAX_BOX]{false};
    int pos = 0;
    int last = pos;
    window[0] = true;

    int i = 0;

    while (pos < 2000000000){
        if(pos - last > MAX_BOX){
            break;
        }

        if(window[i]){
            window[i] = false;
            for(int j = 0; j < N; j++)
                window[(i+boxes[j])%MAX_BOX] = true;
        } 
        else{
            last = pos;
        }
        
        i = (++pos)%MAX_BOX;
    }

    fout << last << endl;
    cout << last << endl;

    return 0;
}