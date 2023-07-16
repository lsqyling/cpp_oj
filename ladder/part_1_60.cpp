#include <cstdio>
#include <set>
#include <queue>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <iostream>
#include <sstream>

namespace L2_005 {
constexpr int N = 55;

std::set<int> sets[N];

int union_set(const std::set<int> &a, const std::set<int> &b)
{
    std::set<int> ans;
    ans.insert(a.begin(), a.end());
    ans.insert(b.begin(), b.end());
    return ans.size();
}

int intersection_set(const std::set<int> &a, const std::set<int> &b)
{
    int cnt = 0;
    for (auto x : a)
    {
        if (auto it = b.find(x); it != b.end())
            ++cnt;
    }
    return cnt;
}

void entry()
{
    int n, k, x, s, t;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &k);
        for (int j = 0; j < k; ++j)
        {
            scanf("%d", &x);
            sets[i].insert(x);
        }
    }
    scanf("%d", &k);
    for (int j = 0; j < k; ++j)
    {
        scanf("%d%d", &s, &t);
        printf("%.2f%%\n", 100.0*intersection_set(sets[s], sets[t])/union_set(sets[s], sets[t]));
    }
}
}

namespace L2_006 {
constexpr int N = 35;
struct node
{
    int data;
    node *left, *right;
};

int in[N], post[N];

node *build_tree(int inL, int inR, int postL, int postR)
{
    if (inL > inR)
        return nullptr;
    node *root = new node;
    root->data = post[postR];
    int k;
    for (k = inL; k <= inR; ++k)
    {
        if (in[k] == post[postR])
            break;
    }
    int nleft = k - inL;
    root->left = build_tree(inL, k - 1, postL, postL + nleft - 1);
    root->right = build_tree(k + 1, inR, postL + nleft, postR - 1);
    return root;
}

void traversal_level(node *root, int n)
{
    if (root == nullptr)
        return ;
    std::queue<node *> Q;
    Q.push(root);
    int cnt = 0;
    while (!Q.empty())
    {
        node *top = Q.front();
        Q.pop();
        printf("%d", top->data);

        if (++cnt < n)
            printf(" ");
        if (top->left)
            Q.push(top->left);
        if (top->right)
            Q.push(top->right);
    }
}



void entry()
{
    int n;
    scanf("%d", &n);

    for (int i = 1; i <= n; ++i)
        scanf("%d", &post[i]);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &in[i]);
    node *tree = build_tree(1, n, 1, n);
    traversal_level(tree, n);
}
}

namespace L2_007 {
constexpr int N = 10'000;

struct family
{
    int id;
    int total_amount;
    double total_houses;
    double total_area;

    family() : id(0), total_amount(1), total_houses(0), total_area(0) {}

};

int father[N];
family all[N];

void init_father()
{
    for (int i = 0; i < N; ++i)
    {
        father[i] = i;
    }
}

int find(int x)
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

void union_(int a, int b)
{
    int fa_a = find(a);
    int fa_b = find(b);
    if (fa_a < fa_b)
    {
        father[fa_b] = fa_a;
        all[fa_a].total_amount += all[fa_b].total_amount;
    }
    if (fa_b < fa_a)
    {
        father[fa_a] = fa_b;
        all[fa_b].total_amount += all[fa_a].total_amount;
    }
}

void entry()
{
    int n;
    scanf("%d", &n);
    int id, p1, p2, k, c;
    double h, a;

    init_father();
    std::vector<int> nids;
    for (int i = 0; i < n; ++i)
    {
        scanf("%d%d%d%d", &id, &p1, &p2, &k);
        nids.push_back(id);
        if (p1 != -1)
            union_(id, p1);
        if (p2 != -1)
            union_(id, p2);
        for (int j = 0; j < k; ++j)
        {
            scanf("%d", &c);
            union_(id, c);
        }
        scanf("%lf%lf", &h, &a);
        all[id].total_houses = h;
        all[id].total_area = a;
    }

    std::set<int> tmp;
    for (auto i : nids)
    {
        auto fa = find(i);
        if (i != fa)
        {
            all[fa].total_houses += all[i].total_houses;
            all[fa].total_area += all[i].total_area;
        }
        tmp.insert(fa);
    }

    std::vector<int> ans(tmp.begin(), tmp.end());
    auto cmp = [](int i, int j)
    {
        if (all[i].total_area/all[i].total_amount != all[j].total_area/all[j].total_amount)
            return all[i].total_area/all[i].total_amount > all[j].total_area/all[j].total_amount;
        else
            return i < j;

    };
    std::sort(ans.begin(), ans.end(), cmp);
    printf("%d\n", ans.size());
    for (auto i : ans)
    {
        printf("%04d %d %.3f %.3f\n", i, all[i].total_amount, all[i].total_houses/all[i].total_amount,
                all[i].total_area/all[i].total_amount);
    }
}
}

