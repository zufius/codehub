// https://codeforces.com/contest/776/problem/D
#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <time.h>
#include <set>

using namespace std;

const int N = 5e5 + 123;
const int oo = 1e9 + 123;
const long long mod = 1e9 + 7;

typedef pair<int,int> pi;
#define mp make_pair
#define getSz(x) ((x).size())
#define SetLength2(a, n, t) a=((t*) calloc(n, sizeof(t))) + (n)/2

int n,m;
bool a[N];
vector <int> S[N];

struct TWOSAT{
    vector <int> *e,*re,ver;
    int *s,*comp,n,total = 0;
    bool *used;

    void initialize(int x){
        n = x;
        SetLength2(s,2 * n + 11,int);
        SetLength2(comp,2 * n + 11,int);
        SetLength2(e,2 * n + 11,vector<int>);
        SetLength2(re,2 * n + 11,vector<int>);
        SetLength2(used,2 * n + 11,bool);
        for(int i = -n; i <= n; ++i) s[i] = comp[i] = used[i] = 0;
    }
    void newOr(int x,int y){
        e[-y].push_back(x);
        e[-x].push_back(y);
        re[x].push_back(-y);
        re[y].push_back(-x);
    }
    void newInfer(int x,int y){
        newOr(-x,y);
    }
    void newEqual(int x,int y){
        newInfer(x,y);
        newInfer(-x,-y);
    }
    void dfs(int u){
        used[u] = 1;
        for(int v : e[u]) if(!used[v]) dfs(v);
        ver.push_back(u);
    }
    void dfs2(int u){
        comp[u] = total;
        for(int v : re[u]) if(!comp[v]) dfs2(v);
    }
    bool find2SAT(){
        for(int i = 1; i <= n; ++i){
            if(!used[i]) dfs(i);
            if(!used[-i]) dfs(-i);
        }
        for(int i = ver.size() - 1; i >= 0; --i){
            int u = ver[i];
            if(!comp[u]){
                ++total;
                dfs2(u);
            }
        }
        for(int i = 1; i <= n; ++i) if(comp[i] == comp[-i]){
            return false;
        }
        return true;
    }
} twosat;

void testcase(){
    cin >> n >> m;
    for(int i = 1; i <= n; ++i) cin >> a[i];
    for(int i = 1; i <= m; ++i){
        int k;
        cin >> k;
        for(int j = 1; j <= k; ++j){
            int x;
            cin >> x;
            S[x].push_back(i);
        }
    }
    twosat.initialize(m);

    for(int i = 1; i <= n; ++i){
        int x = S[i][0],y = S[i][1];
        if(a[i]) twosat.newEqual(x,y);
        else twosat.newEqual(-x,y);
    }

    cout << (twosat.find2SAT() ? "YES" : "NO");
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
