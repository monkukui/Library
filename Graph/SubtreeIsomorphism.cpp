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
using lint = long long int;
long long int INF = 1001001001001001LL;
int inf = 1000000007;
long long int MOD = 1000000007LL;
double PI = 3.1415926535897932;

template<typename T1, typename T2>
inline void chmin(T1 &a, const T2 &b) { if (a > b) a = b; }

template<typename T1, typename T2>
inline void chmax(T1 &a, const T2 &b) { if (a < b) a = b; }

#define ALL(a) a.begin(),a.end()
#define RALL(a) a.rbegin(),a.rend()
#define rep(i, n) for(int i=0;i<(int)(n);i++)


// verified : http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_6_A
// O(E V^2)

// [使い方]
// add_edge(from, to, cap) :  from から to へ 容量 cap の辺を貼る
// max_flow(s, t) :  s から t への最大フローを返す
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


    // 0-indexed
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

    // 0-indexed
    T max_flow(int s, int t){
        T flow = 0;
        while(bfs(s, t)){
            iter.assign(g.size(), 0);
            T f = 0;
            while((f = dfs(s, t, inf)) > 0) flow += f;
        }

        return flow;
    }

    void output() {
        for(int i = 0; i < g.size(); i++) {
            for(auto &e : g[i]) {
                if(e.isrev) continue;
                auto &rev_e = g[e.to][e.rev];
                cout << i << "->" << e.to << " (flow: " << rev_e.cap << "/" << e.cap + rev_e.cap << ")" << endl;
            }
        }
    }
};

void reach(int cur, vector<vector<int>> &g, vector<bool> &visited) {
    visited[cur] = true;
    for (auto nxt : g[cur]) {
        if (visited[nxt]) continue;
        reach(nxt, g, visited);
    }
}

bool dfs(int v, int par, const vector<vector<int>> &G, const vector<vector<int>> &H, vector<vector<set<int>>> &S) {
    const int k = H.size();

    vector<int> children_of_v;
    for (auto nxt : G[v]) {
        if (nxt == par) continue;
        children_of_v.push_back(nxt);
        if (dfs(nxt, v, G, H, S)) {
            return true;
        }
    }

    // base_case
    if (children_of_v.size() == 0) {
        for (int u = 0; u < k; u++) {
            if (H[u].size() == 1) {
                S[v][u].insert(H[u][0]);
            }
        }
        return false;
    }

    // calculate S(v, u)
    for (int u = 0; u < k; u++) {
        vector<int> children_of_u;
        for (auto ch : H[u]) {
            children_of_u.push_back(ch);
        }
        int t = children_of_v.size(); // degree of vertex v
        int s = children_of_u.size(); // degree of vertex u
        // require t >= s - 1
        // require degree(v) >= degree(u) - 1
        if (t < s - 1) continue;

        // construct a bipartite graph
        Dinic<int> bipartite_graph(t + s + 2);
        int source = s + t;
        int sink = s + t + 1;
        for (int i = 0; i < t; i++) {
            bipartite_graph.add_edge(source, i, 1);
        }
        for (int i = 0; i < s; i++) {
            bipartite_graph.add_edge(i + t, sink, 1);
        }

        for (int cv_i = 0; cv_i < t; cv_i++) {
            for (int cu_i = 0; cu_i < s; cu_i++) {
                int cv = children_of_v[cv_i];
                int cu = children_of_u[cu_i];

                // if u \in S(cv, cu) then add edge
                if (S[cv][cu].find(u) != S[cv][cu].end()) {
                    bipartite_graph.add_edge(cv_i, cu_i + t, 1);
                }
            }
        }

        // for all 0 \leq i \leq s do compute the size  m_i of a maximum matching between X_i and Y
        vector<int> m(s + 1, 0);
        m[s] = bipartite_graph.max_flow(source, sink);

        // construct a directed graph B_M
        vector<vector<int>> directed_graph(s + t + 1);
        int super_node = s + t;
        for (int i = 0; i < t + s; i++) {
            for (auto &e : bipartite_graph.g[i]) {
                if (e.isrev) continue;
                auto &rev_e = bipartite_graph.g[e.to][e.rev];
                if (i < t) {
                    if (rev_e.cap == 0) {
                        directed_graph[e.to].push_back(i);
                    } else {
                        directed_graph[i].push_back(e.to);
                    }
                } else {
                    if (rev_e.cap == 0) {
                        directed_graph[super_node].push_back(i);
                    }
                }
            }
        }

        // find critical vertex
        vector<bool> visited(s + t + 1, false);
        visited[super_node] = true;
        reach(super_node, directed_graph, visited);
        for (int i = 0; i < s; i++) {
            if (!visited[i + t]) {
                // this is critical vertex
                m[i] = m[s] - 1;
            } else {
                // this is not critical vertex
                m[i] = m[s];
            }
        }

        for (int i = 0; i < s; i++) {
            if (m[i] == s - 1) {
                S[v][u].insert(children_of_u[i]);
            }
        }
        if (m[s] == s) {
            return true;
        }
    }

    return false;
}

bool SubtreeIsomorphism(const vector <vector<int>> &G, const vector <vector<int>> &H) {
    int n = G.size();
    int k = G.size();
    vector<vector<set<int>>> S(n, vector<set<int>>(k));
    return dfs(0, -1, G, H, S);
}

int main() {

    // input tree G, H
    int n;
    cin >> n;
    vector <vector<int>> G(n);
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        G[a].push_back(b);
        G[b].push_back(a);
    }

    int k;
    cin >> k;
    vector <vector<int>> H(k);
    for (int i = 0; i < k - 1; i++) {
        int a, b;
        cin >> a >> b;
        H[a].push_back(b);
        H[b].push_back(a);
    }

    if (SubtreeIsomorphism(G, H)) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }
    return 0;
}
