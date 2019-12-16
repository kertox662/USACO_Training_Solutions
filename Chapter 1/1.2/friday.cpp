/*
ID: misha2
TASK: friday
LANG: C++                 
*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

bool isLeapYear(int year){
    if(year % 4 == 0){
        if(year%100 == 0){
            if(year%400 == 0){
                return true;
            }
            return false;
        }
        return true;
    }
    return false;
}

const int months[] = {31,28,31,30,31,30,31,31,30,31,30,31};

int main() {
    ofstream fout ("friday.out");
    ifstream fin ("friday.in");

    int occur[] = {0,0,0,0,0,0,0};
    int weekday = 4; //Weekday of last 13th in December 1899
    
    int years;
    fin >> years;

    for(int y = 0; y < years; y++){
        for(int i = 0; i < 12; i++){
            int ind = (i == 0)?11:i-1; //Looks at the previous month length to see how long it took to reach this one
            int ml = months[ind];
            
            if(ml == 28) if(isLeapYear(1900 + y)) ml++; //February check
            weekday = (weekday + ml) % 7;
            occur[weekday]++;
        }
    }
    fout << occur[0];
    for(int i = 1; i < 7; i++){
        fout << ' ' << occur[i];
    }
    fout << endl;


    return 0;
}