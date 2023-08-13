#include "directed_graph.h"

template<typename T>
void swap(directed_graph<T> &first, directed_graph<T> &second) noexcept
{
    first.swap(second);

}


template<typename T>
bool directed_graph<T>::insert(const T &node_value)
{
    T tmp{node_value};
    return insert(std::move(tmp));
}

template<typename T>
bool directed_graph<T>::insert(T &&node_value)
{
    auto it = find_node(node_value);
    if (it != std::end(m_nodes))
        return false;
    m_nodes.emplace_back(this, std::move(node_value));
    return true;
}

template<typename T>
bool directed_graph<T>::erase(const T &node_value)
{


    return false;
}

template<typename T>
bool directed_graph<T>::insert_edge(const T &from_node_value, const T &to_node_value)
{
    const auto from{find_node(from_node_value)};
    const auto to{find_node(to_node_value)};
    if (from == std::end(m_nodes) || to == std::end(m_nodes))
        return false;
    size_t to_index = get_index_node(to);
    return from->get_adjacent_nodes_indices().insert(to_index).second;


}

template<typename T>
bool directed_graph<T>::erase_edge(const T &from_node_value, const T &to_node_value)
{
    return false;
}

template<typename T>
void directed_graph<T>::clear() noexcept
{

}

template<typename T>
T &directed_graph<T>::operator[](size_t index)
{
    return <#initializer#>;
}

template<typename T>
const T &directed_graph<T>::operator[](size_t index) const
{
    return <#initializer#>;
}

template<typename T>
bool directed_graph<T>::operator==(const directed_graph &rhs) const
{
    return false;
}

template<typename T>
bool directed_graph<T>::operator!=(const directed_graph &rhs) const
{
    return false;
}

template<typename T>
void directed_graph<T>::swap(directed_graph &other_graph) noexcept
{

}

template<typename T>
size_t directed_graph<T>::size() const noexcept
{
    return 0;
}

template<typename T>
std::set<T> directed_graph<T>::get_adjacent_nodes_values(const T &node_value) const
{
    return std::set<T>();
}

template<typename T>
std::vector<details::graph_node<T>>::iterator directed_graph<T>::find_node(const T &node_value)
{
    return std::vector<details::graph_node<T>>::iterator();
}

template<typename T>
std::vector<details::graph_node<T>>::const_iterator directed_graph<T>::find_node(const T &node_value) const
{
    return std::vector<details::graph_node<T>>::const_iterator();
}

template<typename T>
void directed_graph<T>::remove_all_links_to(std::vector<details::graph_node<T>>::const_iterator node_iter)
{

}

template<typename T>
std::set<size_t>
directed_graph<T>::get_adjacent_nodes_values(const details::graph_node<T>::adjacency_list_type &indices) const
{
    return std::set<size_t>();
}

template<typename T>
size_t
directed_graph<T>::get_index_node(const std::vector<details::graph_node<T>>::const_iterator &node_iter) const noexcept
{
    const auto index = std::distance(std::cbegin(m_nodes), node_iter);
    return static_cast<size_t >(index);
}