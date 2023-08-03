//
// Created by shiqing on 2020/5/27.
//
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <string>
#include <cstring>
#include <queue>
#include <unordered_map>
#include <map>
#include <set>
#include <cmath>

using std::string;
using std::cin;

namespace pat_a1001 {
constexpr int N = 10;

int nums[N], len = 0;

void digitsOfNum(int n)
{
    do
    {
        nums[len++] = n % 10;
        n /= 10;
    } while (n);
}

void entry()
{
    int a, b;
    scanf("%d%d", &a, &b);
    int n = a + b, sign = n >> 31;
    if (n < 0) n = -n;
    digitsOfNum(n);
    int cnt = 0;
    for (int i = len - 1; i >= 0; --i)
    {
        if (sign)
        {
            printf("-");
            sign = 0;
        }
        printf("%d", nums[i]);
        if (++cnt % 3 == len % 3)
        {
            if (len > 3 && i > 0) printf(",");
        }
    }
}
}

namespace pat_a1002 {
constexpr int N = 1005;

double p[N];

void entry()
{
    int k, n;
    double a;
    scanf("%d", &k);
    for (int i = 0; i < k; ++i)
    {
        scanf("%d%lf", &n, &a);
        p[n] = a;
    }
    scanf("%d", &k);
    for (int i = 0; i < k; ++i)
    {
        scanf("%d%lf", &n, &a);
        p[n] += a;
    }
    int cnt = 0;
    for (int i = 0; i < N; ++i)
    {
        if (p[i] != 0) ++cnt;
    }
    printf("%d", cnt);
    for (int j = N - 1; j >= 0; --j)
    {
        if (p[j] != 0)
        {
            printf(" %d %.1f", j, p[j]);
        }
    }
}
}

namespace pat_a1003 {
constexpr int N = 505;
constexpr int INF = 0x3fff'ffff;

int G[N][N], weight[N];
bool visit[N];
int d[N], w[N], nums[N];

void dijkstra(int s, int n)
{
    std::fill(d, d + N, INF);
    d[s] = 0;
    w[s] = weight[s];
    nums[s] = 1;
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
                    nums[v] = nums[u];
                    w[v] = w[u] + weight[v];
                }
                else if (d[u] + G[u][v] == d[v])
                {
                    nums[v] += nums[u];
                    if (w[u] + weight[v] > w[v])
                    {
                        w[v] = w[u] + weight[v];
                    }
                }
            }
        }
    }
}

void entry()
{
    int n, m, c1, c2;
    scanf("%d%d%d%d", &n, &m, &c1, &c2);
    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &weight[i]);
    }
    std::fill(G[0], G[0] + N * N, INF);
    for (int j = 0; j < m; ++j)
    {
        int u, v, dis;
        scanf("%d%d%d", &u, &v, &dis);
        G[u][v] = G[v][u] = dis;
    }
    dijkstra(c1, n);
    printf("%d %d", nums[c2], w[c2]);
}
}

namespace pat_a1004 {
constexpr int N = 105;
namespace dfs_solve {
std::vector<int> G[N];
int leaf[N], max_h = 0;

void dfs(int u, int h)
{
    if (max_h < h) max_h = h;
    if (G[u].empty())
    {
        ++leaf[h];
        return;
    }
    for (auto v : G[u])
    {
        dfs(v, h + 1);
    }
}

void entry()
{
    int n, m;
    scanf("%d%d", &n, &m);
    if (n == 0) return;
    for (int i = 0; i < m; ++i)
    {
        int u, k, v;
        scanf("%d%d", &u, &k);
        for (int j = 0; j < k; ++j)
        {
            scanf("%d", &v);
            G[u].push_back(v);
        }
    }
    dfs(1, 0);
    for (int i = 0; i <= max_h; ++i)
    {
        printf("%d", leaf[i]);
        if (i < max_h) printf(" ");
    }
}
}
namespace bfs_solve {
std::vector<int> G[N];
int layer[N], leaf[N], max_h = 0;

void bfs(int root)
{
    std::queue<int> Q;
    Q.push(root);
    while (!Q.empty())
    {
        int u = Q.front();
        Q.pop();
        if (max_h < layer[u]) max_h = layer[u];
        if (G[u].empty())
        {
            ++leaf[layer[u]];
        }
        for (auto v : G[u])
        {
            layer[v] = layer[u] + 1;
            Q.push(v);
        }
    }
}

void entry()
{
    int n, m;
    scanf("%d%d", &n, &m);
    if (n == 0) return;
    for (int i = 0; i < m; ++i)
    {
        int u, k, v;
        scanf("%d%d", &u, &k);
        for (int j = 0; j < k; ++j)
        {
            scanf("%d", &v);
            G[u].push_back(v);
        }
    }
    bfs(1);
    for (int i = 0; i <= max_h; ++i)
    {
        printf("%d", leaf[i]);
        if (i < max_h) printf(" ");
    }
}
}
}

namespace pat_a1005 {
constexpr int N = 105;
const char *ENUMS[10] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

int nums[N], len = 0;

void digitsOf(int n)
{
    do
    {
        nums[len++] = n % 10;
        n /= 10;
    } while (n);
}

void entry()
{
    char str[N];
    scanf("%s", str);
    int L = strlen(str), s = 0;
    for (int i = 0; i < L; ++i)
    {
        s += (str[i] - '0');
    }
    digitsOf(s);
    for (int j = len - 1; j >= 0; --j)
    {
        printf("%s", ENUMS[nums[j]]);
        if (j > 0) printf(" ");
    }
}
}

