// O(NlogN^2)
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
}
// O(NlogN)
namespace SuffixArray{
    char *S;
    int n,sa[maxN],pos[maxN],cnt[maxN],pn[maxN],cn[maxN],lcp[maxN],gap = 1;
    
    void build(){
        char tckn = 'A' - 1;

        S = (char*)malloc(maxN*sizeof(char));
        scanf("%s",S + 1);
        n = strlen(S + 1) + 1;
        S[n] = tckn;
        
        /* build Suffix Array */
        
        // initialization
        int classes = 0;
        FOR(i,1,n) ++cnt[S[i] - tckn];
        FOR(i,1,26) cnt[i] += cnt[i - 1];
        FOR(i,1,n) sa[cnt[S[i] - tckn]--] = i;
        FOR(i,1,n){
            if(i <= 1 || S[sa[i]] > S[sa[i - 1]]) ++classes;
            pos[sa[i]] = classes;
        }

        //
        for(int gap = 1; classes < n - 1; gap <<= 1){

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

        --n;
        FOR(i,1,n) sa[i] = sa[i + 1];
        FOR(i,1,n) pos[sa[i]] = i;

        // now build LCP

        for (int i = 1, k = 0; i <= n; ++i) if (pos[i] != n){
            for (int j = sa[pos[i] + 1]; S[i + k] == S[j + k];) ++k;
            lcp[pos[i]] = k;
            if (k)--k;
        }
    }
}
