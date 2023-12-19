#include <algorithm>
#include <cstring>
#include <queue>
#include <map>
#include <stack>
#include <set>
#include <cstdio>
#include "CommonHeaders.h"
#include "../part_1_linear/include/Stack.h"
#include "../part_1_linear/include/Queue.h"

/*
 * read a new line,If end of line is encountered, it is extracted but not stored into buf.
 * or or buf.max_size() is reached.
 * @return 0 that is read nothing or read '\n' and it is discarded. otherwise, it is ok.
 */
int getLine(char *buf, int maxSize)
{
    int c, len = 0;
    while ((c = getchar()) != EOF && len < maxSize)
    {
        buf[len++] = c;
        if (c == '\n') break;
    }
    if (len == 0) return 0;
    if (c != '\n' && c != EOF && len < maxSize)
    {
        buf[len] = '\0';
    }
    else buf[--len] = '\0';
    return len;
}

namespace chapter_3_simulation {

/*
 * 3.1 simple simulation
 */
void callatzGuess(int n)
{
    int cnt = 0;
    while (n > 1)
    {
        n = n % 2 ? (3 * n + 1) / 2 : n / 2;
        ++cnt;
    }
    printf("%d\n", cnt);
}

void testingCallatzGuess()
{
    for (int i = 0; i < 1000; ++i)
    {
        callatzGuess(i);
    }
}

namespace pat_b1032 {
constexpr int MaxN = 100'000;
struct School
{
    int No_ = 0, score_ = 0;
};

bool operator<(const School &lhs, const School &rhs) noexcept
{
    return lhs.score_ > rhs.score_;
}

School List[MaxN];

void entryTotalScore()
{
    int n;
    scanf("%d", &n);
    int idx = 0, s = 0;
    for (int i = 0; i < n; ++i)
    {
        scanf("%d%d", &idx, &s);
        List[idx].No_ = idx;
        List[idx].score_ += s;
    }
    int k = 1, maxScore = 0;
    for (int j = 1; j < n; ++j)
    {
        if (maxScore < List[j].score_)
        {
            maxScore = List[j].score_;
            k = j;
        }
    }
    printf("%d %d\n", k, maxScore);
}
}

namespace codeup_1934 {
int num[205];

void entryFindX()
{
    int n, x;
    while (scanf("%d", &n) != EOF)
    {
        for (int i = 0; i < n; ++i)
        {
            scanf("%d", &num[i]);
        }
        scanf("%d", &x);
        int j;
        for (j = 0; j < n; ++j)
        {
            if (num[j] == x)
            {
                printf("%d\n", j);
                break;
            }
        }
        if (j == n) printf("-1\n");
    }

}
}

namespace pat_b1036 {
void entryPrintSquare()
{
    int col;
    char c;
    scanf("%d %c", &col, &c);
    int row = col % 2 ? col / 2 + 1 : col / 2;
    for (int i = 0; i < row; ++i)
    {
        for (int j = 0; j < col; ++j)
        {
            if (i == 0 || i == row - 1)
            {
                printf("%c", c);
            }
            else if (j == 0 || j == col - 1)
            {
                printf("%c", c);
            }
            else printf("%c", ' ');
        }
        printf("\n");
    }
}
}

/*
 * Date difference
 */
namespace codeup_1928 {
constexpr int Month[13][2] = {
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

constexpr bool isLeapYear(int year) noexcept
{
    return (year % 4 == 0 && year % 100) || year % 400 == 0;
}

void entryCalculateDateDifference()
{
    int t1, t2, y1, m1, d1, y2, m2, d2;
    scanf("%d%d", &t1, &t2);
    if (t1 > t2)
    {
        std::swap(t1, t2);
    }
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
        if (d1 == Month[m1][isLeapYear(y1)] + 1)
        {
            ++m1;
            d1 = 1;
        }
        if (m1 == 13)
        {
            ++y1;
            m1 = 1;
        }
        ++cnt;
    }

    printf("%d\n", cnt);
}
}

namespace _3_5BaseConversation {
int z[40];

void transTo(int base, int x)
{
    int idx = 0;
    do
    {
        z[idx++] = x % base;
        x /= base;
    } while (x);
    for (int i = idx - 1; i > -1; --i)
    {
        printf("%d ", z[i]);
    }
    printf("\n");
}
}

namespace codeup_5901 {
constexpr int N = 256;
char Str[N];

void entryIsPalindrome()
{
    scanf("%s", Str);
    int len = strlen(Str);
    int i, j;
    for (i = 0, j = len - 1; i < j; ++i, --j)
    {
        if (Str[i] != Str[j])
        {
            printf("NO\n");
            break;
        }
    }
    if (i == j) printf("YES\n");
}
}
}

void TestingChapter_3()
{
    using namespace chapter_3_simulation;
    testingCallatzGuess();
    pat_b1032::entryTotalScore();
    codeup_1934::entryFindX();
    pat_b1036::entryPrintSquare();
    codeup_1928::entryCalculateDateDifference();
    _3_5BaseConversation::transTo(2, 11);
    codeup_5901::entryIsPalindrome();
}

