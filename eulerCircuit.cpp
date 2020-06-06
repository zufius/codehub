//https://vn.spoj.com/problems/NKPOS/

#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <time.h>
#include <set>
#include <unordered_map>
#include <stack>

using namespace std;

const int N = 5e5 + 123;

typedef pair<int,int> pi;
#define mp make_pair
#define getSz(x) ((x).size())

int n,m,w[N];

class cmp{
    public:
    size_t operator ()(const pi&pp) const{
        return (long long)pp.first * N + pp.second;
    }
};

unordered_map <pi,int,cmp> f;
vector <int> e[N];
stack <int> S;

void testcase(){
    cin >> n >> m;
    for(int i = 1; i <= n; ++i){
        cin >> w[i];
    }
    for(int i = 1; i <= m; ++i){
        int x,y;
        cin >> x >> y;
        e[x].push_back(y);
        e[y].push_back(x);
        f[mp(x,y)] = f[mp(x,y)] + 1;
        f[mp(y,x)] = f[mp(x,y)];
    }

    cout << m << "\n";
    // check if all vertices have deg = 2k, but it's not necessary in this problem
    S.push(1);

    while(S.size()){
        int u = S.top();
        while(e[u].size() && f[mp(u,e[u].back())] <= 0) e[u].pop_back();
        if(e[u].size()){
            int v = e[u].back();
            --f[mp(u,v)];
            --f[mp(v,u)];
            S.push(v);
        }else{
            cout << u << " ";
            S.pop();
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
