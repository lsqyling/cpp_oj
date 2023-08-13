#ifndef PROFESSIONAL_STL_GRAPH_NODE_H
#define PROFESSIONAL_STL_GRAPH_NODE_H
#include <set>
template<typename T> class directed_graph;

namespace details {
template<typename T>
class graph_node
{
    friend class directed_graph<T>;

    using adjacency_list_type = std::set<size_t>;
public:
    graph_node(directed_graph<T> *graph, const T &t);

    graph_node(directed_graph<T> *graph, T &&t);

    T &value() noexcept;

    const T &value() const noexcept;

    bool operator==(const graph_node &rhs) const = default;

private:
    adjacency_list_type &get_adjacent_nodes_indices();

    const adjacency_list_type &get_adjacent_nodes_indices() const;

    directed_graph<T> *m_graph;
    T m_data;
    adjacency_list_type m_adjacent_node_indices;
};
}




#endif