// Dsu with rollbacks - problem 2 VOI 2020
// https://codeforces.com/group/FLVn1Sc504/contest/266446/problem/B

#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <time.h>
#include <set>

using namespace std;

const int N = 5e4 + 123;
const int oo = 1e9 + 123;

typedef pair<int,int> pi;
#define mp make_pair
#define getSz(x) ((x).size())

int n,m,s,t,m1 = 0,m2 = 0,res = oo * 2;

struct Edge{
    int u,v,c;

    void input(){
        cin >> u >> v >> c;
    }

    bool operator <(const Edge& x) const{
        return c < x.c;
    }

} a[N],b[N];

struct dsu_save{
    int u,ranku,v,rankv;
    bool united = 0;
    dsu_save(){}
    dsu_save(int x,int rankx,int y,int ranky) : u(x),ranku(rankx),v(y),rankv(ranky){}
};

struct Dsu_with_rollbacks{
    int rank[N],p[N];
    vector <dsu_save> queries;

    void init(){
        for(int i = 1; i <= n; ++i){
            p[i] = i;
            rank[i] = 1;
        }
    }

    int find(int u){
        return (p[u] == u) ? u : find(p[u]);
    }

    void unite(int x,int y){
        x = find(x);
        y = find(y);
        if(rank[x] > rank[y]) swap(x,y);
        dsu_save tmp(x,rank[x],y,rank[y]);
        if(x != y){
            tmp.united = 1;
            p[x] = y;
            if(rank[x] == rank[y]) ++rank[y];
        }
        queries.push_back(tmp);
    }

    void rollback(){
        if(queries.empty()) return ;
        dsu_save tmp = queries.back();
        queries.pop_back();
        if(!tmp.united) return ;
        int u = tmp.u,v = tmp.v;
        p[u] = u;
        rank[u] = tmp.ranku;
        rank[v] = tmp.rankv;
    }
} Dsu;

void solve(int x,int y,int l,int r){
    if(x > y) return ;
    //cout << "Solve " << x << " -> " << y << " => ["<<l<<","<<r<<"]" << endl;
    int mid = (x + y) >> 1,fmid = r;
    for(int i = x; i <= mid; ++i) Dsu.unite(a[i].u,a[i].v);

    for(int i = l; i <= r; ++i){
        Dsu.unite(b[i].u,b[i].v);
        if(Dsu.find(s) == Dsu.find(t)){
            fmid = i;
            break;
        }
    }

    if(Dsu.find(s) == Dsu.find(t)){
        res = min(res,a[mid].c + b[fmid].c);
    }

    for(int i = l; i <= fmid; ++i) Dsu.rollback();

    solve(mid + 1,y,l,fmid);

    for(int i = x; i <= mid; ++i) Dsu.rollback();

    for(int i = l; i < fmid; ++i){
        Dsu.unite(b[i].u,b[i].v);
    }

    solve(x,mid - 1,fmid,r);

    for(int i = l; i < fmid; ++i) Dsu.rollback();
}

void testcase(){
    cin >> n >> m >> s >> t;
    for(int i = 1; i <= m; ++i){
        int k;
        cin >> k;
        if(k == 1) a[++m1].input();
        else b[++m2].input();
    }
    a[++m1] = {1,1,0};
    b[++m2] = {1,1,0};

    sort(a + 1,a + 1 + m1);
    sort(b + 1,b + 1 + m2);

    /*cout << m1 << " / " << m2 << endl;
    for(int i = 1; i <= m1; ++i){
        cout << a[i].u << " " << a[i].v << " " << a[i].c << endl;
    }
    cout << "\n";
    for(int i = 1; i <= m2; ++i){
        cout << b[i].u << " " << b[i].v << " " << b[i].c << endl;
    }
    cout << "\n";*/

    Dsu.init();

    solve(1,m1,1,m2);

    cout << res;
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie();
    cout.tie();

    freopen("bus.inp","r",stdin);
    freopen("bus.out","w",stdout);

    // main program here

    int tcase = 1;
    //cin >> tcase;

    for(int i = 1; i <= tcase; ++i) testcase();

    // 

    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    
    return 0;
}
