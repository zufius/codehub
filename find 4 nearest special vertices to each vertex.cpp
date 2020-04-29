// Singapore NOI 2020 - Qualification Round — Problem C : Relay Marathon
// I used dijkstra + randomize to get AC
// https://tlx.toki.id/problems/sg-noi-2020-qual

#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <time.h>
#include <queue>
#include <map>

using namespace std;

struct InputOutputStream {
    enum { SIZE = 1 << 18 | 1 };
 
    char ibuf[SIZE], *s, *t, obuf[SIZE], *oh;
 
    InputOutputStream() : s(), t(), oh(obuf) {}
 
    ~InputOutputStream() { fwrite(obuf, 1, oh - obuf, stdout); }
 
    inline char read() {
        return (s == t) && (t = (s = ibuf) + fread(ibuf, 1, SIZE, stdin)),
               s == t ? -1 : *s++;
    }
 
    template <typename T>
    inline InputOutputStream &operator>>(T &x) {
        static char c;
        static bool iosig;
        for (c = read(), iosig = false; !isdigit(c); c = read()) {
            if (c == -1) return *this;
            iosig |= c == '-';
        }
        for (x = 0; isdigit(c); c = read()) x = x * 10 + (c ^ '0');
        iosig && (x = -x);
        return *this;
    }
 
    template <typename T>
    inline InputOutputStream &operator<<(const T &x) {
        cout << x;
        return *this;
    }
} io;

const int N = 3e5 + 123;
const long long oo = 1e18 + 123;

typedef pair<int,int> pi;
typedef pair<long long,int> piLL;
typedef pair<long long,pi> candidatePair;
#define mp make_pair

int n,m,k;
bool specialVertices[N];
vector <int> w;
vector <pi> e[N];
piLL D[N][4];
int cur[N];

struct cmp{
    bool operator ()(piLL x,piLL y){
        return x > y;
    }
};
priority_queue <piLL,vector<piLL>,cmp> heap;

void dij(){ // calculate firts 4 nearest special vertices to each vertex
    for(int i = 1; i <= n; ++i) for(int j = 0; j < 4; ++j) D[i][j] = mp(oo,0);

    for(int i = 1; i <= n; ++i) if(specialVertices[i]){
        D[i][0] = mp(0,i);
        heap.push(mp(0,i));
    }

    while(heap.size()){
        piLL tmp = heap.top(); 
        heap.pop();
        int u = tmp.second;
        if(tmp.first != D[u][cur[u]].first) continue;
        int z = D[u][cur[u]].second;
        for(pi ed : e[u]){
            int v = ed.first;
            if(cur[v] >= 4) continue;
            long long newC = tmp.first + ed.second;
            bool fixed = 0;
            for(int k = 0; k < cur[v]; ++k) if(D[v][k].second == z){
                fixed = 1;
                break;
            }
            if(fixed) continue;
            int pos = -1;
            for(int k = cur[v]; k < 4; ++k) if(D[v][k].second == z){
                pos = k;
                break;
            }
            if(pos >= 0){
                if(newC < D[v][pos].first){
                    D[v][pos].first = newC;
                    sort(D[v] + cur[v],D[v] + 4);
                }else continue;
            }else{
                for(int j = cur[v]; j < 4; ++j) if(newC < D[v][j].first){
                    for(int k = 3; k > j; --k) D[v][k] = D[v][k - 1];
                    D[v][j] = mp(newC,z);
                    break;
                }
            }
            if(D[v][cur[v]].second == z){
                heap.push(mp(newC,v));
            }
        }
        ++cur[u];
        if(cur[u] < 4) heap.push(mp(D[u][cur[u]].first,u));
    }

    /*for(int i = 1; i <= n; ++i){
        cout << "F["<<i<<"] = ";
        for(int j = 0; j < 4; ++j){
            if(D[i][j].first < oo) cout << D[i][j].first << "/"<<D[i][j].second << "  ";
            else break;
        }
        cout << "\n";
    }*/
}
candidatePair f[4 * N];

int main(){
    //freopen("a.inp","r",stdin); freopen("a.out","w",stdout);

    // main program here

    io >> n >> m >> k;
    for(int i = 1; i <= m; ++i){
        int x,y,z;
        io >> x >> y >> z;
        e[x].push_back(mp(y,z));
        e[y].push_back(mp(x,z));
    }
    for(int i = 1; i <= k; ++i){
        int x;
        io >> x;
        specialVertices[x] = 1;
        w.push_back(x);
    }

    dij();
    
    long long res = oo;

    if(n <= 500){
        for(int i = 1; i <= n; ++i) if(D[i][3].first < oo){
            long long rr = 0;
            for(int j = 0; j < 4; ++j) rr += D[i][j].first;
            res = min(res,rr);
        }
        for(int i = 0; i < w.size(); ++i){
            int x = w[i];
            for(int j = i + 1; j < w.size(); ++j){
                int y = w[j];
                for(int i1 = 0; i1 < 4; ++i1){
                    int z = D[x][i1].second;
                    if(z != x && z != y)
                    for(int j1 = 0; j1 < 4; ++j1){
                        int t = D[y][j1].second;
                        if(t != x && t != y && t != z){
                            long long rr = D[x][i1].first + D[y][j1].first;
                            res = min(res,rr);
                        }
                    }
                }
            }
        }
    }else{
        /*for(int i = 1; i <= n; ++i){
            if(specialVertices[i] && i > 2){
                res = min(res,D[1][1].first + D[i][1].first);
            }
        }*/
        int nPair = 0;
        for(int i = 1; i <= n; ++i) if(specialVertices[i]){
            for(int j = 0; j < 4; ++j) if(D[i][j].first < oo){
                if(D[i][j].second > i){
                    f[++nPair] = mp(D[i][j].first,mp(i,D[i][j].second));
                }
            }else break;
        }
        sort(f + 1,f + 1 + nPair);
        //
        for(int i = 1; i <= nPair; ++i){
            int x = f[i].second.first,y = f[i].second.second;
            for(int j = 1; j <= 150 && j <= nPair; ++j) if(j != i){
                if(f[j].second.first != x && f[j].second.first != y && f[j].second.second != x && f[j].second.second != y){
                    res = min(res,f[i].first + f[j].first);
                }
            }
            for(int k = 1; k <= 150; ++k){
                int j = rand() % 234 + 151;
                if(j <= nPair)
                if(f[j].second.first != x && f[j].second.first != y && f[j].second.second != x && f[j].second.second != y){
                    res = min(res,f[i].first + f[j].first);
                }
            }
        }
    }
    io << res << "\n";

    // 

    //cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    
    return 0;
}
