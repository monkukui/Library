template<typename T>
vector<vector<T>> WarshallFloyd(const vector<vector<pair<int, T>>> &g) {
  // numeric_limits がうまく使えない場合は自分で INF を定義する.
  const auto inf = numeric_limits<T>::max() / 10;
  int n = g.size();
  vector<vector<T>> dist(n, vector<T> (n, inf));
  for(int i = 0; i < n; i++) dist[i][i] = 0;

  for(int u = 0; u < n; u++) {
    for(auto e : g[u]) {
      int v = e.first;
      T cost = e.second;
      dist[u][v] = cost;
    }
  }
  for(int k = 0; k < n; k++)
    for(int i = 0; i < n; i++)
      for(int j = 0; j < n; j++)
        dist[i][j] = min(dist[i][k] + dist[k][j], dist[i][j]);

  return dist;
}

