#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <iostream>
#include <queue>
#include <string>

namespace pat_a1152 {
constexpr int N = 1005;

char num[N];

//[left, right)
int cut_num(int left, int right)
{
    int s = 0;
    for (int i = left; i < right; ++i)
    {
        s = s * 10 + (num[i] - '0');
    }
    return s;
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


void entry()
{
    int n, k;
    scanf("%d%d%s", &n, &k, num);
    bool is_404 = true;
    for (int i = 0; i < n - k + 1; ++i)
    {
        int s = cut_num(i, i + k);
        if (is_prime(s))
        {
            for (int j = i; j < i + k; ++j)
                printf("%c", num[j]);
            is_404 = false;
            break;
        }
    }
    if (is_404)
        printf("404");
}
}

namespace pat_a1153 {
constexpr int N = 10'005;

struct card
{
    char register_id[15];
    int score;
    char level;
    int site;
    int date;
    int testee_num;
};

card list[N];
int n;
auto cmp_level = [](card a, card b)
{
    if (a.score != b.score)
        return a.score > b.score;
    else
        return strcmp(a.register_id, b.register_id) < 0;
};

void statistics(std::vector<card> &by_level, std::vector<card> &by_site, std::vector<card> &by_date,
                char level, int site, int date)
{
    for (int i = 0; i < n; ++i)
    {
        if (list[i].level == level)
            by_level.push_back(list[i]);
        if (list[i].site == site)
            by_site.push_back(list[i]);
        if (list[i].date == date)
            by_date.push_back(list[i]);
    }
}

void print_level(int case_num, char level, std::vector<card> &by_level)
{
    printf("Case %d: 1 %c\n", case_num, level);
    std::sort(by_level.begin(), by_level.end(), cmp_level);
    if (by_level.empty())
    {
        printf("NA\n");
        return ;
    }
    for (auto &item : by_level)
        printf("%s %d\n", item.register_id, item.score);
}

void print_site(int case_num, int site, std::vector<card> &by_site)
{
    printf("Case %d: 2 %d\n", case_num, site);
    int nt = by_site.size(), ns = 0;
    for (auto &item : by_site)
        ns += item.score;
    if (nt != 0)
        printf("%d %d\n", nt, ns);
    else
        printf("NA\n");
}

void print_date(int case_num, int date, std::vector<card> &by_date)
{
    printf("Case %d: 3 %06d\n", case_num, date);
    if (by_date.empty())
    {
        printf("NA\n");
        return ;
    }
    auto cmp_site = [](card a, card b)
    {
        return a.site < b.site;
    };
    std::sort(by_date.begin(), by_date.end(), cmp_site);
    struct node
    {
        int site, num;
    };
    std::vector<node> result;
    for (int i = 0, j = i; i < by_date.size(); )
    {
        while (j < by_date.size() && by_date[i].site == by_date[j].site)
            ++j;
        result.push_back({by_date[i].site, j - i});
        i = j;
    }
    auto cmp_num = [](node a, node b)
    {
        if (a.num != b.num)
            return a.num > b.num;
        else
            return a.site < b.site;
    };
    std::sort(result.begin(), result.end(), cmp_num);
    for (auto &item : result)
        printf("%d %d\n", item.site, item.num);
}

int num_of_range(char *str, int left, int right)
{
    int s = 0;
    for (int i = left; i <= right; ++i)
        s = s * 10 + (str[i] - '0');
    return s;
}

void decode_register_id(char *str, int score, card &tmp)
{
    strcpy(tmp.register_id, str);
    tmp.level = str[0];
    tmp.score = score;
    tmp.site = num_of_range(str, 1, 3);
    tmp.date = num_of_range(str, 4, 9);
    tmp.testee_num = num_of_range(str, 10, 12);
}

bool judge_legal(const card &tmp)
{
    return (100 < tmp.site && tmp.site < 1000)
            && (0 <= tmp.score && tmp.score <= 100)
            && (0 <= tmp.testee_num && tmp.testee_num < 1000);
}

void entry()
{
    int m;
    scanf("%d%d", &n, &m);
    char id[15];
    int score, len = 0;
    card tmp;
    for (int i = 0; i < n; ++i)
    {
        scanf("%s%d", id, &score);
        decode_register_id(id, score, tmp);
        if (judge_legal(tmp))
            list[len++] = tmp;
    }
    n = len;
    for (int i = 1; i <= m; ++i)
    {
        int type;
        scanf("%d", &type);
        std::vector<card> by_level, by_site, by_date;
        switch (type)
        {
            case 1:
            {
                char term;
                getchar();
                scanf("%c", &term);
                statistics(by_level, by_site, by_date, term, -1, -1);
                print_level(i, term, by_level);
                break;
            }
            case 2:
            {
                int term;
                scanf("%d", &term);
                statistics(by_level, by_site, by_date, -1, term, -1);
                print_site(i, term, by_site);
                break;
            }
            case 3:
            {
                int term;
                scanf("%d", &term);
                statistics(by_level, by_site, by_date, -1, -1, term);
                print_date(i, term, by_date);
                break;
            }
            default:
                exit(1);
        }
    }
}
}

namespace pat_a1154 {
constexpr int N = 10'005;

std::vector<int> G[N];
int n;



bool is_k_coloring(const std::vector<int> &colors)
{
    for (int u = 0; u < n; ++u)
    {
        for (auto v : G[u])
            if (colors[u] == colors[v])
                return false;
    }
    return true;
}

void entry()
{
    int m;
    scanf("%d%d", &n, &m);
    int u, v;
    while (m--)
    {
        scanf("%d%d", &u, &v);
        G[u].push_back(v);
        G[v].push_back(u);
    }
    scanf("%d", &m);
    while (m--)
    {
        std::vector<int> colors;
        std::set<int> count;
        int c;
        for (int i = 0; i < n; ++i)
        {
            scanf("%d", &c);
            colors.push_back(c);
            count.insert(c);
        }
        if (is_k_coloring(colors))
            printf("%zu-coloring\n", count.size());
        else
            printf("No\n");
    }
}
}

namespace pat_a1155 {
constexpr int N = 1005;

int tree[N], n;

bool is_max_heap(int index)
{
    if (index > n)
        return true;
    if (2 * index <= n)
    {
        if (tree[index] < tree[2*index])
            return false;
    }
    if (2 * index + 1 <= n)
    {
        if (tree[index] < tree[2*index+1])
            return false;
    }
    return is_max_heap(2 * index) && is_max_heap(2 * index + 1);
}

bool is_min_heap(int index)
{
    if (index > n)
        return true;
    if (2 * index <= n)
        if (tree[index] > tree[2*index])
            return false;
    if (2 * index + 1 <= n)
        if (tree[index] > tree[2*index+1])
            return false;
    return is_min_heap(2 * index) && is_min_heap(2 * index + 1);
}

void dfs(int index, std::vector<int> &path)
{
    if (index > n)
        return ;
    if (2 * index > n)
    {
        path.push_back(tree[index]);
        for (int i = 0; i < path.size(); ++i)
        {
            printf("%d", path[i]);
            if (i < path.size() - 1)
                printf(" ");
            else
                printf("\n");
        }
        path.pop_back();
        return ;
    }
    path.push_back(tree[index]);
    dfs(index * 2 + 1, path);
    dfs(index * 2, path);
    path.pop_back();
}

void entry()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &tree[i]);

