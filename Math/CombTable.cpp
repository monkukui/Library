// nCr を計算する
// 前処理 O(n ^ 2)
// クエリ O(1)
struct CombModP {
    vector<vector<long long>> com;
    void init(long long n) {
        com.assign(n + 1, vector<long long>(n + 1, 0));
        com[0][0] = 1;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j <= n; j++) {
              if (j + 1 <= n) com[i + 1][j + 1] += com[i][j];
              com[i + 1][j] += com[i][j];
            }
        }
    }
    long long nCk(long long n, long long k) {
        return com[n][k];
    }
};

