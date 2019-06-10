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
template <typename T, typename F>
struct SegmentTree{
    // using F = typename<T(T, T)>
    int n;
    F f;
    T ti;
    vector<T> dat;
    SegmentTree(){};
    SegmentTree(F f,T ti):f(f),ti(ti){}
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
    void set_val(int k,T x){
        dat[k+=n]=x;
        while(k>>=1)
            dat[k]=f(dat[(k<<1)|0],dat[(k<<1)|1]);    
    }
    T get_val(int k){
        return dat[k+n];
    }
    T query(int a,int b){
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
    }
    */
};

signed main(){
    
    int n, q; cin >> n >> q;
    auto f = [](int a, int b){ return a + b; };
    SegmentTree<int, decltype(f)> sg(f, 0);
    sg.build(vector<int>(n, 0));

    for(int i = 0; i < q; i++){
        int com, x, y; cin >> com >> x >> y;
        if(!com) sg.set_val(x - 1, sg.get_val(x - 1) + y);
        else cout << sg.query(x - 1, y) << endl;
    }

    return 0;
}
