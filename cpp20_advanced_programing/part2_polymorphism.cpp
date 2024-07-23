#include <iostream>
#include <utility>
#include <vector>
#include <cassert>
#include "../professional_cpp/format.h"

namespace polymorphism_compile {
using std::cout;
using std::endl;

template<typename T> T declval_(long);
template<typename T, typename U = T&&> U declval_(int);

template<typename T>
auto declval() -> decltype(declval_<T>(0))
{
    static_assert(!std::is_void_v<T>, "disable not void");
    return declval_<T>(0);
}
//type traits
//Is it an integer type and floating-point?
struct false_type
{
        static constexpr bool value = false;
};
struct true_type
{
    static constexpr bool value = true;
};

template<typename T>
struct is_integral : false_type {};

template<>
struct is_integral<char> : true_type {};

template<>
struct is_integral<signed char> : true_type {};

template<>
struct is_integral<unsigned char> : true_type {};

template<>
struct is_integral<short> : true_type {};

template<>
struct is_integral<unsigned short> : true_type {};
template<>
struct is_integral<int> : true_type {};

template<>
struct is_integral<unsigned> : true_type {};
template<>
struct is_integral<long> : true_type {};
template<>
struct is_integral<unsigned long> : true_type {};
template<>
struct is_integral<long long> : true_type {};
template<>
struct is_integral<unsigned long long> : true_type {};

template<typename T>
constexpr bool is_integral_v = is_integral<T>::value;

template<typename T>
struct is_floating_point : false_type {};

template<>
struct is_floating_point<float> : true_type {};

template<>
struct is_floating_point<double> : true_type {};

template<>
struct is_floating_point<long double> : true_type {};

template<typename T>
constexpr bool is_floating_point_v = is_floating_point<T>::value;

void testing_number()
{
    static_assert(!is_integral<double>::value, "double is not an integral");

}

template<typename T, typename U>
struct is_same : false_type {};
template<typename T>
struct is_same<T, T> : true_type {};
template<typename T>
struct remove_const
{
    using type = T;
};
template<typename T>
struct remove_const<const T>
{
    using type = T;
};
template<bool cond, typename Then, typename Else>
struct conditional
{
    using type = Then;
};
template<typename Then, typename Else>
struct conditional<false, Then, Else>
{
    using type = Else;
};

template<size_t N> constexpr size_t fibonacci = fibonacci<N-1> + fibonacci<N-2>;
template<> constexpr size_t fibonacci<0> = 0;
template<> constexpr size_t fibonacci<1> = 1;

template<size_t N> constexpr double golden_ratio = fibonacci<N> * 1.0 / fibonacci<N-1>;


void test_fibonacci()
{
    static_assert(fibonacci<10> == 55);
    cout << std::format("{:.10f}", golden_ratio<20>) << endl;
    cout << std::format("{:.10f}", golden_ratio<50>) << endl;
}

struct base {};
struct children : base
{
    int age;
};

struct children1
{
    base b;
    int age;
};

struct children2
{
    base b;
    int age;
};

void test_empty_base_class_optimization()
{
    static_assert(sizeof(children) == 4);
    static_assert(sizeof(children1) == 8);
    static_assert(sizeof(children2) == 8);
}

template<typename T>
struct array_size;
template<typename E, size_t N>
struct array_size<E[N]>
{
    using value_type = E;
    static constexpr size_t len = N;
};

void test_array_size()
{
    static_assert(std::is_same_v<array_size<int[5]>::value_type, int>);
    static_assert(array_size<int[5]>::len == 5);
}

template<typename F>
struct function_trait;

template<typename Ret, typename... Args>
struct function_trait<Ret(Args ...)>
{
    using result_type = Ret;
    using args_type = std::tuple<Args...>;
    static constexpr size_t args_num = sizeof...(Args);
    template<size_t I> using arg = std::tuple_element_t<I, args_type>;
};

void test_function_trait()
{
    using F = void(int, float, double, std::vector<int>);
    static_assert(std::is_same_v<function_trait<F>::result_type , void>);
    static_assert(function_trait<F>::args_num == 4);
    static_assert(std::is_same_v<function_trait<F>::arg<3>, std::vector<int>>);
}


template<bool, typename = void>
struct enable_if {};
template<typename T>
struct enable_if<true, T>
{
    using type = T;
};

template<bool cond, typename T = void>
using enable_if_t = typename enable_if<cond, T>::type;

template<typename T, enable_if_t<is_integral_v<T>>* = nullptr>
constexpr bool num_eq(T a, T b)
{
    return a == b;
}

template<typename T>
constexpr T fabs(T a)
{
    static_assert(std::is_arithmetic_v<T>, "T is arithmetic");
    return a < 0 ? -a : a;
}


template<typename T, enable_if_t<is_floating_point_v<T>>* = nullptr>
constexpr bool num_eq(T a, T b)
{
    return fabs(a - b) < std::numeric_limits<T>::epsilon();
}

void test_num_eq()
{
    static_assert(num_eq(3, 3));
    static_assert(num_eq(3.14, 3.14) == 1);

    cout << std::numeric_limits<double>::epsilon() << endl;
}

template<typename ...> using void_t = void;
template<typename T, typename = void>
struct has_type_member : std::false_type {};

template<typename T>
struct has_type_member<T, void_t<typename T::type>> : std::true_type {};

void test_has_type_member()
{
    static_assert(!has_type_member<int>::value);
    static_assert(has_type_member<std::true_type >::value);
}

template<typename T> struct base1 {};
struct derived : base1<derived> {};

struct point
{
    int x, y;
    friend auto operator<=>(const point &lhs, const point &rhs) = default;
};

template<typename Derived>
struct animal
{
    void bark()
    {
        static_cast<Derived&>(*this).bark_impl();
    }
};

class dog : public animal<dog>
{
    friend animal;
    static void bark_impl() ;
};

void dog::bark_impl()
{ cout << "Bow wow!" << endl; }

class cat : public animal<cat>
{
    friend animal;
    static void bark_impl() { cout << "Miaowing!" << endl; }
};

template<typename T>
void play(animal<T> &animal)
{
    animal.bark();
}

void test_CRTP()
{
    cat a_cat;
    play(a_cat);
    dog adog;
    play(adog);
}
}

