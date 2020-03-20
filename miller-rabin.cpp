#include <iostream>
#include <stdio.h>

#define LL long long

using namespace std;

pair<int,int> factor(int n){
    int m = 0;
    while((n & 1) == 0){
        ++m;
        n >>= 1;
    }
    return make_pair(m,n);
}
LL powmod(LL x,LL y,LL z){
    LL r = 1;
    while(y){
        if(y & 1) r = r * x % z;
        x = x * x % z;
        y >>= 1;
    }
    return r;
}
bool check(LL n,LL s,LL d,LL a){
    if(n == a) return 1;
    LL x = powmod(a,d,n);
    if(x == 1) return 1;
    for(;s > 0;s--){
        if(x == n - 1) return 1;
        x = x * x % n;
    }
    return 0;
}
bool miller(int n){
    if(n < 2) return false;
    if((n & 1) == 0) return n == 2;
    pair<int,int> x = factor(n - 1);
    return check(n,x.first,x.second,2) && check(n,x.first,x.second,7) && && check(n,x.first,x.second,61);
}
int main(){
    cout << miller(1e9 + 7);
    return 0;
}
