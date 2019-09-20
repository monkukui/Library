struct StronglyConnectedComponents {
public:
  const int n;
  vector<bool> isthrough;
  vector<int> vs, cmp;
  vector< vector<int> > G, rG, H; // グラフ、逆辺グラフ、縮約後のグラフ

  StronglyConnectedComponents(vector<vector<int>> &g) :
    n(g.size()), isthrough(n, false), cmp(n, 0), G(n), rG(n) {
    for(int i = 0; i < n; i++) {
      for(size_t j = 0; j < g[i].size(); j++) {
        G[i].push_back(g[i][j]);
        rG[g[i][j]].push_back(i);
      }
    }
  }

  void SccDfsOne(int cur) {
    isthrough[cur] = true;
    for(size_t i = 0; i < G[cur].size(); i++) {
      if(!isthrough[G[cur][i]]) {
        SccDfsOne(G[cur][i]);
      }
    }
    vs.push_back(cur);
  }

  void SccDfsTwo(vector<int> &vec, int cur, int k) {
    cmp[cur] = k;
    isthrough[cur] = true;
    vec.push_back(cur);
    for(size_t i = 0; i < rG[cur].size(); i++) {
      if(!isthrough[rG[cur][i]]) {
        SccDfsTwo(vec, rG[cur][i], k);
      }
    }
  }

  // 縮約後のグループ、グループ数
  pair<vector<int>, int> scc() {
    // 1回めのDFS
    for(int i = 0; i < n; i++)
      if(!isthrough[i]) SccDfsOne(i);

    fill(isthrough.begin(), isthrough.end(), false);
    reverse(vs.begin(), vs.end());
    int k = 0; vector<vector<int>> S;

    // 2回めのDFS
    for(size_t i = 0; i < vs.size(); i++) {
      if(!isthrough[vs[i]]) {
        S.push_back(vector<int>());
        SccDfsTwo(S.back(), vs[i], k++);
      }
    }

    H.resize(k);
    fill(isthrough.begin(), isthrough.end(), false);
    for(size_t i = 0; i < k; i++) {
      for(size_t j = 0; j < S[i].size(); j++) {
        int v = S[i][j];
        for(size_t x = 0; x < G[v].size(); x++) {
          int u = G[v][x];
          if(isthrough[cmp[u]] or cmp[v] == cmp[u]) continue;
          isthrough[cmp[u]] = true;
          H[cmp[v]].push_back(cmp[u]);
        }
      }
      for(size_t j=0; j<H[i].size(); j++) isthrough[H[i][j]] = false;
    }
    return make_pair(cmp, k);
  }
};
