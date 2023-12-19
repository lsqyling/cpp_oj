//
// Created by shiqing on 2021/2/14.
//
#include <cstdio>
#include <algorithm>
#include <cstring>
#include "CommonHeaders.h"


namespace chapter_1_3 {


template<typename T, int N>
void BubbleSort(T (&arr)[N])
{
    int n = N;
    while (--n)
    {
        for (int j = 0; j < n; ++j)
        {
            if (arr[j] > arr[j + 1])
            {
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
}

constexpr double kEps = 1e-8;
const double kPi = std::acos(-1.0);

bool Equ(double a, double b)
{
    return std::abs(a - b) < kEps;
}

void TestingChar()
{
    int n1 = 1, n2 = 3;
    printf("%d %d\n", n1, n2);
    printf("sizeof(int*) = %ld\n", sizeof(int *));
}

void TestingBubbleSort()
{
    auto &arr = generateRandomArray<10'000>();
    BubbleSort(arr);
    bool is_sorted = isSorted(arr);
    printf("The arr is sorted %s.\n", is_sorted ? "true" : "false");
}


void TestingEqu()
{
    double a = 4 * std::asin(std::sqrt(2) / 2);
    double b = 3 * std::asin(std::sqrt(3) / 2);
    printf("%s\n", Equ(a, b) ? "true" : "false");
}

namespace pat_b1001 {

int CountStepsCallatz(int n)
{
    int cnt = 0;
    while (n != 1 && n > 0)
    {
        if (n % 2)
        {
            n = (n * 3 + 1) / 2;
        }
        else
        {
            n /= 2;
        }
        ++cnt;
    }
    return cnt;
}

void TestingCountStepsCallatz()
{
    for (int i = 0; i < 1000; ++i)
    {
        printf("n = %d, steps = %d\n", i, CountStepsCallatz(i));
    }
}
}

namespace pat_b1032 {
constexpr int kN = 100'005;

int all[kN];

void Entry()
{
    int n, idx, score;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
    {
        scanf("%d%d", &idx, &score);
        all[idx] += score;
    }
    int max_id = 0, max_score = 0;
    for (int i = 0; i <= n; ++i)
    {
        if (all[i] > max_score)
        {
            max_score = all[i];
            max_id = i;
        }
    }
    printf("%d %d\n", max_id, max_score);
}
}

namespace pat_b1036 {

void Entry()
{
    int col, row, c;
    scanf("%d %c", &col, &c);
    row = col % 2 ? col / 2 + 1 : col / 2;
    for (int i = 0; i < row; ++i)
    {
        for (int j = 0; j < col; ++j)
        {
            if (i == 0 || i == row - 1)
            {
                printf("%c", c);

            }
            else
            {
                if (j == 0 || j == col - 1)
                {
                    printf("%c", c);
                }
                else
                {
                    printf(" ");
                }
            }
        }
        printf("\n");
    }
}
}

namespace codeup_1928 {
constexpr int kMonth = 13;
constexpr int kYear = 2;

int month[kMonth][kYear] = {
        {0,  0},
        {31, 31},
        {28, 29},
        {31, 31},
        {30, 30},
        {31, 31},
        {30, 30},
        {31, 31},
        {31, 31},
        {30, 30},
        {31, 31},
        {30, 30},
        {31, 31}
};

constexpr bool IsLeap(int year)
{
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

void Entry()
{
    int t1, y1, m1, d1;
    int t2, y2, m2, d2;
    scanf("%d%d", &t1, &t2);
    if (t1 > t2)
    { std::swap(t1, t2); }
    y1 = t1 / 10000;
    m1 = t1 % 10000 / 100;
    d1 = t1 % 100;
    y2 = t2 / 10000;
    m2 = t2 % 10000 / 100;
    d2 = t2 % 100;
    int cnt = 1;
    while (y1 < y2 || m1 < m2 || d1 < d2)
    {
        ++d1;
        if (d1 == month[m1][IsLeap(y1)] + 1)
        {
            ++m1;
            d1 = 1;
        }
        if (m1 == kMonth)
        {
            ++y1;
            m1 = 1;
        }
        ++cnt;
    }
    printf("%d", cnt);
}
}

namespace pat_b1022 {
int nums[35], len = 0;

void Transform(int n, int base)
{
    do
    {
        nums[len++] = n % base;
        n /= base;
    } while (n);
}

void Entry()
{
    int a, b, d;
    scanf("%d%d%d", &a, &b, &d);
    Transform(a + b, d);
    for (int i = len - 1; i >= 0; --i)
    {
        printf("%d", nums[i]);
    }
    printf("\n");
}
}

namespace codeup_5901 {
constexpr int kN = 256;

bool IsPalindromeString(const char *str, int n)
{
    for (int i = 0, j = n - 1; i < j; ++i, --j)
    {
        if (str[i] != str[j]) return false;
    }
    return true;
}

int GetLine(char *str, int max_len)
{
    int len = 0, c;
    while ((c = getchar()) != EOF && len < max_len)
    {
        str[len++] = c;
        if (c == '\n') break;
    }
    if (len == max_len || c == '\n')
    { str[--len] = '\0'; }
    else
    { str[len] = '\0'; }
    return len;
}

void Entry()
{
    char inpus[kN];
    int len = GetLine(inpus, sizeof(inpus));
    printf("%s\n", IsPalindromeString(inpus, len) ? "YES" : "NO");
}
}

namespace pat_b1009 {
constexpr int kN = 100;

char str[kN][kN];

void Entry()
{
    int len = 0;
    while (scanf("%s", str[len]) != EOF)
    {
        ++len;
    }
    for (int i = len - 1; i >= 0; --i)
    {
        printf("%s", str[i]);
        if (i > 0) printf(" ");
    }
}
}
}


int main(int argc, char *argv[])
{
    chapter_1_3::TestingChar();
    chapter_1_3::TestingBubbleSort();
    chapter_1_3::TestingEqu();
    chapter_1_3::pat_b1001::TestingCountStepsCallatz();
    chapter_1_3::pat_b1032::Entry();
    chapter_1_3::pat_b1036::Entry();
    chapter_1_3::codeup_1928::Entry();
    chapter_1_3::pat_b1022::Entry();
    chapter_1_3::codeup_5901::Entry();
    return 0;
}




