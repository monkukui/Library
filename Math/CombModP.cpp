// nCr mod p を計算する（p は素数）
// 前処理 O(p ^ 2)
// クエリ O(log n)
struct CombModP {
    vector<vector<long long>> com;
    long long p;
    CombModP(long long _p) : p(_p) {
        init(p);
    }
    void init(long long p) {
        com.assign(p, vector<long long>(p));
        com[0][0] = 1;
        for (int i = 1; i < p; i++) {
            com[i][0] = 1;
            for (int j = i; j > 0; j--) {
                com[i][j] = (com[i - 1][j - 1] + com[i - 1][j]) % p;
            }
        }
    }
    long long nCk(long long n, long long k) {
        long long ret = 1;
        while (n > 0) {
            int ni = n % p;
            int ki = k % p;
            ret *= com[ni][ki];
            ret %= p;
            n /= p;
            k /= p;
        }
        return ret;
    }
};

