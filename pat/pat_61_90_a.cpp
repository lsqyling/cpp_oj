//
// Created by shiqing on 2021/5/1.
//
#include <cstdio>
#include <algorithm>
#include <queue>
#include <set>
#include <cstring>
#include <string>
#include <iostream>
#include <map>
#include <cmath>
using std::string;

namespace pat_a1061 {

const char *kDay[7] = {"MON", "TUE", "WED", "THU", "FRI", "SAT", "SUN"};


void Entry()
{
    std::string s1, s2, s3, s4;
    std::cin >> s1 >> s2 >> s3 >> s4;
    int i, j, k;
    for (i = 0; i < s1.size() && i < s2.size(); ++i)
    {
        if (s1[i] == s2[i] && (s1[i] >= 'A' && s1[i] <= 'G'))
        {
            break;
        }
    }
    for (j = i + 1; j < s1.size() && j < s2.size(); ++j)
    {
        if (s1[j] == s2[j])
        {
            if (s1[j] >= 'A' && s1[j] <= 'N') break;
            if (s1[j] >= '0' && s1[j] <= '9') break;
        }
    }
    for (k = 0; k < s3.size() && k < s4.size(); ++k)
    {
        if (s3[k] == s4[k] && isalpha(s3[k])) break;
    }
    printf("%s %02d:%02d", kDay[s1[i] - 'A'], isdigit(s1[j]) ? s1[j] - '0' : 10 + s1[j] - 'A', k);
}
}

namespace pat_a1062 {
constexpr int kN = 100'005;
enum class Type
{
    kSage, kNobleman, kFoolMan, kSmallMan
};
struct People
{
    int id_, virtue_, talent_;
    Type t_;
};

bool operator<(const People &a, const People &b)
{
    if (a.t_ != b.t_)
    {
        return a.t_ < b.t_;
    }
    else if (a.virtue_ + a.talent_ != b.virtue_ + b.talent_)
    {
        return a.virtue_ + a.talent_ > b.virtue_ + b.talent_;
    }
    else if (a.virtue_ != b.virtue_)
    {
        return a.virtue_ > b.virtue_;
    }
    else return a.id_ < b.id_;
}

int L, H;
People all[kN];
int len = 0;

Type JudgePeople(People p)
{
    if (p.virtue_ >= H && p.talent_ >= H)
    {
        return Type::kSage;
    }
    else if (p.virtue_ >= H && p.talent_ < H)
    {
        return Type::kNobleman;
    }
    else if (p.virtue_ < H && p.talent_ < H && p.virtue_ >= p.talent_)
    {
        return Type::kFoolMan;
    }
    else return Type::kSmallMan;
}

void Entry()
{
    int n;
    scanf("%d%d%d", &n, &L, &H);
    People tmp;
    for (int i = 0; i < n; ++i)
    {
        scanf("%d%d%d", &tmp.id_, &tmp.virtue_, &tmp.talent_);
        if (tmp.virtue_ < L || tmp.talent_ < L) continue;
        tmp.t_ = JudgePeople(tmp);
        all[len++] = tmp;
    }
    std::sort(all, all + len);
    printf("%d\n", len);
    for (int i = 0; i < len; ++i)
    {
        printf("%08d %d %d\n", all[i].id_, all[i].virtue_, all[i].talent_);
    }
}
}

namespace pat_a1063 {
constexpr int kN = 51;

std::set<int> all[kN];

double CalcSimilarity(const std::set<int> &a, const std::set<int> &b)
{
    int nt = b.size(), nc = 0;
    for (auto x : a)
    {
        if (b.find(x) != b.end())
        {
            ++nc;
        }
        else ++nt;
    }
    return 1.0 * nc / nt * 100;
}

void Entry()
{
    int n, m, x;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &m);
        for (int j = 0; j < m; ++j)
        {
            scanf("%d", &x);
            all[i].insert(x);
        }
    }
    int query, u, v;
    scanf("%d", &query);
    for (int i = 0; i < query; ++i)
    {
        scanf("%d%d", &u, &v);
        printf("%.1f%%\n", CalcSimilarity(all[u], all[v]));
    }
}
}

namespace pat_a1064 {
constexpr int kN = 1005;

int inputs[kN], CBT[kN];
int n, index = 0;

void InOrder(int root)
{
    if (root > n) return;
    InOrder(root * 2);
    CBT[root] = inputs[index++];
    InOrder(root * 2 + 1);
}

void Entry()
{
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &inputs[i]);
    }
    std::sort(inputs, inputs + n);
    InOrder(1);
    for (int i = 1; i <= n; ++i)
    {
        printf("%d", CBT[i]);
        if (i < n) printf(" ");
    }
}
}

