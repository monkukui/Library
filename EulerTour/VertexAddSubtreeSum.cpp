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

using T = lint;  // type T
using E = lint;  // type E

void dfs(int cur, int par, vector<vector<int>> &g, vector<T> &a, T ti, vector<int> &fst, vector<int> &lst, vector<T> &tour) {
  // 初めて出てきたら，値を入れる
  // さよならするときに，単位元を入れる
  
  int id = tour.size();
  fst[cur] = id;
  tour.push_back(a[cur]);
  for (auto nxt : g[cur]) {
    if (nxt == par) continue;
    dfs(nxt, cur, g, a, ti, fst, lst, tour);
  }
  id = tour.size();
  lst[cur] = id;
  tour.push_back(ti);
}


int main() {

  int n, q; cin >> n >> q;
  vector<lint> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  vector<vector<int>> graph(n);
  for (int i = 1; i < n; i++) {
    int p; cin >> p;
    graph[i].push_back(p);
    graph[p].push_back(i);
  }
  
  vector<lint> tour;
  vector<int> fst(n);
  vector<int> lst(n);

  T ti = 0;  // identity element
  dfs(0, -1, graph, a, ti, fst, lst, tour);

  auto f = [](T a, T b){ // return type T value
    return a + b;
  };
  auto g = [](T a, E b){ // return type T value
    return a + b;  // return b;
  };
  SegmentTree<T, E, decltype(f), decltype(g)> sg(f, g, ti);  // don't change
  sg.build(tour);

  for (int i = 0; i < q; i++) {
    int op; cin >> op;
    if (op == 0) {
      T u, x; cin >> u >> x;
      sg.update(fst[u], x);
    } else {
      int u; cin >> u;
      cout << sg.query(fst[u], lst[u]) << endl;
    }
  }
  
  return 0;
}
