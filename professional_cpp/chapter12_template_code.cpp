#include <string>
#include <string_view>
#include <memory>
#include <iostream>
#include <cmath>
#include <utility>
#include <format>

namespace tc {
template<typename, int, int> class grid;
template<typename T, int Row, int Col>
grid<T, Row, Col> operator+(const grid<T, Row, Col> &lhs, const grid<T, Row, Col> &rhs);
template<typename T, int Row, int Col>
std::ostream &operator<<(std::ostream &os, const grid<T, Row, Col> &rhs);


template<typename T, int Row, int Col>
class grid
{

    friend grid operator+<T, Row, Col>(const grid &lhs, const grid &rhs);
    friend std::ostream &operator<<<T, Row, Col>(std::ostream &os, const grid &g);

public:
    grid(std::initializer_list<T> li);
    auto &operator[](int index);

private:
    T cells_[Row][Col];
};


template<typename T, int Row, int Col>
std::ostream &operator<<(std::ostream &os, const grid<T, Row, Col> &rhs)
{
    for (int i = 0; i < Row; ++i)
    {
        for (int j = 0; j < Col; ++j)
        {
            os << std::format("{} ", rhs.cells_[i][j]);
        }
        os << "\n";
    }
    return os;
}

template<typename T, int Row, int Col>
grid<T, Row, Col> operator+(const grid<T, Row, Col> &lhs, const grid<T, Row, Col> &rhs)
{
    return grid<T, Row, Col>({});
}


template<typename T, int Row, int Col>
auto &grid<T, Row, Col>::operator[](int index)
{
    return cells_[index/Col][index%Col];
}

template<typename T, int Row, int Col>
grid<T, Row, Col>::grid(std::initializer_list<T> li)
{
    auto it = li.begin();
    for (int i = 0; i < Row; ++i)
    {
        for (int j = 0; j < Col; ++j)
        {
            if (i * Col + j < li.size())
                cells_[i][j] = *it++;
            else
                cells_[i][j] = T{};
        }
    }
}


void test_grid()
{
    grid<int, 3, 4> a_grid{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            std::cout << std::format("{:02d} ", a_grid[i*4 + j]);
        }
        std::cout << std::endl;
    }

    std::cout << "---------" << std::endl;
    std::cout << a_grid << std::endl;
}

decltype(auto) add(const auto &t1, const auto &t2)
{
    return t1 + t2;
}

template<typename T>
decltype(auto) add(const T &t1, const T &t2)
{
    return t1 + t2;
}


template<typename T>
constexpr T pi = T{3.1415926535897932384626438383279502884};

void test_variable_template()
{
    float f_pi = pi<float>;
    long double ld_pi = pi<long double>;

    std::cout << std::format("f_pi = {}, ld_pi = {}", f_pi, ld_pi) << std::endl;

}

template<typename T>
concept C = sizeof(T) == 4;

template<typename T>
concept Incrementable = requires(T x) { ++x; x++; };

template<typename T>
concept C1 = requires(T x) { typename T::value_type; };

template<typename T>
concept C2 = requires(T x, T y)
{
    { x.swap(y) } noexcept;
};

template<typename T>
concept C3 = requires(const T x)
{
    { x.size() } -> std::convertible_to<size_t>;

};

template<typename T>
concept C4 = requires(const T a, const T b)
{
    { a == b } -> std::convertible_to<bool>;
    { a < b } -> std::convertible_to<bool>;
};

template<typename T>
concept C5 = requires(T x)
{
    requires sizeof(T) == 4;
    ++x; x++; --x; x--;
};

template<typename T>
concept Decrementable = requires(T x)
{
    --x; x--;
};

template<typename T>
concept IncrementAndDecrement = Incrementable<T> && Decrementable<T>;

template<typename T>
concept X = IncrementAndDecrement<T> && Decrementable<T>;

class Foo;

template<typename T>
concept IsDerivedFoo = std::derived_from<T, Foo>;

template<typename T>
concept IsConvertibleToBool = std::convertible_to<T, bool >;

template<typename T>
concept DefaultAndCopyable = std::default_initializable<T> && std::copy_constructible<T>;

template<typename T>
concept MovableAndCopyable = std::copy_constructible<T> && std::move_constructible<T>;

template<typename T, typename U>
concept SameAs = std::same_as<T, U>;

template<typename T>
concept C6 = std::integral<T>;


using namespace std::literals::string_literals;

