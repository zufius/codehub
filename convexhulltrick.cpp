// https://www.spoj.com/problems/ACQUIRE/

// i got a lot of WAs because of 
// - int overflow
// - forgetting to remove unusable lines
// - write a stupid formula to remove lines

// some notes : this problem can be optimized by using a deque (actually a deque-like vector) instead of a stack
// because the x values in queries are in ascending order => just remove the unusable lines at the front of the deque
// => than use binary search on the deque => total complexity will be less than O(n*log(n))

#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <time.h>
#include <stack>

using namespace std;

const int N = 5e5 + 123;
const long long oo = 1e18 + 123;
const long long mod = 1e9 + 7;

typedef pair<long long,long long> pi;
#define w second
#define l first
#define mp make_pair
#define getSz(x) ((x).size())
#define slast S[(int)S.size() - 1]
#define snlast S[(int)S.size() - 2]

int n,m;
pi a[N];
long long dp[N];

bool cmp(pi a,pi b){
    return a.l < b.l;
}
bool cmp2(pi a,pi b){
    return a.l != b.l ? a.l > b.l : a.w > b.w;
}

vector <pi> S;

void push_new_line(pi ll){ // extremely important
    while((int)S.size() > 1){

        long long a1 = snlast.first,b1 = snlast.second;
        long long a2 = slast.first,b2 = slast.second;
        long long a3 = ll.first,b3 = ll.second;

        if((a1 - a2) * (b3 - b1) <= (a1 - a3) * (b2 - b1)) S.pop_back();
        else break;
    }
    S.push_back(ll);
}

long long cal(pi line,long long x){
    return x * line.first + line.second;
}
long long find(long long x){
    int l = 0,r = (int)S.size() - 1;
    long long res = oo;
    while(l < r){
        int mid = (l + r) >> 1;
        long long v1 = cal(S[mid],x),v2 = cal(S[mid + 1],x);
        if(v1 < v2){
            res = min(res,v1);
            r = mid;
        }else if(v1 > v2){
            res = min(res,v2);
            l = mid + 1;
        }else return v1;
    }
    if(l == r) res = min(res,cal(S[l],x));
    return res;
}
void testcase(){
    cin >> n;
    for(int i = 1; i <= n; ++i){
        cin >> a[i].w >> a[i].l;
    }
    sort(a + 1,a + 1 + n,cmp2);

    int maxW = -1,m = 0;
    for(int i = 1; i <= n; ++i){
        if(maxW >= a[i].w) continue;
        a[++m] = a[i];
        maxW = a[i].w;
    }
    n = m;

    // 

    sort(a + 1,a + 1 + n,cmp);

    dp[0] = 0;
    push_new_line(mp(a[1].w,dp[0]));
    //cout << "push ("<<a[1].w<<","<<dp[0]<<")\n";

    for(int i = 1; i <= n; ++i){
        dp[i] = find(a[i].l);
        if(i < n) push_new_line(mp(a[i + 1].w,dp[i]));
        //cout << "push ("<<a[i + 1].w<<","<<dp[i]<<")\n";
    }

    cout << dp[n];
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie();
    cout.tie();

    freopen("a.inp","r",stdin);freopen("a.out","w",stdout);

    // main program here

    int tcase = 1;
    //cin >> tcase;

    for(int i = 1; i <= tcase; ++i) testcase();

    // 

    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    
    return 0;
}
