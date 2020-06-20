// https://codeforces.com/problemset/problem/896/D
// calculate combination with p (modulo) is not a prime (1 <= p <= 10^9)
// Just let k divide gcd(k,p) when pre-processing the factorials and the inversion of factorials of k and multiply them back when computing the combination numbers.And it will lead to an O(nk) solution,where k is the number of prime divisors of p,which is no larger than 9
// There is another way using Chinese Remainder Theorem
#include <bits/stdc++.h>

#pragma GCC optimize("Ofast")
# pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")# define ll long long
using namespace std;
int n, l, r;
ll p, phi, fac[100005], inv[100005], c[11][100005];
int a[11], cnt[100005][11], t[100005], tot = 0;
inline ll qpow(ll a, ll b, ll mod) {
  ll res = 1, tp = a;
  while (b) {
    if (b & 1 ll) {
      res *= tp;
      res %= mod;
    }
    tp *= tp;
    tp %= mod;
    b >>= 1 ll;
  }
  return res;
}
inline void pre() {
  int i, j, tp = p;
  for (i = 2; i * i <= tp; i++) {
    if (tp % i == 0) {
      while (tp % i == 0) tp /= i;
      a[++tot] = i;
    }
  }
  if (tp > 1) a[++tot] = tp;
  phi = p;
  fac[0] = 1 ll;
  for (i = 1; i <= tot; i++) {
    phi = phi / a[i] * (a[i] - 1);
  }
  for (i = 1; i <= n; i++) {
    t[i] = i;
    for (j = 1; j <= tot; j++) {
      cnt[i][j] = cnt[i - 1][j];
      while (t[i] % a[j] == 0) {
        t[i] /= a[j];
        cnt[i][j]++;
      }
    }
    fac[i] = fac[i - 1] * ((ll)(t[i])) % p;
  }
  inv[n] = qpow(fac[n], phi - 1, p);
  for (i = n - 1; i >= 0; i--) {
    inv[i] = inv[i + 1] * ((ll)(t[i + 1])) % p;
  }
  for (i = 1; i <= tot; i++) {
    c[i][0] = 1 ll;
    for (j = 1; j <= cnt[n][i]; j++) {
      c[i][j] = c[i][j - 1] * ((ll)(a[i])) % p;
    }
  }
}
inline ll cal(int x, int y) {
  if (y > x) return 0;
  ll ans = (((fac[x] * inv[x - y]) % p) * inv[y]) % p;
  for (int i = 1; i <= tot; i++) {
    ans = ans * c[i][cnt[x][i] - cnt[y][i] - cnt[x - y][i]] % p;
  }
  return ans;
}
int main() {
  int i;
  ll res = 0;
  scanf("%d%I64d%d%d", & n, & p, & l, & r);
  pre();
  for (i = 0; i <= n; i++) {
    int ls = (n - i + l + 1) / 2, rs = (n - i + r) / 2;
    res += cal(n, i) * (cal(n - i, ls) - cal(n - i, rs + 1));
    res %= p;
  }
  if (res < 0) res += p;
  printf("%I64d\n", res);
  return 0;
}
