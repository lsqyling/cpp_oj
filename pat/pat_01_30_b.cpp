#include "pat.h"

namespace pat_a1001 {
constexpr int N = 15;

int digit[N], len;

void digit_of_num(int n)
{
    len = 0;
    do
    {
        digit[len++] = n % 10;
        n /= 10;
    } while (n);
}

void entry()
{
    int a, b;
    scanf("%d%d", &a, &b);
    int n = a + b;
    if (n < 0)
    {
        n = -n;
        printf("-");
    }
    digit_of_num(n);
    for (int i = len - 1; i >= 0; --i)
    {
        printf("%d", digit[i]);
        if (i > 0 && i % 3 == 0)
        {
            printf(",");
        }
    }
}
}

namespace pat_a1002 {
constexpr int N = 1005;

double polynomial[N];

void entry()
{
    int k, exp;
    double coef;
    scanf("%d", &k);
    for (int i = 0; i < k; ++i)
    {
        scanf("%d%lf", &exp, &coef);
        polynomial[exp] += coef;
    }
    scanf("%d", &k);
    for (int i = 0; i < k; ++i)
    {
        scanf("%d%lf", &exp, &coef);
        polynomial[exp] += coef;
    }
    int n = 0;
    for (int i = 0; i < N; ++i)
    {
        if (polynomial[i] != 0)
            ++n;
    }
    printf("%d", n);
    for (int i = N - 1; i >= 0; --i)
    {
        if (polynomial[i] != 0)
        {
            printf(" %d %.1f", i, polynomial[i]);
        }
    }
}
}

namespace pat_a1003 {
constexpr int N = 505;
constexpr int INF = 0x3fff'ffff;

int G[N][N], n;
int weight[N], w[N];
bool visit[N];
int num[N], d[N];

void dijkstra(int s)
{
    std::fill(d, d + N, INF);
    w[s] = weight[s];
    d[s] = 0;
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
        if (u == -1)
            return ;
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

void entry()
{
    int m, s, e;
    scanf("%d%d%d%d", &n, &m, &s, &e);
    for (int i = 0; i < n; ++i)
        scanf("%d", &weight[i]);
    std::fill(G[0], G[0] + N * N, INF);
    while (m--)
    {
        int u, v, dis;
        scanf("%d%d%d", &u, &v, &dis);
        G[u][v] = G[v][u] = dis;
    }
    dijkstra(s);
    printf("%d %d\n", num[e], w[e]);
}
}

namespace pat_a1004 {
constexpr int N = 105;
namespace bfs_solve {
struct node
{
    int id;
    int layer;
};
std::vector<node> tree[N];
int num[N], max_layer = 0;

void bfs(int root)
{
    std::queue<node> q;
    q.push({root, 1});
    while (!q.empty())
    {
        node top = q.front();
        q.pop();
        if (tree[top.id].empty())
            ++num[top.layer];
        if (top.layer > max_layer)
            max_layer = top.layer;
        for (auto child : tree[top.id])
        {
            child.layer = top.layer + 1;
            q.push(child);
        }
    }
}

void entry()
{
    int n, m;
    scanf("%d%d", &n, &m);
    while (m--)
    {
        int id, k, child;
        scanf("%d%d", &id, &k);
        for (int i = 0; i < k; ++i)
        {
            scanf("%d", &child);
            tree[id].push_back({child, 0});
        }
    }
    bfs(1);
    for (int i = 1; i <= max_layer; ++i)
    {
        printf("%d", num[i]);
        if (i < max_layer)
            printf(" ");
        else
            printf("\n");
    }
}
}

namespace dfs_solve {
std::vector<int> G[N];

int leaf[N], max_h = 0;

void dfs(int u, int h)
{
    if (max_h < h)
        max_h = h;
    if (G[u].empty())
    {
        ++leaf[h];
        return ;
    }
    for (auto v : G[u])
        dfs(v, h + 1);
}

void entry()
{
    int n, m;
    scanf("%d%d", &n, &m);
    while (m--)
    {
        int id, k, c;
        scanf("%d%d", &id, &k);
        for (int i = 0; i < k; ++i)
        {
            scanf("%d", &c);
            G[id].push_back(c);
        }
    }
    dfs(1, 0);
    for (int i = 0; i <= max_h; ++i)
    {
        printf("%d", leaf[i]);
        if (i < max_h)
            printf(" ");
        else
            printf("\n");
    }
}
}
}

namespace pat_a1005 {
constexpr int N = 105;
const char *ennums[10] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

char str[N];
int digit[N], len;

void trans_to_num(int n)
{
    len = 0;
    do
    {
        digit[len++] = n % 10;
        n /= 10;
    } while (n);
}

void entry()
{
    scanf("%s", str);
    int sum = 0;
    for (int i = 0; str[i] != '\0'; ++i)
    {
        sum += str[i] - '0';
    }
    trans_to_num(sum);
    for (int i = len - 1; i >= 0; --i)
    {
        printf("%s", ennums[digit[i]]);
        if (i > 0)
            printf(" ");
        else
            printf("\n");
    }
}
}

namespace pat_a1006 {

struct record
{
    char id[20];
    int sign_in_time;
    int sign_out_time;
};

auto cmp_sign_in = [](record a, record b)
{
    return a.sign_in_time < b.sign_in_time;
};

auto cmp_sign_out = [](record a, record b)
{
    return a.sign_out_time > b.sign_out_time;
};

std::vector<record> list;

void entry()
{
    int m;
    scanf("%d", &m);
    record tmp;
    int h1, m1, s1, h2, m2, s2;
    while (m--)
    {
        scanf("%s %d:%d:%d %d:%d:%d", tmp.id, &h1, &m1, &s1, &h2, &m2, &s2);
        tmp.sign_in_time = h1 * 3600 + m1 * 60 + s1;
        tmp.sign_out_time = h2 * 3600 + m2 * 60 + s2;
        if (tmp.sign_in_time < tmp.sign_out_time)
            list.push_back(tmp);
    }
    std::sort(list.begin(), list.end(), cmp_sign_in);
    std::string in = list[0].id;
    std::sort(list.begin(), list.end(), cmp_sign_out);
    std::string out = list[0].id;
    printf("%s %s", in.c_str(), out.c_str());
}
}

namespace pat_a1007 {
constexpr int N = 10005;


int num[N], dp[N];
int begin[N];

void entry()
{
    int n;
    scanf("%d", &n);
    bool all_negative = true;
    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &num[i]);
        if (num[i] >= 0)
            all_negative = false;
    }
    if (all_negative)
    {
        printf("0 %d %d\n", num[0], num[n-1]);
        return ;
    }

