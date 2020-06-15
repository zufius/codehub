// https://codeforces.com/contest/319/problem/C
// LiChaoTree & coordinate compression
// choosing the right set of values for LiChaoTree is really crucial

#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <time.h>
#include <set>

using namespace std;

const int N = 1e5 + 123;
const long long oo = 5e18 + 123;
const long long mod = 1e9 + 7;

typedef pair<int,int> pi;
#define mp make_pair
#define getSz(x) ((x).size())

int n,m;
long long a[N],d[N],dp[N];
int times = 0;

struct line{
    long long a,b;
    line(long long _x = 0,long long _y = 0) : a(_x),b(_y){}
    long long val(long long x){
        return a * x + b;
    };
};

struct LiChaoTree{
    line f[N * 4];

    void add(int k,int l,int r,line ll){
        if(!f[k].a){
            f[k] = ll;
            return ;
        }
        bool left = ll.val(a[l]) < f[k].val(a[l]);
        if(l + 1 >= r){
            if(left){
                f[k] = ll;
            }
            return ;
        }
        int m = (l + r) >> 1;
        bool mid = ll.val(a[m]) < f[k].val(a[m]);
        if(mid){
            swap(ll,f[k]);
        }
        if(left != mid) add(k << 1,l,m,ll);
        else add(k << 1 | 1,m,r,ll);
    }
    long long getmin(int k,int l,int r,long long x){
        long long rr = !f[k].a ? oo : f[k].val(x);
        if(l + 1 >= r) return rr;
        int m = (l + r) >> 1;
        if(x < a[m]) return min(rr,getmin(k << 1,l,m,x));
        return min(rr,getmin(k << 1 | 1,m,r,x));
    }
} LCT; 

void testcase(){
    cin >> n;
    for(int i = 1; i <= n; ++i) cin >> a[i];
    m = a[n];
    for(int i = 1; i <= n; ++i){
        cin >> d[i];
    }
    a[n + 1] = 1e9 + 123;

    dp[1] = 0;
    
    for(int i = 2; i <= n; ++i){
        times = i - 1;
        LCT.add(1,1,n + 1,line(d[i - 1],dp[i - 1]));
        dp[i] = LCT.getmin(1,1,n + 1,a[i]);
    }

    cout << dp[n];
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