namespace pat_a1065 {
constexpr int kL = 1005;

struct BigInteger
{
    char symbol_ = '\0';
    int data_[kL]{0}, len_ = 0;
};

BigInteger AddOfAbs(BigInteger a, BigInteger b)
{
    BigInteger c;
    int n = a.len_ > b.len_ ? a.len_ : b.len_;
    int r = 0;
    for (int i = 0; i < n; ++i)
    {
        int m = a.data_[i] + b.data_[i];
        c.data_[i] = (r + m) % 10;
        r = (r + m) / 10;
    }
    c.len_ = n;
    if (r > 0)
    {
        c.data_[n] = r;
        ++c.len_;
    }
    return c;
}

bool LessOfAbs(BigInteger a, BigInteger b)
{
    if (a.len_ != b.len_)
    {
        return a.len_ < b.len_;
    }
    else
    {
        for (int i = a.len_ - 1; i >= 0; --i)
        {
            if (a.data_[i] != b.data_[i])
            {
                return a.data_[i] < b.data_[i];
            }
        }
        return false;
    }
}

BigInteger MinusOfAbs(BigInteger a, BigInteger b)
{
    BigInteger c;
    int n = a.len_ > b.len_ ? a.len_ : b.len_;
    if (LessOfAbs(a, b))
    {
        c.symbol_ = '-';
        std::swap(a, b);
    }
    for (int i = 0; i < n; ++i)
    {
        int m = a.data_[i] - b.data_[i];
        c.data_[i] = m;
        if (m < 0)
        {
            c.data_[i] += 10;
            --a.data_[i + 1];
        }
    }
    int j;
    for (j = kL - 1; j >= 0; --j)
    {
        if (c.data_[j]) break;
    }
    c.len_ = j + 1;
    return c;
}

BigInteger Add(BigInteger a, BigInteger b)
{
    if (a.symbol_ == '+' || a.symbol_ == '\0')
    {
        switch (b.symbol_)
        {
            case '\0':
            case '+':
                return AddOfAbs(a, b);
            case '-':
                return MinusOfAbs(a, b);
        }
    }
    else
    {
        switch (b.symbol_)
        {
            case '\0':
            case '+':
                return MinusOfAbs(b, a);
            case '-':
                auto tmp = AddOfAbs(a, b);
                tmp.symbol_ = '-';
                return tmp;
        }
    }
    return {};
}

BigInteger Minus(BigInteger a, BigInteger b)
{
    if (a.symbol_ == '\0' || a.symbol_ == '+')
    {
        switch (b.symbol_)
        {
            case '\0':
            case '+':
                return MinusOfAbs(a, b);
            case '-':
                return AddOfAbs(a, b);
        }
    }
    else
    {
        BigInteger tmp;
        switch (b.symbol_)
        {
            case '\0':
            case '+':
                tmp = AddOfAbs(a, b);
                tmp.symbol_ = '-';
                return tmp;
            case '-':
                return MinusOfAbs(b, a);
        }
    }
    return {};
}

bool Less(BigInteger a, BigInteger b)
{
    BigInteger c = Minus(a, b);
    return c.symbol_ == '-';
}

void RemoveLeftZeros(std::string &s)
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

BigInteger IntegerOf(std::string str)
{
    BigInteger c;
    for (int i = str.size() - 1; i > 0; --i)
    {
        c.data_[c.len_++] = str[i] - '0';
    }
    if (isdigit(str[0]))
    {
        c.data_[c.len_++] = str[0] - '0';
    }
    else
    {
        c.symbol_ = str[0];
    }
    return c;
}

void Entry()
{
    int n;
    std::string sa, sb, sc;
    std::cin >> n;
    for (int i = 1; i <= n; ++i)
    {
        std::cin >> sa >> sb >> sc;
        RemoveLeftZeros(sa);
        RemoveLeftZeros(sb);
        RemoveLeftZeros(sc);
        auto a = IntegerOf(sa), b = IntegerOf(sb), c = IntegerOf(sc);
        printf("Case #%d: %s\n", i, Less(c, Add(a, b)) ? "true" : "false");
    }
}
}

namespace pat_a1066 {
struct Node
{
    explicit Node(int x = 0) : data_(x), height_(1), left_(nullptr), right_(nullptr)
    {
    }

    int data_, height_;
    Node *left_, *right_;
};

int GetHeight(Node *root)
{
    if (root == nullptr) return 0;
    return root->height_;
}

int GetBalanceFactor(Node *root)
{
    return GetHeight(root->left_) - GetHeight(root->right_);
}

void UpdateHeight(Node *root)
{
    root->height_ = std::max(GetHeight(root->left_), GetHeight(root->right_)) + 1;
}

void LeftRotation(Node *&root)
{
    Node *tmp = root->right_;
    root->right_ = tmp->left_;
    tmp->left_ = root;
    UpdateHeight(root);
    UpdateHeight(tmp);
    root = tmp;
}

void RightRotation(Node *&root)
{
    Node *tmp = root->left_;
    root->left_ = tmp->right_;
    tmp->right_ = root;
    UpdateHeight(root);
    UpdateHeight(tmp);
    root = tmp;
}

void Insert(Node *&root, int v)
{
    if (root == nullptr)
    {
        root = new Node(v);
        return;
    }
    if (v < root->data_)
    {
        Insert(root->left_, v);
        UpdateHeight(root);
        if (GetBalanceFactor(root) == 2)
        {
            if (GetBalanceFactor(root->left_) == 1)
            {
                RightRotation(root);
            }
            else if (GetBalanceFactor(root->left_) == -1)
            {
                LeftRotation(root->left_);
                RightRotation(root);
            }
        }
    }
    else
    {
        Insert(root->right_, v);
        UpdateHeight(root);
        if (GetBalanceFactor(root) == -2)
        {
            if (GetBalanceFactor(root->right_) == -1)
            {
                LeftRotation(root);
            }
            else if (GetBalanceFactor(root->right_) == 1)
            {
                RightRotation(root->right_);
                LeftRotation(root);
            }
        }
    }
}

void Entry()
{
    int n, x;
    scanf("%d", &n);
    Node *root = nullptr;
    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &x);
        Insert(root, x);
    }
    printf("%d\n", root->data_);
}
}

namespace pat_a1067 {
constexpr int kN = 100'005;

int pos[kN];

void Entry()
{
    int n, x;
    scanf("%d", &n);
    int left = n - 1, times = 0;
    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &x);
        pos[x] = i;
        if (x && x == i)
        {
            --left;
        }
    }
    int k = 1;
    while (left)
    {
        if (pos[0] == 0)
        {
            while (k < n)
            {
                if (pos[k] != k)
                {
                    std::swap(pos[0], pos[k]);
                    ++times;
                    break;
                }
                ++k;
            }
        }
        while (pos[0] != 0)
        {
            std::swap(pos[0], pos[pos[0]]);
            --left;
            ++times;
        }
    }
    printf("%d\n", times);
}
}