    dp[0] = num[0];
    begin[0] = 0;
    int max = num[0], end;
    for (int j = 1; j < n; ++j)
    {

        if (dp[j-1] > 0)
        {
            dp[j] = dp[j-1] + num[j];
            begin[j] = begin[j-1];
        }
        else
        {
            dp[j] = num[j];
            begin[j] = j;
        }
        if (max < dp[j])
        {
            max = dp[j];
            end = j;
        }
    }
    printf("%d %d %d\n", max, num[begin[end]], num[end]);
}
}

namespace pat_a1008 {
constexpr int N = 105;

int stop[N];

void entry()
{
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &stop[i]);
    }
    int t = 0, diff;
    for (int i = 1; i <= n; ++i)
    {
        diff = stop[i] - stop[i-1];
        diff < 0 ? t += diff * -4 : t += diff * 6;
    }
    t += n * 5;
    printf("%d\n", t);
}
}

namespace pat_a1009 {
constexpr int N = 2005;

double A[N], B[N];

void entry()
{
    int n, exp, max_exp = 0;
    double coef;
    scanf("%d", &n);
    while (n--)
    {
        scanf("%d%lf", &exp, &coef);
        A[exp] = coef;
        if (exp > max_exp)
            max_exp = exp;
    }
    scanf("%d", &n);
    while (n--)
    {
        scanf("%d%lf", &exp, &coef);
        for (int i = 0; i <= max_exp; ++i)
            B[exp+i] += coef * A[i];
    }
    n = 0;
    for (int i = 0; i < N; ++i)
        if (B[i] != 0)
            ++n;
    printf("%d", n);
    for (int j = N - 1; j >= 0; --j)
    {
        if (B[j] != 0)
            printf(" %d %.1f", j, B[j]);
    }
}
}

namespace pat_a1010 {
constexpr int N = 1005;

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
    int r = 0, s;
    for (int i = 0; i < a.len || i < b.len; ++i)
    {
        s = a.digit[i] + b.digit[i] + r;
        res.digit[res.len++] = s % 10;
        r = s / 10;
    }
    if (r != 0)
        res.digit[res.len++] = r;
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

big_integer convert_to_integer(const std::string &str, long base)
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

void remove_front_zero(std::string &str)
{
    int n = 0;
    while (str[n] == '0')
        ++n;
    str.erase(0, n);
}

void entry()
{
    std::string sn1, sn2;
    int tag;
    long radix;
    std::cin >> sn1 >> sn2 >> tag >> radix;
    remove_front_zero(sn1);
    remove_front_zero(sn2);
    big_integer n1, n2;
    if (tag == 1)
        n1 = convert_to_integer(sn1, radix);
    else if (tag == 2)
    {
        n2 = convert_to_integer(sn2, radix);
        std::swap(sn1, sn2);
        std::swap(n1, n2);
    }
    int min_radix = 0;
    for (int c : sn2)
    {
        if ('a' <= c && c <= 'z')
            c = c - 'a' + 10;
        else
            c = c - '0';
        if (c > min_radix)
            min_radix = c;
    }
    min_radix = min_radix + 1;
    long left = min_radix, right = min_radix;
    while ((n2 = convert_to_integer(sn2, right)) < n1)
    {
        if (sn2.size() == 1)
            break;
        left = right;
        right *= 2;
    }

    long base = -1;
    while (left <= right)
    {
        long mid = (left + right) / 2;
        n2 = convert_to_integer(sn2, mid);
        if (n1 == n2)
        {
            base = mid;
            break;
        }
        else if (n1 < n2)
            right = mid - 1;
        else
            left = mid + 1;
    }
    if (base == -1)
        printf("Impossible\n");
    else
        printf("%ld\n", base);
}
}