    std::vector<int> path;
    dfs(1, path);
    if (is_max_heap(1))
        printf("Max Heap\n");
    else if (is_min_heap(1))
        printf("Min Heap\n");
    else
        printf("Not Heap\n");
}
}

namespace pat_a1156 {

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

bool is_sexy_num(int n)
{
    bool sexy_n = false;
    if (is_prime(n))
    {
        if (is_prime(n - 6))
            sexy_n = true;
        else if (is_prime(n + 6))
            sexy_n = true;
    }
    return sexy_n;
}


void entry()
{
    int n;
    scanf("%d", &n);
    bool sexy_num = false;
    if (is_prime(n))
    {
        if (is_prime(n - 6))
        {
            printf("Yes\n%d", n - 6);
            sexy_num = true;
        }
        else if (is_prime(n + 6))
        {
            printf("Yes\n%d", n);
            sexy_num = true;
        }
    }
    if (!sexy_num)
    {
        int i;
        for (i = n + 1; ; ++i)
        {
            if (is_sexy_num(i))
                break;
        }
        printf("No\n%d", i);
    }
}
}

namespace pat_a1157 {
constexpr int N = 100'005;

using std::string;

struct guest
{
    char id[20];
    int birthday;
    bool is_alumni;
};

std::map<string, bool> alumni;

guest list[N];

auto cmp = [](guest a, guest b)
{
    if (a.is_alumni != b.is_alumni)
        return a.is_alumni > b.is_alumni;
    else
        return a.birthday < b.birthday;
};

int get_birthday(char *id)
{
    int sum = 0;
    for (int i = 6; i <= 13; ++i)
        sum = sum * 10 + (id[i] - '0');
    return sum;
}


void entry()
{
    int n, m;
    scanf("%d", &n);
    char id[20];
    for (int i = 0; i < n; ++i)
    {
        scanf("%s", id);
        alumni[id] = true;
    }
    scanf("%d", &m);
    for (int i = 0; i < m; ++i)
    {
        scanf("%s", list[i].id);
        list[i].birthday = get_birthday(list[i].id);
        list[i].is_alumni = alumni[list[i].id];
    }

    int sum = 0;
    for (int i = 0; i < m; ++i)
    {
        sum += list[i].is_alumni;
    }
    std::sort(list, list + m, cmp);
    printf("%d\n%s\n", sum, list[0].id);
}
}

