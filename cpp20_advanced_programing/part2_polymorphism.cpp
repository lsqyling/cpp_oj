#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>
#include "../professional_cpp/format.h"

namespace polymorphism_compile {
using std::cout;
using std::endl;

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

template<typename T, std::enable_if_t<std::is_integral_v<T>>* = nullptr>
constexpr bool num_eq(T a, T b)
{
    return a == b;
}


template<typename T, std::enable_if_t<std::is_floating_point_v<T>>* = nullptr>
constexpr bool num_eq(T a, T b)
{
    return std::fabs(a - b) < std::numeric_limits<T>::epsilon();
}

void test_num_eq()
{
    static_assert(num_eq(3, 3));
    assert(num_eq(3.14, 3.14) == 1);

    cout << std::numeric_limits<float>::epsilon() << endl;
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
    void bark_impl() const { cout << "Bow wow!" << endl; }
};

class cat : public animal<cat>
{
    friend animal;
    void bark_impl() const { cout << "Miaowing!" << endl; }
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
    binary_expression(const U &a, const V &b, Op op_) : u(a), v(b), op(op_) {}
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