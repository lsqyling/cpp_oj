#include <iostream>
#include <variant>
#include <any>
#include <vector>
#include "format.h"


namespace tool {
using namespace std::string_literals;
using std::endl;
using std::cout;
class foo
{
public:
    foo() = delete;
    foo(int) {}
};

class bar
{


public:
    bar() = delete;
    bar(int) {}
};


class my_visitor
{
public:
    void operator()(int i) const
    {
        cout << "int " << i <<  endl;
    }
    void operator()(float f) const
    {
        cout << "float " << f << endl;
    }
    void operator()(const std::string &s)
    {
        cout << "string " << s << endl;
    }
};

void test_variant()
{
    std::variant<int, float, std::string> v;
    std::variant<std::monostate, foo, bar> v1;

    v = 12;
    v = 12.3f;
    v = "An std::string"s;

    std::cout << "Type index: " << v.index() << std::endl;
    std::cout << "Contains an int: " << std::holds_alternative<int>(v) << std::endl;
    cout << std::get<std::string>(v) << endl;

//    cout << std::get<0>(v) << endl;
//    cout << std::get<int>(v) << endl;
    auto ps = std::get_if<std::string>(&v);
    if (ps)
        cout << *ps << endl;
    auto pi = std::get_if<0>(&v);
    if (pi)
        cout << *pi << endl;
    else
        cout << "nullptr" << endl;

    std::visit(my_visitor{}, v);
}

void test_any()
{
    std::any empty;
    std::any ani{3};
    std::any ans{"An std::string."s};

    cout << "empty.has_value = " << empty.has_value() << endl;
    cout << "ani.has_value = " << ani.has_value() << endl;
    cout << "ans.has_value = " << ans.has_value() << endl;

    cout << "ani wrapped type = " << ani.type().name() << endl;
    cout << "ans wrapped type = " << ans.type().name() << endl;
    int i = std::any_cast<int>(ani);
    cout << "i = " << i << endl;
    try
    {
        int test = std::any_cast<int>(ans);
        cout << test << endl;
    } catch (const std::bad_any_cast &e)
    {
        cout << "Exception: " << e.what() << endl;
    }

    std::any thing{3};
    thing = "An other string"s;
    if (thing.has_value())
        cout << std::any_cast<std::string>(thing) << endl;
    std::vector<std::any> v;
    v.push_back(thing);
    v.emplace_back(42);
    v.emplace_back("An std::string stored in vector"s);

    cout << std::any_cast<std::string>(v[2]) << endl;
}

void test_tuple()
{
    std::tuple t1{16, "Test"s, true};
    auto [i, str, b] = t1;
    cout << std::format("i: {}, str: {}, b: {}", i, str, b) << endl;

    i = 3;
    cout << std::format("i: {}, str: {}, b: {}", std::get<0>(t1), str, b) << endl;

    int first = 0;
    std::string s;
    bool third = false;

    cout << std::format("first: {}, s: {}, third: {}", first, s, third) << endl;
    std::tie(first, s, third) = t1;
    cout << std::format("first: {}, s: {}, third: {}", first, s, third) << endl;

    int j;
    std::string ss;
    std::tie(j, ss, std::ignore) = t1;
    cout << std::format("j-{}, ss-{}", j, ss) << endl;







}









}




int main()
{
    tool::test_variant();
    tool::test_any();
    tool::test_tuple();


    return 0;
}