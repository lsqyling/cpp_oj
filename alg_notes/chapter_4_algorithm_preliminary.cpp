//
// Created by shiqing on 2021/3/31.
//
#include <algorithm>
#include <cstring>
#include <random>
#include <chrono>

#include "CommonHeaders.h"

namespace sort {
template<typename T, int N>
void SelectSort(T (&arr)[N])
{
    for (int i = 0; i < N; ++i)
    {
        int &min = arr[i];
        for (int j = i; j < N; ++j)
        {
            if (arr[j] < min)
            {
                min = arr[j];
            }
        }
        std::swap(min, arr[i]);
    }
}

void TestingSelectSort()
{
    auto &arr = generateRandomArray<10000>();
    SelectSort(arr);
    printf("SelectSort the arr is %s.\n", isSorted(arr) ? "true" : "false");
}

template<typename T, int N>
void InsertSort(T (&arr)[N])
{
    T k;
    int j;
    for (int i = 1; i < N; ++i)
    {
        k = arr[i];
        for (j = i - 1; j >= 0 && k < arr[j]; --j)
        {
            arr[j + 1] = arr[j];
        }
        arr[j + 1] = k;
    }
}

void TestingInsertSort()
{
    auto &arr = generateRandomArray<10'000>();
    InsertSort(arr);
    printf("InsertSort the arr is %s.\n", isSorted(arr) ? "true" : "false");
}

namespace pat_a1025 {
constexpr int kN = 300 * 100 + 5;
constexpr int kK = 305;

struct Student
{
    char id_[15];
    int score_;
    int location_number_;
    int local_rank_;
};

bool operator<(const Student &a, const Student &b)
{
    if (a.score_ != b.score_) return a.score_ > b.score_;
    else return strcmp(a.id_, b.id_) < 0;
}

Student all[kN], local[kK];
int len = 0;

void Entry()
{
    int n, k;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &k);
        for (int j = 0; j < k; ++j)
        {
            scanf("%s%d", local[j].id_, &local[j].score_);
            local[j].location_number_ = i;
        }
        std::sort(local, local + k);
        int r = 1;
        for (int j = 0; j < k; ++j)
        {
            if (j > 0 && local[j].score_ != local[j - 1].score_)
            {
                r = j + 1;
            }
            local[j].local_rank_ = r;
            all[len++] = local[j];
        }
    }
    std::sort(all, all + len);
    printf("%d\n", len);
    int r = 1;
    for (int i = 0; i < len; ++i)
    {
        if (i > 0 && all[i].score_ != all[i - 1].score_)
        {
            r = i + 1;
        }
        printf("%s ", all[i].id_);
        printf("%d %d %d\n", r, all[i].location_number_, all[i].local_rank_);
    }
}
}
}

namespace hash {
constexpr int kLen = 100'000;

bool hash_table[kLen];

void Entry()
{
    int n, m, x;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &x);
        hash_table[x] = true;
    }
    for (int i = 0; i < m; ++i)
    {
        scanf("%d", &x);
        if (hash_table[x])
        { printf("YES\n"); }
        else printf("NO\n");
    }
}
}

namespace recursive {
//F(n) = n!
//F(n) = n * F(n - 1)
int F(int n)
{
    if (n == 0) return 1;
    return n * F(n - 1);
}

void TestingFactorial()
{
    int x = 3;
    printf("3! = %d\n", F(x));
}

//F(0) = F(1) = 1;
//F(n) = F(n - 1) + F(n - 2)

int Fibonacci(int n)
{
    if (n == 0 || n == 1) return 1;
    return Fibonacci(n - 1) + Fibonacci(n - 2);
}

void TestingFibonacci()
{
    int x = 5;
    printf("Fibonacci(5) = %d\n", Fibonacci(x));
}

namespace full_permutation {
constexpr int kMaxN = 11;
int p[kMaxN], hash_table[kMaxN];

void GeneratePermutation(int index, int n)
{
    if (index == n + 1)
    {
        for (int i = 1; i <= n; ++i)
        {
            printf("%d", p[i]);
        }
        printf("\n");
        return;
    }
    for (int x = 1; x <= n; ++x)
    {
        if (hash_table[x] == false)
        {
            p[index] = x;
            hash_table[x] = true;
            GeneratePermutation(index + 1, n);
            hash_table[x] = false;
        }

    }
}

void TestingGeneratePermutation()
{
    int n = 5;
    GeneratePermutation(1, n);
}
}

namespace queen_n {
constexpr int kN = 11;

int p[kN], hash_table[kN], count = 0;

void GenerateQueen(int index, int n)
{
    if (index == n + 1)
    {
        ++count;
        return;
    }
    for (int x = 1; x <= n; ++x)
    {
        if (hash_table[x] == false)
        {
            bool flag = true;
            for (int j = 1; j < index; ++j)
            {
                if (std::abs(index - j) == std::abs(x - p[j]))
                {
                    flag = false;
                    break;
                }
            }
            if (flag)
            {
                p[index] = x;
                hash_table[x] = true;
                GenerateQueen(index + 1, n);
                hash_table[x] = false;
            }
        }
    }
}

void TestingGenerateQueen()
{
    GenerateQueen(1, 8);
    printf("the 8 queen's number is %d.\n", count);
}
}
}

