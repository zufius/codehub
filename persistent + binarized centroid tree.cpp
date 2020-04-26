// https://codeforces.com/contest/757/problem/G
#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <set>
#include <iterator>
#include <time.h>
#include <stdlib.h>

using namespace std;

#define sz(x) (int)x.size()
#define pi pair<int,int>
#define pii pair<int,long long>
#define mp make_pair

const int N = 4e5 + 123;
const long long mod = (1LL << 30) - 1;

int n,m,q;
int a[N],pa[N][20],h[N];
long long d[N];
vector <pi> e[N],ce[N];

int fastread(){
    char c;
    int r = 0;
    while(c = getchar(),c < '0' || c > '9');
    r = c - '0';
    while(c = getchar(),c >= '0' && c <= '9') r = r * 10 + (c - '0');
    return r;
}

void dfs(int u,int p = 0){
    if(u > 1){
        for(int i = 0; i < e[u].size(); ++i) if(e[u][i].first == p){
            e[u][i] = e[u].back();
            break;
        }
        e[u].pop_back();
    }
    // now e[u] only contains children of u
    for(int i = 0; i < e[u].size(); ++i) if(e[u][i].first != p) dfs(e[u][i].first,u);
}
void updateEdgesList(int u,int p = 0){
    for(int i = 0; i < ce[u].size(); ++i) if(ce[u][i].first != p){
        ce[ce[u][i].first].push_back(mp(u,ce[u][i].second));
        updateEdgesList(ce[u][i].first,u);
    }
}
void binarize(){
    for(int u = 1; u <= n; ++u){
        // u = 1 -> there must be at most 3 child nodes (from the original tree)
        // u > 1 -> there must be at most 2 child node
        int nchild = 3 - (u > 1);
        if(sz(e[u]) <= nchild) ce[u] = e[u];
        else{
            int k = sz(e[u]) - 1;
            for(int i = 1; i < nchild; ++i){
                ce[u].push_back(e[u][k--]);
            }
            int curVertex = 0,prev = 0;
            while(k >= 0){
                curVertex = ++m;
                ce[curVertex].push_back(e[u][k--]);
                if(prev) ce[curVertex].push_back(mp(prev,0));
                prev = curVertex;
            }
            ce[u].push_back(mp(curVertex,0));
        }
    }
    updateEdgesList(1);
}

void dfs2(int u,int p = 0){
    pa[u][0] = p;
    h[u] = h[p] + 1;
    for(int i = 0; i < ce[u].size(); ++i){
        if(ce[u][i].first != p){
            d[ce[u][i].first] = d[u] + ce[u][i].second;
            dfs2(ce[u][i].first,u);
        }
    }
}

int lca(int u,int v){
    if(h[u] < h[v]) swap(u,v);
    for(int i = 19; i >= 0; --i) if(h[pa[u][i]] >= h[v]) u = pa[u][i];
    if(u == v) return u;
    for(int i = 19; i >= 0; --i) if(pa[u][i] != pa[v][i]) u = pa[u][i],v = pa[v][i];
    return pa[u][0];
}

long long dist(int u,int v){
    int k = lca(u,v);
    return d[u] + d[v] - (d[k] << 1);
}

void buildLCA(){
    dfs2(1);
    for(int j = 1; j < 20; ++j)
        for(int i = 1; i <= m; ++i) pa[i][j] = pa[pa[i][j - 1]][j - 1];
}

namespace Centroid{
    int bsize[N],parentCenNode[N],childvertices[N][3],perNodes[16678910][3],root[N],V[N],rootCentroid = 0;
    long long g[16678910],preD[N][20];
    bool Cen[N];
    pii f[16678910]; // total distance from u to its descendants on centroid tree

    void dfs_centroid(int u,int p = 0){
        bsize[u] = 1;
        for(int i = 0; i < ce[u].size(); ++i) if(!Cen[ce[u][i].first] && ce[u][i].first != p){
            dfs_centroid(ce[u][i].first,u);
            bsize[u] += bsize[ce[u][i].first];
        }
    }

