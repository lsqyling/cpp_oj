#include <cstdio>
#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include <algorithm>
#include <map>
#include <cmath>

namespace basic_101 {


void entry()
{
    std::string str;
    int d;
    std::cin >> str >> d;

    int s1, s2;
    s1 = std::stoi(str);

    std::string st1 = str.substr(str.size() - d);
    str.erase(str.size() - d);
    std::string new_num = st1 + str;

    s2 = std::stoi(new_num);

    printf("%.2f\n", 1.0*s2/s1);
}
}

namespace basic_102 {
using std::string;
void entry()
{
    int n ,price, amount;
    scanf("%d", &n);
    string id, max_amount_id, max_sales_id;
    int max_amount = -1, max_sales = -1;
    for (int i = 0; i < n; ++i)
    {
        std::cin >> id >> price >> amount;
        if (amount > max_amount)
        {
            max_amount = amount;
            max_amount_id = id;
        }
        if (price * amount > max_sales)
        {
            max_sales = price * amount;
            max_sales_id = id;
        }
    }

    std::cout << max_amount_id << " " << max_amount << std::endl;
    std::cout << max_sales_id << " " << max_sales << std::endl;
}
}

namespace basic_103 {

void entry()
{
    int64_t m, n;
    scanf("%ld%ld", &m, &n);
    bool flag = false;
    for (int64_t a = m; a <= n; ++a)
    {
        for (int64_t b = 1; b < a; ++b)
        {
            if (a*a*a-(a-1)*(a-1)*(a-1) == (b*b+(b-1)*(b-1))*(b*b+(b-1)*(b-1)))
            {
                printf("%ld %ld\n", a, b);
                flag = true;
            }
        }
    }
    if (!flag)
        printf("No Solution");
}
}

namespace basic_104 {

int calc_sum_of_digits(int n)
{
    int sum = 0;
    do
    {
        sum += n % 10;
        n /= 10;
    } while (n);
    return sum;
}

int gcd(int a, int b)
{
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

bool is_prime(int n)
{
    if (n < 2)
        return false;
    int sqrt_n = sqrt(n);
    for (int i = 2; i <= sqrt_n; ++i)
    {
        if (n % i == 0)
            return false;
    }
    return true;
}

int left(int k)
{
    int sum = 1;
    for (int i = 0; i < k; ++i)
    {
        sum *= 10;
    }
    return sum;
}

struct pair
{
    int first;
    int second;
};

bool operator<(pair a, pair b)
{
    if (a.first != b.first)
        return a.first < b.first;
    else
        return a.second < b.second;
}



void entry()
{
    int n, k, m;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d%d", &k, &m);
        printf("Case %d\n", i);
        if (m/k > 9 || k <= 3 || k >= 10)
        {
            printf("No Solution\n");
            continue;
        }
        bool flag = false;
        std::vector<pair> ans;
        for (int p = left(k),j = p/10 + 99; j < p; j += 100)
        {
            if (calc_sum_of_digits(j) == m)
            {
                int N = calc_sum_of_digits(j+1);
                int g = gcd(N, m);
                if (g > 2 && is_prime(g))
                {
                    ans.push_back({N, j});
                    flag = true;
                }
            }
        }
        if (!flag)
            printf("No Solution\n");
        else
        {
            std::sort(ans.begin(), ans.end());
            for (int j = 0; j < ans.size(); ++j)
            {
                printf("%d %d\n", ans[j].first, ans[j].second);
            }

        }
    }
}
}

namespace basic_105 {
constexpr int N = 100'005;

struct node
{
    int adr, data, next;
};

node list[N];
//1->2->3->4->5->6->7->8 k=3 =>3->2->1->6->5->4-7->8
int reverse_of_k_nodes(int head, int k)
{
    if (head == -1 || list[head].next == -1 || k < 2)
        return head;
    int tail = head;
    for (int i = 0; i < k; ++i)
    {
        if (tail == -1)
            return head;
        tail = list[tail].next;
    }
    int pre = -1, cur = head;
    while (cur != tail)
    {
        auto next = list[cur].next;

        list[cur].next = pre;
        pre = cur;
        cur = next;

    }
    list[head].next = reverse_of_k_nodes(tail, k);
    return pre;
}

int reverse_of_list(int head)
{
    if (head == -1 || list[head].next == -1)
        return head;
    int tail = -1;
    int pre = -1, cur = head;
    while (cur != tail)
    {
        auto next = list[cur].next;

        list[cur].next = pre;
        pre = cur;
        cur = next;
    }
    return pre;
}

void entry()
{
    int h1, h2, n;
    scanf("%d%d%d", &h1, &h2, &n);
    int adr, data, next;
    for (int i = 0; i < n; ++i)
    {
        scanf("%d%d%d", &adr, &data, &next);
        list[adr].adr = adr;
        list[adr].data = data;
        list[adr].next = next;
    }
    int len1 = 0, len2 = 0;
    int cur = h1;
    while (cur != -1)
    {
        cur = list[cur].next;
        ++len1;
    }
    cur = h2;
    while (cur != -1)
    {
        cur = list[cur].next;
        ++len2;
    }
    if (len1 >= 2 * len2)
    {
        std::swap(h1, h2);
        std::swap(len1, len2);
    }
    h1 = reverse_of_list(h1);

    int cur1 = h1, cur2 = h2;
    while (cur1 != -1)
    {
        auto next1 = list[cur1].next;
        auto next2 = list[cur2].next;

        list[cur1].next = list[next2].next;
        list[next2].next = cur1;

        cur2 = list[cur1].next;
        cur1 = next1;
    }
    cur = h2;
    while (list[cur].next != -1)
    {
        printf("%05d %d %05d\n", list[cur].adr, list[cur].data, list[cur].next);
        cur = list[cur].next;
    }
    printf("%05d %d -1", list[cur].adr, list[cur].data);
}
}



int main(int argc, char **argv)
{
//    basic_101::entry();
//    basic_102::entry();
//    basic_103::entry();
//    basic_104::entry();
    basic_105::entry();
    return 0;
}