namespace chapter_4_alg_preliminary {
/*
 * sorting array A[lo, hi)
 */
template<typename T>
void selectSort(T *A, int lo, int hi)
{
    T min;
    while (++lo < hi)
    {
        min = A[lo - 1];
        for (int i = lo; i < hi; ++i)
        {
            if (A[i] < min) min = A[i];
        }
        std::swap(A[lo - 1], min);
    }
}

template<typename T>
bool isSorted(T *A, int lo, int hi) noexcept
{
    while (++lo < hi && A[lo - 1] <= A[lo]);
    return lo == hi;
}

void testingSelectSort()
{
    int A[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    int A2[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    selectSort(A, 0, 10);
    selectSort(A2, 0, 10);
    printf("A is sorted = %d\n", isSorted(A, 0, 10));
    printf("A1 is sorted = %d\n", isSorted(A2, 0, 10));
}

template<typename T>
void insertSort(T *A, int lo, int hi)
{
    T k;
    int j;
    for (int i = lo + 1; i < hi; ++i)
    {
        k = A[i];
        for (j = i - 1; j >= lo && k < A[j]; --j)
        {
            A[j + 1] = A[j];
        }
        A[j + 1] = k;
    }

}

void testingInsertSort()
{
    int A[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    int A2[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    insertSort(A, 0, 10);
    insertSort(A2, 0, 10);
    printf("A is sorted = %d\n", isSorted(A, 0, 10));
    printf("A1 is sorted = %d\n", isSorted(A2, 0, 10));
}

template<typename T>
void bubbleSort(T *A, int lo, int hi)
{
    bool flag = true;
    for (; lo < hi && flag; --hi)
    {
        int i = lo;
        flag = false;
        while (++i < hi)
        {
            if (A[i] < A[i - 1])
            {
                std::swap(A[i], A[i - 1]);
                flag = true;
            }
        }
    }
}

void testingBubbleSort()
{
    int A[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    int A2[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    bubbleSort(A, 0, 10);
    bubbleSort(A2, 0, 10);
    printf("A is sorted = %d\n", isSorted(A, 0, 10));
    printf("A1 is sorted = %d\n", isSorted(A2, 0, 10));
}
/*
 * PAT Ranking
 */
namespace pat_a1025 {
struct Student
{
    char id_[15];
    int testNo_, score_, localRank_;
};

bool operator<(const Student &lhs, const Student &rhs) noexcept
{
    if (lhs.score_ != rhs.score_) return lhs.score_ > rhs.score_;
    else return strcmp(lhs.id_, rhs.id_) < 0;
}

constexpr int MaxN = 100 * 300 + 5;

Student List[MaxN];

void entryPATRanking()
{
    int n, preK = 0, k, idx = 0;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &k);
        for (int j = 0; j < k; ++j)
        {
            scanf("%s%d", List[idx].id_, &List[idx].score_);
            List[idx].testNo_ = i + 1;
            ++idx;
        }
        std::sort(List + i * preK, List + idx);
        List[i * preK].localRank_ = 1;
        for (int r = 1; r < k; ++r)
        {
            if (List[i * preK + r].score_ == List[i * preK + r - 1].score_)
            {
                List[i * preK + r].localRank_ = List[i * preK + r - 1].localRank_;
            }
            else List[i * preK + r].localRank_ = r + 1;
        }
        preK = k;
    }

    std::sort(List, List + idx);
    printf("%d\n", idx);
    int r = 1;
    for (int i = 0; i < idx; ++i)
    {
        if (i > 0 && List[i].score_ != List[i - 1].score_)
        {
            r = i + 1;
        }
        printf("%s %d %d %d\n", List[i].id_, r, List[i].testNo_, List[i].localRank_);
    }
}
}

namespace _4_2Hash {
constexpr int MaxN = 100'000 + 5;
bool hashTable[MaxN];

void entryContainsAOfB()
{
    int n, m, x;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &x);
        hashTable[x] = true;
    }
    scanf("%d", &m);
    for (int j = 0; j < m; ++j)
    {
        scanf("%d", &x);
        if (hashTable[x])
        {
            printf("YES\n");
        }
        else printf("NO\n");
    }
}

namespace hashString {
constexpr int MaxN = 26 * 26 * 26 + 10;

int hashTable[MaxN];

int hashFunc(char S[], int len)
{
    int id = 0;
    for (int i = 0; i < len; ++i)
    {
        id = id * 26 + (S[i] - 'A');
    }
    return id;
}

void entryStringHash()
{
    int n, m;
    char str[5];
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
    {
        scanf("%s", str);
        int id = hashFunc(str, strlen(str));
        ++hashTable[id];
    }
    scanf("%d", &m);
    for (int j = 0; j < m; ++j)
    {
        scanf("%s", str);
        int id = hashFunc(str, strlen(str));
        printf("%d\n", hashTable[id]);
    }
}
}
}

/*
 * 2020/19
 * Lesson 12 Goodbye and good luck
 * First listen and then answer the question.
 * Where is Captain Alison going and how?
 * Our neighbour, Captain Charles Alison will sail from Portsmouth tomorrow.We'll meet him at harbour early in the morning.
 * He will be in his small boat, Topsail. Topsail is a famous little boat. It has sailed across the Atlantic many times.
 * Captain Alison will set out at eight o'clock, so we'll have plenty of time. We'll see his boat and we'll say goodbye to
 * him. He will be away for two months. We are very proud of him. He will take part in an important race across the Atlantic.
 *
 * Composition:
 * Something about Mr.Jason
 * Mr.Jason is a visitor from America.He arrived in Beijing yesterday.He will stay in China for about half a year.During the
 * period, he is going to visit some middle schools in different cities.He wants to collect some information. He has planned
 * to write book about middle school education in China when he gets back to his country.At the same time, he will go to
 * Shanghai for an important meeting. He will be there for a week.He said he would come to China again next year.
 *
 */

namespace _4_3DivideConquer {
int factorial(int n)
{
    if (n == 0) return 1;
    return factorial(n - 1) * n;
}

int fibonacci(int n)
{
    if (n == 0 || n == 1) return 1;
    return fibonacci(n - 1) * fibonacci(n - 2);
}

namespace full_permutation {
constexpr int MaxN = 12;
int n;
bool hashTable[MaxN] = {false};
int P[MaxN];

void generateFullPermutation(int index)
{
    if (index == n + 1)
    {
        for (int i = 1; i <= n; ++i)
        {
            printf("%d ", P[i]);
        }
        printf("\n");
        return;
    }

    for (int x = 1; x <= n; ++x)
    {
        if (!hashTable[x])
        {
            P[index] = x;
            hashTable[x] = true;
            generateFullPermutation(index + 1);
            hashTable[x] = false;
        }
    }
}

void testingFullPermutation()
{
    n = 3;
    generateFullPermutation(1);
}
}

namespace n_queen {
constexpr int MaxN = 13;
int n, count;
bool hashTable[MaxN] = {false};
int P[MaxN];

void generateP(int index)
{
    if (index == n + 1)
    {
        ++count;
        for (int i = 1; i <= n; ++i)
        {
            printf("%d ", P[i]);
        }
        printf("\n");
        return;
    }

    for (int x = 1; x <= n; ++x)
    {
        if (!hashTable[x])
        {
            bool flag = true;
            for (int pre = 1; pre < index; ++pre)
            {
                if (std::abs(index - pre) == std::abs(x - P[pre]))
                {
                    flag = false;
                    break;
                }
            }
            if (flag)
            {
                P[index] = x;
                hashTable[x] = true;
                generateP(index + 1);
                hashTable[x] = false;
            }
        }
    }

}

void testingNQueen()
{
    n = 8;
    generateP(1);
    printf("the number of legal queen is: %d\n", count);
}
}
}

namespace _4_4GreedyAlg {
constexpr int MaxN = 1'005;
struct MoonCake
{
    double store_ = 0, totalSell_ = 0, price_ = 0;
};

bool operator<(const MoonCake &lhs, const MoonCake &rhs) noexcept
{
    return lhs.price_ > rhs.price_;
}

MoonCake List[MaxN];

void entryCalculateMaxProfit()
{
    int n;
    double D;
    scanf("%d%lf", &n, &D);
    for (int i = 0; i < n; ++i)
    {
        scanf("%lf", &List[i].store_);
    }
    for (int i = 0; i < n; ++i)
    {
        scanf("%lf", &List[i].totalSell_);
        List[i].price_ = List[i].totalSell_ / List[i].store_;
    }

    std::sort(List, List + n);
    double r = 0;
    for (int j = 0; j < n; ++j)
    {
        if (List[j].store_ <= D)
        {
            D -= List[j].store_;
            r += List[j].totalSell_;
        }
        else
        {
            r += List[j].price_ * D;
            break;
        }
    }

    printf("%.2f\n", r);
}

namespace pat_b1023 {
int count[10];

void entryMinNum()
{
    for (int i = 0; i < 10; ++i)
    {
        scanf("%d", &count[i]);
    }

    for (int j = 1; j < 10; ++j)
    {
        if (count[j])
        {
            printf("%d", j);
            break;
        }
    }

    for (int k = 0; k < 10; ++k)
    {
        for (int i = 0; i < count[k]; ++i)
        {
            printf("%d", k);
        }
    }
    printf("\n");
}
}

namespace inteval {
constexpr int MaxN = 105;
struct Inteval
{
    int x_, y_;
};

bool operator<(const Inteval &lhs, const Inteval &rhs) noexcept
{
    if (lhs.x_ != rhs.x_) return lhs.x_ > rhs.y_;
    else return lhs.y_ < rhs.y_;
}

Inteval List[MaxN];

void entryTheNumberOfDisjointIntevals()
{
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
    {
        scanf("%d%d", &List[i].x_, &List[i].y_);
    }

    std::sort(List, List + n);
    int ans = 1, lastX = List[0].x_;
    for (int j = 1; j < n; ++j)
    {
        if (List[j].y_ <= lastX)
        {
            lastX = List[j].x_;
            ++ans;
        }
    }

    printf("%d\n", ans);
}
}
}

namespace _4_5Binary {
/*
 * binary search A[left, right]
 *
 */
int binarySearch(int A[], int left, int right, int x)
{
    int mid;
    while (left <= right)
    {
        mid = (right - left) / 2 + left;
        if (x < A[mid]) right = mid - 1;
        else if (A[mid] < x) left = mid + 1;
        else return mid;
    }
    return -1;
}

void testingBinarySearch()
{
    int A[] = {1, 3, 4, 6, 7, 8, 10, 11, 12, 15};
    auto x = binarySearch(A, 0, 9, 6),
            y = binarySearch(A, 0, 9, 9);
    printf("%d %d\n", x, y);
}

/*
 * returns the first pos that not less than x.
 */
int lowerBound(int A[], int lo, int hi, int x)
{
    int mid;
    while (lo < hi)
    {
        mid = lo + (hi - lo) / 2;
        x <= A[mid] ? hi = mid : lo = mid + 1;
    }
    return lo;
}

/*
 * returns the first pos that greater than x.
 */
int upperBound(int A[], int lo, int hi, int x)
{
    int mid;
    while (lo < hi)
    {
        mid = lo + (hi - lo) / 2;
        x < A[mid] ? hi = mid : lo = mid + 1;
    }
    return lo;
}

constexpr double square(double x) noexcept
{
    return x * x;
}

constexpr double EPS = 1e-8;

constexpr double sqrt(double x) noexcept
{
    double left = 1, right = x, mid = 0;
    while (EPS < right - left)
    {
        mid = (left + right) / 2;
        x < square(mid) ? right = mid : left = mid;
    }
    return mid;
}

void testingSqrt()
{
    for (int i = 0; i < 100; ++i)
    {
        auto r = sqrt(i);
        printf("%.8f\n", r);
    }
}

constexpr long binaryPow(long a, long b, long m) noexcept
{
    if (b == 0) return 1;
    if (b & 1) return a * binaryPow(a, b - 1, m) % m;
    else
    {
        auto mul = binaryPow(a, b >> 1, m);
        return mul * mul % m;
    }
}

constexpr long binaryPowNoRecursive(long a, long b, long m) noexcept
{
    long ans = 1;
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

namespace _4_6TwoPointers {

void resolveSumOfAAndB(int A[], int S, int len)
{
    int i = 0, j = len - 1;
    while (i < j)
    {
        if (A[i] + A[j] == S)
        {
            printf("%d %d\n", i, j);
            ++i;
            --j;
        }
        else if (A[i] + A[j] < S) ++i;
        else --j;
    }
}

void testingResolveSumOfAAndB()
{
    int A[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    resolveSumOfAAndB(A, 9, 9);
}

int merge(int A[], int B[], int C[], int n, int m)
{
    int i = 0, j = 0, k = 0;
    while (i < n && j < m)
    {
        if (A[i] <= B[j]) C[k++] = A[i++];
        else C[k++] = B[j++];
    }
    while (i < n) C[k++] = A[i++];
    while (j < m) C[k++] = B[j++];
    return k;
}

constexpr int MaxN = 100;
int Tmp[MaxN];

void merge(int A[], int lo, int hi, int left, int right)
{
    int i = lo, j = left, k = 0;
    while (i <= hi && j <= right)
    {
        if (A[i] <= A[j]) Tmp[k++] = A[i++];
        else Tmp[k++] = A[j++];
    }
    while (i <= hi) Tmp[k++] = A[i++];
    while (j <= right) Tmp[k++] = A[j++];
    for (int w = 0; w < k; ++w)
    {
        A[lo + w] = Tmp[w];
    }
}

void mergeSort(int A[], int left, int right)
{
    if (left < right)
    {
        int mid = (left + right) / 2;
        mergeSort(A, left, mid);
        mergeSort(A, mid + 1, right);
        merge(A, left, mid, mid + 1, right);
    }
}

void mergeSortNotRecursive(int A[], int n)
{
    for (int step = 2; step / 2 < n; step *= 2)
    {
        for (int i = 0; i < n; i += step)
        {
            insertSort(A, i, std::min(i + step, n + 1));
        }
    }
}

void testingMergeSort()
{
    int A[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    mergeSort(A, 0, 9);
    printArray(cout, A) << endl;
}

int partition(int A[], int low, int hi)
{
    int pivot = A[low];
    while (low < hi)
    {
        while (low < hi && pivot <= A[hi]) --hi;
        A[low] = A[hi];
        while (low < hi && A[low] <= pivot) ++low;
        A[hi] = A[low];
    }
    A[low] = pivot;
    return low;
}

/*
 * 2020/1/10
 * Lesson 13 The Greenwood Boys
 * First listen and then answer the question.
 * Why will the police have a difficult time?
 * The Greenwood Boys are a group of pop singers. At present, they are visiting all parts of the country.
 * They will be arriving here tomorrow. They will be coming by train and most of the young people in the town will by meeting them
 * at station.Tomorrow evening they will singing at Worker's Club. The Greenwood Boys will be stay for five days. During this
 * time, they will give five performances.As usual, the police will have a difficult time. They will be trying to keep order.
 * It is always the same on these occasions.
 */

void quickSort(int A[], int left, int right)
{
    if (left < right)
    {
        auto index = partition(A, left, right);
        quickSort(A, left, index - 1);
        quickSort(A, index + 1, right);
    }
}

void testingQuickSort()
{
    int A[] = {0, 1, 2, 3, 9, 8, 7, 6, 5, 4};
    quickSort(A, 0, 9);
    printArray(cout, A) << endl;
}
}

namespace pat_b1040 {
constexpr int MOD = 1'000'000'007;
constexpr int MaxN = 100'005;

char str[MaxN];
int leftNumOfP[MaxN];

void entryCountNumOfPAT()
{
    scanf("%s", str);
    int len = strlen(str);
    for (int i = 0; i < len; ++i)
    {
        if (i) leftNumOfP[i] = leftNumOfP[i - 1];
        if (str[i] == 'P')
        {
            ++leftNumOfP[i];
        }
    }
    int ans = 0, rightNumOfT = 0;
    for (int j = len - 1; j >= 0; --j)
    {
        if (str[j] == 'T') ++rightNumOfT;
        else if (str[j] == 'A')
        {
            ans = (ans + leftNumOfP[j] * rightNumOfT) % MOD;
        }
    }
    printf("%d\n", ans);
}
}
}

void TestingChapter_4()
{
    using namespace chapter_4_alg_preliminary;
    testingSelectSort();
    testingInsertSort();
    testingBubbleSort();
    pat_a1025::entryPATRanking();
    _4_2Hash::entryContainsAOfB();
    _4_2Hash::hashString::entryStringHash();
    _4_3DivideConquer::full_permutation::testingFullPermutation();
    _4_3DivideConquer::n_queen::testingNQueen();
    _4_4GreedyAlg::entryCalculateMaxProfit();
    _4_4GreedyAlg::pat_b1023::entryMinNum();
    _4_4GreedyAlg::inteval::entryTheNumberOfDisjointIntevals();
    _4_5Binary::testingBinarySearch();
    _4_5Binary::testingSqrt();
    _4_6TwoPointers::testingResolveSumOfAAndB();
    _4_6TwoPointers::testingMergeSort();
    _4_6TwoPointers::testingQuickSort();
    pat_b1040::entryCountNumOfPAT();
}

/*
 * 2020/1/8
 * Lesson 12 Goodbye and good luck
 * First listen and answer the question.
 * Where is Captain Alison going and how?
 * Our neighbour, Captain Charles Alison will sail from Portsmouth tomorrow.
 * We will meet him at the harbour early in the morning.
 * He will be his small boat, Topsail. Topsail is a famous little boat.
 * It has sailed across the Atlantic many times.
 * Captain Alison will set out at eight o'clock, so we'll have plenty of time.
 * We'll see his boat and then we'll say goodbye to him.
 * He will be away for two month.
 * We are very proud of him.
 * He will take part in an important race across the Atlantic .
 */

namespace chapter_5_mathematics {

namespace pat_a1069 {
constexpr int N = 4;

void toArray(int n, int num[])
{
    for (int i = 0; i < N; ++i)
    {
        num[i] = n % 10;
        n /= 10;
    }
}

int toNum(int num[])
{
    int sum = 0;
    for (int i = 0; i < N; ++i)
    {
        sum = sum * 10 + num[i];
    }
    return sum;
}

void entryBlockHoleNum()
{
    int n;
    scanf("%d", &n);
    int aux[N + 1];
    while (n != 0 && n != 6174)
    {
        toArray(n, aux);
        std::sort(aux, aux + N, std::greater<int>());
        auto max = toNum(aux);
        std::sort(aux, aux + N, std::less<int>());
        auto min = toNum(aux);
        n = max - min;
        printf("%04d - %04d = %04d\n", max, min, n);
    }
}
}

constexpr int gcd(int a, int b) noexcept
{
    return b ? gcd(b, a % b) : a;
}

constexpr int gcdNotRecursive(int a, int b) noexcept
{
    int r = 0;
    while (b)
    {
        r = a % b;
        a = b;
        b = r;
    }
    return a;
}

void testingGcd()
{
    for (int i = 0, j = 100; i < j; ++i, --j)
    {
        printf("gcd(%d, %d) = %d\n", i, j, gcdNotRecursive(i, j));
    }
}

constexpr bool isPrime(int n) noexcept
{
    if (n <= 1) return false;
    int sqr = std::sqrt(n);
    for (int i = 2; i <= sqr; ++i)
    {
        if (n % i == 0) return false;
    }
    return true;
}

void testingIsPrime()
{
    std::vector<int> vi;
    for (int i = 0; i < 100'000'000; ++i)
    {
        if (isPrime(i)) vi.push_back(i);
    }
    cout << vi.size() << endl;
}

namespace eratosthenes {
constexpr int MaxN = 100'000'005;
bool p[MaxN] = {false};

std::vector<int> primes;

void findPrime()
{
    for (int i = 2; i < MaxN; ++i)
    {
        if (!p[i])
        {
            primes.push_back(i);
            for (int j = i * 2; j < MaxN; j += i)
            {
                p[j] = true;
            }
        }
    }
    cout << primes.size() << endl;
}
}
}

void TestingChapter_5()
{
    using namespace chapter_5_mathematics;
    pat_a1069::entryBlockHoleNum();
    testingGcd();
    testingIsPrime();
    eratosthenes::findPrime();
}

namespace chapter_7_data_structure {
namespace Stack {
template<typename T, unsigned L = 256>
struct S
{
    T data_[L];
    int top_ = -1;
};


template<typename T>
void clear(S<T> &s)
{
    s.top_ = -1;
}

template<typename T>
int size(const S<T> &s)
{
    return s.top_ + 1;
}

template<typename T>
bool empty(const S<T> &s)
{
    return s.top_ == -1;
}

template<typename T>
void push(S<T> &s, const T &x)
{
    s.data_[++s.top_] = x;
}

template<typename T>
void pop(S<T> &s)
{
    --s.top_;
}

template<typename T>
T top(S<T> &s)
{
    return s.data_[s.top_];
}

void testingStack()
{
    S<int> s;
    for (int i = 0; i < 100; ++i)
    {
        push(s, i);
    }
    cout << size(s) << endl;
    while (!empty(s))
    {
        pop(s);
    }
    cout << empty(s) << endl;
}
}


namespace Queue {
template<typename T, unsigned L = 128>
struct Q
{
    T data_[L];
    int front_ = -1, rear_ = -1;
};

template<typename T>
void clear(Q<T> &q)
{
    q.front_ = q.rear_ = -1;
}

template<typename T>
int size(const Q<T> &q)
{
    return q.rear_ - q.front_;
}

template<typename T>
bool empty(const Q<T> &q)
{
    return q.front_ == q.rear_;
}

template<typename T>
void enqueue(Q<T> &q, T x)
{
    q.data_[++q.rear_] = x;
}

template<typename T>
void dequeue(Q<T> &q)
{
    ++q.front_;
}

void testingQueue()
{
    Q<int> q;
    for (int i = 0; i < 100; ++i)
    {
        enqueue(q, i);
    }
    cout << size(q) << endl;
    for (int j = 0; j < 50; ++j)
    {
        dequeue(q);
    }
    cout << empty(q) << endl;
}
}

namespace pat_1097 {
constexpr int MaxN = 100'000;
constexpr int MaxK = 10'005;

struct Node
{
    int address_, key_, next_;
};

Node nodeList[MaxN];
Node dupList[MaxN];
bool hashTable[MaxK];

void entryDuplicationOnLinkedList()
{
    int h, n, address, key, next;
    scanf("%d%d", &h, &n);
    for (int i = 0; i < n; ++i)
    {
        scanf("%d%d%d", &address, &key, &next);
        nodeList[address].address_ = address;
        nodeList[address].key_ = key;
        nodeList[address].next_ = next;
    }
    auto p = h, preP = -1, dpIdx = 0;
    while (p != -1)
    {
        key = nodeList[p].key_;
        if (!hashTable[std::abs(key)])
        {
            hashTable[std::abs(key)] = true;
        }
        else
        {
            dupList[dpIdx++] = nodeList[p];
            nodeList[preP].next_ = nodeList[p].next_;

        }
        preP = p;
        p = nodeList[p].next_;
    }
    p = h;
    while (nodeList[p].next_ != -1)
    {
        printf("%05d %d %05d\n", nodeList[p].address_, nodeList[p].key_, nodeList[p].next_);
        p = nodeList[p].next_;
    }
    printf("%05d %d %d\n", nodeList[p].address_, nodeList[p].key_, nodeList[p].next_);
    int j;
    for (j = 0; j < dpIdx - 1; ++j)
    {
        printf("%05d %d %05d\n", dupList[j].address_, dupList[j].key_, dupList[j + 1].address_);
    }
    if (j == dpIdx - 1) printf("%05d %d %d", dupList[j].address_, dupList[j].key_, -1);
}
}
}

void TestingChapter_7()
{
    using namespace chapter_7_data_structure;
    Stack::testingStack();
    Queue::testingQueue();
    pat_1097::entryDuplicationOnLinkedList();
}

/*
 * 2020/1/11
 * Composition:
 * There are many popular stars, such as Jackie Chen, Jay Chou, Zhang Ziyi and so on. However, my favourite star is Jeremy
 * Lin. He is a famous basketball player. He is very cool and he plays basketball very well. Besides, he is hard-working
 * and he has ever studies in a famous university.I like playing basketball, too. I want to be a basketball star when I
 * grow up. I will work hard, too. I want to go to a famous university.
 */

namespace chapter_8_search {
namespace DFS {
namespace dfs_example_1 {
constexpr int MaxN = 30;
int n, V, maxC;
int W[MaxN], C[MaxN];

void dfs(int index, int sumW, int sumC)
{
    if (index == n)
    {
        if (sumW <= V && maxC < sumC)
        {
            maxC = sumC;
        }
        return;
    }
    dfs(index + 1, sumW, sumC);
    dfs(index + 1, sumW + W[index], sumC + C[index]);
}

int ans = 0;

void dfsOptimization(int index, int sumW, int sumC)
{
    if (index == n) return;
    dfsOptimization(index + 1, sumW, sumC);
    if (sumW + W[index] <= V)
    {
        if (sumC + C[index] > ans)
        {
            ans = sumC + C[index];
        }
        dfsOptimization(index + 1, sumW + W[index], sumC + C[index]);
    }
}

void entryMaxProfit()
{
    scanf("%d%d", &n, &V);
    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &W[i]);
    }
    for (int j = 0; j < n; ++j)
    {
        scanf("%d", &C[j]);
    }
//    dfs(0, 0, 0);
//    printf("%d\n", maxC);
    dfsOptimization(0, 0, 0);
    printf("%d\n", ans);
}
}

namespace dfs_example_2 {
constexpr int MaxN = 100;
int n, k, x, maxSumSqu = -1, A[MaxN];
std::vector<int> tmp, ans;

void dfs(int index, int nowK, int sum, int sumSqu)
{
    if (nowK == k && sum == x)
    {
        if (sumSqu > maxSumSqu)
        {
            maxSumSqu = sumSqu;
            ans = tmp;
        }
        return;
    }
    if (index == n || nowK > k || sum > x) return;
//    select index No.
    tmp.push_back(A[index]);
    dfs(index + 1, nowK + 1, sum + A[index], sumSqu + A[index] * A[index]);
    tmp.pop_back();
//    not select index No.
    dfs(index + 1, nowK, sum, sumSqu);
}
}
}


namespace BFS {
namespace bfs_1 {
constexpr int MaxN = 120;
struct Node
{
    int x_, y_;
};
int matrix[MaxN][MaxN];
bool inq[MaxN][MaxN];
constexpr int X[4] = {0, 0, 1, -1};
constexpr int Y[4] = {1, -1, 0, 0};

constexpr bool judge(int x, int y, int m, int n)
{
    if (x >= n || x < 0 || y >= m || y < 0) return false;
    return !(matrix[x][y] == 0 || inq[x][y]);
}

void bfs(int x, int y, int m, int n)
{
    std::queue<Node> Q;
    Q.push({x, y});
    inq[x][y] = true;
    while (!Q.empty())
    {
        auto h = Q.front();
        Q.pop();
        for (int i = 0; i < 4; ++i)
        {
            auto newX = h.x_ + X[i];
            auto newY = h.y_ + Y[i];
            if (judge(newX, newY, m, n))
            {
                Q.push({newX, newY});
                inq[newX][newY] = true;
            }
        }
    }
}

void entryZeroOneOfMatrix()
{
    int m, n;
    scanf("%d%d", &m, &n);
    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            scanf("%d", &matrix[m][n]);
        }
    }
    int ans = 0;
    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (matrix[i][j] == 1 && !inq[i][j])
            {
                ++ans;
                bfs(i, j, m, n);
            }
        }
    }
    printf("%d\n", ans);
}
}

namespace bfs_2 {
constexpr int MaxN = 100;
constexpr int X[4] = {0, 0, 1, -1};
constexpr int Y[4] = {1, -1, 0, 0};

struct Node
{
    int x_, y_, step_;
};

Node S, T;
int row, col;
char mazeMatrix[MaxN][MaxN];
bool inq[MaxN][MaxN];

bool judge(int x, int y) noexcept
{
    if (x >= row || x < 0 || y >= col || y < 0) return false;
    if (mazeMatrix[x][y] == '*') return false;
    return !inq[x][y];
}

int bfs()
{
    std::queue<Node> Q;
    Q.push(S);
    while (!Q.empty())
    {
        auto top = Q.front();
        Q.pop();
        if (top.x_ == T.x_ && top.y_ == T.y_)
        {
            return top.step_;
        }
        for (int i = 0; i < 4; ++i)
        {
            int newX = top.x_ + X[i];
            int newY = top.y_ + Y[i];
            if (judge(newX, newY))
            {
                Q.push({newX, newY, top.step_ + 1});
                inq[newX][newY] = true;
            }
        }
    }
    return -1;
}

void entryMaze()
{
    scanf("%d%d", &row, &col);
    for (int i = 0; i < row; ++i)
    {
        getchar();
        for (int j = 0; j < col; ++j)
        {
            mazeMatrix[i][j] = getchar();
        }
        mazeMatrix[i][col + 1] = '\0';
    }

    scanf("%d%d%d%d", &S.x_, &S.y_, &T.x_, &T.y_);
    S.step_ = 0;
    printf("%d\n", bfs());
}
}
}
}

