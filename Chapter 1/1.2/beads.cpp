/*
ID: misha2
TASK: beads
LANG: C++                 
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct sequence{ //Custom type to represent sequences of certain colors
    int length;
    char color;
};

int max(int a, int b){
    return (a > b)?a:b;
}

int min(int a, int b){
    return (a < b)?a:b;
}

int main() {
    ofstream fout ("beads.out");
    ifstream fin ("beads.in");

    int beads;
    string neck;
    fin >> beads >> neck;

    vector<sequence> s; 

    char first = neck[0];
    
    int cSum = 0; //Current length of sequence
    char c = first; //Current colour
    for(int i = 0; i < beads; i++){
        if(neck[i] == c){ //Checks next bead, if identical to previous add it to sequence length
            cSum++;
        }
        else{ //Otherwise, reset and start for next color
            s.push_back((sequence){cSum, c});
            cSum = 1;
            c = neck[i];
        }

        if(i == beads - 1){ //If last bead is the same as the first one, then it will loop back around, so we add to first sequence
            if (neck[i] == first && s.size() > 0) s[0].length += cSum;
            else{
                s.push_back((sequence){cSum, c});
            }
        }
    }

    int size = s.size();
    if (size > 1)
        for(int i = 0; i < size; i++){ //Makes a copy of the current sequence so it simulates looping
            s.push_back(s[i]);
        }

    for(int i = 1; i < s.size() - 1;){
        if(s[i].color == 'w'){ //If a white is in the middle of two identical colours, it can be treated as the other colour
            if(s[i - 1].color == s[i+1].color){
                s[i - 1].length += s[i].length + s[i + 1].length;
                s.erase(s.begin() + i);
                s.erase(s.begin() + i);
            }
            else i++;
        }
        else i++;
    }

    int tL = 0;
    int i = 0;
    int whiteSum = 0;
    
    do{ //Calculates the top length
        char c = s[i].color; //Occurs when starting a new colour
        int l = s[i].length + whiteSum; //Have to include the number of whites to the left of the current sequence
        whiteSum = 0;
        if(c == 'w') ++i %= s.size(); //Skip if the first color is white, will be counted later anyways
        else{
            while(s[i].color == c || s[i].color == 'w'){ //If the colour is the same or if it's white
                if(s[i].color == 'w') whiteSum += s[i].length; //If the current colour is white, then must update white sum
                else whiteSum = 0;

                i = (i+1)%s.size(); //Next sequence
                if(i == 0)break;
                l += s[i].length;
                
            }
            int temp = i;
            while(s[i].color != c){ //I think this checks if it is the last sequence?? ?? ??
                ++i %= s.size();
                if(i == 0 || s[i].color == c)break;
                l += s[i].length;
            }
            i = temp;
        }
        tL = max(tL, l); //Sees if cur length is max
    } while(i != 0);
    tL = min(tL, neck.length()); //Might be the case where like rwrwrwrw where it would calc a bigger thing than it acutally is
    fout << tL << endl;
    return 0;
}