namespace pat_a1006 {
struct Node
{
    char id_[20];
    int in_, out_;
};
auto cmp_in = [](const Node &a, const Node &b)
{
    return a.in_ < b.in_;
};
auto cmp_out = [](const Node &a, const Node &b)
{
    return a.out_ > b.out_;
};

std::vector<Node> all;

inline int secondsOf(int h, int m, int s)
{
    return h * 3600 + m * 60 + s;
}

void entry()
{
    int n;
    scanf("%d", &n);
    Node tmp;
    int h, m, s;
    for (int i = 0; i < n; ++i)
    {
        scanf("%s%d:%d:%d", tmp.id_, &h, &m, &s);
        tmp.in_ = secondsOf(h, m, s);
        scanf("%d:%d:%d", &h, &m, &s);
        tmp.out_ = secondsOf(h, m, s);
        all.push_back(tmp);
    }
    Node unlock, lock;
    std::sort(all.begin(), all.end(), cmp_in);
    unlock = all[0];
    std::sort(all.begin(), all.end(), cmp_out);
    lock = all[0];
    printf("%s %s", unlock.id_, lock.id_);
}
}

namespace pat_a1007 {
constexpr int N = 10005;

int A[N], dp[N], begin[N];

void entry()
{
    int n;
    scanf("%d", &n);
    bool flag = false;
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &A[i]);
        if (A[i] >= 0) flag = true;
    }
    if (flag == false)
    {
        printf("%d %d %d", 0, A[1], A[n]);
        return;
    }
    dp[0] = dp[1] = A[1];
    begin[1] = 1;
    int e = 1;
    for (int j = 2; j <= n; ++j)
    {
        dp[j] = std::max(A[j], dp[j - 1] + A[j]);
        dp[j] == A[j] ? begin[j] = j : begin[j] = begin[j - 1];
        if (dp[0] < dp[j])
        {
            e = j;
            dp[0] = dp[j];
        }
    }
    printf("%d %d %d", dp[0], A[begin[e]], A[e]);
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
    int t = 0, dif = 0;
    for (int j = 1; j <= n; ++j)
    {
        dif = stop[j] - stop[j - 1];
        dif < 0 ? t += dif * -4 : t += dif * 6;
    }
    t += n * 5;
    printf("%d", t);
}
}

namespace pat_a1009 {
constexpr int N = 2005;

double p[N], ans[N];

void entry()
{
    int k, n;
    double a;
    scanf("%d", &k);
    for (int i = 0; i < k; ++i)
    {
        scanf("%d%lf", &n, &a);
        p[n] = a;
    }
    scanf("%d", &k);
    for (int i = 0; i < k; ++i)
    {
        scanf("%d%lf", &n, &a);
        for (int j = 0; j < N; ++j)
        {
            if (p[j] != 0)
            {
                ans[n + j] += a * p[j];
            }
        }
    }
    int cnt = 0;
    for (int i = 0; i < N; ++i)
    {
        if (ans[i] != 0) ++cnt;
    }
    printf("%d", cnt);
    for (int i = N - 1; i >= 0; --i)
    {
        if (ans[i] != 0)
        {
            printf(" %d %.1f", i, ans[i]);
        }
    }
}
}

namespace pat_a1010 {
constexpr int N = 15;
constexpr long long INF = 0x7f'ff'ff'ff'ff'ff'ff'ffL;

long long equationOfX(char *str, long long radix, long long bound)
{
    int len = strlen(str);
    long long s = 0;
    for (int i = 0; i < len; ++i)
    {
        if ('0' <= str[i] && str[i] <= '9')
        {
            s = s * radix + (str[i] - '0');
        }
        else
        {
            s = s * radix + (str[i] - 'a' + 10);
        }
        if (s < 0 || s > bound) return -1;
    }
    return s;
}

int cmp(char str_n2[], long long radix, long long t)
{
    long long n2 = equationOfX(str_n2, radix, t);
    if (n2 < 0) return 1;
    if (t > n2) return -1;
    else if (t == n2) return 0;
    else return 1;
}

int binarySearch(char str_n2[], long long left, long long right, long long t)
{
    long long mid;
    while (left <= right)
    {
        mid = left + (right - left) / 2;
        int flag = cmp(str_n2, mid, t);
        if (flag == 0) return mid;
        else if (flag == -1) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

int findLargestDigit(char str[])
{
    int x = '0', len = strlen(str);
    for (int i = 0; i < len; ++i)
    {
        if (x < str[i]) x = str[i];
    }
    if ('0' <= x && x <= '9') x = x - '0';
    else x = x - 'a' + 10;
    return x + 1;
}

void entry()
{
    char str_n1[N], str_n2[N];
    int tag, radix;
    scanf("%s%s%d%d", str_n1, str_n2, &tag, &radix);
    if (tag == 2)
    {
        std::swap(str_n1, str_n2);
    }
    long long n1 = equationOfX(str_n1, radix, INF);
    long long left = findLargestDigit(str_n2);
    long long right = std::max(left, n1) + 1;
    long long ans = binarySearch(str_n2, left, right, n1);
    if (ans == -1) printf("Impossible");
    else printf("%lld", ans);
}
}

namespace pat_a1011 {
constexpr int N = 3;
constexpr char R[N] = {'W', 'T', 'L'};

int maxOfThree(double odd[])
{
    int j = 0;
    for (int i = 0; i < N; ++i)
    {
        if (odd[j] < odd[i])
        {
            j = i;
        }
    }
    return j;
}

void entry()
{
    double odd[3], ans = 1;
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            scanf("%lf", &odd[j]);
        }
        int k = maxOfThree(odd);
        printf("%c ", R[k]);
        ans *= odd[k];
    }
    printf("%.2f", (ans * 0.65 - 1) * 2);
}
}

