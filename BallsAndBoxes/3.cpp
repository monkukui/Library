// ボール: 区別あり, 箱：区別あり, 入れ方: 1 つ以上
#include <iostream>
using namespace std;
const int MOD = 1000000007;
const long long MAXN = 1001024;

// 繰り返し 2 乗法
long long modpow(long long a, long long n) {
  long long res = 1;
  while (n > 0) {
    if (n & 1) res = res * a % MOD;
    a = a * a % MOD;
    n >>= 1;
  }
  return res;
}

long long fac[MAXN], finv[MAXN], inv[MAXN];

// 前処理 O(n)
void comb_init(){
  fac[0] = fac[1] = 1;
  finv[0] = finv[1] = 1;
  inv[1] = 1;
  for(long long i = 2; i < MAXN; i++){
    fac[i] = fac[i - 1] * i % MOD;
    inv[i] = MOD - inv[MOD%i] * (MOD / i) % MOD;
    finv[i] = finv[i - 1] * inv[i] % MOD;
  }
}

// 二項係数計算 O(1)
long long COM(long long n, long long k){
  if (n < k) return 0;
  if (n < 0 || k < 0) return 0;
  return fac[n] * (finv[k] * finv[n - k] % MOD) % MOD;
}

int main() {
  
  int n, k; cin >> n >> k;
  long long ans = 0;
  comb_init();
  for(int i = 0; i < k; i++) {
    // i 個の箱を選んで, 絶対ボールを入れないことにする
    // 残りの箱に自由に入れる
    int rest = k - i;
    long long add = COM(k, i) * modpow(rest, n) % MOD;
    
    if(i % 2 == 0) ans = (ans + add      ) % MOD;
    else           ans = (ans - add + MOD) % MOD;
  }
  cout << ans << endl;
  return 0;
}
