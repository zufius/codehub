// C11SEQ spoj
#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <time.h>
#include <set>

using namespace std;

const int N = 1e5 + 123;
const long long mod = 1e9 + 7;
const long long oo = 1e18 + 7;

typedef pair<int,int> pi;
#define mp make_pair
#define getSz(x) ((x).size())
#define SetLength2(a, n, t) a=((t*) calloc(n, sizeof(t))) + (n)/2

int n,m;
long long a[N],l,r;

struct Treap{
    int total = 0,cnt = 0;
    long long key,val,maxVal,minVal;
    Treap *left,*right;

    Treap(){left = right = NULL;}
    Treap(long long x){
        left = right = NULL;
        val = maxVal = minVal = x;
        total = cnt = 1;
        key = rand() % (int)1234567890 + 1;
    }
} *root = NULL;

typedef Treap* tPointer;

int getTotal(tPointer x){
    return x ? x->total : 0;
}
long long getMaxVal(tPointer x){
    return x ? x -> maxVal : -oo;
}
long long getMinVal(tPointer x){
    return x ? x -> minVal : oo;
}
void update(tPointer x){
    if(!x) return ;
    x->total = x->cnt + getTotal(x->left) + getTotal(x->right);
    x->maxVal = max(x->val,max(getMaxVal(x->left),getMaxVal(x->right)));
    x->minVal = min(x->val,min(getMinVal(x->left),getMinVal(x->right)));
}
tPointer rotateLeft(tPointer node){
    if(!node->left) return node;
    tPointer t = node->left,x = t->right;
    t->right = node;
    node->left = x;
    update(node);
    update(t);
    return t;
}
tPointer rotateRight(tPointer node){
    if(!node->right) return node;
    tPointer t = node->right,x = t->left;
    t->left = node;
    node->right = x;
    update(node);
    update(t);
    return t;
}
tPointer insert(tPointer node,long long x){
    if(!node) return new Treap(x);
    if(x == node->val){
        ++node->cnt;
    }else if(x < node->val){
        node->left = insert(node->left,x);
        if(node->left->key > node->key) node = rotateLeft(node);
    }else{
        node->right = insert(node->right,x);
        if(node->right->key > node->key) node = rotateRight(node);
    }
    update(node);
    return node;
}
tPointer deleteVal(tPointer node,long long x){
    if(!node) return NULL;
    if(x < node->val){
        node->left = deleteVal(node->left,x);
    }else if(x > node->val){
        node->right = deleteVal(node->right,x);
    }else{
        --node->cnt;
        if(node->cnt <= 0){
            if(!node->left && !node->right){
                delete node;
                node = NULL;
            }else if(!node->left || !node->right){
                tPointer tmp = node;
                node = node->left ? node->left : node->right;
                delete tmp;
            }else{
                if(node->left->key < node->right->key){
                    node = rotateLeft(node);
                    node->left = deleteVal(node->left,x);
                }else{
                    node = rotateRight(node);
                    node->right = deleteVal(node->right,x);
                }
            }
        }
    }
    update(node);
    return node;
}
int get(tPointer node,long long x){ // number of value <= x
    if(!node) return 0;
    if(x < node->minVal) return 0;
    if(node->maxVal <= x) return node->total;
    return (node->val <= x ? node->cnt : 0) + get(node->left,x) + get(node->right,x);
}
void dfs(tPointer node){
    if(!node) return ;
    dfs(node->left);
    cout << node->val << "/"<<node->cnt<<"/"<<node->total << "  ";
    dfs(node->right);
}
void testcase(){
    srand(time(NULL));
    scanf("%d%lli%lli",&n,&l,&r);
    for(int i = 1; i <= n; ++i) {
        scanf("%lli",&a[i]);
        a[i] += a[i - 1];
    }

    // l <= t[i] - t[j - 1] <= r 
    // t[j - 1] <= t[i] - l && t[j - 1] >= t[i] - r
    // t[j - 1] $ [t[i] - r,t[i] - l]

    long long res = 0;
    for(int i = 1,j = -1; i <= n; ++i){
        while(j + 1 < i){
            ++j;
            root = insert(root,a[j]);
        }
        int k = rand() % i;
        root = insert(deleteVal(root,a[k]),a[k]); // this is is just for testing the deleteVal function
        res += max(0,get(root,a[i] - l) - get(root,a[i] - r - 1));
        //cout << "explore : " << i << endl;
        //dfs(root);
        //cout << endl;
    }
    printf("%lli",res);
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
