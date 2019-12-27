/*
ID: misha2
TASK: shopping
LANG: C++                 
*/

#include <iostream>
#include <fstream>
#include <array>
#include <map>
#include <set>
#include <queue>
#define MAX_OFFERS 99
#define MAX_PURCHASES 5

using namespace std;

array<map<int,int>, MAX_OFFERS> offers;
int numOffers, numBuy;

map<int,int> regCost;
map<map<int,int>,int> lowestPrice;
set<map<int,int> > checked;
queue<map<int,int> > purchaseQ;
array<int, 5> productCode;

map<int,int> toPurchase;

int main() {
    ofstream fout ("shopping.out");
    ifstream fin ("shopping.in");
    fin >> numOffers;
    for(int i = 0; i < numOffers; i++){
        int numProducts, productCode, quant, cost;
        map<int,int> offer;
        fin >> numProducts;
        for(int j = 0; j < numProducts; j++){
            fin >> productCode >> quant;
            offer[productCode] = quant;
        }
        fin >> cost;
        offer[0] = cost;
        offers[i] = offer;
    }

    fin >> numBuy;
    for(int i = 0; i < numBuy; i++){
        int code, quant, reg;
        fin >> code >> quant >> reg;
        regCost[code] = reg;
        toPurchase[code] = quant;
        productCode[i] = code;
    }

    map<int,int> empty;
    for(int i = 0; i < numBuy; i++){
        empty[productCode[i]] = 0;
    }

    for(int i = 0; i < numBuy; i++){
        map<int,int> single = empty;
        single[productCode[i]] = 1;
        purchaseQ.push(single);
    }

    while(!purchaseQ.empty()){
        map<int,int> cur = purchaseQ.front();
        purchaseQ.pop();

        int lowest = 0;
        for(auto i : cur) 
            lowest += regCost[i.first] * i.second;
        for(int o = 0; o < numOffers; o++){
            auto curCopy = cur;
            bool validOffer = true;
            for(int i = 0; i < numBuy; i++){
                if(offers[o][productCode[i]] > curCopy[productCode[i]] ){
                    validOffer = false;
                    break;
                }
                else{
                    curCopy[productCode[i]] -= offers[o][productCode[i]];
                }
            }
            if(!validOffer) continue;
            int curPrice = offers[o][0] + lowestPrice[curCopy];
            if(curPrice < lowest) lowest = curPrice;
        }
        lowestPrice[cur] = lowest;

        for(int i = 0; i < numBuy; i++){
            auto curCopy = cur;
            curCopy[productCode[i]]++;
            if(curCopy[productCode[i]] > 5) continue;
            if(checked.find(curCopy) != checked.end()) continue;
            checked.insert(curCopy);
            purchaseQ.push(curCopy);
        }
        if(cur == toPurchase) break;
    }

    fout << lowestPrice[toPurchase] << endl;
    cout << lowestPrice[toPurchase] << endl;

    return 0;
}