void TestingChapter_8()
{
    using namespace chapter_8_search;
    DFS::dfs_example_1::entryMaxProfit();
    BFS::bfs_2::entryMaze();
}

namespace chapter_9_tree {
template<typename T>
struct Node
{
    explicit Node(const T &val = T()) : data_(val), left_(nullptr), right_(nullptr)
    {
    }

    T data_;
    Node *left_, *right_;

    /*~Node() {
        cout << "deleting..." << data_ << endl;
    }*/
};


using INode = Node<int>;
using SNode = Node<string>;

void search(INode *root, int x, int newData)
{
    if (root == nullptr) return;
    if (root->data_ == x)
    {
        root->data_ = newData;
    }
    search(root->left_, x, newData);
    search(root->right_, x, newData);
}

SNode *treeFactory()
{
    auto n1 = new SNode("A"),
            n2 = new SNode("B"),
            n3 = new SNode("C"),
            n4 = new SNode("D"),
            n5 = new SNode("E"),
            n6 = new SNode("F"),
            n7 = new SNode("G");
    n1->left_ = n2;
    n1->right_ = n3;
    n2->left_ = n4;
    n2->right_ = n5;
    n3->left_ = n6;
    n3->right_ = n7;
    return n1;
}

template<typename T>
void destroy(T *root) noexcept
{
    if (root)
    {
        destroy(root->left_);
        destroy(root->right_);
        delete root;
    }
}

void preOrderTraversal(SNode *root)
{
    if (root)
    {
        cout << root->data_;
        preOrderTraversal(root->left_);
        preOrderTraversal(root->right_);
    }
}

using Stack = linear::Stack<SNode *>;

void preOrder(SNode *root)
{
    auto p = root;
    Stack S;
    while (p || !S.empty())
    {
        while (p)
        {
            S.push(p);
            cout << p->data_;
            p = p->left_;
        }
        if (!S.empty())
        {
            p = S.pop();
            p = p->right_;
        }
    }
}


void inOrderTraversal(SNode *root)
{
    if (root)
    {
        inOrderTraversal(root->left_);
        cout << root->data_;
        inOrderTraversal(root->right_);
    }
}

void inOrder(SNode *root)
{
    Stack S;
    auto p = root;
    while (p || !S.empty())
    {
        while (p)
        {
            S.push(p);
            p = p->left_;
        }
        if (!S.empty())
        {
            p = S.pop();
            cout << p->data_;
            p = p->right_;
        }
    }
}

void postOrderTraversal(SNode *root)
{
    if (root)
    {
        postOrderTraversal(root->left_);
        postOrderTraversal(root->right_);
        cout << root->data_;
    }
}

void postOrder(SNode *root)
{
    Stack S;
    SNode *p = root, *r = nullptr;
    while (p || !S.empty())
    {
        while (p)
        {
            S.push(p);
            p = p->left_;
        }
        if (!S.empty())
        {
            p = S.top();
            if (p->right_ && p->right_ != r)
            {
                p = p->right_;
            }
            else
            {
                S.pop();
                cout << p->data_;
                r = p, p = nullptr;
            }
        }
    }
}

void testingTraversal()
{
    auto root = treeFactory();
    cout << "pre order traversal:" << endl;
    preOrderTraversal(root);
    cout << endl;
    preOrder(root);

    cout << "\nin order traversal:" << endl;
    inOrderTraversal(root);
    cout << endl;
    inOrder(root);

    cout << "\npost order traversal:" << endl;
    postOrderTraversal(root);
    cout << endl;
    postOrder(root);
    destroy(root);

}

INode *createByPreOrderAndInOrder(int pre[], int in[], int preL, int preR, int inL, int inR)
{
    if (preL > preR) return nullptr;
    auto root = new INode;
    root->data_ = pre[preL];
    int k;
    for (k = inL; k <= inR; ++k)
    {
        if (in[k] == pre[preL]) break;
    }
    int numLeft = k - inL;
//    left tree's preorder [preL + 1, preL + numLeft] inOrder[inL, k - 1]
    root->left_ = createByPreOrderAndInOrder(pre, in, preL + 1, preL + numLeft, inL, k - 1);
//    right subtree's preorder[preL + numLeft + 1, preR] inorder[k+ 1, inR]
    root->right_ = createByPreOrderAndInOrder(pre, in, preL + numLeft + 1, preR, k + 1, inR);
    return root;
}

/*
 * Tree traversals
 */
namespace pat_a1020 {
constexpr int MaxN = 35;
int postOrder[MaxN];
int inOrder[MaxN];

struct Node
{
    int data_;
    Node *left_ = nullptr, *right = nullptr;
};

Node *createTree(int post[], int in[], int pL, int pR, int inL, int inR)
{
    if (pL > pR) return nullptr;
    auto root = new Node;
    root->data_ = post[pR];
    int k;
    for (k = inL; k <= inR; ++k)
    {
        if (in[k] == post[pR]) break;
    }
    int numLeft = k - inL;
    root->left_ = createTree(post, in, pL, pL + numLeft - 1, inL, k - 1);
    root->right = createTree(post, in, pL + numLeft, pR - 1, k + 1, inR);
    return root;
}

void entryLayerTraversal()
{
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &postOrder[i]);
    }
    for (int j = 0; j < n; ++j)
    {
        scanf("%d", &inOrder[j]);
    }
    auto root = createTree(postOrder, inOrder, 0, n - 1, 0, n - 1);
    linear::Queue<Node *> Q;
    Q.enqueue(root);
    int cnt = 0;
    while (!Q.empty())
    {
        auto now = Q.dequeue();
        ++cnt;
        printf("%d", now->data_);
        if (cnt < n) printf(" ");
        if (now->left_) Q.enqueue(now->left_);
        if (now->right) Q.enqueue(now->right);
    }
}
}

