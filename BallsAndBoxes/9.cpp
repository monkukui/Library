// ボール: 区別あり, 箱：区別なし, 入れ方: 1 個以上
// スターリング数
// S(n, k) = S(n - 1, k - 1) + k * S(n - 1, k)
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
  cout << S[n][k] << endl;
  return 0;
}
