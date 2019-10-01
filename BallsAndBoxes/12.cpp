// ボール: 区別なし, 箱：区別なし, 入れ方: 1 個以上
// 分割数
// P(n, k) = P(n, k - 1) + P(n - k, k)
#include <iostream>
using namespace std;
const int MOD = 1000000007;
const long long MAXN = 1010;
long long P[MAXN][MAXN] = {};

void pertition_init() {
  for(int k = 0; k < MAXN; k++) P[0][k] = 1;
  for(int n = 1; n < MAXN; n++) {
    for(int k = 1; k < MAXN; k++) {
      P[n][k] += P[n][k - 1] + (n - k >= 0 ? P[n - k][k] : 0);
      P[n][k] %= MOD;
    }
  }
}

int main() {
  
  pertition_init();
  int n, k; cin >> n >> k;
  if(n - k < 0) cout << 0 << endl;
  else cout << P[n - k][k] << endl;
  return 0;
}