namespace pat_a1158 {
constexpr int N = 1005;

int G[N][N], n;

int father[N];
std::set<int> gang[N];

void init_father()
{
    for (int i = 0; i < N; ++i)
        father[i] = i;
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
    {
        if (fa < fb)
            father[fb] = fa;
        else
            father[fa] = fb;
    }
}


bool is_suspect(int u, int k)
{
    int short_calls = 0;
    int receive_calls = 0;
    for (int v = 1; v <= n; ++v)
    {
        if (G[u][v] != 0)
        {
            if (G[u][v] <= 5)
            {
                ++short_calls;
                if (G[v][u] != 0)
                    ++receive_calls;
            }
        }
    }
    return short_calls > k && receive_calls <= 0.2 * short_calls;
}

void print_gang(int i)
{
    int num = 0;
    for (auto e : gang[i])
    {
        printf("%d", e);
        if (++num < gang[i].size())
            printf(" ");
    }
    printf("\n");
}

void check_gangs(const std::vector<int> &bad_guys)
{
    for (int i = 0; i < bad_guys.size(); ++i)
    {
        for (int j = i + 1; j < bad_guys.size(); ++j)
        {
            int u = bad_guys[i], v = bad_guys[j];
            if (G[u][v] != 0 && G[v][u] != 0)
                union_(u, v);
        }
    }
    for (auto u : bad_guys)
    {
        int fa = find_father(u);
        gang[fa].insert(u);
    }
}

void entry()
{
    int k, m;
    scanf("%d%d%d", &k, &n, &m);
    while (m--)
    {
        int u, v, t;
        scanf("%d%d%d", &u, &v, &t);
        G[u][v] += t;
    }
    std::vector<int> bad_guys;
    for (int u = 1; u <= n; ++u)
    {
        if (is_suspect(u, k))
            bad_guys.push_back(u);
    }
    init_father();
    check_gangs(bad_guys);
    if (bad_guys.empty())
    {
        printf("None\n");
        return ;
    }
    for (int i = 1; i <= n; ++i)
    {
        if (!gang[i].empty())
            print_gang(i);
    }
}
}

