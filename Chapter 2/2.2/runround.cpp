/*
ID: misha2
TASK: runround
LANG: C++                 
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

vector<int> makeV(int n){
    vector<int> v;
    while(n > 0){
        v.push_back(n % 10);
        n /= 10;
    }
    reverse(v.begin(), v.end());
    return v;
}

int sumV(vector<int> v){
    int s = 0;
    for(int i : v) s+=i;
    return s;
}

vector<int> fixSelfLoop(vector<int> v){
    if(v[0] == 9 && v.size() == 9){
        v[0] = 0;
        v.insert(v.begin(), 1);
        return fixSelfLoop(v);
    }
    for(int i = 0; i < v.size(); i++){
        if(v[i] == v.size()) v[i]++;
    }
    return v;
}

set<int> getModSet(vector<int> v){
    set<int> s;
    for(int i = 0; i < v.size(); i++){
        s.insert((i + v[i]) % v.size());
    }
    return s;
}

bool checkRun(vector<int> v){
    int start = 0, it = 0;
    do{
        // cout << start << ' ' << it << endl; 
        start = (start + v[start]) % v.size();
        it++;
    }while (start != 0 && it <= v.size() + 1);

    if(it != v.size()) return false;
    return true;
}

vector<int> next(vector<int> v){
    // for(int i : v) cout << i;
    // cout << endl;
    for(int i = v.size() - 1; i >= 0; i--){
        // cout << "Before: " <<  v[i] << endl;
        ++v[i] %= 10;
        // cout << "After: " <<  v[i] << endl;
        if(v[i]!=0) break;
    }
    
    if(v[0] == 0) v.insert(v.begin(), 1);
    
    // for(int i : v) cout << i;
    // cout << endl;
    return v;
}

int main() {
    ofstream fout ("runround.out");
    ifstream fin ("runround.in");

    int start;
    fin >> start;

    bool found = false;
    vector<int> v = next(makeV(start));
    v = fixSelfLoop(v);

    while(!found){
        // for(int i : v) cout << i;
        // cout << endl;
        // cout << "HERE" << endl;
        int sum = sumV(v);
        auto s = getModSet(v);
        bool repeat = false;
        for(int i : v){
            if(count(v.begin(), v.end(), i) > 1){
                repeat = true;
                break;
            }
        }

        if(repeat || sum % v.size() != 0 || s.size() != v.size()){
            v = fixSelfLoop(next(v));
            continue;
        }
        if(checkRun(v)) found = true;
        else v = fixSelfLoop(next(v));
    }
    
    for(int i : v) fout << i;
    fout << endl;

    return 0;
}