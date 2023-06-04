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
#include <stack>
#include <cmath>

using std::string;
using std::cin;
using std::cout;

namespace pat_a1031 {
constexpr int N = 100;

char str[N];

void entry()
{
    scanf("%s", str);
    int n = strlen(str);
    int n1 = (n + 2) / 3, n3 = n1, n2 = n + 2 - n1 - n3;
    for (int i = 0; i < n1; ++i)
    {
        printf("%c", str[i]);
        for (int j = 0; j < n2 - 2; ++j)
        {
            if (i != n1 - 1) printf(" ");
            else printf("%c", str[i + j + 1]);
        }
        printf("%c\n", str[n - 1 - i]);
    }
}
}

namespace pat_a1032 {
constexpr int N = 10'0005;

struct Node
{
    int data_, next_;
};

Node letters[N];

void entry()
{
    int h1, h2, n;
    scanf("%d%d%d", &h1, &h2, &n);
    for (int i = 0; i < n; ++i)
    {
        int id;
        char c;
        int next;
        scanf("%d %c %d", &id, &c, &next);
        letters[id].data_ = c;
        letters[id].next_ = next;
    }
    int n1 = 0, n2 = 0, h = h1;
    while (h != -1)
    {
        h = letters[h].next_;
        ++n1;
    }
    h = h2;
    while (h != -1)
    {
        h = letters[h].next_;
        ++n2;
    }
    int m = n1 - n2, ph1 = h1, ph2 = h2;
    if (m < 0)
    {
        m = -m;
        while (m--)
        {
            ph2 = letters[ph2].next_;
        }
    }
    else
    {
        while (m--) ph1 = letters[ph1].next_;
    }
    while (ph1 != -1)
    {
        if (ph1 == ph2) break;
        ph1 = letters[ph1].next_;
        ph2 = letters[ph2].next_;
    }
    if (ph1 != -1) printf("%05d", ph1);
    else printf("-1");
}
}

namespace pat_a1033 {
constexpr int N = 505;
constexpr int INF = 0x3fff'ffff;

struct Station
{
    double price_, dis_;
};

bool operator<(const Station &a, const Station &b)
{
    return a.dis_ < b.dis_;
}

Station all[N];

void entry()
{
    double C, D, d_avg;
    int n;
    scanf("%lf%lf%lf%d", &C, &D, &d_avg, &n);
    for (int i = 0; i < n; ++i)
    {
        scanf("%lf%lf", &all[i].price_, &all[i].dis_);
    }
    all[n].price_ = 0;
    all[n].dis_ = D;
    std::sort(all, all + n + 1);
    if (all[0].dis_ != 0)
    {
        printf("The maximum travel distance = 0.00");
        return;
    }
    double distance = C * d_avg, total = 0, remain = 0;
    int s;
    for (s = 0; s < n;)
    {
        int next = -1;
        double min_price = INF;
        for (int j = s + 1; j <= n && all[j].dis_ - all[s].dis_ <= distance; ++j)
        {
            if (all[j].price_ < min_price)
            {
                min_price = all[j].price_;
                next = j;
                if (min_price < all[s].price_) break;
            }
        }
        if (next == -1) break;
        double need_oil = (all[next].dis_ - all[s].dis_) / d_avg;
        if (all[next].price_ < all[s].price_)
        {
            if (remain < need_oil)
            {
                total += (need_oil - remain) * all[s].price_;
                remain = 0;
            }
            else remain -= need_oil;
        }
        else
        {
            total += (C - remain) * all[s].price_;
            remain = C - need_oil;
        }
        s = next;
    }
    if (s == n)
    {
        printf("%.2f", total);
    }
    else printf("The maximum travel distance = %.2f", all[s].dis_ + distance);
}
}

