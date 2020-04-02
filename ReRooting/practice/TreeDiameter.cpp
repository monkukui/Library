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

void dfs1(int cur, int par, vector<vector<int>> &g, vector<int> &D) {
  for (auto nxt : g[cur]) {
    if (nxt == par) continue;
    dfs1(nxt, cur, g, D);
  }

  int maxLen = -1;
  for (auto nxt : g[cur]) {
    if (nxt == par) continue;
    maxLen = max(maxLen, D[nxt]);
  }

  D[cur] = maxLen + 1;
}

void dfs2(int cur, int par, vector<vector<int>> &g, vector<int> &D, vector<int> &ans, int Dpar) {

  
  int maxLen = Dpar;
  vector<int> left;
  vector<int> right;
  for (auto nxt : g[cur]) {
    if (nxt == par) continue;
    left.push_back(D[nxt]);
    right.push_back(D[nxt]);
    maxLen = max(maxLen, D[nxt]);
  }
  ans[cur] = maxLen + 1;
  
  for (int i = 1; i < left.size(); i++) {
    left[i] = max(left[i], left[i - 1]);
  }

  for (int i = (int)right.size() - 2; i >= 0; i--) {
    right[i] = max(right[i], right[i + 1]);
  }

  int id = 0;
  for (auto nxt : g[cur]) {
    if (nxt == par) continue;
    
    int nxtDpar = Dpar + 1;
    if (id != 0) nxtDpar = max(nxtDpar, left[id - 1] + 1);
    if (id != (int)right.size() - 1) nxtDpar = max(nxtDpar, right[id + 1] + 1);
    id++;

    dfs2(nxt, cur, g, D, ans, nxtDpar);
  }

}

int main() {
  
  int n; cin >> n;
  vector<vector<int>> g(n);
  for (int i = 0; i < n - 1; i++) {
    int a, b; cin >> a >> b;
    a--;
    b--;
    g[a].push_back(b);
    g[b].push_back(a);
  }

  vector<int> D(n, -1);
  vector<int> ans(n, -1);
  dfs1(0, -1, g, D);
  dfs2(0, -1, g, D, ans, -1);
  for (int i = 0; i < n; i++) {
    cout << 2 * (n - 1) - ans[i] << endl;
  }
  return 0;
}
