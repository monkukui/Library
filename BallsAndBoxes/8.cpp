// ボール: 区別あり, 箱：区別なし, 入れ方: 1 つ以下
#include <iostream>
using namespace std;

int main() {
  
  int n, k; cin >> n >> k;
  
  // 箱が足りるなら 1
  // 足りないなら 0
  if(n <= k) cout << 1 << endl;
  else cout << 0 << endl;

  return 0;
}