void test_concept_auto()
{
    IncrementAndDecrement auto value1 = 1;
    std::cout << std::format("value1 = {}", value1) << std::endl;

//    Incrementable auto value{"abc"s};

    int arr[5];
    Incrementable auto value{arr};


    std::cout << std::format("value = {}", *value) << std::endl;

    auto pi = std::make_shared<int>();
    std::cout << std::format("pi = {}", *pi) << std::endl;

    auto up = std::make_unique<int>();
    *up = 5;

    std::cout << std::format("up = {}", *up) << std::endl;
}

template<std::convertible_to<bool> T>
void handle(const T &t)
{
    std::cout << std::format("{} calls.", __func__ ) << std::endl;
}

template<Incrementable T>
void process(const T &t)
{
    std::cout << std::format("{} calls.", __func__ ) << std::endl;
}

template<typename T> requires Incrementable<T>
void process1(const T &t)
{
    std::cout << std::format("{} calls.", __func__ ) << std::endl;
}

template<typename T> requires std::convertible_to<T, bool>
void process2(const T &t)
{
    std::cout << std::format("{} calls.", __func__ ) << std::endl;
}

template<typename T> requires requires(T x) { x++; ++x; }
void process3(const T &t)
{
    std::cout << std::format("{} calls.", __func__ ) << std::endl;

}

template<typename T> requires std::is_arithmetic_v<T>
void process4(const T &t)
{
    std::cout << std::format("{} calls.", __func__ ) << std::endl;
}

template<typename T> requires std::integral<T>
void process5(const T &t)
{
    std::cout << std::format("{} calls, integral<T>", __func__ ) << std::endl;
}

template<typename T> requires (std::integral<T> && sizeof(T) == 4)
void process5(const T &t)
{
    std::cout << std::format("{} calls, integral<T> && sizeof(T) == 4", __func__ ) << std::endl;
}



void test_type_constraint_func()
{
    handle(4);
//    process("abc"s);

    char arr[5];
    process(arr);
    process1(arr);
    process2(arr);
    process3(arr);
    double x = 3.1415926;
    process4(x);

    process5(int{5});
    process5(short{4});
}

static const size_t NO_FOUND = static_cast<size_t>(-1);


template<typename T>
size_t find(const T *arr, size_t n, const T &x)
{
    for (size_t i = 0; i < n; ++i)
    {
        if (arr[i] == x)
            return i;
    }
    return NO_FOUND;
}

template<std::floating_point T>
bool are_equal(T x, T y, int precision = 4)
{
    return std::fabs(x - y) <= std::numeric_limits<T>::epsilon() * std::fabs(x + y) * precision
           || std::fabs(x - y) < std::numeric_limits<T>::min();
}

template<std::floating_point T>
size_t find(const T *arr, size_t n, const T &x)
{
    for (size_t i = 0; i < n; ++i)
    {
        if (are_equal(arr[i], x))
            return i;
    }
    return NO_FOUND;
}

void test_find()
{
    int arr[]{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};

    std::cout << std::format("11 == find(arr, 11, 11)? {}", 11 == find(arr, 11, 11)) << std::endl;

    double d_arr[]{3.14, 3.1415, 4.357383, 5.397912, 6.1234, 7.245435};
    std::cout << std::format("5 == find(d_arr, 6, 7.245435)? {}", 5 == find(d_arr, 6, 7.245435)) << std::endl;
}
template<typename K, typename V>
class key_value_pair
{
public:
    key_value_pair(K key, V value);

    K get_key() const
    {
        return key_;
    }

    void set_key(K key)
    {
        key_ = key;
    }

    V get_value() const
    {
        return value_;
    }

    void set_value(V value)
    {
        value_ = value;
    }

private:
    K key_{};
    V value_{};

};


template<typename K, typename V>
key_value_pair<K, V>::key_value_pair(K key, V value): key_(std::move(key)), value_(std::move(value))
{

}


void test_key_value_pair()
{
    key_value_pair<std::string, int> kv{"John Doe", 5};
    std::cout << std::format("[{}:{}]", kv.get_key(), kv.get_value())
              << std::endl;
    key_value_pair<std::string, std::string> mykv{"zhang", "san"};
    std::cout << std::format("[{}:{}]", mykv.get_key(), mykv.get_value())
              << std::endl;

}
}




int main(int argc, char *argv[])
{
    tc::test_grid();
    tc::test_variable_template();
    tc::test_concept_auto();
    tc::test_type_constraint_func();
    tc::test_find();
    tc::test_key_value_pair();

    return 0;
}