#include <iostream>
#include <memory>
#include "format.h"


namespace mem {
class simple
{
public:
    simple() { std::cout << "Simple constructor called!" << std::endl; }
    ~simple() { std::cout << "Simple destructor called!" << std::endl; }

    void go() { std::cout << "This is go method!" << std::endl; }
};


void test_new_array()
{
    simple *ps = new simple[4];
    simple *ptr = reinterpret_cast<simple *>(::operator new(sizeof(simple) * 5));
    for (int i = 0; i < 5; ++i)
    {
        new(&ptr[i]) simple;
    }

    for (int j = 0; j < 5; ++j)
    {
        ptr[j].~simple();
    }

    ::operator delete(ptr);
    delete[] ps;
}

void leaky()
{
    simple *ps = new simple;

    ps->go();
}
void could_leaky()
{
    simple *ps = new simple;

    ps->go();

    delete ps;
}

void safe_memory()
{
    std::cout << std::format("--------\nentry {}.", __func__) << std::endl;
    auto uptr = std::make_unique<simple>();
    uptr->go();
    uptr.reset();
    uptr.reset(new simple);


    auto ptr = std::make_unique<int[]>(10);
    auto ptr1 = std::make_unique_for_overwrite<int[]>(10);

    for (int i = 0; i < 10; ++i)
    {
        std::cout << std::format("{}\n", ptr[i]);
    }
    for (int j = 0; j < 10; ++j)
    {
        std::cout << std::format("{}\n", ptr1[j]);

    }

    auto p = std::make_unique<double>();
    std::cout << std::format("leaving {}.\n-------", __func__) << std::endl;
}

struct foo
{
    int i;
    foo() = default;
};

struct bar
{
    int j;
    bar();
};

bar::bar() = default;

void test_initial()
{
    foo a;
    bar b;
    std::cout << std::format("foo a.i = {}, bar b.j = {}", a.i, b.j) << std::endl;


    foo aa{};
    bar bb{};
    std::cout << std::format("foo aa.i = {}, bar bb.j = {}", aa.i, bb.j) << std::endl;

}

void test_shared_ptr()
{
    std::cout << std::format("--------\nentry {}.", __func__) << std::endl;

    auto ps = std::make_shared<simple>();
    ps->go();

    auto p1 = ps;
    auto p2 = ps;
    p1->go();
    p2->go();

    std::cout << std::format("leaving {}.\n-------", __func__) << std::endl;

}

std::unique_ptr<simple> create()
{
    auto ptr = std::make_unique<simple>();
    ptr->go();

//    do something

    return ptr;
}

void test_create()
{
    auto ptr = create();
    ptr->go();
}

class foo_shared : public std::enable_shared_from_this<foo_shared>
{
public:

    foo_shared()
    {
        std::cout << std::format("-----------\nentrying {}", __func__) << std::endl;
    }

    ~foo_shared()
    {
        std::cout << std::format("-----------\nleaving {}", __func__) << std::endl;
    }

    std::shared_ptr<foo_shared> get_pointer()
    {
        return shared_from_this();
    }
};

void test_shared_from_this()
{
    auto ptr = std::make_shared<foo_shared>();
    auto ptr2 = ptr->get_pointer();


}

}

int main(int argc, char *argv[])
{
    mem::test_new_array();
    mem::safe_memory();
    mem::test_initial();
    mem::test_shared_ptr();
    mem::test_create();
    mem::test_shared_from_this();
    return 0;
}