#include <vector>
#include <thread>
#include <iostream>
#include <cassert>
#include <array>
#include "../professional_cpp/format.h"

constexpr int N = 100'0000;
constinit std::mutex g_mut;
int x = 0;



void test_thread()
{

    auto add = [](int &num) {
        for (int i = 0; i < N; ++i)
        {
            std::lock_guard lg(g_mut);
            ++num;
        }};
    std::jthread t1{add, std::ref(x)};
    std::jthread t2{add, std::ref(x)};

    t1.join();
    t2.join();

    std::cout << std::format("x = {}\n", x);
}


template<int ... Is>
constexpr int rsum = (Is + ... + 0);

template<int ... Is>
constexpr int lsum = (0 + ... + Is);

static_assert(rsum<1, 2, 3, 4, 5> == 15);
static_assert(lsum<1, 2, 3, 4, 5> == 15);

template<int...Is>
constexpr int rsub = (Is - ... - 0);

template<int...Is>
constexpr int lsub = (0 - ... - Is);

static_assert(rsub<1, 2, 3, 4, 5> == 3);
static_assert(lsub<1, 2, 3, 4, 5> == -15);

constexpr int min(std::initializer_list<int> xs)
{
    int low = std::numeric_limits<int>::max();
    for (const auto &item: xs)
    {
        if (item < low)
            low = item;
    }
    return low;
}

static_assert(min({5, 4, 3, 2, 1}) == 1);

consteval int min_(std::initializer_list<int> xs)
{
    int low = std::numeric_limits<int>::max();
    for (const auto &item: xs)
    {
        if (item < low)
            low = item;
    }
    return low;
}

static_assert(min_({5, 4, 3, 2, 1, 0}) == 0);

constexpr std::vector<int> sieve_prime(int n)
{
    std::vector<bool> visit(n+1, true);
    std::vector<int> res;
    for (int i = 2; i <= n; ++i)
    {
        if (visit[i])
        {
            res.push_back(i);
            for (int j = i + i; j <= n; j += i)
            {
                visit[j] = false;
            }
        }
    }
    return res;
}

constexpr size_t prime_count(int n)
{
    return sieve_prime(n).size();
}

//static_assert(prime_count(100) == 25);

template<int n>
constexpr auto save_prime_to_array()
{
    std::array<int, 25> result{};
    auto primes = sieve_prime(n);
    std::copy(primes.begin(), primes.end(), result.data());
    return result;
}

auto primes100 = save_prime_to_array<100>();

void test_sieve_prime()
{
    auto res = sieve_prime(100);
    assert(res.size() == 25);
    assert(primes100.size() == 25);
}

struct shape
{
    virtual ~shape() = default;
    virtual double get_area() const = 0;
};

struct circle : shape
{
    constexpr circle(double r) : m_r(r) {}

    constexpr double get_area() const override
    {
        return std::numbers::pi * m_r * m_r;
    }

private:
    double m_r;
};


constexpr double calc_subtype()
{
    std::array<shape*, 4> shapes{
        new circle(10), new circle(20), new circle(3.5), new circle(4.0)
    };

    double sum = 0;
    for (auto s: shapes)
    {
        sum += s->get_area();
        delete s;
    }
    return sum;
}

static_assert(std::is_constant_evaluated());
int y = 0;
const int a = std::is_constant_evaluated() ? y : 1;
constexpr int b = std::is_constant_evaluated() ? 1 : y;


constexpr size_t collatz_time(size_t n)
{
    size_t step = 0;
    for (; n > 1; ++step)
        n = n % 2 == 0 ? n / 2 : 3 * n + 1;
    return step;
}

constexpr size_t sum_collatz_time(size_t n)
{
    size_t sum = 0;
    for (size_t i = 1; i <= n; ++i)
    {
        sum += collatz_time(n);
    }
    return sum;
}
//note: constexpr evaluation hit maximum step limit; possible infinite loop?
//constexpr auto res = sum_collatz_time(100000000);
auto res = sum_collatz_time(10000);

//constexpr auto v = 1 / 0;note: division by zero
//constexpr int v = 2147483647 * 2;note: value 4294967294 is outside the range of representable values of type 'int'
/*
 * note: read of dereferenced null pointer is not allowed in a constant expression
constexpr int f()
{
    int *p = nullptr;
    return *p;
}
*/
/*
 * cannot refer to element 12 of array of 10 elements in a constant expression
 *
constexpr int f(const int *p) { return *(p+12); }
constexpr int g() { int arr[10]{}; return f(arr); }
constexpr int v = g();
*/
/*
 * note: read of variable whose lifetime has ended

constexpr int &f() { int x = 123; return x; }
constexpr auto v = f();
*/

