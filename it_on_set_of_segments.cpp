// https://vn.spoj.com/problems/JEWELNB/
// https://codeforces.com/group/FLVn1Sc504/contest/274814/problem/X

// It's kind of the same as LiChaoTree on set of lines, I just divide each segment into sub-segments
// that cover whole a node => process them like normal lines
// IT on set of segments

#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <time.h>
#include <set>

using namespace std;

const int N = 5e5 + 123;
const int oo = 1e9 + 123;
const long long ooL = 1e18 + 123;
const long long mod = 1e9 + 7;

typedef pair<int,int> pi;
#define mp make_pair
#define getSz(x) ((x).size())

int n,m;

struct line{
    long long a,b;
    line(long long _a = 0,long long _b = 0) : a(_a),b(_b){}
    long long val(long long x){return a * x + b;}
    bool operator == (const line &ll) const{
        return a == ll.a && b == ll.b;
    }
} tmp(-oo,-oo);

struct it_on_set_of_segments{

    line f[N << 2];

    void init(int k,int l,int r){
        f[k] = tmp;
        if(l < r){
            int mid = (l + r) >> 1;
            init(k << 1,l,mid);
            init(k << 1 | 1,mid + 1,r);
        }
    }
    void add_new_line(int k,int l,int r,line ll){
        if(f[k] == tmp){
            f[k] = ll;
            return ;
        }
        if(l >= r){
            if(f[k].val(l) < ll.val(l)){
                f[k] = ll;
            }
            return ;
        }
        int mid = (l + r) >> 1;
        bool left = ll.val(l) > f[k].val(l);
        bool m = ll.val(mid) > f[k].val(mid);
        if(m){
            swap(f[k],ll);
        }
        if(left != m) add_new_line(k << 1,l,mid,ll); // left != m, not left != mid
        else add_new_line(k << 1 | 1,mid + 1,r,ll);
    }
    void add(int k,int l,int r,int L,int R,line ll){
        if(l > R || L > r) return ;
        if(L <= l && r <= R){
            add_new_line(k,l,r,ll);
            return ;
        }
        int mid = (l + r) >> 1;
        add(k << 1,l,mid,L,R,ll);
        add(k << 1 | 1,mid + 1,r,L,R,ll);
    }

    long long query(int k,int l,int r,int x){
        if(x > r || x < l) return -ooL;
        long long rr = f[k] == tmp ? -ooL : f[k].val(x);
        if(l < r){
            int mid = (l + r) >> 1;
            rr = max(rr,query(k << 1,l,mid,x));
            rr = max(rr,query(k << 1 | 1,mid + 1,r,x));
        }
        return rr;
    }
} its;

void testcase(){
    scanf("%d%d",&n,&m);
    its.init(1,1,n);
    for(int i = 1; i <= m; ++i){
        int l,r,c,d;
        scanf("%d%d%d%d",&l,&r,&c,&d);
        its.add(1,1,n,l,r,line(d,- (long long)l * d + c));
    }
    for(int i = 1; i <= n; ++i){
        printf("%lli\n",max(0LL,its.query(1,1,n,i)));
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