namespace pat_a1011 {
constexpr int N = 3;

const char game_res[N] = {'W', 'T', 'L'};


void entry()
{
    int indices[N];
    double product = 1;
    double profit;
    for (int i = 0; i < N; ++i)
    {
        int max = 0;
        double max_profit = 0;
        for (int j = 0; j < N; ++j)
        {
            scanf("%lf", &profit);
            if (profit > max_profit)
            {
                max_profit = profit;
                max = j;
            }
        }
        product *= max_profit;
        indices[i] = max;
    }
    for (int i = 0; i < N; ++i)
    {
        printf("%c ", game_res[indices[i]]);
    }
    printf("%.2f\n", (product * 0.65 - 1) * 2);
}
}

namespace pat_a1012 {
constexpr int N = 4;
constexpr int M = 2005;
using std::string;

const int priority[N] = {3, 0, 1, 2};
const int id_c[M] = {'C', 'M', 'E', 'A'};

struct stu
{
    char id[10];
    int grade[N];
    int rank[N];
    int best_rank;
    char course;
};
stu list[M];
std::map<string, stu> query;
int cmp_idx, n;

bool cmp_index(const stu &a, const stu &b)
{
    if (a.grade[cmp_idx] != b.grade[cmp_idx])
        return a.grade[cmp_idx] > b.grade[cmp_idx];
    else
        return strcmp(a.id, b.id) < 0;
}

void sort_set_rank()
{
    for (int i = 0; i < N; ++i)
    {
        cmp_idx = i;
        std::sort(list, list + n, cmp_index);
        int r = 1;
        for (int j = 0; j < n; ++j)
        {
            if (j > 0 && list[j].grade[i] != list[j-1].grade[i])
                r = j + 1;
            list[j].rank[i] = r;
        }
    }
    for (int i = 0; i < n; ++i)
    {
        int min_idx = priority[0];
        int min = list[i].rank[min_idx];
        for (int j = 0; j < N; ++j)
        {
            if (list[i].rank[priority[j]] < min)
            {
                min = list[i].rank[priority[j]];
                min_idx = priority[j];
            }
        }
        list[i].best_rank = min;
        list[i].course = id_c[min_idx];
        query[list[i].id] = list[i];
    }
}

void entry()
{
    int m;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++i)
    {
        scanf("%s", list[i].id);
        int j;
        double sum = 0;
        for (j = 0; j < N - 1; ++j)
        {
            scanf("%d", &list[i].grade[j]);
            sum += list[i].grade[j];
        }
        list[i].grade[j] = round(sum / (1.0 * (N - 1)));
    }
    sort_set_rank();
    char sid[10];
    while (m--)
    {
        scanf("%s", sid);
        auto it = query.find(sid);
        if (it == query.end())
            printf("N/A");
        else
            printf("%d %c", it->second.best_rank, it->second.course);
        printf("\n");
    }
}
}

namespace pat_a1013 {
constexpr int N = 1005;

int G[N][N], n;
bool visit[N];

void dfs(int u, int del_point)
{
    if (u == del_point)
        return ;
    if (visit[u])
        return ;
    visit[u] = true;
    for (int v = 1; v <= n; ++v)
    {
        if (G[u][v] != 0)
            dfs(v, del_point);
    }
}

int count_connected_blocks(int del_point)
{
    int count = 0;
    memset(visit, false, sizeof(visit));
    for (int v = 1; v <= n; ++v)
    {
        if (del_point != v && !visit[v])
        {
            dfs(v, del_point);
            ++count;
        }
    }
    return count;
}



void entry()
{
    int m, k;
    scanf("%d%d%d", &n, &m, &k);
    while (m--)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        G[u][v] = G[v][u] = 1;
    }
    while (k--)
    {
        int u;
        scanf("%d", &u);
        int count = count_connected_blocks(u);
        printf("%d\n", count - 1);
    }
}
}

