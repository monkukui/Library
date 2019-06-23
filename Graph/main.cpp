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

int di[] = {-1, 0, 1, 0, -1, 1, 1, -1};
int dj[] = {0, 1, 0, -1, 1, 1, -1, -1};


template<typename T>
vector<T> dijkstra(vector<vector<pair<int, T>>> &g, int s){
    
    int n = g.size();
    // numeric_limits がうまく使えない場合は自分で INF を定義する.
    const auto inf = numeric_limits<T>::max();
    vector<T> dist(n, inf);

    using P = pair<T, int>;
    // 小さい順に取り出せる
    priority_queue<P, vector<P>, greater<P>> que;
    dist[s] = 0;
    que.emplace(dist[s], s);
    while(!que.empty()){
        T cost;
        int node;
        tie(cost, node) = que.top();
        que.pop();
        if(dist[node] < cost) continue;
        for(auto &e : g[node]){
            auto next_cost = cost + e.second;
            int next_node = e.first;
            if(dist[next_node] <= next_cost) continue;
            dist[next_node] = next_cost;
            que.emplace(next_cost, next_node);
        }
    }

    return dist;
}

signed main(){
    
    int V, E, R; cin >> V >> E >> R;
    vector<vector<pair<int, int>>> g(V);
    for(int i = 0; i < E; i++){
        int a, b, c; cin >> a >> b >> c;
        g[a].push_back({b, c});
    }

    auto result = dijkstra<int>(g, R);
    for(int i = 0; i < V; i++){
        if(result[i] == numeric_limits<int>::max()) puts("INF");
        else printf("%lld\n", result[i]);
    }
    return 0;
}
