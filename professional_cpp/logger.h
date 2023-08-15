#ifndef PROFESSIONAL_STL_LOGGER_H
#define PROFESSIONAL_STL_LOGGER_H
#include <queue>
#include <condition_variable>
#include <iostream>




namespace ts {
class logger
{
public:
    logger();
    logger(const logger &) = delete;
    logger &operator=(const logger &) = delete;
    ~logger();

    void log(std::string entry);


private:
    void process_entries();
    void process_entries_helper(std::queue<std::string> &queue, std::ofstream &ofs) const;

    std::mutex m_mut;
    std::condition_variable m_cond;
    std::thread m_thread;
    std::queue<std::string> m_queue;
    bool m_exit{false};
};























}














#endif