namespace pat_a1034 {
constexpr int N = 2005;

bool visit[N];
int G[N][N], weight[N], n = 0;
std::map<string, int> s_to_num, gang;
std::map<int, string> num_to_s;

int change(const string &s)
{
    if (s_to_num.find(s) != s_to_num.end())
    {
        return s_to_num[s];
    }
    else
    {
        s_to_num[s] = n;
        num_to_s[n] = s;
    }
    return n++;
}

void dfs(int u, int &h, int &num, int &total)
{
    ++num;
    visit[u] = true;
    if (weight[u] > weight[h])
    {
        h = u;
    }
    for (int v = 0; v < n; ++v)
    {
        if (G[u][v] > 0)
        {
            total += G[u][v];
            G[v][u] = G[u][v] = 0;
            if (!visit[v])
            {
                dfs(v, h, num, total);
            }
        }
    }
}

void dfsTraversal(int k)
{
    for (int u = 0; u < n; ++u)
    {
        if (!visit[u])
        {
            int h = u, num = 0, total = 0;
            dfs(u, h, num, total);
            if (num > 2 && total > k)
            {
                gang[num_to_s[h]] = num;
            }
        }
    }
}

void entry()
{
    int m, k;
    scanf("%d%d", &m, &k);
    char a[5], b[5];
    int w;
    for (int i = 0; i < m; ++i)
    {
        scanf("%s%s%d", a, b, &w);
        int u = change(a);
        int v = change(b);
        G[u][v] += w;
        G[v][u] += w;
        weight[u] += w;
        weight[v] += w;
    }
    dfsTraversal(k);
    printf("%lu\n", gang.size());
    for (const auto &p : gang)
    {
        printf("%s %d\n", p.first.c_str(), p.second);
    }
}
}

namespace pat_a1035 {
constexpr int N = 1005;

struct Account
{
    char names_[12], password_[12];
};
Account accounts[N];

void entry()
{
    int n;
    scanf("%d", &n);
    std::vector<int> modified;
    for (int i = 0; i < n; ++i)
    {
        scanf("%s%s", accounts[i].names_, accounts[i].password_);
        char *s = accounts[i].password_;
        int len = strlen(s);
        for (int j = 0; j < len; ++j)
        {
            if (s[j] == '1' || s[j] == '0' || s[j] == 'l' || s[j] == 'O')
            {
                modified.push_back(i);
                break;
            }
        }
    }
    int m = modified.size();
    if (m == 0)
    {
        printf("There %s %d %s and no account is modified", n > 1 ? "are" : "is", n, n > 1 ? "accounts" : "account");
        return;
    }
    printf("%d\n", m);
    for (auto i : modified)
    {
        char *s = accounts[i].password_;
        while (*s)
        {
            switch (*s)
            {
                case '1':
                    *s = '@';
                    break;
                case '0':
                    *s = '%';
                    break;
                case 'l':
                    *s = 'L';
                    break;
                case 'O':
                    *s = 'o';
                    break;
                default:;
            }
            ++s;
        }
        printf("%s %s\n", accounts[i].names_, accounts[i].password_);
    }
}
}

namespace pat_a1036 {

struct Student
{
    char name_[12], gender_, id_[12];
    int grade_;
};
auto cmp_male = [](const Student &a, const Student &b)
{
    if (a.gender_ != b.gender_)
    {
        return a.gender_ > b.gender_;
    }
    else return a.grade_ < b.grade_;
};
auto cmp_female = [](const Student &a, const Student &b)
{
    if (a.gender_ != b.gender_)
    {
        return a.gender_ < b.gender_;
    }
    else return a.grade_ > b.grade_;
};

void entry()
{
    int n;
    scanf("%d", &n);
    std::vector<Student> all;
    Student stu;
    for (int i = 0; i < n; ++i)
    {
        scanf("%s %c %s %d", stu.name_, &stu.gender_, stu.id_, &stu.grade_);
        all.push_back(stu);
    }
    std::sort(all.begin(), all.end(), cmp_female);
    Student female = all[0];
    std::sort(all.begin(), all.end(), cmp_male);
    Student male = all[0];
    bool flag = false;
    if (female.gender_ != 'F')
    {
        printf("Absent\n");
        flag = true;
    }
    else printf("%s %s\n", female.name_, female.id_);
    if (male.gender_ != 'M')
    {
        printf("Absent\n");
        flag = true;
    }
    else printf("%s %s\n", male.name_, male.id_);
    if (flag) printf("NA");
    else printf("%d", female.grade_ - male.grade_);
}
}