namespace pat_a1014 {
constexpr int N = 25;
constexpr int K = 1005;

struct window
{
    int end_time;
    int pop_time;
    std::queue<int> q;
};

window windows[N];
int n, k;

int convert_to_minutes(int h, int m)
{
    return h * 60 + m;
}

int ans[N], need_time[N];

void entry()
{
    int index = 0;
    int m, query;
    scanf("%d%d%d%d", &n, &m, &k, &query);
    for (int i = 0; i < k; ++i)
    {
        scanf("%d", &need_time[i]);
    }
//    init window
    for (int i = 0; i < n; ++i)
    {
        windows[i].pop_time = windows[i].end_time = convert_to_minutes(8, 0);
    }
//    init customer's state
    for (int i = 0; i < std::min(m * n, k); ++i)
    {
        windows[index%n].q.push(index);
        windows[index%n].end_time += need_time[index];
        if (index < n)
            windows[index].pop_time = need_time[index];
        ans[index] = windows[index%n].end_time;
        ++index;
    }
//    process the remaining customers
    for (; index < k; ++index)
    {
        int idx = -1, min_pop_time = 0x3fff'ffff;
        for (int i = 0; i < n; ++i)
        {
            if (windows[i].pop_time < min_pop_time)
            {
                min_pop_time = windows[i].pop_time;
                idx = i;
            }
        }
        window &w = windows[idx];
        w.q.pop();
        w.q.push(index);
        w.end_time += need_time[index];
        w.pop_time += need_time[w.q.front()];
        ans[index] = w.end_time;
    }
    while (query--)
    {
        int id;
        scanf("%d", &id);
        --id;
        if (ans[id] - need_time[id] >= convert_to_minutes(17, 0))
        {
            printf("Sorry\n");
        }
        else
        {
            printf("%02d:%02d\n", ans[id] / 60, ans[id] % 60);
        }
    }
}
}

namespace pat_a1015 {
constexpr int N = 35;

int digit[N], len;

int reverse_num(int n, int radix)
{
    len = 0;
    do
    {
        digit[len++] = n % radix;
        n /= radix;
    } while (n);
    int sum = 0;
    for (int i = 0; i < len; ++i)
    {
        sum = sum * radix + digit[i];
    }
    return sum;
}

bool is_prime_num(int n)
{
    if (n < 2)
        return false;
    int sqrt_n = std::sqrt(n);
    for (int i = 2; i <= sqrt_n; ++i)
    {
        if (n % i == 0)
            return false;
    }
    return true;
}

void entry()
{
    while (1)
    {
        int n, radix;
        scanf("%d", &n);
        if (n < 0)
            break;
        scanf("%d", &radix);
        int r = reverse_num(n, radix);
        if (is_prime_num(n) && is_prime_num(r))
            printf("Yes\n");
        else
            printf("No\n");
    }
}
}

namespace pat_a1016 {
int rate[24];

struct record
{
    char name[25];
    int month;
    int day, hour, minute;
    char state[10];
};

auto cmp = [](const record &a, const record &b)
{
    if (strcmp(a.name, b.name) != 0)
        return strcmp(a.name, b.name) < 0;
    else
        return a.minute + a.hour * 60 + a.day * 24 * 60 < b.minute + b.hour * 60 + b.day * 24 * 60;
};

struct pair
{
    double toll;
    int time;
};

pair calc_toll(const record &t1, const record &t2)
{
    int d1 = t1.day, h1 = t1.hour, m1 = t1.minute;
    int d2 = t2.day, h2 = t2.hour, m2 = t2.minute;
    int sum = 0, t = 0;
    while (m1 < m2 || h1 < h2 || d1 < d2)
    {
        ++m1;
        ++t;
        sum += rate[h1];
        if (m1 == 60)
        {
            ++h1;
            m1 = 0;
        }
        if (h1 == 24)
        {
            ++d1;
            h1 = 0;
        }
    }
    return {sum * 1.0 / 100.0, t};
}

void read_data(std::vector<record> &records)
{
    for (int i = 0; i < 24; ++i)
    {
        scanf("%d", &rate[i]);
    }
    int n;
    scanf("%d", &n);
    record tmp;
    for (int i = 0; i < n; ++i)
    {
        scanf("%s %d:%d:%d:%d %s",
              tmp.name,
              &tmp.month, &tmp.day, &tmp.hour, &tmp.minute,
              tmp.state);
        records.push_back(tmp);
    }
}

void entry()
{
    std::vector<record> records;
    std::vector<record> bill;
    read_data(records);

    std::sort(records.begin(), records.end(), cmp);
    for (int i = 0; i < records.size() - 1; ++i)
    {
        auto &r1 = records[i], &r2 = records[i+1];
        if (strcmp(r1.name, r2.name) == 0 &&
            (strcmp(r1.state, "on-line") == 0 && strcmp(r2.state, "off-line") == 0))
        {
            bill.push_back(r1);
            bill.push_back(r2);
        }
    }

    for (int i = 0, j = 0; j < bill.size(); )
    {
        while (j < bill.size() && strcmp(bill[i].name, bill[j].name) == 0)
            ++j;

        printf("%s %02d\n", bill[j-1].name, bill[j-1].month);
        double total = 0;
        while (i < j)
        {
            auto p = calc_toll(bill[i], bill[i+1]);
            printf("%02d:%02d:%02d %02d:%02d:%02d %d $%.2f\n",
                   bill[i].day, bill[i].hour, bill[i].minute,
                   bill[i+1].day, bill[i+1].hour, bill[i+1].minute,
                   p.time, p.toll);
            total += p.toll;
            i += 2;
        }
        printf("Total amount: $%.2f\n", total);
    }
}
}