namespace _9_3TreeTraversal {
constexpr int MaxN = 1'000;
struct Node
{
    int data_, layer_;
    std::vector<int> child_;
};

Node tree[MaxN];

void preorder(int root)
{
    if (root == -1) return;
    printf("%d ", tree[root].data_);
    for (int i = 0; i < tree[root].child_.size(); ++i)
    {
        preorder(tree[root].child_[i]);
    }
}

/*
 * 2020/1/12
 * Lesson 14 Do you speak English?
 * First listen and then answer the question
 * Did the young man speak English?
 * I had an amusing experience last year. After I had left the small village in the South of France, I drove on to the next
 * town. On the way, a young man waved to me.I stopped and he asked me for a lift.As soon as he had got into the car, I said
 * good morning to him in French and he replied in the same language. Apart from a few words, I do not know any French at all.
 * Neither of us spoken during the journey. I had nearly reached the town when the young man suddenly said, very slowly,
 * 'Do you speak English?' As I soon learnt, he was English himself.
 *
 * Composition:
 * We all know English is very useful for us. I study English every day. And I always get good grades in exams. But I cant't
 * speak English well. So I ask my pen friend for some advice.Firstly, he told me to speak English as much as possible.
 * Secondly, he thought I should keep a diary in English. Thirdly, he asked me to listen to English songs and watch English
 * films.Listening can also help with spoken English. I think these are good ways to improve my spoken English.
 */

void layerOrder(int root)
{
    linear::Queue<int> Q;
    Q.enqueue(root);
    tree[root].layer_ = 0;
    while (!Q.empty())
    {
        auto front = Q.dequeue();
        printf("%d ", tree[front].data_);
        for (int i = 0; i < tree[front].child_.size(); ++i)
        {
            auto child = tree[front].child_[i];
            tree[child].layer_ = tree[front].layer_ + 1;
            Q.enqueue(child);
        }
    }
}
}

namespace pat_a1053 {
constexpr int MaxN = 105;
struct Node
{
    int weight_;
    std::vector<int> child_;
};

Node tree[MaxN];

bool cmp(int a, int b) noexcept
{
    return tree[a].weight_ > tree[b].weight_;
}

int n, m, S;
int path[MaxN];

void dfs(int index, int numNode, int sum)
{
    if (sum > S) return;
    if (sum == S)
    {
        if (!tree[index].child_.empty()) return;
        for (int i = 0; i < numNode; ++i)
        {
            printf("%d", tree[path[i]].weight_);
            if (i < numNode - 1) printf(" ");
            else printf("\n");
        }
        return;
    }
    for (int j = 0; j < tree[index].child_.size(); ++j)
    {
        int child = tree[index].child_[j];
        path[numNode] = child;
        dfs(child, numNode + 1, sum + tree[child].weight_);
    }
}

void entryPrintPathOfSumEqualsS()
{
    scanf("%d%d%d", &n, &m, &S);
    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &tree[i].weight_);
    }
    int id, sz, child;
    for (int j = 0; j < m; ++j)
    {
        scanf("%d%d", &id, &sz);
        for (int i = 0; i < sz; ++i)
        {
            scanf("%d", &child);
            tree[id].child_.push_back(child);
        }
        std::sort(tree[id].child_.begin(), tree[id].child_.end(), cmp);
    }

    path[0] = 0;
    dfs(0, 1, tree[0].weight_);
}
}

namespace _9_4BST {
struct Node
{
    int data_;
    Node *left_, *right_;

    explicit Node(int val = 0) : data_(0), left_(nullptr), right_(nullptr)
    {
    }
};

void search(Node *root, int x)
{
    if (root == nullptr)
    {
        printf("search failed\n");
        return;
    }
    if (x == root->data_)
    {
        printf("%d\n", root->data_);
    }
    else if (x < root->data_)
    {
        search(root->left_, x);
    }
    else search(root->right_, x);
}

void insert(Node *&root, int x)
{
    if (root == nullptr)
    {
        root = new Node(x);
        return;
    }
    if (x == root->data_) return;
    else if (x < root->data_)
    {
        insert(root->left_, x);
    }
    else insert(root->right_, x);
}

Node *create(int data[], int n)
{
    Node *root = nullptr;
    for (int i = 0; i < n; ++i)
    {
        insert(root, data[i]);
    }
    return root;
}

Node *findMax(Node *root)
{
    while (root->right_)
    {
        root = root->right_;
    }
    return root;
}

Node *findMin(Node *root)
{
    while (root->left_)
    {
        root = root->left_;
    }
    return root;
}

void deleteOf(Node *&root, int x)
{
    if (root == nullptr) return;
    if (root->data_ == x)
    {
        if (root->left_)
        {
            auto preX = findMax(root->left_);
            root->data_ = preX->data_;
            deleteOf(root->left_, x);
        }
        else if (root->right_)
        {
            auto succ = findMin(root->right_);
            root->data_ = succ->data_;
            deleteOf(root->right_, x);
        }
        else
        {
            delete root;
            root = nullptr;
        }
    }
    else if (root->data_ < x)
    {
        deleteOf(root->right_, x);
    }
    else
    {
        deleteOf(root->left_, x);
    }
}

/*
 * 2020/1/22
 * Lesson 15 Good news
 * First listen and then answer the question.
 * What was the good news?
 * The secretary told me that Mr.Harmsworth would see me. I felt very nervous when I went into his office. He did not look
 * up from his desk when I entered.After I had sat down, he said that business was very bad. He told me that the firm
 * could not afford to pay such large salaries.Twenty people had already left. I knew that my turn had come.
 * 'Mr.Harmsworth' I said in a weak voice.
 * 'Don't interrupt' he said. Then he smiled he told me that I would receive an extra thousand pounds a year!
 *
 * Composition:
 * Yesterday was my birthday.When I got up in the morning, I found nobody was at home.My parents had gone out.But they
 * didn't leave a message.It was boring alone.I decided to visit my friends.I was just about to go out when it began to rain.
 * It rained cats and dogs.What a terrible day!I was so sad.In the evening, I heard someone knocking at my door while I was
 * sleeping. I got up and opened the door.My parents and my friends were in the living room. There was also a big birthday cake.
 * They said, 'Happy birthday to you!' It's really a big surprise.
 *
 *
 * Lesson 16 A polite request
 * First listen and then answer the question.
 * What was the polite request?
 * If you park your car in the wrong place, a traffic policeman will soon find it.You will be very luck if he lets you go
 * without a ticket.However, this does not always happen.Traffic police are sometimes very polite.During a holiday in Sweden,
 * I found this note on my car, 'sir, we welcome you to our city'.This is no parking area. You will enjoy your stay here,
 * if you pay attention to our street signs.This note is only a reminder.If you receive a request like this, you can not
 * fail to obey it.
 *
 * Composition:
 * More and more people have bought cars, and a lot of people want to buy cars, too.Frankly speaking, cars have ever made
 * our life easier.But now, too many cars make our life difficult, especially in big cities.On one hand, too many cars can
 * cause heavy traffic jams.At the same time, there are also more and more accidents.On the other hand, too many cars are
 * bad for our health and environment.So I think we'd better go to school by bus or by bike. It is not so far from my house
 * to school. So I walk there every day.
 *
 *
 * Lesson 17 Always young
 * First listen and then answer the question.
 * Why doesn't aunt Jennifer tell anyone how old she is?
 * My aunt Jennifer is an actress.She must be at least thirty-five years old.In spite of this, she often appears on the stage
 * as a young girl.Jennifer will have to take part in a new play soon.This time, she will be girl of seventeen.In the play,
 * she must appear in a bright red dress and long black stockings.Last year in another play, she had to wear short socks,
 * and a bright, orange-coloured dress. If anyone ever asks her how old she is, she always answers,'Darling, it must be terrible
 * to be grown up'.
 *
 * Composition:
 * I want to be a teacher when I grow up!
 * When I grow up, I want to be a teacher.My parents and my sister are all teachers.They teach students knowledge and help
 * them with their difficulties.All their students and workmates like them very much.But to be a teacher, I must study
 * hard from now on. I must be good at my study.So I wil try my best to learn more knowledge. When i become a teacher, i
 * will communicate with my students and be their friend.We will get along well with each other.Of course, I will work hard, too.
 * Being a teacher, i will have long holidays. I will help students with their study or travel around our country.
 *
 *
 * Lesson 18 He often does this
 * First listen and then answer the question
 * What had happened to the write's bag?
 * After i had had a lunch at a village pub, I looked for my bag.I had left it on a chair beside the door and now it wasn't
 * there.As i was looking for it, the landlord came in.'Did you have a good meal?' he asked.'Yes, thank you!' i answered, 'But
 * i can't pay the bill. I haven't got my bag.' The landlord smiled and immediately went out. I a few minutes, he returned with
 * my bag and gave it back to me.'I'm so sorry' he said, 'my dog had taken it into the garden. He often does this!'
 *
 *
 * Composition:
 * This is what happened to Mr.Smith last night.Mr.Smith had dinner with his friends in a restaurant.When he returned home,
 * it was very late.He stood in front of the door and felt his key in his bag.But he couldn't find it.His wife had already
 * gone to bed, so he decided not to wake her up.He found a ladder behind his house.He put it against the wall, and began to
 * climb towards the bedroom window.He was almost up to the window when a policeman appeared below. He shouted at Mr.Smith,
 * 'What are you doing there?' He thought Mr.Smith was a thief.Mrs.Smith was woken up by the noise.She got up and explained who
 * he was.'OK, now you can get in, but don't do it again,' the policeman said and then left.
 *
 *
 * Lesson 19 Sold out
 * First listen and then answer the question
 * When will the write see the play?
 * 'The play may begin at any moment' I said. 'It may have begun already' Susan answered. I hurried to the ticket office.
 * 'May I have two tickets please?' I asked. 'I'm sorry, We've sold out' the girl said.'What a pity!' Susan exclaimed.
 * Just then, a man hurried to the ticket office. 'Can I return these two tickets?' he asked. 'Certainly' the girl said.
 * I went back to the ticket office at once.'Could I have those two tickets please ?' I asked.
 * 'Certainly,' the girl said, 'but they're for next Wednesday's performance,
 * do you still want them?'
 * 'I might as well have them' I said sadly.
 *
 *
 * Composition:
 * I get up at 6:30 every day and I never go to school late.But yesterday I was late. I found it was still dark outside
 * when I woke up yesterday morning. I looked at my watch. It was 5:30. I fell asleep again.After a while, the clock in
 * the living room struck seven.But my watch was still 5:30. "Oh, my dear! My watch doesn't work," I said. I got up quickly
 * brushed my teeth, washed my face and then rushed out of the door.I hurried to school. When I went into our classroom, the
 * first lesson had been over. The teacher said to me, "Don't be late again."
 */
}


namespace pat_a1043 {
struct Node
{
    int data_;
    Node *left_, *right_;

