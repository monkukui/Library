#include "atcoder/modint.hpp"
#include <iostream>
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
#include <climits>
#include <ctime>
#include <cassert>
#include <numeric>
#include <functional>
#include <bitset>
#include <cstddef>
#include <type_traits>
#include <vector>

using namespace std;
const long long int INF = numeric_limits<long long int>::max() / 4;
const int inf = numeric_limits<int>::max() / 4;
const long long int MOD1000000007 = 1000000007;
const long long int MOD998244353 = 998244353;
const double MATH_PI = 3.1415926535897932;

template<typename T1, typename T2>
inline void chmin(T1 &a, const T2 &b) { if (a > b) a = b; }

template<typename T1, typename T2>
inline void chmax(T1 &a, const T2 &b) { if (a < b) a = b; }

#define lint long long int
#define ALL(a) a.begin(),a.end()
#define RALL(a) a.rbegin(),a.rend()
#define rep(i, n) for(int i=0;i<(int)(n);i++)
#define VI vector<int>
#define VLL vector<long long>
#define VC vector<char>
#define VB vector<bool>
#define PI pair<int, int>
#define PLL pair<long long, long long>
#define VPI vector<pair<int, int>>
#define VPLL vector<pair<long long, long long>>
#define VVI vector<vector<int>>
#define VVPI vecor<vector<pair<int, int>>>
#define VVPILL vector<vector<pair<int, long long>>>

#define SUM(v) accumulate(ALL(v), 0LL)
#define MIN(v) *min_element(ALL(v))
#define MAX(v) *max_element(ALL(v))


const int MAX_ROW = 2510; // to be set appropriately
const int MAX_COL = 2510; // to be set appropriately

struct BitMatrix {
    int H, W;
    bitset<MAX_COL> val[MAX_ROW];

    BitMatrix(int m = 1, int n = 1) : H(m), W(n) {}

    inline bitset<MAX_COL> &operator[](int i) { return val[i]; }
};

int GaussJordan(BitMatrix &A, bool is_extended = false) {
    int rank = 0;
    for (int col = 0; col < A.W; ++col) {
        if (is_extended && col == A.W - 1) break;
        int pivot = -1;
        for (int row = rank; row < A.H; ++row) {
            if (A[row][col]) {
                pivot = row;
                break;
            }
        }
        if (pivot == -1) continue;
        swap(A[pivot], A[rank]);
        for (int row = 0; row < A.H; ++row) {
            if (row != rank && A[row][col]) A[row] ^= A[rank];
        }
        ++rank;
    }
    return rank;
}

int linear_equation(BitMatrix A, vector<int> b, vector<int> &res) {
    int m = A.H, n = A.W;
    BitMatrix M(m, n + 1);
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) M[i][j] = A[i][j];
        M[i][n] = b[i];
    }
    int rank = GaussJordan(M, true);

    // check if it has no solution
    for (int row = rank; row < m; ++row) if (M[row][n]) return -1;

    // answer
    res.assign(n, 0);
    for (int i = 0; i < rank; ++i) res[i] = M[i][n];
    return rank;
}

using mint = atcoder::static_modint<1000000009>;

void f() {

    int h, w;
    cin >> h >> w;
    vector<vector<int>> s(h, vector<int>(w));
    rep (i, h) {
        rep (j, w) {
            cin >> s[i][j];
        }
    }

    int n = h * w;
    // cout << "n = " << n << endl;
    BitMatrix A(n, n);
    vector<int> b(n, 0);
    rep (i, h) {
        rep (j, w) {
            int mi = i * w + j;
            b[mi] = s[i][j];
            // A[mi][mi] = 1;
            rep (ii, h) {
                rep (jj, w) {
                    if (i == ii or j == jj or (i + j == ii + jj) or (i - j == ii - jj)) {
                        int mj = ii * w + jj;
                        A[mi][mj] = 1;
                    }
                }
            }
        }
    }

    vector<int> res;
    // for (int i = 0; i < n; i++) {
    //     for (int j = 0; j < n; j++) {
    //         cout << A[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    // for (int i = 0; i < n; i++) {
    //     cout << b[i] << endl;
    // }
    int rank = linear_equation(A, b, res);
    if (rank == -1) {
        cout << 0 << endl;
    } else {
        cout << mint(2).pow(n - rank).val() << endl;
    }
}

int main() {

    f();
    return 0;
}