namespace pat_b1020 {
constexpr int kN = 1005;

struct MoonCake
{
    double store_, sell_, price_;
};
auto cmp = [](const MoonCake &a, const MoonCake &b)
{
    return a.price_ > b.price_;
};

MoonCake cakes[kN];

void Entry()
{
    int n;
    double D;
    scanf("%d%lf", &n, &D);
    for (int i = 0; i < n; ++i)
    {
        scanf("%lf", &cakes[i].store_);
    }
    for (int i = 0; i < n; ++i)
    {
        scanf("%lf", &cakes[i].sell_);
        cakes[i].price_ = cakes[i].sell_ / cakes[i].store_;
    }
    std::sort(cakes, cakes + n, cmp);
    double ans = 0;
    for (int i = 0; i < n; ++i)
    {
        if (cakes[i].store_ <= D)
        {
            D -= cakes[i].store_;
            ans += cakes[i].sell_;
        }
        else
        {
            ans += cakes[i].price_ * D;
            break;
        }
    }
    printf("%.2f\n", ans);
}
}

namespace pat_b1023 {
constexpr int kN = 10;

int nums[kN];

void Entry()
{
    for (int i = 0; i < kN; ++i)
    {
        scanf("%d", &nums[i]);
    }
    for (int i = 1; i < kN; ++i)
    {
        if (nums[i])
        {
            printf("%d", i);
            --nums[i];
            break;
        }
    }
    for (int i = 0; i < kN; ++i)
    {
        for (int j = 0; j < nums[i]; ++j)
        {
            printf("%d", i);
        }
    }
}
}

namespace binary {
// A[] The array is a strictly increasing sequence
// [left, right] ---> [0, n-1]
int BinarySearch(const int A[], int left, int right, int x)
{
    int mid;
    while (left <= right)
    {
        mid = (left + right) / 2;
        if (A[mid] == x) return mid;
        else if (x < A[mid])
        {
            right = mid - 1;
        }
        else
        {
            left = mid + 1;
        }
    }
    return -1;
}

// A[] The array is a non-descending sequence
// [left, right] ----> [0, n]
// Find the position of the first element greater than or equal to x in the sequence
int LowerBound(const int A[], int left, int right, int x)
{
    int mid;
    while (left < right)
    {
        mid = (left + right) / 2;
        x <= A[mid] ? right = mid : left = mid + 1;
    }
    return left;
}

//find the position of the first element greater than x in the sequence
int UpperBound(const int A[], int left, int right, int x)
{
    int mid;
    while (left < right)
    {
        mid = (left + right) / 2;
        x < A[mid] ? right = mid : left = mid + 1;
    }
    return left;
}

//sqrt(2) = ?
constexpr double kEps = 1e-5;

double Square(double x)
{
    return x * x;
}

double Sqrt2()
{
    double left = 1, right = 2, mid;
    while (right - left > kEps)
    {
        mid = (left + right) / 2;
        Square(mid) < 2 ? left = mid : right = mid;
    }
    return mid;
}

void TestingSqrt2()
{
    printf("%f", Sqrt2());
}

using Long = int64_t;

// a(b) % m = ?
Long BinaryPowRecursive(Long a, Long b, Long m)
{
    if (b == 0) return 1;
    if (b & 1) return a * BinaryPowRecursive(a, b - 1, m) % m;
    else
    {
        Long mul = BinaryPowRecursive(a, b / 2, m);
        return mul * mul % m;
    }
}

Long BinaryPow(Long a, Long b, Long m)
{
    Long ans = 1;
    while (b)
    {
        if (b & 1)
        {
            ans = ans * a % m;
        }
        a = a * a % m;
        b >>= 1;
    }
    return ans;
}
}