    explicit Node(int x = 0) : data_(x), left_(nullptr), right_(nullptr)
    {
    }
};

void insert(Node *&root, int x)
{
    if (root == nullptr)
    {
        root = new Node(x);
        return;
    }
    if (x < root->data_) insert(root->left_, x);
    else insert(root->right_, x);
}

void preorder(Node *root, std::vector<int> &vi)
{
    if (root)
    {
        vi.push_back(root->data_);
        preorder(root->left_, vi);
        preorder(root->right_, vi);
    }
}

void preorderMirror(Node *root, std::vector<int> &vi)
{
    if (root)
    {
        vi.push_back(root->data_);
        preorderMirror(root->right_, vi);
        preorderMirror(root->left_, vi);
    }
}

void postorder(Node *root, std::vector<int> &vi)
{
    if (root)
    {
        postorder(root->left_, vi);
        postorder(root->right_, vi);
        vi.push_back(root->data_);
    }
}

void postorderMirror(Node *root, std::vector<int> &vi)
{
    if (root)
    {
        postorderMirror(root->right_, vi);
        postorderMirror(root->left_, vi);
        vi.push_back(root->data_);
    }
}

void entryIsBinarySearchTree()
{
    Node *root = nullptr;
    std::vector<int> pre, preM, post, postM, input;
    int n, x;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &x);
        input.push_back(x);
        insert(root, x);
    }
    preorder(root, pre);
    preorderMirror(root, preM);
    postorder(root, post);
    postorderMirror(root, postM);
    if (pre == input)
    {
        printf("YES\n");
        for (int i = 0; i < post.size(); ++i)
        {
            printf("%d", post[i]);
            if (i < post.size() - 1)
            {
                printf(" ");
            }
        }
    }
    else if (preM == input)
    {
        printf("YES\n");
        for (int i = 0; i < postM.size(); ++i)
        {
            printf("%d", postM[i]);
            if (i < postM.size() - 1)
            {
                printf(" ");
            }
        }
    }
    else printf("NO");
}
}
/*
 * 2020/1/23
 * Lesson 20 One man in a boat
 * First listen and then answer the question
 * Why is fishing the writer's favourite sport
 * Fishing is my favourite sport. I often fish for hours with catching anything. But this does not worry me. Some fishermen
 * are unlucky. Instead of catching fish, they catch old boots and rubbish. I am even less luck. I never catch anything-
 * not even old boots.After having spent whole mornings on the river, I always go home with an empty bag. 'You must give up fishing'
 * my friends say, 'It's a waste of time'. They don't realize one important thing, I am not really interested in fishing, I am only
 * interested in sitting in a boat and doing nothing at all.
 *
 *
 * Composition:
 * My favourite sport
 * I like doing sports very much. I often take part in different kinds of sports. But my favourite sport is playing football.
 * I am a football player of our school team.Football is very exciting.I think football players are very cool. Playing football
 * can make me strong hand healthy. It can also make me feel relaxed and happy after class. I can learn to work with my teammates.
 * We play football very Saturday and Sunday afternoon. I hope I can be a famous football player when I grow up.
 *
 *
 * Lesson 21 Mad or not
 * First listen and then answer the question
 * Why do people think the writer is mad?
 * Aeroplanes are slowly driving me mad. I live near an airport, passing planes can be heard night and day. The airport was
 * built years ago, but for some reason it couldn't be used then. Last year, however, it came into use.Over a hundred people
 * must have been driven away from their homes by the noise. I am one of the few people left.
 * Sometimes I think this house will be knocked down by a passing plane.  I have been offered a large sum of money
 * to go away, but I am determined to stay here.
 * Everyone says I must be mad and they are probably right.
 *
 *
 * Composition:
 * It was Sunday yesterday. Mike went home late and wanted to have a good sleep. He was very tired.But his neighbour nearly
 * drove him mad.People upstairs had a party.They played music very loudly.The party was not over until three o'clock in
 * the morning.The couple downstairs quarrelled again.Mr.Smith's car next door cried all night. What a bad night! Mike
 * couldn't fall asleep at all.
 *
 *
 *
 * Lesson 22 A glass envelope
 * First listen and then answer the question
 * How did Jane receive a letter from a stranger?
 * My daughter, Jane, never dreamed of receiving a letter from a girl of her own age in Holland. Last year, we were travelling
 * across the Channel, and Jane put a piece of paper with her name and address on it into a bottle. She threw the bottle into
 * the sea.She never thought of it again, but ten months later, she received a letter from a girl in Holland.
 * Both girls write each other regularly now. However, they have decided to use the post office. Letters will cost a little
 * more, but they will certainly travel faster.
 *
 *
 * Composition:
 * Dear Tom,
 *      I am glad to be your pen friend. Now I'd like to introduce myself to you. I'm Li Ming.I am a boy of thirteen years
 * old from Beijing.There are three people in my family, my father, my mother and I. My father is a driver while my mother
 * is a teacher.Now I'm studying in the NO.4 Middle school. There are five subjects in my class.They are Chinese, Maths,
 * English, Physics and Chemistry.My favourite subject is English.And I like playing basketball after school.I often play
 * basketball with my classmates.What about you? I'm looking forward to hearing from you soon.
 *                                                                                                         Yours,
 *                                                                                                         Li Ming
 *
 *
 *
 * Lesson 23 A new house
 * First listen and then answer the question
 * Why is the new house special?
 * I had a letter from my sister yesterday. She lives in Nigeria.In her letter, she said that she would come to England next year.
 * If she comes, she will get a surprise. We are now living in a beautiful new house in the country. Work on it had begun
 * before my sister left.The house was completed five months ago.In my letter, I told her that she could stay with us.
 * The house has many large rooms and there is a lovely garden.It is very modern house, so it looks strange to some people.
 * It must be the only modern house in the drict.
 *
 *
 * Composition:
 * My new house
 * I always dream of having a new house. Then my parents and I can move into the house.There are three bedrooms, a kitchen,
 * a bathroom and a large sitting room in our house. It is very clean and tidy.Every evening, my father is watching TV in the
 * sitting room while mother is cooking delicious food in the kitchen for us. I can do my homework in my room. After that,
 * I will play with my pet dog.Of course, there is also a garden. On Sunday, my parents and I can plant beautiful flowers in it.
 * We will be very happy in our new house.
 *
 *
 * 2020/1/24
 * Lesson 24 It could be worse
 * First listen and then answer the question
 * Had the writer's money been stolen?
 * I entered the hotel manager's office and sat down.I had just lost fifty pounds and I felt very upset."I left the money
 * in my room" I said, "And it's not there now." The manager was sympathetic, but he could do nothing."Everyone's losing money
 * these days" he said. He started to complain about this wicked world but was interrupted by a knock at the door.A girl
 * came in and put an envelope on his desk. It contained fifty pounds. "I found this outside this gentleman's room" she said.
 * "Well," I said to the manger, "there is still some honesty in this world".
 *
 * Composition:
 * Lily found her ring missing after she had left the hotel.So she called the manager, "I must have left my ring in my room,"
 * Lily said, "Would you help me find it?" "OK, I will call you later." After an hour, the manager called Lily and told her
 * that he had checked the room carefully, but he didn't find the ring.The manager was sympathetic.He sent a small gift to her.
 * A few days later, Lily found the ring in her handbag. She felt so lucky and happy.At the same time, she was so sorry.
 *
 *
 * 2020/1/25
 * Lesson 25 Do the English speak english?
 * First listen and then answer the question
 * Why does the writer not understand the porter?
 * I arrived in London at last. The railway station was big, black and dark. I did not know the way to my hotel, so I asked the porter.
 * I not only spoke English very carefully, but very clearly as well. The porter, however, couldn't not understand me. I repeated my
 * questions several times and at last he understood. He answered me, but he spoke neither slowly nor clearly.
 * "I am a foreigner." I said.Then he spoke slowly, but I couldn't understand him.My teacher never spoke English like that.
 * The porter and I looked each other and smiled. Then he said something and I understood it."You'll soon learn English!" he said.
 * I wonder. In England, each person speaks a different language. The English understand each other, but I don't understand them.
 * Do they speak English?
 *
 * Composition:
 * English is my favourite subject because English is widely used in the world.What's more, I like it because my English teacher is kind
 * and friendly to me. In order to learn English well, I read English aloud every morning and listen to the teacher carefully in class.
 * After class, I often watch English programmes, listen to English songs and keep an English diary every day. In a word, I love English
 * and I will continue to learn it better.
 *
 * 2020/1/26
 * Lesson 26 The best art critics
 * First listen and then answer the question
 * Who is student's best art critic?
 * I am an art student and I paint a lot of pictures. Many people pretend that they understand modern art. They always tell you
 * what a picture is about. Of course, many pictures are not about anything, they are just pretty patterns. We like them in
 * the same way that we like pretty curtain material. I think the young children often appreciate modern pictures better than
 * anyone else.They notice more.My sister is only seven, but she always tells me whether my pictures are good or not.She came into
 * my room yesterday. "what are your doing?" she asked, "I'm hanging this picture on the wall." I answered, "it's a new one, do you like it?"
 * She looked at it critically for a moment. "It's all right" she said, "but isn't is upside down?" I looked at it again. She was right.
 * It was!
 *
 * Composition:
 * Hi, everyone! Here's my plan for the weekend.
 * On Saturday morning, I'm going to watch TV to relax myself after a long week's study. I like watching comedies and cartoons. On Saturday
 * afternoon, I'm going to the bookstore to buy some books. Reading is one of my hobbies.
 * On Sunday, I'm going to visit my grandparents because I miss them very much. I'll helop them do some housework.After I come back, I'll do
 * my homework to get ready for the next week.
 * That's my weekend, like it?
 * Thank you!
 *
 *
 */

namespace _9_5AVL {
struct Node
{
    int data_, height_;
    Node *left_, *right_;

    explicit Node(int x = 0) : data_(x), height_(1), left_(nullptr), right_(nullptr)
    {
    }
};

int getHeight(Node *root) noexcept
{
    return root ? root->height_ : 0;
}

void updateHeight(Node *root)
{
    root->height_ = std::max(getHeight(root->left_), getHeight(root->right_)) + 1;
}

int getBalanceFactor(Node *root) noexcept
{
    return getHeight(root->left_) - getHeight(root->right_);
}


void search(Node *root, int x)
{
    if (root == nullptr)
    {
        printf("search failed\n");
        return;
    }
    if (root->data_ == x)
    {
        printf("%d\n", root->data_);
    }
    else if (x < root->data_)
    {
        search(root->left_, x);
    }
    else search(root->right_, x);
}

void leftRotation(Node *&root)
{
    auto tmp = root->right_;
    root->right_ = tmp->left_;
    tmp->left_ = root;
    updateHeight(root);
    updateHeight(tmp);
    root = tmp;
}

void rightRotation(Node *&root)
{
    auto tmp = root->left_;
    root->left_ = tmp->right_;
    tmp->right_ = root;
    updateHeight(root);
    updateHeight(tmp);
    root = tmp;
}


void insert(Node *&root, int x)
{
    if (root == nullptr)
    {
        root = new Node(x);
        return;
    }
    if (x < root->data_)
    {
        insert(root->left_, x);
        updateHeight(root);
        if (getBalanceFactor(root) == 2)
        {
            if (getBalanceFactor(root->left_) == 1)
            {
                rightRotation(root);
            }
            else if (getBalanceFactor(root->left_) == -1)
            {
                leftRotation(root->left_);
                rightRotation(root);
            }
        }
    }
    else
    {
        insert(root->right_, x);
        updateHeight(root);
        if (getBalanceFactor(root) == -2)
        {
            if (getBalanceFactor(root->right_) == -1)
            {
                leftRotation(root);
            }
            else if (getBalanceFactor(root->right_) == 1)
            {
                rightRotation(root->right_);
                leftRotation(root);
            }
        }
    }
}


void destroy(Node *root)
{
    if (root)
    {
        destroy(root->left_);
        destroy(root->right_);
        delete root;
    }
}

void testingAVL()
{
    Node *root = nullptr;
    for (int i = 0; i < 2048; ++i)
    {
        insert(root, i);
    }
    printf("the tree's height is %d.\n", root->height_);
    destroy(root);
}
}

namespace _9_6UFS {
constexpr int N = 2 << 16;
int father[N];

void init()
{
    for (int i = 0; i < N; ++i)
    {
        father[i] = i;
    }
}

int findFather(int x)
{
    while (x != father[x])
    {
        x = father[x];
    }
    return x;
}


void Union(int x, int y)
{
    auto fX = findFather(x);
    auto fY = findFather(y);
    if (fX != fY)
    {
        father[fX] = fY;
    }
}

/*
 * path compression algorithm
 */
int findFatherWithCompression(int x)
{
    int a = x;
    while (x != father[x])
    {
        x = father[x];
    }
    while (a != father[a])
    {
        auto z = a;
        a = father[a];
        father[z] = x;
    }
    return x;
}

namespace GoodFriend {
constexpr int N = 105;
int father[N];
bool isRoot[N];

int findFather(int x)
{
    int a = x, z;
    while (x != father[x])
    {
        x = father[x];
    }
//    path compression
    while (a != father[a])
    {
        z = a;
        a = father[a];
        father[z] = x;
    }
    return x;
}

void Union(int x, int y)
{
    auto fX = findFather(x);
    auto fY = findFather(y);
    if (fX != fY)
    {
        father[fX] = fY;
    }
}

void init(int n)
{
    for (int i = 1; i <= n; ++i)
    {
        father[i] = i;
        isRoot[i] = false;
    }
}

void entryGoodFriend()
{
    int n, m, a, b;
    scanf("%d%d", &n, &m);
    init(n);
    for (int i = 0; i < m; ++i)
    {
        scanf("%d%d", &a, &b);
        Union(a, b);
    }
    for (int j = 1; j <= n; ++j)
    {
        isRoot[findFather(j)] = true;
    }
    int ans = 0;
    for (int k = 1; k <= n; ++k)
    {
        ans += isRoot[k];
    }
    printf("%d\n", ans);
}
}
}


