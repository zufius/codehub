/* JEWELNB spoj
https://codeforces.com/group/FLVn1Sc504/contest/274814/problem/X
I got 90/100 with this algorithm*/

// lichao tree on set of lines + "Deleting elements from Data Structure" (cp-algorithms)
// or there's an alternative : IT on set of segments
// i made a mistake ...queries[z--] => this is too dangerous
#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <time.h>
#include <set>

using namespace std;

const int N = 2e5 + 123;
const long long oo = 1e18 + 123;
const int ominus = -1e9 -123;
const long long mod = 1e9 + 7;

typedef pair<int,int> pi;
#define mp make_pair
#define getSz(x) ((x).size())

int n,m;
long long res[N];

struct line{
    long long a,b;
    line(long long _x = 0,long long _y = 0) : a(_x),b(_y){}
    long long val(long long x){
        if(a == ominus && b == ominus) return -oo;
        return a * x + b;
    }
    bool operator == (const line&ll) const{
        return a == ll.a && b == ll.b;
    }
} tmp(ominus,ominus);

struct lichao_save{
    int k;
    line x;
    lichao_save(int _k = 0,line ll = tmp) : k(_k),x(ll){}
};

struct lichaotree_with_rollbacks{
    line f[N * 4];
    lichao_save queries[N * 20];
    int z = 0;

    void init(int k,int l,int r){
        f[k] = tmp;
        if(l < r){
            int mid = (l + r) >> 1;
            init(k << 1,l,mid);
            init(k << 1 | 1,mid + 1,r);
        }
    }

    int replace(int k,line newll){
        queries[++z] = lichao_save(k,f[k]);
        f[k] = newll;
        return 1;
    }
    int add(int k,int l,int r,line ll){
        if(f[k] == tmp){
            return replace(k,ll);
        }
        if(l == r){
            if(ll.val(l) > f[k].val(l)){
                return replace(k,ll);
            }
            return 0;
        }
        int mid = (l + r) >> 1;
        bool left = ll.val(l) >= f[k].val(l);
        bool m = ll.val(mid) >= f[k].val(mid);

        int total = 0;
        if(m){
            line t = f[k];
            total += replace(k,ll);
            ll = t;
        }
        if(left != m) total += add(k << 1,l,mid,ll);
        else total += add(k << 1 | 1,mid + 1,r,ll);
        return total;
    }

    long long getmax(int k,int l,int r,int x){
        long long rr = f[k].val(x);
        if(l >= r) return rr;
        int mid = (l + r) >> 1;
        if(x <= mid) return max(rr,getmax(k << 1,l,mid,x));
        return max(rr,getmax(k << 1 | 1,mid + 1,r,x));
    }

    void rollback(){
        if(z > 0){
            f[queries[z].k] = queries[z].x;
            --z;
        }
    }

} LCT;

typedef pair<line,int> lct;

struct lineContainer{
    int n0 = 0,nDS = 0;
    int cnt[N * 20],a[N * 20];
    lct Q[N * 20];

    void init(){
        for(int i = 1; i <= nDS; ++i) cnt[i] += cnt[i - 1];
        cnt[nDS + 1] = cnt[nDS];
        for(int i = 1; i <= n0; ++i){
            a[cnt[Q[i].second]--] = i;
        }
    }
    void add(int k,line ll){
        ++cnt[k];
        Q[++n0] = mp(ll,k);
    } 
} lc;

struct DSDeletor{
    vector <line> S[N * 4];
    
    void add(int k,int l,int r,int L,int R,line ll){
        lc.nDS = max(lc.nDS,k);
        if(l > R || L > r) return ;
        if(L <= l && r <= R){
            lc.add(k,ll);
            return ;
        }
        int mid = (l + r) >> 1;
        add(k << 1,l,mid,L,R,ll);
        add(k << 1 | 1,mid + 1,r,L,R,ll);
    }

    void cal(int k,int l,int r){
        int total = 0;
        for(int i = lc.cnt[k] + 1; i <= lc.cnt[k + 1]; ++i){
            int j = lc.a[i];
            total += LCT.add(1,1,n,lc.Q[j].first);
        }
        /*for(line ll : S[k]){
            total += LCT.add(1,1,n,ll);
        }*/
        if(l >= r) printf("%lli\n",max(0LL,LCT.getmax(1,1,n,l)));
        else{
            int mid = (l + r) >> 1;
            cal(k << 1,l,mid);
            cal(k << 1 | 1,mid + 1,r);
        }
        for(int i = 1; i <= total; ++i) LCT.rollback();
    }
} DSD;

void testcase(){
    scanf("%d%d",&n,&m);
    for(int i = 1; i <= m; ++i){
        int l,r;
        long long c,d;
        scanf("%d%d%lli%lli",&l,&r,&c,&d);
        DSD.add(1,1,n,l,r,line(d,c - d * l));
    }
    lc.init();
    LCT.init(1,1,n);
    if(n >= 2e5) return ;
    DSD.cal(1,1,n);
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie();
    cout.tie();
    
    // main program here

    int tcase = 1;
    //cin >> tcase;

    for(int i = 1; i <= tcase; ++i) testcase();

    // 

    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    
    return 0;
}   