namespace two_pointers {
//, 5, 6}, M = 8, question: 2 + 6 = 8, 3 + 5 = 8 ?
void Equation(const int A[], int n, int m)
{
    int i = 0, j = n - 1;
    while (i < j)
    {
        if (A[i] + A[j] == m)
        {
            printf("%d + %d = %d\n", A[i], A[j], m);
        }
        else if (A[i] + A[j] < m)
        {
            ++i;
        }
        else
        {
            --j;
        }
    }
}

int Merge(const int A[], const int B[], int C[], int n, int m)
{
    int i = 0, j = 0, index = 0;
    while (i < n && j < m)
    {
        if (A[i] <= B[j])
        {
            C[index++] = A[i++];
        }
        else
        {
            C[index++] = B[j++];
        }
    }
    while (i < n) C[index++] = A[i++];
    while (j < m) C[index++] = B[j++];
    return index;
}

constexpr int kN = 105;

void Merge(int A[], int left_1, int left_2, int right_1, int right_2)
{
    int i = left_1, j = right_1;
    int tmp[kN], k = 0;
    while (i <= left_2 && j <= right_2)
    {
        if (A[i] <= A[j])
        {
            tmp[k++] = A[i++];
        }
        else
        {
            tmp[k++] = A[j++];
        }
    }
    while (i <= left_2)
    { tmp[k++] = A[i++]; }
    while (j < right_2)
    { tmp[k++] = A[j++]; }
    for (int s = 0; s < k; ++s)
    {
        A[left_1 + s] = tmp[s];
    }
}

void MergeSort(int A[], int left, int right)
{
    if (left < right)
    {
        int mid = (left + right) / 2;
        MergeSort(A, left, mid);
        MergeSort(A, mid + 1, right);
        Merge(A, left, mid, mid + 1, right);
    }
}

int Partition(int A[], int left, int right)
{
    int tmp = A[left];
    while (left < right)
    {
        while (left < right && A[right] > tmp) --right;
        A[left] = A[right];
        while (left < right && A[left] <= tmp) ++left;
        A[right] = A[left];
    }
    A[left] = tmp;
    return left;
}

void QuickSort(int A[], int left, int right)
{
    if (left < right)
    {
        int pos = Partition(A, left, right);
        QuickSort(A, left, pos - 1);
        QuickSort(A, pos + 1, right);
    }
}

void TestingQuickSort()
{
    auto &arr = generateRandomArray<10'000>();
    QuickSort(arr, 0, 10'000 - 1);
    printf("the arr is sorted %s.\n", isSorted(arr) ? "true" : "false");
}
}

namespace pat_a1093 {
constexpr int kN = 10'005;
constexpr int kMod = 10'0000'0007;

char str[kN];
int left_num_p[kN];

void CalcLeftNumP(int n)
{
    for (int i = 0; i < n; ++i)
    {
        if (i > 0)
        {
            left_num_p[i] = left_num_p[i - 1];
        }
        if (str[i] == 'P')
        {
            ++left_num_p[i];
        }
    }
}

void Entry()
{
    scanf("%s", str);
    int n = strlen(str);
    CalcLeftNumP(n);
    int ans = 0, right_num_t = 0;
    for (int i = n - 1; i >= 0; --i)
    {
        if (str[i] == 'T')
        {
            ++right_num_t;
        }
        else if (str[i] == 'A')
        {
            ans = (ans + left_num_p[i] * right_num_t) % kMod;
        }
    }
    printf("%d\n", ans);
}
}

int RandomPartition(int A[], int left, int right)
{
    static std::default_random_engine e(right - left);
    static std::uniform_int_distribution<int> u(left, right);
    int r = u(e);
    std::swap(A[left], A[r]);
    int tmp = A[left];
    while (left < right)
    {
        while (left < right && A[right] > tmp) --right;
        A[left] = A[right];
        while (left < right && A[left] <= tmp) ++left;
        A[right] = A[left];
    }
    A[left] = tmp;
    return left;
}

//求无序数组的第K大数
int RandomSelect(int A[], int left, int right, int k)
{
    if (left == right) return A[left];
    int p = RandomPartition(A, left, right);
    int m = p - left + 1;
    if (m == k)
    {
        return A[p];
    }
    else if (k < m)
    {
        return RandomSelect(A, left, p - 1, k);
    }
    else
    {
        return RandomSelect(A, p + 1, right, k - m);
    }
}

//问题：给定一个有整数组成的集合，集合中的整数各不相同，现在要将它分为两个子集，使得这两个集合的并为原集合，交为空集合，同时在两个子集合的
//元素个数n1与n2之差的绝对值|n1 - n2|尽可能的小，要求它们各自的元素至和S1与S2之差的绝对值|S1 - S2| 尽可能的大。求这个|S1 - S2|?
constexpr int kN = 10'005;

int nums[kN];

void Solve()
{
    int sum = 0, s1 = 0, n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &nums[i]);
        sum += nums[i];
    }
    RandomSelect(nums, 0, n - 1, n / 2);
    for (int i = 0; i < n / 2; ++i)
    {
        s1 += nums[i];
    }
    int s2 = sum - s1;
    printf("|S1 - S2| = %d\n", s2 - s1);
}


int main(int argc, char *argv[])
{
    sort::TestingSelectSort();
    sort::TestingInsertSort();
    sort::pat_a1025::Entry();
    recursive::TestingFactorial();
    recursive::TestingFibonacci();
    recursive::full_permutation::TestingGeneratePermutation();
    recursive::queen_n::TestingGenerateQueen();
    pat_b1020::Entry();
    pat_b1023::Entry();
    binary::TestingSqrt2();
    two_pointers::TestingQuickSort();
    pat_a1093::Entry();
    Solve();
    return 0;
}