/*
 * in call to 'vector(400, std::vector<int>::allocator_type())'
constexpr int f()
{
    std::vector<int> v(400);
    int *q = &v[7];
    v.resize(900);
    return *q;
}

constexpr int v = f();
*/

void test_calc_subtype()
{
    std::cout << "sum = " << calc_subtype() << std::endl;
    std::cout << "a = " << a << std::endl;
    std::cout << "b = " << b << std::endl;
    std::cout << "res = " << res << std::endl;

}

struct foo {};
template<auto...>
struct value_list {};
value_list<'C', 0, 2L, nullptr, foo{}> xx;

//template<const char *>
//struct C {};
//C<"hello"> c;Pointer to subobject of string literal is not allowed in a template argumen

template<size_t N>
struct cstring
{
    char str[N]{};
    constexpr cstring(const char (&s)[N])
    {
        std::copy_n(s, N, str);
    }
};

template<cstring str>
struct C {};

static_assert(std::is_same_v<C<"hello">, C<"hello">>);
static_assert(!std::is_same_v<C<"hello">, C<"world">>);

template<cstring str>
struct C1 { static constexpr auto ptr = &str; };
template<cstring str>
struct C2 { static constexpr auto ptr = &str; };

static_assert(!std::is_same_v<C1<"hello">, C2<"hello">>);
static_assert(C1<"hello">::ptr == C2<"hello">::ptr);

template<cstring str>
constexpr auto operator""_fs()
{
    return str;
}


value_list<"hello"_fs> v1;

template<bool move_constructable = true, bool copy_constructable = true,
        bool move_assignable = true, bool copy_assignable = true>
struct counted {};

using construct_only = counted<true, true, false, false>;

struct counted_policy
{
    bool move_constructable{true};
    bool copy_constructable{true};
    bool move_assignable{true};
    bool copy_assignable{true};
};

inline constexpr counted_policy default_counted_policy;
template<counted_policy policy = default_counted_policy>
struct counted_ {};

using construct_only_ = counted_<counted_policy{.move_assignable = false,
                                  .copy_assignable = false}>;

namespace meta_compile_str {
template<typename T>
constexpr auto strlen = strlen<std::remove_cvref_t<T>>;
template<size_t N>
constexpr size_t strlen<char[N]> = N - 1;
template<size_t N>
constexpr size_t strlen<std::array<char, N>> = N - 1;

static_assert(strlen<decltype("hello")> == 5);

template<typename DelimType, size_t N>
struct join_string_fold
{
    constexpr join_string_fold(DelimType delimiter) : m_delimiter(delimiter) {}
    template<typename STR>
    friend constexpr decltype(auto) operator+(join_string_fold &&self, STR &&str)
    {
        self.m_pstr = std::copy_n(std::begin(str), strlen<STR>, self.m_pstr);
        if (self.m_joined_str.end() - self.m_pstr > strlen<DelimType>)
            self.m_pstr = std::copy_n(self.m_delimiter, strlen<DelimType>, self.m_pstr);
        return std::forward<join_string_fold>(self);
    }

    std::array<char, N+1> m_joined_str{};
    DelimType m_delimiter;
    decltype(m_joined_str.begin()) m_pstr{m_joined_str.begin()};
};

template<typename DelimType, typename... STRs>
constexpr auto join(DelimType &&delimiter, STRs &&...strs)
{
    constexpr size_t strn = sizeof...(STRs);
    constexpr size_t len = (strlen<STRs> + ... + 0) + (strn >= 1 ? strn - 1 : 0) * strlen<DelimType>;
    return (join_string_fold<DelimType, len>(std::forward<DelimType>(delimiter))
            + ... + std::forward<STRs>(strs)).m_joined_str;
}

template<typename...STRs>
constexpr auto concat(STRs &&...strs)
{
    return join("", std::forward<STRs>(strs)...);
}

void test_join_concat()
{
    constexpr auto one_two = concat("one", "two");
    constexpr auto one_two_three = concat(one_two, "three");
    std::cout << std::format("size = {}, {}\n", one_two_three.size(), one_two_three.data());
}
}










int main()
{
    test_thread();
    test_sieve_prime();
    test_calc_subtype();
    meta_compile_str::test_join_concat();
    return 0;
}
