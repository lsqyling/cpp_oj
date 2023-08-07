#include <span>
#include <functional>
#include <cmath>
#include <iostream>
#include <format>
#include <memory>


namespace fc {
using namespace std::placeholders;


template<typename Iter, typename StartValue, typename Operation>
auto accumulate_data(Iter begin, Iter end, StartValue sv, Operation op)
{
    auto ret = sv;
    for (Iter it = begin; it != end; ++it)
    {
        ret = op(ret, *it);
    }

    return ret;
}

double geometric_mean(std::span<const int> values)
{
    auto mult = accumulate_data(std::cbegin(values), std::cend(values),
                                1, std::multiplies<>{});
    return std::pow(mult, 1.0 / static_cast<double>(values.size()));
}


void test_accumulate_data()
{
    std::vector<int> values{1, 2, 3};
    double result = accumulate_data(values.begin(), values.end(),
                                    1.1, std::multiplies<>{});
    std::cout << "result = " << result << std::endl;
    std::cout << "geometric_mean = " << geometric_mean(values) << std::endl;
}

void func(int num, std::string_view sv)
{
    std::cout << std::format("func({}, {})\n", num, sv);
}

void increment(int &i) { ++i; }

void test_bind()
{
    auto f1 = std::bind(func, _1, "mystring");
    f1(16);

    auto f2 = std::bind(func, _2, _1);
    f2("mystringf2", 1);

    int index = 0;
    auto incre = std::bind(increment, index);
    auto incr_index = std::bind(increment, std::ref(index));
    incre();
    std::cout << "index = " << index << std::endl;
    incr_index();
    std::cout << "index = " << index << std::endl;
}

class person
{
public:
    person(std::string name) : name_(std::move(name)) {}
    const std::string &get_name() const { return name_; }

private:
    std::string name_;
};

auto multi_by_lambda(int x)
{
    return [x] { return 2 * x; };
}

void test_lambda()
{
    auto basic_lambda = []() { std::cout << "Hello from Lambda\n"; };
    basic_lambda();

    auto person1 = [](const person &p) { return p.get_name(); };
    auto person2 = [](const person &p)
            -> decltype(auto) { return p.get_name(); };
    person p1{"zhangsan"};
    std::cout << person1(p1) << std::endl;
    std::cout << person1(person("lisi")) << std::endl;
    auto are_equal = [](const auto &v1, const auto &v2) { return v1 == v2; };
    std::cout << "are_equal: " << are_equal(3, 4) << std::endl;
    double pi = 3.1415926;

    auto my_pi = [my_capture = "Pi: ", pi] { std::cout << my_capture << pi << "\n"; };
    my_pi();
    auto ptr = std::make_unique<double>(3.1415926);
    auto my_ptr = [p = std::move(ptr)] { std::cout << "*ptr: " << *p << "\n"; };
    my_ptr();

    auto fn = multi_by_lambda(5);
    std::cout << "fn = " << fn() << std::endl;

    using lambda_type = decltype([](int a, int b) { return a + b; });
    lambda_type add;
    std::cout << "lambda = " << add(3, 2) << std::endl;
}
}





int main()
{
    fc::test_accumulate_data();
    fc::test_bind();
    fc::test_lambda();



    return 0;
}