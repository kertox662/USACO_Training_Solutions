/*
ID: misha2
TASK: fracdec
LANG: C++                 
*/

#include <iostream>
#include <fstream>
#include <set>
#include <vector>

using namespace std;

string longDivision(int n, int d){
    string result;
    result += to_string(n/d);
    result+=".";
    vector<pair<int,int> > digits;
    set<int> rem;
    int repInd = 0;
    n = n%d * 10;
    while(n!=0){
        int q = n/d, r = n%d;
        digits.push_back({q,r});
        if(rem.find(r) != rem.end()){
            for(int i = 0; i < digits.size(); i++){
                if(digits[i].second == r){
                    if(q == digits[i].first){
                        repInd = i;
                        digits.pop_back();
                    }
                    else {
                        repInd = i+1;
                    }
                    break;
                }
            }
            break;
        }
        rem.insert(r);
        n = r*10;
    }
    if (rem.size() == 0)return result + "0";
    else if(n == 0){
        for(int i = 0; i < digits.size(); i++){
            result += to_string(digits[i].first);
        }
        return result;
    }

    for(int i = 0; i < digits.size(); i++){
        if(i == repInd) result += '(';
        result += to_string(digits[i].first);
    }
    result += ')';
    return result;

}


int main() {
    ofstream fout ("fracdec.out");
    ifstream fin ("fracdec.in");

    int n,d;
    fin >> n >> d;

    string s = longDivision(n,d);
    // fout << s << endl;
    for(int i = 0; i < s.length(); i++){
        if(i!=0 && i%76 == 0) fout << endl;
        fout << s[i];
    }
    if(s.length()%76 != 0)
        fout << endl;

    // double q = n/d;
    // cout << q << ' ' << ((q*d == n)?"TRUE":"FALSE") << endl;

    return 0;
}