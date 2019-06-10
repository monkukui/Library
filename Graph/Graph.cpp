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
