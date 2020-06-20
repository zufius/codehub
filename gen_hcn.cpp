// highly composite numbers
// There're 156 hcn less than 1e18

#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <time.h>
#include <set>

using namespace std;
using i128 = __int128_t;

const int N = 5e5 + 123;
const long long oo = 1e18;

typedef pair<int,int> pi;
#define mp make_pair
#define getSz(x) ((x).size())
#define SetLength2(a, n, t) a=((t*) calloc(n, sizeof(t))) + (n)/2

int n,m;
vector <int> primes;
vector <pair<long long,long long> > res;

void build(int i = 0,long long val = 1,long long cdiv = 1,int last = 60){
    if(i >= primes.size()){
        res.push_back(mp(val,cdiv));
        return ;
    }
    i128 tmp = val;
    for(int j = 0; j <= last; ++j){
        tmp *= (j <= 0 ? 1 : primes[i]);
        if(tmp > oo) return ;
        build(i + 1,tmp,cdiv * (j + 1),j);
    }
}
void testcase(){
    for(int i = 2; i <= 55; ++i){
        bool c = 1;
        for(int j = 2; j * j <= i; ++j) if(i % j == 0) c = 0;
        if(c){
            primes.push_back(i);
        }
    }
    build();
    sort(res.begin(),res.end());
    long long maxdiv = 0;
    for(int i = 0; i < res.size(); ++i){
        auto pp = res[i];
        if(pp.second <= maxdiv) continue;
        cout << pp.first << " ~> " << pp.second << "\n";
        maxdiv = pp.second;
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
