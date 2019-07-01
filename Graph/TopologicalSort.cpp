// トポソ
// O(V + E)
// [入力] 重みなし有効グラフ
// [出力] ソートされた頂点列(0-indexed) DAG じゃ無い場合は空列を返す
// verify http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_4_B
vector<int> toposort(vector<vector<int>> &g){
    int n = (int)g.size();
    vector<int> d(n, 0);     // 入次数
    for(int i = 0; i < n; i++){
        for(int j = 0; j < (int)g[i].size(); j++){
            d[g[i][j]]++;
        }
    }
     
    // 入次数が 0 の頂点を queue に入れる
    queue<int> que;
    for(int i = 0; i < n; i++){
        if(d[i] == 0) que.push(i);
    }
 
    vector<int> ret;
    while(!que.empty()){
        int cur = que.front();
        que.pop();
        ret.push_back(cur);
 
        for(int i = 0; i < (int)g[cur].size(); i++){
            int nxt = g[cur][i];
            d[nxt]--;
            if(d[nxt] == 0) que.push(nxt);
        }
    }
 
    // DAG じゃなかったら、頂点列が不足しているはず
    if(ret.size() == n) return ret;
    else return vector<int>();
}
