#ifndef CPP20_ADVANCED_PROGRAMMING_DATA_TABLE_H
#define CPP20_ADVANCED_PROGRAMMING_DATA_TABLE_H
#include <cstddef>
#include <bitset>
#include <iostream>
#include "../professional_cpp/format.h"
#include "type_list.h"

using std::cout;
namespace template_meta_programming {
//Key => ValueType
template<auto Key, typename ValueType, size_t Dim = 1>
struct entry
{
    static constexpr auto key = Key;
    static constexpr size_t dim = Dim;
    static constexpr bool is_array = Dim > 1;
    using type = ValueType;
};

template<auto Key, typename ValueType, size_t Dim>
struct entry<Key, ValueType[Dim]> : entry<Key, ValueType, Dim> {};

template<typename E>
concept KVEntry = requires
{
    typename E::type;
    requires std::is_standard_layout_v<typename E::type>;
    requires std::is_trivial_v<typename E::type>;
    { E::key } -> std::convertible_to<size_t >;
    { E::dim } -> std::convertible_to<size_t >;
};

static_assert(KVEntry<entry<0, char[10]>>);

//////////////////////////////////////////////////////
// GroupEntriesTrait
template<TL Es = type_list<>, TL Gs = type_list<>>
struct group_entries_trait : Gs {};

template<TL Es = type_list<>, TL Gs = type_list<>>
using group_entries_trait_t = group_entries_trait<Es, Gs>::type;

template<KVEntry H, KVEntry ...Ts, TL Gs>
class group_entries_trait<type_list<H, Ts...>, Gs>
{
    template<KVEntry E>
    using group_prediction = std::bool_constant<H::dim == E::dim
                                                && sizeof(H::type) == sizeof(E::type)
                                                && alignof(H::type) == alignof(E::type)>;

    using group = partition_t<type_list<H, Ts...>, group_prediction>;
    using satisfied = typename group::satisfied;
    using rest = typename group::rest;
public:
    using type = typename group_entries_trait<rest, typename Gs::template append<satisfied>>::type;
};


template<TL Gs>
class group_index_trait
{
    template<size_t GroupIdx = 0, size_t InnerIdx = 0, TL Res = type_list<>>
    struct index
    {
        constexpr static size_t group_index = GroupIdx;
        constexpr static size_t inner_index = InnerIdx;
        using result = Res;
    };

    template<typename Acc, TL G>
    class add_group
    {
        constexpr static size_t group_index = Acc::group_index;

        template<typename Acc_, KVEntry E>
        class add_key
        {
            constexpr static size_t inner_index = Acc_::inner_index;
            struct key_with_index
            {
                constexpr static auto key = E::key;
                constexpr static auto id = (group_index << 16) | inner_index;
            };
            using result = typename Acc_::result::template append<key_with_index>;
        public:
            using type = index<group_index + 1, inner_index + 1, result>;
        };

        using result = typename Acc::result;
    public:
        using type = fold_t<G, index<group_index + 1, 0, result>, add_key>;
    };

public:
    using type = typename fold_t<Gs, index<>, add_group>::result;
};

template<TL Gs>
using group_index_trait_t = group_index_trait<Gs>::type;


template<TL Es>
class data_table
{
    template<KVEntry EH, KVEntry ...ET>
    class generic_region
    {
        constexpr static size_t number_of_entries = sizeof...(ET) + 1;
        constexpr static size_t max_size = std::max(alignof(typename EH::type),
                                                    sizeof(typename EH::type)) * EH::dim;
        char data[number_of_entries][max_size];
    public:
        bool get_data(size_t nth_data, void *out, size_t len)
        {
            if (nth_data >= number_of_entries) [[unlikely]]
            { return false; }
            copy_n(data[nth_data], std::min(len, max_size), reinterpret_cast<char *>(out));
            return true;
        }

        bool set_data(size_t nth_data, const void *value, size_t len)
        {
            if (nth_data >= number_of_entries) [[unlikely]]
            { return false; }
            copy_n(reinterpret_cast<const char *>(value), std::min(len, max_size), data[nth_data]);
            return true;
        }
    };

    template<typename... R>
    class regions
    {
        std::tuple<R...> m_regions;

        template<size_t I, typename OP>
        bool for_data(OP &&op, size_t index)
        {
            size_t region_idx = index >> 16;
            size_t nth_data = index & 0xFFFF;
            if (I == region_idx)
            { return op(std::get<I>(m_regions), nth_data); }
            return false;
        }

        template<typename OP, size_t... Is>
        bool for_data(std::index_sequence<Is...>, OP &&op, size_t index)
        {
            return (for_data<Is>(std::forward<OP>(op), index) || ...);
        }

    public:
        bool get_data(size_t index, void *out, size_t len)
        {
            auto op = [&](auto &region, size_t nth_data) { return region.get_data(nth_data, out, len); };
            return for_data(std::make_index_sequence<sizeof...(R)>{}, op, index);
        }

        bool set_data(size_t index, const void *value, size_t len)
        {
            auto op = [&](auto &region, size_t nth_data) { return region.set_data(nth_data, value, len); };
            return for_data(std::make_index_sequence<sizeof...(R)>{}, op, index);
        }
    };

    template<TL Gs>
    class generic_region_trait
    {
        template<TL G>
        using to_region = return_<typename G::template to<generic_region>>;
    public:
        using type = map_t<Gs, to_region>;
    };

    template<TL Gs>
    using generic_region_trait_t = generic_region_trait<Gs>::type;

    template<typename ...Indexes>
    struct indexer
    {
        size_t key_to_id[sizeof...(Indexes)]{};
        std::bitset<sizeof...(Indexes)> mask;

        constexpr indexer()
        {
            constexpr size_t index_size = sizeof...(Indexes);
            static_assert(((Indexes::key < index_size) && ...), "key is out of size");
            (void(key_to_id[Indexes::key] = Indexes::id), ...);
        }
    };

    using Gs = group_entries_trait_t<Es>;
    using regions_class = typename generic_region_trait_t<Gs>::template to<regions>;
    using indexer_class = typename group_index_trait_t<Gs>::template to<indexer>;

    regions_class m_regions;
    indexer_class m_indexer;
public:
    bool get_data(size_t key, void *out, size_t len = -1)
    {
        if (key >= Es::size || !m_indexer.mask[key])
        { return false; }
        return m_regions.get_data(m_indexer.key_to_id[key], out, len);
    }

    bool set_data(size_t key, const void *value, size_t len = -1)
    {
        if (key >= Es::size)
        {
            return false;
        }
        return m_indexer.mask[key] =
                       m_regions.set_data(m_indexer.key_to_id[key], value, len);
    }

    void dump_group_info()
    {
        cout << std::format("sizeof data_table = {}\n", sizeof(data_table));
        cout << std::format("sizeof Region = {}\n", sizeof(regions_class));
        cout << std::format("sizeof indexer = {}\n", sizeof(indexer_class));
        for (size_t k = 0; k < Es::size; ++k)
        {
            cout << std::format("key = {} id = {:#05x} group = {} subgroup = {}\n", k,
                   m_indexer.key_to_id[k],
                   m_indexer.key_to_id[k] >> 16,
                   m_indexer.key_to_id[k] & 0xFFFF);
        }
    }
};






















}

































#endif