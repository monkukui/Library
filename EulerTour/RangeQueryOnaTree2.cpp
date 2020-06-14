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
template <typename T,typename E, typename F, typename G, typename H>
struct LazySegmentTree{
    //using F = function<T(T,T)>;
    //using G = function<T(T,E)>;
    //using H = function<E(E,E)>;
    int n,height;
    F f;
    G g;
    H h;
    T ti;
    E ei;
    vector<T> dat;
    vector<E> laz;
    LazySegmentTree(F f,G g,H h,T ti,E ei):
        f(f),g(g),h(h),ti(ti),ei(ei){}

    void init(int n_){
        n=1;height=0;
        while(n<n_) n<<=1,height++;
        dat.assign(2*n,ti);
        laz.assign(2*n,ei);
    }
    void build(const vector<T> &v){
        int n_=v.size();
        init(n_);
        for(int i=0;i<n_;i++) dat[n+i]=v[i];
        for(int i=n-1;i;i--)
            dat[i]=f(dat[(i<<1)|0],dat[(i<<1)|1]);
    }
    inline T reflect(int k){
        return laz[k]==ei?dat[k]:g(dat[k],laz[k]);
    }
    inline void eval(int k){
        if(laz[k]==ei) return;
        laz[(k<<1)|0]=h(laz[(k<<1)|0],laz[k]);
        laz[(k<<1)|1]=h(laz[(k<<1)|1],laz[k]);
        dat[k]=reflect(k);
        laz[k]=ei;
    }
    inline void thrust(int k){
        for(int i=height;i;i--) eval(k>>i);
    }
    inline void recalc(int k){    
        while(k>>=1)
            dat[k]=f(reflect((k<<1)|0),reflect((k<<1)|1));
    }
    void update(int a,int b,E x){
        thrust(a+=n);
        thrust(b+=n-1);
        for(int l=a,r=b+1;l<r;l>>=1,r>>=1){
            if(l&1) laz[l]=h(laz[l],x),l++;
            if(r&1) --r,laz[r]=h(laz[r],x);
        }
        recalc(a);
        recalc(b);
    }
    void set_val(int a,T x){
        thrust(a+=n);
        dat[a]=x;laz[a]=ei;
        recalc(a);
    }
    T query(int a,int b){
        thrust(a+=n);
        thrust(b+=n-1);
        T vl=ti,vr=ti;
        for(int l=a,r=b+1;l<r;l>>=1,r>>=1) {
            if(l&1) vl=f(vl,reflect(l++));
            if(r&1) vr=f(reflect(--r),vr);
        }
        return f(vl,vr);
    }
};

/* 
 *    [考えるべきこと]
 *    区間をマージしてから作用素を作用させても、作用素を作用させてから区間をマージするのと結果が同じ
 *    複数の作用素をマージして一度に作用させられること
 *    作用素を伝搬し終わっているのかの判定に必要（まあこれは満たされていなくても最悪どうにかなる）
 *    O(N) とかだと困る（setのマージとか）
 *    区間の長さに比例して作用が変わるときは，practice/RSRA や Library-Checher の RangeAffineRangeSum を参照する
 * 
 */

/**  テンプレ
int main(){
}
**/

/**  テンプレ
int main(){
}
**/

using T = pair<lint, int>;  // type T
using E = lint;  // type E

void dfs(int cur, int par, vector<vector<int>> &g, vector<T> &tour, vector<int> &fst, vector<int> &lst) {
  int id = tour.size();
  fst[cur] = id;
  tour.push_back({0, 1});
  for (auto nxt : g[cur]) {
    if (nxt == par) continue;
    dfs(nxt, cur, g, tour, fst, lst);
  }
  id = tour.size();
  lst[cur] = id;
  tour.push_back({0, -1});
}

int main() {
  
  int n; cin >> n;
  vector<vector<int>> graph(n);
  for (int i = 0; i < n; i++) {
    int k; cin >> k;
    for (int j = 0; j < k; j++) {
      int to; cin >> to;
      graph[i].push_back(to);
      graph[to].push_back(i);
    }
  }


  vector<T> tour;
  vector<int> fst(n);
  vector<int> lst(n);
  dfs(0, -1, graph, tour, fst, lst);

  /*
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
  sg.build(tour);
  */
  auto f = [](T a, T b){ // return type T value
    return make(a.first + b.first, a.second + b.second);
  };
  auto g = [](T a, E b){ // return type T value
    if (a.second > 0) return {a.first + b, a.second};
    else return make_pair(a.first - b, a.second);
  };
  auto h = [](E a, E b){ // return type E value
    return a + b;
  };
  T ti = 0;  // identity element
  E ei = 0;  // identity element
  LazySegmentTree<T, E, decltype(f), decltype(g), decltype(h)> sg(f, g, h, ti, ei);  // don't change
  sg.build(tour);


  int q; cin >> q;
  for (int i = 0; i < q; i++) {
    int op; cin >> op;
    if (op == 0) {
      lint v, w; cin >> v >> w;
      sg.update(0, fst // 辛い
      sg.update(fst[v] - 1, w);
      sg.update(lst[v], -w);
    } else {
      int u; cin >> u;
      cout << sg.query(0, fst[u]) << endl;
    }
  }
  return 0;
}
