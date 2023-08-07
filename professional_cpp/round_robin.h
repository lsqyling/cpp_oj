#ifndef PROFESSIONAL_CPP_ROUND_ROBIN_H
#define PROFESSIONAL_CPP_ROUND_ROBIN_H

#include <vector>
#include <stdexcept>

template<typename T>
class round_robin
{
public:
    explicit round_robin(size_t num_expected = 0);
    round_robin(const round_robin &) = delete;
    round_robin &operator=(const round_robin &) = delete;

    round_robin(round_robin &&src) noexcept = default;
    round_robin &operator=(round_robin &&) = default;

    void add(const T &elem);
    void remove(const T &elem);
    T &get_next();


private:
    std::vector<T> elements_;
    std::vector<T>::iterator iter_next;
};


template<typename T>
round_robin<T>::round_robin(size_t num_expected) : elements_(num_expected), iter_next(std::begin(elements_))
{
}

template<typename T>
void round_robin<T>::add(const T &elem)
{
    auto pos = iter_next - std::begin(elements_);
    elements_.push_back(elem);
    iter_next = std::begin(elements_) + pos;
}

template<typename T>
void round_robin<T>::remove(const T &elem)
{
    for (auto it = elements_.begin(); it != elements_.end(); ++it)
    {
        if (*it == elem)
        {
            std::ptrdiff_t pos;
            if (iter_next == std::end(elements_) - 1 && iter_next == it)
                pos = 0;
            else if (iter_next <= it)
                pos = iter_next - std::begin(elements_);
            else
                pos = iter_next - std::begin(elements_) - 1;

            elements_.erase(it);
            iter_next = std::begin(elements_) + pos;
            return ;
        }
    }
}

template<typename T>
T &round_robin<T>::get_next()
{
    if (elements_.empty())
        throw std::out_of_range("No elements in the list");

    auto ret = iter_next;
    ++iter_next;
    if (iter_next == std::end(elements_))
        iter_next = std::begin(elements_);
    return *ret;
}


#endif