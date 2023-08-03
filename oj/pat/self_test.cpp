#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <vector>
#include <algorithm>
#include <istream>

namespace self_1 {

void entry()
{
    int n;
    char c;
    scanf("%d %c", &n, &c);
    int r, m, k;
    k = floor(sqrt((n+1)*1.0/2.0));
    r = n + 1 - 2 * k * k;
    m = 2 * k - 1;

    for (int i = 0; i < m; ++i)
    {
        if (i <= m/2)
            for (int j = 0; j < m; ++j)
            {
                if (i <= j && j < m - i)
                    printf("%c", c);
                else if (j < i)
                    printf(" ");
            }
        else
            for (int j = 0; j < m; ++j)
            {
                if (m-i-1 <= j && j < i+1)
                    printf("%c", c);
                else if (j <m-i-1)
                    printf(" ");
            }
        printf("\n");
    }
    printf("%d\n", r);

}
}

namespace self_2 {

void filter_out(std::vector<int> &ret)
{
    int n;
    scanf("%d", &n);
    bool table[n+1];
    memset(table, true, sizeof(table));
    for (int i = 2; i <= n; ++i)
    {
        if (table[i])
        {
            for (int j = i + i; j <= n; j += i)
                table[j] = false;
        }
    }
    for (int i = 2; i <= n; ++i)
    {
        if (table[i])
            ret.push_back(i);
    }
}

void entry()
{
    std::vector<int> nums;
    filter_out(nums);
    int cnt = 0;
    for (int i = 1; i < nums.size(); ++i)
    {
        if (nums[i] - nums[i-1] == 2)
            ++cnt;
    }
    printf("%d", cnt);
}
}

namespace self_3 {

void entry()
{
    int n, m;
    scanf("%d%d", &n, &m);
    m %= n;
    int num[n];
    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &num[i]);
    }
    std::reverse(num, num + n);
    std::reverse(num, num + m);
    std::reverse(num + m, num + n);
    for (int j = 0; j < n; ++j)
    {
        if (j != 0)
            printf(" ");
        printf("%d", num[j]);
    }
}
}

namespace self_4 {
struct bign
{
    int digit[1000];
    int len;
    bign() : digit{0}, len(0) {}
};

bign operator+(const bign &a, const bign &b)
{
    int r = 0;
    bign c;
    for (int i = 0; i < a.len || i < b.len; ++i)
    {
        c.digit[c.len++] = (r + a.digit[i] + b.digit[i]) % 10;
        r = (r + a.digit[i] + b.digit[i]) / 10;
    }
    if (r)
        c.digit[c.len++] = r % 10;
    return c;
}

std::istream &operator>>(std::istream &is, bign &n)
{
    std::string str;
    is >> str;
    for (int i = str.size() - 1; i >= 0; --i)
    {
        n.digit[n.len++] = str[i] - '0';
    }
    return is;
}

std::ostream &operator<<(std::ostream &os, const bign &n)
{
    for (int i = n.len-1; i >= 0; --i)
    {
        os << n.digit[i];
    }
    return os;
}

void entry()
{
    bign n;
    std::cin >> n;
    int table[10];
    memset(table, 0, sizeof(table));
    for (int i = 0; i < n.len; ++i)
    {
        table[n.digit[i]]++;
    }

    bign c = n + n;
    for (int j = 0; j < c.len; ++j)
    {
        table[c.digit[j]]--;
    }

    bool flag = true;
    for (int k = 0; k < 10; ++k)
    {
        if (table[k] != 0)
        {
            flag = false;
            break;
        }
    }

    if (flag)
        std::cout << "Yes" << std::endl;
    else
        std::cout << "No" << std::endl;
    std::cout << c << std::endl;
}
}

namespace self_5 {
const char symbol[5] = {'S', 'H', 'C', 'D', 'J'};
constexpr int N = 55;

void entry()
{
    int k;
    scanf("%d", &k);
    int cards[N], shuffle[N];
    for (int j = 1; j < N; ++j)
    {
        scanf("%d", &shuffle[j]);
        cards[j] = j;
    }
    int tmp[N];
    while (k--)
    {
        for (int i = 1; i < N; ++i)
            tmp[shuffle[i]] = cards[i];
        for (int j = 1; j < N; ++j)
            cards[j] = tmp[j];
    }

    for (int i = 1; i < N; ++i)
    {
        if (i != 1)
            printf(" ");
        printf("%c%d", symbol[(cards[i]-1)/13], (cards[i]-1)%13+1);
    }
}
}







int main(int argc, char **argv)
{
//    self_1::entry();
//    self_2::entry();
//    self_3::entry();
//    self_4::entry();
    self_5::entry();
    return 0;
}