namespace pat_a1037 {
constexpr int N = 100'005;

long coupons[N], products[N];

void entry()
{
    int nc, np;
    scanf("%d", &nc);
    for (int i = 0; i < nc; ++i)
    {
        scanf("%ld", &coupons[i]);
    }
    scanf("%d", &np);
    for (int j = 0; j < np; ++j)
    {
        scanf("%ld", &products[j]);
    }
    auto greater = [](long a, long b)
    { return a > b; };
    std::sort(coupons, coupons + nc, greater);
    std::sort(products, products + np, greater);
    long money = 0;
    for (int i = 0; i < nc && i < np; ++i)
    {
        if (coupons[i] > 0 && products[i] > 0)
        {
            money += coupons[i] * products[i];
        }
    }
    for (int i = nc - 1, j = np - 1; i >= 0 && j >= 0; --j, --i)
    {
        if (coupons[i] < 0 && products[j] < 0)
        {
            money += coupons[i] * products[j];
        }
    }
    printf("%ld", money);
}
}

namespace pat_a1038 {
constexpr int N = 10'005;

string nums[N];

auto cmp = [](const string &a, const string &b)
{
    return a + b < b + a;
};

void entry()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i)
    {
        cin >> nums[i];
    }
    std::sort(nums, nums + n, cmp);
    string ans;
    for (int j = 0; j < n; ++j)
    {
        ans += nums[j];
    }
    auto pos = ans.find_first_not_of('0');
    if (pos == string::npos) cout << 0;
    else
    {
        ans = ans.substr(pos);
        cout << ans;
    }
}
}

namespace pat_a1039 {

std::multimap<string, int> registered_courses;

void entry()
{
    int n, k;
    scanf("%d%d", &n, &k);
    char name[5];
    for (int j = 0; j < k; ++j)
    {
        int c_num, s;
        scanf("%d%d", &c_num, &s);
        for (int i = 0; i < s; ++i)
        {
            scanf("%s", name);
            registered_courses.insert({name, c_num});
        }
    }
    for (int i = 0; i < n; ++i)
    {
        scanf("%s", name);
        auto it = registered_courses.lower_bound(name), end = registered_courses.upper_bound(name);
        std::set<int> indices;
        for (; it != end; ++it)
        {
            indices.insert(it->second);
        }
        printf("%s %lu", name, indices.size());
        for (auto index : indices)
        {
            printf(" %d", index);
        }
        printf("\n");
    }
}
}

namespace pat_a1040 {
constexpr int N = 1024;

char str[N];
//dp[i][j] means that str[i, j] is a symmetric string?
bool dp[N][N];

int getLine(char *buf, int max_n)
{
    int c, len = 0;
    while ((c = getchar()) != EOF && len < max_n)
    {
        buf[len++] = c;
        if (c == '\n') break;
    }
    if (len == 0 || c == EOF) buf[len] = '\0';
    else buf[--len] = '\0';
    return len;
}

void entry()
{
    int len = getLine(str, sizeof(str));
    int maxL = 1;
    for (int i = 0; i < len; ++i)
    {
        dp[i][i] = true;
        if (i < len - 1)
        {
            if (str[i] == str[i + 1])
            {
                dp[i][i + 1] = true;
                maxL = 2;
            }
        }
    }
    for (int L = 3; L <= len; ++L)
    {
        for (int i = 0; i < len + 1 - L; ++i)
        {
            int j = i + L - 1;
            if (str[i] == str[j] && dp[i + 1][j - 1])
            {
                dp[i][j] = true;
                maxL = L;
            }
        }
    }
    printf("%d", maxL);
}
}

namespace pat_a1041 {
constexpr int N = 100'005;

int nums[N], table[N];

void entry()
{
    int n, e;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &e);
        nums[i] = e;
        ++table[e];
    }
    int bet_n = -1;
    for (int j = 0; j < n; ++j)
    {
        if (table[nums[j]] == 1)
        {
            bet_n = nums[j];
            break;
        }
    }
    if (bet_n != -1) printf("%d", bet_n);
    else printf("None");
}
}

