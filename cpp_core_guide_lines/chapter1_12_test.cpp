#include <memory>
#include <iostream>
#include <utility>
#include <chrono>
#include <future>
#include <algorithm>
#include <numeric>
#include <random>
#include <deque>
#include <list>
#include <forward_list>
#include <execution>

namespace c130 {
struct Base
{
    Base() = default;
    virtual ~Base() = default;
    virtual std::unique_ptr<Base> clone()
    {
        return std::unique_ptr<Base>(new Base(*this));
    }

    virtual std::string get_name() const { return "Base"; }


protected:
    Base(const Base &) = default;
    Base &operator=(const Base &) = default;
};

struct Derived : Base
{
    Derived() = default;

    std::unique_ptr<Base> clone() override
    {
        return std::unique_ptr<Derived>(new Derived(*this));
    }

    std::string get_name() const override
    {
        return "Derived";
    }

protected:
    Derived(const Derived &) = default;
    Derived &operator=(const Derived &) = default;
};


void test()
{
    std::cout << "\n";

    auto base1 = std::make_unique<Base>();
    auto base2 = base1->clone();
    std::cout << "base1->get_name(): " << base1->get_name() << "\n";
    std::cout << "base2->get_name(): " << base2->get_name() << "\n";

    auto derived1 = std::make_unique<Derived>();
    auto derived2 = derived1->clone();
    std::cout << "derived1->get_name(): " << derived1->get_name() << "\n";
    std::cout << "derived2->get_name(): " << derived1->get_name() << "\n";

    std::cout << "\n";
}
}

namespace c129 {

struct Point {};
struct Color {};

class Shape
{
public:
    virtual Point center() const = 0;
    virtual Color color() const = 0;

    virtual void rotate(int) = 0;
    virtual void move(Point p) = 0;

    virtual void red_draw() const = 0;
};

class Circle : public virtual Shape
{
public:
    virtual int radius() = 0;


};


class ImplShape : public virtual Shape
{
public:
    Point center() const override
    {
        return {};
    }

    Color color() const override
    {
        return {};
    }

    void rotate(int i) override
    {

    }

    void move(Point p) override
    {

    }

    void red_draw() const override
    {

    }
};


class ImplCircle : public virtual Circle, public virtual ImplShape
{
public:
    int radius() override
    {
        return 0;
    }

    Point center() const override
    {
        return ImplShape::center();
    }

    Color color() const override
    {
        return ImplShape::color();
    }

    void rotate(int i) override
    {
        ImplShape::rotate(i);
    }

    void move(Point p) override
    {
        ImplShape::move(p);
    }

    void red_draw() const override
    {
        ImplShape::red_draw();
    }

};
}

namespace es_21 {
class Base
{

    friend std::ostream &operator<<(std::ostream &os, const Base &b);

public:
    Base() = default;

    Base(int xx, int yy, std::string st) : x(xx), y(yy), s(std::move(st))
    {}


private:
    int x = 1, y = 2;
    std::string s{"world"};
};

std::ostream &operator<<(std::ostream &os, const Base &b)
{
    os << "Base.x = " << b.x << "\n"
       << "Base.y = " << b.y << "\n"
       << "Base.s = " << b.s << "\n";

    return os;
}


void test()
{
    Base b1;
    Base b2(3, 4, "hello");

    std::cout << b1 << std::endl;
    std::cout << b2 << std::endl;
}
}

constexpr int TenMill = 10'000'000;

namespace meyers {
class MySingleton
{
public:
    MySingleton(const MySingleton &) = delete;
    MySingleton &operator=(const MySingleton &) = delete;

    static MySingleton &get_instance()
    {
        static MySingleton instance;
        volatile int dummy = 0;
        return instance;
    }
private:
    ~MySingleton() = default;
    MySingleton() = default;
};

std::chrono::duration<double> get_time()
{
    auto begin = std::chrono::system_clock::now();
    for (int i = 0; i < TenMill; ++i)
    {
        MySingleton::get_instance();
    }
    return std::chrono::system_clock::now() - begin;
}

void test()
{
    auto fut1 = std::async(std::launch::async, get_time);
    auto fut2 = std::async(std::launch::async, get_time);
    auto fut3 = std::async(std::launch::async, get_time);
    auto fut4 = std::async(std::launch::async, get_time);

    auto total = fut1.get() + fut2.get() + fut3.get() + fut4.get();
    std::cout << total.count() << "\n";
}
}

