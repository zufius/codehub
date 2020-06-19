- euler totient function : n = p1^q1 * ... * pm^qm (p1,...,pm are prime factos of n)
=> Q(n) = n * (1 - 1/p1) * (1 - 1/p2) * ... * (1 - 1/p3) 
 ( this can be proved using inclusion-exclusion principle, or using the property that Q(n) is a multiplicative function )

//
int q(int n){
   int res = n;
   for(int i = 2; i * i <= n; ++i) if(n % i == 0){
       res -= res/i; // res = res * (1 - 1/i)
       while(n % i == 0) n /= i;
   }
   if(n > 1) res -= res/n;
   return res;
}
