// LIS
// dp[i] := ながさ i にしたときの最小要素
// O(n log n)
vector<long long> LongestIncreasingSubsequence(vector<long long> &a) {
  size_t n = a.size();
  vector<long long> dp(n + 1, INF);
  for(size_t i = 0; i < n; i++) {
    *lower_bound(dp.begin(), dp.end(), a[i]) = a[i];
  }
  return dp;
}
