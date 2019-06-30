// 最小全域木を求めるアルゴリズム
// Union Find を使う方
// O(E log V)
// verify : http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_2_A&lang=jp

struct UnionFind{
    
    vector<int> M_par;
    vector<int> M_rank;
    vector<int> M_size;

private:
    void init(int n = 1){
        M_par.resize(n);
        M_rank.resize(n);
        M_size.resize(n);
        for(int i = 0; i < n; i++){
            M_par[i] = i;
            M_rank[i] = 0;
            M_size[i] = 1;
        }
    }

public:

    UnionFind(size_t n = 1){
        init(n);
    }

    size_t find(size_t x){
        if(M_par[x] == x) return x;
        size_t r = find(M_par[x]);
        return M_par[x] = r;
    }
    
    bool same(size_t x, size_t y){
        return find(x) == find(y);
    }

    bool unite(size_t x, size_t y){
        x = find(x);
        y = find(y);
        if(x == y) return false;
        if(M_rank[x] < M_rank[y]) swap(x, y);
        if(M_rank[x] == M_rank[y]) M_rank[x]++;
        M_par[y] = x;
        M_size[x] = M_size[x] + M_size[y];
        return true;
    }

    size_t size(size_t x){
        return M_size[find(x)];
    }

};


// [入力] undirected-graph [出力] コスト
template<typename T>
T kruskal(vector<vector<pair<int, T>>> &g){
    
    int n = (int)g.size();
    //{cost, {to, from}}
    vector<pair<T, pair<int, int>>> edges;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < g[i].size(); j++){
            edges.push_back({g[i][j].second, {i, g[i][j].first}});
        }
    }

    sort(edges.begin(), edges.end());
    UnionFind uf(n);
    T ret = 0;
    for(int i = 0; i < (int)edges.size(); i++){
        if(uf.unite(edges[i].second.first, edges[i].second.second)) ret += edges[i].first;
    }

    return ret;
}
