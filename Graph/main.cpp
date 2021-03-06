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


template< typename T >
struct Dinic{
    const T inf;

    struct edge{
        int to;
        T cap;
        int rev;
        bool isrev;
    };

    vector<vector<edge>> g;
    vector<int> min_cost, iter;

    Dinic(int V) : inf(numeric_limits<T>::max()), g(V){}

    void add_edge(int from, int to, T cap){
        g[from].emplace_back((edge){to, cap, (int)g[to].size(), false});
        g[to].emplace_back((edge){from, 0, (int)g[from].size() - 1, true});
    }

    bool bfs(int s, int t) {
        min_cost.assign(g.size(), -1);
        queue<int> que;
        min_cost[s] = 0;
        que.push(s);
        while(!que.empty() && min_cost[t] == -1){
            int p = que.front();
            que.pop();
            for(auto &e : g[p]) {
                if(e.cap > 0 && min_cost[e.to] == -1){
                    min_cost[e.to] = min_cost[p] + 1;
                    que.push(e.to);
                }
            }
        }
        return min_cost[t] != -1;
    }
    T dfs(int idx, const int t, T flow){
        if(idx == t) return flow;
        for(int &i = iter[idx]; i < g[idx].size(); i++){
            edge &e = g[idx][i];
            if(e.cap > 0 && min_cost[idx] < min_cost[e.to]){
                T d = dfs(e.to, t, min(flow, e.cap));
                if(d > 0){
                    e.cap -= d;
                    g[e.to][e.rev].cap += d;
                    return d;
                }
            }
        }
    return 0;
  }
    
    T max_flow(int s, int t){
        T flow = 0;
        while(bfs(s, t)){
            iter.assign(g.size(), 0);
            T f = 0;
            while((f = dfs(s, t, inf)) > 0) flow += f;
        }

        return flow;
    }
};

signed main(){
    
    int n, m; cin >> n >> m;
    Dinic<int> g(n);
    for(int i = 0; i < m; i++){
        int a, b, c; cin >> a >> b >> c;
        g.add_edge(a, b, c);
    }
    cout << g.max_flow(0, n - 1) << endl;
    return 0;
}
