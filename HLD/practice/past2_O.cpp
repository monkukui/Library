#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#include <deque>
#include <list>
#include <queue>
#include <stack>
#include <vector>
#include <utility>
#include <algorithm>
#include <map>
#include <set>
#include <complex>
#include <cmath>
#include <limits>
#include <climits>
#include <ctime>
#include <cassert>
#include <numeric>
#include <functional>
#include <bitset>

using namespace std;
using lint = long long int;
long long int INF = 1001001001001001LL;
int inf = 1000000007;
long long int MOD = 1000000007LL;
double PI = 3.1415926535897932;

template<typename T1,typename T2>inline void chmin(T1 &a,const T2 &b){if(a>b) a=b;}
template<typename T1,typename T2>inline void chmax(T1 &a,const T2 &b){if(a<b) a=b;}

#define ALL(a) a.begin(),a.end()
#define RALL(a) a.rbegin(),a.rend()

/* do your best */

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
vector<pair<T, pair<int, int>>> kruskal(vector<vector<pair<int, T>>> &g, lint &treeCost){
    
    int n = (int)g.size();
    //{cost, {to, from}}
    vector<pair<T, pair<int, int>>> edges;
    vector<pair<T, pair<int, int>>> retEdges;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < g[i].size(); j++){
            edges.push_back({g[i][j].second, {i, g[i][j].first}});
        }
    }

    sort(edges.begin(), edges.end());
    UnionFind uf(n);
    T ret = 0;
    for(int i = 0; i < (int)edges.size(); i++){
        if(uf.unite(edges[i].second.first, edges[i].second.second)) {
          ret += edges[i].first;
          retEdges.push_back(edges[i]);
        }
    }

    treeCost = ret;
    return retEdges;
}

//BEGIN CUT HERE
class HLD {
private:
  void dfs_sz(int v) {
    for(int &u:G[v])
      if(u==par[v]) swap(u,G[v].back());
    if(~par[v]) G[v].pop_back();

    for(int &u:G[v]){
      par[u]=v;
      dep[u]=dep[v]+1;
      dfs_sz(u);
      sub[v]+=sub[u];
      if(sub[u]>sub[G[v][0]]) swap(u,G[v][0]);
    }
  }

  void dfs_hld(int v,int c,int &pos) {
    vid[v]=pos++;
    inv[vid[v]]=v;
    type[v]=c;
    for(int u:G[v]){
      if(u==par[v]) continue;
      head[u]=(u==G[v][0]?head[v]:u);
      dfs_hld(u,c,pos);
    }
  }

public:
  vector< vector<int> > G;
  vector<int> vid, head, sub, par, dep, inv, type;

  HLD(int n):
    G(n),vid(n,-1),head(n),sub(n,1),
    par(n,-1),dep(n,0),inv(n),type(n){}

  void add_edge(int u,int v) {
    G[u].emplace_back(v);
    G[v].emplace_back(u);
  }

  void build(vector<int> rs={0}) {
    int c=0,pos=0;
    for(int r:rs){
      dfs_sz(r);
      head[r]=r;
      dfs_hld(r,c++,pos);
    }
  }

  int lca(int u,int v){
    while(1){
      if(vid[u]>vid[v]) swap(u,v);
      if(head[u]==head[v]) return u;
      v=par[head[v]];
    }
  }

  int distance(int u,int v){
    return dep[u]+dep[v]-2*dep[lca(u,v)];
  }

  // for_each(vertex)
  // [l, r) <- attention!!
  template<typename F>
  void for_each(int u, int v, const F& f) {
    while(1){
      if(vid[u]>vid[v]) swap(u,v);
      f(max(vid[head[v]],vid[u]),vid[v]+1);
      if(head[u]!=head[v]) v=par[head[v]];
      else break;
    }
  }

  template<typename T,typename Q,typename F>
  T for_each(int u,int v,T ti,const Q &q,const F &f){
    T l=ti,r=ti;
    while(1){
      if(vid[u]>vid[v]){
        swap(u,v);
        swap(l,r);
      }
      l=f(l,q(max(vid[head[v]],vid[u]),vid[v]+1));
      if(head[u]!=head[v]) v=par[head[v]];
      else break;
    }
    return f(l,r);
  }

  // for_each(edge)
  // [l, r) <- attention!!
  template<typename F>
  void for_each_edge(int u, int v,const F& f) {
    while(1){
      if(vid[u]>vid[v]) swap(u,v);
      if(head[u]!=head[v]){
        f(vid[head[v]],vid[v]+1);
        v=par[head[v]];
      }else{
        if(u!=v) f(vid[u]+1,vid[v]+1);
        break;
      }
    }
  }
};
//END CUT HERE

