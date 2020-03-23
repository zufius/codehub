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

const int maxN = 1e6 + 11;

int tcases = 1;

int M;
char W[maxN];
pi A[maxN];

namespace SuffixArray{
    char S[maxN];
    int n = 0,sa[maxN],pos[maxN],cnt[maxN],pn[maxN],cn[maxN],lcp[maxN],gap = 1;
    int CharAlp[maxN],tckn = 2e5;

    void readString(int i){
        scanf("%s",S + n + 1);
        A[i].fi = n + 1;
        int m = n + strlen(S + n + 1);
        FOR(i,n + 1,m) CharAlp[i] = 2e5 + (S[i] - 'A' + 1); // tckn must decrease after each string E.g : A@ - A@ => loop of gap would never stop
        n = m;
        CharAlp[++n] = tckn--;
        A[i].se = n;
    }
    
    void build(){
        /* build Suffix Array */

        // initialization
        int classes = 0;
        FOR(i,1,n) ++cnt[CharAlp[i]];
        FOR(i,1,2e5 + 26) cnt[i] += cnt[i - 1];
        FOR(i,1,n) sa[cnt[CharAlp[i]]--] = i;
        FOR(i,1,n){
            if(i <= 1 || CharAlp[sa[i]] > CharAlp[sa[i - 1]]) ++classes;
            pos[sa[i]] = classes;
        }
        // main algorithm
        for(int gap = 1; classes < n; gap <<= 1){

            FOR(i,1,n){
                pn[i] = sa[i] - gap;
                if(pn[i] < 1) pn[i] += n;
            }

            fill(cnt,cnt + 1 + classes,0); // cnt[0] = 0

            FOR(i,1,n) ++cnt[pos[pn[i]]];
            FOR(i,1,classes) cnt[i] += cnt[i - 1];
            FORD(i,n,1) sa[cnt[pos[pn[i]]]--] = pn[i];
            classes = 0;

            FOR(i,1,n){
                int j = sa[i - 1] + gap,k = sa[i] + gap;
                if(j > n) j -= n; if(k > n) k -= n;
                if(i <= 1 || (pos[sa[i - 1]] < pos[sa[i]] || pos[j] < pos[k])) ++classes;
                cn[sa[i]] = classes;
            }
            FOR(i,1,n) pos[i] = cn[i];
        }

        // now build LCP
        
        for (int i = 1, k = 0; i <= n; ++i) if(pos[i] != n){
            for (int j = sa[pos[i] + 1]; i + k <= n && j + k <= n && S[i + k] == S[j + k];) ++k;
            lcp[pos[i]] = k;
            if (k)--k;
        }
    }

    // process queries offline
    int lastC[maxN],D[maxN];
    deque <int> Q;

    void initAnswer(){
        FOR(i,1,n){
            lastC[i] = lastC[i - 1];
            if(sa[i] <= A[0].se) lastC[i] = i;
            while(!Q.empty() && Q.front() < lastC[i]) Q.pop_front();
            if(Q.size()) D[i] = lcp[Q.front()];
            while(!Q.empty() && lcp[Q.back()] >= lcp[i]) Q.pop_back();
            Q.pb(i);
        }

        //
        lastC[n + 1] = n + 1;
        Q.clear();
        FORD(i,n,1){
            lastC[i] = lastC[i + 1];
            if(sa[i] <= A[0].se) lastC[i] = i;
            // from i -> lastC[i] - 1
            while(Q.size() && lcp[Q.back()] >= lcp[i]) Q.pop_back();
            Q.pb(i);
            while(Q.size() && Q.front() >= lastC[i]) Q.pop_front();
            if(Q.size()) D[i] = max(D[i],lcp[Q.front()]);
        }
    }
}

void testcase(){
    SuffixArray::readString(0);
    scanf("%d",&M);
    FOR(i,1,M) SuffixArray::readString(i);
    
    SuffixArray::build();
    SuffixArray::initAnswer();
    
    FOR(i,1,M){
        int res = 0;
        int l = A[i].fi,r = A[i].se - 1;
        while(l <= r){
            int v = SuffixArray::pos[l];
            if(!SuffixArray::D[v]){
                res = -1;
                break;
            }
            l += SuffixArray::D[v];
            ++res;
        }

        printf("%d\n",res);
    }
}

int main(){

    FOR(i,1,tcases) testcase();

    return 0;
}