namespace pat_a1017 {
constexpr int K = 105;

struct customer
{
    int arrive_time;
    int serve_time;
};

std::vector<customer> queue;
int end_window_t[K];

int convert_to_seconds(int h, int m, int s)
{
    return h * 3600 + m * 60 + s;
}

bool cmp_by_arrive(const customer &a, const customer &b)
{
    return a.arrive_time < b.arrive_time;
}

void entry()
{
    int n, k, total_wait_t = 0;
    int begin_t = convert_to_seconds(8, 0, 0);
    int end_t = convert_to_seconds(17, 0, 0);
    scanf("%d%d", &n, &k);
//    init window
    for (int i = 0; i < k; ++i)
    {
        end_window_t[i] = begin_t;
    }
//    input customer
    customer tmp;
    for (int i = 0; i < n; ++i)
    {
        int h, m, s, serve_t;
        scanf("%d:%d:%d %d", &h, &m, &s, &serve_t);
        int arrive_t = convert_to_seconds(h, m, s);
        if (arrive_t > end_t)
            continue;
        tmp.arrive_time = arrive_t;
        tmp.serve_time = serve_t <= 60 ? serve_t * 60 : 3600;
        queue.push_back(tmp);
    }
    std::sort(queue.begin(), queue.end(), cmp_by_arrive);
    for (int i = 0; i < queue.size(); ++i)
    {
        int idx = -1, min_end_t = 0x3fff'ffff;
        for (int j = 0; j < k; ++j)
        {
            if (end_window_t[j] < min_end_t)
            {
                min_end_t = end_window_t[j];
                idx = j;
            }
        }
//
        if (end_window_t[idx] <= queue[i].arrive_time)
        {
            end_window_t[idx] = queue[i].arrive_time + queue[i].serve_time;
        }
        else
        {
            total_wait_t += end_window_t[idx] - queue[i].arrive_time;
            end_window_t[idx] += queue[i].serve_time;
        }
    }

    if (queue.empty())
        printf("0.0");
    else
        printf("%.1f", 1.0 * total_wait_t / 60.0 / queue.size());
}
}

namespace pat_a1018 {
constexpr int N = 505;
constexpr int INF = 0x3fff'ffff;

int G[N][N], n;
int weight[N], d[N];
bool visit[N];

std::vector<int> pre[N];

void dijkstra(int s)
{
    std::fill(d, d + N, INF);
    d[s] = 0;
    for (int i = 0; i < n + 1; ++i)
    {
        int u = -1, min = INF;
        for (int j = 0; j <= n; ++j)
        {
            if (!visit[j] && d[j] < min)
            {
                min = d[j];
                u = j;
            }
        }
        if (u == -1)
            return ;
        visit[u] = true;
        for (int v = 0; v <= n; ++v)
        {
            if (!visit[v] && G[u][v] != INF)
            {
                if (d[u] + G[u][v] < d[v])
                {
                    d[v] = d[u] + G[u][v];
                    pre[v].clear();
                    pre[v].push_back(u);
                }
                else if (d[u] + G[u][v] == d[v])
                {
                    pre[v].push_back(u);
                }
            }
        }
    }
}

std::vector<int> tmp, path;
int min_take_num = INF;
int min_back_num = INF;

void dfs_path(int v)
{
    if (pre[v].empty())
    {
        int take = 0, back = 0;
        for (int i = tmp.size() - 1; i >= 0; --i)
        {
            int u = tmp[i];
            if (weight[u] > 0)
                back += weight[u];
            else
            {
                if (back > -weight[u])
                    back -= -weight[u];
                else
                {
                    take += -weight[u] - back;
                    back = 0;
                }
            }
        }
        if (take < min_take_num)
        {
            min_take_num = take;
            min_back_num = back;
            path = tmp;
        }
        else if (take == min_take_num)
        {
            if (back < min_back_num)
            {
                min_back_num = back;
                path = tmp;
            }
        }
        return ;
    }
    tmp.push_back(v);
    for (auto u : pre[v])
        dfs_path(u);
    tmp.pop_back();
}

void entry()
{
    int c_max, sp, m;
    scanf("%d%d%d%d", &c_max, &n, &sp, &m);
    std::fill(G[0], G[0] + N * N, INF);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &weight[i]);
        weight[i] -= c_max/2;
    }
    while (m--)
    {
        int u, v, dis;
        scanf("%d%d%d", &u, &v, &dis);
        G[u][v] = G[v][u] = dis;
    }
    dijkstra(0);
    dfs_path(sp);
    printf("%d 0", min_take_num);
    for (int i = path.size() - 1; i >= 0; --i)
    {
        printf("->%d", path[i]);
    }
    printf(" %d\n", min_back_num);
}
}

namespace pat_a1019 {
constexpr int N = 35;

int digit[N], len;

void convert_to_num(int n, int base)
{
    len = 0;
    do
    {
        digit[len++] = n % base;
        n /= base;
    } while (n);
}

bool is_palindromic_num()
{
    for (int i = 0, j = len - 1; i < j; ++i, --j)
    {
        if (digit[i] != digit[j])
            return false;
    }
    return true;
}

void entry()
{
    int n, base;
    scanf("%d%d", &n, &base);
    convert_to_num(n, base);
    if (is_palindromic_num())
        printf("Yes\n");
    else
        printf("No\n");
    for (int i = len - 1; i >= 0; --i)
    {
        printf("%d", digit[i]);
        if (i > 0)
            printf(" ");
    }
}
}