// quoted from beet-aizu
template <typename T, typename E, typename F, typename G>
struct SegmentTree{
    // using F = function<T(T, T)>
    // using G = function<T(T, E)>
    int n;
    F f;
    G g;
    T ti;
    vector<T> dat;
    SegmentTree(){};
    SegmentTree(F f,G g,T ti):f(f),g(g),ti(ti){}
    void init(int n_){    
        n=1;
        while(n<n_) n<<=1;
        dat.assign(n<<1,ti);
    }
    void build(const vector<T> &v){
        int n_=v.size();
        init(n_);
        for(int i=0;i<n_;i++) dat[n+i]=v[i];
        for(int i=n-1;i;i--)
            dat[i]=f(dat[(i<<1)|0],dat[(i<<1)|1]);
    }
    void update(int k,const E &x){
        k += n;
        dat[k] = g(dat[k], x);
        while(k>>=1)
            dat[k]=f(dat[(k<<1)|0],dat[(k<<1)|1]);    
    }
    T operator [](int k) const { return dat[k+n]; }
    T query(int a,int b) const {
        T vl=ti,vr=ti;
        for(int l=a+n,r=b+n;l<r;l>>=1,r>>=1) {
            if(l&1) vl=f(vl,dat[l++]);
            if(r&1) vr=f(dat[--r],vr);
        }
        return f(vl,vr);
    }

    /* TODO わからない 聞く 
    template<typename C>
    int find(int a,int b,C &check,int k,int l,int r){
        if(!check(dat[k])||r<=a||b<=l) return -1;
        if(k>=n) return k-n;
        int m=(l+r)>>1;
        int vl=find(a,b,check,(k<<1)|0,l,m);
        if(~vl) return vl;
        return find(a,b,check,(k<<1)|1,m,r);
    }
    template<typename C>
    int find(int a,int b,C &check){
        return find(a,b,check,1,0,n);
    }*/
    
};


/**  テンプレ
int main(){
}
**/

int main() {
  
  int n, m; cin >> n >> m;
  vector<vector<pair<int, lint>>> gg(n);
  vector<pair<lint, pair<int, int>>> original;
  for (int i = 0; i < m; i++) {
    int a, b;
    lint c;
    cin >> a >> b >> c;
    a--;
    b--;
    gg[a].push_back({b, c});
    gg[b].push_back({a, c});

    original.push_back({c, {a, b}});
  }

  lint treeCost;
  auto edges = kruskal(gg, treeCost);
  assert(edges.size() == n - 1);
  set<pair<lint, pair<int, int>>> treeEdge;
  for (auto e : edges) {
    treeEdge.insert(e);
    swap(e.second.first, e.second.second);
    treeEdge.insert(e);
  }

  vector<vector<pair<int, lint>>> g(n);

  HLD hld(n);
  for (auto e : edges) {
    lint cost;
    int u, v;
    cost = e.first;
    u = e.second.first;
    v = e.second.second;

    // え？こういう書き方出来ひんの？
    // tie(cost, tie(u, v)) = e;
    g[u].push_back({v, cost});
    g[v].push_back({u, cost});
    hld.add_edge(u, v);
  }

  hld.build();
  
  // 区間 max セグ木
  using T = lint;  // type T
  using E = lint;  // type E
  auto f = [](T a, T b){ // return type T value
    return max(a, b);
  };
  auto ggg = [](T a, E b){ // return type T value
    return b;  // return b;
  };
  T ti = 0;  // identity element
  SegmentTree<T, E, decltype(f), decltype(ggg)> sg(f, ggg, ti);  // don't change
  sg.build(vector<lint> (n, 0));

  // 辺に関する値を割り振っていく
  for (auto e : edges) {
    lint cost;
    int u, v;
    cost = e.first;
    u = e.second.first;
    v = e.second.second;

    if (hld.par[u] != v) {
      swap(u, v);
    }

    assert(hld.par[u] == v);
    sg.update(hld.vid[u], cost);
  }

  for (auto e : original) {
    // 全域木に含まれているなら
    if (treeEdge.find(e) != treeEdge.end()) {
      cout << treeCost << endl;
    } else {
      lint ans = e.first + treeCost;
      int u;
      int v;
      tie(u, v) = e.second;

      // u, v パス上の最大値を取得して引く
      lint maxCost = 0;
      hld.for_each_edge(u, v, [&](int l, int r) {
        maxCost = max(maxCost, sg.query(l, r));
      });

      ans -= maxCost;

      cout << ans << endl;
    }
  }




  return 0;
}