namespace _9_7Heap {
constexpr int MaxN = 2 << 16;
int Heap[MaxN], Len = 0;

/*
 * Heap[lo, hi]
 */
void adjustDown(int lo, int hi)
{
    int i = lo, j = 2 * i;
    while (j <= hi)
    {
        if (j + 1 <= hi && Heap[j + 1] > Heap[j])
        {
            ++j;
        }
        if (Heap[j] > Heap[i])
        {
            std::swap(Heap[j], Heap[i]);
            i = j;
            j = 2 * i;
        }
        else break;
    }
}

void createHeap()
{
    for (int i = Len / 2; i > 0; --i)
    {
        adjustDown(i, Len);
    }
}

void deleteTop()
{
    Heap[1] = Heap[Len--];
    adjustDown(1, Len);
}

/*
 * Heap[lo, hi]
 */
void adjustUp(int lo, int hi)
{
    int i = hi, j = i / 2;
    while (j >= lo)
    {
        if (Heap[j] < Heap[i])
        {
            std::swap(Heap[j], Heap[i]);
            i = j;
            j = i / 2;
        }
        else break;
    }
}

void insert(int x)
{
    Heap[++Len] = x;
    adjustUp(1, Len);
}

void heapSort()
{
    createHeap();
    for (int i = Len; i > 1; --i)
    {
        std::swap(Heap[1], Heap[i]);
        adjustDown(1, i - 1);
    }
}
}

namespace _9_8Huffman {
namespace codeup_21142 {
std::priority_queue<int, std::vector<int>, std::greater<>> Q;

void entryAddFruit()
{
    int n, x, y;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &x);
        Q.push(x);
    }
    int ans = 0;
    while (Q.size() > 1)
    {
        x = Q.top();
        Q.pop();
        y = Q.top();
        Q.pop();
        Q.push(x + y);
        ans += x + y;
    }
    printf("%d\n", ans);
}
}
}
}

void TestingChapter_9()
{
    using namespace chapter_9_tree;
    testingTraversal();
    pat_a1020::entryLayerTraversal();
    pat_a1053::entryPrintPathOfSumEqualsS();
    pat_a1043::entryIsBinarySearchTree();
    _9_5AVL::testingAVL();
    _9_6UFS::GoodFriend::entryGoodFriend();
    _9_8Huffman::codeup_21142::entryAddFruit();
}

namespace chapter_10_graph {
namespace _10_3GraphTraversal {
namespace AdjacencyMatrix_DFS {
constexpr int MaxV = 1005;
constexpr int INF = 1 << 30;

int G[MaxV][MaxV], n;
bool visit[MaxV];

void dfs(int u, int depth)
{
    visit[u] = true;
    for (int v = 0; v < n; ++v)
    {
        if (!visit[v] && G[u][v] != INF)
        {
            dfs(v, depth + 1);
        }
    }
}

void dfsGraph()
{
    for (int u = 0; u < n; ++u)
    {
        if (!visit[u])
        {
            dfs(u, 1);
        }
    }
}
}

namespace AdjacencyList_DFS {
constexpr int MaxV = 1005;
constexpr int INF = 1 << 30;

std::vector<int> G[MaxV];
int n;
bool visit[MaxV];

void dfs(int u, int depth)
{
    visit[u] = true;
    for (int i = 0; i < G[u].size(); ++i)
    {
        int v = G[u][i];
        if (!visit[u])
        {
            dfs(v, depth + 1);
        }
    }
}

void dfsGraph()
{
    for (int u = 0; u < n; ++u)
    {
        if (!visit[u])
        {
            dfs(u, 1);
        }
    }
}
}
}

namespace pat_a1034 {
constexpr int MaxN = 2010;

std::map<string, int> strToNum;
std::map<int, string> numToStr;
std::map<string, int> gangMap;

int G[MaxN][MaxN], weight[MaxN];
int n, k, numPerson = 0;
bool visit[MaxN];

void dfs(int nowV, int &h, int &num, int &totalValue)
{
    ++num;
    visit[nowV] = true;
    if (weight[nowV] > weight[h])
    {
        h = nowV;
    }
    for (int i = 0; i < numPerson; ++i)
    {
        if (G[nowV][i] > 0)
        {
            totalValue += G[nowV][i];
            G[nowV][i] = G[i][nowV] = 0;
            if (!visit[i])
            {
                dfs(i, h, num, totalValue);
            }
        }
    }
}

void dfsGraph()
{
    for (int i = 0; i < numPerson; ++i)
    {
        if (!visit[i])
        {
            int h = i, num = 0, totalValue = 0;
            dfs(i, h, num, totalValue);
            if (num > 2 && totalValue > k)
            {
                gangMap[numToStr[h]] = num;
            }
        }

    }
}

int doNumber(const string &name)
{
    if (strToNum.find(name) != strToNum.end())
    {
        return strToNum[name];
    }
    else
    {
        strToNum[name] = numPerson;
        numToStr[numPerson] = name;
        return numPerson++;
    }
}

void entryFindGangAndHeaders()
{
    int w;
    string name1, name2;
    cin >> n >> k;
    for (int i = 0; i < n; ++i)
    {
        cin >> name1 >> name2 >> w;
        int id1 = doNumber(name1);
        int id2 = doNumber(name2);
        weight[id1] += w;
        weight[id2] += w;
        G[id1][id2] += w;
        G[id2][id1] += w;
    }
    dfsGraph();
    cout << gangMap.size() << endl;
    for (const auto &itM : gangMap)
    {
        cout << itM.first << " " << itM.second << endl;
    }
}
}

namespace AdjacencyMatrix_BFS {
constexpr int MaxV = 1005;
constexpr int INF = 1 << 30;

int G[MaxV][MaxV], n;
bool inq[MaxV];

void bfs(int u)
{
    std::queue<int> Q;
    Q.push(u);
    inq[u] = true;
    while (!Q.empty())
    {
        auto v = Q.front();
        Q.pop();
        for (int w = 0; w < n; ++w)
        {
            if (!inq[w] && G[v][w] != INF)
            {
                Q.push(w);
                inq[w] = true;
            }
        }
    }
}

void bfsGraph()
{
    for (int u = 0; u < n; ++u)
    {
        if (!inq[u])
        {
            bfs(u);
        }
    }
}
}

namespace AdjacencyList_BFS {
constexpr int MaxV = 1005;

std::vector<int> G[MaxV];
int n;
bool inq[MaxV];

void bfs(int u)
{
    std::queue<int> Q;
    Q.push(u);
    inq[u] = true;
    while (!Q.empty())
    {
        auto h = Q.front();
        Q.pop();
        for (int i = 0; i < G[h].size(); ++i)
        {
            auto w = G[h][i];
            if (!inq[w])
            {
                Q.push(w);
                inq[w] = true;
            }
        }
    }
}

void bfsGraph()
{
    for (int u = 0; u < n; ++u)
    {
        if (!inq[u])
        {
            bfs(u);
        }
    }
}
}

namespace pat_a1076 {
constexpr int MaxV = 1005;
struct Node
{
    int id_, layer_;
};

std::vector<Node> G[MaxV];
bool inq[MaxV];

int bfs(int v, int layer)
{
    int numForward = 0;
    std::queue<Node> Q;
    Q.push({v, 0});
    inq[v] = true;
    while (!Q.empty())
    {
        auto topNode = Q.front();
        Q.pop();
        int u = topNode.id_;
        for (int i = 0; i < G[u].size(); ++i)
        {
            auto nextLayerNode = G[u][i];
            nextLayerNode.layer_ = topNode.layer_ + 1;
            if (!inq[nextLayerNode.id_] && nextLayerNode.layer_ <= layer)
            {
                Q.push(nextLayerNode);
                inq[nextLayerNode.id_] = true;
                ++numForward;
            }
        }
    }
    return numForward;
}

void entryCountingNumOfForward()
{
    Node user;
    int n, layer, numFollow, idFollow;
    scanf("%d%d", &n, &layer);
    for (int i = 1; i <= n; ++i)
    {
        user.id_ = i;
        scanf("%d", &numFollow);
        for (int j = 0; j < numFollow; ++j)
        {
            scanf("%d", &idFollow);
            G[idFollow].push_back(user);
        }
    }

    int numQuery, s;
    scanf("%d", &numQuery);
    for (int k = 0; k < numQuery; ++k)
    {
        std::memset(inq, false, sizeof(inq));
        scanf("%d", &s);
        auto numForward = bfs(s, layer);
        printf("%d\n", numForward);
    }
}
}


namespace _10_4ShortestPath {
namespace Dijkstra_AdjMatrix {
constexpr int MaxV = 1000;
constexpr int INF = 0x3ffffff;

int G[MaxV][MaxV], n;
int d[MaxV];
bool visit[MaxV];

void dijkstra(int s)
{
    std::fill(d, d + MaxV, INF);
    d[s] = 0;
    for (int i = 0; i < n; ++i)
    {
        int u = -1, min = INF;
        for (int j = 0; j < n; ++j)
        {
            if (!visit[j] && d[j] < min)
            {
                u = j;
                min = d[j];
            }
        }
        if (u == -1) return;
        visit[u] = true;
        for (int v = 0; v < n; ++v)
        {
            if (!visit[v] && G[u][v] != INF && d[u] + G[u][v] < d[v])
            {
                d[v] = d[u] + G[u][v];
            }
        }
    }
}
}

namespace Dijkstra_AdjList {
constexpr int MaxV = 1005;
constexpr int INF = 0x3ffffff;
struct Node
{
    int v_, dis_;
};

std::vector<Node> G[MaxV];
int d[MaxV], n;
bool visit[MaxV];

void dijkstra(int s)
{
    std::fill(d, d + MaxV, INF);
    d[s] = 0;
    for (int i = 0; i < n; ++i)
    {
        int u = -1, min = INF;
        for (int j = 0; j < n; ++j)
        {
            if (!visit[j] && d[j] < min)
            {
                u = j;
                min = d[j];
            }
        }
        if (u == -1) return;
        visit[u] = true;
        for (int j = 0; j < G[u].size(); ++j)
        {
            int v = G[u][j].v_;
            if (!visit[v] && d[u] + G[u][j].dis_ < d[v])
            {
                d[v] = d[u] + G[u][j].dis_;
            }
        }
    }
}
}

namespace pat_a1003 {
constexpr int MaxV = 505;
constexpr int INF = 0x3ffffff;

int G[MaxV][MaxV], d[MaxV], weight[MaxV], w[MaxV], num[MaxV];
bool visit[MaxV];

void dijkstra(int s, int n)
{
    std::fill(d, d + MaxV, INF);
    d[s] = 0;
    w[s] = weight[s];
    num[s] = 1;
    for (int i = 0; i < n; ++i)
    {
        int u = -1, min = INF;
        for (int j = 0; j < n; ++j)
        {
            if (!visit[j] && d[j] < min)
            {
                u = j;
                min = d[j];
            }
        }
        if (u == -1) return;
        visit[u] = true;
        for (int v = 0; v < n; ++v)
        {
            if (!visit[v] && G[u][v] != INF)
            {
                if (d[u] + G[u][v] < d[v])
                {
                    d[v] = d[u] + G[u][v];
                    num[v] = num[u];
                    w[v] = w[u] + weight[v];
                }
                else if (d[u] + G[u][v] == d[v])
                {
                    if (w[u] + weight[v] > w[v])
                    {
                        w[v] = w[u] + weight[v];
                    }
                    num[v] += num[u];
                }
            }
        }
    }
}

void entryEmergency()
{
    int n, m, s, e;
    scanf("%d%d%d%d", &n, &m, &s, &e);
    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &weight[i]);
    }
    std::fill(G[0], G[0] + MaxV * MaxV, INF);
    int u, v;
    for (int j = 0; j < m; ++j)
    {
        scanf("%d%d", &u, &v);
        scanf("%d", &G[u][v]);
        G[v][u] = G[u][v];
    }
    dijkstra(s, n);
    printf("%d %d\n", num[e], w[e]);
}
}

