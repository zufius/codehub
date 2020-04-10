// https://codeforces.com/contest/1080/problem/F

#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>

using namespace std;

#define pi pair<int,int>
#define pii pair<pi,int>
#define mp make_pair
#define all(x) x.begin(),x.end()

const int N = 3e5 + 123;
const int oo = 1e9 + 123;

int n,m,k;
vector <pii> segments;

namespace PersistentIT{
    int head[N],nodes = 0;
    struct{
        int fmin,left,right;
    } seg[N * 4];
    
    int build(int l,int r){
        int k = ++nodes;
        seg[k].fmin = oo;
        if(l < r){
            int mid = (l + r) >> 1;
            seg[k].left = build(l,mid);
            seg[k].right = build(mid + 1,r);
        }
        return k;
    }

    int update(int k,int l,int r,int R,int p){
        if(l > p || r < p) return k;
        int x = ++nodes;
        if(l == r){
            seg[x].fmin = min(seg[k].fmin,R);
            return x;
        }
        int mid = (l + r) >> 1;
        seg[x].left = update(seg[k].left,l,mid,R,p);
        seg[x].right = update(seg[k].right,mid + 1,r,R,p);
        seg[x].fmin = max(seg[seg[x].left].fmin,seg[seg[x].right].fmin);
        return x;
    }

    void initialization(){
        head[0] = build(1,n);
        sort(all(segments));
        int prevHead = head[0];
        for(int i = (int)segments.size() - 1; i >= 0; --i){
            pii sm = segments[i];
            int l = sm.first.first,r = sm.first.second,p = sm.second;
            head[i + 1] = PersistentIT::update(prevHead,1,n,r,p);
            prevHead = head[i + 1];
        }
    }

    int find(int k,int l,int r,int L,int R){
        if(l > R || L > r) return -oo;
        if(L <= l && r <= R) return seg[k].fmin;
        int mid = (l + r) >> 1;
        return max(find(seg[k].left,l,mid,L,R),find(seg[k].right,mid + 1,r,L,R));
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie();
    cout.tie();

    freopen("a.inp","r",stdin);
    freopen("a.out","w",stdout);

    cin >> n >> m >> k;
    for(int i = 1; i <= k; ++i){
        int l,r,p;
        cin >> l >> r >> p;
        segments.push_back(mp(mp(l,r),p));
    }

    PersistentIT::initialization();

    for(int i = 1; i <= m; ++i){
        int a,b,x,y;
        cin >> a >> b >> x >> y;
        int v = upper_bound(all(segments),mp(mp(x - 1,oo),oo)) - segments.begin();
        if(v < 0) cout << "no\n";
        else{
            int vmin = PersistentIT::find(PersistentIT::head[v + 1],1,n,a,b);
            if(vmin > y) cout << "no\n";
            else cout << "yes\n";
        }
        cout.flush();
    }

    return 0;
}