namespace pat_a1012 {
constexpr int N = 2005;
constexpr int K = 4;
const char COURSE[K] = {'A', 'C', 'M', 'E'};

struct Student
{
    char id_[8];
    int score_[K], rank_[K];
};
int cmp_id;
auto cmp = [](const Student &a, const Student &b)
{
    if (a.score_[cmp_id] != b.score_[cmp_id]) return a.score_[cmp_id] > b.score_[cmp_id];
    else return strcmp(a.id_, b.id_) < 0;
};
Student List[N];
std::unordered_map<string, Student> ss;

struct Pair
{
    int rank, course_id;
};

Pair searchBestRank(string id)
{
    auto it_r = ss.find(id);
    if (it_r == ss.end()) return {-1, -1};
    int j = 0;
    for (int i = 0; i < K; ++i)
    {
        if (it_r->second.rank_[i] < it_r->second.rank_[j])
        {
            j = i;
        }
    }
    return {it_r->second.rank_[j], j};
}

void computeBestRank(int n)
{
    for (int i = 0; i < K; ++i)
    {
        cmp_id = i;
        std::sort(List, List + n, cmp);
        int r = 1;
        for (int j = 0; j < n; ++j)
        {
            if (j > 0 && List[j].score_[i] != List[j - 1].score_[i])
            {
                r = j + 1;
            }
            List[j].rank_[i] = r;
        }
    }
    for (int i = 0; i < n; ++i)
    {
        ss[List[i].id_] = List[i];
    }
}

void entry()
{
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++i)
    {
        scanf("%s", List[i].id_);
        int total = 0, score;
        for (int j = 1; j < K; ++j)
        {
            scanf("%d", &score);
            total += score;
            List[i].score_[j] = score;
        }
        List[i].score_[0] = total / 3;
    }
    computeBestRank(n);
    char id[8];
    while (m--)
    {
        scanf("%s", id);
        Pair p = searchBestRank(id);
        if (p.rank == -1) printf("N/A\n");
        else
        {
            printf("%d %c\n", p.rank, COURSE[p.course_id]);
        }
    }
}
}

namespace pat_a1013 {
constexpr int N = 1005;
namespace graph_dfs {
std::vector<int> G[N];
bool visit[N];

void dfs(int u, int p)
{
    if (u == p) return;
    visit[u] = true;
    for (auto v : G[u])
    {
        if (!visit[v])
        {
            dfs(v, p);
        }
    }
}

int countConnectedBlock(int n, int p)
{
    int block = 0;
    for (int i = 1; i <= n; ++i)
    {
        if (i != p && !visit[i])
        {
            dfs(i, p);
            ++block;
        }
    }
    return block;
}

void entry()
{
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 0; i < m; ++i)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        G[u].push_back(v);
        G[v].push_back(u);
    }
    while (k--)
    {
        int p;
        scanf("%d", &p);
        std::memset(visit, false, sizeof(visit));
        int cnt = countConnectedBlock(n, p);
        printf("%d\n", cnt - 1);
    }
}
}
namespace graph_ufs {
std::vector<int> G[N];
int father[N];
bool visit[N];

int findFather(int x)
{
    int a = x;
    while (x != father[x])
    {
        x = father[x];
    }
    while (a != father[a])
    {
        int z = a;
        a = father[a];
        father[z] = x;
    }
    return x;
}

void Union(int a, int b)
{
    int fa_a = findFather(a);
    int fa_b = findFather(b);
    if (fa_a != fa_b)
    {
        father[fa_a] = fa_b;
    }
}

void init()
{
    for (int i = 0; i < N; ++i)
    {
        father[i] = i;
        visit[i] = false;
    }
}

int countConnectedBlock(int n, int p)
{
    int block = 0;
    for (int i = 1; i <= n; ++i)
    {
        if (i == p) continue;
        int fa_i = findFather(i);
        if (!visit[fa_i])
        {
            ++block;
            visit[fa_i] = true;
        }
    }
    return block;
}

void entry()
{
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 0; i < m; ++i)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        G[u].push_back(v);
        G[v].push_back(u);
    }
    while (k--)
    {
        int p;
        scanf("%d", &p);
        init();
        for (int i = 1; i <= n; ++i)
        {
            for (int j = 0; j < G[i].size(); ++j)
            {
                int u = i, v = G[i][j];
                if (u == p || v == p) continue;
                Union(u, v);
            }
        }
        int cnt = countConnectedBlock(n, p);
        printf("%d\n", cnt - 1);
    }
}
}
}

namespace pat_a1014 {
constexpr int N = 25;
constexpr int K = 1005;
constexpr int INF = 0x3fff'ffff;
constexpr int START = 8 * 60;
constexpr int END = 17 * 60;


struct Window
{
    int end_t_, front_end_t_;
    std::queue<int> q_;
};
int cost_time[K], customer_end_t[K];
Window windows[N];

void entry()
{
    int n, m, k, q;
    scanf("%d%d%d%d", &n, &m, &k, &q);
    for (int i = 0; i < k; ++i)
    {
        scanf("%d", &cost_time[i]);
    }
//    init windows
    for (int i = 0; i < n; ++i)
    {
        windows[i].end_t_ = START;
        windows[i].front_end_t_ = START;
    }
//    enqueue
    int in_id = 0;
    for (int i = 0; i < std::min(n * m, k); ++i)
    {
        int w_id = in_id % n;
        windows[w_id].q_.push(in_id);
        windows[w_id].end_t_ += cost_time[in_id];
        if (i < n)
        {
            windows[w_id].front_end_t_ += cost_time[in_id];
        }
        customer_end_t[in_id] = windows[w_id].end_t_;
        ++in_id;
    }
//    processing the remained customers
    for (; in_id < k; ++in_id)
    {
//        find the eariest end of customer
        int w_id = -1, early_end = INF;
        for (int i = 0; i < n; ++i)
        {
            if (windows[i].front_end_t_ < early_end)
            {
                early_end = windows[i].front_end_t_;
                w_id = i;
            }
        }
//        update the window
        auto &w = windows[w_id];
        w.q_.pop();
        w.q_.push(in_id);
        w.end_t_ += cost_time[in_id];
        w.front_end_t_ += cost_time[w.q_.front()];
        customer_end_t[in_id] = w.end_t_;
    }
    while (q--)
    {
        int c_id;
        scanf("%d", &c_id);
        --c_id;
        int end_t = customer_end_t[c_id];
        if (end_t - cost_time[c_id] >= END) printf("Sorry\n");
        else
        {
            printf("%02d:%02d\n", end_t / 60, end_t % 60);
        }
    }
}
}