namespace pat_a1159 {
constexpr int N = 35;
using std::string;

struct bnode
{
    int data, layer;
    bnode *left, *right;
    bnode *parent = nullptr;
};

int post[N], in[N], n;
std::map<int, bnode *> data_search;
bool is_full_tree = true;



bnode *built_tree(int layer, int postL, int postR, int inL, int inR)
{
    if (inL > inR)
        return nullptr;
    bnode *root = new bnode;
    root->data = post[postR];
    root->layer = layer;
    data_search[root->data] = root;
    int i;
    for (i = inL; i <= inR; ++i)
        if (post[postR] == in[i])
            break;
    int num_left = i - inL;

    root->left = built_tree(layer + 1, postL, postL + num_left - 1, inL, i - 1);
    root->right = built_tree(layer + 1, postL + num_left, postR - 1, i + 1, inR);
    if (root->left != nullptr)
        root->left->parent = root;
    if (root->right != nullptr)
        root->right->parent = root;

    if (root->left != nullptr)
        if (root->right == nullptr)
            is_full_tree = false;
    if (root->right != nullptr)
        if (root->left == nullptr)
            is_full_tree = false;
    return root;
}

bool is_root(int data)
{
    return data == post[n-1];
}


bool is_sibling(int a, int b)
{
    bnode *pa = data_search[a];
    bnode *pb = data_search[b];
    return (pa != nullptr && pb != nullptr)
            && (pa->parent == pb->parent);
}

bool is_parent(int a, int b)
{
    bnode *pa = data_search[a];
    bnode *pb = data_search[b];
    return (pa && pb) && (pa == pb->parent);
}

bool is_left(int a, int b)
{
    bnode *pa = data_search[a];
    bnode *pb = data_search[b];
    return (pa && pb) && (pa == pb->left);
}

bool is_right(int a, int b)
{
    bnode *pa = data_search[a];
    bnode *pb = data_search[b];
    return (pa && pb) && (pa == pb->right);
}


bool is_same_level(int a, int b)
{
    bnode *pa = data_search[a];
    bnode *pb = data_search[b];

    return (pa && pb ) && (pa->layer == pb->layer);
}


void entry()
{
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &post[i]);
    }
    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &in[i]);
    }
    bnode *root = built_tree(1, 0, n - 1, 0, n - 1);
    int m;
    scanf("%d", &m);
    while (m--)
    {
        string line;
        do
        {
            std::getline(std::cin, line);
        } while (line.empty());

        int a, b;
        bool yes = false;
        if (line.find("root") != string::npos)
        {
            sscanf(line.c_str(), "%d is the root", &a);
            yes = root->data == a;
        }
        else if (line.find("siblings") != string::npos)
        {
            sscanf(line.c_str(), "%d and %d are siblings", &a, &b);
            yes = is_sibling(a, b);
        }
        else if (line.find("parent") != string::npos)
        {
            sscanf(line.c_str(), "%d is the parent of %d", &a, &b);
            yes = is_parent(a, b);
        }
        else if (line.find("left") != string::npos)
        {
            sscanf(line.c_str(), "%d is the left child of %d", &a, &b);
            yes = is_left(a, b);
        }
        else if (line.find("right") != string::npos)
        {
            sscanf(line.c_str(), "%d is the right child of %d", &a, &b);
            yes = is_right(a, b);
        }
        else if (line.find("same") != string::npos)
        {
            sscanf(line.c_str(), "%d and %d are on the same level", &a, &b);
            yes = is_same_level(a, b);
        }
        else if (line.find("full") != string::npos)
        {
            yes = is_full_tree;
        }
        else
            exit(1);

        if (yes)
            printf("Yes\n");
        else
            printf("No\n");
    }
}
}

