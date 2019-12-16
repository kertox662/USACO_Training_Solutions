/*
ID: misha2
TASK: wormhole
LANG: C++                 
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

/*STRATEGY:
Find all collision links (If the y-values are the same then the links are a list of the positions with increasing x)
Generate each pairing recursively
For each pair, see if any starting hole will cause a cycle
If it does add one to cycle pairings
Output cycle pairings
*/

struct wormhole{
    int x,y;
    wormhole *next;
};

bool addLink(wormhole *l, wormhole *h){
    auto prev = h;
    while(h != nullptr && h->x < l->x){
        prev = h;
        h = h->next;
    }
    if (h == nullptr){
        prev->next = l;
        return false;
    }
    
    else if (prev == h) {
        l->next = h;
        return true;
    }
    else{
        prev->next = l;
        l->next = h;
        return false;
    }
}

void printLinks(wormhole *h){
    while(h != nullptr){
        cout << '(' << h->x << ',' << h->y << ") -> ";
        h = h->next;
    }
    cout << endl;
}

bool isInCycle(wormhole *holes, int *comb, int size){
    for(int i = 0; i < size; i++){
        wormhole *h = &holes[i];
        int ind = i;
        bool doPair = false;
        int step = 0;
        while(h != nullptr && step <= size * 2){
            
            if(doPair){
                ind = comb[ind];
                h = &holes[ind];
            }
            else{
                h = h->next;
                ind = h - holes;
            }

            doPair = !doPair;
            step++;
        }

        if(step > size * 2) return true;
    }

    return false;
}

void produceComb(wormhole *holes, int *comb, int size, bool *used, int *s){
    int i = -1;
    for(int j = 0; j < size; j++){
        if(!used[j]) {
            i = j;
            break;
        }
    }

    if(i == -1){
        if(isInCycle(holes, comb, size)){
            (*s)++;
        }
    }
    
     else{
        for(int j = i + 1; j < size; j++){
            if(used[j]) continue;
            comb[i] = j;
            comb[j] = i;
            used[i] = true;
            used[j] = true;
            produceComb(holes,comb, size, used, s);
            used[i] = false;
            used[j] = false;
        }
    }
}

int main() {
    ofstream fout ("wormhole.out");
    ifstream fin ("wormhole.in");

    int nHole;
    fin >> nHole;

    wormhole holes[nHole];
    vector<wormhole*> heads;
    
    for(int i = 0; i < nHole; i++){
        
        int x,y;
        fin >> x >> y;

        holes[i] = (wormhole){x,y};

        bool foundCollision = false;
        for(int j = 0; j < heads.size(); j++){
            wormhole* h = heads[j];
            
            if(h->y == y){
                bool doUpdate = addLink(&holes[i], h);
                
                if(doUpdate){
                    heads[j] = &holes[i];
                }
                
                foundCollision = true;
                break;
            }
        }
        if(!foundCollision) heads.push_back(&holes[i]);
    }

    int comb[nHole];
    bool used[nHole];
    for(int i = 0; i < nHole; i++) used[i] = false;

    int s = 0;

    produceComb(holes, comb, nHole, used, &s);

    fout << s << endl;

    return 0;
}