namespace pat_a1020 {
constexpr int N = 35;

int post[N], in[N];

struct node
{
    int data;
    node *left, *right;
};

node *built_tree(int inL, int inR, int postL, int postR)
{
    if (inL > inR)
        return nullptr;
    node *root = new node;
    root->data = post[postR];

    int k;
    for (k = inL; k <= inR; ++k)
    {
        if (post[postR] == in[k])
            break;
    }
    int left_n = k - inL;
    root->left = built_tree(inL, k - 1, postL, postL + left_n - 1);
    root->right = built_tree(k + 1, inR, postL + left_n, postR - 1);
    return root;
}

void level_traversal(node *root, int n)
{
    if (root == nullptr)
        return ;
    std::queue<node *> q;
    q.push(root);
    int cnt = 0;
    while (!q.empty())
    {
        node *top = q.front();
        q.pop();
        printf("%d", top->data);
        if (++cnt < n)
            printf(" ");
        if (top->left != nullptr)
            q.push(top->left);
        if (top->right != nullptr)
            q.push(top->right);
    }
}

void entry()
{
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
        scanf("%d", &post[i]);
    for (int i = 0; i < n; ++i)
        scanf("%d", &in[i]);

    node *root = built_tree(0, n - 1, 0, n - 1);
    level_traversal(root, n);
}
}

namespace pat_a1021 {
constexpr int N = 10'005;

std::vector<int> tree[N];

int father[N], n;
bool is_root[N];
void init_father()
{
    for (int i = 0; i < N; ++i)
    {
        father[i] = i;
    }
}

int find_father(int x)
{
    int a = x;
    while (x != father[x])
        x = father[x];
    while (a != father[a])
    {
        int z = a;
        a = father[a];
        father[z] = x;
    }
    return x;
}

void union_(int a, int b)
{
    int fa = find_father(a);
    int fb = find_father(b);
    if (fa != fb)
        father[fa] = fb;
}

int calc_connected_block()
{
    for (int i = 1; i <= n; ++i)
    {
        is_root[find_father(i)] = true;
    }
    int block = 0;
    for (int i = 1; i <= n; ++i)
    {
        block += is_root[i];
    }
    return block;
}

std::vector<int> set_a;
int max_h = -1;
void dfs(int u, int h, int pre)
{
    if (h > max_h)
    {
        set_a.clear();
        set_a.push_back(u);
        max_h = h;
    }
    else if (h == max_h)
        set_a.push_back(u);
    for (auto  v : tree[u])
    {
        if (pre == v)
            continue;
        dfs(v, h + 1, u);
    }
}

void entry()
{
    scanf("%d", &n);
    init_father();
    for (int i = 1; i < n; ++i)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        tree[u].push_back(v);
        tree[v].push_back(u);
        union_(u, v);
    }
    int count = calc_connected_block();
    if (count > 1)
    {
        printf("Error: %d components\n", count);
        return;
    }
    dfs(1, 0, -1);
    std::vector<int> set_b = set_a;
    dfs(set_a[0], 0, -1);

    for (auto a : set_a)
        set_b.push_back(a);
    std::sort(set_b.begin(), set_b.end());
    printf("%d\n", set_b[0]);
    for (int i = 1; i < set_b.size(); ++i)
    {
        if (set_b[i] != set_b[i-1])
            printf("%d\n", set_b[i]);
    }
}
}

namespace pat_a1022 {

using std::string;

struct book
{
    int id;
    string title;
    string author;
    string keywords;
    string publisher;
    int year;
};

bool operator<(const book &a, const book &b)
{
    return a.id < b.id;
}

std::multimap<string, book> title_1;
std::multimap<string, book> author_2;
std::multimap<string, book> keyword_3;
std::multimap<string, book> publisher_4;
std::multimap<int, book> year_5;

template<typename T>
void print_query(T it, T end, const string &line)
{
    std::cout << line << "\n";
    if (it == end)
        printf("Not Found\n");
    else
    {
        std::vector<int> ans;
        for (; it != end; ++it)
            ans.push_back(it->second.id);
        std::sort(ans.begin(), ans.end());
        for (auto id : ans)
        {
            printf("%07d\n", id);
        }
    }
}

void entry()
{
    int n;
    std::cin >> n;
    getchar();
    string line;
    while (n--)
    {
        std::vector<string> block;
        book tmp;
        for (int i = 0; i < 6; ++i)
        {
            std::getline(std::cin, line);
            block.emplace_back(line);
        }
        tmp.id = std::stoi(block[0]);
        tmp.title = block[1];
        tmp.author = block[2];
        tmp.keywords = block[3];
        tmp.publisher = block[4];
        tmp.year = std::stoi(block[5]);

        title_1.insert({tmp.title, tmp});
        author_2.insert({tmp.author, tmp});
        std::istringstream is(tmp.keywords);
        string key;
        while (is >> key)
            keyword_3.insert({key, tmp});
        publisher_4.insert({tmp.publisher, tmp});
        year_5.insert({tmp.year, tmp});
    }

    std::cin >> n;
    getchar();
    while (n--)
    {
        string query;
        std::getline(std::cin, line);
        query = line;
        int q = query[0] - '0';
        query.erase(0, 3);

        switch (q)
        {
            case 1:
            {
                auto it = title_1.lower_bound(query);
                auto end = title_1.upper_bound(query);
                print_query(it, end, line);
                break;
            }
            case 2:
            {
                auto it = author_2.lower_bound(query);
                auto end = author_2.upper_bound(query);
                print_query(it, end, line);
                break;
            }
            case 3:
            {
                auto it = keyword_3.lower_bound(query);
                auto end = keyword_3.upper_bound(query);
                print_query(it, end, line);
                break;
            }
            case 4:
            {
                auto it = publisher_4.lower_bound(query);
                auto end = publisher_4.upper_bound(query);
                print_query(it, end, line);
                break;
            }
            case 5:
            {
                int y = std::stoi(query);
                auto it = year_5.lower_bound(y);
                auto end = year_5.upper_bound(y);
                print_query(it, end, line);
                break;
            }
            default:
                ;
        }
    }
}
}