namespace pat_a1042 {
constexpr int N = 55;
const char CARD[6] = {'S', 'H', 'C', 'D', 'J'};

void entry()
{
    int t;
    scanf("%d", &t);
    int indices[N], src[N];
    for (int j = 1; j < N; ++j)
    {
        scanf("%d", &indices[j]);
        src[j] = j;
    }
    while (t--)
    {
        int tmp[N];
        for (int i = 1; i < N; ++i)
        {
            tmp[indices[i]] = src[i];
        }
        for (int i = 1; i < N; ++i)
        {
            src[i] = tmp[i];
        }
    }
    for (int i = 1; i < N; ++i)
    {
        int r = src[i] % 13, q = src[i] / 13;
        r == 0 ? r = 13, --q : r;
        printf("%c%d", CARD[q], r);
        if (i < N - 1) printf(" ");
    }
}
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

std::vector<int> src_pre;

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

void preOrder(Node *root, std::vector<int> &s_pre)
{
    if (root)
    {
        s_pre.push_back(root->data_);
        preOrder(root->left_, s_pre);
        preOrder(root->right_, s_pre);
    }
}

void changeToMirrorBST(Node *&root)
{
    if (root)
    {
        changeToMirrorBST(root->left_);
        changeToMirrorBST(root->right_);
        std::swap(root->left_, root->right_);
    }
}

void postOrder(Node *root, std::vector<int> &s_post)
{
    if (root)
    {
        postOrder(root->left_, s_post);
        postOrder(root->right_, s_post);
        s_post.push_back(root->data_);
    }
}

void entry()
{
    int n, x;
    scanf("%d", &n);
    Node *root = nullptr;
    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &x);
        src_pre.push_back(x);
        insert(root, x);
    }
    std::vector<int> pre, m_pre, post, m_post;
    preOrder(root, pre);
    if (pre == src_pre)
    {
        printf("YES\n");
        postOrder(root, post);
        for (int i = 0; i < post.size(); ++i)
        {
            printf("%d", post[i]);
            if (i < post.size() - 1) printf(" ");
        }
    }
    else
    {
        changeToMirrorBST(root);
        preOrder(root, m_pre);
        if (m_pre == src_pre)
        {
            printf("YES\n");
            postOrder(root, m_post);
            for (int i = 0; i < m_post.size(); ++i)
            {
                printf("%d", m_post[i]);
                if (i < m_post.size() - 1) printf(" ");
            }
        }
        else printf("NO");
    }
}
}

namespace pat_a1044 {
constexpr int N = 100'005;
constexpr int INF = 0x3fff'ffff;
int values[N];

struct Pair
{
    int i_, j_;
};

void entry()
{
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &values[i]);
    }
    std::vector<Pair> probably;
    int s = 0, min_s = INF;
    for (int i = 1, j; i <= n; ++i)
    {
        s = 0;
        j = i;
        while (j <= n && s < m)
        {
            s += values[j];
            ++j;
        }
        if (s - m < 0) break;
        if (s - m <= min_s)
        {
            min_s = s - m;
            probably.push_back({i, j - 1});
            if (min_s == 0)
            {
                printf("%d-%d\n", i, j - 1);
            }
        }
    }
    if (min_s > 0)
    {
        int t;
        for (auto &p : probably)
        {
            t = 0;
            for (int i = p.i_; i <= p.j_; ++i)
            {
                t += values[i];
            }
            if (t - m == min_s)
            {
                printf("%d-%d\n", p.i_, p.j_);
            }
        }
    }
}
}

namespace pat_a1045 {
constexpr int C = 205, N = 10'005;
namespace LIS {
int hash_table[C];
int A[N], len = 0, dp[N];

void entry()
{
    int n, m, x;
    scanf("%d%d", &n, &m);
    memset(hash_table, -1, sizeof(hash_table));
    for (int i = 0; i < m; ++i)
    {
        scanf("%d", &x);
        hash_table[x] = i;
    }
    scanf("%d", &n);
    for (int j = 0; j < n; ++j)
    {
        scanf("%d", &x);
        if (hash_table[x] >= 0)
        {
            A[len++] = hash_table[x];
        }
    }
//    LIS
    int max_n = 0;
    for (int i = 0; i < len; ++i)
    {
        dp[i] = 1;
        for (int j = 0; j < i; ++j)
        {
            if (A[j] <= A[i] && dp[i] < dp[j] + 1)
            {
                dp[i] = dp[j] + 1;
            }
        }
        if (max_n < dp[i]) max_n = dp[i];
    }
    printf("%d", max_n);
}
}
namespace LCS {
int A[C], B[N], dp[C][N];

void entry()
{
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; ++i)
    {
        scanf("%d", &A[i]);
    }
    scanf("%d", &n);
    for (int j = 1; j <= n; ++j)
    {
        scanf("%d", &B[j]);
    }
//    LCS
    for (int i = 0; i <= m; ++i)
    {
        dp[i][0] = 0;
    }
    for (int j = 0; j <= n; ++j)
    {
        dp[0][j] = 0;
    }
    for (int i = 1; i <= m; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            int max_tmp = dp[i - 1][j] > dp[i][j - 1] ? dp[i - 1][j] : dp[i][j - 1];
            A[i] == B[j] ? dp[i][j] = max_tmp + 1 : dp[i][j] = max_tmp;
        }
    }
    printf("%d", dp[m][n]);
}
}
}

