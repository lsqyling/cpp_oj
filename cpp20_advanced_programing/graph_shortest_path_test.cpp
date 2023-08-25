#include <cstddef>
#include "type_list.h"


using namespace template_meta_programming;

template<typename Node>
concept Vertex = requires
{
    Node::id;
};

template<Vertex F, Vertex T>
struct edge
{
    using from = F;
    using to = T;
};

template<typename Node = void>
requires (Vertex<Node> || std::is_void_v<Node>)
struct edge_trait
{
    template<typename Edge>
    using is_from = std::is_same<typename Edge::from, Node>;
    template<typename Edge>
    using is_to = std::is_same<typename Edge::to, Node>;
    template<typename Edge>
    using get_from = return_<typename Edge::from>;
    template<typename Edge>
    using get_to = return_<typename Edge::to>;
};

template<typename Link, TL Out = type_list<>>
struct chain;

template<Vertex F, TL Out>
struct chain<auto (*)(F) -> void, Out>
{
    using from = F;
    using type = Out;
};

template<Vertex F, Vertex T, TL Out>
struct chain<auto (*)(F) -> T, Out>
{
private:
    using to = typename chain<T, Out>::from;
public:
    using from = F;
    using type = typename chain<T, typename Out::template append<edge<from, to>>>::type;
};

template<typename Link>
using chain_t = chain<Link>::type;

#define NODE(NODE)          auto(*) (NODE)
#define LINK(LINK)          LINK -> void

template<typename ...Chains>
class graph
{
    using edges = unique_t<concat_t<chain_t<Chains>...>>;

    template<Vertex From, Vertex To, TL Path>
    struct path_finder;
//    1. To reach the target, add the target to the path.
    template<Vertex Target, TL Path>
    struct path_finder<Target, Target, Path> : Path::template append<Target> {};
//    2. A cycle was found, returning an empty path.
    template<Vertex CurrNode, Vertex Target, TL Path>
    requires elem_v<Path, CurrNode>
    struct path_finder<CurrNode, Target, Path> : type_list<> {};

    template<Vertex CurrNode, Vertex Target, TL Path = type_list<>>
    class path_finder
    {
        using edges_from = filter_t<edges, edge_trait<CurrNode>::template is_from>;
        using next_nodes = map_t<edges_from, edge_trait<>::get_to>;

        template<Vertex AdjacentNode>
        using get_path = path_finder<AdjacentNode, Target, typename Path::template append<CurrNode>>;

        using all_path_from_cur_node = map_t<next_nodes, get_path>;

        template<TL AccMinPath, TL Path_>
        using get_min_path = std::conditional_t<AccMinPath::size == 0
                                                || (AccMinPath::size > Path_::size
                                                    && Path_::size > 0), Path_, AccMinPath>;
    public:
        using type = fold_t<all_path_from_cur_node, type_list<>, get_min_path>;
    };


    template<typename NodeType>
    struct path_ref
    {
        const NodeType *path;
        size_t sz;
    };

    template<Vertex Node, Vertex ...Nodes>
    class path_storage
    {
        using node_type = std::decay_t<decltype(Node::id)>;
        static constexpr node_type path_array[]{Node::id, Nodes::id...};

    public:
        static constexpr path_ref<node_type> path{
                .path = path_array,
                .sz = sizeof...(Nodes) + 1
        };
    };


    template<Vertex From, Vertex To>
    using path_finder_t = path_finder<From, To>::type;

    using all_node_pairs = cross_product_t<unique_t<map_t<edges, edge_trait<>::get_from>>,
            unique_t<map_t<edges, edge_trait<>::get_to>>,
            std::pair>;

    template<typename NodePair>
    using is_non_empty_path = std::bool_constant<(path_finder_t<typename NodePair::first_type,
            typename NodePair::second_type>::size > 0)>;


    using reachable_node_pairs = filter_t<all_node_pairs, is_non_empty_path>;


    template<typename NodePair>
    using save_path = return_<std::pair<NodePair,
            typename path_finder_t<typename NodePair::first_type,
                    typename NodePair::second_type>::template to<path_storage>>>;

    using saved_all_path = map_t<reachable_node_pairs, save_path>;

    template<typename NodeType, Vertex From, Vertex Target, typename PathStorage>
    static constexpr bool math_path(NodeType from, NodeType to,
                                    path_ref<NodeType> &result,
                                    std::pair<std::pair<From, Target>, PathStorage>)
    {
        if (From::id == from && Target::id == to)
        {
            result = PathStorage::path;
            return true;
        }
        return false;
    }


    template<typename NodeType, typename...PathPairs>
    static constexpr void math_path(NodeType from, NodeType to,
                                    path_ref<NodeType> &result,
                                    type_list<PathPairs...>)
    {
        (math_path(from, to, result, PathPairs{}) || ...);
    }

public:

    template<typename NodeType>
    static constexpr path_ref<NodeType> get_path(NodeType from, NodeType to)
    {
        path_ref<NodeType> result;
        math_path(from, to, result, saved_all_path{});
        return result;
    }
};

template<char ID>
struct node
{
    static constexpr char id = ID;
};

//using A = node<'A'>;
//using B = node<'B'>;
//using C = node<'C'>;
//using D = node<'D'>;
//using E = node<'E'>;
//
//using g = graph<
////        LINK(NODE(A)-> NODE(B) -> NODE(C) -> NODE(D)),
////        LINK(NODE(A) -> NODE(C)),
////        LINK(NODE(B) -> NODE(A)),
////        LINK(NODE(A) -> NODE(E))
////
////
//        auto (*)(A) -> auto (*)(B) -> auto(*)(C) -> auto (*)(D) -> void,
//        auto (*)(A) -> auto (*)(C) -> void,
//        auto (*)(B) -> auto (*)(A) -> void,
//        auto (*)(A) -> auto (*)(E) -> void
//        >;
//static_assert(g::get_path('A', 'D').sz == 3);
//




int main()
{
    return 0;
}