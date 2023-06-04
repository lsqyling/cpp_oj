//
// Created by shiqing on 2021/4/12.
//
#include <cstdio>
#include <cstring>
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <stack>

using std::string;
using std::cin;

namespace string_topic {
constexpr int kPrime = 1000'0019;
constexpr int kMod = 1'0000'0000'7;

/*
 * Q: Given N strings with only lowercase letters, find the number of different strings.
 */
namespace question_1 {

long HashCode(const std::string &s)
{
    long h = 0;
    for (int i = 0; i < s.size(); ++i)
    {
        h = (h * kPrime + s[i] - 'a') % kMod;
    }
    return h;
}

void Entry()
{
    std::vector<long> ans;
    std::string s;
    while (getline(std::cin, s), s != "#")
    {
        long id = HashCode(s);
        ans.push_back(id);
    }
    std::sort(ans.begin(), ans.end());
    int cnt = 0;
    for (int i = 0; i < ans.size(); ++i)
    {
        if (i == 0 || ans[i] != ans[i - 1])
        {
            ++cnt;
        }
    }
    printf("%d", cnt);
}
}
/*
 * Q: Enter two strings with a length not exceeding 1000,
 * and find the length of their longest common string.
 */


namespace kmp {
constexpr int kL = 256;

int next[kL], next_val[kL];

void GetNext(const char s[], int len)
{
    int j = next[0] = -1;
    for (int i = 1; i < len; ++i)
    {
        while (j != -1 && s[i] != s[j + 1])
        {
            j = next[j];
        }
        if (s[i] == s[j + 1]) ++j;
        next[i] = j;
    }
}

void GetNextVal(const char s[], int len)
{
    int j = next_val[0] = -1;
    for (int i = 0; i < len; ++i)
    {
        while (j != -1 && s[i] != s[j + 1])
        {
            j = next_val[j];
        }
        if (s[i] == s[j + 1]) ++j;
        if (j == -1 || s[i + 1] != s[j + 1])
        {
            next_val[i] = j;
        }
        else
        {
            next_val[i] = next_val[j];
        }
    }
}

bool MatchOfKmp(const char text[], const char pattern[])
{
    int n = strlen(text), m = strlen(pattern);
    GetNext(pattern, m);
    int j = -1;
    for (int i = 0; i < n; ++i)
    {
        while (j != -1 && text[i] != pattern[j + 1])
        {
            j = next[j];
        }
        if (text[i] == pattern[j + 1]) ++j;
        if (j == m - 1) return true;
    }
    return false;
}

int MatchOfKmpAndCounting(const char text[], const char pattern[])
{
    int n = strlen(text), m = strlen(pattern);
    GetNext(pattern, m);
    int count = 0, j = -1;
    for (int i = 0; i < n; ++i)
    {
        while (j != -1 && text[i] != pattern[j + 1])
        {
            j = next[j];
        }
        if (text[i] == pattern[j + 1]) ++j;
        if (j == m - 1)
        {
            ++count;
            j = next[j];
        }
    }
    return count;
}
}
}

namespace pat_a1057 {
constexpr int kBlockN = 316;
constexpr int kN = 10'0010;

std::stack<int> S;
int block[kN], table[kN];

void PeekMedian(int k)
{
    int cnt = 0, idx = 0;
    while (cnt + block[idx] < k)
    {
        cnt += block[idx];
        ++idx;
    }
    int num = idx * kBlockN;
    while (cnt + table[num] < k)
    {
        cnt += table[num++];
    }
    printf("%d\n", num);
}

void Push(int x)
{
    S.push(x);
    block[x / kBlockN]++;
    table[x]++;
}

void Pop()
{
    int x = S.top();
    S.pop();
    --block[x / kBlockN];
    --table[x];
    printf("%d\n", x);
}

void Entry()
{
    int x, query;
    std::memset(block, 0, sizeof(block));
    std::memset(table, 0, sizeof(table));
    char cmd[20];
    scanf("%d", &query);
    for (int i = 0; i < query; ++i)
    {
        scanf("%s", cmd);
        if (std::strcmp(cmd, "Push") == 0)
        {
            scanf("%d", &x);
            Push(x);
        }
        else if (std::strcmp(cmd, "Pop") == 0)
        {
            if (S.empty())
            {
                printf("Invalid\n");
            }
            else
            {
                Pop();
            }
        }
        else
        {
            if (S.empty())
            {
                printf("Invalid\n");
            }
            else
            {
                int K = S.size();
                if (K % 2 == 1) K = (K + 1) / 2;
                else K /= 2;
                PeekMedian(K);
            }
        }
    }
}
}
/*
 * Q: Given a sequence A with N integers (N<= 10^5,A[i] <= 10^5),
 * for each number in the sequence, find the number on the left side of
 * the sequence that is smaller than it The number of.
 */
namespace tree_array {
constexpr int kN = 10'0010;

int c[kN];

inline int Lowbit(int x)
{
    return x & -x;
}

void Update(int x, int v)
{
    for (int i = x; i < kN; i += Lowbit(i))
    {
        c[i] += v;
    }
}

int GetSum(int x)
{
    int sum = 0;
    for (int i = x; i > 0; i -= Lowbit(i))
    {
        sum += c[i];
    }
    return sum;
}

void Entry()
{
    int n, x;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &x);
        Update(x, 1);
        printf("%d\n", GetSum(x - 1));
    }
}

int FindKthElement(int k, int n)
{
    int lo = 1, hi = n, mid;
    while (lo < hi)
    {
        mid = (lo + hi) / 2;
        if (GetSum(mid) >= k) hi = mid;
        else lo = mid + 1;
    }
    return lo;
}


}


int main(int argc, char *argv[])
{
    pat_a1057::Entry();
    tree_array::Entry();
    return 0;
}


