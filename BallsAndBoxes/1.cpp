// ボール: 区別あり, 箱：区別あり, 入れ方: 制限なし
#include <iostream>
using namespace std;
const int MOD = 1000000007;

int main() {
  
  int n, k; cin >> n >> k;
  long long ans = 1;
  for(int i = 0; i < n; i++) {
    ans *= k;
    ans %= MOD;
  }
  cout << ans << endl;
  return 0;
}
