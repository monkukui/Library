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
// 連続する部分文字列の数え上げは，この問題を参照 SA + LCP
//（https://atcoder.jp/contests/s8pc-2/tasks/s8pc_2_e）
//
// 本問題は，0 以上の文字を取り除いて，繋げ合わせてできる文字列の数え上げ（重複ダブルカウントはしない）

lint CountSubstring(string s) {
  
  int n = s.size();
  // next[i][c] := s[i] 以降で最初に出現する c の位置
  vector<vector<int>> next(n + 1, vector<int>(26, n));
  for (int i = n - 1; i >= 0; i--) {
    for (int j = 0; j < 26; j++) {
      next[i][j] = next[i + 1][j];
    }
    next[i][s[i] - 'a'] = i;
  }


  vector<lint> dp(n + 1, 0);
  dp[0] = 1;
  
  for (int i = 0; i < n; i++) {
    // 遷移は 26 こ
    for (int j = 0; j < 26; j++) {
      if (next[i][j] == n) continue;
      dp[next[i][j] + 1] += dp[i];
      dp[next[i][j] + 1] %= MOD;
    }
  }

  lint ret = 0;
  for (int i = 0; i <= n; i++) {
    ret += dp[i];
    ret %= MOD; 
  }

  return ret;
}

int main() {

  string s; cin >> s;
  cout << CountSubstring(s) << endl;
  return 0;
}
