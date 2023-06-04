//
// Created by shiqing on 2021/4/2.
//
#include <cstdio>
#include <algorithm>
#include <cassert>
#include <cstring>

#include "../common/CommonHeaders.h"

namespace math {
namespace pat_a1069 {
constexpr int kN = 10;

int num[kN], len;

void ToArray(int n)
{
    len = 0;
    do
    {
        num[len++] = n % 10;
        n /= 10;
    } while (n);
}

int ToNumber()
{
    int s = 0;
    for (int i = 0; i < len; ++i)
    {
        s = s * 10 + num[i];
    }
    return s;
}

void Entry()
{
    int n;
    scanf("%d", &n);
    for (;;)
    {
        ToArray(n);
        std::sort(num, num + len, [](int a, int b)
        { return a > b; });
        int max = ToNumber();
        std::sort(num, num + len);
        int min = ToNumber();
        n = max - min;
        printf("%04d - %04d = %04d\n", max, min, n);
        if (n == 0 || n == 6174) break;
    }
}
}

/*
 * 递归式：gcd(a, b) = gcd(b, a % b)
 * 递归边界：gcd(a, 0) = a;
 */
int Gcd(int a, int b)
{
    if (b == 0) return a;
    return Gcd(b, a % b);
}

int Lcm(int a, int b)
{
    int d = Gcd(a, b);
    return a / d * b;
}
//Four arithmetic of fractions
//Numerator of fraction
//Denominator of fraction
namespace fractions {
long Gcd(long a, long b)
{
    if (b == 0) return a;
    return Gcd(b, a % b);
}

struct Fraction
{
    long up_, down_;
};

Fraction Reduction(Fraction a)
{
    if (a.down_ < 0)
    {
        a.up_ = -a.up_;
        a.down_ = -a.down_;
    }
    if (a.up_ == 0)
    {
        a.down_ = 1;
    }
    else
    {
        long d = Gcd(std::abs(a.up_), std::abs(a.down_));
        a.up_ /= d;
        a.down_ /= d;
    }
    return a;
}

Fraction Add(Fraction a, Fraction b)
{
    Fraction r;
    r.up_ = a.up_ * b.down_ + b.up_ * a.down_;
    r.down_ = a.down_ * b.down_;
    return Reduction(r);
}

Fraction Minus(Fraction a, Fraction b)
{
    Fraction r;
    r.up_ = a.up_ * b.down_ - b.up_ * a.down_;
    r.down_ = a.down_ * b.down_;
    return Reduction(r);
}

Fraction Multi(Fraction a, Fraction b)
{
    Fraction r;
    r.up_ = a.up_ * b.up_;
    r.down_ = a.down_ * b.down_;
    return Reduction(r);
}

Fraction Divide(Fraction a, Fraction b)
{
    Fraction r;
    r.up_ = a.up_ * b.down_;
    r.down_ = a.down_ * b.up_;
    assert(r.down_);
    return Reduction(r);
}

void ShowResult(Fraction r)
{
    r = Reduction(r);
    if (r.down_ == 1)
    { printf("%ld", r.up_); }
    else if (std::abs(r.up_) > r.down_)
    {
        printf("%ld %ld/%ld", r.up_ / r.down_, std::abs(r.up_) % r.down_, r.down_);
    }
    else
    {
        printf("%ld/%ld", r.up_, r.down_);
    }
}

void TestingFraction()
{
    Fraction a{5, 3}, b{-6, 4};
    ShowResult(Add(a, b));
    printf("\n");
    ShowResult(Minus(a, b));
    printf("\n");
    ShowResult(Multi(a, b));
    printf("\n");
    ShowResult(Divide(a, b));
    printf("\n");
}
}

namespace prime {
bool IsPrime(int n)
{
    if (n <= 1) return false;
    int sqrt_n = std::sqrt(n);
    for (int i = 2; i <= sqrt_n; ++i)
    {
        if (n % i == 0) return false;
    }
    return true;
}

namespace eratosthenes {
constexpr int kN = 10'005;

int prime[kN], len = 0;
bool p[kN];

void FindPrime()
{
    for (int i = 2; i < kN; ++i)
    {
        if (!p[i])
        {
            prime[len++] = i;
            for (int j = 2 * i; j < kN; j += i)
            {
                p[j] = true;
            }
        }
    }
}

void TestingFindPrime()
{
    FindPrime();
    for (int i = 0; i < len; ++i)
    {
        printf("%d ", prime[i]);
        if (i > 0 && i % 100 == 0)
        { printf("\n"); }
    }
}
}
}

namespace pat_a1059 {
constexpr int kPrimeLen = 100'005;
constexpr int kFactorLen = 10;

int prime[kPrimeLen], len = 0;
struct Factor
{
    int x_, cnt_;
};

Factor factors[kFactorLen];
int num = 0;

bool IsPrime(int n)
{
    if (n <= 1) return false;
    int sqrt_n = std::sqrt(n);
    for (int i = 2; i <= sqrt_n; ++i)
    {
        if (n % i == 0) return false;
    }
    return true;
}

void FindPrime()
{
    for (int i = 0; i < kPrimeLen; ++i)
    {
        if (IsPrime(i))
        {
            prime[len++] = i;
        }
    }
}

void FindFactor(int n)
{
    FindPrime();
    int sqrt_n = std::sqrt(n);
    for (int i = 0; i < len && prime[i] <= sqrt_n; ++i)
    {
        if (n % prime[i] == 0)
        {
            factors[num].x_ = prime[i];
            factors[num].cnt_ = 0;
            while (n % prime[i] == 0)
            {
                ++factors[num].cnt_;
                n /= factors[num].x_;
            }
            ++num;
        }
        if (n == 1) break;
    }
    if (n != 1)
    {
        factors[num].x_ = n;
        factors[num++].cnt_ = 1;
    }
}

void Entry()
{
    int n;
    scanf("%d", &n);
    if (n == 1)
    {
        printf("1=1");
        return;
    }
    FindFactor(n);
    printf("%d=", n);
    for (int i = 0; i < num; ++i)
    {
        if (i > 0) printf("*");
        printf("%d", factors[i].x_);
        if (factors[i].cnt_ > 1)
        {
            printf("^%d", factors[i].cnt_);
        }
    }
}
}
namespace biginteger {
constexpr int kMaxLen = 10'000;

struct BigInteger
{
    int store_[kMaxLen]{}, len_ = 0;
};

BigInteger TransformStr(const char str[])
{
    BigInteger r;
    int len = strlen(str);
    for (int i = len - 1; i >= 0; --i)
    {
        r.store_[r.len_++] = str[i] - '0';
    }
    return r;
}

BigInteger operator+(BigInteger a, BigInteger b)
{
    BigInteger c;
    int r = 0;
    for (int i = 0; i < a.len_ || i < b.len_; ++i)
    {
        auto tmp = r + a.store_[i] + b.store_[i];
        c.store_[c.len_++] = tmp % 10;
        r = tmp / 10;
    }
    if (r)
    {
        c.store_[c.len_++] = r;
    }
    return c;
}

BigInteger operator-(BigInteger a, BigInteger b)
{
    BigInteger c;
    for (int i = 0; i < a.len_ || i < b.len_; ++i)
    {
        if (a.store_[i] < b.store_[i])
        {
            --a.store_[i + 1];
            a.store_[i] += 10;
        }
        c.store_[c.len_++] = a.store_[i] - b.store_[i];
    }
    while (c.len_ > 1 && c.store_[c.len_ - 1] == 0)
    {
        --c.len_;
    }
    return c;
}

bool operator<(BigInteger a, BigInteger b)
{
    if (a.len_ < b.len_) return true;
    else if (a.len_ > b.len_) return false;
    else
    {
        for (int i = a.len_ - 1; i >= 0; --i)
        {
            if (a.store_[i] < b.store_[i]) return true;
            else if (a.store_[i] > b.store_[i]) return false;
        }
    }
    return false;
}

BigInteger operator*(BigInteger a, int b)
{
    BigInteger c;
    int r = 0;
    for (int i = 0; i < a.len_; ++i)
    {
        auto tmp = a.store_[i] * b + r;
        c.store_[c.len_++] = tmp % 10;
        r = tmp / 10;
    }
    while (r)
    {
        c.store_[c.len_++] = r % 10;
        r /= 10;
    }
    return c;
}

BigInteger Divide(BigInteger a, int b, int &r)
{
    BigInteger c;
    c.len_ = a.len_;
    for (int i = a.len_ - 1; i >= 0; --i)
    {
        r = r * 10 + a.store_[i];
        if (r < b)
        {
            c.store_[i] = 0;
        }
        else
        {
            c.store_[i] = r / b;
            r %= b;
        }
    }
    while (c.len_ > 1 && c.store_[c.len_ - 1] == 0)
    {
        --c.len_;
    }
    return c;
}
}
}