namespace pat_a1068 {
constexpr int kN = 100'005;
constexpr int kV = 105;

int c[kN], dp[kV];
bool choice[kN][kV], table[kN];

void Entry()
{
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &c[i]);
    }
    std::sort(c + 1, c + n + 1, [](auto a, auto b)
    { return a > b; });
    for (int i = 1; i <= n; ++i)
    {
        for (int v = m; v >= c[i]; --v)
        {
            if (dp[v] <= dp[v - c[i]] + c[i])
            {
                dp[v] = dp[v - c[i]] + c[i];
                choice[i][v] = true;
            }
            else
            {
                choice[i][v] = false;
            }
        }
    }
    if (dp[m] != m) printf("No Solution");
    else
    {
        int k = n, num = 0, v = m;
        while (k >= 0)
        {
            if (choice[k][v])
            {
                table[k] = true;
                v -= c[k];
                ++num;
            }
            else
            {
                table[k] = false;
            }
            --k;
        }
        for (int j = n; j >= 1; --j)
        {
            if (table[j])
            {
                printf("%d", c[j]);
                --num;
                if (num) printf(" ");
            }
        }
    }
}
}

namespace pat_a1069 {
constexpr int kL = 4;

int nums[kL];

void TransToArray(int n)
{
    for (int i = 0; i < kL; ++i)
    {
        nums[i] = n % 10;
        n /= 10;
    }
}

int TransToNum()
{
    int ans = 0;
    for (int i = kL - 1; i >= 0; --i)
    {
        ans = ans * 10 + nums[i];
    }
    return ans;
}

void Entry()
{
    int n;
    scanf("%d", &n);
    for (;;)
    {
        TransToArray(n);
        std::sort(nums, nums + kL);
        int max = TransToNum();
        std::sort(nums, nums + kL, [](auto a, auto b)
        { return a > b; });
        int min = TransToNum();
        n = max - min;
        printf("%04d - %04d = %04d\n", max, min, n);
        if (n == 0 || n == 6174) break;
    }
}
}

namespace test {
constexpr int kL = 35;
const char kDigital[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};

char nums[kL], len;

void ToArray(int n, int base)
{
    len = 0;
    do
    {
        nums[len++] = kDigital[n % base];
        n /= base;
    } while (n);
}

void PrintBitOfN(int n, int b)
{
    ToArray(n, b);
    for (int i = len - 1; i >= 0; --i)
    {
        printf("%c", nums[i]);
        if (i > 0) printf(" ");
    }
    printf("\n");
}
}

namespace pat_a1070 {
constexpr int kN = 1005;
const double kEps = 1e-5;

struct MoonCake
{
    double inventory_;
    double value_;
};
auto cmp = [](MoonCake a, MoonCake b)
{
    return a.value_ / a.inventory_ - b.value_ / b.inventory_ > kEps;
};

MoonCake cakes[kN];

void Entry()
{
    int n;
    double demand;
    scanf("%d%lf", &n, &demand);
    for (int i = 0; i < n; ++i)
    {
        scanf("%lf", &cakes[i].inventory_);
    }
    for (int i = 0; i < n; ++i)
    {
        scanf("%lf", &cakes[i].value_);
    }
    std::sort(cakes, cakes + n, cmp);
    double total = 0;
    for (int i = 0; i < n; ++i)
    {
        if (demand >= cakes[i].inventory_)
        {
            demand -= cakes[i].inventory_;
            total += cakes[i].value_;
        }
        else
        {
            total += demand / cakes[i].inventory_ * cakes[i].value_;
            demand = 0;
        }
        if (demand == 0) break;
    }
    printf("%.2f\n", total);
}
}

namespace pat_a1071 {

std::map<std::string, int> count;

void Entry()
{
    std::string text;
    getline(std::cin, text);
    int max_times = 0;
    for (int i = 0; i < text.size(); ++i)
    {
        std::string word;
        while (i < text.size() && isalnum(text[i]))
        {
            word += static_cast<char>(tolower(text[i]));
            ++i;
        }
        if (!word.empty())
        {
            ++count[word];
            if (count.at(word) > max_times)
            {
                max_times = count.at(word);
            }
        }
    }
    for (const auto &item : count)
    {
        if (item.second == max_times)
        {
            std::cout << item.first << " " << max_times << std::endl;
            break;
        }
    }
}
}

namespace pat_a1072 {
constexpr int kV = 1020;
constexpr int kInf = 0x3fff'ffff;

int G[kV][kV], n, m, k, DS;
int d[kV];
bool visit[kV];

void Dijkstra(int s)
{
    std::memset(visit, false, sizeof(visit));
    std::fill(d, d + kV, kInf);
    d[s] = 0;
    for (int i = 0; i < n + m; ++i)
    {
        int u = -1, min = kInf;
        for (int j = 1; j <= n + m; ++j)
        {
            if (!visit[j] && d[j] < min)
            {
                u = j;
                min = d[j];
            }
        }
        if (u == -1) return;
        visit[u] = true;
        for (int v = 1; v <= n + m; ++v)
        {
            if (!visit[v] && G[u][v] != kInf)
            {
                if (d[u] + G[u][v] < d[v])
                {
                    d[v] = d[u] + G[u][v];
                }
            }
        }
    }
}

int GetId(char str[])
{
    int len = strlen(str), id = 0;
    for (int i = 0; i < len; ++i)
    {
        if (str[i] != 'G')
        {
            id = id * 10 + (str[i] - '0');
        }
    }
    return str[0] == 'G' ? n + id : id;
}

void Entry()
{
    scanf("%d%d%d%d", &n, &m, &k, &DS);
    std::fill(G[0], G[0] + kV * kV, kInf);
    char city1[5], city2[5];
    int u, v, w;
    for (int i = 0; i < k; ++i)
    {
        scanf("%s %s %d", city1, city2, &w);
        u = GetId(city1);
        v = GetId(city2);
        G[u][v] = G[v][u] = w;
    }
    double ans_dis = -1, ans_avg = kInf;
    int ans_id = -1;
    for (int i = n + 1; i <= n + m; ++i)
    {
        double dis = kInf, avg = 0;
        Dijkstra(i);
        for (int j = 1; j <= n; ++j)
        {
            if (d[j] > DS)
            {
                dis = -1;
                break;
            }
            if (d[j] < dis) dis = d[j];
            avg += 1.0 * d[j] / n;
        }
        if (dis == -1) continue;
        if (dis > ans_dis)
        {
            ans_id = i;
            ans_dis = dis;
            ans_avg = avg;
        }
        else if (dis == ans_dis && avg < ans_avg)
        {
            ans_id = i;
            ans_avg = avg;
        }
    }
    if (ans_id == -1) printf("No Solution\n");
    else
    {
        printf("G%d\n", ans_id - n);
        printf("%.1f %.1f\n", ans_dis, ans_avg);
    }
}
}

