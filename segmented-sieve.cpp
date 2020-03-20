// https://www.spoj.com/problems/PRIME1/
// https://www.spoj.com/problems/PRINT/
// segmented sieve is much faster than rabin-miller

#include <iostream>
#include <stdio.h>
#include <vector>
#include <math.h>

using namespace std;

const int maxN = 46789;
const int maxM = 1e6 + 123;

int prime[maxN];
bool p[maxM];
vector<int> primeList;

void init(){
    for(int i = 2; i < maxN; ++i) prime[i] = i;
    for(int i = 2; i * i < maxN; ++i)
        if(prime[i] == i)
        for(int j = i * i; j < maxN; j += i) prime[j] = i;
    for(int i = 2; i < maxN; ++i) if(prime[i] == i) primeList.push_back(i);
}

int low,high;
void segmentedsieve(){
    int N = high - low + 1;
    for(int i = 1; i <= N; ++i) p[i] = 1;
    for(int x : primeList){
        if(x > sqrt(high)) break;
        int y = low/x * x;
        while(y < low || y == x) y += x;
        while(y <= high){
            p[y - low + 1] = 0;
            y += x;
        }
    }
    for(int i = 1; i <= N; ++i) if(p[i]) printf("%d\n",i + low - 1);
}
int main(){
    init();

    int t;
    scanf("%d",&t);
    while(t--){
        scanf("%d%d",&low,&high);
        while(low <= 1) ++low;
        if(low <= high) segmentedsieve();
    }
    return 0;
}
