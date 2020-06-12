// https://vn.spoj.com/problems/ORDERSET/
#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <time.h>
#include <set>

using namespace std;

const int N = 5e5 + 123;
const int oo = 1e9;

typedef pair<int,int> pi;
#define mp make_pair
#define getSz(x) ((x).size())

inline int readInt(){
    char c;
    while(c = getchar(), c != '-' && (c < '0' || c > '9'));
    bool neg = c == '-';
    if(neg){
        while(c = getchar(),c < '0' || c > '9');
    }
    int rr = c - '0';
    while(c = getchar(),c >= '0' && c <= '9') rr = rr * 10 + (c - '0');
    return neg ? -rr : rr;
}

int q;

struct trie{
    trie* node[2];
    int f,numEnd;

    trie(){
        node[0] = node[1] = NULL;
        f = numEnd = 0;
    }
};

typedef trie* ptrie;

trie *root = new trie();

int getf(ptrie tmp){
    if(!tmp) return 0;
    return tmp->f;
}

void Insert(int x){
    x += oo;
    ptrie pNode = root;
    for(int i = 30; i >= 0; --i){
        int j = ((x >> i) & 1);
        if(!pNode->node[j]) pNode->node[j] = new trie();
        pNode = pNode->node[j];
    }
    if(!pNode->numEnd){
        pNode->numEnd = 1;
        pNode = root;
        for(int i = 30; i >= 0; --i){
            int j = ((x >> i) & 1);
            pNode = pNode->node[j];
            pNode->f += 1;
        }
        root->f += 1;
    }
}
void Delete(int x){
    x += oo;
    ptrie pNode = root;
    for(int i = 30; i >= 0; --i){
        int j = ((x >> i) & 1);
        if(!pNode->node[j]) return ;
        pNode = pNode->node[j];
    }
    if(pNode->numEnd){
        pNode->numEnd = 0;
        pNode = root;
        for(int i = 30; i >= 0; --i){
            int j = ((x >> i) & 1);
            pNode = pNode->node[j];
            pNode->f -= 1;
        }
        root->f -= 1;
    }
}
vector <int> res;

void FindKth(int k){
    ptrie pNode = root;
    if(k > root->f){
        printf("invalid\n");
        return ;
    }
    int cur = 0;
    res.clear();
    for(int i = 30; i >= 0; --i){
        int j = 0;
        if(cur + getf(pNode->node[0]) < k){
            cur += getf(pNode->node[0]);
            ++j;
        }
        res.push_back(j);
        pNode = pNode->node[j];
    }
    int rr = 0;
    for(int i = 0; i <= 30; ++i){
        rr += ((int)res.back() << i);
        res.pop_back();
    }
    printf("%d\n",rr - oo);
}

void CountLessThan(int x){
    x += oo;
    ptrie pNode = root;

    int cur = 0;
    for(int i = 30; i >= 0; --i){
        int j = (x >> i) & 1;
        if(j){
            cur += getf(pNode->node[0]);
        }
        if(!pNode->node[j]) break;
        pNode = pNode->node[j];
    }
    printf("%d\n",cur);
}
void testcase(){
    q = readInt();
    for(int i = 1; i <= q; ++i){
        char c;
        int x;
        c = getchar();
        while(c < 'A' || c > 'Z') c = getchar();
        x = readInt();
        switch(c){
            case 'I': Insert(x); break;
            case 'D' : Delete(x); break;
            case 'K' : FindKth(x); break;
            default : CountLessThan(x); break;
        }
    }
}
int main(){
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
