// 抽象累積和
// 構築 O(n), get O(1)

template<typename T>
struct CumSum{
private: 
  size_t n;
  vector<T> dat;

public: 
  CumSum(const vector<T> &v){
    n = v.size();
    dat.resize(n + 1, 0);
    for(size_t i = 0; i < n; i++){
      dat[i + 1] = dat[i] + v[i];
    }
  }

  T get(size_t r) const { // 0-indexed, [0. r)
    return dat[r];
  }

  T get(size_t l, size_t r){ // 0-indexed, [l, r)
    return dat[r] - dat[l];
  }
};