namespace stl {

void TestingStringNpos()
{
    std::cout << string::npos << endl;
    printf("string::npos = %lu\n", string::npos);
}

namespace pat_a1060 {
string Process(string s, int &e, int n)
{
    int k = 0;
    while (s.size() && s[0] == '0')
    {
        s.erase(s.begin());
    }
    if (s[0] == '.')
    {
        s.erase(s.begin());
        while (s.size() && s[0] == '0')
        {
            s.erase(s.begin());
            --e;
        }
    }
    else
    {
        while (k < s.size() && s[k] != '.')
        {
            ++k;
            ++e;
        }
        if (k < s.size())
        {
            s.erase(s.begin() + k);
        }
    }
    if (s.empty())
    {
        e = 0;
    }
    int num = 0;
    k = 0;
    string res;
    while (num < n)
    {
        if (k < s.size()) res += s[k++];
        else res += '0';
        ++num;
    }
    return res;
}

void Entry()
{
    string s1, s2, s3, s4;
    int n;
    cin >> n >> s1 >> s2;
    int e1 = 0, e2 = 0;
    s3 = Process(s1, e1, n);
    s4 = Process(s2, e2, n);
    if (s3 == s4 && e1 == e2)
    {
        cout << "YES 0." << s3 << "*10^" << e1 << endl;
    }
    else
    {
        cout << "NO 0." << s3 << "*10^" << e1 << " 0." << s4 << "*10^" << e2 << endl;
    }
}
}

void TestingNextPermutation()
{
    int arr[6] = {0, 1, 2, 3, 4, 5};
    do
    {
        for (int i = 0; i < 6; ++i)
        {
            printf("%d ", arr[i]);
        }
        printf("\n");
    } while (std::next_permutation(arr, arr + 6));
}


}


int main(int argc, char *argv[])
{
    math::pat_a1069::Entry();
    math::fractions::TestingFraction();
    math::prime::eratosthenes::TestingFindPrime();
    math::pat_a1059::Entry();
    stl::TestingStringNpos();
    stl::pat_a1060::Entry();
    stl::TestingNextPermutation();

    return 0;
}

