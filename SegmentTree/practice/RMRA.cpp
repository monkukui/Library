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

signed main(){
    
    int n, q; cin >> n >> q;
    auto f = [](int a, int b){ return min(a, b); };
    auto g = [](int a, int b){ return a + b; };
    auto h = [](int a, int b){ return a + b; };
    LazySegmentTree<int, int, decltype(f), decltype(g), decltype(h)> sg(f, g, h, INT_MAX, 0);
    sg.build(vector<int>(n, 0));
    for(int i = 0; i < q; i++){
        int com; cin >> com;
        if(!com){
            int s, t, x; cin >> s >> t >> x;
            sg.update(s, t + 1, x);
        }else{
            int s, t; cin >> s >> t;
            cout << sg.query(s, t + 1) << endl;
        }
    }

    return 0;
}
