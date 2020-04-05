// https://codeforces.com/group/FLVn1Sc504/contest/274707/problem/D
// https://vn.spoj.com/problems/TWOSAT

#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>

using namespace std;

#define SetLength2(a, n, t) a=((t*) calloc(n, sizeof(t))) + (n)/2

const int N = 1e5 + 123;
const int oo = 1e9 + 7;

namespace twosat{
    int n,times = 0;
    int *color,*num,*low;
    bool failed = 0;
    vector <int> *e,vt;

    void init(int _n){
        n = _n;
        SetLength2(color,2*n + 11,int);
        SetLength2(num,2*n + 11,int);
        SetLength2(low,2*n + 11,int);
        SetLength2(e,2*n + 11,vector<int>);
    }

    void newOr(int x,int y){
        e[-x].push_back(y);
        e[-y].push_back(x);
    }

    void setcolor(int u,int x){
        if(color[u] == (x^3)) failed = 1; else color[u] = x; // == has a higher precendence than ^
        if(color[-u] == x) failed = 1; else color[-u] = x^3;
    }
    
    void tarjan(int u){
        vt.push_back(u);
        num[u] = low[u] = ++times;
        for(int v : e[u]){
            if(num[v]) low[u] = min(low[u],num[v]);
            else{
                tarjan(v);
                low[u] = min(low[u],low[v]);
            }
            if(color[v] == 1) setcolor(u,1);
        }
        if(low[u] == num[u]){
            int v = 0;
            if(color[u] == 0) setcolor(u,2);
            do{
                v = vt.back(); vt.pop_back();
                setcolor(v,color[u]);
                num[v] = low[v] = oo;
            }while(v != u);
        }
    }

    void run(){
        for(int i = 1; i <= n; ++i){
            if(!num[i]) tarjan(i);
            if(!num[-i]) tarjan(-i);
        }
        if(failed) cout << "NO";
        else{
            cout << "YES\n";
            int k = 0;
            for(int i = 1; i <= n; ++i) if(color[i] == 2) ++k;
            cout << k << "\n";
            for(int i = 1; i <= n; ++i) if(color[i] == 2) cout << i << " ";
        }
    }
}

int n,m;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie();
    cout.tie();

    freopen("twosat.inp","r",stdin);
    freopen("twosat.out","w",stdout);
    
    cin >> m >> n;
    twosat::init(n);

    for(int i = 1; i <= m; ++i){
        int x,y;
        cin >> x >> y;
        twosat::newOr(x,y);
    }

    twosat::run();

    return 0;
}
