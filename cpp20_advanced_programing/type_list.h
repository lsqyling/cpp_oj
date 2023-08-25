#ifndef CPP20_ADVANCED_PROGRAMMING_TYPE_LIST_H
#define CPP20_ADVANCED_PROGRAMMING_TYPE_LIST_H
#include <type_traits>
#include <vector>

namespace template_meta_programming {
template<typename ...Ts>
struct type_list
{
    struct is_type_list {};
    using type = type_list;
    static constexpr size_t size = sizeof...(Ts);
    template<typename ...T> using append = type_list<Ts..., T...>;
    template<typename ...T> using prepend = type_list<T..., Ts...>;
    template<template<typename ...> class T> using to = T<Ts...>;
};

template<typename TypeList>
concept TL = requires
{
    typename TypeList::type;
    typename TypeList::is_type_list;
};

template<TL In, template<typename> class F>
struct map;
template<template<typename> class F, typename ...Ts>
struct map<type_list<Ts...>, F> : type_list<typename F<Ts>::type...> {};

template<TL In, template<typename> class P, TL Out = type_list<>>
struct filter : Out {};

template<template<typename> class P, TL Out, typename H, typename ...Ts>
struct filter<type_list<H, Ts...>, P, Out> :
        std::conditional_t<P<H>::value,
                filter<type_list<Ts...>, P, typename Out::template append<H>>,
                filter<type_list<Ts...>, P, Out>> {};

template<TL In, template<typename> class F>
using map_t = typename map<In, F>::type;

template<TL In, template<typename> class P>
using filter_t = typename filter<In, P>::type;

using long_list = type_list<char, float, double, int, char, std::vector<int>>;

template<typename T>
using less_size4 = std::bool_constant<sizeof(T) < 4>;

template<typename T>
struct return_
{
    using type = T;
};

template<TL In, typename Init, template<typename, typename> class Op>
struct fold : return_<Init> {};

template<typename Acc, template<typename, typename> class Op,
        typename H, typename ...Ts>
struct fold<type_list<H, Ts...>, Acc, Op> : fold<type_list<Ts...>, typename Op<Acc, H>::type, Op> {};

template<TL In, typename Init, template<typename, typename> class Op>
using fold_t = fold<In, Init, Op>::type;

template<typename Acc, typename E>
using type_size_acc = std::integral_constant<size_t, Acc::value + sizeof(E)>;


// 1. concat alg.
template<TL... In>
struct concat;

template<TL... In>
using concat_t = concat<In...>::type;

template<>
struct concat<> : type_list<> {};

template<TL In>
struct concat<In> : In {};

template<TL In1, TL In2, TL ...Reset>
struct concat<In1, In2, Reset...> : concat_t<concat_t<In1, In2>, Reset...> {};


template<typename ...Ts, typename ...Ts2>
struct concat<type_list<Ts...>, type_list<Ts2...>> : type_list<Ts..., Ts2...> {};


//2. elem alg.
template<TL In, typename E>
struct elem : std::false_type {};

template<typename E, typename...Ts>
struct elem<type_list<Ts...>, E> : std::bool_constant<(false || ... || std::is_same_v<E, Ts>)> {};

template<TL In, typename E>
inline constexpr bool elem_v = elem<In, E>::value;

//3. unique alg.
template<TL In>
class unique
{
    template<TL Acc, typename E>
    using append = std::conditional_t<elem_v<Acc, E>, Acc, typename Acc::template append<E>>;
public:
    using type = fold_t<In, type_list<>, append>;
};

template<TL In>
using unique_t = unique<In>::type;


//4. partition alg.
template<TL In, template<typename> class P>
class partition
{
    template<typename Arg>
    using not_p = std::bool_constant<!P<Arg>::value>;
public:
    struct type
    {
        using satified = filter_t<In, P>;
        using rest = filter_t<In, not_p>;
    };
};

template<TL In, template<typename> class P>
using partition_t = partition<In, P>::type;

using split_by_size4 = partition_t<long_list, less_size4>;

// 5. sort alg.

template<TL In, template<typename, typename> class Cmp>
struct sort : type_list<> {};

template<template<typename, typename> class Cmp, typename Pivot, typename ...Ts>
struct sort<type_list<Pivot, Ts...>, Cmp>
{
private:
    template<typename E> using lt = Cmp<E, Pivot>;
    using p = partition_t<type_list<Ts...>, lt>;
    using small_sorted = typename sort<typename p::satified, Cmp>::type;
    using bigger_sorted = typename sort<typename p::rest, Cmp>::type;
public:
    using type = concat_t<typename small_sorted::template append<Pivot>,
            bigger_sorted>;
};

template<TL In, template<typename, typename> class Cmp>
using sort_t = sort<In, Cmp>::type;


template<typename L, typename R>
using size_of_cmp = std::bool_constant<sizeof(L) < sizeof(R)>;

// 6. Cartesian Product alg.
template<TL A, TL B, template<typename, typename> class Pair>
struct cross_product
{
    template<TL ResultOuter, typename ElemA>
    struct outer_append
    {
        template<TL ResultInner, typename ElemB>
        using inner_append = typename ResultInner::template append<Pair<ElemA, ElemB>>;
        using type = fold_t<B, ResultOuter, inner_append>;
    };

    using type = fold_t<A, type_list<>, outer_append>;
};


template<TL A, TL B, template<typename, typename> class Pair>
using cross_product_t = cross_product<A, B, Pair>::type;
static_assert(cross_product_t<long_list, long_list, std::pair>::size ==
              long_list::size * long_list::size);



}
#endif