// https://codeforces.com/contest/1080/problem/E //// use overflow hashing at row 54 to reduce time complexity
#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>

using namespace std;

const int N = 511;
const long long mod = 1e9 + 7;
const long long base = 41;

int n,m;
string s[N];
long long hPow[N],hashTable[N][26],res = 0;
long long a[N];
bool palin[N];

class{
    public :
    int cnt[N][26];

    void run(int ii){
        for(int i = 1; i <= m; ++i){
            for(int k = 0; k < 26; ++k){
                cnt[i][k] = cnt[i - 1][k] + ((int)(s[ii][i - 1] - 'a') == k);
            }
        }
    }

    int cal(int c,int l,int r){
        return cnt[r][c] - cnt[l - 1][c];
    }

} StringManager[N];

void initialization(){
    for(int i = 1; i <= n; ++i) StringManager[i].run(i);
    hPow[0] = 1;
    for(int i = 1; i < N; ++i) hPow[i] = (hPow[i - 1] * base) % mod;
    for(int i = 1; i <= m; ++i){
        for(int j = 0; j < 26; ++j){
            hashTable[i][j] = (hashTable[i - 1][j] * base + j + 1) % mod;
        }
    }
}

long long createHash(int row,int l,int r){
    bool ispalin = 1,f = 0;
    long long rhash = 0;
    for(int i = 0; i < 26; ++i){
        int j = StringManager[row].cal(i,l,r);
        if(!j) continue;
        rhash = (rhash * hPow[j] + hashTable[j][i]); // % mod
        if(j & 1){
            if(f) ispalin = 0;
            else f = 1;
        }
    }
    palin[row << 1] = ispalin;
    return rhash;
}

namespace Manacher{
    int k = 0;
    long long a[N];
    int f[N];

    void init(){
        k = 2 * n + 1;
        for(int i = 1; i <= k; ++i){
            a[i] = -1;
            palin[i] = 1;
        }
    }

    bool checkPalin(int i){
        if(i & 1) return 1;
        return palin[i >> 1];
    }

    void run(){
        int r = 0,l = -1;
        for(int i = 1; i <= k; ++i){
            int j = i > r ? 0 : min(f[r + l - i],r - i);
            while(i + j < k && i - j > 1 && palin[i + j + 1] && palin[i - j - 1] && a[i + j + 1] == a[i - j - 1]) ++j;
            f[i] = j;
            if(i + f[i] > r){
                r = i + f[i];
                l = i - f[i];
            }
            if(!(i & 1)){
                if(palin[i]) res += (f[i] + 1) >> 1;
            }else{
                res += f[i] >> 1;
            }
        }
    }
};

int main(){

    scanf("%d%d",&n,&m);
    for(int i = 1; i <= n; ++i){
        char c;
        for(int j = 1; j <= m; ++j){
            while(c = getchar(),c < 'a' || c > 'z');
            s[i] = s[i] + c;
        }
    }

    initialization();

    Manacher::init();


    for(int l = 1; l <= m; ++ l){
        for(int r = l; r <= m; ++r){
            for(int row = 1; row <= n; ++row){
                Manacher::a[row << 1] = createHash(row,l,r);
            }
            Manacher::run();
        }
    }

    printf("%lli",res);

    return 0;
}
