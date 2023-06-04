#ifndef GLOB__
#define GLOB__

#include <utility>

namespace single {
template<typename T>
class glob
{
public:
    static T *get()
    {
        return *getpptr();
    }
    template<typename... Args>
    static void new_(Args &&...args)
    {
        if (get() != nullptr)
            throw 1;
        *getpptr() = new T(std::forward<Args>(args)...);
    }

    static void delete_()
    {
        if (get() != nullptr)
        {
            delete *getpptr();
            *getpptr() = nullptr;
        }
    }
private:
    static T **getpptr()
    {
        static T *base = nullptr;
        return &base;
    }

};










}

















#endif