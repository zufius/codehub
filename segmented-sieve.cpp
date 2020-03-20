// https://www.spoj.com/problems/PRIME1/

#include <iostream>
#include <stdio.h>
#include <vector>

using namespace std;

const int maxN = 34567;
const int maxM = 1e5 + 123;

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
        int y = low/x * x;
        while(y < low || y == x) y += x;
        while(y <= high){
            p[y - low + 1] = 0;
            y += x;
        }
    }
    for(int i = 1; i <= N; ++i) if(p[i]) cout << i + low - 1 << "\n";
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie();
    cout.tie();
    
    init();

    int t;
    cin >> t;
    while(t--){
        cin >> low >> high;
        while(low <= 1) ++low;
        if(low <= high) segmentedsieve();
        cout << "\n";
    }
    return 0;
}
