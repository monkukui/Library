// 根は 0
// 構築 O(n log n) クエリ O(log n)
// 無向グラフ（木）を与える．
struct DoublingLowestCommonAncestor {
  const int LOG;
  vector<int> dep;
  const vector<vector<int>> &g;
  vector<vector<int>> table;

  DoublingLowestCommonAncestor(const vector<vector<int>> &g) : g(g), dep(g.size()), LOG(32 - __builtin_clz(g.size())) {
    table.assign(LOG, vector<int>(g.size(), -1));
  }

  void dfs(int idx, int par, int d) {
    table[0][idx] = par;
    dep[idx] = d;
    for (auto &to : g[idx]) {
      if (to != par) dfs(to, idx, d + 1);
    }
  }

  void build() {
    dfs(0, -1, 0);
    for (int k = 0; k + 1 < LOG; k++) {
      for (int i = 0; i < table[k].size(); i++) {
        if (table[k][i] == -1) table[k + 1][i] = -1;
        else table[k + 1][i] = table[k][table[k][i]];
      }
    }
  }
  
  // lca(u, v) を返す
  int query(int u, int v) {
    if (dep[u] > dep[v]) swap(u, v);
    for (int i = LOG - 1; i >= 0; i--) {
      if (((dep[v] - dep[u]) >> i) & 1) v = table[i][v];
    }
    if (u == v) return u;
    for (int i = LOG - 1; i >= 0; i--) {
      if (table[i][u] != table[i][v]) {
        u = table[i][u];
        v = table[i][v];
      }
    }
    return table[0][u];
  }
  
  // u の深さを返す
  int depth(int u) {
    return dep[u];
  }
};
