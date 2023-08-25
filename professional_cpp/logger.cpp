#include <fstream>
#include <chrono>
#include "logger.h"
using namespace std::chrono_literals;
ts::logger::logger() : m_thread(&logger::process_entries, this)
{

}

void ts::logger::log(std::string entry)
{
    std::unique_lock lock{m_mut};
    m_queue.push(std::move(entry));
    m_cond.notify_all();
}

ts::logger &ts::logger::instance()
{
    static logger logger_1;
    return logger_1;
}

ts::logger::~logger()
{
    {
        std::unique_lock lock{m_mut};
        m_exit = true;
    }
    m_cond.notify_all();
    m_thread.join();

}

void ts::logger::process_entries()
{
    std::ofstream ofs("log.txt");
    if (ofs.fail())
    {
        std::cerr << "Failed to open logfile." << std::endl;
        return;
    }
    std::unique_lock lock{m_mut, std::defer_lock};
    while (true)
    {
        lock.lock();
        if (!m_exit)
        {
            std::this_thread::sleep_for(10ms);
            m_cond.wait(lock);
        }
        else
        {
            process_entries_helper(m_queue, ofs);
            break;
        }
        m_cond.wait(lock);
        std::queue<std::string> tmp;
        tmp.swap(m_queue);
        lock.unlock();
        process_entries_helper(tmp, ofs);
    }

}

void ts::logger::process_entries_helper(std::queue<std::string> &queue, std::ofstream &ofs) const
{
    while (!queue.empty())
    {
        ofs << queue.front() << "\n";
        queue.pop();
    }

}