namespace pat_a1046 {
constexpr int N = 100'005;

int d[N];

int distanceOf(int u, int v, int n)
{
    int s = 0;
    if (u < v)
    {
        for (int i = u; i < v; ++i)
        {
            s += d[i];
        }
    }
    else
    {
        for (int i = u; i <= n; ++i)
        {
            s += d[i];
        }
        for (int i = 1; i < v; ++i)
        {
            s += d[i];
        }
    }
    return s;
}

void entry()
{
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &d[i]);
    }
    int m, u, v;
    scanf("%d", &m);
    while (m--)
    {
        scanf("%d%d", &u, &v);
        int s1 = distanceOf(u, v, n);
        int s2 = distanceOf(v, u, n);
        int s = s1 < s2 ? s1 : s2;
        printf("%d\n", s);
    }
}
}

namespace pat_a1047 {
constexpr int N = 40'005;
constexpr int K = 2550;

char all[N][5];
std::vector<int> course[K];

auto cmp = [](int a, int b)
{
    return strcmp(all[a], all[b]) < 0;
};

void entry()
{
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++i)
    {
        int k, c;
        scanf("%s%d", all[i], &k);
        for (int j = 0; j < k; ++j)
        {
            scanf("%d", &c);
            course[c].push_back(i);
        }
    }
    for (int i = 1; i <= m; ++i)
    {
        auto &ss = course[i];
        printf("%d %lu\n", i, ss.size());
        std::sort(ss.begin(), ss.end(), cmp);
        for (auto &e : ss)
        {
            printf("%s\n", all[e]);
        }
    }
}
}

namespace pat_a1048 {
constexpr int N = 100'005;

int values[N];

void entry()
{
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &values[i]);
    }
    std::sort(values, values + n);
    int i, j;
    for (i = 0, j = n - 1; i < j;)
    {
        auto s = values[i] + values[j];
        if (s < m) ++i;
        else if (s > m) --j;
        else break;
    }
    if (i == j) printf("No Solution");
    else printf("%d %d", values[i], values[j]);
}
}

namespace pat_a1049 {

void entry()
{
    int n, a = 1, ans = 0;
    int left, right, now;
    scanf("%d", &n);
    while (n / a)
    {
        left = n / (a * 10);
        now = n / a % 10;
        right = n % a;
        if (now == 0) ans += left * a;
        else if (now == 1) ans += left * a + right + 1;
        else ans += (left + 1) * a;
        a *= 10;
    }
    printf("%d", ans);
}
}

namespace pat_a1050 {
constexpr int N = 10'005;

char s1[N], s2[N];
bool table[256];

int getLine(char *buf, int max_n)
{
    int c, len = 0;
    while ((c = getchar()) != EOF && len < max_n)
    {
        buf[len++] = c;
        if (c == '\n') break;
    }
    if (c == EOF || len == 0) buf[len] = '\0';
    else buf[--len] = '\0';
    return len;
}

void entry()
{
    int n1 = getLine(s1, sizeof(s1));
    int n2 = getLine(s2, sizeof(s2));
    for (int i = 0; i < n2; ++i)
    {
        table[s2[i]] = true;
    }
    for (int j = 0; j < n1; ++j)
    {
        if (!table[s1[j]]) printf("%c", s1[j]);
    }
}
}

