template<typename TF,typename TC>
struct PrimalDual{
    struct edge{
        int to;
        TF cap;
        TC cost;
        int rev;
        edge(){}
        edge(int to,TF cap,TC cost,int rev):to(to),cap(cap),cost(cost),rev(rev){}
    };

    static const TC INF;
    vector<vector<edge>> G;
    vector<TC> h,dist;
    vector<int> prevv,preve;

    PrimalDual(){}
    PrimalDual(int n):G(n),h(n),dist(n),prevv(n),preve(n){}

    void add_edge(int u,int v,TF cap,TC cost){
        G[u].emplace_back(v,cap,cost,G[v].size());
        G[v].emplace_back(u,0,-cost,G[u].size()-1);
    }

    void dijkstra(int s){
        struct P{
            TC first;
            int second;
            P(TC first,int second):first(first),second(second){}
            bool operator<(const P&a) const{return a.first<first;}
        };
        priority_queue<P> que;
        fill(dist.begin(),dist.end(),INF);

        dist[s]=0;
        que.emplace(dist[s],s);
        while(!que.empty()){
            P p=que.top();que.pop();
            int v=p.second;
            if(dist[v]<p.first) continue;
            for(int i=0;i<(int)G[v].size();i++){
                edge &e=G[v][i];
                if(e.cap==0) continue;
                if(dist[v]+e.cost+h[v]-h[e.to]<dist[e.to]){
                    dist[e.to]=dist[v]+e.cost+h[v]-h[e.to];
                    prevv[e.to]=v;
                    preve[e.to]=i;
                    que.emplace(dist[e.to],e.to);
                }
            }
        }
    }

    TC flow(int s,int t,TF f,int &ok){
        TC res=0;
        fill(h.begin(),h.end(),0);
        while(f>0){
            dijkstra(s);
            if(dist[t]==INF){
                ok=0;
                return res;
            }

            for(int v=0;v<(int)h.size();v++)
                if(dist[v]<INF) h[v]=h[v]+dist[v];

            TF d=f;
            for(int v=t;v!=s;v=prevv[v])
                d=min(d,G[prevv[v]][preve[v]].cap);

            f-=d;
            res=res+h[t]*d;
            for(int v=t;v!=s;v=prevv[v]){
                edge &e=G[prevv[v]][preve[v]];
                e.cap-=d;
                G[v][e.rev].cap+=d;
            }
        }
        ok=1;
        return res;
    }
};
template<typename TF, typename TC> const TC PrimalDual<TF, TC>::INF = numeric_limits<TC>::max()/2;
