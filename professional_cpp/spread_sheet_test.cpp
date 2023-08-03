#include <bit>
#include "spread_sheet.h"
#include "format.h"

class self
{
public:
    ~self()
    {
        std::cout << std::format("call {}.", __func__) << std::endl;
    }


};

class Base
{
public:
    ~Base()
    {
        std::cout << std::format("call {}.", __func__) << std::endl;
    }

    Base() = default;

    Base(const Base &base) : i_(base.i_), str_(base.str_), self_(base.self_)
    {
        std::cout << std::format("call {}.", __func__) << std::endl;

    }


private:
    int i_;
    std::string str_;
    self self_;
};





void test_base()
{
    Base b1, b2;
    Base b3{b1};
    b2 = b1;
    b3 = std::move(b2);

    Base b4{std::move(b3)};





}







struct A
{
    int a_;
    int b_;
    auto operator<=>(const A &a) const = default;
    bool operator==(const A &a) const = default;
};

class animal
{
public:
    virtual void sleep();
    virtual void eat() = 0;
};

class dog : public virtual animal
{
public:
    void bark();

    void eat() override;
};

class bird : public virtual animal
{
    void chirp();

public:
    void eat() override;
};

void animal::sleep()
{
    std::cout << "zzzzz..." << std::endl;

}

void dog::bark()
{
    std::cout << "Woof!" << std::endl;
}

void dog::eat()
{
    std::cout << "The dog eat!" << std::endl;
}

void bird::eat()
{
    std::cout << "The bird eat!" << std::endl;
}

void bird::chirp()
{
    std::cout << "Chirp!" << std::endl;
}

class dog_bird : public dog, public bird
{
public:
    void eat() override ;
};

void dog_bird::eat()
{
    dog::eat();
}

void test_bit_cast()
{
    float f = 1.23;
    unsigned x = std::bit_cast<unsigned >(f);
    std::cout << std::format("f = {:.2f}, x = {}", f, x) << std::endl;

}

int main()
{
    test_bit_cast();

    A a{1, 2};
    A b{2, 2};

    if (a < b)
        std::cout << std::format("a < b : {}", a < b) << std::endl;
    else
        std::cout << "a >= b" << std::endl;

    if (a != b)
        std::cout << "a != b" << std::endl;



    test_base();

    dog_bird db;
    db.sleep();

    int j;
    void *pa = &j;

    int *pj = reinterpret_cast<int*>(pa);
    *pj = 3;
    std::cout << std::format("j = {}.", j) << std::endl;




    return 0;
}