namespace pat_a1160 {
constexpr int N = 10;

int seq[N], k, m;

int sum_of_digit(int n)
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

bool is_forever_num(int x, int &n)
{
    if (m != sum_of_digit(x))
        return false;
    n = sum_of_digit(x + 1);
    int p = gcd(m, n);
    if (!is_prime(p))
        return false;
    return p > 2;
}

struct node
{
    int n, a;
};

auto cmp = [](node a, node b)
{
    if (a.n != b.n)
        return a.n < b.n;
    return a.a < b.a;
};

int seq_of_num()
{
    int sum = 0;
    for (int i = 0; i < k; ++i)
    {
        sum = sum * 10 + seq[i];
    }
    return sum;
}

void dfs(std::vector<node> &res, int index, int digit, int sum)
{
    if (index >= k || sum > m)
        return ;
    if (sum + 9 * (k - index - 1) < m)
        return ;
    seq[index] = digit;
    if (sum == m && index == k - 1)
    {
        int forever_n = seq_of_num();
        int n;
        if (is_forever_num(forever_n, n))
            res.push_back({n, forever_n});
        return ;
    }
    for (int i = 0; i < 10; ++i)
        dfs(res, index + 1, i, sum + i);
}


void print_case(int i)
{
    std::vector<node> res;
    printf("Case %d\n", i);
    for (int j = 1; j < 10; ++j)
    {
        dfs(res, 0, j, j);
    }
    std::sort(res.begin(), res.end(), cmp);
    if (res.empty())
    {
        printf("No Solution\n");
        return ;
    }
    for (auto e : res)
        printf("%d %d\n", e.n, e.a);
}

void entry()
{
    int s;
    scanf("%d", &s);
    for (int i = 1; i <= s; ++i)
    {
        scanf("%d%d", &k, &m);
        memset(seq, 0, sizeof(seq));
        print_case(i);
    }
}
}

namespace pat_a1161 {
constexpr int N = 100'005;

struct node
{
    int addr, data, next;
};

node list[N];
std::vector<node> list1, list2;

void entry()
{
    int h1, h2, n;
    scanf("%d%d%d", &h1, &h2, &n);
    int addr, data, next;
    for (int i = 0; i < n; ++i)
    {
        scanf("%d%d%d", &addr, &data, &next);
        list[addr].addr = addr;
        list[addr].data = data;
        list[addr].next = next;
    }
    int p = h1;
    while (p != -1)
    {
        list1.push_back(list[p]);
        p = list[p].next;
    }
    p = h2;
    while (p != -1)
    {
        list2.push_back(list[p]);
        p = list[p].next;
    }
    if (list2.size() >= 2 * list1.size())
        std::swap(list1, list2);
    std::vector<node> list3;
    std::reverse(list2.begin(), list2.end());

    int i, j;
    for (i = j = 0; i < list1.size() && j < list2.size(); ++i, ++j)
    {
        list3.push_back(list1[i]);
        ++i;
        if (i < list1.size())
            list3.push_back(list1[i]);
        list3.push_back(list2[j]);
    }
    if (i == list1.size())
    {
        while (j < list2.size())
            list3.push_back(list2[j++]);
    }
    if (j == list2.size())
    {
        while (i < list1.size())
            list3.push_back(list1[i++]);
    }
    for (i = 0; i < list3.size() - 1; ++i)
    {
        printf("%05d %d %05d\n", list3[i].addr, list3[i].data, list3[i+1].addr);
    }
    printf("%05d %d -1\n", list3[i].addr, list3[i].data);
}
}

namespace pat_a1162 {
constexpr int N = 25;

struct node
{
    char data[15];
    int left, right;
};

node tree[N];
bool visit[N];
int n;

void postorder(int root)
{
    if (root == -1)
        return;
    if (tree[root].left == -1)
    {
        printf("(");
        printf("%s", tree[root].data);
        postorder(tree[root].right);
        printf(")");
    }
    else
    {
        printf("(");
        postorder(tree[root].left);
        postorder(tree[root].right);
        printf("%s", tree[root].data);
        printf(")");
    }
}

void dfs(int index)
{
    if (index == -1)
        return;
    if (visit[index])
        return;
    visit[index] = true;
    dfs(tree[index].left);
    dfs(tree[index].right);
}

int find_root()
{
    for (int i = 1, j; i <= n; ++i)
    {
        memset(visit, false, sizeof(visit));
        dfs(i);
        for (j = 1; j <= n; ++j)
            if (!visit[j])
                break;
        if (j == n + 1)
            return i;
    }
    return -1;
}

void entry()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%s%d%d", tree[i].data, &tree[i].left, &tree[i].right);
    }
    int root = find_root();
    postorder(root);
}
}

