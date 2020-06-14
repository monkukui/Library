// 木の直径
// O(n)
// [入力] 非負重み付き向こう木  [出力] 木の直径
// verify http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_5_A

template<typename T>
pair<T, int> dfs(const vector<vector<pair<int, T>>> &g, int idx, int par){
    
    pair<T, int> ret(0, idx);
    for(auto &e : g[idx]){
        if(e.first == par) continue;
        auto cost = dfs(g, e.first, idx);
        cost.first += e.second;
        ret = max(ret, cost);
    }

    return ret;
}

template<typename T>
T tree_diameter(const vector<vector<pair<int, T>>> &g){

    auto p = dfs(g, 0, -1);
    auto q = dfs(g, p.second, -1);
    return q.first;
}
