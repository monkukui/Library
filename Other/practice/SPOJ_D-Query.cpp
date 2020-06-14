#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#include <deque>
#include <list>
#include <queue>
#include <stack>
#include <vector>
#include <utility>
#include <algorithm>
#include <map>
#include <set>
#include <complex>
#include <cmath>
#include <limits>
#include <climits>
#include <ctime>
#include <cassert>
#include <numeric>
#include <functional>
#include <bitset>

using namespace std;
using lint = long long int;
long long int INF = 1001001001001001LL;
int inf = 1000000007;
long long int MOD = 1000000007LL;
double PI = 3.1415926535897932;

template<typename T1,typename T2>inline void chmin(T1 &a,const T2 &b){if(a>b) a=b;}
template<typename T1,typename T2>inline void chmax(T1 &a,const T2 &b){if(a<b) a=b;}

#define ALL(a) a.begin(),a.end()
#define RALL(a) a.rbegin(),a.rend()

/* do your best */

struct Mo {
  using ADD = function<void(int)>;
  using DEL = function<void(int)>;
  using REM = function<void(int)>;

  int width;
  vector<int> left, right, order;
  vector<bool> v;

  Mo(int n, int q) : width((int) sqrt(n)), order(q), v(n) {
    iota(begin(order), end(order), 0);
  }

  // [l, r)
  void add_query(int l, int r) {
    left.push_back(l);
    right.push_back(r);
  }

  void run(const ADD &add, const DEL &del, const REM &rem) {
    assert(left.size() == order.size());
    sort(begin(order), end(order), [&](int a, int b) {
      int ablock = left[a] / width, bblock = left[b] / width;
      if(ablock != bblock) return ablock < bblock;
      if(ablock & 1) return right[a] < right[b];
      return right[a] > right[b];
    });
    int nl = 0, nr = 0;
    auto push = [&](int idx) {
      v[idx].flip();
      if(v[idx]) add(idx);
      else del(idx);
    };
    for(auto idx : order) {
      while(nl > left[idx]) push(--nl);
      while(nr < right[idx]) push(nr++);
      while(nl < left[idx]) push(nl++);
      while(nr > right[idx]) push(--nr);
      rem(idx);
    }
  }
};

// 区間 [l, r) の値の種類数を求めよ
int main() {

  int n, q; cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }

  cin >> q;

  vector<int> cnt(1000001, 0); // cnt[i] := 値 i の種類数
  Mo mo(n, q);
  for (int i = 0; i < q; i++) {
    int l, r; cin >> l >> r;
    l--;
    mo.add_query(l, r);
  }

  int sum = 0; // 区間内の種類数
  vector<int> ans(n);
  auto add = [&](int idx) {
    if (cnt[a[idx]] == 0) sum++;
    cnt[a[idx]]++;
  };
  auto del = [&](int idx) {
    if (cnt[a[idx]] == 1) sum--;
    cnt[a[idx]]--;
    assert(cnt[a[idx]] >= 0);
  };
  auto rem = [&](int idx) {
    ans[idx] = sum;
  };
  mo.run(add, del, rem);
  for (int i = 0; i < q; i++) {
    cout << ans[i] << endl;
  }

  
  return 0;
}
