#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <future>
#include "format.h"

namespace ts {
using namespace std::literals::chrono_literals;
using std::cout;
using std::endl;
}
namespace ts::thread {

void counter(int id, int num_iterations)
{
    for (int i = 0; i < num_iterations; ++i)
    {
        cout << "Counter " << id << " has value " << i << endl;
    }
}


void test_counter()
{
    std::thread t1{counter, 1, 6};
    std::thread t2{counter, 2, 4};
    t1.join();
    t2.join();
}

void test_lambda_thread()
{
    int id = 1;
    int num = 10;
    auto call = [id, num] {
        for (int i = 0; i < num; ++i)
        {
            cout << "Counter " << id << " has value " << i << endl;
        }
    };
    std::thread t1{call};
    t1.join();
}

class request
{
public:
    request(int id) : m_id(id) {}
    void process() const
    {
        cout << "Processing request " << m_id << endl;

    }
private:
    int m_id;
};

void test_member_func()
{
    request r{1};
    std::thread t{&request::process, &r};
    t.join();
}

int k;
thread_local int n;

void thr_func(int id)
{
    cout << std::format("Thread {}: k = {}, n = {}\n", id, k, n);
    ++k;
    ++n;
}


void test_thread_local()
{
    std::thread t1{thr_func, 1};
    t1.join();
    std::thread t2{thr_func, 2};
    t2.join();
}

void test_jthread()
{
    auto callable = [](const std::stop_token& token) {
        int i = 0;
        while (!token.stop_requested())
        {
            cout << "before cancel" << endl;
            std::this_thread::sleep_for(5s);
            cout << "cannot received stop requested " << ++i << " times." << endl;
        }
    };

    std::jthread jt{callable};
    std::this_thread::sleep_for(1s);
    jt.request_stop();
}

void do_some_work()
{
    for (int i = 0; i < 5; ++i)
    {
        cout << i << endl;
    }
    cout << "Thread throwing a runtime_error exception..." << endl;
    throw std::runtime_error("Exception from thread");
}

void thr_func_exception(std::exception_ptr &err)
{
    try
    {
        do_some_work();
    } catch (...)
    {
        cout << "Thread caught exception, returning exception..." << endl;
        err = std::current_exception();
    }
}

void do_work_in_main_thread()
{
    std::exception_ptr error;
    std::thread launch{thr_func_exception, std::ref(error)};
    launch.join();
    if (error)
    {
        cout << "Main thread received exception, rethrowing it..." << endl;
        std::rethrow_exception(error);
    }
    else
    {
        cout << "Main thread did not receive any exception." << endl;
    }
}

void test_throw_between_thread()
{
    try
    {
        do_work_in_main_thread();
    } catch (const std::exception &e)
    {
        cout << "Main function caught: '" << e.what() << "'" << endl;
    }
}
}

namespace ts::atomic {
void test_under_hardware_lock_for_atomic()
{
    class foo { int m_array[132]; };
    class bar { int m_int; };

    std::atomic<foo> f;
    std::atomic<bar> b;
    cout << std::is_trivial_v<foo> << endl;
    cout << std::is_trivial_v<foo> << endl;

    std::atomic<int> atomic_i;
    std::atomic_bool atomic_b;
    std::atomic_char atomic_c;
    std::atomic<double> atomic_d;
    cout << std::is_trivial_v<int> << " " << atomic_i.is_lock_free()<< endl;
    cout << std::is_trivial_v<bool> << " " << atomic_b.is_lock_free()<< endl;
    cout << std::is_trivial_v<char> << " " << atomic_c.is_lock_free()<< endl;
    cout << std::is_trivial_v<double> << " " << atomic_d.is_lock_free()<< endl;


    std::atomic_int value = 10;
    cout << "value = " << value << endl;
    int fetched = value.fetch_add(4);
    cout << "fetched = " << fetched << endl;
    cout << "value = " << value << endl;
}

void increment(int &counter)
{
    for (int i = 0; i < 100; ++i)
    {
        ++counter;
        std::this_thread::sleep_for(1ms);
    }
}

void test_non_atomic_increment()
{
    int counter = 0;
    std::vector<std::thread> threads;
    for (int i = 0; i < 10; ++i)
    {
        threads.emplace_back(increment, std::ref(counter));
    }
    for (auto &t: threads)
    {
        t.join();
    }
    cout << "Result = " << counter << endl;
}

void increment_atomic(std::atomic_int &counter)
{
    for (int i = 0; i < 100; ++i)
    {
        ++counter;
        std::this_thread::sleep_for(1ms);
    }
}

void test_atomic_increment()
{
    std::atomic_int counter = 0;
    std::vector<std::thread> threads;
    for (int i = 0; i < 10; ++i)
    {
        threads.emplace_back(increment_atomic, std::ref(counter));
    }
    for (int i = 0; i < 10; ++i)
    {
        threads[i].join();
    }
    cout << "result = " << counter << endl;
}

void increment_atomic_ref(int &counter)
{
    std::atomic_ref<int> r_cnt{counter};
    for (int i = 0; i < 100; ++i)
    {
        ++r_cnt;
        std::this_thread::sleep_for(1ms);
    }
}

void test_increment_atomic_ref()
{
    int counter = 0;
    std::vector<std::thread> threads;
    for (int i = 0; i < 10; ++i)
    {
        threads.emplace_back(increment_atomic_ref, std::ref(counter));
    }
    for (auto &t: threads)
    {
        t.join();
    }
    cout << "Result = " << counter << endl;
}

void test_wait_notify()
{
    std::atomic_int value{0};
    std::thread job{[&value] {
        cout << "Thread starts waiting." << endl;
        value.wait(0);
        cout << "Thread wakes up, value = " << value << endl;
    }};

    std::this_thread::sleep_for(2s);
    cout << "Main thread is going to change value to 1." << endl;
    value = 1;
    value.notify_all();
    job.join();
}
}