namespace pat_a1015 {
constexpr int N = 32;

int nums[N], len = 0;

bool isPrime(int n)
{
    if (n == 1 || n == 0) return false;
    int sqr_n = std::sqrt(n);
    for (int i = 2; i <= sqr_n; ++i)
    {
        if (n % i == 0) return false;
    }
    return true;
}

void digitsOf(int n, int d)
{
    len = 0;
    do
    {
        nums[len++] = n % d;
        n /= d;
    } while (n);
}

int reversibleNum(int n, int d)
{
    digitsOf(n, d);
    int s = 0;
    for (int i = 0; i < len; ++i)
    {
        s = s * d + nums[i];
    }
    return s;
}

void entry()
{
    for (;;)
    {
        int n, d;
        scanf("%d", &n);
        if (n < 0) return;
        scanf("%d", &d);
        int rn = reversibleNum(n, d);
        if (isPrime(n) && isPrime(rn))
        {
            printf("Yes\n");
        }
        else printf("No\n");
    }
}
}

namespace pat_a1016 {
constexpr int H = 24, N = 1005, L = 25;
constexpr int ONLINE = 0, OFFLINE = 1;
const char *STATE[2] = {"on-line", "off-line"};

struct Customer
{
    char name_[L];
    int month_, d_, h_, m_;
    int state_;
};
auto cmp = [](const Customer &a, const Customer &b)
{
    if (strcmp(a.name_, b.name_) != 0) return strcmp(a.name_, b.name_) < 0;
    else if (a.d_ != b.d_) return a.d_ < b.d_;
    else if (a.h_ != b.h_) return a.h_ < b.h_;
    else return a.m_ < b.m_;
};
int rates[H];
Customer List[N];

struct Pair
{
    int time;
    double money;
};

Pair elapseTimeAndMoney(const Customer &a, const Customer &b)
{
    int d = a.d_, h = a.h_, m = a.m_;
    int clock = 0, money = 0;
    while (d != b.d_ || h != b.h_ || m != b.m_)
    {
        ++m;
        ++clock;
        money += rates[h];
        if (m == 60)
        {
            ++h;
            m = 0;
        }
        if (h == 24)
        {
            ++d;
            h = 0;
        }
    }
    return {clock, money * 0.01};
}

void entry()
{
    for (int i = 0; i < H; ++i)
    {
        scanf("%d", &rates[i]);
    }
    int n;
    scanf("%d", &n);
    char str[10];
    for (int j = 0; j < n; ++j)
    {
        auto &c = List[j];
        scanf("%s%d:%d:%d:%d%s", c.name_, &c.month_, &c.d_, &c.h_, &c.m_, str);
        if (strcmp(str, STATE[ONLINE]) == 0) c.state_ = ONLINE;
        else c.state_ = OFFLINE;
    }
    std::sort(List, List + n, cmp);
    std::vector<Customer> ans;
    for (int i = 1; i < n; ++i)
    {
        auto &a = List[i - 1], &b = List[i];
        if (strcmp(a.name_, b.name_) == 0 && (a.state_ == ONLINE && b.state_ == OFFLINE))
        {
            ans.push_back(a);
            ans.push_back(b);
        }
    }
    for (int i = 0, j = i; i < ans.size();)
    {
        while (j < ans.size() && strcmp(ans[j].name_, ans[i].name_) == 0) ++j;
        printf("%s %02d\n", ans[i].name_, ans[i].month_);
        double total = 0;
        for (int k = i; k < j; k += 2)
        {
            auto &a = ans[k], &b = ans[k + 1];
            auto r = elapseTimeAndMoney(a, b);
            total += r.money;
            printf("%02d:%02d:%02d %02d:%02d:%02d %d $%.2f\n", a.d_, a.h_, a.m_, b.d_, b.h_, b.m_, r.time, r.money);
        }
        printf("Total amount: $%.2f\n", total);
        i = j;
    }
}
}

namespace pat_a1017 {
constexpr int INF = 0x3fff'ffff;
constexpr int N = 10'005;
constexpr int K = 105;
constexpr int START = 8 * 3600;
constexpr int END = 17 * 3600;

struct Customer
{
    int arr_t_, cost_t_;
};
auto cmp = [](const Customer &a, const Customer &b)
{
    return a.arr_t_ < b.arr_t_;
};

std::vector<Customer> customers;
int end_time[K];

int timeOf(int h, int m, int s)
{
    return h * 3600 + m * 60 + s;
}

void entry()
{
    int n, k;
    scanf("%d%d", &n, &k);
    Customer tmp;
    for (int i = 0; i < n; ++i)
    {
        int h, m, s;
        scanf("%d:%d:%d%d", &h, &m, &s, &tmp.cost_t_);
        tmp.arr_t_ = timeOf(h, m, s);
        tmp.cost_t_ *= 60;
        if (tmp.cost_t_ > 3600) tmp.cost_t_ = 3600;
        if (tmp.arr_t_ > END) continue;
        customers.push_back(tmp);
    }
    for (int j = 0; j < k; ++j)
    {
        end_time[j] = START;
    }
    std::sort(customers.begin(), customers.end(), cmp);
    int wait = 0;
    for (int i = 0; i < customers.size(); ++i)
    {
        int w = -1, early = INF;
        for (int j = 0; j < k; ++j)
        {
            if (end_time[j] < early)
            {
                early = end_time[j];
                w = j;
            }
        }
        if (customers[i].arr_t_ < end_time[w])
        {
            wait += end_time[w] - customers[i].arr_t_;
            end_time[w] += customers[i].cost_t_;
        }
        else
        {
            end_time[w] = customers[i].arr_t_ + customers[i].cost_t_;
        }
    }
    printf("%.1f", wait / 60.0 / customers.size());
}
}

