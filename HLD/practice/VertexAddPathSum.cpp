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

/* do your best */

int main() {
  
  int n, q; cin >> n >> q;
  vector<lint> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }

  HLD hld(n);
  for (int i = 0; i < n - 1; i++) {
    int u, v; cin >> u >> v;
    hld.add_edge(u, v);
  }

  hld.build();

  using T = lint;  // type T
  using E = lint;  // type E
  auto f = [](T a, T b){ // return type T value
    return a + b;
  };
  auto g = [](T a, E b){ // return type T value
    return a + b;  // return b;
  };
  T ti = 0;  // identity element
  SegmentTree<T, E, decltype(f), decltype(g)> sg(f, g, ti);  // don't change
  sg.build(vector<lint> (n, 0));

  for (int i = 0; i < n; i++) {
    sg.update(hld.vid[i], a[i]);
  }

  for (int i = 0; i < q; i++) {
    int op; cin >> op;
    if (op == 0) {
      lint p, x; cin >> p >> x;
      sg.update(hld.vid[p], x);
    } else {
      int u, v; cin >> u >> v;
      lint ans = 0;
      hld.for_each(u, v, [&](int l, int r) {
        ans += sg.query(l, r);
      });
      cout << ans << endl;
    }
  }

  return 0;
}
