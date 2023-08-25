#include <iostream>
#include "format.h"
#include "round_robin.h"

class process
{
public:
    explicit process(std::string_view name) : name_(name) {}

    process() = default;

    void do_work_during_time_slice()
    {
        std::cout << "Process " << name_
         << " performing work during time slice." << std::endl;
    }


    bool operator==(const process &rhs) const = default;
    auto operator<=>(const process &rhs) const = default;

private:
    std::string name_;
};

class scheduler
{
public:
    explicit scheduler(const std::vector<process> &processes);

    void schedule_time_slice();

    void remove_process(const process &pro);


private:
    round_robin<process> processes_;

};

scheduler::scheduler(const std::vector<process> &processes)
{
    for (auto &process: processes)
    {
        processes_.add(process);
    }
}

void scheduler::schedule_time_slice()
{
    try
    {
        processes_.get_next().do_work_during_time_slice();
    } catch (std::out_of_range &e)
    {
        std::cerr << "No more process to schedule." << std::endl;
    }
}
void scheduler::remove_process(const process &pro)
{
    processes_.remove(pro);
}


int main()
{
    std::vector<process> processes{process("1"), process("2"), process("3")};
    scheduler schedule{processes};

    for (int i = 0; i < 4; ++i)
    {
        schedule.schedule_time_slice();
    }

    schedule.remove_process(processes[1]);
    std::cout << "Removed second process" << std::endl;
    for (int i = 0; i < 4; ++i)
    {
        schedule.schedule_time_slice();
    }
    process p;
    auto cmp = []() noexcept {};
    auto cmp2 = []{};

    std::cout << std::format("process has dtor? {}", noexcept(p.~process())) << std::endl;
    std::cout << std::format("process has ctor? {}", noexcept(process())) << std::endl;
    std::cout << std::format("cmp has noexcept? {}", noexcept(cmp)) << std::endl;
    std::cout << std::format("cmp2 has noexcept? {}", noexcept(cmp2)) << std::endl;



    return 0;
}