namespace pat_a1018 {
constexpr int N = 505;
constexpr int INF = 0x3fff'ffff;
int G[N][N], weight[N];
int d[N];
bool visit[N];
std::vector<int> pre[N], tmp, path;
int min_take = INF, min_back = INF;

void dijkstra(int s, int n)
{
    std::fill(d, d + n + 1, INF);
    d[s] = 0;
    for (int i = 0; i < n + 1; ++i)
    {
        int u = -1, min = INF;
        for (int j = 0; j < n + 1; ++j)
        {
            if (!visit[j] && d[j] < min)
            {
                min = d[j];
                u = j;
            }
        }
        if (u == -1) return;
        visit[u] = true;
        for (int v = 0; v < n + 1; ++v)
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

void dfs(int v, int st)
{
    if (v == st)
    {
        tmp.push_back(v);
        int take = 0, back = 0;
        for (int i = tmp.size() - 1; i >= 0; --i)
        {
            int u = tmp[i];
            if (weight[u] > 0)
            {
                back += weight[u];
            }
            else
            {
                if (back > std::abs(weight[u]))
                {
                    back -= std::abs(weight[u]);
                }
                else
                {
                    take += std::abs(weight[u]) - back;
                    back = 0;
                }
            }
        }
        if (take < min_take)
        {
            min_take = take;
            min_back = back;
            path = tmp;
        }
        else if (take == min_take)
        {
            if (back < min_back)
            {
                min_back = back;
                path = tmp;
            }
        }
        tmp.pop_back();
        return;
    }
    tmp.push_back(v);
    for (auto u : pre[v])
    {
        dfs(u, st);
    }
    tmp.pop_back();
}

void entry()
{
    int c_max, n, sp, m;
    scanf("%d%d%d%d", &c_max, &n, &sp, &m);
    std::fill(G[0], G[0] + N * N, INF);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &weight[i]);
        weight[i] -= c_max / 2;
    }
    for (int j = 0; j < m; ++j)
    {
        int u, v, t;
        scanf("%d%d%d", &u, &v, &t);
        G[u][v] = G[v][u] = t;
    }
    dijkstra(0, n);
    dfs(sp, 0);
    printf("%d ", min_take);
    for (int i = path.size() - 1; i >= 0; --i)
    {
        printf("%d", path[i]);
        if (i > 0) printf("->");
    }
    printf(" %d", min_back);
}
}

namespace pat_a1019 {
constexpr int N = 35;

int nums[N], len;

void digitsOf(int n, int base)
{
    len = 0;
    do
    {
        nums[len++] = n % base;
        n /= base;
    } while (n);
}

bool isPalindromicNum(int n, int base)
{
    digitsOf(n, base);
    for (int i = 0, j = len - 1; i < j; ++i, --j)
    {
        if (nums[i] != nums[j]) return false;
    }
    return true;
}

void entry()
{
    int n, base;
    scanf("%d%d", &n, &base);
    if (isPalindromicNum(n, base)) printf("Yes\n");
    else printf("No\n");
    for (int i = len - 1; i >= 0; --i)
    {
        printf("%d", nums[i]);
        if (i > 0) printf(" ");
    }
}
}

namespace pat_a1020 {
constexpr int N = 35;

int post[N], in[N];

struct Node
{
    int data_;
    Node *left_, *right_;

    explicit Node(int x = 0) : data_(x), left_(nullptr), right_(nullptr)
    {
    }
};

Node *constructTree(int pL, int pR, int inL, int inR)
{
    if (pL > pR) return nullptr;
    Node *root = new Node(post[pR]);
    int k;
    for (k = inL; k <= inR; ++k)
    {
        if (post[pR] == in[k]) break;
    }
    int n_left = k - inL;
    root->left_ = constructTree(pL, pL + n_left - 1, inL, k - 1);
    root->right_ = constructTree(pL + n_left, pR - 1, k + 1, inR);
    return root;
}

void levelTraversal(Node *root, int n)
{
    if (root == nullptr) return;
    std::queue<Node *> Q;
    Q.push(root);
    while (!Q.empty())
    {
        Node *front = Q.front();
        Q.pop();
        printf("%d", front->data_);
        if (--n > 0) printf(" ");
        if (front->left_) Q.push(front->left_);
        if (front->right_) Q.push(front->right_);
    }
}

void entry()
{
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &post[i]);
    }
    for (int j = 0; j < n; ++j)
    {
        scanf("%d", &in[j]);
    }
    Node *root = constructTree(0, n - 1, 0, n - 1);
    levelTraversal(root, n);
}
}

