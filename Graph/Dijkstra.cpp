// verified : http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_A
// 負辺があると動作しない?
// O(E log V)
template<typename T>
vector<T> dijkstra(vector<vector<pair<int, T>>> &g, int s){
     
    int n = g.size();
    // numeric_limits がうまく使えない場合は自分で INF を定義する.
    const auto inf = numeric_limits<T>::max();
    vector<T> dist(n, inf);
 
    using P = pair<T, int>;
    // 小さい順に取り出せる
    priority_queue<P, vector<P>, greater<P>> que;
    dist[s] = 0;
    que.emplace(dist[s], s);
    while(!que.empty()){
        T cost;
        int node;
        tie(cost, node) = que.top();
        que.pop();
        if(dist[node] < cost) continue;
        for(auto &e : g[node]){
            auto next_cost = cost + e.second;
            int next_node = e.first;
            if(dist[next_node] <= next_cost) continue;
            dist[next_node] = next_cost;
            que.emplace(next_cost, next_node);
        }
    }
 
    return dist;
}