namespace double_checked_locking_pattern {
class MySingleton
{
public:
    MySingleton(const MySingleton &) = delete;
    MySingleton &operator=(const MySingleton &) = delete;
private:
    MySingleton() = default;
    ~MySingleton() = default;

    static std::atomic<MySingleton*> instance;
    static std::mutex my_mutex;
public:
    static MySingleton *get_instance()
    {
        MySingleton *sin = instance.load(std::memory_order_acquire);
        if (!sin)
        {
            std::lock_guard<std::mutex> my_lock(my_mutex);
            sin = instance.load(std::memory_order_relaxed);
            if (!sin)
            {
                sin = new MySingleton;
                instance.store(sin, std::memory_order_release);
            }
        }
        volatile int dummy = 0;
        return sin;
    }
};

std::atomic<MySingleton*> MySingleton::instance;
std::mutex MySingleton::my_mutex;

using meyers::get_time;
using meyers::test;
}

namespace per7 {

template<typename T>
void swap(T &a, T &b) noexcept
{
    T tmp(std::move(a));
    a = std::move(b);
    b = std::move(tmp);
}

class big_array
{
public:
    explicit big_array(size_t size) : m_data(new int[size]), m_size(size) {}
    big_array(const big_array &rhs) : m_data(new int[rhs.m_size]), m_size(rhs.m_size)
    {
        std::cout << "Copy constructor" << "\n";
        std::copy(rhs.m_data, rhs.m_data + rhs.m_size, m_data);
    }
    big_array &operator=(const big_array &other)
    {
        std::cout << "Copy assignment" << "\n";
        if (this != &other)
        {
            delete[] m_data;
            m_data = nullptr;
            m_size = 0;
            m_data = new int[other.m_size];
            m_size = other.m_size;
            std::copy(other.m_data, other.m_data + other.m_size, m_data);
        }
        return *this;
    }

    ~big_array()
    {
        delete[] m_data;
    }


private:
    int *m_data;
    size_t m_size;
};

void test()
{
    std::cout << "\n";

    big_array arr1(2011);
    big_array arr2(2017);
    swap(arr1, arr2);

    std::cout << "\n";
}
}