namespace pat_a1021 {
constexpr int N = 10'005;
constexpr int INF = 0x3fff'ffff;

std::vector<int> G[N];
bool visit[N];
int deepest = 0;
std::vector<int> tmp, ans;

void dfs(int v, int max_h)
{
    if (visit[v]) return;
    if (deepest < max_h)
    {
        tmp.clear();
        tmp.push_back(v);
        deepest = max_h;
    }
    else if (deepest == max_h)
    {
        tmp.push_back(v);
    }
    visit[v] = true;
    for (auto u : G[v])
    {
        dfs(u, max_h + 1);
    }
}

void entry()
{
    int n;
    scanf("%d", &n);
    for (int i = 1; i < n; ++i)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        G[u].push_back(v);
        G[v].push_back(u);
    }
    int block = 0;
    for (int i = 1; i <= n; ++i)
    {
        if (!visit[i])
        {
            dfs(i, 0);
            ++block;
        }
    }
    if (block != 1)
    {
        printf("Error: %d components", block);
    }
    else
    {
        ans = tmp;
        std::memset(visit, false, sizeof(visit));
        dfs(ans[0], 0);
        for (auto u : tmp)
        {
            ans.push_back(u);
        }
        std::sort(ans.begin(), ans.end());
        printf("%d\n", ans[0]);
        for (int i = 1; i < ans.size(); ++i)
        {
            if (ans[i] != ans[i - 1])
            {
                printf("%d\n", ans[i]);
            }
        }
    }
}
}

namespace pat_a1022 {
struct Book
{
    char info_[6][85];
};

bool operator<(const Book &a, const Book &b)
{
    return strcmp(a.info_[0], b.info_[0]) < 0;
}

std::multimap<string, Book> BookStore[5];

int getLine(char *str, int max_n)
{
    int c, len = 0;
    while ((c = getchar()) != EOF && len < max_n)
    {
        str[len++] = c;
        if (c == '\n') break;
    }
    len == 0 ? str[len] = '\0' : str[--len] = '\0';
    return len;
}

void readKeywords(char *str, std::vector<string> &keys)
{
    int len = strlen(str);
    char key[12];
    int k = 0;
    for (int i = 0; i <= len; ++i)
    {
        if (i < len && str[i] != ' ')
        {
            key[k++] = str[i];
        }
        else
        {
            key[k++] = '\0';
            keys.emplace_back(key);
            k = 0;
        }
    }
}


void entry()
{
    int n;
    scanf("%d", &n);
    getchar();
    Book book;
    while (n--)
    {
        for (int i = 0; i < 6; ++i)
        {
            getLine(book.info_[i], sizeof(book.info_[i]));
        }
        for (int i = 1; i < 6; ++i)
        {
            if (i != 3)
            {
                BookStore[i].insert({book.info_[i], book});
            }
        }
        std::vector<string> keys;
        readKeywords(book.info_[3], keys);
        for (const auto &k : keys)
        {
            BookStore[3].insert({k, book});
        }
    }
    int q, k;
    scanf("%d", &q);
    while (q--)
    {
        scanf("%d", &k);
        getchar();
        getchar();
        char ss[100];
        getLine(ss, sizeof(ss));
        printf("%d: %s\n", k, ss);
        auto it = BookStore[k].lower_bound(ss);
        auto end = BookStore[k].upper_bound(ss);
        if (it == end)
        {
            printf("Not Found\n");
        }
        else
        {
            std::set<Book> ids;
            for (; it != end; ++it)
            {
                ids.insert(it->second);
            }
            for (auto iter = ids.begin(); iter != ids.end(); ++iter)
            {
                printf("%s\n", iter->info_[0]);
            }
        }
    }
}
}

namespace pat_a1023 {

string doubleOf(string n)
{
    string s;
    int r = 0, a;
    for (int i = n.size() - 1; i >= 0; --i)
    {
        a = (n[i] - '0') * 2 % 10;
        a += r;
        s.insert(s.begin(), a + '0');
        r = (n[i] - '0') * 2 / 10;
    }
    if (r) s.insert(s.begin(), r + '0');
    return s;
}

int nums[25];

void entry()
{
    string n;
    cin >> n;
    for (int i = 0; i < n.size(); ++i)
    {
        ++nums[n[i] - '0'];
    }
    string m = doubleOf(n);
    for (int j = 0; j < m.size(); ++j)
    {
        --nums[m[j] - '0'];
    }
    bool flag = true;
    for (int k = 0; k < 25; ++k)
    {
        if (nums[k] != 0)
        {
            flag = false;
            break;
        }
    }
    if (flag) printf("Yes\n");
    else printf("No\n");
    printf("%s", m.c_str());
}
}

namespace pat_a1024 {
struct Bign
{
    int d_[1000];
    int len_;

    Bign() : len_(0)
    {
        memset(d_, 0, sizeof(d_));
    }
};

Bign add(Bign a, Bign b)
{
    int r = 0;
    Bign c;
    for (int i = 0; i < a.len_ || i < b.len_; ++i)
    {
        int tmp = a.d_[i] + b.d_[i] + r;
        c.d_[c.len_++] = tmp % 10;
        r = tmp / 10;
    }
    if (r != 0) c.d_[c.len_++] = r;
    return c;
}

Bign convertTo(char *str)
{
    int len = strlen(str);
    Bign c;
    c.len_ = len;
    for (int i = 0; i < len; ++i)
    {
        c.d_[i] = str[len - 1 - i] - '0';
    }
    return c;
}

bool isPalindromicNum(Bign c)
{
    for (int i = 0, j = c.len_ - 1; i < j; ++i, --j)
    {
        if (c.d_[i] != c.d_[j]) return false;
    }
    return true;
}

void print(Bign a)
{
    for (int i = a.len_ - 1; i >= 0; --i)
    {
        printf("%d", a.d_[i]);
    }
}

void entry()
{
    char str[25];
    int T, step = 0;
    scanf("%s%d", str, &T);
    Bign n = convertTo(str);
    while (step < T && !isPalindromicNum(n))
    {
        Bign m = n;
        std::reverse(m.d_, m.d_ + m.len_);
        n = add(n, m);
        ++step;
    }
    print(n);
    printf("\n%d", step);
}
}