namespace polymorphism_compile::calc {
template<typename U, typename V, typename Op>
struct binary_expression
{
    binary_expression(U a, V b, Op op_) : u(std::move(a)), v(std::move(b)), op(op_) {}
    auto operator()() const { return op(u, v); }
protected:
    U u;
    V v;
    Op op;

};

void test_binary_expression()
{
    binary_expression expr{3.5, 4, [](auto a, auto b) { return a * b; }};
    double res = expr() * 2.5;
    cout << "res = " << res << endl;
}

template<typename U, typename V, typename OP>
struct binary_container_expression : private binary_expression<U, V, OP>
{
    using base = binary_expression<U, V, OP>;
    using base::base;
    auto operator[](size_t index) const
    {
        assert(index < size());
        return base::op(base::u[index], base::v[index]);
    }
    size_t size() const
    {
        assert(base::u.size() == base::v.size());
        return base::u.size();
    }
};

template<typename U, typename V, typename OP>
binary_container_expression(U, V, OP) -> binary_container_expression<U, V, OP>;


void test_binary_container_expression()
{
    std::vector x{1, 2, 4}, y{1, 1, 1};
    int alpha = 4;
    auto add_scaled = [alpha](auto a, auto b) { return a + alpha * b; };
    auto expr = binary_container_expression(x, y, add_scaled);
    for (int i = 0; i < expr.size(); ++i)
    {
        cout << expr[i] << " ";
    }
}

template<typename T>
constexpr bool is_container_v = requires(T t) {
    typename T::value_type;
    typename T::iterator;
};

template<typename T, typename U, typename V>
constexpr bool is_container_v<binary_container_expression<T, U, V>> = true;

template<typename T>
concept containerize = is_container_v<T>;

template<containerize T, containerize U>
auto operator+(const T &lhs, const U &rhs)
{
    auto plus = [](auto x, auto y) { return x + y; };
    return binary_container_expression(lhs, rhs, plus);
}
}

namespace polymorphism_compile::meta {
template<typename T, size_t D1, size_t ...Dn>
struct array
{
    using type = std::array<typename array<T, Dn...>::type, D1>;
};
template<typename T, size_t D1>
struct array<T, D1>
{
    using type = std::array<T, D1>;
};

using array5x4x3x = std::array<std::array<std::array<int, 3>, 4>, 5>;
using carray5x4x3x = int[5][4][3];

static_assert(std::is_same_v<array5x4x3x, array<int, 5, 4, 3>::type>, "not equal");
static_assert(!std::is_same_v<array<double, 5, 4, 3>::type, carray5x4x3x>);
}



int main()
{
    polymorphism_compile::test_fibonacci();
    polymorphism_compile::test_empty_base_class_optimization();
    polymorphism_compile::test_array_size();
    polymorphism_compile::test_function_trait();
    polymorphism_compile::test_num_eq();
    polymorphism_compile::test_CRTP();
    polymorphism_compile::calc::test_binary_expression();
    polymorphism_compile::calc::test_binary_container_expression();
    return 0;
}