namespace pat_a1073 {
constexpr int kLen = 10'005;

char str[kLen];

string ProcessedScientificNotation(const char s[])
{
    bool is_negative = s[0] == '-';
    int len = strlen(s), j = 1;
    string raw_fractional;
    while (j < len && s[j] != 'E')
    {
        raw_fractional += s[j];
        ++j;
    }
    int exponent;
    sscanf(s + j + 1, "%d", &exponent);
    auto dot_pos = raw_fractional.find('.');
    int dot_left = dot_pos, dot_right = raw_fractional.size() - 1 - dot_pos;
    if (exponent > 0)
    {
        if (exponent < dot_right)
        {
            for (int i = 0; i < exponent; ++i)
            {
                std::swap(raw_fractional[dot_pos + i], raw_fractional[dot_pos + i + 1]);
            }
        }
        else
        {
            raw_fractional.erase(dot_pos, 1);
            int n0 = exponent - dot_right;
            for (int i = 0; i < n0; ++i)
            {
                raw_fractional.push_back('0');
            }
        }
    }
    else
    {
        exponent = -exponent;
        if (exponent < dot_left)
        {
            for (int i = 0; i < exponent; ++i)
            {
                std::swap(raw_fractional[dot_pos - i], raw_fractional[dot_pos - i - 1]);
            }
        }
        else
        {
            raw_fractional.erase(dot_pos, 1);
            int n0 = exponent - dot_left;
            for (int i = 0; i < n0; ++i)
            {
                raw_fractional.insert(raw_fractional.begin(), '0');
            }
            raw_fractional = "0." + raw_fractional;
        }
    }
    return is_negative ? "-" + raw_fractional : raw_fractional;
}

void Entry()
{
    scanf("%s", str);
    string ans = ProcessedScientificNotation(str);
    printf("%s", ans.c_str());
}
}

namespace pat_a1074 {
constexpr int kN = 100'005;

struct Node
{
    int ads_, data_, next_;
};

Node ans[kN], inputs[kN];
int n = 0;

//[s, e)
void Reverse(Node *link, int s, int e)
{
    for (int i = s, j = e - 1; i < j; i++, j--)
    {
        std::swap(link[i], link[j]);
    }
}

void Entry()
{
    int h, N, K;
    scanf("%d%d%d", &h, &N, &K);
    int ads, data, next;
    for (int i = 0; i < N; ++i)
    {
        scanf("%d%d%d", &ads, &data, &next);
        inputs[ads].ads_ = ads;
        inputs[ads].data_ = data;
        inputs[ads].next_ = next;
    }
    while (h != -1)
    {
        ans[n++] = inputs[h];
        h = inputs[h].next_;
    }
    int block = n / K;
    for (int i = 0; i < block; ++i)
    {
        Reverse(ans, i * K, (i + 1) * K);
    }
    for (int j = 0; j < n; ++j)
    {
        if (j < n - 1)
        {
            printf("%05d %d %05d\n", ans[j].ads_, ans[j].data_, ans[j + 1].ads_);
        }
        else
        {
            printf("%05d %d -1\n", ans[j].ads_, ans[j].data_);
        }
    }
}
}

namespace pat_a1075 {
constexpr int kN = 10'005;
constexpr int K = 6;

struct User
{
    int id_;
    int score_[K]{-1, -1, -1, -1, -1, -1};
    int total_score_{0};
    int perfectly_solved_{0};
    bool is_shown{false};
};

bool operator<(const User &a, const User &b)
{
    if (a.total_score_ != b.total_score_)
    {
        return a.total_score_ > b.total_score_;
    }
    else if (a.perfectly_solved_ != b.perfectly_solved_)
    {
        return a.perfectly_solved_ > b.perfectly_solved_;
    }
    else
    {
        return a.id_ < b.id_;
    }
}

User all[kN];
int full[K];

void Entry()
{
    int n, k, m;
    scanf("%d%d%d", &n, &k, &m);
    for (int i = 1; i <= k; ++i)
    {
        scanf("%d", &full[i]);
    }
    int id, p_id, score;
    for (int j = 0; j < m; ++j)
    {
        scanf("%d%d%d", &id, &p_id, &score);
        if (score != -1)
        {
            all[id].is_shown = true;
        }
        if (score == -1 && all[id].score_[p_id] == -1)
        {
            all[id].score_[p_id] = 0;
        }
        if (score == full[p_id] && all[id].score_[p_id] < full[p_id])
        {
            ++all[id].perfectly_solved_;
        }
        if (score > all[id].score_[p_id])
        {
            all[id].score_[p_id] = score;
        }
    }
    for (int i = 1; i <= n; ++i)
    {
        all[i].id_ = i;
        for (int j = 1; j <= k; ++j)
        {
            if (all[i].score_[j] != -1)
            {
                all[i].total_score_ += all[i].score_[j];
            }
        }
    }
    std::sort(all + 1, all + n + 1);
    int r = 1;
    for (int i = 1; i <= n && all[i].is_shown; ++i)
    {
        if (i > 1 && all[i].total_score_ != all[i - 1].total_score_)
        {
            r = i;
        }
        printf("%d %05d %d", r, all[i].id_, all[i].total_score_);
        for (int j = 1; j <= k; ++j)
        {
            if (all[i].score_[j] == -1)
            {
                printf(" -");
            }
            else
            {
                printf(" %d", all[i].score_[j]);
            }
        }
        printf("\n");
    }
}
}