namespace pat_a1051 {
constexpr int N = 1005;

int pop_s[N];
int S[N], top = -1;

void entry()
{
    int m, n, k;
    scanf("%d%d%d", &m, &n, &k);
    while (k--)
    {
        top = -1;
        for (int i = 0; i < n; ++i)
        {
            scanf("%d", &pop_s[i]);
        }
        int j = 0;
        bool flag = true;
        for (int i = 1; i <= n; ++i)
        {
            S[++top] = i;
            if (top + 1 > m)
            {
                flag = false;
                break;
            }
            while (top != -1 && S[top] == pop_s[j])
            {
                --top;
                ++j;
            }
        }
        if (top == -1 && flag)
        {
            printf("YES\n");
        }
        else printf("NO\n");
    }
}
}

namespace pat_a1052 {
constexpr int N = 1000'005;

struct Node
{
    int ads_, key_, next_;
};

bool operator<(const Node &a, const Node &b)
{
    return a.key_ < b.key_;
}

Node List[N];

void entry()
{
    int n, h;
    scanf("%d%d", &n, &h);
    for (int i = 0; i < n; ++i)
    {
        int ads, k, next;
        scanf("%d%d%d", &ads, &k, &next);
        List[ads].ads_ = ads;
        List[ads].key_ = k;
        List[ads].next_ = next;
    }
    std::vector<Node> list;
    while (h != -1)
    {
        list.push_back(List[h]);
        h = List[h].next_;
    }
    std::sort(list.begin(), list.end());
    int sz = list.size(), i;
    if (sz) printf("%d %05d\n", sz, list[0].ads_);
    else
    {
        printf("%d -1", sz);
        return;
    }
    for (i = 0; i < sz - 1; ++i)
    {
        printf("%05d %d %05d\n", list[i].ads_, list[i].key_, list[i + 1].ads_);
    }
    printf("%05d %d -1", list[i].ads_, list[i].key_);
}
}

namespace pat_a1053 {
constexpr int N = 105;

struct Node
{
    int weight_;
    std::vector<int> child_;
};

Node tree[N];
int path[N];

auto cmp = [](int a, int b)
{
    return tree[a].weight_ > tree[b].weight_;
};

void dfs(int index, int num, int sum, int S)
{
    if (sum > S) return;
    if (sum == S)
    {
        if (!tree[index].child_.empty()) return;
        for (int i = 0; i < num; ++i)
        {
            printf("%d", tree[path[i]].weight_);
            if (i < num - 1) printf(" ");
            else printf("\n");
        }
        return;
    }
    for (int i = 0; i < tree[index].child_.size(); ++i)
    {
        auto child = tree[index].child_[i];
        path[num] = child;
        dfs(child, num + 1, sum + tree[child].weight_, S);
    }
}

void entry()
{
    int n, m, S;
    scanf("%d%d%d", &n, &m, &S);
    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &tree[i].weight_);
    }
    int id, k, child;
    for (int i = 0; i < m; ++i)
    {
        scanf("%d%d", &id, &k);
        for (int j = 0; j < k; ++j)
        {
            scanf("%d", &child);
            tree[id].child_.push_back(child);
        }
        std::sort(tree[id].child_.begin(), tree[id].child_.end(), cmp);
    }
    path[0] = 0;
    dfs(0, 1, tree[0].weight_, S);
}
}

namespace pat_a1054 {
std::map<int, int> count;

void entry()
{
    int m, n;
    scanf("%d%d", &m, &n);
    int e, x = 0;
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            scanf("%d", &e);
            ++count[e];
            if (count[e] > n * m / 2)
            {
                x = e;
            }
        }
    }
    printf("%d", x);
}
}

namespace pat_a1055 {
constexpr int N = 100'005;
constexpr int M = 100;

struct Billionaire
{
    char name_[10];
    int age_, net_;
};

auto cmp = [](const Billionaire &a, const Billionaire &b)
{
    if (a.net_ != b.net_)
    {
        return a.net_ > b.net_;
    }
    else if (a.age_ != b.age_)
    {
        return a.age_ < b.age_;
    }
    else return strcmp(a.name_, b.name_) < 0;
};
Billionaire all[N], valid[N];
int num_age[M];


void entry()
{
    int n, k;
    scanf("%d%d", &n, &k);
    for (int i = 0; i < n; ++i)
    {
        scanf("%s%d%d", all[i].name_, &all[i].age_, &all[i].net_);
    }
    std::sort(all, all + n, cmp);
    int valid_n = 0;
    for (int i = 0; i < n; ++i)
    {
        if (num_age[all[i].age_] < M)
        {
            ++num_age[all[i].age_];
            valid[valid_n++] = all[i];
        }
    }
    int m, min, max;
    for (int i = 1; i <= k; ++i)
    {
        scanf("%d%d%d", &m, &min, &max);
        printf("Case #%d:\n", i);
        int printed_n = 0;
        for (int j = 0; j < valid_n && printed_n < m; ++j)
        {
            if (valid[j].age_ >= min && valid[j].age_ <= max)
            {
                printf("%s %d %d\n", valid[j].name_, valid[j].age_, valid[j].net_);
                ++printed_n;
            }
        }
        if (printed_n == 0)
        {
            printf("None");
        }
    }
}
}

