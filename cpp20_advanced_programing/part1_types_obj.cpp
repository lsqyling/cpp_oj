#include <memory>
#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <cmath>
#include <iterator>
#include <variant>
#include <numbers>

using std::endl;
using std::cout;
using namespace std::placeholders;
namespace to {
template<typename T, typename... Args>
std::unique_ptr<T> make_unique_ptr(Args &&...args)
{
    return std::make_unique<T>(std::forward<Args>(args)...);
}

template<typename F, typename ...Args>
using invoke_result_of_func = decltype(F()(Args()...));

template<typename F, typename ...Args>
using invoke_result_of_func_perfect = decltype(std::declval<F>()(std::declval<Args>()...));

struct afunc_obj
{
    double operator()(char, int) const { return 3.41; }
    float operator()(int) const { return 3.14; }
};

using T1 = invoke_result_of_func_perfect<afunc_obj, char, int>;
using T2 = invoke_result_of_func_perfect<afunc_obj, int>;

template<typename T>
struct declval_protector
{
    static constexpr bool value = false;
};

template<typename T>
T &&declval()
{
    static_assert(declval_protector<T>::value, "declval 应该只在decltype/sizeof等非求值上下文中使用");
}

void test_declval()
{
//    declval<afunc_obj>();
}

template<typename T, typename U>
struct pair
{
    pair() = default;
    pair(T, U) {}
};
template<typename T, typename U>
struct pair1
{
    template<class A, class B>
    pair1(A &&, B &&) {}
};

template<typename T, typename U>
pair1(T, U) -> pair1<T, U>;


void test_pair()
{
    pair1 foo1{1, 2};
    pair foo{1, 2};
    pair<int, float> foo2;
}

template<typename T>
struct plus
{
    T operator()(T x, T y) const
    {
        return x + y;
    }
};

void test_plus()
{
    std::cout << plus<int>()(3, 2) << std::endl;

    std::vector nums{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::copy_if(nums.begin(), nums.end(), std::ostream_iterator<int>(std::cout, ", "),
                 std::bind(std::greater<>(), _1, 4));
}

using int_add_func = int (*)(int, int);
constexpr int_add_func func_lambda = [](auto a, auto b) { return a + b; };

const auto add_lambda = [](auto a, auto b) { return a + b; };
auto add_lambda1 = []<typename T>(T a, T b) { return a + b; };

void test_constexpr()
{
    std::cout << "add_lambda is constexpr." << std::endl;
}

enum class Op { ADD, MUL};
std::function<int (int, int)> operation_factory(Op op)
{
    switch (op)
    {
        case Op::ADD:
            return [](int a, int b) { return a + b; };
        case Op::MUL:
            return std::multiplies<>();
    }
    return {};
}


void test_function_of_op()
{
    cout << operation_factory(Op::MUL)(3, 4) << endl;
    cout << operation_factory(Op::ADD)(3, 4) << endl;

}
}

namespace p_r {
struct shape
{
    virtual ~shape() = default;
    virtual double get_area() const = 0;
    virtual double get_perimeter() const = 0;
};

struct circle : shape
{
    explicit circle(double r) : m_r(r) {}

    double get_area() const override
    {
        return std::numbers::pi * m_r * m_r;
    }

    double get_perimeter() const override
    {
        return 2 * std::numbers::pi * m_r;
    }
private:
    double m_r;
};

struct rectangle : shape
{
    rectangle(double w, double h) : m_w(w), m_h(h) {}

    double get_area() const override
    {
        return m_w * m_h;
    }

    double get_perimeter() const override
    {
        return 2 * (m_w + m_h);
    }


private:
    double m_w, m_h;
};


void test_polymorphism_point()
{
    std::unique_ptr<shape> shape = std::make_unique<circle>(3);
    cout << "shape area: " << shape->get_area()
         << " perimeter: " << shape->get_perimeter()
         << endl;

    shape = std::make_unique<rectangle>(2, 3);
    cout << "rectangle area: " << shape->get_area()
         << " perimeter: " << shape->get_perimeter()
         << endl;
}
}

namespace p_v {
struct circle { double r; };
struct rectangle { double w, h; };

double get_area(const circle &s)
{
    return std::numbers::pi * s.r * s.r;
}

double get_perimeter(const circle &s)
{
    return 2 * std::numbers::pi * s.r;
}

double get_area(const rectangle &s)
{
    return s.w * s.h;
}

double get_perimeter(const rectangle &s)
{
    return 2 * (s.w + s.h);
}

using shape_t = std::variant<circle, rectangle>;

double get_area(const shape_t &shape)
{
    return std::visit([](const auto &s) { return get_area(s);}, shape);
}

double get_perimeter(const shape_t &shape)
{
    return std::visit([](const auto &s) { return get_perimeter(s);}, shape);
}

void test_polymorphism_value()
{
    shape_t shape = circle{.r = 3};

    cout << "circle area: " << get_area(shape)
         << " perimeter: " << get_perimeter(shape)
         << endl;

    shape = rectangle{.w = 3, .h = 4};

    cout << "circle area: " << get_area(shape)
         << " perimeter: " << get_perimeter(shape)
         << endl;
}
}


namespace extern_tools {
struct point
{
    int x;
    int y;
};

auto add_lambda = [](auto a, auto b) { return a + b; };


point pt;
point *ppt = &pt;
const point *cppt = &pt;
point &lrpt = pt;
point &&rrpt = point();

using t1_t = decltype(pt);
using t2_t = decltype(ppt);
using t3_t = decltype(cppt);
using t4_t = decltype(lrpt);
using t5_t = decltype(rrpt);

template<typename ...Ts>
void dump()
{
    std::cout << "dump" << std::endl;
}


void test()
{
    dump<t1_t, t2_t, t3_t, t4_t, t5_t>();
    cout << add_lambda(3, 4) << endl;
}

template<typename T, typename U = T &&>
U declval_(int);

template<typename T>
T declval_(long);

template<typename T>
auto declval() -> decltype(declval_<T>(0))
{
    static_assert(to::declval_protector<T>::value, "declval 应该只在decltype/sizeof等非求值上下文中使用");
    return declval_<T>(0);
}
}









int main()
{
    to::test_declval();
    to::test_pair();
    to::test_plus();
    to::test_constexpr();
    to::test_function_of_op();
    p_r::test_polymorphism_point();
    p_v::test_polymorphism_value();
    extern_tools::test();
    return 0;
}