namespace pat_a1076 {
constexpr int kV = 1005;

struct Node
{
    int id_, layer_;
};
std::vector<Node> G[kV];
bool inq[kV];

int Bfs(int s, int L)
{
    std::queue<Node> Q;
    Q.push({s, 0});
    inq[s] = true;
    int cnt = 0;
    while (!Q.empty())
    {
        Node top = Q.front();
        Q.pop();
        int u = top.id_;
        for (auto next : G[u])
        {
            next.layer_ = top.layer_ + 1;
            if (!inq[next.id_] && next.layer_ <= L)
            {
                Q.push(next);
                inq[next.id_] = true;
                ++cnt;
            }
        }
    }
    return cnt;
}

void Entry()
{
    int n, L, followers, id;
    scanf("%d%d", &n, &L);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &followers);
        for (int j = 0; j < followers; ++j)
        {
            scanf("%d", &id);
            G[id].push_back({i, 0});
        }
    }
    int num_query, q_id;
    scanf("%d", &num_query);
    for (int i = 0; i < num_query; ++i)
    {
        scanf("%d", &q_id);
        memset(inq, false, sizeof(inq));
        int forwards = Bfs(q_id, L);
        printf("%d\n", forwards);
    }
}
}

namespace pat_a1077 {
constexpr int kN = 105;
constexpr int kL = 300;

int GetLine(char str[], int n)
{
    int c, len = 0;
    while ((c = getchar()) != EOF)
    {
        str[len++] = c;
        if (c == '\n') break;
    }
    if (c == '\n') str[--len] = '\0';
    if (c == EOF) str[len] = '\0';
    return len;
}

void Reverse(char str[], int s, int e)
{
    for (int i = s, j = e - 1; i < j; ++i, --j)
    {
        std::swap(str[i], str[j]);
    }
}


void Entry()
{
    int n;
    scanf("%d", &n);
    getchar();
    char lines[kN][kL];
    for (int i = 0; i < n; ++i)
    {
        int len = GetLine(lines[i], sizeof(lines[i]));
        Reverse(lines[i], 0, len);
    }
    int i, j, max_suffix = 0;
    for (i = 0; i < strlen(lines[0]); ++i)
    {
        for (j = 1; j < n; ++j)
        {
            if (lines[j][i] != lines[j - 1][i]) goto label;
        }
    }
    label:
    max_suffix = i;
    for (int k = max_suffix - 1; k >= 0; --k)
    {
        printf("%c", lines[0][k]);
    }
    if (max_suffix == 0)
    {
        printf("nai");
    }
}
}

namespace pat_a1078 {
constexpr int kM = 10'005;

bool table[kM];
int t_size;

bool IsPrime(int n)
{
    if (n <= 1) return false;
    int sqrt_n = std::sqrt(n);
    for (int i = 2; i <= sqrt_n; ++i)
    {
        if (n % i == 0) return false;
    }
    return true;
}

int TSize(int m_size)
{
    int i;
    for (i = m_size;; ++i)
    {
        if (IsPrime(i)) break;
    }
    return i;
}

int QuadraticProbing(int n)
{
    int h = n % t_size, pos = -1;
    for (int k = 0; k < t_size; ++k)
    {
        if (table[(h + k * k) % t_size] == false)
        {
            pos = (h + k * k) % t_size;
            table[pos] = true;
            break;
        }
    }
    return pos;
}

int LinearProbing(int n)
{
    int h = n % t_size, pos = -1;
    for (int k = 0; k < t_size; ++k)
    {
        if (table[(h + k) % t_size] == false)
        {
            pos = (h + k) % t_size;
            table[pos] = true;
            break;
        }
    }
    return pos;
}

void Entry()
{
    int m, n, x;
    scanf("%d%d", &m, &n);
    t_size = TSize(m);
    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &x);
        auto id = QuadraticProbing(x);
        if (id == -1) printf("-");
        else printf("%d", id);
        if (i < n - 1) printf(" ");
    }
}
}

namespace pat_a1079 {
constexpr int kN = 10'0005;

struct Node
{
    double data_;
    std::vector<int> child_;
};
Node tree[kN];
double price, r, ans = 0;

void Dfs(int index, int depth)
{
    if (tree[index].child_.empty())
    {
        ans += tree[index].data_ * std::pow(1 + r, depth);
        return;
    }
    for (auto c : tree[index].child_)
    {
        Dfs(c, depth + 1);
    }
}

void Entry()
{
    int n, k, child;
    scanf("%d%lf%lf", &n, &price, &r);
    r /= 100;
    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &k);
        if (k == 0)
        {
            scanf("%lf", &tree[i].data_);
        }
        else
        {
            for (int j = 0; j < k; ++j)
            {
                scanf("%d", &child);
                tree[i].child_.push_back(child);
            }
        }
    }
    Dfs(0, 0);
    printf("%.1f\n", price * ans);
}
}

namespace pat_a1080 {
constexpr int N = 40'005;
constexpr int K = 5;
constexpr int M = 105;

struct student
{
    int ge, gi, sum;
    int rank, id;
    int sch[K];
};

struct school
{
    int quota, stu_num;
    int last_admit;
    std::vector<int> ids;
};

student applicants[N];
school schools[M];

bool operator<(const student &a, const student &b)
{
    if (a.sum != b.sum)
    {
        return a.sum > b.sum;
    }
    else
    {
        return a.ge > b.ge;
    }
}

void admission_procedure(int n, int m, int k)
{
    std::sort(applicants, applicants + n);
    for (int i = 0; i < n; ++i)
    {
        if (i > 0 && applicants[i].sum == applicants[i - 1].sum && applicants[i].ge == applicants[i - 1].ge)
        {
            applicants[i].rank = applicants[i - 1].rank;
        }
        else
        {
            applicants[i].rank = i;
        }
    }
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < k; ++j)
        {
            int sch_id = applicants[i].sch[j];
            int num = schools[sch_id].stu_num;
            int last = schools[sch_id].last_admit;
            if (num < schools[sch_id].quota || (last != -1 && applicants[i].rank == applicants[last].rank))
            {
                schools[sch_id].ids.push_back(i);
                schools[sch_id].last_admit = i;
                ++schools[sch_id].stu_num;
                break;
            }
        }
    }
}

