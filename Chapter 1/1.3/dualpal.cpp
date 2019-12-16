/*
ID: misha2
TASK: dualpal
LANG: C++                 
*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const char symb[20] = {'0','1','2','3','4','5','6','7','8','9'};

string toBase(int n, int b){
    string result = "";
    int r;
    while (n != 0){
        r = n % b;
        result = symb[r] + result;
        n /= b;
    }
    return result;
}

bool isPalindrome(string s){
    int l = s.length();
    for(int i = 0; i <= l - i - 1; i++){ //Checks from either end to see if it string a valid palindrome
        if(s[i] != s[l - i - 1]) return false;
    }
    return true;
}

int main() {
    ofstream fout ("dualpal.out");
    ifstream fin ("dualpal.in");

    int num, start;
    fin >> num >> start;

    int pals[num];
    int numFound = 0;

    while(numFound < num){
        start++;
        int numPal = 0;
        for(int i = 2; i <= 10 && numPal < 2; i++){ //For each base, see if it is a palindrome, if it is, increase numPal;
            if(isPalindrome(toBase(start, i))){
                numPal++;
            }
        }
        if(numPal >= 2){ //Only increase if at least two were found
            pals[numFound] = start;
            numFound++;
        }

    }

    for(int i : pals) fout << i << endl;

    return 0;
}