// 個数制限付きナップサック問題
// O(nW log(max m))
vector<long long> KnapsackProblemWithLimitations(vector<long long> v, vector<long long> w, vector<long long> m, long long W) {
  size_t n = v.size();
  vector<long long> dp(W + 1, 0);
  for(size_t i = 0; i < n; i++) {
    for(long long k = 0; m[i] > 0; k++) {
      long long key = min(m[i], (long long)(1 << k));
        m[i] -= key;
        for(long long j = W; j >= key * w[i]; j--) {
        dp[j] = max(dp[j], dp[j - key * w[i]] + key * v[i]);
      }
    }
  }
  return dp;
}
