#include <cstdint>
#include <iostream>
#include <vector>
#include "format.h"
#include <list>


namespace at {
using std::cout;
using std::endl;
using namespace std::string_literals;


template<typename T, const T &DEFAULT>
class grid
{

};
namespace {
int default_int = 11;
double d1 = 3.14;
}
void test_grid()
{
    grid<int, default_int> my_int_grid;
    grid<double, d1> my_double_grid;
}

template<typename T, size_t HEIGHT, size_t WEIGHT>
class grid1
{
    
};

template<size_t HEIGHT, size_t WEIGHT>
class grid1<const char *, HEIGHT, WEIGHT>
{
    
};


void test_grid1()
{
    grid1<int, 3, 3> my_int_grid;
    grid1<const char*, 2, 2> my_str_grid;
//    grid1<4, 4> test_grid1;
}

template<typename T>
class grid2
{
    
};

template<typename T>
class grid2<T*>
{
    
};


template<typename T, size_t N>
class nd_grid
{
public:
    explicit nd_grid(size_t size = DefaultSize);

    nd_grid<T, N - 1> &operator[](size_t x)
    {
        return m_elements[x];
    }

    const nd_grid<T, N - 1> &operator[](size_t x) const
    {
        return m_elements[x];
    }

    void resize(size_t size);

    size_t get_size() const
    {
        return m_elements.size();
    }

    inline static const size_t DefaultSize = 10;
private:
    std::vector<nd_grid<T, N - 1>> m_elements;
};


template<typename T, size_t N>
nd_grid<T, N>::nd_grid(size_t size)
{
    resize(size);
}

template<typename T, size_t N>
void nd_grid<T, N>::resize(size_t size)
{
    m_elements.resize(size);
    for (auto &item: m_elements)
    {
        item.resize(size);
    }
}


template<typename T>
class nd_grid<T, 1>
{
public:
    explicit nd_grid(size_t size = DefaultSize)
    {
        resize(size);
    }

    T &operator[](size_t size)
    {
        return m_elements[size];
    }

    const T &operator[](size_t size) const
    {
        return m_elements[size];
    }

    void resize(size_t size)
    {
        m_elements.resize(size);
    }

    size_t get_size() const
    {
        return m_elements.size();
    }


    inline static const size_t DefaultSize = 10;
private:
    std::vector<T> m_elements;

};


void  test_nd_grid()
{
    nd_grid<int, 3> my_3d_grid(5);
    my_3d_grid[2][1][2] = 5;
    my_3d_grid[1][1][1] = 7;

    for (int i = 0; i < 5; ++i)
    {
        for (int j = 0; j < 5; ++j)
        {
            for (int k = 0; k < 5; ++k)
            {
                cout << std::format("my_3d_grid[{}][{}][{}] = {}", i, j, k, my_3d_grid[i][j][k])
                     << "\n";
            }
        }
    }
}


template<typename... Types>
class my_variadic_template
{

};

void test_my_variadic_template()
{
    my_variadic_template<int> i;
    my_variadic_template<std::string, double, std::list<int>, std::vector<int> > ii;
    my_variadic_template<> iii;
}

void handle_value(int value) { cout << "Integer: " << value << endl; }
void handle_value(std::string_view value) { cout << "String: " << value << endl; }
void handle_value(double value) { cout << "Double: " << value << endl; }
void process_values() {}

template<typename T, typename... Args>
void process_values(T arg0, Args...args)
{
    handle_value(arg0);
    process_values(args...);
}



void test_process_values()
{
    process_values(1, 2, 3, 3.56, "test", "hello", "world", 1.1f);
}

template<typename... Args>
void print_values(const Args &...args)
{
    ((cout << args << endl), ...);
}

void test_print_values()
{
    print_values(1, 2, 3, 3.56, "test", "hello", "world", 1.1f);

}

template<typename T, typename...V>
double sum_values(const T &init, const V &...v)
{
    return (init + ... + v);
}

void test_sum_values()
{
    cout << sum_values(1, 2, 3, 4, 3.3, 4.5) << endl;
    cout << sum_values(1) << endl;
//    cout << sum_values() << endl;
}
template<typename...Args>
bool all_of(const Args &...args)
{
    return (... && args);
}

template<typename... Args>
bool any_of(const Args &...args)
{
    return (... || args);
}

void test_all_any()
{
    cout << std::format("{}{}{}", all_of(1, 1, 0), all_of(1, 1), all_of()) << endl;
    cout << std::format("{}{}{}", any_of(1, 1, 0), any_of(0, 0), any_of()) << endl;

}


template<uint8_t n>
struct factorial
{
    static const unsigned long long value = n * factorial<n-1>::value;
};

template<>
struct factorial<0>
{
    static const unsigned long long value = 1;
};


template<uint8_t N>
constexpr unsigned long long Factorial = N * Factorial<N - 1>;

template<>
constexpr unsigned long long Factorial<0> = 1;

void test_factorial()
{

    cout << "6! = " << factorial<6>::value << endl;
    cout << "7! = " << Factorial<7> << endl;
}

template<typename TupleType, int n = std::tuple_size_v<TupleType>>
void tuple_print(const TupleType &tuple)
{
    if constexpr (n > 1)
        tuple_print<TupleType, n - 1>(tuple);
    cout << std::get<n - 1>(tuple) << endl;
}

template<typename Tuple, size_t ...indices>
void tuple_print_helper(const Tuple &t, std::index_sequence<indices...>)
{
    ((cout << std::get<indices>(t) << endl), ...);
}

template<typename...Args>
void print_tuple(const std::tuple<Args...> &t)
{
    tuple_print_helper(t, std::index_sequence_for<Args...>());
}

void test_tuple_print()
{

    std::tuple t{167, "Testing", false, 2.3};
    tuple_print(t);
    print_tuple(t);
}


template<typename T>
void process(const T &t)
{
    if constexpr (std::is_integral_v<T>)
        cout << t << " is an integral type." << endl;
    else
        cout << t << " is a non-integral type." << endl;
}

template<typename T1, typename T2>
void same(const T1 &t1, const T2 &t2)
{
    bool iss = std::is_same_v<T1, T2>;
    cout << std::format("'{}' and '{}' are {} types.", t1, t2, iss ? "the same" : "different")
         << endl;
}


void test_process_same()
{
    process(5);
    process(5.5);
    process("hello");
    process(std::string("world"));

    same(1, 32);
    same(1, 3.14);
    same(3.10, "Test"s);
}

template<typename T>
constexpr std::conditional_t<std::is_nothrow_move_assignable_v<T>, T &&, const T &>
move_assign_if_noexcept(T &t) noexcept
{
    return std::move(t);
}

struct move_assignable
{
    move_assignable &operator=(const move_assignable &rhs)
    {
        cout << "copy assign" << endl;
        return *this;
    }
    move_assignable &operator=(move_assignable &&rhs)
    {
        cout << "move assign" << endl;
        return *this;
    }
};


struct move_assignable_noexcept
{
    move_assignable_noexcept &operator=(const move_assignable_noexcept &rhs)
    {
        cout << "copy assign" << endl;
        return *this;
    }
    move_assignable_noexcept &operator=(move_assignable_noexcept &&rhs) noexcept
    {
        cout << "move assign" << endl;
        return *this;
    }
};

void test_move_assign_if_noexcept()
{
    move_assignable a, b;
    move_assignable_noexcept c, d;
    a = move_assign_if_noexcept(b);
    c = move_assign_if_noexcept(d);
}

struct is_doable
{
    void doit() const { cout << "IsDoable::doit()" << endl; }
};

struct derived : is_doable
{
};

template<typename T>
std::enable_if_t<std::is_base_of_v<is_doable, T>, void> call_doit(const T &t)
{
    t.doit();
}

template<typename T>
std::enable_if_t<!std::is_base_of_v<is_doable, T>, void> call_doit(const T &t)
{
    cout << "cannot call doit()" << endl;
}

void test_call_doit()
{
    derived d;
    call_doit(d);
    call_doit(123);
}

template<typename T>
void call_doit(const T &t[[maybe_unused]])
{
    if constexpr (std::is_base_of_v<is_doable, T>)
        t.doit();
    else
        cout << "Cannot call doit()!" << endl;
}

template<typename T>
void call_doit_again(const T &t)
{
    if constexpr (std::is_invocable_v<decltype(&is_doable::doit), T>)
    {
        t.doit();
    }
    else
        cout << "Cannot call doit()" << endl;

}
}

