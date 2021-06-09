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

lint sum(lint x) {
    lint ret = 0;
    while (x > 0) {
        ret += x % 10;
        x /= 10;
    }
    return ret;
}

lint f(lint x) {
    lint y = sum(x);
    return (x + y) % 100000;
}

int main() {

    lint n, k;
    cin >> n >> k;
    lint m = 100000;
    vector<vector<lint>> to(60, vector<lint>(m));
    for (int i = 0; i < m; i++) {
        // i の遷移先が f(i)
        to[0][i] = f(i);
    }
    for (int i = 0; i < 60 - 1; i++) {
        for (int j = 0; j < m; j++) {
            to[i + 1][j] = to[i][to[i][j]];
        }
    }

    // n から始まって k step 先を求める
    lint cur = n;
    for (lint i = 60 - 1; i >= 0; i--) {
        if (k >> i & 1) {
            cur = to[i][cur];
        }
    }
    cout << cur << endl;
    return 0;
}

// 問題：https://atcoder.jp/contests/typical90/tasks/typical90_bf

// 総和とかもなんかできる
// ボンドさん：https://twitter.com/bond_cmprog/status/1307316401871282180/photo/1
