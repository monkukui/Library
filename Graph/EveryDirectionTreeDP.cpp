/* monkukui 競技プログラミング用のテンプレート  (ここから) */
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
using ll = long long int;
using lnt = long long int;
using Graph = vector<vector<int>>;
using Wgraph = vector<vector<pair<int, long long int>>>;
constexpr long long int INF = 1001001001001001LL;
constexpr long long int MOD = 1000000007LL;
constexpr double PI = 3.1415926535897932;
constexpr long long int di[] = {-1, 0, 1, 0, -1, 1, 1, -1};
constexpr long long int dj[] = {0, 1, 0, -1, 1, 1, -1, -1};

template<typename T1,typename T2> inline void chmin(T1 &a,T2 b){if(a>b) a=b;}
template<typename T1,typename T2> inline void chmax(T1 &a,T2 b){if(a<b) a=b;}
inline void yes(){ cout << "yes" << endl; }
inline void Yes(){ cout << "Yes" << endl; }
inline void YES(){ cout << "YES" << endl; }
inline void no(){ cout << "no" << endl; }
inline void No(){ cout << "No" << endl; }
inline void NO(){ cout << "NO" << endl; }
inline void possible(){ cout << "possible" << endl; }
inline void Possible(){ cout << "Possible" << endl; }
inline void POSSIBLE(){ cout << "POSSIBLE" << endl; }
inline void impossible(){ cout << "impossible" << endl; }
inline void Impossible(){ cout << "Impossible" << endl; }
inline void IMPOSSIBLE(){ cout << "IMPOSSIBLE" << endl; }

#define REP(i,n) for(int i = 0; i < (n); i++)
#define RREP(i,n) for(int i = 1; i <= (n); i++)
#define DREP(i,n) for(int i = (n)-1; i >= 0; i--)
#define SREP(i,s,t) for(int i = s; i < t; i++)
#define ALL(a) a.begin(),a.end()
#define RALL(a) a.rbegin(),a.rend()
#define PB push_back

/* monkukui 競技プログラミング用のテンプレート (ここまで)*/

// 重み付き木の直径を ++全方位木 DP++ で求める

void dfs1(int cur, int par, vector<vector<pair<int, int>>> &g, vector<int> &D) {
  for(auto e : g[cur]) {
    int nxt = e.first;
    int d = e.second;
    if(nxt == par) continue;
    dfs1(nxt, cur, g, D);
    D[cur] = max(D[cur], D[nxt] + d);
  }
}

void dfs2(int cur, int par, vector<vector<pair<int, int>>> &g, vector<int> &dp, int par_edge_cost) {
  if(par != -1) {
    dp[cur] = max(dp[cur], dp[par] + par_edge_cost);
  }

  for(auto e : g[cur]) {
    int nxt = e.first;
    int d = e.second;
    if(nxt == par) continue;
    dfs2(nxt, cur, g, dp, d);
  }
}

int main(){
  
  // 入力
  int n; cin >> n; int m = n - 1;
  vector<vector<pair<int, int>>> g(n);
  
  for(int i = 0; i < m; i++) {
    int a, b, c; cin >> a >> b >> c;
    g[a].push_back({b, c});
    g[b].push_back({a, c});
  }
  vector<int> D(n, 0);
  dfs1(0, -1, g, D);

  vector<int> dp(n, 0);
  for(int i = 0; i < n; i++) dp[i] = D[i];
  for(int i = 0; i < n; i++) {
    cerr << "dp[" << i << "] = " << dp[i] << endl;
  }
  dfs2(0, -1, g, dp, -1);

  for(int i = 0; i < n; i++) {
    cerr << "dp[" << i << "] = " << dp[i] << endl;
  }

  return 0;
}