namespace at::exercise {
template<int N>
struct fib
{
    static constexpr int value = fib<N-1>::value + fib<N-2>::value;
};

template<>
struct fib<1>
{
    static constexpr int value = 0;
};

template<>
struct fib<2>
{
    static constexpr int value = 1;
};

void test_fib()
{
    cout << std::format("{}, {}, {}, {}, {}, {}, {}, {}, {}",
                        fib<1>::value, fib<2>::value, fib<3>::value,
                        fib<4>::value, fib<5>::value, fib<6>::value,
                        fib<7>::value, fib<8>::value, fib<9>::value)
         << endl;
}

consteval int fib_of(int n)
{
    int a = 0, b = 1;
    while (n--)
    {
        b = a + b;
        a = b - a;
    }
    return a;
}


void test_fib_non_template_recursion()
{
    cout << std::format("{}, {}, {}, {}, {}, {}, {}, {}, {}",
                        fib_of(1), fib_of(2), fib_of(3),
                        fib_of(4), fib_of(5), fib_of(6),
                        fib_of(7), fib_of(8), fib_of(9))
         << endl;
}

template<typename T, typename... Args>
void push_back_values(std::vector<T> &v, Args &&...args)
{
    (v.push_back(std::forward<Args>(args)), ...);
}

void test_back_values()
{
    std::vector<int> values1;
    push_back_values(values1, 9, 8, 7, 6);
    for (auto& value : values1) { cout << value << " "; }
    cout << endl;

    std::vector<double> values2;
    push_back_values(values2, 1.1, 2, 3.3, 4);
    for (auto& value : values2) { cout << value << " "; }
    cout << endl;

    std::vector<std::string> values3;
    push_back_values(values3, "Hello", "World", "!");
    for (auto& value : values3) { cout << value << " "; }
    cout << endl;
}
}


int main()
{
    at::test_grid();
    at::test_nd_grid();
    at::test_process_values();
    at::test_print_values();
    at::test_sum_values();
    at::test_all_any();
    at::test_factorial();
    at::test_tuple_print();
    at::test_process_same();
    at::test_move_assign_if_noexcept();
    at::test_call_doit();
    at::exercise::test_fib();
    at::exercise::test_fib_non_template_recursion();
    at::exercise::test_back_values();
    return 0;
}