
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

// えびちゃんの make_vector (ここから)
template <typename Tp, size_t N>
std::vector<Tp> make_vector_detail(std::vector<size_t>& sizes, typename std::enable_if<(N == 1), const Tp&>::type x) {
  return std::vector<Tp>(sizes[0], x);
}
template <typename Tp, size_t N>
auto make_vector_detail(std::vector<size_t>& sizes, typename std::enable_if<(N > 1), const Tp&>::type x) {
  size_t size = sizes[N-1];
  sizes.pop_back();
  return std::vector<decltype(make_vector_detail<Tp, N-1>(sizes, x))>(size, make_vector_detail<Tp, N-1>(sizes, x));
}

template <typename Tp, size_t N>
auto make_vector(const size_t(&sizes)[N], const Tp& x) {
  std::vector<size_t> s(N);
  for (size_t i = 0; i < N; ++i) s[i] = sizes[N-i-1];
  return make_vector_detail<Tp, N>(s, x);
}
// えびちゃんの make_vector (ここまで)

signed main(){
    
    return 0;
}
