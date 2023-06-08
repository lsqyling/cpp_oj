#include <cstdio>
#include <algorithm>
#include <vector>
#include <cmath>
#include <cstring>
#include <iostream>
#include <string>


namespace basic_61 {

int score[105];
int right_ans[105];


void entry()
{
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; ++i)
    {
        scanf("%d", &score[i]);
    }
    for (int j = 0; j < m; ++j)
    {
        scanf("%d", &right_ans[j]);
    }
    for (int k = 0; k < n; ++k)
    {
        int sum = 0;
        int tmp;
        for (int i = 0; i < m; ++i)
        {
            scanf("%d", &tmp);
            if (right_ans[i] == tmp)
                sum += score[i];
        }
        printf("%d\n", sum);
    }
}
}

namespace basic_62 {
struct fraction
{
    int up, down;
};

int gcd(int a, int b)
{
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

int lcm(int a, int b)
{
    int g = gcd(a, b);
    return a * b / g;
}

void simply(fraction &f)
{
    int g = gcd(f.up, f.down);
    f.up /= g;
    f.down /= g;
}

bool operator<(fraction a, fraction b)
{
    int d = lcm(a.down, b.down);
    int t = d / a.down;
    a.down *= t;
    a.up *= t;

    t = d / b.down;
    b.down *= t;
    b.up *= t;
    return a.up < b.up;
}


void same_down(fraction &a, fraction &b, fraction &c)
{
    int d = lcm(a.down, b.down);
    d = lcm(d, c.down);

    int t = d / a.down;
    a.down *= t;
    a.up *= t;

    t = d / b.down;
    b.down *= t;
    b.up *= t;

    t = d / c.down;
    c.down *= t;
    c.up *= t;
}

void entry()
{
    fraction a, b, c;
    scanf("%d/%d %d/%d %d", &a.up, &a.down, &b.up, &b.down, &c.down);
    c.up = 1;

    int old = c.down;
    same_down(a, b, c);
    if (b < a)
        std::swap(a, b);

    std::vector<fraction> ans;
    for (int i = a.up + 1; i < b.up; ++i)
    {
        int t = c.down / old;
        if (i % t == 0)
        {
            c.up = i;
            auto tmp = c;
            simply(tmp);
            if (tmp.down == old)
            {
                ans.push_back(tmp);
            }

        }
    }

    for (int j = 0; j < ans.size(); ++j)
    {
        printf("%d/%d", ans[j].up, ans[j].down);
        if (j < ans.size() - 1)
            printf(" ");
    }
}
}

namespace basic_63 {
void entry()
{
    int n;
    scanf("%d", &n);
    int a, b, c;
    int max = 0;
    for (int i = 0; i < n; ++i)
    {
        scanf("%d%d", &a, &b);
        c = a * a + b * b;
        if (c > max)
            max = c;
    }

    printf("%.2f\n", sqrt(1.0 * max));
}
}

namespace basic_64 {

int digit[10], len = 0;
bool table[40];


void convert(int n, int radix)
{
    len = 0;
    do
    {
        digit[len++] = n % radix;
        n /= radix;
    } while (n);
}

void entry()
{
    int n, x;
    scanf("%d", &n);
    int count = 0;
    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &x);
        convert(x, 10);
        int sum = 0;
        for (int j = 0; j < len; ++j)
        {
            sum += digit[j];
        }
        if (!table[sum])
        {
            ++count;
            table[sum] = true;
        }
    }
    printf("%d\n", count);
    for (int k = 0; k < 40; ++k)
    {
        if (table[k])
        {
            printf("%d", k);
            if (--count > 0)
                printf(" ");
        }
    }
}
}

namespace basic_65 {
constexpr int N = 100'005;
constexpr int M = 10'005;

int couple[N], guest[M];
bool table[N];

void entry()
{
    int n;
    int c, p;
    scanf("%d", &n);
    memset(couple, -1, sizeof(couple));
    for (int i = 0; i < n; ++i)
    {
        scanf("%d%d", &c, &p);
        couple[c] = p;
        couple[p] = c;
    }

    int m;
    scanf("%d", &m);
    std::vector<int> ans;
    for (int j = 0; j < m; ++j)
    {
        scanf("%d", &c);
        guest[j] = c;
        table[c] = true;
    }

    for (int j = 0; j < m; ++j)
    {
        c = guest[j];
        p = couple[c];
        if (p == -1 || !table[p])
            ans.push_back(c);
    }

    std::sort(ans.begin(), ans.end());
    printf("%zu\n", ans.size());
    for (int k = 0; k < ans.size(); ++k)
    {
        printf("%05d", ans[k]);
        if (k < ans.size() - 1)
            printf(" ");
    }
}
}

namespace basic_66 {

void entry()
{
    int m, n, A, B, v, x;
    scanf("%d%d%d%d%d", &m, &n, &A, &B, &v);
    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            scanf("%d", &x);
            if (A <= x && x <= B)
                x = v;
            printf("%03d", x);
            if (j < n - 1)
                printf(" ");
        }
        printf("\n");
    }
}
}

namespace basic_67 {
void entry()
{
    std::string password;
    int n;
    std::cin >> password >> n;
    getchar();
    std::string tmp;
    for (int j = 0; j < n; ++j)
    {

        std::getline(std::cin, tmp);
        if (tmp == "#")
            return ;
        if (tmp == password)
        {
            std::cout << "Welcome in";
            return ;
        }
        else
            std::cout << "Wrong password: " << tmp << std::endl;
    }
    std::cout << "Account locked";
}
}




















int main(int argc, char **argv)
{
//    basic_61::entry();
//    basic_62::entry();
//    basic_63::entry();
//    basic_64::entry();
//    basic_65::entry();
//    basic_66::entry();
    basic_67::entry();
    return 0;

}