namespace pat_a1003_bellman {
constexpr int MaxV = 510;
constexpr int INF = 0x3ffffff;

struct Node
{
    int v_, dis_;
};
std::vector<Node> G[MaxV];
int d[MaxV], w[MaxV], num[MaxV], weight[MaxV];
std::set<int> pre[MaxV];

void bellman(int s, int n)
{
    std::fill(d, d + MaxV, INF);
    d[s] = 0;
    w[s] = weight[s];
    num[s] = 1;
    for (int i = 0; i < n - 1; ++i)
    {
        for (int u = 0; u < n; ++u)
        {
            for (int j = 0; j < G[u].size(); ++j)
            {
                int v = G[u][j].v_;
                int dis = G[u][j].dis_;
                if (d[u] + dis < d[v])
                {
                    d[v] = d[u] + dis;
                    w[v] = w[u] + weight[v];
                    num[v] = num[u];
                    pre[v].clear();
                    pre[v].insert(u);
                }
                else if (d[u] + dis == d[v])
                {
                    if (w[u] + weight[v] > w[v])
                    {
                        w[v] = w[u] + weight[v];
                    }
                    pre[v].insert(u);
                    num[v] = 0;
                    for (const auto &item : pre[v])
                    {
                        num[v] += num[item];
                    }
                }
            }
        }
    }
}

void entryEmergency()
{
    int n, m, s, e;
    scanf("%d%d%d%d", &n, &m, &s, &e);
    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &weight[i]);
    }
    int u, v, wt;
    for (int j = 0; j < m; ++j)
    {
        scanf("%d%d%d", &u, &v, &wt);
        G[u].push_back({v, wt});
        G[v].push_back({u, wt});
    }
    bellman(s, n);
    printf("%d %d\n", num[e], w[e]);
}
}

namespace pat_a1030 {
constexpr int MaxV = 505;
constexpr int INF = 0x3ffffff;

int G[MaxV][MaxV], cost[MaxV][MaxV];
int d[MaxV], c[MaxV], pre[MaxV];
bool visit[MaxV];

void dijkstra(int s, int n)
{
    std::fill(d, d + MaxV, INF);
    std::fill(c, c + MaxV, INF);
    for (int i = 0; i < n; ++i)
    {
        pre[i] = i;
    }
    d[s] = 0;
    c[s] = 0;
    for (int i = 0; i < n; ++i)
    {
        int u = -1, min = INF;
        for (int j = 0; j < n; ++j)
        {
            if (!visit[j] && d[j] < min)
            {
                u = j;
                min = d[j];
            }
        }
        if (u == -1) return;
        visit[u] = true;
        for (int v = 0; v < n; ++v)
        {
            if (!visit[v] && G[u][v] != INF)
            {
                if (d[u] + G[u][v] < d[v])
                {
                    d[v] = d[u] + G[u][v];
                    c[v] = c[u] + cost[u][v];
                    pre[v] = u;
                }
                else if (d[u] + G[u][v] == d[v])
                {
                    if (c[u] + cost[u][v] < c[v])
                    {
                        c[v] = c[u] + cost[u][v];
                        pre[v] = u;
                    }
                }
            }
        }
    }
}

void dfsPrintPre(int v, int s)
{
    if (v == s)
    {
        printf("%d ", v);
        return;
    }
    dfsPrintPre(pre[v], s);
    printf("%d ", v);
}

void entryTravelPlan()
{
    std::fill(G[0], G[0] + MaxV * MaxV, INF);
    int n, m, s, e;
    scanf("%d%d%d%d", &n, &m, &s, &e);
    int u, v;
    for (int i = 0; i < m; ++i)
    {
        scanf("%d%d", &u, &v);
        scanf("%d%d", &G[u][v], &cost[u][v]);
        G[v][u] = G[u][v];
        cost[v][u] = cost[u][v];
    }
    dijkstra(s, n);
    dfsPrintPre(e, s);
    printf("%d %d", d[e], c[e]);
}
}

namespace BellmanFord {
constexpr int MaxV = 1005;
constexpr int INF = 0x3ffffff;

struct Node
{
    int v_, dis_;
};

std::vector<Node> G[MaxV];
int d[MaxV], n;

bool bellman(int s)
{
    std::fill(d, d + MaxV, INF);
    d[s] = 0;
    for (int i = 0; i < n - 1; ++i)
    {
        for (int u = 0; u < n; ++u)
        {
            for (int j = 0; j < G[u].size(); ++j)
            {
                int v = G[u][j].v_;
                int dis = G[u][j].dis_;
                if (d[u] + dis < d[v])
                {
                    d[v] = d[u] + dis;
                }
            }
        }
    }
    for (int u = 0; u < n; ++u)
    {
        for (int j = 0; j < G[u].size(); ++j)
        {
            int v = G[u][j].v_;
            int dis = G[u][j].dis_;
            if (d[u] + dis < d[v])
            {
                return false;
            }
        }
    }
    return true;
}
}

namespace SPFA {
constexpr int MaxV = 1005;
constexpr int INF = 0x3ffffff;

struct Node
{
    int v_, dis_;
};

std::vector<Node> G[MaxV];
int d[MaxV], num[MaxV], n;
bool inq[MaxV];

bool spfa(int s)
{
    std::fill(d, d + MaxV, INF);
    std::queue<int> Q;
    Q.push(s);
    inq[s] = true;
    ++num[s];
    d[s] = 0;
    while (!Q.empty())
    {
        int u = Q.front();
        Q.pop();
        inq[u] = false;
        for (int j = 0; j < G[u].size(); ++j)
        {
            int v = G[u][j].v_;
            int dis = G[u][j].dis_;
            if (d[u] + dis < d[v])
            {
                d[v] = d[u] + dis;
                if (!inq[v])
                {
                    Q.push(v);
                    inq[v] = true;
                    ++num[v];
                    if (num[v] >= n) return false;
                }
            }
        }
    }
    return true;
}
}

namespace Floyd {
constexpr int INF = 0x3ffffff;
constexpr int MaxV = 205;

int dist[MaxV][MaxV], n, m;

void floyd()
{
    for (int k = 0; k < n; ++k)
    {
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (dist[i][k] != INF && dist[k][j] != INF && dist[i][k] + dist[k][j] < dist[i][j])
                {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
}

void entry()
{
    std::fill(dist[0], dist[0] + MaxV * MaxV, INF);
    int u, v, w;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++i)
    {
        dist[i][i] = 0;
    }
    for (int i = 0; i < m; ++i)
    {
        scanf("%d%d%d", &u, &v, &w);
        dist[u][v] = w;
    }
    floyd();
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            printf("%d ", dist[i][j]);
        }
        printf("\n");
    }
}
}
}

namespace _10_5MST {
constexpr int MaxV = 1000;
constexpr int INF = 0x3ffffff;

namespace AdjMatrix_Prim {
int G[MaxV][MaxV], n;
int d[MaxV];
bool visit[MaxV];

int prim()
{
    std::fill(d, d + MaxV, INF);
    d[0] = 0;
    int ans = 0;
    for (int i = 0; i < n; ++i)
    {
        int u = -1, min = INF;
        for (int j = 0; j < n; ++j)
        {
            if (!visit[j] && d[j] < min)
            {
                u = j;
                min = d[j];
            }
        }
        if (u == -1) return -1;
        visit[u] = true;
        ans += d[u];
        for (int v = 0; v < n; ++v)
        {
            if (!visit[v] && G[u][v] != INF && G[u][v] < d[v])
            {
                d[v] = G[u][v];
            }
        }
    }
    return ans;
}
}

namespace AdjList_Prim {
struct Node
{
    int v_, dis_;
};
std::vector<Node> G[MaxV];
int d[MaxV], n;
bool visit[MaxV];

int prim()
{
    std::fill(d, d + MaxV, INF);
    d[0] = 0;
    int ans = 0;
    for (int i = 0; i < n; ++i)
    {
        int u = -1, min = INF;
        for (int j = 0; j < n; ++j)
        {
            if (!visit[j] && d[j] < min)
            {
                u = j;
                min = d[j];
            }
        }
        if (u == -1) return -1;
        visit[u] = true;
        ans += d[u];
        for (int j = 0; j < G[u].size(); ++j)
        {
            int v = G[u][j].v_;
            if (!visit[v] && G[u][j].dis_ < d[v])
            {
                d[v] = G[u][j].dis_;
            }
        }
    }
    return ans;
}
}

namespace Exercise_Prim {
int G[MaxV][MaxV], d[MaxV];
bool visit[MaxV];

int prim(int n)
{
    std::fill(d, d + MaxV, INF);
    d[0] = 0;
    int ans = 0;
    for (int i = 0; i < n; ++i)
    {
        int u = -1, min = INF;
        for (int j = 0; j < n; ++j)
        {
            if (!visit[j] && d[j] < min)
            {
                u = j;
                min = d[j];
            }
        }
        if (u == -1) return -1;
        visit[u] = true;
        ans += d[u];
        for (int v = 0; v < n; ++v)
        {
            if (!visit[v] && G[u][v] != INF && G[u][v] < d[v])
            {
                d[v] = G[u][v];
            }
        }
    }
    return ans;
}

void entryExercise()
{
    int n, m, u, v, w;
    scanf("%d%d", &n, &m);
    std::fill(G[0], G[0] + MaxV * MaxV, INF);
    for (int i = 0; i < m; ++i)
    {
        scanf("%d%d%d", &u, &v, &w);
        G[u][v] = G[v][u] = w;
    }
    auto ans = prim(n);
    printf("%d\n", ans);
}
}

namespace Kruskal_Alg {
constexpr int MaxV = 110;
constexpr int MaxE = 10010;
struct Edge
{
    int u_, v_, eWeight_;
};

Edge edges[MaxE];

bool operator<(const Edge &lhs, const Edge &rhs) noexcept
{
    return lhs.eWeight_ < rhs.eWeight_;
}

int father[MaxV];

int findFather(int x)
{
    int a = x;
    while (x != father[x])
    {
        x = father[x];
    }
    while (a != father[a])
    {
        auto z = a;
        a = father[a];
        father[z] = x;
    }
    return x;
}

int kruskal(int n, int m)
{
    int ans = 0, numE = 0;
    for (int i = 0; i < n; ++i)
    {
        father[i] = i;
    }
    std::sort(edges, edges + m);
    for (int j = 0; j < m; ++j)
    {
        int faU = findFather(edges[j].u_);
        int faV = findFather(edges[j].v_);
        if (faU != faV)
        {
            father[faU] = faV;
            ans += edges[j].eWeight_;
            ++numE;
            if (numE == n - 1) break;
        }
    }
    if (numE != n - 1) return -1;
    return ans;
}

void entryKruskal()
{
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; ++i)
    {
        scanf("%d%d%d", &edges[i].u_, &edges[i].v_, &edges[i].eWeight_);
    }
    int ans = kruskal(n, m);
    printf("%d\n", ans);
}
}
}

namespace _10_6TopologicalSort {
constexpr int MaxV = 1005;

std::vector<int> G[MaxV];
int n, m, inDegree[MaxV];

bool topologicalSort()
{
    int num = 0;
    std::queue<int> Q;
    for (int i = 0; i < n; ++i)
    {
        if (inDegree[i] == 0)
        {
            Q.push(i);
        }
    }
    while (!Q.empty())
    {
        int u = Q.front();
        Q.pop();
        for (int j = 0; j < G[u].size(); ++j)
        {
            int v = G[u][j];
            --inDegree[v];
            if (inDegree[v] == 0)
            {
                Q.push(v);
            }
        }
        G[u].clear();
        ++num;
    }
    return num == n;
}
}

namespace _10_7AOV_AOE {}
}

void TestingChapter_10()
{
    using namespace chapter_10_graph;
    pat_a1034::entryFindGangAndHeaders();
    pat_a1076::entryCountingNumOfForward();
    _10_4ShortestPath::pat_a1003::entryEmergency();
    _10_4ShortestPath::pat_a1003_bellman::entryEmergency();
    _10_4ShortestPath::pat_a1030::entryTravelPlan();
    _10_4ShortestPath::Floyd::entry();
    _10_5MST::Exercise_Prim::entryExercise();
    _10_5MST::Kruskal_Alg::entryKruskal();
}

namespace chapter_11_dynamic_programming {
namespace Fibonacci {
constexpr int N = 1005;
int dp[N];

int F(int n)
{
    if (n == 0 || n == 1) return 1;
    if (dp[n]) return dp[n];
    else
    {
        dp[n] = F(n - 1) + F(n - 2);
        return dp[n];
    }
}

void entryFibonacci()
{
    auto ans = F(47);
    printf("%d\n", ans);
}
}

namespace CountingTower {
constexpr int N = 1000;
int nt[N][N], dp[N][N];

void entryCountingTower()
{
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= i; ++j)
        {
            scanf("%d", &nt[i][j]);
        }
    }
    for (int k = 0; k <= n; ++k)
    {
        dp[n][k] = nt[n][k];
    }
    for (int i = n - 1; i >= 1; --i)
    {
        for (int j = 1; j <= i; ++j)
        {
            dp[i][j] = std::max(dp[i + 1][j], dp[i + 1][j + 1]) + nt[i][j];
        }
    }
    printf("%d\n", dp[1][1]);
}
}

namespace MCS {
/*
 * sum of maximum continuous subsequence
 */
constexpr int N = 100'005;
int A[N], dp[N];

void entry()
{
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &A[i]);
    }
    dp[0] = A[0];
    for (int i = 1; i < n; ++i)
    {
        dp[i] = std::max(A[i], dp[i - 1] + A[i]);
    }
    int k = 0;
    for (int j = 1; j < n; ++j)
    {
        if (dp[j] > dp[k])
        {
            k = j;
        }
    }
    printf("%d\n", dp[k]);
}
}

