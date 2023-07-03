#include <cstdio>
#include <set>
#include <queue>
#include <algorithm>
#include <cstring>


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



int main(int argc, char **argv)
{
//    L2_005::entry();
//    L2_006::entry();
//    L2_007::entry();
    L2_008::entry();
    return 0;
}