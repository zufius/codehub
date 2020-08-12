// Substr

// KMP
#include <iostream>
#include <stdio.h>
 
using namespace std;
 
const int N = 1e6 + 1;
 
#define FOR(i,l,r) for(int i = l; i <= r;++i)
 
int n,m,p[N]; // max length k sao cho B[1 -> k] lÃ  háº­u tá» "thá»±c sá»±" cá»§a B[1 -> i]
string a,b;
 
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
 
    //freopen("a.inp","r",stdin);
    //freopen("a.out","w",stdout);
 
    cin >> a >> b;
    a = " " + a;
    b = " " + b + "@";
    n = a.size() - 1; m = b.size() - 2;
    
    int k = 0;
    FOR(i,2,m){
        while(k > 0 && b[k + 1] != b[i]) k = p[k];
        if(b[k + 1] == b[i]) ++k;
        p[i] = k;
    }
    //
    k = 0;
    FOR(i,1,n){
        while(k > 0 && b[k + 1] != a[i]) k = p[k];
        if(b[k + 1] == a[i]) ++k;
        if(k >= m){
            cout << i - m + 1 << " ";
            k = p[k];
        }
    }
 
    return 0;
} 

// Z
SPOJ submission 22745229 (CPP) plaintext list. Status: AC, problem SUBSTR, contest SPOJVN. By achung0147 (ntc), 2018-11-22 03:14:07.
#include <iostream>
#include <stdio.h>
 
using namespace std;
 
string P,T;
int Z[2345678];
int L = 0, R = 0,N = 0,M = 0;
char S[2345678];
 
void Find(int i,int v){
    if(v < i) v = i;
    //cout << "OK Find => " << i << " " << v << endl;
    while(v <= N + M && S[v] == S[v - i + 1]) ++v;
    Z[i] = v - i;
    if(v - 1 > R){
        L = i;
        R = v - 1;
    }
   // cout << " `~~~>>>> " << v << endl;
    return ;
}
int main(){
    //freopen("SUBSTR.INP","r",stdin);
    //freopen("SUBSTR.OUT","w",stdout);
 
    cin >> T >> P;
 
    N = P.size();
    M = T.size();
    
    for(int i = 1; i <= N; ++i) S[i] = P[i - 1];
    for(int i = 1; i <= M; ++i) S[i + N] = T[i - 1];
 
    Z[1] = 0;
    for(int i = 2; i <= N + M; ++i){
        if(i >= R) Find(i,i);
        else{
            int a = i - L + 1;
            int b = R - L + 1;
            if(i + Z[a] - 1 < R) Z[i] = Z[a];
            else Find(i,R + 1);
        }
    }
 
    //for(int i = 1; i <= N + M; ++i) cout << i << " : " << S[i] << " => " << Z[i] << endl;
    for(int i = N + 1; i <= N + M; ++i)
        if(Z[i] >= N) cout << i - N << " ";
 
    return 0;
} 
