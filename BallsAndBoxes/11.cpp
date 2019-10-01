// ボール: 区別なし, 箱：区別なし, 入れ方: 1 つ以下
#include <iostream>
using namespace std;

int main() {
  
  int n, k; cin >> n >> k;
  
  // 箱が足りるなら 1
  // 足りないなら 0
  cout << (n <= k) << endl;

  return 0;
}
