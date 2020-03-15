#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

#define FOR(i,l,r) for(int i = l; i <= r; ++i)
#define REP(i,l,r) for(int i = l; i < r; ++i)
#define mp make_pair

const int maxN = 1e3 + 123;
const long long oo = 1e18 + 123;

namespace DinitzFlow{
    vector <int> a[maxN];
    pair<int,long long> e[maxN * maxN];
    long long flow[maxN * maxN],d[maxN];

    int n = 0,m = 0,s = 0,t = 0,times = 0,G[maxN];
    long long maxflow = 0;
    queue <int> Q;
    
    bool bfs(){
        while(!Q.empty()) Q.pop();
        Q.push(s);
        FOR(i,1,n) d[i] = oo;
        d[s] = 0;
        while(!Q.empty()){
            int u = Q.front(); Q.pop();
            for(auto j : a[u]){
                int v = e[j].first;
                if(d[v] >= oo && flow[j] < e[j].second){
                    d[v] = d[u] + 1;
                    if(v == t) return 1;
                    Q.push(v);
                }
            }
        }
        return 0;
    }

    long long dfs(int u,long long curFlow = oo){
        if(u == t) return curFlow;
        G[u] = times;
        for(int j : a[u]){
            int v = e[j].first;
            if(d[v] == d[u] + 1 && flow[j] < e[j].second && G[v] != times){
                if(long long x = dfs(v,min(curFlow,e[j].second - flow[j]))){
                    flow[j] += x;
                    flow[j ^ 1] -= x;
                    return x;
                }
            }
        }
        return 0;
    }

    void run(){
        while(bfs()){
            while(long long x = (++times,dfs(s,oo))) maxflow += x;
        }
        cout << maxflow;
    }

    void input(){
        cin >> n >> m >> s >> t;
        int k = 0;
        FOR(i,1,m){
            int u,v,c;
            cin >> u >> v >> c;
            a[u].push_back(k);
            e[k++] = mp(v,c);
            a[v].push_back(k);
            e[k++] = mp(u,0);
        }
    }
}

int main(){

    ios_base::sync_with_stdio(false);
    cin.tie();
    cout.tie();

    DinitzFlow::input();
    DinitzFlow::run();

    return 0;
}
