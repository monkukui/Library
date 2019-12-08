// ボール: 区別なし, 箱：区別あり, 入れ方: 制限なし
#include <iostream>
using namespace std;
const int MOD = 1000000007;
const long long MAXN = 1001024;
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
  
  comb_init();
  int n, k; cin >> n >> k;
  cout << mod_comb(n + k - 1, k - 1) << endl; 
  return 0;
}