void entry()
{
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 0; i < m; ++i)
    {
        scanf("%d", &schools[i].quota);
        schools[i].stu_num = 0;
        schools[i].last_admit = -1;
    }
    for (int i = 0; i < n; ++i)
    {
        applicants[i].id = i;
        scanf("%d%d", &applicants[i].ge, &applicants[i].gi);
        applicants[i].sum = applicants[i].ge + applicants[i].gi;
        for (int j = 0; j < k; ++j)
        {
            scanf("%d", &applicants[i].sch[j]);
        }
    }
    admission_procedure(n, m, k);
    auto cmp_id = [](int i, int j)
    {
        return applicants[i].id < applicants[j].id;
    };
    for (int i = 0; i < m; ++i)
    {
        if (schools[i].stu_num > 0)
        {
            std::sort(schools[i].ids.begin(), schools[i].ids.end(), cmp_id);
            for (int j = 0; j < schools[i].stu_num; ++j)
            {
                printf("%d", applicants[schools[i].ids[j]].id);
                if (j < schools[i].stu_num - 1)
                {
                    printf(" ");
                }
            }
        }
        printf("\n");

    }

}
}

namespace pat_a1081 {
using int_t = int64_t;

struct fraction
{
    int_t up;
    int_t down;

    fraction() : up(0), down(1)
    {
    }
};

int_t gcd(int_t a, int_t b)
{
    return b == 0 ? a : gcd(b, a % b);
}

int_t abs(int_t a)
{
    return a < 0 ? -a : a;
}

fraction reduce(const fraction &a)
{
    fraction res = a;
    if (res.down < 0)
    {
        res.up = -res.up;
        res.down = -res.down;
    }
    if (res.up == 0)
    {
        res.down = 1;
    }
    else
    {
        int_t d = gcd(abs(a.up), abs(a.down));
        res.up /= d;
        res.down /= d;
    }
    return res;
}


fraction operator+(const fraction &a, const fraction &b)
{
    fraction res;
    res.up = a.up * b.down + b.up * a.down;
    res.down = a.down * b.down;
    return reduce(res);
}

void entry()
{
    int n;
    scanf("%d", &n);
    fraction res, tmp;
    for (int i = 0; i < n; ++i)
    {
        scanf("%ld/%ld", &tmp.up, &tmp.down);
        res = res + tmp;
    }
    int_t a = res.up / res.down;
    int_t b = abs(res.up % res.down);
    if (res.down == 1) printf("%ld", res.up);
    else if (abs(res.up) > abs(res.down))
    {
        printf("%ld %ld/%ld", a, b, res.down);
    }
    else
    {
        printf("%ld/%ld", res.up, res.down);
    }
}
}

namespace pat_a1082 {
const char *zh_num_char[] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
const char *zh_unit_section[] = {"", "A", "B"};
const char *zh_unit_char[] = {"", "C", "D", "E"};
const char *num_to_pinyin[256] = {"ling", "yi", "er", "san", "si", "wu", "liu", "qi", "ba", "jiu"};

void init_num_to_pinyin()
{
    num_to_pinyin['A'] = "Wan";
    num_to_pinyin['B'] = "Yi";
    num_to_pinyin['C'] = "Shi";
    num_to_pinyin['D'] = "Bai";
    num_to_pinyin['E'] = "Qian";
}

void section_to_zh(uint64_t section, std::string &zh_str)
{
    std::string str_ins;
    int unit_pos = 0;
    bool zero = true;
    while (section > 0)
    {
        auto v = section % 10;
        if (v == 0)
        {
            if (!zero)
            {
                zero = true;
                zh_str.insert(0, zh_num_char[v]);
            }
        }
        else
        {
            zero = false;
            str_ins = zh_num_char[v];
            str_ins += zh_unit_char[unit_pos];
            zh_str.insert(0, str_ins);
        }
        ++unit_pos;
        section /= 10;
    }
}

void number_to_zh(uint64_t num, std::string &zh_str)
{
    int unit_pos = 0;
    bool need_zero = false;
    while (num > 0)
    {
        std::string str_ins;
        uint64_t section = num % 10000;
        if (need_zero)
        {
            zh_str.insert(0, zh_num_char[0]);
        }
        section_to_zh(section, str_ins);
        str_ins += (section != 0) ? zh_unit_section[unit_pos] : zh_unit_section[0];
        zh_str.insert(0, str_ins);

        need_zero = (section < 1000) && (section > 0);
        num /= 10000;
        ++unit_pos;
    }
}

void entry()
{
    int64_t n;
    scanf("%ld", &n);
    if (n == 0)
    {
        printf("ling");
        return ;
    }
    bool is_native = false;
    uint64_t num;
    if (n < 0)
    {
        num = -n;
        is_native = true;
    }
    else
    {
        num = n;
    }
    std::string res;
    number_to_zh(num, res);
    if (is_native)
    {
        printf("Fu ");
    }
    init_num_to_pinyin();
    for (int i = 0; i < res.size(); ++i)
    {   if (res[i] <= '9' && res[i] >= '0')
        {
            printf("%s", num_to_pinyin[res[i] - '0']);
        }
        else
        {
            printf("%s", num_to_pinyin[res[i]]);

        }
        if (i < res.size() - 1)
        {
            printf(" ");
        }
    }
}
}


namespace pat_a1083 {
constexpr int N = 105;
constexpr int LEN = 12;

struct student
{
    char name[LEN];
    char id[LEN];
    int grade = -1;
};

student stu[N];

void entry()
{
    int n;
    scanf("%d", &n);
    student tmp;
    for (int i = 0; i < n; ++i)
    {
        scanf("%s%s%d", tmp.name, tmp.id, &tmp.grade);
        stu[tmp.grade] = tmp;
    }

    int left, right;
    scanf("%d%d", &left, &right);

    bool no_one = true;
    for (int i = right; i >= left; --i)
    {
        if (stu[i].grade != -1)
        {
            printf("%s %s\n", stu[i].name, stu[i].id);
            no_one = false;
        }
    }
    if (no_one)
    {
        printf("NONE");
    }
}
}

