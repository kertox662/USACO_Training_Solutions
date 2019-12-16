/*
ID: misha2
TASK: gift1
LANG: C++                 
*/

#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

int main() {
    ofstream fout ("gift1.out");
    ifstream fin ("gift1.in");

    map<string, int> people;

    int numP;
    fin >> numP;

    string names[numP];

    for(int i = 0; i < numP; i++){ //Gets all names
        string name;
        fin >> name;
        people[name] = 0;
        names[i] = name;
    }

    for(int i = 0; i < numP; i++){
        string name;
        int account, friends;
        fin >> name >> account >> friends;
        if(friends > 0 && account > 0){
            int newPersonal = people[name] + account%friends - account; //Adds to account the left over amount from gifting and how much they spend
            people[name] = newPersonal;
            for(int i = 0; i < friends; i++){ //Updates friend account
                string f;
                fin >> f;
                people[f] += account / friends;
            }
        }
    }

    for(string name : names){
        fout << name << ' ' << people[name] << endl;
    }

    return 0;
}