#include "atcoder/all"
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


// 引用：https://drken1215.hatenablog.com/entry/2019/03/20/202800
const double EPS = 1e-10;

// matrix
template<class T>
struct Matrix {
    vector<vector<T> > val;

    Matrix(int n, int m, T x = 0) : val(n, vector<T>(m, x)) {
        init(n, m, x);
    }

    void init(int n, int m, T x = 0) { val.assign(n, vector<T>(m, x)); }

    size_t size() const { return val.size(); }

    inline vector<T> &operator[](int i) { return val[i]; }
};

template<class T>
int GaussJordan(Matrix<T> &A, bool is_extended = false) {
    int m = A.size(), n = A[0].size();
    int rank = 0;
    for (int col = 0; col < n; ++col) {
        // 拡大係数行列の場合は最後の列は掃き出ししない
        if (is_extended && col == n - 1) break;

        // ピボットを探す
        int pivot = -1;
        T ma = EPS;
        for (int row = rank; row < m; ++row) {
            if (abs(A[row][col]) > ma) {
                ma = abs(A[row][col]);
                pivot = row;
            }
        }
        // ピボットがなかったら次の列へ
        if (pivot == -1) continue;

        // まずは行を swap
        swap(A[pivot], A[rank]);

        // ピボットの値を 1 にする
        auto fac = A[rank][col];
        for (int col2 = 0; col2 < n; ++col2) A[rank][col2] /= fac;

        // ピボットのある列の値がすべて 0 になるように掃き出す
        for (int row = 0; row < m; ++row) {
            if (row != rank && abs(A[row][col]) > EPS) {
                auto fac = A[row][col];
                for (int col2 = 0; col2 < n; ++col2) {
                    A[row][col2] -= A[rank][col2] * fac;
                }
            }
        }
        ++rank;
    }
    return rank;
}

template<class T>
vector<T> linear_equation(Matrix<T> A, vector<T> b) {
    // extended
    int m = A.size(), n = A[0].size();
    Matrix<T> M(m, n + 1);
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) M[i][j] = A[i][j];
        M[i][n] = b[i];
    }
    int rank = GaussJordan(M, true);

    // check if it has no solution
    vector<T> res;
    for (int row = rank; row < m; ++row) {
        if (abs(M[row][n]) > EPS) return res;
    }

    // answer
    res.assign(n, 0);
    for (int i = 0; i < rank; ++i) res[i] = M[i][n];
    return res;
}

int di[] = {0, 1, 0, -1};
int dj[] = {1, 0, -1, 0};

void dfs(int i, int j, vector<vector<char>> &g, vector<vector<bool>> &can_reach) {
    int n = g.size();
    int m = g[0].size();
    for (int dir = 0; dir < 4; dir++) {
        int ni = i + di[dir];
        int nj = j + dj[dir];
        if (ni < 0 or nj < 0 or ni >= n or nj >= m) continue;
        if (g[ni][nj] == '#') continue;
        if (can_reach[ni][nj]) continue;
        can_reach[ni][nj] = true;
        dfs(ni, nj, g, can_reach);
    }
}

int main() {

    // グリッドの input
    int h, w; cin >> h >> w;
    vector<vector<char>> g(h, vector<char>(w));
    rep (i, h) {
        rep (j, w) {
            cin >> g[i][j];
        }
    }

    // 到達できるところをあらかじめ計算しておく
    vector<vector<bool>> can_reach(h, vector<bool>(w, false));
    can_reach[0][0] = true;
    dfs(0, 0, g, can_reach);

    // 各マスとその四方向について連立方程式を立てる
    int n = h * w;
    Matrix<double> A(n, n);
    vector<double> b(n, 0.0);
    auto to_id = [&](int i, int j){
        return i * w + j;
    };
    rep (i, h) {
        rep (j, w) {
            int mi = to_id(i, j);
            if (i == h - 1 and j == w - 1) {
                A[mi][mi] = 1.0;
                b[mi] = 0.0;
                continue;
            }

            if (!can_reach[i][j]) {
                // 到達不可能な場合
                int mj = to_id(i, j);
                A[mi][mj] = 1.0;
                b[mi] = 0.0;
            } else {
                // 到達可能な場合
                double cnt = 0.0;
                for (int dir = 0; dir < 4; dir++) {
                    int ni = i + di[dir];
                    int nj = j + dj[dir];
                    if (ni < 0 or nj < 0 or ni >= h or nj >= w) continue;
                    if (g[ni][nj] == '#') continue;
                    cnt += 1.0;
                }

                // E(x, y) = \sum {1/cnt * E(nx, ny)} + 1 みたいな感じになる
                for (int dir = 0; dir < 4; dir++) {
                    int ni = i + di[dir];
                    int nj = j + dj[dir];
                    if (ni < 0 or nj < 0 or ni >= h or nj >= w) continue;
                    if (g[ni][nj] == '#') continue;

                    int mj = to_id(ni, nj);
                    A[mi][mj] = -1.0 / cnt;
                }
                A[mi][mi] = 1.0;
                b[mi] = 1.0;
            }
        }
    }

    auto ans = linear_equation(A, b);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << A[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    for (int i = 0; i < n; i++) {
        cout << b[i] << endl;
    }
    printf("%.10f\n", ans[0]);
    return 0;
}
