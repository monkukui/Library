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
  using T = ***;  // type T
  using E = ***;  // type E
  auto f = [](T a, T b){ // return type T value
    return ***;
  };
  auto g = [](T a, E b){ // return type T value
    return ***;
  };
  auto h = [](E a, E b){ // return type E value
    return ***;
  };
  T ti = ***;  // identity element
  E ei = ***;  // identity element
  LazySegmentTree<T, E, decltype(f), decltype(g), decltype(h)> sg(f, g, h, ti, ei);  // don't change
  sg.build(***);
}
**/
