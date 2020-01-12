
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

//
//  |-----|
//  |7|0|4|
//  |-+-+-|     int ni = i + di[dir]
//  |3|*|1|     int nj = j + dj[dir]
//  |-+-+-|
//  |6|2|5|
//  |-----|
//
//
//  e.g.
//  int h = 2;
//  int w = 3;
//  int n = h * w;
//
//    |0|1|2|
//    |-+-+-|
//   0|0|1|2|
//  --|-+-+-|
//   1|3|4|5|
//    |-----|
//
//
//
// This is just code for competitive programming
// You can't blame me


long long int di[] = {-1, 0, 1, 0, -1, 1, 1, -1};
long long int dj[] = {0, 1, 0, -1, 1, 1, -1, -1};

// true だったら範囲外
bool out_of_grid(int i, int j, int h, int w) {
  return !(0 <= i and i < h and 0 <= j and j < w);
}

int coordinate_to_node(int i, int j, int h, int w) {
  return i * w + j;
}

pair<int, int> node_to_coordinate(int node, int h, int w) {
  return {node / h, node % w};
}

// weighted
vector<vector<pair<int, int>>> grid_to_graph(const vector<vector<int>> &grid) {
  int h = grid.size();
  int w = grid[0].size();
  int n = h * w;
  vector<vector<pair<int, int>>> g(n);
  for(int i = 0; i < h; i++) {
    for(int j = 0; j < w; j++) {
      if(grid[i][j] == 0) continue;
      int cur = coordinate_to_node(i, j, h, w);
      for(int dir = 0; dir < 4; dir++) {
        int ni = i + di[dir];
        int nj = j + dj[dir];
        if(out_of_grid(ni, nj, h, w)) continue;
        if(grid[ni][nj] == 0) continue;
        int nxt = coordinate_to_node(ni, nj, h, w);
        g[cur].push_back({nxt, 1});
        g[nxt].push_back({cur, 1});
      }
    }
  }

  return g;
}