namespace pat_a1023 {
constexpr int N = 10;
using std::string;

int table[N];


string double_of_num(const string &str)
{
    int carry = 0;
    string res;
    for (int i = str.size() - 1; i >= 0; --i)
    {
        int tmp = (str[i] - '0') * 2 + carry;
        res.insert(res.begin(), 1, tmp % 10 + '0');
        carry = tmp / 10;
    }
    if (carry)
        res.insert(res.begin(), 1, carry + '0');
    return res;
}


void entry()
{
    string src;
    std::cin >> src;
    for (auto c : src)
        ++table[c-'0'];
    string res = double_of_num(src);
    for (auto c : res)
        --table[c-'0'];

    bool flag = true;
    for (int i = 0; i < N; ++i)
    {
        if (table[i] != 0)
        {
            flag = false;
            break;
        }
    }
    if (flag)
        printf("Yes\n");
    else
        printf("No\n");
    printf("%s", res.c_str());
}
}

namespace pat_a1024 {
using std::string;


bool is_palindromic_num(const string &str)
{
    for (int i = 0, j = str.size() - 1; i < j; ++i, --j)
    {
        if (str[i] != str[j])
            return false;
    }
    return true;
}

string reverse_to_num(string str)
{
    for (int i = 0, j = str.size() -1; i < j; ++i, --j)
    {
        std::swap(str[i], str[j]);
    }
    return str;
}

string add(const string &a, const string &b)
{
    string res;
    int carry = 0;
    for (int i = 0; i < a.size(); ++i)
    {
        int tmp = (a[i] - '0') + (b[i] - '0') + carry;
        res.insert(0, 1, tmp % 10 + '0');
        carry = tmp / 10;
    }
    if (carry)
        res.insert(0, 1, carry + '0');
    return res;
}



void entry()
{
    string n;
    int k;
    std::cin >> n >> k;
    int step;
    for (step = 0; step < k; ++step)
    {
        if (is_palindromic_num(n))
            break;
        n = add(n, reverse_to_num(n));
    }
    std::cout << n << "\n" << step;
}
}

namespace pat_a1025 {
struct stu
{
    long id;
    int score;
    int locate;
    int local_rank;
};

auto cmp = [](const stu &a, const stu &b)
{
    if (a.score != b.score)
        return a.score > b.score;
    else
        return a.id < b.id;
};

std::vector<stu> all;

void entry()
{
    int n, k;
    long id;
    int score;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        std::vector<stu> tmp;
        scanf("%d", &k);
        for (int j = 0; j < k; ++j)
        {
            scanf("%ld%d", &id, &score);
            tmp.push_back({id, score, i, 1});
        }
        std::sort(tmp.begin(), tmp.end(), cmp);
        int r = 1;
        for (int j = 0; j < k; ++j)
        {
            if (j > 0 && tmp[j].score != tmp[j-1].score)
                r = j + 1;

            tmp[j].local_rank = r;
            all.push_back(tmp[j]);
        }
    }

    std::sort(all.begin(), all.end(), cmp);
    int size = all.size();
    int r = 1;
    printf("%d\n", size);
    for (int i = 0; i < size; ++i)
    {
        if (i > 0 && all[i].score != all[i-1].score)
            r = i + 1;

        printf("%013ld %d %d %d\n", all[i].id, r, all[i].locate, all[i].local_rank);
    }
}
}



namespace pat_a1027 {
constexpr int N = 13;

const char base[N] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C'};

int digit[N], len;

void convert_to_digit(int n)
{
    len = 0;
    do
    {
        digit[len++] = n % 13;
        n /= 13;
    } while (n);
}

void entry()
{
    int color[3];
    for (int i = 0; i < 3; ++i)
        scanf("%d", &color[i]);

    printf("#");
    for (int i = 0; i < 3; ++i)
    {
        convert_to_digit(color[i]);
        if (len == 1)
            printf("0");
        for (int j = len - 1; j >= 0; --j)
            printf("%c", base[digit[j]]);
    }
}
}

