#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <vector>
#include <map>
#include <set>
#include <deque>
#include <queue>
#include <stdlib.h>
#include <time.h>
#include <iomanip>
#include <math.h>
#include <bitset>
#include <string.h>

using namespace std;

#define taskname "A"
#define LL long long 
#define uLL unsigned long long 
#define FOR(i,l,r) for(int i = l; i <= r; ++i)
#define REP(i,l,r) for(int i = l; i < r; ++i)
#define FORD(i,r,l) for(int i = r; i >= l; --i)
#define REPD(i,r,l) for(int i = r; i > l; --i)
#define sz(x) (int)((x).size())
#define all(x) (x).begin(), (x).end()
#define debug(x) { cerr << #x << " = " << x << endl; }
#define sci(x) int x; scanf("%d", &x);
#define scii(x, y) int x, y; scanf("%d %d", &x, &y);
#define sciii(x, y, z) int x, y, z; scanf("%d %d %d", &x, &y, &z);
#define pi pair<int,int>
#define pii pair<int,pi>
#define mp make_pair
#define fi first
#define se second
#define pb push_back
#define _USE_MATH_DEFINES 
/* M_PI */
#define SetLength2(a, n, t) a=((t*) calloc(n, sizeof(t))) + (n)/2

const int maxN = 2e5 + 11;
const LL oo = 1e17 + 11;

int tcases = 1;

int L,R,res = 0;

class{
    public : 
    LL powmod(LL x,LL y,LL n){
        LL rr = 1;
        while(y){
            if(y & 1) rr = rr * x % n;
            x = x * x % n;
            y >>= 1;
        }
        return rr;
    }
    pi factor(LL n){
        int m = 0;
        while(!(n & 1)){
            ++m;
            n >>= 1;
        }
        return mp(m,n);
    }

    bool check(LL n,LL s,LL d,LL a){
        LL x = powmod(a,d,n);
        if(x == 1) return 1;
        for(;s; s--){
            if(x == n - 1) return 1;
            x = x * x % n;
        }
        return 0;
    }
    
    bool isPrime(LL n){
        if(n < 5) return n == 2 || n == 3;
        if(n % 2 == 0 || n % 3 == 0) return 0;
        pi ft = factor(n - 1);
        return check(n,ft.fi,ft.se,2) && check(n,ft.fi,ft.se,3);
    }
} MillerRabin;

vector <int> factorization;
vector <int> divisor[1234];

void init(){
    REP(i,2,1234){
        int x = i;
        for(int j = 2; j * j <= x; ++j) if(x % j == 0){
            while(x % j == 0){
                divisor[i].pb(j);
                x /= j;
            }
        }
        if(x > 1) divisor[i].pb(x);
    }
}

LL _next(LL x,int n){
    return (x * x + 1) % n;
}

LL __gcd(LL x,LL y){
    return y == 0 ? x : __gcd(y,x % y);
}

int find_factor(int n){
    LL x = rand() % n,y = x,p = 1;
    do{
        x = _next(x,n);
        y = _next(_next(y,n),n);
        p = __gcd(llabs(x - y),n);
    }while(p == 1);
    return p;
}
void RHO(int n){
    if(n < 1234){
        factorization.insert(factorization.end(),divisor[n].begin(),divisor[n].end());
        return ;
    }
    if(MillerRabin.isPrime(n)){
        factorization.pb(n);
        return ;
    }
    int p = 0;
    while(p == 0 || p == n){
        p = find_factor(n);
    }
    RHO(p);
    RHO(n/p);
}

int n,k;
void testcase(){
    init();
    scanf("%d%d",&n,&k);
    RHO(n);
    if((int)factorization.size() < k) puts("-1");
    else{
        while((int)factorization.size() > k){
            int x = factorization.back();
            factorization.pop_back();
            factorization.back() *= x;
        }
        for(int x : factorization) printf("%d ",x);
    }

}

int main(){
    
    FOR(i,1,tcases) testcase();

    return 0;
}
