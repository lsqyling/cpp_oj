#ifndef PROFESSIONAL_STL_DIRECTED_GRAPH_H
#define PROFESSIONAL_STL_DIRECTED_GRAPH_H
#include <vector>
#include "graph_node.h"


template<typename T>
class directed_graph
{
public:
    // For an insert to be successful, the value shall not be in the graph yet.
    // Returns true if a new node with given value has been added to
    // the graph, and false if there was already a node with the given value.
    bool insert(const T &node_value);

    bool insert(T &&node_value);

    // Returns true if the given node value was erased, false otherwise.
    bool erase(const T &node_value);

    // Returns true if the edge was successfully created, false otherwise.
    bool insert_edge(const T &from_node_value, const T &to_node_value);

    // Returns true if the given edge was erased, false otherwise.
    bool erase_edge(const T &from_node_value, const T &to_node_value);

    // Removes all nodes from the graph.
    void clear() noexcept;

    // Returns a reference to the node with given index.
    // No bounds checking is done.
    T &operator[](size_t index);

    const T &operator[](size_t index) const;

    // Two directed graphs are equal if they have the same nodes and edges.
    // The order in which the nodes and edges have been added does not
    // affect equality.
    bool operator==(const directed_graph &rhs) const;

    bool operator!=(const directed_graph &rhs) const;

    // Swaps all nodes between this graph and the given graph.
    void swap(directed_graph &other_graph) noexcept;

    // Returns the number of nodes in the graph.
    size_t size() const noexcept;

    // Returns a set with the adjacent nodes of a given node.
    // If the given node does not exist, an empty set is returned.
    std::set<T> get_adjacent_nodes_values(const T &node_value) const;

private:
    friend details::graph_node<T>;
    using nodes_container_type = std::vector<details::graph_node<T>>;
    nodes_container_type m_nodes;

    nodes_container_type::iterator find_node(const T &node_value);

    nodes_container_type::const_iterator find_node(const T &node_value) const;

    // Given an iterator to a node, removes that node from all adjacency lists
    // of all other nodes.
    void remove_all_links_to(nodes_container_type::const_iterator node_iter);

    std::set<size_t> get_adjacent_nodes_values(
            const details::graph_node<T>::adjacency_list_type &indices) const;

    size_t get_index_node(const nodes_container_type::const_iterator &node_iter) const noexcept;

};

template<typename T>
void swap(directed_graph<T> &first, directed_graph<T> &second) noexcept;




#endif