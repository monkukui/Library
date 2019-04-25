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

// 1 点更新区間取得
// 条件は要素がモノイドであること（あるいは半群？）
// 有名どころは 和, 積, min, max gcd lcm
// プラスアルファで行列 ?



template <typename T>
struct SegmentTree{
    using F = function<T(T, T)>;
    int n;
    F f;
    T ti;
    vector<T> dat;
    SegmentTree(){};
    SegmentTree(F f, T ti, const vector<T> &v):f(f),ti(ti){
        int sz = v.size();
        n = 1;
        while(n < sz) n <<= 1;
        dat.assign(2 * n - 1, ti);
        for(int i = 0; i < sz; i++) dat[n - 1 + i] = v[i];
        for(int i = n - 2; i >= 0; i--) dat[i] = f(dat[2 * i + 1], dat[2 * i + 2]);
    }

    // x 番目(0 - indexed) の要素を val に更新
    void update(int x, T val){
        x += (n - 1);
        dat[x] = val;
        while(x > 0){
            x = (x - 1) / 2;
            dat[x] = f(dat[2 * x + 1], dat[2 * x + 2]);
        }
    }

    // 区間[a, b)を取得する
    T query(int a, int b, int k, int l, int r){
        if(r <= a || b <= l) return ti;
        if(a <= l && r <= b) return dat[k];
        T vl = query(a, b, k * 2 + 1, l, (l + r) / 2);
        T vr = query(a, b, k * 2 + 2, (l + r) / 2, r);
        return f(vl, vr);
    }
    
    T query(int a, int b){
        return query(a, b, 0, 0, n);
    }
};


signed main(){

    int n, q; cin >> n >> q;
    int ti = 2147483647;
    vector<int> v(n, ti);
    auto f = [](int a, int b){return min(a, b);};
    // 関数, 単位元, 元の配列の順に宣言
    SegmentTree<int> sg(f, ti, v);
    
    for(int i = 0; i < q; i++){
        int c, x, y; cin >> c >> x >> y;
        if(c) cout << sg.query(x, y + 1) << endl;
        else sg.update(x, y);
    }

    return 0;
}