namespace pat_a1163 {
constexpr int N = 1005;
constexpr int INF = 0x3fff'ffff;

int G[N][N], n;
bool visit[N];
int d[N];

bool dijkstra(int s, const std::vector<int> &short_set)
{
    std::fill(d, d + N, INF);
    memset(visit, false, sizeof(visit));
    d[s] = 0;
    for (int i = 0; i < n; ++i)
    {
        int u = short_set[i], min = d[short_set[i]];
        for (int j = 1; j <= n; ++j)
        {
            if (!visit[j] && d[j] < min)
                return false;
        }
        visit[u] = true;
        for (int v = 1; v <= n; ++v)
        {
            if (!visit[v] && G[u][v] != INF)
            {
                if (d[u] + G[u][v] < d[v])
                {
                    d[v] = d[u] + G[u][v];
                }
            }
        }
    }
    return true;
}

void entry()
{
    int m;
    scanf("%d%d", &n, &m);
    std::fill(G[0], G[0] + N * N, INF);
    while (m--)
    {
        int u, v, dis;
        scanf("%d%d%d", &u, &v, &dis);
        G[u][v] = G[v][u] = dis;
    }
    scanf("%d", &m);
    while (m--)
    {
        std::vector<int> short_path;
        int u;
        for (int i = 0; i < n; ++i)
        {
            scanf("%d", &u);
            short_path.push_back(u);
        }
        if (dijkstra(short_path[0], short_path))
            printf("Yes\n");
        else
            printf("No\n");

    }
}
}

namespace pat_a1164 {
constexpr int N = 7 * 26 + 3;
using std::string;

string picture[N];

void entry()
{
    for (int i = 0; i < 7 * 26; ++i)
        std::getline(std::cin, picture[i]);

    std::vector<string> words;
    string tmp, line;
    std::getline(std::cin, line);
    for (auto c : line)
    {
        if ('A' <= c && c <= 'Z')
            tmp.push_back(c);
        else
        {
            if (tmp != "")
            {
                words.push_back(tmp);
                tmp = "";
            }
        }
    }
    if (tmp != "")
        words.push_back(tmp);

    for (int k = 0; k < words.size(); ++k)
    {
        string word = words[k];
        for (int row = 0; row < 7; ++row)
        {
            for (int i = 0; i < word.size(); ++i)
            {
                int s = word[i] - 'A';
                printf("%s", picture[7 * s + row].c_str());
                if (i < word.size() - 1)
                    printf(" ");
            }
            printf("\n");
        }
        if (k < words.size() - 1)
            printf("\n");
    }
}
}

namespace pat_a1165 {
constexpr int N = 100'005;

struct node
{
    int addr, data, next;
};

node list[N];


void entry()
{
    int h, n, k;
    scanf("%d%d%d", &h, &n, &k);
    int addr, data, next;
    for (int i = 0; i < n; ++i)
    {
        scanf("%d%d%d", &addr, &data, &next);
        list[addr].addr = addr;
        list[addr].data = data;
        list[addr].next = next;
    }
    int p = h;
    std::vector<std::vector<node>> ans;
    std::vector<node> tmp;
    while (p != -1)
    {
        if (tmp.size() == k)
        {
            ans.push_back(tmp);
            tmp.clear();
        }
        tmp.push_back(list[p]);
        p = list[p].next;
    }
    if (!tmp.empty())
        ans.push_back(tmp);
    std::vector<node> res;
    for (int i = ans.size() - 1; i >= 0; --i)
    {
        for (auto e : ans[i])
            res.push_back(e);
    }
    int i;
    for (i = 0; i < res.size() - 1; ++i)
    {
        printf("%05d %d %05d\n", res[i].addr, res[i].data, res[i+1].addr);
    }
    if (i == res.size() - 1)
        printf("%05d %d -1\n", res[i].addr, res[i].data);
}
}

