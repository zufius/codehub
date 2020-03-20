//https://www.spoj.com/problems/PON/

#include <iostream>
#include <stdio.h>
#include <vector>

typedef unsigned long long LL;

using namespace std;
using u128 = __uint128_t;

vector <LL> smallPrime,witness;

pair<LL,LL> factor(LL n){
    LL m = 0;
    while(!(n & 1)){
        ++m;
        n >>= 1;
    }
    return make_pair(m,n);
}
LL modpower(LL x,LL y,LL n){
    LL rr = 1;
    while(y){
        if(y & 1) rr = (u128)rr * x % n;
        x = (u128)x*x % n;
        y >>= 1;
    }
    return rr;
}
bool check(LL n,LL s,LL d, LL a){
    LL x = modpower(a,d,n);
    if(x == 1) return 1;
    for(;s > 0; --s){
        if(x == n - 1) return 1;
        x = (u128)x * x % n;
    }
    return 0;
}
bool miller(LL x){
    if(x < 5) return x == 2 || x == 3;
    for(LL p : smallPrime) if(x % p == 0) return 0;
    pair<LL,LL> ft = factor(x - 1);
    for(LL a : witness) if(!check(x,ft.first,ft.second,a)) return 0;
    return 1;
}
int main(){
    ios_base::sync_with_stdio(false); cin.tie(); cout.tie();
    
    for(int i = 5; i < 100; ++i){
        bool isprime = 1;
        for(int j = 2; j * j <= i; ++j) if(i % j == 0) isprime = 0;
        if(isprime){
            smallPrime.push_back(i);
            if(i < 41) witness.push_back(i);
        }
    }
    int t;
    cin >> t;
    while(t--){
        LL x;
        cin >> x;
        cout << (miller(x) ? "YES" : "NO");
        cout << "\n";
    }
    return 0;
}

// n ~ 1e6 => 2 3
// n ~ 2^32 => 2 7 61 / 2 3 5 7
// n ~ 64 bit => 2 3 5 7 11 13 17 19 23 29 31 37 41