    int find_centroid(int u,int total,int p = 0){
        for(int i = 0; i < ce[u].size(); ++i) if(!Cen[ce[u][i].first] && ce[u][i].first != p && bsize[ce[u][i].first] >= (total >> 1)) return find_centroid(ce[u][i].first,total,u);
        return u;
    }
    void build(int u = 1,int p = 0){
        dfs_centroid(u);
        int cen = find_centroid(u,bsize[u]);
        Cen[cen] = 1;
        if(p){
            parentCenNode[cen] = p;
            for(int i = 0; i < 3; ++i) if(!childvertices[p][i]){
                childvertices[p][i] = cen;
                break;
            }
        }else rootCentroid = cen;
        for(int i = 0; i < ce[cen].size(); ++i) if(!Cen[ce[cen][i].first]) build(ce[cen][i].first,cen);
    }
    void newPersistentTree(int curTree,int u){ // make node u active in treeID'th persistent centroid tree
        int x = u,k = 0;
        while(x){
            V[++k] = x;
            //int pnode = persistentNodeSet::get(prevTree,x);
            //f[++m] = mp(f[pnode].first + 1,f[pnode].second + dist(u,x));
            //persistentNodeSet::add(curTree,x,m);
            x = parentCenNode[x];
            //if(x) g[m] = g[pnode] + dist(u,x);
        }
        int node1 = root[curTree - 1];
        for(int i = k; i; --i){
            ++m;
            for(int j = 0; j < 3; ++j) perNodes[m][j] = perNodes[node1][j];
            if(node1 == root[curTree - 1]) root[curTree] = m;
            else if(i < k) g[m] = g[node1] + preD[u][i]; // dist(u,V[i + 1]);
            f[m] = mp(f[node1].first + 1,f[node1].second + preD[u][i - 1]); // + dist(u,V[i])
            if(i > 1) for(int j = 0; j < 3; ++j) if(V[i - 1] == childvertices[V[i]][j]){
                node1 = perNodes[node1][j];
                perNodes[m][j] = m + 1;
            }
        }
    }

    long long getTotalDist(int treeId,int v){
        if(treeId <= 0) return 0;
        int x = v,k = 0;
        while(x){
            V[++k] = x;
            x = parentCenNode[x];
        }
        int curNode = root[treeId];
        long long rr = 0;
        for(int i = k; i; --i){
            if(i <= 1) rr += f[curNode].second;
            else{
                int nextNode = 0;
                for(int j = 0; j < 3; ++j) if(childvertices[V[i]][j] == V[i - 1]) nextNode = perNodes[curNode][j];
                pii tmp = mp(f[curNode].first - f[nextNode].first,f[curNode].second - g[nextNode]);
                rr += preD[v][i - 1] * tmp.first + tmp.second;
                curNode = nextNode;
            }
        }
        /*int x = parentCenNode[v],prevNode = persistentNodeSet::get(treeId,v);
        long long rr = f[prevNode].second;
        while(x){
            int pnode = persistentNodeSet::get(treeId,x);
            pii tmp = mp(f[pnode].first - f[prevNode].first,f[pnode].second - g[prevNode]);
            rr += dist(v,x) * tmp.first + tmp.second;
            x = parentCenNode[x];
            prevNode = pnode;
        }*/
        return rr;
    }

    int initPersistentTree(int u){
        for(int i = 0; i < 3; ++i) if(childvertices[u][i]){
            perNodes[u][i] = initPersistentTree(childvertices[u][i]);
        }
        return u;
    }
    void init(){
        for(int i = 1; i <= m; ++i){
            int x = i,k = 0;
            while(x){
                preD[i][k++] = dist(i,x);
                x = parentCenNode[x];
            }
        }
        root[0] = initPersistentTree(rootCentroid);
        for(int i = 1; i <= n; ++i){
            newPersistentTree(i,a[i]);
        }
    }

    long long query1(int l,int r,int v){
        return getTotalDist(r,v) - getTotalDist(l - 1,v);
    }
    void query2(int x){
        // remove old nodes
        swap(a[x],a[x + 1]);
        newPersistentTree(x,a[x]);
        newPersistentTree(x + 1,a[x + 1]);
    }
};

int main(){
    #ifndef ONLINE_JUDGE
        freopen("a.inp","r",stdin);
        freopen("a.out","w",stdout);
    #else
        // online submission
    #endif

    m = n = fastread(); q = fastread();
    for(int i = 1; i <= n; ++i) a[i] = fastread();
    for(int i = 1; i < n; ++i){
        int u,v,w;
        u = fastread(); v = fastread(); w = fastread();
        e[u].push_back(mp(v,w));
        e[v].push_back(mp(u,w));
    }
 
    dfs(1);
 
    binarize(); // after binarized, each node in current tree has degree <= 3
 
    buildLCA();
 
    Centroid::build(); // build centroid tree from the binarized tree
    Centroid::init();

    // answer queries
    long long lastAns = 0;
    for(int i = 1; i <= q; ++i){
        int t,b,c,d;
        t = fastread(); b = fastread();
        b ^= lastAns;
        if(t == 1){
            c = fastread(); d = fastread();
            c ^= lastAns;
            d ^= lastAns;
            lastAns = Centroid::query1(b,c,d);
            printf("%lli\n",lastAns);
        }else{
            Centroid::query2(b);
        }
        lastAns &= mod;
    }

    return 0;
}