namespace pat_a1056 {
constexpr int N = 1005;

struct Mouse
{
    int weight_, rank_;
};
Mouse mice[N];

void entry()
{
    int np, ng;
    scanf("%d%d", &np, &ng);
    for (int i = 0; i < np; ++i)
    {
        scanf("%d", &mice[i].weight_);
    }
    std::queue<int> Q;
    for (int i = 0; i < np; ++i)
    {
        int t;
        scanf("%d", &t);
        Q.push(t);
    }
    int tmp = np, group;
    while (Q.size() != 1)
    {
        tmp % ng == 0 ? group = tmp / ng : group = tmp / ng + 1;
        for (int i = 0; i < group; ++i)
        {
            int k = Q.front();
            for (int j = 0; j < ng; ++j)
            {
                if (i * ng + j >= tmp) break;
                int front = Q.front();
                if (mice[front].weight_ > mice[k].weight_)
                {
                    k = front;
                }
                mice[front].rank_ = group + 1;
                Q.pop();
            }
            Q.push(k);
        }
        tmp = group;
    }
    mice[Q.front()].rank_ = 1;
    for (int i = 0; i < np; ++i)
    {
        printf("%d", mice[i].rank_);
        if (i < np - 1) printf(" ");
    }
}
}

namespace pat_a1057 {
constexpr int N = 100'005;
constexpr int SN = 316;

std::stack<int> S;
int block[SN], table[N];

void peekMedian(int K)
{
    int sum = 0, idx = 0;
    while (sum + block[idx] < K)
    {
        sum += block[idx++];
    }
    int num = idx * SN;
    while (sum + table[num] < K)
    {
        sum += table[num++];
    }
    printf("%d\n", num);
}

void push(int x)
{
    S.push(x);
    ++block[x / SN];
    ++table[x];
}

void pop()
{
    int x = S.top();
    S.pop();
    --block[x / SN];
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
        if (strcmp(cmd, "Push") == 0)
        {
            scanf("%d", &x);
            push(x);
        }
        else if (strcmp(cmd, "Pop") == 0)
        {
            if (S.empty())
            {
                printf("Invalid\n");
            }
            else
            {
                pop();
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
                int k = S.size();
                k % 2 ? k = (k + 1) / 2 : k /= 2;
                peekMedian(k);
            }
        }
    }
}
}

namespace pat_a1058 {
constexpr int kL = 29;
constexpr int kM = 17;

struct Hogwarts
{
    int high_, mid_, low_;
};

Hogwarts HogwartsAdd(Hogwarts a, Hogwarts b)
{
    Hogwarts c;
    c.low_ = (a.low_ + b.low_) % kL;
    int r = (a.low_ + b.low_) / kL;
    c.mid_ = (r + a.mid_ + b.mid_) % kM;
    r = (r + a.mid_ + b.mid_) / kM;
    c.high_ = r + a.high_ + b.high_;
    return c;
}

void Entry()
{
    Hogwarts a, b;
    scanf("%d.%d.%d %d.%d.%d", &a.high_, &a.mid_, &a.low_, &b.high_, &b.mid_, &b.low_);
    Hogwarts c = HogwartsAdd(a, b);
    printf("%d.%d.%d\n", c.high_, c.mid_, c.low_);
}
}

