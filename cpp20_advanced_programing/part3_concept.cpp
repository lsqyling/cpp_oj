#include <vector>
#include <iostream>
namespace concept_constraint {
using std::cout;
using std::endl;

template<typename T>
concept integral = std::is_integral_v<T>;

template<typename T>
concept foo = true;

template<typename T>
concept C = std::is_integral_v<typename T::type> || (sizeof(T) > 1);


template<typename... Ts>
concept S = (integral<typename Ts::type> || ...);

template<typename M>
concept Machine = requires(M m)
{
    m.power_up();
    m.power_down();
};

template<typename T>
concept Animal = requires(T animal)
{
    play(animal);
    T::count;
    animal.age;
};

template<typename T>
concept Number = requires(T a, T b, T c)
{
    a == b;
    a + b * c;
};

template<typename T>
concept CT = requires
{
    typename T::type;
    typename std::vector<T>;
};

struct foo1
{
    using type = float;
};

void test_simple_concept()
{
    static_assert(std::floating_point<float>);
    static_assert(!std::floating_point<int>);
    static_assert(foo<int>);
    static_assert(integral<int>);
    static_assert(C<double>);
    static_assert(CT<foo1>);
}

template<typename T>
concept C1 = requires(T x)
{
    { f(x) } -> std::same_as<T>;
    { g(x) } -> std::convertible_to<double>;
};

template<typename T>
concept C2 = requires(T x)
{
    f(x);
    requires std::same_as<T, decltype(f(x))>;
    g(x);
    requires std::convertible_to<T, double>;
};

template<typename T>
concept C3 = requires
{
    requires sizeof(T) > sizeof(void *);
    requires std::is_trivial_v<T>;
};

template<typename T>
constexpr bool has_member_swap = requires(T a, T b) { a.swap(b); };

template<size_t N>
concept even = requires {
    requires N % 2 == 0;
};

template<typename T>
void clever_swap(T &a, T &b)
{
    if constexpr (requires(T c, T d){ c.swap(d); })
    {
        a.swap(b);
    }
    else
    {
        using std::swap;
        swap(a, b);
    }
}

template<typename T>
requires std::is_integral_v<T>
auto gcd(T a, T b)
{
    if (b == 0)
        return a;
    return gcd(b, a % b);
}


void test_gcd()
{
    cout << gcd(12, 8) << endl;
//    gcd(1.0, 2.0);

}

template<typename T>
concept Scalar = std::is_arithmetic_v<T>;

template<typename T>
struct math_traits
{
    static constexpr bool customized = false;
};

struct big_int
{
    int digit[1000];
    int len;
};

template<>
struct math_traits<big_int>
{
    static constexpr bool customized = true;
};

template<typename T>
concept CustomMath = math_traits<T>::customized;

template<typename T>
concept Mathematical = Scalar<T> || CustomMath<T>;

template<Mathematical T, Mathematical U>
void calculate(const T &, const U &)
{
    cout << "Q" << endl;
}

template<typename T, typename U>
requires (Scalar<T> && Scalar<U>) || (CustomMath<T> && CustomMath<U>)
void calculate(const T &, const U &)
{
    cout << "P" << endl;
}

template<typename T, typename U>
requires std::same_as<T, U> && std::is_integral_v<T>
void f(T, U);


template<typename From, typename To>
concept Convertible = std::is_convertible_v<From, To>
                      &&
                      requires(std::add_rvalue_reference<From> (&f)())
                      {
                          static_cast<To>(f());
                      };

struct to
{
    template<typename From>
    explicit to(From) = delete;
};

struct from
{
    operator to();
};

void test_convertible_from_to()
{
    static_assert(std::is_convertible_v<from, to>);
    static_assert(!Convertible<from, to>);
}

template<typename F, typename ...Args>
concept invocable = requires(F &&f, Args &&...args)
{
    invoke(std::forward<F>(f), std::forward<Args>(args)...);
};







}


















int main()
{
    concept_constraint::test_simple_concept();
    concept_constraint::test_gcd();
    concept_constraint::test_convertible_from_to();
    return 0;
}