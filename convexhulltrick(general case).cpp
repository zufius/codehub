// https://open.kattis.com/problems/joiningnetwork
#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <time.h>
#include <deque>

using namespace std;
using i128 = __int128_t;

const int N = 5e4 + 123;
const i128 oo = 9e18 + 123;
const i128 mod = 1e9 + 7;

typedef pair<i128,i128> pi;
#define mp make_pair
#define getSz(x) ((x).size())

int n,m;
i128 res = -oo;

struct Tree{
    int n;
    vector <int> e[N];
    i128 total = 0;

    void input(){
        cin >> n;
        for(int i = 1; i < n; ++i){
            int x,y;
            cin >> x >> y;
            e[x].push_back(y);
            e[y].push_back(x);
        }
    }

    int c[N]; // number of chilren in branch u
    i128 h[N],g[N];

    void dfs(int u,int p = 0){
        c[u] = 1;
        for(int v : e[u]){
            if(v == p) continue;
            dfs(v,u);
            c[u] += c[v];
            h[u] += h[v] + c[v];
            g[u] += g[v] + h[v] * 2 + c[v];
        }
    }
    void dfs2(int u,int p = 0,i128 totalH = 0,i128 totalG = 0){
        for(int v : e[u]){
            if(v == p) continue;
            totalH += h[v] + c[v];
            totalG += g[v] + h[v] * 2 + c[v];
        }
        h[u] = totalH;
        g[u] = totalG;
        for(int v : e[u]){
            if(v == p) continue;
            dfs2(v,u,totalH - h[v] - c[v] + n - c[v],(totalG - g[v] - h[v] * 2 - c[v]) + (totalH - h[v] - c[v]) * 2 + n - c[v]);
        }
    }
    void init(){
        dfs(1);
        dfs2(1);
        for(int i = 1; i <= n; ++i){
            total += g[i];
            g[i] += h[i] * 2;
        }
        total >>= 1;
    }
} A,B;

void printi128(i128 res){
    if(res < 0){
        cout << "-";
        res = -res;
    }
    vector <int> rr;
    while(res){
        rr.push_back(res % 10);
        res /= 10;
    }
    while(rr.size()){
        cout << rr.back();
        rr.pop_back();
    }
}

struct line{
    i128 a,b;
    i128 val(i128 x){
        return a * x + b;
    }
    line(){}
    line(i128 a1 = 0,i128 b1 = 0): a(a1),b(b1){}

};

struct ConvexHull{
    vector <line> S;

    i128 getmax(i128 x){
        int l = 0,r = (int)S.size() - 1;
        i128 rr = -oo;
        while(l < r){
            int mid = (l + r) >> 1;
            i128 v1 = S[mid].val(x),v2 = S[mid + 1].val(x);
            if(v1 < v2){
                rr = max(rr,v2);
                l = mid + 1;
            }else if(v1 > v2){
                rr = max(rr,v1);
                r = mid;
            }else return v1;
        }

        if(l <= r) rr = max(rr,S[l].val(x));
        return rr;
    }
    
    long double intx(line x,line y){
        return (1.0L * x.b - 1.0L * y.b) * 1.0L/(y.a - x.a);
    }

    void add(line ll){
        if(S.size() && S.back().a == ll.a){
            ll.b = max(ll.b,S.back().b);
            S.pop_back(); // this is extremely important
            // not return here, but still process this line like in other cases
        }
        int sz = S.size();
        while(sz > 1 && intx(S[sz - 2],S[sz - 1]) > intx(S[sz - 1],ll)) --sz,S.pop_back();
        S.push_back(ll);
    }

} H;

vector <line> llcontainer;

void testcase(){
    A.input(); n = A.n;
    B.input(); m = B.n;

    A.init();
    B.init();

    // convex hull trick

    for(int i = 1; i <= n; ++i){
        llcontainer.push_back(line(-A.h[i] * 2,-A.g[i] * m));
    }
    sort(llcontainer.begin(),llcontainer.end(),[&](line x,line y){return x.a < y.a;});

    for(int i = 0; i < n; ++i) H.add(llcontainer[i]);

    for(int i = 1; i <= m; ++i){
        res = max(res,-B.g[i] * A.n + H.getmax(B.h[i]));
    }

    res = -res + A.total + B.total + (i128)A.n * B.n;

    printi128(res);
    cout << "\n";
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


// deque can be accessed by index
