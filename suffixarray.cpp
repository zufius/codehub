// https://codeforces.com/gym/102428/problem/G

#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <vector>
#include <map>
#include <set>
#include <deque>
#include <queue>
#include <stdlib.h>
#include <time.h>
#include <iomanip>
#include <math.h>
#include <bitset>
#include <string.h>

using namespace std;

#define taskname "A"
#define LL long long 
#define uLL unsigned long long 
#define FOR(i,l,r) for(int i = l; i <= r; ++i)
#define REP(i,l,r) for(int i = l; i < r; ++i)
#define FORD(i,r,l) for(int i = r; i >= l; --i)
#define REPD(i,r,l) for(int i = r; i > l; --i)
#define sz(x) (int)((x).size())
#define all(x) (x).begin(), (x).end()
#define debug(x) { cerr << #x << " = " << x << endl; }
#define sci(x) int x; scanf("%d", &x);
#define scii(x, y) int x, y; scanf("%d %d", &x, &y);
#define sciii(x, y, z) int x, y, z; scanf("%d %d %d", &x, &y, &z);
#define pi pair<int,int>
#define pii pair<int,pi>
#define mp make_pair
#define fi first
#define se second
#define pb push_back
#define _USE_MATH_DEFINES 
/* M_PI */
#define SetLength2(a, n, t) a=((t*) calloc(n, sizeof(t))) + (n)/2

const int maxN = 2e5 + 11;
const LL oo = 1e17 + 11;
const LL MOD = 1e9 + 8577;
const LL base = 41;

int tcases = 1;

LL hPow[maxN];
char W[maxN];

class Hasher{
    public : 

    int n;
    char *S;
    LL hashCode[maxN];

    LL getHash(int l,int r){
        LL x = hashCode[r],y = hashCode[l - 1];
        return ((hashCode[r] - hashCode[l - 1] * hPow[r - l + 1]) % MOD + MOD) % MOD;
    }

    void build(char *tmp){

        S = tmp;
        n = strlen(S + 1);

        FOR(i,1,n){
            hashCode[i] = (hashCode[i - 1] * base + S[i] - 'A' + 1) % MOD;
        }
    }

} Hasher1,Hasher2;

namespace SuffixArray{
    char *S;
    int n,sa[maxN],pos[maxN],tmp[maxN],lcp[maxN],gap = 1;
    
    bool cmp(int i,int j){
        if(pos[i] != pos[j]) return pos[i] < pos[j];
        i += gap; j += gap;
        return i <= n && j <= n ? pos[i] < pos[j] : i > j;
    }
    void build(){
        S = (char*)malloc(maxN*sizeof(char));
        scanf("%s",S + 1);
        n = strlen(S + 1);

        Hasher1.build(S);

        S[n + 1] = '@';

        FOR(i,1,n){
            sa[i] = i;
            pos[i] = S[i] - 'A';
        }

        while(true){
            sort(sa + 1,sa + 1 + n,cmp);
            FOR(i,2,n){
                tmp[i] = tmp[i - 1] + cmp(sa[i - 1],sa[i]);
            }
            FOR(i,1,n) pos[sa[i]] = tmp[i] + 1;
            if(tmp[n] >= n - 1) break;
            gap <<= 1;
        }

        // now build LCP

        for (int i = 1, k = 0; i <= n; ++i) if (pos[i] != n){
            for (int j = sa[pos[i] + 1]; S[i + k] == S[j + k];) ++k;
            lcp[pos[i]] = k;
            if (k)--k;
        }
    }

    bool isGreaterOrEqual(int x,int l,int r){
        int i = sa[x];
        int lo = 1,hi = min(n - i + 1,r - l + 1),v = 0; // find the lcp of W[l..r] and S[i..n]

        while(lo <= hi){
            int mid = (lo + hi) >> 1;
            if(Hasher1.getHash(i,i + mid - 1) == Hasher2.getHash(l,l + mid - 1)){
                v = mid;
                lo = mid + 1;
            }else hi = mid - 1;
        }
        if(v >= min(r - l + 1,n - i + 1)){
            return r - l <= n - i;
        }
        return S[i + v] >= W[l + v];
    }

    bool isSubString(int l,int r){
        int lo = 1,hi = n,v = n + 1; // find the first pos that >= W[l..r]
        while(lo <= hi){
            int mid = (lo + hi) >> 1;
            if(isGreaterOrEqual(mid,l,r)){
                hi = mid - 1;
                v = mid;
            }else lo = mid + 1;
        }
        if(v > n){
            return 0;
        }
        return Hasher1.getHash(sa[v],sa[v] + r - l) == Hasher2.getHash(l,r);
    }
}

void testcase(){

    hPow[0] = 1;
    REP(i,1,maxN) hPow[i] = (hPow[i - 1] * base) % MOD;

    SuffixArray::build();

    sci(M);

    FOR(i,1,M){
        scanf("%s",W + 1);

        Hasher2.build(W);

        int l = 1,r = strlen(W + 1);
        int res = 0;
        while(l <= r){
            int k = 0;
            while(l + k <= r && SuffixArray::isSubString(l,l + k)) ++k;
            if(!k){
                res = -1;
                break;
            }
            l += k;
            ++res;
        }
        printf("%d\n",res);
    }

}

int main(){

    FOR(i,1,tcases) testcase();

    return 0;
}
