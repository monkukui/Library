template<typename Weight>
struct edge{
    size_t src, dst;
    Weight cost;

    edge() = default;
    edge(size_t src, size_t dst, Weight const& cost): src(src), dst(dst), cost(cost){}

    bool operator <(edge const &other) const{
        if(cost != other.cost) return cost < other.cost;
        if(src != other.src) return src > other.src;
        return dst < other.dst;
    }
};

template<typename Weight>
struct graph: std::vector<std::vector<edge<Weight>>>{
    graph(size_t n): std::vector<std::vector<edge<Weight>>>(n){}

    void connect_to(size_t src, size_t dst, Weight const& cost){
        (*this)[src].emplace_back(src, dst, cost);
    }

    void connect_with(size_t src, size_t dst, Weight const& cost){
        connect_to(src, dst, cost);
        connect_to(dst, src, cost);
    }
};

template<typename Weight>
std::vector<Weight> shortest(graph<Weight> const &g, size_t s = 0, Weight inf = numeric_limits<Weight>::max(), Weight ei = Weight()){
    // based on Dijkstra algorithm
    size_t n = g.size();
    std::vector<Weight> res(n, inf);
    using P = std::pair<Weight, size_t>;
    std::priority_queue<P, std::vector<P>, std::greater<P>> pq;
    res[s] = ei;
    pq.emplace(res[s], s);

    while(!pq.empty()){
        Weight cur_cost;
        size_t cur_node;
        std::tie(cur_cost, cur_node) = pq.top();
        pq.pop();
        if(res[cur_node] < cur_cost) continue;
        for(auto const& e: g[cur_node]){
            Weight next_cost = cur_cost+ e.cost;
            size_t next_node = e.dst;
            if(res[next_node] > next_cost){
                res[next_node] = next_cost;
                pq.emplace(next_cost, next_node);
            }
        }
    }

    return res;
}
