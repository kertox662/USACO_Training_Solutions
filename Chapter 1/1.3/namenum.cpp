/*
ID: misha2
TASK: namenum
LANG: C++                 
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

string letters[][3] = {{"A", "B", "C"},
                    {"D", "E", "F"},
                    {"G", "H", "I"},
                    {"J", "K", "L"},
                    {"M", "N", "O"},
                    {"P", "R", "S"},
                    {"T", "U", "V"},
                    {"W", "X", "Y"}};
int getIndex(char c){
    return c - 50;
}

vector<string> output;

int binarySearch(string n, int s, int e, vector<string> *a){
    int mid = (s + e) / 2;
    if (e < s) return -1;
    else if(a->at(mid) == n) return mid;
    else if(a->at(mid) < n) return binarySearch(n, mid + 1, e, a);
    return binarySearch(n, s, mid - 1, a);
}

void printMatches(string s, string cur, vector<string> *dict){
    for(string letter:letters[getIndex(s[0])]){//looks at the first letter and iterates through each letter
        if(s.length() > 1) printMatches(s.substr(1), cur + letter, dict); //If still have letters to add, recurse
        else{
            if(binarySearch(cur + letter, 0, dict->size(), dict) != -1) output.push_back(cur + letter); //Otherwise, search for the name in the dictionary
        }
    }
}

int main() {
    ofstream fout ("namenum.out");
    ifstream fin ("namenum.in");
    ifstream din("dict.txt");
    
    vector<string> dict;
    string name, serial;

    while(getline(din, name)){
        if (name[0] != 'Z' && name[0] != 'Q'){//Don't want to have stuff that starts with Z or Q as it will screw with the index
            dict.push_back(name);
        }
    }
    fin >> serial;

    printMatches(serial, "", &dict);
    if(output.size() == 0) fout << "NONE" << endl;
    else for(string s : output) fout << s << endl;

    return 0;
}