namespace L2_008 {
constexpr int N = 1005;

char S[N];
bool dp[N][N];
void entry()
{
    fgets(S, sizeof(S), stdin);
    int len = strlen(S);
    memset(dp, 0, sizeof(dp));
//    boundary
    int ans = 0;
    for (int i = 0; i < len; ++i)
    {
        dp[i][i] = 1;
        if (i < len - 1)
        {
            if (S[i] == S[i+1])
            {
                dp[i][i+1] = 1;
                ans = 2;
            }
        }
    }

    for (int L = 3; L <= len; ++L)
    {
        for (int i = 0; i + L - 1 < len; ++i)
        {
            int j = i + L - 1;
            if (S[i] == S[j] && dp[i+1][j-1] == 1)
            {
                dp[i][j] = 1;
                ans = L;
            }
        }
    }

    printf("%d\n", ans);
}
}

namespace L2_009 {
constexpr int N = 10'005;
constexpr double EPS = 1e-8;

template<class T>
inline bool equal(T a, T b)
{
    return fabs(a - b) < EPS;
}

template<class T>
inline bool greater(T a, T b)
{
    return a - b > EPS;
}

struct envelope
{
    int id;
    int amount;
    double balance;
};

bool operator<(const envelope &a, const envelope &b)
{
    if (!equal(a.balance, b.balance))
        return greater(a.balance, b.balance);
    else if (a.amount != b.amount)
        return a.amount > b.amount;
    else
        return a.id < b.id;
}

envelope all[N];

void entry()
{
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        int k, ni;
        double pi;
        scanf("%d", &k);
        for (int j = 0; j < k; ++j)
        {
            scanf("%d%lf", &ni, &pi);
            all[ni].amount++;
            all[ni].balance += pi;
            all[i].balance -= pi;
        }
        all[i].id = i;
    }

    std::sort(all + 1, all + n + 1);
    for (int i = 1; i <= n; ++i)
    {
        printf("%d %.2f\n", all[i].id, all[i].balance/100);
    }
}
}

namespace L2_010 {
constexpr int N = 105;

int relations[N][N];
int father[N];

void init()
{
    for (int i = 0; i < N; ++i)
    {
        father[i] = i;
    }
}

int find(int x)
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
    int fa = find(a);
    int fb = find(b);
    if (fa != fb)
        father[fa] = fb;
}

void entry()
{
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);
    init();
    int u, v, op;
    for (int i = 0; i < m; ++i)
    {
        scanf("%d%d%d", &u, &v, &op);
        relations[u][v] = relations[v][u] = op;
        if (op == 1)
            union_(u, v);
    }
    for (int j = 0; j < k; ++j)
    {
        scanf("%d%d", &u, &v);
        int fu = find(u);
        int fv = find(v);
        if (relations[u][v] != -1 && fu == fv)
            printf("No problem\n");
        else if (relations[u][v] == 0)
            printf("OK\n");
        else if (fu == fv && relations[u][v] == -1)
            printf("OK but...\n");
        else if (relations[u][v] == -1 && fu != fv)
            printf("No way\n");
    }
}
}


namespace L2_011 {
constexpr int N = 35;

struct node
{
    int data;
    node *left, *right;
};

int in[N], pre[N];

node *build_tree(int inL, int inR, int preL, int preR)
{
    if (inL > inR)
        return nullptr;
    node *root = new node;
    root->data = pre[preL];
    int k;
    for (k = inL; k <= inR; ++k)
        if (in[k] == pre[preL])
            break;

    int nleft = k - inL;
    root->left = build_tree(inL, k - 1, preL + 1, preL + nleft);
    root->right = build_tree(k + 1, inR, preL + 1 + nleft, inR);
    return root;
}

void mirror_tree(node *&root)
{
    if (root == nullptr)
        return;
    mirror_tree(root->left);
    mirror_tree(root->right);
    std::swap(root->left, root->right);
}

void traversal_level(node *root, int n)
{
    std::queue<node *> Q;
    Q.push(root);
    int cnt = 0;
    while (!Q.empty())
    {
        node *top = Q.front();
        Q.pop();
        printf("%d", top->data);
        if (++cnt < n)
            printf(" ");

        if (top->left)
            Q.push(top->left);
        if (top->right)
            Q.push(top->right);
    }
}

void entry()
{
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
        scanf("%d", &in[i]);
    for (int j = 0; j < n; ++j)
        scanf("%d", &pre[j]);

    node *root = build_tree(0, n - 1, 0, n - 1);
    mirror_tree(root);
    traversal_level(root, n);
}
}