namespace pat_a1025 {
constexpr int N = 300 * 100 + 5;
constexpr int K = 305;

struct Node
{
    char id_[15];
    int score_;
    int final_r_, location_, local_r_;
};
auto cmp = [](const Node &a, const Node &b)
{
    if (a.score_ != b.score_) return a.score_ > b.score_;
    else return strcmp(a.id_, b.id_) < 0;
};
Node all[N], local[K];
int len = 0;

void entry()
{
    int n, k;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &k);
        for (int j = 0; j < k; ++j)
        {
            scanf("%s%d", local[j].id_, &local[j].score_);
            local[j].location_ = i;
        }
        std::sort(local, local + k, cmp);
        int r = 1;
        for (int j = 0; j < k; ++j)
        {
            if (i > 0 && local[j].score_ != local[j - 1].score_)
            {
                r = j + 1;
            }
            local[j].local_r_ = r;
            all[len++] = local[j];
        }
    }
    std::sort(all, all + len, cmp);
    printf("%d\n", len);
    int r = 1;
    for (int i = 0; i < len; ++i)
    {
        if (i > 0 && all[i].score_ != all[i - 1].score_)
        {
            r = i + 1;
        }
        all[i].final_r_ = r;
        printf("%s %d %d %d\n", all[i].id_, all[i].final_r_, all[i].location_, all[i].local_r_);
    }
}
}

namespace pat_a1026 {
constexpr int K = 105;
constexpr int INF = 0x3fff'ffff;
constexpr int START = 8 * 3600, END = 21 * 3600;

struct Table
{
    int end_t_, cnt_, is_vip_;
};
struct Player
{
    int arr_t_, start_t_, serve_t_, is_vip_;
};
auto cmp_arr = [](const Player &a, const Player &b)
{
    return a.arr_t_ < b.arr_t_;
};
auto cmp_serving_t = [](const Player &a, const Player &b)
{
    return a.start_t_ < b.start_t_;
};

inline int secondsOf(int h, int m, int s)
{
    return h * 3600 + m * 60 + s;
}

std::vector<Player> players;
Table tables[K];

int nextVipPlayer(int vip_id)
{
    ++vip_id;
    while (vip_id < players.size() && players[vip_id].is_vip_ == 0) ++vip_id;
    return vip_id;
}

void assignTable(int id, int t_id)
{
    auto &p = players[id];
    auto &t = tables[t_id];
    if (p.arr_t_ <= t.end_t_)
    {
        p.start_t_ = t.end_t_;
    }
    else
    {
        p.start_t_ = p.arr_t_;
    }
    t.end_t_ = p.start_t_ + p.serve_t_;
    ++t.cnt_;
}


void entry()
{
    int n;
    scanf("%d", &n);
    Player tmp;
    for (int i = 0; i < n; ++i)
    {
        int h, m, s, play_t, tag;
        scanf("%d:%d:%d %d %d", &h, &m, &s, &play_t, &tag);
        tmp.arr_t_ = secondsOf(h, m, s);
        if (tmp.arr_t_ >= END) continue;
        tmp.serve_t_ = play_t > 120 ? 2 * 3600 : play_t * 60;
        tmp.start_t_ = END;
        tmp.is_vip_ = tag;
        players.push_back(tmp);
    }
    int k, m;
    scanf("%d%d", &k, &m);
//    init tables
    for (int i = 1; i <= k; ++i)
    {
        tables[i].end_t_ = START;
        tables[i].cnt_ = tables[i].is_vip_ = 0;
    }
    for (int j = 0; j < m; ++j)
    {
        int t_id;
        scanf("%d", &t_id);
        tables[t_id].is_vip_ = 1;
    }
//    sort players by arriving time
    std::sort(players.begin(), players.end(), cmp_arr);
    for (int i = 0, vip_i = nextVipPlayer(-1); i < players.size();)
    {
        int t_id = -1, early = INF;
        for (int j = 1; j <= k; ++j)
        {
            if (tables[j].end_t_ < early)
            {
                early = tables[j].end_t_;
                t_id = j;
            }
        }
        if (tables[t_id].end_t_ >= END) break;
        if (players[i].is_vip_ && i < vip_i)
        {
            ++i;
            continue;
        }
        if (tables[t_id].is_vip_)
        {
//            1->
            if (players[i].is_vip_)
            {
                assignTable(i, t_id);
                if (vip_i == i) vip_i = nextVipPlayer(vip_i);
                ++i;
            }
//            2->
            else
            {
                if (vip_i < players.size() && players[vip_i].arr_t_ <= tables[t_id].end_t_)
                {
                    assignTable(vip_i, t_id);
                    vip_i = nextVipPlayer(vip_i);
                }
                else
                {
                    assignTable(i, t_id);
                    ++i;
                }
            }
        }
        else
        {
//            3->
            if (players[i].is_vip_ == 0)
            {
                assignTable(i, t_id);
            }
//            4->
            else
            {
//                find the eariest free vip table
                int vip_t_id = -1, vip_early = INF;
                for (int j = 1; j <= k; ++j)
                {
                    if (tables[j].is_vip_ && tables[j].end_t_ < vip_early)
                    {
                        vip_early = tables[j].end_t_;
                        vip_t_id = j;
                    }
                }
                if (players[i].arr_t_ >= tables[vip_t_id].end_t_)
                {
                    assignTable(i, vip_t_id);

                }
                else
                {
                    assignTable(i, t_id);
                }
                if (vip_i == i) vip_i = nextVipPlayer(vip_i);
            }
            ++i;
        }
    }
    std::sort(players.begin(), players.end(), cmp_serving_t);
    for (int i = 0; i < players.size() && players[i].start_t_ < END; ++i)
    {
        auto &p = players[i];
        int t1 = p.arr_t_, t2 = p.start_t_;
        printf("%02d:%02d:%02d ", t1 / 3600, t1 % 3600 / 60, t1 % 60);
        printf("%02d:%02d:%02d ", t2 / 3600, t2 % 3600 / 60, t2 % 60);
        printf("%.0f\n", std::round((t2 - t1) / 60.0));
    }
    for (int i = 1; i <= k; ++i)
    {
        printf("%d", tables[i].cnt_);
        if (i < k) printf(" ");
    }
}
}