namespace pat_a1084 {
constexpr int MAX_SIZE = 85;

char str_src[MAX_SIZE];
char str_out[MAX_SIZE];

int table[256];
bool is_printed[256];


int get_line(char *buf, int max_size)
{
    int c, len = 0;
    while ((c = getchar()) != EOF && len < max_size)
    {
        if (c == '\n') break;
        buf[len++] = c;
    }
    buf[len] = '\0';
    return len;
}



void entry()
{
    int len1, len2;
    get_line(str_src, MAX_SIZE);
    get_line(str_out, MAX_SIZE);
    len1 = strlen(str_src);
    len2 = strlen(str_out);
    for (int i = 0; i < len1; ++i)
    {
        ++table[toupper(str_src[i])];
    }
    for (int i = 0; i < len2; ++i)
    {
        --table[toupper(str_out[i])];
    }
    for (int j = 0; j < len1; ++j)
    {
        if (table[toupper(str_src[j])] != 0)
        {
            if (!is_printed[toupper(str_src[j])])
            {
                printf("%c", toupper(str_src[j]));
                is_printed[toupper(str_src[j])] = true;
            }
        }
    }
}
}

namespace pat_a1085 {
constexpr int N = 100'005;

int64_t num[N];

static int max(int a, int b)
{
    return a > b ? a : b;
}

void entry()
{
    int n, p;
    scanf("%d%d", &n, &p);
    for (int i = 0; i < n; ++i)
    {
        scanf("%ld", &num[i]);
    }
    std::sort(num, num + n);

    int count = 1;
    for (int i = 0, j = 0; i < n && j < n; ++i)
    {
        while (j < n && num[j] <= num[i] * p)
        {
            count = max(count, j - i + 1);
            ++j;
        }
    }
    printf("%d\n", count);
}
}

namespace pat_a1086 {
constexpr int N = 35;

struct tree_node
{
    int data;
    tree_node *left;
    tree_node *right;
};

int pre[N], in[N], n;
int stack[N], top = -1;

tree_node *create(int preL, int preR, int inL, int inR)
{
    if (preL > preR)
        return nullptr;

    auto root = new tree_node;
    root->data = pre[preL];
    root->left = root->right = nullptr;

    int k;
    for (k = inL; k <= inR; ++k)
    {
        if (in[k] == pre[preL])
            break;
    }
    int num_left = k - inL;

    root->left = create(preL + 1, preL + num_left, inL, k - 1);
    root->right = create(preL + num_left + 1, preR, k + 1, inR);

    return root;
}

int count = 0;
void postorder(tree_node *root)
{
    if (root == nullptr)
        return ;
    postorder(root->left);
    postorder(root->right);

    printf("%d", root->data);
    ++count;
    if (count < n)
    {
        printf(" ");
    }
}

void entry()
{
    scanf("%d", &n);
    char tmp[5];
    int x, pre_index = 0, in_index = 0;
    for (int i = 0; i < 2 * n; ++i)
    {
        scanf("%s", tmp);
        if (strcmp(tmp, "Push") == 0)
        {
            scanf("%d", &x);
            pre[pre_index++] = x;
            stack[++top] = x;
        }
        else if (strcmp(tmp, "Pop") == 0)
        {
            in[in_index++] = stack[top];
            --top;
        }
    }

    tree_node *root = create(0, n - 1, 0, n - 1);
    postorder(root);
}
}

namespace pat_a1087 {
constexpr int MaxV = 205;
constexpr int INF = 0x3fff'ffff;

char id_city[MaxV][4];
std::map<std::string, int> city_id;

int n, G[MaxV][MaxV], weight[MaxV];
int w[MaxV], d[MaxV], pt[MaxV], num_dist[MaxV], pre[MaxV];
bool visit[MaxV];

void dijkstra(int s)
{
    std::fill(d, d + MaxV, INF);
    for (int i = 0; i < n; ++i)
    {
        pre[i] = i;
    }
    d[s] = 0;
    w[s] = weight[s];
    num_dist[s] = 1;
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
            return;
        visit[u] = true;
        for (int v = 0; v < n; ++v)
        {
            if (G[u][v] != INF && !visit[v])
            {
                if (d[u] + G[u][v] < d[v])
                {
                    d[v] = d[u] + G[u][v];
                    w[v] = w[u] + weight[v];
                    num_dist[v] = num_dist[u];
                    pt[v] = pt[u] + 1;
                    pre[v] = u;
                }
                else if (d[u] + G[u][v] == d[v])
                {
                    num_dist[v] += num_dist[u];
                    if (w[u] + weight[v] > w[v])
                    {
                        w[v] = w[u] + weight[v];
                        pt[v] = pt[u] + 1;
                        pre[v] = u;
                    }
                    else if (w[u] + weight[v] == w[v])
                    {
                        double u_avg = 1.0 * (w[u] + weight[v]) / (pt[u] + 1);
                        double v_avg = 1.0 * w[v] / pt[v];
                        if (u_avg > v_avg)
                        {
                            pt[v] = pt[u] + 1;
                            pre[v] = u;
                        }
                    }
                }
            }
        }
    }
}


static void print_path(int v)
{
    if (v == 0)
    {
        printf("%s", id_city[v]);
        return ;
    }
    print_path(pre[v]);
    printf("->%s", id_city[v]);
}

void entry()
{
    int m;
    fscanf(stdin, "%d%d%s", &n, &m, id_city[0]);
    city_id[id_city[0]] = 0;
    for (int i = 1; i < n; ++i)
    {
        scanf("%s%d", id_city[i], &weight[i]);
        city_id[id_city[i]] = i;
    }
    std::fill(G[0], G[0] + MaxV * MaxV, INF);
    char city1[5], city2[5];
    int x;
    for (int i = 0; i < m; ++i)
    {
        scanf("%s%s%d", city1, city2, &x);
        int u = city_id[city1], v = city_id[city2];
        G[u][v] = G[v][u] = x;
    }
    dijkstra(0);

    int e = city_id["ROM"];
    printf("%d %d %d %d\n", num_dist[e], d[e], w[e], w[e] / pt[e]);
    print_path(e);
}
}