namespace LIS {
constexpr int N = 105;
int A[N], dp[N];

void entry()
{
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &A[i]);
    }
    int ans = -1;
    for (int i = 1; i <= n; ++i)
    {
        dp[i] = 1;
        for (int j = 1; j < i; ++j)
        {
            if (A[i] > A[j] && dp[j] + 1 > dp[i])
            {
                dp[i] = dp[j] + 1;
            }
        }
        ans = std::max(ans, dp[i]);
    }
    printf("%d\n", ans);
}
}

namespace LCS {
constexpr int N = 1005;
char A[N], B[N];
int dp[N][N];

void entry()
{
    getLine(A + 1, N);
    getLine(B + 1, N);
    int lenA = strlen(A + 1), lenB = strlen(B + 1);
    for (int i = 0; i <= lenA; ++i)
    {
        dp[i][0] = 0;
    }
    for (int j = 0; j <= lenB; ++j)
    {
        dp[0][j] = 0;
    }
    for (int i = 1; i <= lenA; ++i)
    {
        for (int j = 1; j <= lenB; ++j)
        {
            if (A[i] == B[j])
            {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            }
            else
            {
                dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    printf("%d\n", dp[lenA][lenB]);
}
}

/*
 * 2020/1/27
 * Lesson 27 A wet night
 * First listen and then answer the question
 * What happened to boys in the night?
 * Late in the afternoon, the boys put up their tent in the middle of a field.As soon as this was done, they cooked a meal
 * over an open fire.They were all hungry and food smelled good. After a wonderful meal they told stories and sang songs by
 * the campfire.But some time later it began to rain.The boys felt tired and they put out the fire and crept into their tent.
 * Their sleeping bags were warm and comfortable, so they all slept soundly. In the middle of the night, two boys woke up and began
 * shouting. The tent was full of water.They all leapt out of their sleeping bags and hurried outside. It was raining heavily and
 * they found that a stream had formed in the field. The stream wound its way across the field and then flowed right under their tent.
 *
 * Composition:
 * Once a young man was travelling on a train. He was causing a lot of trouble to the passengers around him. At last he
 * got out at a station with his two heavy bags. No one helped him. When he was quite far away from the train, one of the other
 * passengers opened the window and shouted to him, "You left something behind on the train." Then he closed the window.
 * The young man turned back to the train with his two bags, very tired. "What did I leave behind?" he shouted through the
 * window.
 * As the train began to move again. the passenger who had called him back opened the window again and said, "A very bad impression."
 *
 *
 *
 */

namespace LPS {
/*
 * Longest palindrome substring
 */
constexpr int N = 1005;
char S[N];
int dp[N][N];

void entry()
{
    getLine(S, N);
    int len = strlen(S), ans = 1;
//    boundary
    for (int i = 0; i < len; ++i)
    {
        dp[i][i] = 1;
        if (i < len - 1)
        {
            if (S[i] == S[i + 1])
            {
                dp[i][i + 1] = 1;
                ans = 2;
            }
        }
    }
//    state transition equation
    for (int L = 3; L <= len; ++L)
    {
        for (int i = 0; i + L - 1 < len; ++i)
        {
            int j = i + L - 1;
            if (S[i] == S[j] && dp[i + 1][j - 1] == 1)
            {
                dp[i][j] = 1;
                ans = L;
            }
        }
    }
    printf("%d\n", ans);
}
}

namespace DAG {
constexpr int INF = 0x3ffffff;
constexpr int MaxN = 1005;

int G[MaxN][MaxN], dp[MaxN], n;

int calcDp(int i)
{
    if (dp[i] > 0) return dp[i];
    for (int j = 0; j < n; ++j)
    {
        if (G[i][j] != INF)
        {
            dp[i] = std::max(dp[i], calcDp(j) + G[i][j]);
        }
    }
    return dp[i];
}

int calcDp(int i, std::vector<int> choice[], int num[])
{
    if (dp[i] > 0) return dp[i];
    for (int j = 0; j < n; ++j)
    {
        if (G[i][j] != INF)
        {
            int tmp = calcDp(j, choice, num) + G[i][j];
            if (tmp > dp[i])
            {
                dp[i] = tmp;
                choice[i].clear();
                choice[i].push_back(j);
                num[j] = num[i];
            }
            else if (tmp == dp[i])
            {
                choice[i].push_back(j);
                num[j] += num[i];
            }
        }
    }
    return dp[i];
}

int calcDp(int i, bool visit[])
{
    if (visit[i]) return dp[i];
    visit[i] = true;
    for (int j = 0; j < n; ++j)
    {
        if (G[i][j] != INF)
        {
            dp[i] = std::max(dp[i], calcDp(j, visit) + G[i][j]);
        }
    }
    return dp[i];
}
}

namespace BackpackProblem {
constexpr int MaxN = 100;
constexpr int MaxV = 1005;

int w[MaxN], c[MaxN], dp[MaxV];

void entry()
{
    int n, V;
    scanf("%d%d", &n, &V);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &w[i]);
    }
    for (int j = 1; j <= n; ++j)
    {
        scanf("%d", &c[j]);
    }
//    boundary
    for (int v = 0; v <= V; ++v)
    {
        dp[v] = 0;
    }
    for (int i = 1; i <= n; ++i)
    {
        for (int v = V; v >= w[i]; --v)
        {
            dp[v] = std::max(dp[v], dp[v - w[i]] + c[i]);
        }
    }
    int max = 0;
    for (int v = 0; v <= V; ++v)
    {
        if (dp[v] > max)
        {
            max = dp[v];
        }
    }
    printf("%d\n", max);
}
}
}

namespace chapter_12_string {
constexpr int Mod = 1'000'000'007;
constexpr int P = 10'000'019;

namespace _12_1Hash {
int hashCode(string s) noexcept
{
    int h = 0;
    for (int i = 0; i < s.size(); ++i)
    {
        h = (h * P + s[i] - 'a') % Mod;
    }
    return h;
}
}

namespace _12_2KMP {
int *getNext(char pattern[], int len)
{
    int *next = new int[len];
    int j = next[0] = -1;
    for (int i = 1; i < len; ++i)
    {
        while (j != -1 && pattern[i] != pattern[j + 1])
        {
            j = next[j];
        }
        if (pattern[i] == pattern[j + 1])
        {
            ++j;
        }
        next[i] = j;
    }
    return next;
}

bool kmpAlg(char text[], char pattern[])
{
    int n = strlen(text), m = strlen(pattern);
    auto next = getNext(pattern, m);
    int j = -1;
    for (int i = 0; i < n; ++i)
    {
        while (j != -1 && text[i] != pattern[j + 1])
        {
            j = next[j];
        }
        if (text[i] == pattern[j + 1])
        {
            ++j;
        }
        if (j == m - 1) return true;
    }
    delete[] next;
    return false;
}

int kmpCountingTimes(char text[], char pattern[])
{
    int n = std::strlen(text), m = std::strlen(pattern);
    auto next = getNext(pattern, m);
    int j = -1, ans = 0;
    for (int i = 0; i < n; ++i)
    {
        while (j != -1 && text[i] != pattern[j + 1])
        {
            j = next[j];
        }
        if (text[i] == pattern[j + 1])
        {
            ++j;
        }
        if (j == m - 1)
        {
            ++ans;
            j = next[j];
        }
    }
    delete[] next;
    return ans;
}

int *getNextval(const char s[], int len)
{
    auto next = new int[len];
    int j = next[0] = -1;
    for (int i = 1; i < len; ++i)
    {
        while (j != -1 && s[i] != s[j + 1])
        {
            j = next[j];
        }
        if (s[i] == s[j + 1])
        {
            ++j;
        }
        if (j == -1 || s[i + 1] != s[j + 1])
        {
            next[i] = j;
        }
        else
        {
            next[i] = next[j];
        }
    }
    return next;
}
}
}

namespace chapter_13_special_topic {
namespace _13_1Block {
namespace pat_a1057 {
constexpr int N = 100'010;
constexpr int NB = 316, NT = 317;


std::stack<int> S;
int block[NB], table[N];

void peekMedian(int k)
{
    int sum = 0;
    int idx = 0;
    while (sum + block[idx] < k)
    {
        sum += block[idx++];
    }
    int num = idx * NB;
    while (sum + table[num] < k)
    {
        sum += table[num++];
    }
    printf("%d\n", num);
}

void push(int x)
{
    S.push(x);
    ++block[x / NB];
    ++table[x];
}

void pop()
{
    int x = S.top();
    S.pop();
    --block[x / NB];
    --table[x];
    printf("%d\n", x);
}

void entry()
{
    int x, query;
    char cmd[20];
    scanf("%d", &query);
    for (int i = 0; i < query; ++i)
    {
        scanf("%s", cmd);
        if (std::strcmp(cmd, "Push") == 0)
        {
            scanf("%d", &x);
            push(x);
        }
        else if (std::strcmp(cmd, "Pop") == 0)
        {
            if (S.empty()) printf("Invalid\n");
            else pop();
        }
        else
        {
            if (S.empty()) printf("Invalid\n");
            else
            {
                int k = S.size();
                if (k % 2) k = (k + 1) / 2;
                else k = k / 2;
                peekMedian(k);
            }
        }
    }
}
}
}

namespace _13_2BIT {

constexpr inline int lowBit(int x) noexcept
{
    return x & (-x);
}

void testingLowBit()
{
    for (int i = 0; i < 100; ++i)
    {
        printf("%d ", lowBit(i));
    }
    printf("\n");
}

int getSum(int x, int *c)
{
    int sum = 0;
    for (int i = x; i > 0; i -= lowBit(i))
    {
        sum += c[i];
    }
    return sum;
}

void update(int x, int v, int *c, int n)
{
    for (int i = 0; i <= n; i += lowBit(i))
    {
        c[i] += v;
    }
}

namespace apply_1 {
constexpr int MaxN = 100'010;
int c[MaxN];

constexpr inline int lowbit(int x) noexcept
{
    return x & (-x);
}


void update(int x, int v, int n)
{
    for (int i = x; i <= n; i += lowbit(x))
    {
        c[i] += v;
    }
}

int getSum(int x)
{
    int sum = 0;
    for (int i = x; i > 0; i -= lowbit(i))
    {
        sum += c[i];
    }
    return sum;
}

void entry()
{
    int x, n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &x);
        update(x, 1, n);
        printf("%d\n", getSum(x - 1));
    }
}
}

namespace apply_2 {
constexpr int MaxN = 100'010;
struct Node
{
    int val_, pos_;
};

bool operator<(const Node &lhs, const Node &rhs) noexcept
{
    return lhs.val_ < rhs.val_;
}

Node tmp[MaxN];
int A[MaxN], c[MaxN];

constexpr inline int lowbit(int x) noexcept
{
    return x & (-x);
}

void update(int x, int v, int n)
{
    for (int i = x; i <= n; i += lowbit(i))
    {
        c[i] += v;
    }
}

int getSum(int x)
{
    int sum = 0;
    for (int i = x; i > 0; i -= lowbit(x))
    {
        sum += c[i];
    }
    return sum;
}

void entry()
{
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &tmp[i].val_);
        tmp[i].pos_ = i;
    }
    std::sort(tmp, tmp + n);
    for (int i = 0; i < n; ++i)
    {
        if (i == 0 || tmp[i].val_ != tmp[i - 1].val_)
        {
            A[tmp[i].pos_] = i + 1;
        }
        else
        {
            A[tmp[i].pos_] = A[tmp[i - 1].pos_];
        }
    }
    for (int i = 0; i < n; ++i)
    {
        update(A[i], 1, n);
        printf("%d\n", getSum(A[i] - 1));
    }
}

int findKthElement(int K)
{
    int lo = 1, hi = MaxN, mid;
    while (lo < hi)
    {
        mid = (lo + hi) / 2;
        getSum(mid) >= K ? hi = mid : lo = mid + 1;
    }
    return lo;
}
}
}
}

void TestingChapter_11_12_13()
{
    using namespace chapter_11_dynamic_programming;
    using namespace chapter_12_string;
    using namespace chapter_13_special_topic;
    Fibonacci::entryFibonacci();
    CountingTower::entryCountingTower();
    MCS::entry();
    LIS::entry();
    LCS::entry();
    LPS::entry();
    BackpackProblem::entry();
    _13_1Block::pat_a1057::entry();
    _13_2BIT::testingLowBit();
    _13_2BIT::apply_1::entry();
    _13_2BIT::apply_2::entry();
}

int main(int argc, char *argv[])
{
    TestingChapter_3();
    TestingChapter_4();
    TestingChapter_5();
    TestingChapter_7();
    TestingChapter_8();
    TestingChapter_9();
    TestingChapter_10();
    TestingChapter_11_12_13();
    return 0;
}