namespace pat_a1166 {
constexpr int N = 205;

int G[N][N], n;
bool visit[N];


bool is_ok(const std::vector<int> &friends)
{
    for (int i = 0; i < friends.size(); ++i)
    {
        for (int j = i + 1; j < friends.size(); ++j)
        {
            int u = friends[i], v = friends[j];
            if (G[u][v] == 0)
                return false;
        }
    }
    for (int u = 1; u <= n; ++u)
    {
        bool flag = true;
        if (!visit[u])
        {
            for (auto v : friends)
            {
                if (G[u][v] == 0)
                {
                    flag = false;
                    break;
                }
            }
            if (flag)
                return false;
        }
    }
    return true;
}

int is_more(const std::vector<int> &friends)
{
    for (int i = 0; i < friends.size(); ++i)
    {
        for (int j = i + 1; j < friends.size(); ++j)
        {
            int u = friends[i], v = friends[j];
            if (G[u][v] == 0)
                return 0;
        }
    }
    for (int u = 1; u <= n; ++u)
    {
        bool flag = true;
        if (!visit[u])
        {
            for (auto v : friends)
            {
                if (G[u][v] == 0)
                {
                    flag = false;
                    break;
                }
            }
            if (flag)
                return u;
        }
    }
    return 0;
}




void entry()
{
    int m;
    scanf("%d%d", &n, &m);
    while (m--)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        G[u][v] = G[v][u] = 1;
    }
    int k;
    scanf("%d", &k);
    for (int i = 1; i <= k; ++i)
    {
        memset(visit, false, sizeof(visit));
        std::vector<int> friends;
        int l, u;
        scanf("%d", &l);
        for (int j = 0; j < l; ++j)
        {
            scanf("%d", &u);
            friends.push_back(u);
            visit[u] = true;
        }
        if (is_ok(friends))
            printf("Area %d is OK.\n", i);
        else if (int who = is_more(friends))
        {
            printf("Area %d may invite more people, such as %d.\n", i, who);
        }
        else
            printf("Area %d needs help.\n", i);
    }
}
}

namespace pat_a1167 {
constexpr int N = 35;

struct node
{
    int data;
    node *left, *right;
};

int in[N], n;

int find_min_index(int left, int right)
{
    int min = left;
    for (int i = left; i <= right; ++i)
        if (in[i] < in[min])
            min = i;
    return min;
}

node *built_tree(int inL, int inR)
{
    if (inL > inR)
        return nullptr;
    node *root = new node;
    int k = find_min_index(inL, inR);
    root->data = in[k];

    root->left = built_tree(inL, k - 1);
    root->right = built_tree(k + 1, inR);

    return root;
}

void level_order(node *root)
{
    std::queue<node *> q;
    q.push(root);
    int cnt = 0;
    while (!q.empty())
    {
        auto top = q.front();
        q.pop();
        printf("%d", top->data);
        if (++cnt < n)
            printf(" ");
        else
            printf("\n");
        if (top->left != nullptr)
            q.push(top->left);
        if (top->right != nullptr)
            q.push(top->right);
    }
}

void entry()
{
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &in[i]);
    }
    node *root = built_tree(0, n - 1);
    level_order(root);
}
}



int main(int argc, char **argv)
{
//    pat_a1152::entry();
//    pat_a1153::entry();
//    pat_a1154::entry();
//    pat_a1155::entry();
//    pat_a1156::entry();
//    pat_a1157::entry();
//    pat_a1158::entry();
//    pat_a1159::entry();
//    pat_a1160::entry();
//    pat_a1161::entry();
//    pat_a1162::entry();
//    pat_a1163::entry();
//    pat_a1164::entry();
//    pat_a1165::entry();
//    pat_a1166::entry();
    pat_a1167::entry();
    return 0;
}