// 抽象二次元累積和
// 構築 O(hw), get O(1)
// TODO verify (https://atcoder.jp/contests/arc089/tasks/arc089_b)

//       ^
//       u
//  <= l   r =>
//       d
//       v      

template<typename T>
struct RecSum{
private: 
  size_t h, w;
  vector<vector<T>> dat;

public: 
  RecSum(const vector<vector<T>> &v){
    h = v.size();
    w = v[0].size();
    dat.resize(h + 1);
    for(size_t i = 0; i < h + 1; i++) dat[i].resize(w + 1, 0);
    for(size_t i = 0; i < h; i++){
      for(size_t j = 0; j < w; j++){
        dat[i + 1][j + 1] = v[i][j] + dat[i + 1][j];
      }
    }
    for(size_t j = 0; j < w; j++){
      for(size_t i = 0; i < h; i++){
        dat[i + 1][j + 1] += dat[i][j + 1];
      }
    }
  }

  T get(size_t l, size_t r, size_t u, size_t d) const { // 0-indexed, [l, r), [u, d)
    return dat[d][r] - dat[u][r] - dat[d][l] + dat[u][l];
  }
};
