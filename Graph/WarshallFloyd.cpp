vector<vector<long long>> WarshallFloyd(const vector<vector<pair<int, long long>>> &g) {
  const long long L_INF = 1001001001001001LL;
  int n = g.size();
  vector<vector<long long>> dist(n, vector<long long> (n, L_INF));
  for(int i = 0; i < n; i++) dist[i][i] = 0;
  for(int k = 0; k < n; k++)
    for(int i = 0; i < n; i++)
      for(int j = 0; j < n; j++)
        dist[i][j] = min(dist[i][k] + dist[k][j], dist[i][j]);

  return dist;
}