namespace per11 {
int gcd(int a, int b)
{
    while (b != 0)
    {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

constexpr int gcd_(int a, int b)
{
    while (b != 0)
    {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

void test()
{
    std::cout << "\n";

    constexpr int res1 = gcd_(121, 11);
    std::cout << "gcd_(121, 11) = " << res1 << "\n";

    int val = 121;
    int res2 = gcd_(val, 11);
    std::cout << "gcd_(val, 11) = " << res2 << '\n';

    std::cout << '\n';
}
}

namespace per19_memory_access {
constexpr int SIZE = 100'000'000;

template<typename T>
void sum_up(T &t, std::string_view msg)
{
    std::cout << std::fixed/* << std::setprecision(10)*/;
    auto begin = std::chrono::steady_clock::now();
    auto res = std::accumulate(t.begin(), t.end(), 0LL);
    auto last = std::chrono::steady_clock::now() - begin;

    std::cout << '\n';
    std::cout << msg << '\n';
    std::cout << "time: " << last.count() << '\n';
    std::cout << "res: " << res << '\n';
    std::cout << '\n';
    std::cout << '\n';
}



void test()
{
    std::cout << '\n';

    std::random_device seed;
    std::mt19937 engine(seed());
    std::uniform_int_distribution dis(0, 1000);

    std::vector<int> rand_num;
    rand_num.resize(SIZE);
    for (int i = 0; i < SIZE; ++i)
    {
        rand_num.push_back(dis(engine));
    }

    {
        std::vector<int> vec(rand_num.begin(), rand_num.end());
        sum_up(vec, "std::vector<int>");
    }

    {
        std::deque<int> deq(rand_num.begin(), rand_num.end());
        sum_up(deq, "std::deque<int>");
    }
    {
        std::list<int> list(rand_num.begin(), rand_num.end());
        sum_up(list, "std::list<int>");
    }
    {
        std::forward_list<int> fwl(rand_num.begin(), rand_num.end());
        sum_up(fwl, "std::forward_list<int>");
    }


}
}

namespace cp2 {
int get_unique_id()
{
    static int id = 0;
    return id++;
}

void test()
{
    auto fut1 = std::async([]{ return get_unique_id(); });
    auto fut2 = std::async([]{ return get_unique_id(); });

    std::cout << fut1.get() << '\n';
    std::cout << fut2.get() << '\n';
}
}

namespace cp3 {
std::once_flag once_flag;

void do_once()
{
    std::call_once(once_flag, []{ std::cout << "Important initialization" << '\n'; });
}

void test()
{
    std::thread t1(do_once);
    std::thread t2(do_once);
    std::thread t3(do_once);
    std::thread t4(do_once);
    std::thread t5(do_once);

    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
}
}

namespace cp7 {
void base_of_thread()
{
    int res;
    std::thread t([&res]{ res = 3 + 4; });
    t.join();
    std::cout << "base of thread: res = " << res << '\n';
}

void base_of_task()
{
    auto fut = std::async([]{ return 3 + 4; });
    std::cout << "base of task: res = " << fut.get() << '\n';
}

void test()
{
    base_of_thread();
    base_of_task();
}
}

namespace cp9 {
bool data_ready = false;

std::mutex mut;
std::condition_variable cond1;
std::condition_variable cond2;

int counter = 0;
int COUNT_LIMIT = 50;

void set_true()
{
    while (counter <= COUNT_LIMIT)
    {
        std::unique_lock lck(mut);
        cond1.wait(lck, []{ return data_ready == false;});
        data_ready = true;
        ++counter;
        std::cout << data_ready << '\n';
        cond2.notify_one();
    }
}

void set_false()
{
    while (counter < COUNT_LIMIT)
    {
        std::unique_lock lck(mut);
        cond2.wait(lck, []{ return data_ready == true; });
        data_ready = false;
        std::cout << data_ready << '\n';
        cond1.notify_one();
    }
}

void test()
{
    std::cout << std::boolalpha << '\n';
    std::cout << "Begin: " << data_ready << '\n';

    std::thread t1(set_true);
    std::thread t2(set_false);

    t1.join();
    t2.join();

    data_ready = false;
    std::cout << "End: " << data_ready << '\n';
    std::cout << '\n';
}
}

namespace cp42 {
std::mutex mut;
std::condition_variable cond;

bool data_ready = false;

void waiting_for_work()
{
    std::cout << "Waiting " << '\n';
    std::unique_lock lck(mut);
    cond.wait(lck, []{ return data_ready; });
    std::cout << "Running " << '\n';
}

void set_data_ready()
{
    {
        std::lock_guard lck(mut);
        data_ready = true;
    }
    std::cout << "Data prepared" << '\n';
    cond.notify_one();
}

void test()
{
    std::cout << '\n';
    std::thread t2(set_data_ready);
    std::thread t1(waiting_for_work);

    t1.join();
    t2.join();
    std::cout << '\n';
}
}

namespace cp32 {
struct my_int
{
    int val{2017};
    ~my_int()
    {
        std::cout << "Goodbye" << '\n';
    }
};

void show_number(std::shared_ptr<my_int> pi)
{
    std::cout << pi->val << "\n";
}

void thread_creator()
{
    auto ptr = std::make_shared<my_int>();

    std::thread t1(show_number, ptr);
    std::thread t2(show_number, ptr);

    t1.detach();
    t2.detach();
}
using namespace std::chrono_literals;
void test()
{
    std::cout << '\n';
    thread_creator();
//    std::this_thread::sleep_for(1s);
    std::cout << '\n';
}
}

namespace cp41 {
constexpr int NumThreads = 1'000'000;

void test()
{
    auto st = std::chrono::system_clock::now();
    for (int i = 0; i < NumThreads; ++i)
    {
        std::thread([]{}).detach();
    }
    auto du = std::chrono::system_clock::now() - st;
    std::cout << "time: " << du.count() << " seconds" << '\n';
}
}

namespace cp44 {
template<typename Mut>
concept Mutex = requires(Mut m)
{
    m.lock();
    m.unlock();
};


template<typename Mut>
requires requires(Mut m) { m.lock(); m.unlock(); }
class my_guard
{
public:
    explicit my_guard(Mut &mut) : m_mut(mut)
    {
        std::cout << "lock" << '\n';
        m_mut.lock();
    }
    ~my_guard()
    {
        m_mut.unlock();
        std::cout << "unlock" << '\n';
    }


private:
    Mut &m_mut;
};

void test()
{
    std::cout << "\n";
    std::mutex mut;
    my_guard lck(mut);
    std::cout << "CRITICAL SECTION" << "\n";
    std::cout << "\n";
}
}

namespace parallel {
void test()
{
    std::cout << '\n';

    std::vector<int> res1{1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::vector<int> res2(res1.size());
    std::transform_exclusive_scan(std::execution::par,
                                  res1.begin(), res1.end(),
                                  res2.begin(), 0,
                                  [](int b, int e) { return b + e; },
                                  [](int a) { return a * a;});
    std::cout << "transform_exclusive_scan: " ;
    for (auto v: res2)
    {
        std::cout << v << " ";
    }
    std::cout << "\n";
}
}

namespace send_msg_10_4 {
struct div
{
    void operator()(std::promise<int> int_promise, int a, int b) const
    {
        try
        {
            if (b == 0)
            {
                std::string err = "Illegal division by zero: "
                        + std::to_string(a) + "/" + std::to_string(b);
                throw std::runtime_error(err);
            }
            int_promise.set_value(a/b);
        } catch (...)
        {
            int_promise.set_exception(std::current_exception());
        }
    }
};

void execute_division(int nom, int denom)
{
    std::promise<int> div_promise;
    auto div_res = div_promise.get_future();

    div div_;
    std::thread div_thr(div_, std::move(div_promise), nom, denom);

    try
    {
        std::cout << nom << "/" << denom << " = "
                  << div_res.get() << "\n";
    } catch (std::runtime_error &e)
    {
        std::cout << e.what() << '\n';
    }
    div_thr.join();
}

void test()
{
    std::cout << '\n';

    execute_division(10, 0);
    execute_division(20, 10);

    std::cout << '\n';
}
}

namespace single_sync {
void waiting_for_work(std::future<void> fut)
{
    std::cout << "Waiting " << '\n';
    fut.wait();
    std::cout << "Running " << '\n';
}

void set_data_ready(std::promise<void> prom)
{
    std::cout << "Data prepared" << '\n';
    prom.set_value();
}

void test()
{
    std::cout << '\n';

    std::promise<void> promise;
    auto fut = promise.get_future();

    std::thread t1(waiting_for_work, std::move(fut));
    std::thread t2(set_data_ready, std::move(promise));
    t1.join();
    t2.join();

    std::cout << '\n';
}
}

namespace con1 {
struct immutable
{
    int val{12};
};

void test()
{
    const int val = 12;
//    val = 13;
    const immutable immu;
//    immu.val = 13;
   std::cout << val << '\n';
   std::cout << immu.val << '\n';
}
}

namespace con2 {
struct immutable
{
    mutable int val{12};
    void cannot_modify() const
    {
        val = 13;
    }
};



void test()
{
    const immutable immu;
    immu.cannot_modify();
}
}

namespace t43 {
using PFI = int (*)(int);
template<typename T>
using PFT = int (*)(T);


}













int main()
{
    c130::test();
    es_21::test();

    meyers::test();
    double_checked_locking_pattern::test();
    per7::test();
    per11::test();
    per19_memory_access::test();
    cp2::test();
    cp3::test();
    cp7::test();
    cp9::test();
    cp42::test();
    cp32::test();
    cp41::test();
    cp44::test();
    parallel::test();
    send_msg_10_4::test();
    single_sync::test();
    con1::test();
    con2::test();
}