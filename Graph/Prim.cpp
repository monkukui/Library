// 最小全域技を求める
// O(E log V)
// verify http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_2_A


template<typename T>
T prim(vector<vector<pair<int, T>>> &g){
    int n = (int)g.size();
    T ret = 0;
    vector<bool> used(n, false);
    using P = pair<T, int>;
    priority_queue<P, vector<P>, greater<P>> que;
    que.push({0, 0});
    while(!que.empty()){
        auto p = que.top();
        que.pop();
        if(used[p.second]) continue;
        used[p.second] = true;
        ret += p.first;
        for(auto &e : g[p.second]){
            que.push({e.second, e.first});
        }
    }

    return ret;
}
