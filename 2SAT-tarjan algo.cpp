// https://codeforces.com/contest/1215/problem/F
// 2SAT : tarjan version
#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <time.h>
#include <stack>

using namespace std;

const int N = 4e5 + 123;
const int oo = 1e9 + 123;
const long long mod = 1e9 + 7;

typedef pair<int,int> pi;
#define mp make_pair
#define getSz(x) ((x).size())
#define SetLength2(a, n, t) a=((t*) calloc(n, sizeof(t))) + (n)/2

int n,p,k,m,c[N];
pi a[N];

namespace TWOSAT{

    vector <int> *e;
    int n,*comp,*num,*low,total = 0,times = 0;
    stack <int> S;

    void initialize(int n0){
        n = n0;
        SetLength2(e,n * 2 + 11,vector<int>);
        SetLength2(comp,n * 2 + 11,int);
        SetLength2(num,n * 2 + 11,int);
        SetLength2(low,n * 2 + 11,int);
        for(int i = -n; i <= n; ++i){
            e[i].clear();
            num[i] = low[i] = 0;
        }
    }
    void newOr(int x,int y){
        e[-x].push_back(y);
        e[-y].push_back(x);
    }
    void newInfer(int x,int y){
        newOr(-x,y);
    }
    void dfs(int u){
        S.push(u);
        num[u] = low[u] = ++times;
        for(int v : e[u]){
            if(num[v]) low[u] = min(low[u],num[v]);
            else{
                dfs(v);
                low[u] = min(low[u],low[v]);
            }
        }
        if(num[u] == low[u]){
            ++total;
            while(true){
                int v = S.top(); S.pop();
                comp[v] = total;
                num[v] = low[v] = oo;
                if(v == u) break ;
            }
        }
    }
    void solve(){
        for(int i = 1; i <= n; ++i){
            if(!num[i]) dfs(i);
            if(!num[-i]) dfs(-i);
        }
        for(int i = 1; i <= n; ++i) if(comp[i] == comp[-i]){
            cout << -1;
            return ;
        }
        int l = -1e9,r = 1e9,cnt = 0;
        for(int i = 1; i <= p; ++i){
            if(comp[i] < comp[-i]){
                ++cnt;
                l = max(l,a[i].first);
                r = min(r,a[i].second);
            }
        }
        cout << cnt << " " << l << "\n";
        for(int i = 1; i <= p; ++i){
            if(comp[i] < comp[-i]){
                cout << i << " ";
            }
        }
    }
};

bool cmp(int i,int j){
    return a[i] < a[j];
}
bool cmp2(int i,int x){
    return a[i].first <= x;
}
void testcase(){
    cin >> n >> p >> k >> m;
    TWOSAT::initialize(p * 2);
    for(int i = 1; i <= n; ++i){
        int x,y;
        cin >> x >> y;
        TWOSAT::newOr(x,y);
    }
    for(int i = 1; i <= p; ++i){
        cin >> a[i].first >> a[i].second;
        c[i] = i;
    }
    sort(c + 1,c + 1 + p,cmp);

    for(int i = 1; i <= p; ++i){
        int k = lower_bound(c + 1,c + 1 + p,a[i].second,cmp2) - c;
        if(k <= p){
            TWOSAT::newInfer(i,p + k);
        }
        if(i < p) TWOSAT::newInfer(p + i,p + i + 1);
        TWOSAT::newInfer(p + i,-c[i]);
    }

    for(int i = 1; i <= m; ++i){
        int x,y;
        cin >> x >> y;
        TWOSAT::newOr(-x,-y);
    }
    
    TWOSAT::solve();
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