namespace pat_a1028 {
constexpr int N = 10'0005;

struct student
{
    char id[10];
    char name[10];
    int grade;
};

student list[N];

bool cmp_c1(const student &a, const student &b)
{
    return strcmp(a.id, b.id) < 0;
}

bool cmp_c2(const student &a, const student &b)
{
    if (strcmp(a.name, b.name) != 0)
        return strcmp(a.name, b.name) < 0;
    else
        return strcmp(a.id, b.id) < 0;
}

bool cmp_c3(const student &a, const student &b)
{
    if (a.grade != b.grade)
        return a.grade < b.grade;
    else
        return strcmp(a.id, b.id) < 0;
}

void entry()
{
    int n, c;
    scanf("%d%d", &n, &c);
    for (int i = 0; i < n; ++i)
    {
        scanf("%s%s%d", list[i].id, list[i].name, &list[i].grade);
    }
    switch (c)
    {
        case 1:
            std::sort(list, list + n, cmp_c1);
            break;
        case 2:
            std::sort(list, list + n, cmp_c2);
            break;
        case 3:
            std::sort(list, list + n, cmp_c3);
            break;
        default:
            ;
    }
    for (int i = 0; i < n; ++i)
    {
        printf("%s %s %d\n", list[i].id, list[i].name, list[i].grade);
    }
}
}

namespace pat_a1029 {
void entry()
{
    int n;
    long x;
    scanf("%d", &n);
    std::vector<long> ans;
    for (int i = 0; i < n; ++i)
    {
        scanf("%ld", &x);
        ans.push_back(x);
    }
    scanf("%d", &n);
    while (n--)
    {
        scanf("%ld", &x);
        ans.push_back(x);
    }
    std::sort(ans.begin(), ans.end());
    printf("%ld\n", ans[(ans.size()-1)/2]);
}
}

namespace pat_a1030 {
constexpr int N = 505;
constexpr int INF = 0x3fff'ffff;

struct node
{
    int dis, cost;
};

node G[N][N];
bool visit[N];
int n, d[N], c[N], pre[N];

void dijkstra(int s)
{
    std::fill(d, d + N, INF);
    std::fill(c, c + N, INF);
    for (int i = 0; i < N; ++i)
        pre[i] = i;
    d[s] = 0;
    c[s] = 0;
    for (int i = 0; i < n; ++i)
    {
        int u = -1, min = INF;
        for (int j = 0; j < n; ++j)
        {
            if (!visit[j] && d[j] < min)
            {
                min = d[j];
                u = j;
            }
        }
        if (u == -1)
            return ;
        visit[u] = true;
        for (int v = 0; v < n; ++v)
        {
            if (!visit[v] && G[u][v].dis != INF)
            {
                if (d[u] + G[u][v].dis < d[v])
                {
                    d[v] = d[u] + G[u][v].dis;
                    c[v] = c[u] + G[u][v].cost;
                    pre[v] = u;
                }
                else if (d[u] + G[u][v].dis == d[v])
                {
                    if (c[u] + G[u][v].cost < c[v])
                    {
                        c[v] = c[u] + G[u][v].cost;
                        pre[v] = u;
                    }
                }
            }
        }
    }
}

void print_path(int s, int u)
{
    if (u == s)
    {
        printf("%d", s);
        return ;
    }
    print_path(s, pre[u]);
    printf(" %d", u);
}


void entry()
{
    int m, s, e;
    scanf("%d%d%d%d", &n, &m, &s, &e);
    std::fill(G[0], G[0] + N * N, node{INF, INF});
    while (m--)
    {
        int u, v, dis, cost;
        scanf("%d%d%d%d", &u, &v, &dis, &cost);
        G[u][v] = G[v][u] = {dis, cost};
    }
    dijkstra(s);
    print_path(s, e);
    printf(" %d %d", d[e], c[e]);
}
}








int main(int argc, char **argv)
{
//    pat_a1001::entry();
//    pat_a1002::entry();
//    pat_a1003::entry();
//    pat_a1004::bfs_solve::entry();
//    pat_a1004::dfs_solve::entry();
//    pat_a1005::entry();
//    pat_a1006::entry();
//    pat_a1007::entry();
//    pat_a1008::entry();
//    pat_a1009::entry();
//    pat_a1010::entry();
//    pat_a1011::entry();
//    pat_a1012::entry();
//    pat_a1013::entry();
//    pat_a1014::entry();
//    pat_a1015::entry();
    pat_a1016::entry();
//    pat_a1017::entry();
//    pat_a1018::entry();
//    pat_a1019::entry();
//    pat_a1020::entry();
//    pat_a1021::entry();
//    pat_a1022::entry();
//    pat_a1023::entry();
//    pat_a1024::entry();
//    pat_a1025::entry();
//    pat_a1027::entry();
//    pat_a1028::entry();
//    pat_a1029::entry();
//    pat_a1030::entry();
    return 0;
}
