#ifndef BIG_INTEGER__
#define BIG_INTEGER__
#include <cstring>

namespace bigi {
constexpr int N = 1024;

struct big_integer
{
    big_integer(long n) : big_integer()
    {
        do
        {
            digit[len++] = n % 10;
            n /= 10;
        } while (n);
    }

    big_integer() : len(0)
    {
        memset(digit, 0, sizeof(digit));
    }

    uint8_t digit[N];
    int len;
public:
    static void reduce(big_integer &a)
    {
        while (a.len > 1 && a.digit[a.len-1] == 0)
            --a.len;
    }
};

big_integer operator+(const big_integer &a, const big_integer &b)
{
    big_integer res;
    int carry = 0, s;
    for (int i = 0; i < a.len || i < b.len; ++i)
    {
        s = a.digit[i] + b.digit[i] + carry;
        res.digit[res.len++] = s % 10;
        carry = s / 10;
    }
    if (carry != 0)
        res.digit[res.len++] = carry;
    return res;
}

big_integer operator*(const big_integer &a, const big_integer &b)
{
    big_integer ans;
    int carry = 0, begin;
    for (int i = 0; i < b.len; ++i)
    {
        begin = i;
        for (int j = 0; j < a.len; ++j)
        {
            ans.digit[begin] += b.digit[i] * a.digit[j] + carry;
            carry = ans.digit[begin] / 10;
            ans.digit[begin] %= 10;
            ++begin;
        }
        while (carry)
        {
            ans.digit[begin] += carry;
            carry = ans.digit[begin] / 10;
            ans.digit[begin] %= 10;
            ++begin;
        }
        if (ans.len < begin)
            ans.len = begin;
    }
    big_integer::reduce(ans);
    return ans;
}

bool operator==(const big_integer &a, const big_integer &b)
{
    if (a.len != b.len)
        return false;
    for (int i = 0; i < a.len; ++i)
    {
        if (a.digit[i] != b.digit[i])
            return false;
    }
    return true;
}

bool operator<(const big_integer &a, const big_integer &b)
{
    if (a.len > b.len)
        return false;
    if (a.len < b.len)
        return true;
    for (int i = a.len - 1; i >= 0; --i)
    {
        if (a.digit[i] > b.digit[i])
            return false;
        if (a.digit[i] < b.digit[i])
            return true;
    }
    return false;
}

std::ostream &operator<<(std::ostream &os, const big_integer &a)
{
    for (int i = a.len - 1; i >= 0; --i)
        os << (int)a.digit[i];
    return os;
}

big_integer value_of(const std::string &str, long base)
{
    int c;
    big_integer sum = 0;
    for (int i = 0; i < str.size(); ++i)
    {
        c = str[i];
        if ('a' <= c && c <= 'z')
            c = c - 'a' + 10;
        else
            c = c - '0';
        sum = (sum * base) + c;
    }
    return sum;
}

std::istream &operator>>(std::istream &is, big_integer &a)
{
    long n;
    is >> n;
    a = n;
    return is;
}

void remove_front_zero(std::string &str)
{
    int n = 0;
    while (n < str.size() && str[n] == '0')
        ++n;
    str.erase(0, n == str.size() ? n - 1 : n);
}




}




#endif