namespace L2_012 {
constexpr int N = 1005;


class heap
{
public:
    heap() : heap_{0}, n_(0)
    {
    }

    heap(std::initializer_list<int> li);
    void insert(int x);
    bool is_root(int x);
    bool is_siblings(int x, int y);
    bool is_parent(int x, int y);
    bool is_child(int x, int y);

private:

    void adjust_down(int low, int high);
    void adjust_up(int low, int high);
    void build_heap();

    int heap_[N];
    int n_;
};

heap::heap(std::initializer_list<int> li) : heap()
{
    for (const auto &item : li)
    {
        heap_[++n_] = item;
    }
    build_heap();
}

void heap::insert(int x)
{
    heap_[++n_] = x;
    adjust_up(1, n_);
}

bool heap::is_root(int x)
{
    return heap_[1] == x;
}

bool heap::is_siblings(int x, int y)
{
    int index_x, index_y;
    for (int i = 1; i <= n_; ++i)
    {
        if (heap_[i] == x)
            index_x = i;
        if (heap_[i] == y)
            index_y = i;
    }
    return index_x/2 == index_y/2;
}

bool heap::is_parent(int x, int y)
{
    int index_x, index_y;
    for (int i = 1; i <= n_; ++i)
    {
        if (heap_[i] == x)
            index_x = i;
        if (heap_[i] == y)
            index_y = i;
    }
    return index_y/2 == index_x;
}

bool heap::is_child(int x, int y)
{
    int index_x, index_y;
    for (int i = 1; i <= n_; ++i)
    {
        if (heap_[i] == x)
            index_x = i;
        if (heap_[i] == y)
            index_y = i;
    }
    return index_x/2 == index_y;
}

void heap::adjust_down(int low, int high)
{
    int i = low, j = 2 * i;

    while (j <= high)
    {
        if (j + 1 <= high && heap_[j+1] < heap_[j])
            ++j;

        if (heap_[j] < heap_[i])
        {
            std::swap(heap_[j], heap_[i]);
            i = j;
            j = i * 2;
        }
        else
            break;
    }
}

void heap::adjust_up(int low, int high)
{
    int i = high, j = i / 2;
    while (j >= low)
    {
        if (heap_[j] > heap_[i])
        {
            std::swap(heap_[j], heap_[i]);
            i = j;
            j = i / 2;
        }
        else
            break;
    }

}

void heap::build_heap()
{
    for (int i = n_/2; i >= 1 ; --i)
    {
        adjust_down(i, n_);
    }

}


void entry()
{
    int n, m;
    scanf("%d%d", &n, &m);
    heap min_heap;
    for (int i = 0; i < n; ++i)
    {
        int x;
        scanf("%d", &x);
        min_heap.insert(x);
    }
    getchar();
    int x, y;
    char ans;
    std::string str;
    for (int j = 0; j < m; ++j)
    {
        std::getline(std::cin, str);
        if (auto it = str.find("is the root"); it != std::string::npos)
        {
            std::istringstream iss(str);
            iss >> x;
            ans = min_heap.is_root(x) ? 'T' : 'F';
            printf("%c\n", ans);
        }
        if (auto it = str.find("are siblings"); it != std::string::npos)
        {
            std::istringstream iss(str);
            std::string tmp;
            iss >> x >> tmp >> y;
            ans = min_heap.is_siblings(x, y) ? 'T' : 'F';
            printf("%c\n", ans);
        }

        if (auto it = str.find("is the parent of"); it != std::string::npos)
        {
            std::istringstream iss(str);
            std::string tmp;
            iss >> x;
            for (int i = 0; i < 4; ++i)
            {
                iss >> tmp;
            }
            iss >> y;
            ans = min_heap.is_parent(x, y) ? 'T' : 'F';
            printf("%c\n", ans);
        }
        if (auto it = str.find("is a child of"); it != std::string::npos)
        {
            std::istringstream iss(str);
            std::string tmp;
            iss >> x;
            for (int i = 0; i < 4; ++i)
            {
                iss >> tmp;
            }
            iss >> y;
            ans = min_heap.is_child(x, y) ? 'T' : 'F';
            printf("%c\n", ans);
        }
    }
}
}

namespace L2_013 {















}


int main(int argc, char **argv)
{
//    L2_005::entry();
//    L2_006::entry();
//    L2_007::entry();
//    L2_008::entry();
//    L2_009::entry();
//    L2_010::entry();
//    L2_011::entry();
    L2_012::entry();
    return 0;
}
