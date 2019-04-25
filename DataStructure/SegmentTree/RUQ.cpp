#include <iostream>
#include <iomanip>
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
#include <cfloat>
#include <climits>
#include <ctime>
#include <cassert>
#include <numeric>
#include <fstream>
#include <functional>
#include <bitset>

using namespace std;
#define int long long int
const int INF = 1001001001001001LL;
const int MOD = 1000000007;

// 区間更新区間取得
// 遅延評価セグ木

template <typename T, typename E>
struct SegmentTree{
    using F = function<T(T, T)>;
    using G = function<T(T, E)>;
    using H = function<E(E, E)>;
    using P = function<E(E, int)>;
    int n;
    F f;
    G g;
    H h;
    P p;
    T ti;
    E ei;
    vector<T> dat;
    vector<E> laz;
    SegmentTree(){};
    SegmentTree(F f, G g, H h, T ti, E ei, const vector<T> &v, P p=[](E a, int b){return a;}):
                f(f),g(g),h(h),ti(ti),ei(ei),p(p){
        int sz = v.size();
        n = 1;
        while(n < sz) n <<= 1;
        dat.assign(2 * n - 1, ti);
        laz.resize(2 * n - 1, ei);
        for(int i = 0; i < sz; i++) dat[n - 1 + i] = v[i];
        for(int i = n - 2; i >= 0; i--) dat[i] = f(dat[2 * i + 1], dat[2 * i + 2]);
    }
    
    inline void eval(int len, int k){
            
        if(laz[k] == ei) return;
        if(k * 2 + 1 < n * 2 - 1){
            laz[k * 2 + 1] = h(laz[k * 2 + 1], laz[k]);
            laz[k * 2 + 2] = h(laz[k * 2 + 2], laz[k]);
        }
        dat[k] = g(dat[k], p(laz[k], len));
        laz[k] = ei;
    }

    // 区間[a, b) に x を g する
    T update(int a, int b, E x, int k, int l, int r){
        eval(r - l, k);
        if(r <= a || b <= l) return dat[k];
        if(a <= l && r <= b){
            laz[k] = h(laz[k], x);
            return g(dat[k], p(laz[k], r - l));
        }

        return dat[k] = f(update(a, b, x, k * 2 + 1, l, (l + r) / 2), update(a, b, x, k * 2 + 2, (l + r) / 2, r));
    }

    T update(int a, int b, E x){
        return update(a, b, x, 0, 0, n);
    }

    
    T query(int a, int b, int k, int l, int r){
        eval(r - l, k);
        if(r <= a || b <= l) return ti;
        if(a <= l && r <= b) return dat[k];
        T vl = query(a, b, k * 2 + 1, l, (l + r) / 2);
        T vr = query(a, b, k * 2 + 2, (l + r) / 2, r);
        return f(vl, vr);
    }

    T query(int a, int b){
        return query(a, b, 0, 0, n);
    }
      
};

signed main(){
    
    int n, q; cin >> n >> q;
    int ti = 2147483647;
    int ei = -1;
    vector<int> v(n, ti);
    auto f = [](int a, int b){return a;};
    auto g = [&](int a, int b){
        if(b == ei) return a;    
        else return b;
    };

    auto h = [&](int a, int b){
        if(b == ei) return a;
        else return b;
    };

    SegmentTree<int, int> sg(f, g, h, ti, ei, v);
    
    for(int i = 0; i < q; i++){
        int c; cin >> c;
        if(c){
            int x; cin >> x;
            cout << sg.query(x, x + 1) << endl;
        }else{
            int s, t, x; cin >> s >> t >> x;
            sg.update(s, t + 1, x);
        }
    }

    return 0;
}

