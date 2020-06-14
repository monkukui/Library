// O(E log V)
template<typename T>
vector<pair<T, int>> dijkstra(vector<vector<pair<int, T>>> &g, int s){
     
  int n = g.size();
  // numeric_limits がうまく使えない場合は自分で INF を定義する.
  const auto inf = numeric_limits<T>::max();
  vector<pair<T, int>> dist(n, {inf, -1});

  using P = pair<T, int>;
  // 小さい順に取り出せる
  priority_queue<P, vector<P>, greater<P>> que;
  dist[s] = {0, -1};
  que.emplace(dist[s].first, s);
  while(!que.empty()){
    T cost;
    int node;
    tie(cost, node) = que.top();
    que.pop();
    if(dist[node].first < cost) continue;
    for(auto &e : g[node]){
      auto next_cost = cost + e.second;
      int next_node = e.first;
      if(dist[next_node].first <= next_cost) continue;
      dist[next_node] = {next_cost, node};
      que.emplace(next_cost, next_node);
    }
  }

  return dist;
}
