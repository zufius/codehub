//https://vn.spoj.com/problems/MATCH1/
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
int Match[N],g[N],times = 0;
vector <int> e[N];

bool dfs(int u){
    g[u] = times;
    for(int v : e[u]){
        if(!Match[v] || (g[Match[v]] != times && dfs(Match[v]))){
            Match[u] = v;
            Match[v] = u;
            return 1;
        }
    }
    return 0;
}
void testcase(){
    cin >> m >> n;
    int x,y;
    while(cin >> x >> y){
        e[x].push_back(y + m);
    }
    for(int i = 1; i <= m; ++i){
        ++times;
        dfs(i);
    }
    int rr = 0;
    for(int i = 1; i <= m; ++i) if(Match[i]) ++rr;
    cout << rr << "\n";
    for(int i = 1; i <= m; ++i){
        if(Match[i]){
            cout << i << " " << Match[i] - m << "\n";
        }
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
