// https://tlx.toki.id/problems/sg-noi-2016/C/submissions/644003
// NOI singapore 2016 problem C
// finding MIS on DAG -> create two copies of the graph, if there exists edge (u,v) on the original graph -> add edge (u,v') to the new bipartie graph
// on bipartie : MIS (max independent set) = n - MVC (min vertex cover) = n - MCBM (maximum cardinality bipartite matching)
// 
#include <bits/stdc++.h>

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

const int N = 511;
const LL oo = 1e17 + 11;

int tcases = 1;

int n,m;
pi a[N];
int s[N];
bool f[N][N];
vector <int> e[N];

struct MCBM{
    vector <int> e[N];
    int mx[N],my[N],trace[N],g[N],times = 0;
    
    bool dfs(int u){
        g[u] = times;
        for(int v : e[u]) if(!my[v] || (g[my[v]] != times && dfs(my[v]))){
            mx[u] = v;
            my[v] = u;
            return 1;
        }
        return 0;
    }
    int findMCBM(){
        int res = 0;
        FOR(i,1,n) if(!mx[i]) { // important !!!
            ++times;
            dfs(i);
        }
        FOR(i,1,n) if(mx[i]) ++res;
        return res;
    }
} biparG;

void testcase(){
    cin >> n;
    FOR(i,1,n){
        cin >> a[i].fi >> a[i].se >> s[i];
    }
    FOR(i,1,n){
        FOR(j,1,n) if(a[i].se < a[j].se && max(abs(a[i].fi - a[j].fi),abs(a[i].se - a[j].se)) <= max(s[i],s[j])){
            f[i][j] = 1;
        }
    }
    FOR(k,1,n){
        FOR(i,1,n)
        FOR(j,1,n) if(f[i][k] && f[k][j]) f[i][j] = 1;
    }
    FOR(i,1,n){
        FOR(j,1,n) if(f[i][j]) biparG.e[i].pb(j);
    }

    // find MVC - minimum vertex cover

    int mvc = biparG.findMCBM();
    int mis = n - mvc;

    if(mis >= n){
        cout << -1 << "\n";
    }else cout << mis + 1 << "\n";
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie();
    cout.tie();

    //freopen(taskname".INP","r",stdin); freopen(taskname".OUT","w",stdout);
    
    //cin >> tcases;
    
    FOR(i,1,tcases) testcase();

    //
    
    return 0;
}
