// 単一始点全点間最短路を求めるアルゴリズム
// 不平路を検出した時は、空列を返す
// O(VE)

// verified http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_B

template<typename T>
vector<T> bellman_ford(vector<vector<pair<int, T>>> g, int s){

    int n = (int)g.size();
    // ここで怒られる場合は inf を自分で定義する
    const auto inf = numeric_limits<T>::max();
    vector<T> dist(n, inf);
    dist[s] = 0;
    for(int i = 0; i < n - 1; i++){
        for(int u = 0; u < n; u++){
            for(auto &e : g[u]){
                if(dist[u] == inf) continue;
                dist[e.first] = min(dist[e.first], dist[u] + e.second);
            }
        }
    }

    for(int u = 0; u < n; u++){
        for(auto &e : g[u]){
            if(dist[u] == inf) continue;
            if(dist[u] + e.second < dist[e.first]) return vector<T>();
        }
    }

    return dist;
}