namespace ts::mut {
std::atomic_flag spin_lock = ATOMIC_FLAG_INIT;
constexpr size_t NumberOfThreads = 50;
constexpr size_t LoopPerThread = 100;

void do_work(size_t thread_number, std::vector<size_t> &data)
{
    for (int i = 0; i < LoopPerThread; ++i)
    {
        while (spin_lock.test_and_set())
            std::this_thread::sleep_for(1ms);
        data.push_back(thread_number);
        spin_lock.clear();
    }
}

void test_spin_lock()
{
    std::vector<size_t> data;
    std::vector<std::thread> threads;
    for (int i = 0; i < NumberOfThreads; ++i)
    {
        threads.emplace_back(do_work, i, std::ref(data));
    }
    for (auto &t: threads)
    {
        t.join();
    }

    cout << std::format("data contains {} elements, expected {}.\n", data.size(),
                        NumberOfThreads * LoopPerThread)
         << endl;
}

std::once_flag g_once_flag;
void init_shared_resources()
{
    std::this_thread::sleep_for(1ms);
    cout << "Shared resources initialized." << endl;
}

void processing_func()
{
    std::this_thread::sleep_for(1ms);
    std::call_once(g_once_flag, init_shared_resources);
    cout << "Processing" << endl;
}

void test_processing_func()
{
    std::vector<std::thread> threads;
    for (int i = 0; i < 3; ++i)
    {
        threads.emplace_back(processing_func);
    }
    for (auto &item: threads)
    {
        item.join();
    }
}

class counter
{
public:
    counter(int id, int num_iterations) : m_id(id), m_number_iterations(num_iterations) {}
    void operator()() const
    {
        for (int i = 0; i < m_number_iterations; ++i)
        {
            std::lock_guard lock(m_mut);
            cout << "Counter " << m_id << " has value " << i << endl;
        }
    }
private:
    int m_id;
    int m_number_iterations;
    inline static std::mutex m_mut;
};

int calc_sum(int a, int b)
{
    std::this_thread::sleep_for(1ms);
    return a + b;
}

void test_task()
{
    std::packaged_task<int(int, int)> task(calc_sum);
    auto the_future = task.get_future();
    std::thread t{std::move(task), 39, 3};
    int result = the_future.get();
    cout << "result = " << result << endl;
    t.join();
}

void test_async()
{
    auto my_future = std::async(calc_sum, 3, 5);
    auto my_future1 = std::async(std::launch::async, calc_sum, 3, 5);
    int result = my_future.get();
    cout << "result = " << result << endl;
    cout << "result1 = " << my_future1.get() << endl;
}
}


int main()
{
    ts::thread::test_counter();
    ts::thread::test_lambda_thread();
    ts::thread::test_member_func();
    ts::thread::test_thread_local();
    ts::thread::test_jthread();
    ts::thread::test_throw_between_thread();

    ts::atomic::test_under_hardware_lock_for_atomic();
    ts::atomic::test_non_atomic_increment();
    ts::atomic::test_atomic_increment();
    ts::atomic::test_increment_atomic_ref();
    ts::atomic::test_wait_notify();

    ts::mut::test_spin_lock();
    ts::mut::test_processing_func();
    ts::mut::test_task();
    ts::mut::test_async();
    return 0;
}