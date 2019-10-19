// 個数制限なしナップサック問題
// O(nW)
vector<long long> KnapsackProblem(vector<long long> &v, vector<long long> &w, long long W) {
  size_t n = v.size();
  vector<vector<long long>> dp(n + 1, vector<long long> (W + 1, 0));
  for(size_t i = 0; i < n; i++) {
    for(size_t j = 0; j <= W; j++) {
      if(j < w[i]) {
        dp[i + 1][j] = dp[i][j];
      } else {
        dp[i + 1][j] = max(dp[i][j], dp[i + 1][j - w[i]] + v[i]);
      }
    }
  }
  return dp[n];
}