namespace pat_a1059 {
constexpr int kN = 100'005;

int primes[kN], len = 0;

struct Factor
{
    int elem_, cnt_;
};

Factor factors[10];
int num = 0;

bool IsPrime(int n)
{
    if (n == 0 || n == 1) return false;
    int sqrt_n = std::sqrt(n);
    for (int i = 2; i <= sqrt_n; ++i)
    {
        if (n % i == 0) return false;
    }
    return true;
}

void CalcPrimes()
{
    for (int i = 2; i < kN; ++i)
    {
        if (IsPrime(i))
        {
            primes[len++] = i;
        }
    }
}

void CalcFactors(int n)
{
    int sqrt_n = std::sqrt(n);
    for (int i = 0; i < len && primes[i] <= sqrt_n; ++i)
    {
        if (n % primes[i] == 0)
        {
            factors[num].elem_ = primes[i];
            factors[num].cnt_ = 0;
            while (n % primes[i] == 0)
            {
                ++factors[num].cnt_;
                n /= factors[num].elem_;
            }
            ++num;
        }
        if (n == 1) break;
    }
    if (n != 1)
    {
        factors[num].elem_ = n;
        factors[num].cnt_ = 1;
        ++num;
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
    CalcPrimes();
    CalcFactors(n);
    printf("%d=", n);
    for (int i = 0; i < num; ++i)
    {
        if (i > 0) printf("*");
        printf("%d", factors[i].elem_);
        if (factors[i].cnt_ > 1)
        {
            printf("^%d", factors[i].cnt_);
        }
    }
}
}

namespace pat_a1060 {
struct StandardDecimal
{
    string decimal_;
    int base_;
};

bool operator==(const StandardDecimal &a, const StandardDecimal &b)
{
    return a.decimal_ == b.decimal_ && a.base_ == b.base_;
}

void RemoveLeftZeros(string &s)
{
    for (auto it = s.begin(); it != s.end();)
    {
        if (*it == '0')
        {
            s.erase(it);
        }
        else break;
    }
}

void AddDot(string &s)
{
    auto pos = s.find('.');
    if (pos == string::npos) s.insert(s.end(), '.');
}

void RemoveDot(string &s)
{
    auto pos = s.find('.');
    if (pos != string::npos)
    {
        s.erase(s.begin() + pos);
    }
}

StandardDecimal ProcessDecimal(string &s, int n)
{
    StandardDecimal d;
    RemoveLeftZeros(s);
    AddDot(s);
    int j = 0;
    while (s[j] != '.') ++j;
    if (j == 0)
    {
        int i = 1;
        for (; i < s.size();)
        {
            if (s[i] == '0') ++i;
            else break;
        }
        if (i == s.size()) j = 0;
        else j = -i + 1;
    }
    d.base_ = j;
    RemoveDot(s);
    RemoveLeftZeros(s);
    for (int i = 0; i < n; ++i)
    {
        s.push_back('0');
    }
    s.erase(s.begin() + n, s.end());
    d.decimal_ = s;
    return d;
}

void Entry()
{
    int n;
    string s1, s2;
    std::cin >> n >> s1 >> s2;
    auto r1 = ProcessDecimal(s1, n);
    auto r2 = ProcessDecimal(s2, n);
    if (r1 == r2)
    {
        printf("YES 0.%s*10^%d", r1.decimal_.c_str(), r1.base_);
    }
    else
    {
        printf("NO 0.%s*10^%d 0.%s*10^%d", r1.decimal_.c_str(), r1.base_, r2.decimal_.c_str(), r2.base_);
    }
}
}


int main(int argc, char *argv[])
{
    pat_a1031::entry();
    pat_a1032::entry();
    pat_a1033::entry();
    pat_a1034::entry();
    pat_a1035::entry();
    pat_a1036::entry();
    pat_a1037::entry();
    pat_a1038::entry();
    pat_a1039::entry();
    pat_a1040::entry();
    pat_a1041::entry();
    pat_a1042::entry();
    pat_a1043::entry();
    pat_a1044::entry();
    pat_a1045::LIS::entry();
    pat_a1045::LCS::entry();
    pat_a1046::entry();
    pat_a1047::entry();
    pat_a1048::entry();
    pat_a1049::entry();
    pat_a1050::entry();
    pat_a1051::entry();
    pat_a1052::entry();
    pat_a1053::entry();
    pat_a1054::entry();
    pat_a1055::entry();
    pat_a1056::entry();
    pat_a1057::entry();
    pat_a1058::Entry();
    pat_a1059::Entry();
    pat_a1060::Entry();
    return 0;
}