namespace pat_a1027 {

const char SHOW[13] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C'};

int nums[35], len = 0;

void digitsOf(int n)
{
    len = 0;
    do
    {
        nums[len++] = SHOW[n % 13];
        n /= 13;
    } while (n);
}

void entry()
{
    int color;
    printf("%c", '#');
    for (int i = 0; i < 3; ++i)
    {
        scanf("%d", &color);
        digitsOf(color);
        if (len == 1) printf("0");
        for (int j = len - 1; j >= 0; --j)
        {
            printf("%c", nums[j]);
        }
    }
}
}

namespace pat_a1028 {
constexpr int N = 10'0005;

struct Student
{
    char id_[10], name_[10];
    int score_;
};
int C;
auto cmp_c = [](const Student &a, const Student &b)
{
    switch (C)
    {
        case 2:
            if (strcmp(a.name_, b.name_) != 0) return strcmp(a.name_, b.name_) < 0;
            else return strcmp(a.id_, b.id_) < 0;
        case 3:
            if (a.score_ != b.score_) return a.score_ < b.score_;
            else return strcmp(a.id_, b.id_) < 0;
        default:
            return strcmp(a.id_, b.id_) < 0;
    }
};
Student List[N];

void entry()
{
    int n;
    scanf("%d%d", &n, &C);
    for (int i = 0; i < n; ++i)
    {
        scanf("%s%s%d", List[i].id_, List[i].name_, &List[i].score_);
    }
    std::sort(List, List + n, cmp_c);
    for (int j = 0; j < n; ++j)
    {
        printf("%s %s %d\n", List[j].id_, List[j].name_, List[j].score_);
    }
}
}

namespace pat_a1029 {
constexpr int N = 2 * 10'0005;
int s1[N], s2[N];
int s[2 * N];

void entry()
{
    int n1, n2;
    scanf("%d", &n1);
    for (int i = 0; i < n1; ++i)
    {
        scanf("%d", &s1[i]);
    }
    scanf("%d", &n2);
    for (int j = 0; j < n2; ++j)
    {
        scanf("%d", &s2[j]);
    }
    int i, j, k;
    for (i = j = k = 0; i < n1 && j < n2;)
    {
        if (s1[i] < s2[j]) s[k++] = s1[i++];
        else s[k++] = s2[j++];
    }
    while (i < n1) s[k++] = s1[i++];
    while (j < n2) s[k++] = s2[j++];
    printf("%d", s[(k - 1) / 2]);
}
}

namespace pat_a1030 {
constexpr int N = 505;
constexpr int INF = 0x3fff'ffff;

struct Node
{
    int dis_, cost_;
};
Node G[N][N];
bool visit[N];
int d[N], c[N], pre[N];

void dijkstra(int s, int n)
{
    std::fill(d, d + N, INF);
    d[s] = 0;
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
        if (u == -1) return;
        visit[u] = true;
        for (int v = 0; v < n; ++v)
        {
            if (!visit[v] && G[u][v].dis_ != INF)
            {
                if (d[u] + G[u][v].dis_ < d[v])
                {
                    d[v] = d[u] + G[u][v].dis_;
                    c[v] = c[u] + G[u][v].cost_;
                    pre[v] = u;
                }
                else if (d[u] + G[u][v].dis_ == d[v])
                {
                    if (c[u] + G[u][v].cost_ < c[v])
                    {
                        c[v] = c[u] + G[u][v].cost_;
                        pre[v] = u;
                    }
                }
            }
        }
    }
}

void printfPath(int v, int s)
{
    if (v == s)
    {
        printf("%d ", v);
        return;
    }
    printfPath(pre[v], s);
    printf("%d ", v);
}

void entry()
{
    int n, m, s, e;
    scanf("%d%d%d%d", &n, &m, &s, &e);
    std::fill(G[0], G[0] + N * N, Node{INF, INF});
    for (int i = 0; i < m; ++i)
    {
        int u, v, dis, cost;
        scanf("%d%d%d%d", &u, &v, &dis, &cost);
        G[v][u] = G[u][v] = {dis, cost};
    }
    dijkstra(s, n);
    printfPath(e, s);
    printf("%d %d", d[e], c[e]);
}
}

int main(int argc, char *argv[])
{
    pat_a1001::entry();
    pat_a1002::entry();
    pat_a1003::entry();
    pat_a1004::dfs_solve::entry();
    pat_a1004::bfs_solve::entry();
    pat_a1005::entry();
    pat_a1006::entry();
    pat_a1007::entry();
    pat_a1008::entry();
    pat_a1009::entry();
    pat_a1010::entry();
    pat_a1011::entry();
    pat_a1012::entry();
    pat_a1013::graph_dfs::entry();
    pat_a1013::graph_ufs::entry();
    pat_a1014::entry();
    pat_a1015::entry();
    pat_a1016::entry();
    pat_a1017::entry();
    pat_a1018::entry();
    pat_a1019::entry();
    pat_a1020::entry();
    pat_a1021::entry();
    pat_a1022::entry();
    pat_a1023::entry();
    pat_a1024::entry();
    pat_a1025::entry();
    pat_a1026::entry();
    pat_a1027::entry();
    pat_a1028::entry();
    pat_a1029::entry();
    pat_a1030::entry();
    return 0;
}
