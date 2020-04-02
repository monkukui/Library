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


// オイラーツアー実装例シリーズ
// Vertex
// Path
// Monoid

void dfs(int cur, int par, vector<vector<int>> &g, vector<lint> &a, vector<int> &fst, vector<int> &lst, vector<lint> &tour) {
  // 初めて出てきたら，値を入れる
  // さよならするときに，逆元を入れる
  
  int id = tour.size();
  fst[cur] = id;
  tour.push_back(a[cur]);
  for (auto nxt : g[cur]) {
    if (nxt == par) continue;
    dfs(nxt, cur, g, a, fst, lst, tour);
  }
  id = tour.size();
  lst[cur] = id;
  tour.push_back(-a[cur]);
}

// 根は 0
// 構築 O(n log n) クエリ O(log n)
// 無向グラフ（木）を与える．
struct LowestCommonAncestor {
  const int LOG;
  vector<int> dep;
  const vector<vector<int>> &g;
  vector<vector<int>> table;

  LowestCommonAncestor(const vector<vector<int>> &g) : g(g), dep(g.size()), LOG(32 - __builtin_clz(g.size())) {
    table.assign(LOG, vector<int>(g.size(), -1));
  }

  void dfs(int idx, int par, int d) {
    table[0][idx] = par;
    dep[idx] = d;
    for (auto &to : g[idx]) {
      if (to != par) dfs(to, idx, d + 1);
    }
  }

  void build() {
    dfs(0, -1, 0);
    for (int k = 0; k + 1 < LOG; k++) {
      for (int i = 0; i < table[k].size(); i++) {
        if (table[k][i] == -1) table[k + 1][i] = -1;
        else table[k + 1][i] = table[k][table[k][i]];
      }
    }
  }
  
  // lca(u, v) を返す
  int query(int u, int v) {
    if (dep[u] > dep[v]) swap(u, v);
    for (int i = LOG - 1; i >= 0; i--) {
      if (((dep[v] - dep[u]) >> i) & 1) v = table[i][v];
    }
    if (u == v) return u;
    for (int i = LOG - 1; i >= 0; i--) {
      if (table[i][u] != table[i][v]) {
        u = table[i][u];
        v = table[i][v];
      }
    }
    return table[0][u];
  }
  
  // u の深さを返す
  int depth(int u) {
    return dep[u];
  }
};

int main() {
   
  int n, q; cin >> n >> q;
  vector<lint> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }

  vector<vector<int>> graph(n);
  for (int i = 0; i < n - 1; i++) {
    int u, v; cin >> u >> v;
    graph[u].push_back(v);
    graph[v].push_back(u);
  }

  LowestCommonAncestor lca(graph);
  lca.build();
  
  vector<lint> tour;  // セグ木に載せるやつ
  vector<int> fst(n); // 初めて出現した id
  vector<int> lst(n); // 最後に出現した id
  
  dfs(0, -1, graph, a, fst, lst, tour);
  
  /*
  for (int i = 0; i < tour.size(); i++) {
    cerr << tour[i] << " ";
  }
  cerr << endl;
  for (int i = 0; i < n; i++) {
    cerr << "fst[" << i << "] = " << fst[i] << endl;
  }
  */

  using T = lint;  // type T
  using E = lint;  // type E
  auto f = [](T a, T b){ // return type T value
    return a + b;
  };
  auto g = [](T a, E b){ // return type T value
    return a + b;  // return b;
  };
  T ti = 0;  // identify element
  SegmentTree<T, E, decltype(f), decltype(g)> sg(f, g, ti);  // don't change
  sg.build(tour);   // 初期配列を代入

  for (int i = 0; i < q; i++) {
    // cerr << i << "th query" << endl;
    int op; cin >> op;
    if (op == 0) {
      // 点更新
      int p;
      lint x;
      cin >> p >> x;
      a[p] += x;
      sg.update(fst[p], x);
      sg.update(lst[p], -x);
    } else {
      int u, v; cin >> u >> v;
      int l = lca.query(u, v);
      
      // cerr << "(" << fst[0] << ", " << fst[u] + 1 << ") = " << sg.query(fst[0], fst[u] + 1) << endl;
      // cerr << "(" << fst[0] << ", " << fst[v] + 1 << ") = " << sg.query(fst[0], fst[v] + 1) << endl;
      // cerr << "(" << fst[0] << ", " << fst[l] + 1 << ") = " << sg.query(fst[0], fst[l] + 1) << endl;
      cout << sg.query(fst[0], fst[u] + 1) + sg.query(fst[0], fst[v] + 1) - 2 * sg.query(fst[0], fst[l] + 1) + a[l] << endl;
    }
  }


  return 0;
}
