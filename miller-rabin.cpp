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

//https://www.spoj.com/problems/FACT1/

#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <time.h>
#include <set>
 
using namespace std;
using u128 = __uint128_t;
 
const int N = 5e5 + 123;
const int oo = 1e9 + 123;
const u128 mod = 1e9 + 7;
 
typedef pair<int,int> pi;
#define mp make_pair
#define LL u128
#define getSz(x) ((x).size())
#define SetLength2(a, n, t) a=((t*) calloc(n, sizeof(t))) + (n)/2
 
int n,m;
 
namespace MillerRabinTest{
    vector <LL> smallPrime,witness;
 
    void init(){
 
    }
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
        for(LL p : smallPrime){
            if(x == p) return 1;
            if(x % p == 0) return 0;
        }
        pair<LL,LL> ft = factor(x - 1);
        for(LL a : witness) if(!check(x,ft.first,ft.second,a)) return 0;
        return 1;
    }
};
 
void refine(vector <pair<u128,int> > &f){
    sort(f.begin(),f.end());
    int j = 0;
    for(int i = 1; i < f.size(); ++i){
        if(f[i].first == f[j].first){
            f[j].second += f[i].second;
        }else{
            f[++j] = f[i];
        }
    }
    while(f.size() > j + 1) f.pop_back();
}
 
vector <pair<u128,int> > factors,smallFactors[1234];
 
u128 f(u128 a,u128 c,u128 mod){
    return ((u128)a * a + c) % mod;
}
u128 gcd(u128 x,u128 y){
    return y == 0 ? x : gcd(y,x % y);
}
u128 next(u128 a,u128 x){
    return ((u128)a * a + 1) % x;
}
u128 find_factor(u128 x){
    u128 a = rand() % x,b = a,times = 0,g = 1;
    while(g == 1 && times < 3456){
        ++times;
        a = next(a,x);
        b = next(next(b,x),x);
        g = gcd(llabs(a - b),x);
    }
    return g;
}
void RHO(u128 x){
    if(x < 1024){
        factors.insert(factors.end(),smallFactors[x].begin(),smallFactors[x].end());
        return ;
    }
    if(MillerRabinTest::miller(x)){
        factors.push_back(mp(x,1));
        return ;
    }
    u128 d = 1;
    while(d == 1 || d == x){
        d = find_factor(x);
    }
    RHO(d);
    RHO(x/d);
}
void factorize(u128 x){
    factors.clear();
    RHO(x);
}
bool readInt(u128 &x){
    string s;
    cin >> s;
    if(s == "0") return 0;
    x = 0;
    for(int i = 0; i < s.size(); ++i){
        x = x * 10 + (s[i] - '0');
    }
    return 1;
}
string printInt(u128 x){
    string s;
    while(x > 0){
        s = (char)('0' + x % 10) + s;
        x /= 10;
    }
    return s;
}
void testcase(){
    for(int i = 2; i < 1024; ++i){
        int d = i;
        for(int j = 2; j * j <= d; ++j) if(d % j == 0){
            int k = 0;
            while(d % j == 0){
                d /= j;
                ++k;
            }
            smallFactors[i].push_back(mp(j,k));
        }
        if(i <= 41 && smallFactors[i].empty()){
            MillerRabinTest::witness.push_back(i);
        }
        if(d > 1) smallFactors[i].push_back(mp(d,1));
    }
    for(int p = 2; p <= 41; ++p) if(smallFactors[p].size() == 1 && smallFactors[p].back().second == 1) MillerRabinTest::witness.push_back(p);
    u128 x;
    while(readInt(x)){
        factorize(x);
        refine(factors);
        for(auto pp : factors){
            cout << printInt(pp.first) << "^"<<pp.second<<" ";
        }
        cout << "\n";
    }
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie();
    cout.tie();
 
    #ifndef ONLINE_JUDGE
        freopen("a.inp","r",stdin);
        freopen("a.out","w",stdout);
    #else
        // online submission
    #endif
 
    // main program here
 
    int tcase = 1;
    //cin >> tcase;
 
    for(int i = 1; i <= tcase; ++i) testcase();
 
    // 
 
    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    
    return 0;
} 
// n ~ 1e6 => 2 3
// n ~ 2^32 => 2 7 61 / 2 3 5 7
// n ~ 64 bit => 2 3 5 7 11 13 17 19 23 29 31 37 41
