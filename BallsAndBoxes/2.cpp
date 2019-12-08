// ボール: 区別あり, 箱：区別あり, 入れ方: 箱の中身は 1 つ以下
#include <iostream>
using namespace std;
const int MOD = 1000000007;

int perm(int k, int n) {
  if(k < n) return 0;
  long long ret = 1;
  for(int i = 0; i < n; i++) {
    ret *= (k - i);
    ret %= MOD;
  }
  return ret;
}

int main() {
  int n, k; cin >> n >> k;
  cout << perm(k, n) << endl;
  return 0;
}