namespace pat_a1088 {
struct Rational
{
    int64_t up;
    int64_t down;
};

int64_t gcd(int64_t a, int64_t b)
{
    return b == 0 ? a : gcd(b, a % b);
}

int64_t abs(int64_t x)
{
    return x < 0 ? -x : x;
}

Rational reduce(const Rational &a)
{
    Rational tmp = a;
    if (tmp.down < 0)
    {
        tmp.up = -tmp.up;
        tmp.down = -tmp.down;
    }
    if (tmp.up == 0)
    {
        tmp.down = 1;
    }
    else
    {
        auto d = gcd(abs(a.up), abs(a.down));
        tmp.up /= d;
        tmp.down /= d;
    }
    return tmp;
}

Rational operator+(const Rational &a, const Rational &b)
{
    Rational tmp;
    tmp.up = a.up * b.down + b.up * a.down;
    tmp.down = a.down * b.down;
    return reduce(tmp);
}

Rational operator-(const Rational &a, const Rational &b)
{
    Rational tmp;
    tmp.up = a.up * b.down - b.up * a.down;
    tmp.down = a.down * b.down;
    return reduce(tmp);
}

Rational operator*(const Rational &a, const Rational &b)
{
    Rational tmp;
    tmp.up = a.up * b.up;
    tmp.down = a.down * b.down;
    return reduce(tmp);
}

Rational operator/(const Rational &a, const Rational &b)
{
    Rational tmp;
    tmp.up = a.up * b.down;
    tmp.down = a.down * b.up;
    return reduce(tmp);
}

std::string format(const Rational &a)
{
    char tmp[35];
    Rational r = reduce(a);
    if (r.down == 1)
    {
        sprintf(tmp, "%ld", r.up);
    }
    else if (abs(r.up) > abs(r.down))
    {
        sprintf(tmp, "%ld %ld/%ld", r.up / r.down, abs(r.up) % abs(r.down), r.down);
    }
    else
    {
        sprintf(tmp, "%ld/%ld", r.up, r.down);
    }
    std::string res(tmp);
    if (r.up < 0)
    {
        res.insert(0, "(");
        res.push_back(')');
    }
    return res;
}

void entry()
{
    Rational a, b;
    scanf("%ld/%ld %ld/%ld", &a.up, &a.down, &b.up, &b.down);

    printf("%s + %s = %s\n", format(a).c_str(), format(b).c_str(), format(a + b).c_str());
    printf("%s - %s = %s\n", format(a).c_str(), format(b).c_str(), format(a - b).c_str());
    printf("%s * %s = %s\n", format(a).c_str(), format(b).c_str(), format(a * b).c_str());

    if (b.up == 0)
    {
        printf("%s / %s = %s\n", format(a).c_str(), format(b).c_str(), "Inf");
    }
    else
    {
        printf("%s / %s = %s\n", format(a).c_str(), format(b).c_str(), format(a / b).c_str());
    }
}
}

namespace pat_a1089 {
constexpr int N = 105;

int arr[N], n;
std::vector<int> last_arr;

void insert_sort(void)
{
    std::vector<int> tmp(arr, arr + n);
    bool flag = false;
    for (int i = 1; i < n; ++i)
    {
        if (i != 1 && tmp == last_arr)
        {
            flag = true;
        }
        int bak = tmp[i], j;
        for (j = i - 1; j >= 0 && tmp[j] > bak; --j)
        {
            tmp[j+1] = tmp[j];
        }
        tmp[j+1] = bak;
        if (flag)
        {
            printf("Insertion Sort\n");
            for (int k = 0; k < n; ++k)
            {
                printf("%d", tmp[k]);
                if (k < n - 1)
                {
                    printf(" ");
                }

            }
        }
    }
}

void merge_sort(void)
{
    std::vector<int> tmp(arr, arr + n);
    bool flag = false;
    for (int step = 2; step / 2 <= n; step *= 2)
    {
        if (step != 2 && tmp == last_arr)
        {
            flag = true;
        }
        for (int i = 0; i < n; i += step)
        {
            std::sort(tmp.begin() + i, tmp.begin() + std::min(i + step, n));
        }
        if (flag)
        {
            printf("Merge Sort\n");
            for (int i = 0; i < n; ++i)
            {
                printf("%d", tmp[i]);
                if (i < n - 1)
                {
                    printf(" ");
                }

            }
        }
    }
}

void entry()
{
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &arr[i]);
    }
    int x;
    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &x);
        last_arr.push_back(x);
    }
    merge_sort();
    insert_sort();
}
}

namespace pat_a1090 {
constexpr int N = 100'005;

std::vector<int> tree[N];

int max_depth = 0, num = 0;
void dfs(int index, int depth)
{
    if (tree[index].empty())
    {
        if (depth > max_depth)
        {
            max_depth = depth;
            num = 1;
        }
        else if (depth == max_depth)
        {
            ++num;
        }
        return ;
    }
    for (int i = 0; i < tree[index].size(); ++i)
    {
        dfs(tree[index][i], depth + 1);
    }
}

void entry()
{
    int n;
    double p, r;
    scanf("%d%lf%lf", &n, &p, &r);
    r /= 100;

    int father, root;
    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &father);
        if (father == -1)
        {
            root = i;
        }
        else
        {
            tree[father].push_back(i);
        }
    }

    dfs(root, 0);
    printf("%.2f %d\n", p * pow((1 + r), max_depth), num);
}
}



int main(int argc, char *argv[])
{
    pat_a1061::Entry();
    pat_a1062::Entry();
    pat_a1063::Entry();
    pat_a1064::Entry();
    pat_a1065::Entry();
    pat_a1066::Entry();
    pat_a1067::Entry();
    pat_a1068::Entry();
    pat_a1069::Entry();
    pat_a1070::Entry();
    pat_a1071::Entry();
    pat_a1072::Entry();
    pat_a1073::Entry();
    pat_a1074::Entry();
    pat_a1075::Entry();
    pat_a1076::Entry();
    pat_a1077::Entry();
    pat_a1078::Entry();
    pat_a1079::Entry();
    pat_a1080::entry();
    pat_a1081::entry();
    pat_a1082::entry();
    pat_a1083::entry();
    pat_a1084::entry();
    pat_a1085::entry();
    pat_a1086::entry();
    pat_a1087::entry();
    pat_a1088::entry();
    pat_a1089::entry();
    pat_a1090::entry();
    return 0;
}
