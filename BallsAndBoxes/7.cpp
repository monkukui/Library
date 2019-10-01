// ボール: 区別あり, 箱：区別なし, 入れ方: 制限なし
// ベル数
// B(n, k) = S(n, 0) + S(n, 1) + ... + S(n, k)
#include <iostream>
using namespace std;
const int MOD = 1000000007;
const long long MAXN = 1010;
long long S[MAXN][MAXN] = {};

void star_init() {
  S[0][0] = 1;
  for(int n = 1; n < MAXN; n++) {
    for(int k = 1; k < MAXN; k++) {
      S[n][k] = S[n - 1][k - 1] + k * S[n - 1][k];
      S[n][k] %= MOD;
    }
  }
}


int main() {
  
  star_init();
  int n, k; cin >> n >> k;
  long long B = 0;
  for(int i = 0; i <= k; i++) {
    B += S[n][i];
    B %= MOD;
  }
  cout << B << endl;
  return 0;
}
