#include <iostream>
#include <array>
#include <vector>
#include "../professional_cpp/format.h"
#include "type_list.h"

using std::cout;
using std::endl;
namespace meta {
#define MAX(a, b) (((a) < (b)) ? (b) : (a))
using namespace template_meta_programming;
template<typename T>
concept Comparable = requires(T a, T b)
{
    { a < b } -> std::same_as<bool>;
};


template<typename T>
requires Comparable<T>
T max(T a, T b)
{
    return a < b ? b : a;
}

struct foo {};

void test_max_comparable()
{
    cout << "max() = " << max(3, 4) << endl;
//    max(foo{}, foo{});
}

template<size_t N>
struct fibonacci
{
    static constexpr size_t value = fibonacci<N-1>::value + fibonacci<N-2>::value;
};

template<>
struct fibonacci<0>
{
    static constexpr size_t value = 0;
};

template<>
struct fibonacci<1>
{
    static constexpr size_t value = 1;
};

void test_fibonacci()
{
    cout << "fib(10) = " << fibonacci<10>::value << endl;
}

template<typename T, size_t M, size_t N>
struct nd_grid
{
    using type = std::array<typename nd_grid<T, M, N-1>::type, M>;
    auto &operator[](size_t index)
    {
        return data_[index];
    }

private:
    std::array<nd_grid<T, M, N-1>, M> data_;
};

template<typename T, size_t M>
struct nd_grid<T, M, 1>
{
    using type = std::array<T, M>;

    T &operator[](size_t index)
    {
        return data_[index];
    }

private:
    std::array<T, M> data_;
};


void test_nd_grid()
{
    using _3d_array3 = nd_grid<int, 3, 3>::type;
    const int len = 3;
    _3d_array3 array;

    for (int i = 0; i < len; ++i)
    {
        for (int j = 0; j < len; ++j)
        {
            for (int k = 0; k < len; ++k)
            {
                array[i][j][k] = i + 2 * j + 3 * k;
            }
        }
    }

    for (int i = 0; i < len; ++i)
    {
        for (int j = 0; j < len; ++j)
        {
            for (int k = 0; k < len; ++k)
            {
                cout << std::format("array[{}][{}][{}] = {:02d}",
                                    i, j, k, array[i][j][k]) << "\n";
            }
        }
    }
}


template<typename T, size_t I, size_t ...Is>
struct ndarray
{
    using type = std::array<typename ndarray<T, Is...>::type, I>;
};

template<typename T, size_t I>
struct ndarray<T, I>
{
    using type = std::array<T, I>;
};

using _3d_array_5_4_3 = ndarray<int, 5, 4, 3>::type;
using array_543 = std::array<std::array<std::array<int, 3>, 4>, 5>;

void test_array543()
{
    static_assert(std::is_same_v<array_543, _3d_array_5_4_3>);
    _3d_array_5_4_3 example;
    example[0][1][2] = 2;
    cout << example[0][1][2] << endl;
}





void test_map_t()
{
    static_assert(std::is_same_v<map_t<long_list, std::add_pointer>,
            type_list<char *, float *, double *, int *, char *, std::vector<int> *>>);

    static_assert(std::is_same_v<filter_t<long_list, less_size4>::type, type_list<char, char>>);
    static_assert(fold_t<long_list, std::integral_constant<size_t, 0>, type_size_acc>::value == 42);

    cout << sizeof(std::vector<int>) << endl;
}

void test_check_type_list()
{
    static_assert(std::is_same_v<concat_t<type_list<int, double>, type_list<char, float>>,
            type_list<int, double, char, float>::type>);

    static_assert(elem_v<long_list, char>);
    static_assert(elem_v<long_list, double>);
    static_assert(!elem_v<long_list, long long>);
    static_assert(std::is_same_v<unique_t<long_list>,
            type_list<char, float, double, int, std::vector<int>>>);
    static_assert(std::is_same_v<split_by_size4::satified, type_list<char, char>>);
    static_assert(std::is_same_v<split_by_size4::rest, type_list<float, double, int, std::vector<int>>>);
    static_assert(std::is_same_v<sort_t<long_list, size_of_cmp>,
            type_list<char, char, float, int, double, std::vector<int>>>);
}
}





int main()
{
    meta::test_max_comparable();
    meta::test_fibonacci();
    meta::test_nd_grid();
    meta::test_array543();
    meta::test_map_t();
    meta::test_check_type_list();
    return 0;
}