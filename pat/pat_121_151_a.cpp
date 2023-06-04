#include <cstdio>
#include <cstring>
#include <queue>
#include <map>
#include <algorithm>
#include <sstream>
#include <set>
#include <cmath>
#include <stack>

namespace pat_a1121 {
constexpr int N = 100'005;

int couple[N];
int guest[N];

bool visible[N];

void entry()
{
    int n, k, c, p;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
    {
        scanf("%d%d", &c, &p);
        couple[c] = p;
        couple[p] = c;
    }
    scanf("%d", &k);
    std::vector<int> dogs;
    for (int i = 0; i < k; ++i)
    {
        scanf("%d", &p);
        guest[i] = p;
        visible[p] = true;
    }

    for (int i = 0; i < k; ++i)
    {
        c = guest[i];
        p = couple[c];
        if (!visible[p])
            dogs.push_back(c);
    }

    std::sort(dogs.begin(), dogs.end());
    n = dogs.size();
    printf("%d\n", n);
    for (int i = 0; i < n; ++i)
    {
        printf("%05d", dogs[i]);
        if (i < n - 1)
            printf(" ");
        else
            printf("\n");
    }
}
}

namespace pat_a1122_x {
constexpr int N = 205;

int G[N][N];
bool visit[N];

bool is_circle_hamilton(const std::vector<int> &path, int n)
{
    int sz = path.size();
    if (sz <= n || path[0] != path[sz-1])
        return false;
    memset(visit, false, sizeof(visit));
    int u = path[0], s = u, v;
    visit[u] = true;
    for (int i = 1; i < sz - 1; ++i)
    {
        v = path[i];
        if (G[u][v] == 1 && !visit[v])
        {
            visit[v] = true;
            u = v;
        }
        else
            return false;
    }
    return G[u][s] == 1;
}

void entry()
{
    int n, m, u, v;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; ++i)
    {
        scanf("%d%d", &u, &v);
        G[u][v] = G[v][u] = 1;
    }
    int k;
    scanf("%d", &k);
    for (int i = 0; i < k; ++i)
    {
        std::vector<int> tmp;
        scanf("%d", &m);
        for (int j = 0; j < m; ++j)
        {
            scanf("%d", &v);
            tmp.push_back(v);
        }
        if (is_circle_hamilton(tmp, n))
            printf("YES\n");
        else
            printf("NO\n");
    }
}
}

namespace pat_a1123 {
constexpr int N = 25;

struct avl_node
{
    int data, height;
    avl_node *left, *right;
};

int get_height(avl_node *root)
{
    if (root == nullptr)
        return 0;
    return root->height;
}

int get_balance_factor(avl_node *root)
{
    return get_height(root->left) - get_height(root->right);
}

void update_height(avl_node *root)
{
    root->height = 1 + std::max(get_height(root->left), get_height(root->right));
}

void turn_left(avl_node *&root)
{
    avl_node *tmp = root->right;
    root->right = tmp->left;
    tmp->left = root;
    update_height(root);
    update_height(tmp);
    root = tmp;
}

void turn_right(avl_node *&root)
{
    avl_node *tmp = root->left;
    root->left = tmp->right;
    tmp->right = root;
    update_height(root);
    update_height(tmp);
    root = tmp;
}

void insert(avl_node *&root, int x)
{
    if (root == nullptr)
    {
        root = new avl_node;
        root->data = x;
        root->height = 1;
        root->left = root->right = nullptr;
        return ;
    }
    if (x < root->data)
    {
        insert(root->left, x);
        update_height(root);
        if (get_balance_factor(root) == 2)
        {
            if (get_balance_factor(root->left) == 1)
                turn_right(root);
            else if (get_balance_factor(root->left) == -1)
            {
                turn_left(root->left);
                turn_right(root);
            }
        }
    }
    else
    {
        insert(root->right, x);
        update_height(root);
        if (get_balance_factor(root) == -2)
        {
            if (get_balance_factor(root->right) == -1)
                turn_left(root);
            else if (get_balance_factor(root->right) == 1)
            {
                turn_right(root->right);
                turn_left(root);
            }
        }
    }
}

bool is_complete_binary_tree(avl_node *root)
{
    if (root == nullptr)
        return true;
    std::queue<avl_node *> q;
    q.push(root);
    while (!q.empty())
    {
        auto h = q.front();
        q.pop();
        if (h)
        {
            q.push(h->left);
            q.push(h->right);
        }
        else
        {
            while (!q.empty())
            {
                h = q.front();
                q.pop();
                if (h)
                    return false;
            }
        }
    }
    return true;
}

void level_traversal(avl_node *root, int &n)
{
    std::queue<avl_node *> q;
    q.push(root);
    while (!q.empty())
    {
        auto h = q.front();
        q.pop();
        printf("%d", h->data);
        if (--n > 0)
            printf(" ");
        else
            printf("\n");
        if (h->left)
            q.push(h->left);
        if (h->right)
            q.push(h->right);
    }
}

void entry()
{
    int n, x;
    scanf("%d", &n);

    avl_node *root = nullptr;
    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &x);
        insert(root, x);
    }
    level_traversal(root, n);
    if (is_complete_binary_tree(root))
        printf("YES\n");
    else
        printf("NO\n");
}
}

namespace pat_a1124 {
constexpr int M = 1005;
constexpr int N = 25;

char candidate_winners[M][N];
using std::string;

void entry()
{
    int n, step, index;
    scanf("%d%d%d", &n, &step, &index);
    for (int i = 1; i <= n; ++i)
        scanf("%s", candidate_winners[i]);

    std::map<string, bool> winner;
    if (index > n)
    {
        printf("Keep going...\n");
        return;
    }
    for (int i = index; i <= n; i += step)
    {
        if (!winner[candidate_winners[i]])
        {
            winner[candidate_winners[i]] = true;
            printf("%s\n", candidate_winners[i]);
        }
        else
        {
            while (i <= n && winner[candidate_winners[++i]]);
            if (i <= n)
            {
                winner[candidate_winners[i]] = true;
                printf("%s\n", candidate_winners[i]);
            }
        }
    }
}
}

namespace pat_a1125 {
constexpr int N = 10005;

int num[N];

void entry()
{
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &num[i]);
    }
    std::sort(num, num + n);
    int sum = num[0];
    for (int i = 1; i < n; ++i)
    {
        sum += num[i];
        sum /= 2;
    }
    printf("%d\n", sum);
}
}

namespace pat_a1126 {
constexpr int N = 505;
constexpr int INF = 0x3fff'ffff;

int G[N][N], n;
int degree[N];
bool visit[N];

void dfs(int v, int &sum)
{
    visit[v] = true;
    ++sum;
    for (int u = 1; u <= n; ++u)
    {
        if (!visit[u] && G[v][u] != INF)
            dfs(u, sum);
    }
}

void entry()
{
    int m, u, v;
    scanf("%d%d", &n, &m);
    std::fill(G[0], G[0] + N * N, INF);
    for (int i = 0; i < m; ++i)
    {
        scanf("%d%d", &u, &v);
        G[u][v] = G[v][u] = 1;
        ++degree[u];
        ++degree[v];
    }
    int sum = 0, cnt = 0;
    dfs(1, sum);
    for (int i = 1; i <= n; ++i)
    {
        if (degree[i] % 2 == 1)
            ++cnt;
    }
    for (int i = 1; i <= n; ++i)
    {
        printf("%d", degree[i]);
        if (i < n)
            printf(" ");
        else
            printf("\n");

    }
    if (sum == n && cnt == 2)
        printf("Semi-Eulerian\n");
    else if (sum == n && cnt == 0)
        printf("Eulerian\n");
    else
        printf("Non-Eulerian\n");
}
}

namespace pat_a1127 {
constexpr int N = 35;

struct node
{
    int data;
    node *left, *right;
};

int in[N], post[N];

node *build_tree(int inL, int inR, int pL, int pR)
{
    if (inL > inR)
        return nullptr;
    node *root = new node;
    root->data = post[pR];

    int k;
    for (k = inL; k <= inR; ++k)
    {
        if (post[pR] == in[k])
            break;
    }
    int n_left = k - inL;

    root->left = build_tree(inL, k - 1, pL, pL + n_left - 1);
    root->right = build_tree(k + 1, inR, pL + n_left, pR - 1);
    return root;
}

void zigzag_traversal(node *root, int &n)
{
    if (root == nullptr)
        return ;
    std::stack<node *> S[2];
    int cur = 0, next = 1;
    S[cur].push(root);
    while (!S[cur].empty() || !S[next].empty())
    {
        node *top = S[cur].top();
        S[cur].pop();
        printf("%d", top->data);
        if (--n > 0)
            printf(" ");
        else
            printf("\n");
        if (cur == 0)
        {
            if (top->right)
                S[next].push(top->right);
            if (top->left)
                S[next].push(top->left);
        }
        else
        {
            if (top->left)
                S[next].push(top->left);
            if (top->right)
                S[next].push(top->right);
        }
        if (S[cur].empty())
        {
            cur = 1 - cur;
            next = 1 - next;
        }
    }
}

void entry()
{
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &in[i]);
    }
    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &post[i]);
    }
    node *root = build_tree(0, n - 1, 0, n - 1);
    zigzag_traversal(root, n);
}
}

namespace pat_a1128 {
constexpr int N = 1005;

bool is_queue(int x1, int y1, int x2, int y2)
{
    return (x1 != x2) && (y1 != y2) && (x1 - y1 != x2 - y2) && (x1 + y1 != x2 + y2);
}

int row[N];

void entry()
{
    int m, n;
    scanf("%d", &m);
    for (int k = 0; k < m; ++k)
    {
        scanf("%d", &n);
        for (int j = 1; j <= n; ++j)
            scanf("%d", &row[j]);
        bool flag = true;
        for (int i = 1; i <= n; ++i)
        {
            for (int j = i + 1; j <= n; ++j)
                if (!is_queue(row[i], i, row[j], j))
                {
                    flag = false;
                    goto label;
                }
        }
        label:
        if (flag)
            printf("YES\n");
        else
            printf("NO\n");
    }
}
}

namespace pat_a1129 {
constexpr int N = 50'005;

int times[N];
int index[N], len = 0;
bool is_at[N];

bool cmp(int a, int b)
{
    if (times[a] != times[b])
    {
        return times[a] > times[b];
    }
    else
    {
        return a < b;
    }
}

void entry()
{
    int n, k;
    scanf("%d%d", &n, &k);
    for (int i = 0; i < n; ++i)
    {
        int x;
        scanf("%d", &x);
        if (i > 0)
        {
            std::sort(index, index + len, cmp);
            printf("%d:", x);
            for (int j = 0; j < k && j < len; ++j)
                printf(" %d", index[j]);
            printf("\n");
        }
        ++times[x];
        if (!is_at[x])
        {
            if (len < k)
            {
                index[len++] = x;
                is_at[x] = true;
            }
            else
            {
                if (times[index[k-1]] < times[x])
                {
                    is_at[index[k-1]] = false;
                    index[k-1] = x;
                    is_at[x] = true;
                }
                else if (times[index[k-1]] == times[x] && x < index[k-1])
                {
                    is_at[index[k-1]] = false;
                    index[k-1] = x;
                    is_at[x] = true;
                }
            }
        }
    }
}
}

namespace pat_a1130 {
constexpr int N = 25;
constexpr int M = 15;

struct node
{
    char data[M];
    int left, right;
};
bool visited[N];
node tree[N];
int n, tree_root;

void dfs(int index)
{
    if (index == -1)
        return ;
    visited[index] = true;
    dfs(tree[index].left);
    dfs(tree[index].right);
}

int find_root()
{
    for (int i = 1; i <= n; ++i)
    {
        dfs(i);
        bool flag = true;
        for (int j = 1; j <= n; ++j)
        {
            if (!visited[j])
            {
                flag = false;
                break;
            }
        }
        if (flag)
            return i;
        memset(visited, false, n);
    }
    return -1;
}

void infix_expr(int root)
{
    if (root == -1)
        return;
    if (tree[root].left != -1 || tree[root].right != -1)
        if (root != tree_root)
            printf("(");
    infix_expr(tree[root].left);
    printf("%s", tree[root].data);
    infix_expr(tree[root].right);
    if (tree[root].left != -1 || tree[root].right != -1)
        if (root != tree_root)
            printf(")");
}

void entry()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%s%d%d", tree[i].data, &tree[i].left, &tree[i].right);
    }
    tree_root = find_root();
    infix_expr(tree_root);
}
}

namespace pat_a1131_part_right_run_timeout {
constexpr int N = 10'005;
constexpr int INF = 0x3fff'ffff;

struct node
{
    int v;
    int dis;
    int line_no;
};

std::vector<node> G[N];
bool visit[N];
int d[N];
int pre[N];
int times[N];

int get_line_num(int u, int v)
{
    for (auto e : G[u])
    {
        if (e.v == v)
            return e.line_no;
    }
    return -1;
}

void dijkstra(int s)
{
    std::fill(d, d + N, INF);
    std::fill(times, times + N, INF);
    std::fill(visit, visit + N, false);
    for (int i = 0; i < N; ++i)
        pre[i] = i;
    times[s] = 0;
    d[s] = 0;
    for (int i = 0; i < N; ++i)
    {
        int u = -1, min = INF;
        for (int j = 0; j < N; ++j)
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
        for (auto e : G[u])
        {
            int v = e.v;
            if (!visit[v])
            {
                if (d[u] + e.dis < d[v])
                {
                    d[v] = d[u] + e.dis;
                    pre[v] = u;
                    if (get_line_num(u, v) == get_line_num(pre[u], u))
                        times[v] = times[u];
                    else
                        times[v] = times[u] + 1;

                }
                else if (d[u] + e.dis == d[v])
                {
                    if (get_line_num(u, v) == get_line_num(pre[u], u))
                    {
                        if (times[u] < times[v])
                        {
                            times[v] = times[u];
                            pre[v] = u;
                        }
                    }
                    else
                    {
                        if (times[u] + 1 < times[v])
                        {
                            times[v] = times[u] + 1;
                            pre[v] = u;
                        }
                    }
                }
            }
        }
    }
}

void dfs(int s, int v, std::vector<int> &path)
{
    if (v == s)
    {
        path.push_back(v);
        return ;
    }
    dfs(s, pre[v], path);
    path.push_back(v);
}



void print_path(const std::vector<int> &path)
{
    int n = path.size();
    printf("%d\n", n - 1);
    int i, j, p_num, n_num;
    for (i = 0, j = 1; j < n - 1; ++j)
    {
        p_num = get_line_num(path[j-1], path[j]);
        n_num = get_line_num(path[j], path[j+1]);
        if (n_num != p_num)
        {
            printf("Take Line#%d from %04d to %04d.\n", p_num, path[i], path[j]);
            i = j;
        }
    }
    printf("Take Line#%d from %04d to %04d.\n", n_num, path[i], path[j]);
}

void entry()
{
    int m, n, u, v;
    scanf("%d", &m);
    for (int i = 1; i <= m; ++i)
    {
        scanf("%d%d", &n, &u);
        for (int j = 1; j < n; ++j)
        {
            scanf("%d", &v);
            G[u].push_back({.v = v, .dis = 1, .line_no = i});
            G[v].push_back({.v = u, .dis = 1, .line_no = i});
            u = v;
        }
    }
    int s, e, k;
    scanf("%d", &k);
    for (int i = 0; i < k; ++i)
    {
        scanf("%d%d", &s, &e);
        std::vector<int> path;
        dijkstra(s);
        dfs(s, e, path);
/*        int stops = path.size();
        printf("%d\n", stops - 1);
        for (int j = 0; j < stops; ++j)
        {
            printf("%d", path[j]);
            if (j < stops - 1)
                printf(" ");
            else
                printf("\n");
        }

        printf("-----------------------\n");
        printf("-----------------------\n");*/
        print_path(path);
    }
}
}

namespace pat_a1131_run_timeout {
constexpr int N = 10'005;
constexpr int INF = 0x3fff'ffff;

struct node
{
    int v;
    int dis;
    int line_no;
};

std::vector<node> G[N];
bool visit[N];
int d[N];
std::vector<int> pre[N];

int get_line_num(int u, int v)
{
    for (auto e : G[u])
    {
        if (e.v == v)
            return e.line_no;
    }
    return -1;
}

void dijkstra(int s)
{
    std::fill(d, d + N, INF);
    std::fill(visit, visit + N, false);
    d[s] = 0;
    for (int i = 0; i < N; ++i)
    {
        int u = -1, min = INF;
        for (int j = 0; j < N; ++j)
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
        for (auto e : G[u])
        {
            int v = e.v;
            if (!visit[v])
            {
                if (d[u] + e.dis < d[v])
                {
                    d[v] = d[u] + e.dis;
                    pre[v].clear();
                    pre[v].push_back(u);
                }
                else if (d[u] + e.dis == d[v])
                {
                    pre[v].push_back(u);
                }
            }
        }
    }
}


int calc_transfer_times(std::vector<int> tmp_path)
{
    std::reverse(tmp_path.begin(), tmp_path.end());
    int n = tmp_path.size();
    int j, p_num, n_num;
    int cnt = 0;
    for (j = 1; j < n - 1; ++j)
    {
        p_num = get_line_num(tmp_path[j-1], tmp_path[j]);
        n_num = get_line_num(tmp_path[j], tmp_path[j+1]);
        if (n_num != p_num)
            ++cnt;
    }
    return cnt;
}


int min_times = INF;

void dfs(int s, int v, std::vector<int> &path, std::vector<int> &tmp)
{
    if (v == s)
    {
        tmp.push_back(v);
        int times = calc_transfer_times(tmp);
        if (times < min_times)
        {
            min_times = times;
            path = tmp;
        }
        tmp.pop_back();
        return ;
    }
    tmp.push_back(v);
    for (auto u : pre[v])
        dfs(s, u, path, tmp);
    tmp.pop_back();
}



void print_path(std::vector<int> &path)
{
    int n = path.size();
    std::reverse(path.begin(), path.end());
    printf("%d\n", n - 1);
    int i, j, p_num, n_num;
    for (i = 0, j = 1; j < n - 1; ++j)
    {
        p_num = get_line_num(path[j-1], path[j]);
        n_num = get_line_num(path[j], path[j+1]);
        if (n_num != p_num)
        {
            printf("Take Line#%d from %04d to %04d.\n", p_num, path[i], path[j]);
            i = j;
        }
    }
    printf("Take Line#%d from %04d to %04d.\n", n_num, path[i], path[j]);
}

void entry()
{
    int m, n, u, v;
    scanf("%d", &m);
    for (int i = 1; i <= m; ++i)
    {
        scanf("%d%d", &n, &u);
        for (int j = 1; j < n; ++j)
        {
            scanf("%d", &v);
            G[u].push_back({.v = v, .dis = 1, .line_no = i});
            G[v].push_back({.v = u, .dis = 1, .line_no = i});
            u = v;
        }
    }
    int s, e, k;
    scanf("%d", &k);
    for (int i = 0; i < k; ++i)
    {
        scanf("%d%d", &s, &e);
        dijkstra(s);
        std::vector<int> path, tmp;
        min_times = INF;
        dfs(s, e, path, tmp);
        print_path(path);
    }
}
}

namespace pat_a1131_x {
constexpr int N = 10'005;
constexpr int INF = 0x3fff'ffff;

struct node
{
    int v;
    int line_no;
};

std::vector<node> G[N];
bool visit[N];

int min_stops = INF;
int min_transfers = INF;
std::vector<int> path, tmp;

int get_line_num(int u, int v)
{
    for (auto e : G[u])
    {
        if (e.v == v)
            return e.line_no;
    }
    return -1;
}

void dfs(int ed, int u, int line_num, int transfer_num)
{
    if (u == ed)
    {
        tmp.push_back(u);
        if (tmp.size() < min_stops)
        {
            min_stops = tmp.size();
            path = tmp;
            min_transfers = transfer_num;
        }
        else if (tmp.size() == min_stops)
        {
            if (transfer_num < min_transfers)
            {
                min_transfers = transfer_num;
                path = tmp;
            }
        }
        tmp.pop_back();
        return ;
    }
    visit[u] = true;
    tmp.push_back(u);
    for (auto e : G[u])
    {
        if (!visit[e.v])
        {
            if (line_num == e.line_no)
            {
                dfs(ed, e.v, e.line_no, transfer_num);
            }
            else
            {
                dfs(ed, e.v, e.line_no, transfer_num + 1);
            }
        }
    }
    tmp.pop_back();
    visit[u] = false;
}

void print_path(const std::vector<int> &path)
{
    int n = path.size();
    printf("%d\n", n - 1);
    int i, j, p_num, n_num;
    for (i = 0, j = 1; j < n - 1; ++j)
    {
        p_num = get_line_num(path[j-1], path[j]);
        n_num = get_line_num(path[j], path[j+1]);
        if (n_num != p_num)
        {
            printf("Take Line#%d from %04d to %04d.\n", p_num, path[i], path[j]);
            i = j;
        }
    }
    printf("Take Line#%d from %04d to %04d.\n", n_num, path[i], path[j]);
}

void entry()
{
    int m, n, u, v;
    scanf("%d", &m);
    for (int i = 1; i <= m; ++i)
    {
        scanf("%d%d", &n, &u);
        for (int j = 1; j < n; ++j)
        {
            scanf("%d", &v);
            G[u].push_back({v, i});
            G[v].push_back({u, i});
            u = v;
        }
    }
    int s, e, k;
    scanf("%d", &k);
    for (int i = 0; i < k; ++i)
    {
        scanf("%d%d", &s, &e);
        min_stops = INF;
        min_transfers = INF;
        dfs(e, s, G[s][0].line_no, 0);
        print_path(path);
    }
}
}

namespace pat_a1132 {
constexpr int N = 35;
int num[N], len;

void trans_num(int n)
{
    len = 0;
    do
    {
        num[len++] = n % 10;
        n /= 10;
    } while (n > 0);
}

void cut_two_num(int n, int &n1, int &n2)
{
    trans_num(n);
    for (int i = 0, j = len - 1; i < j; ++i, --j)
    {
        int tmp = num[i];
        num[i] = num[j];
        num[j] = tmp;
    }
    n1 = 0;
    n2 = 0;
    for (int i = 0; i < len; ++i)
    {
        if (i < len / 2)
            n1 = n1 * 10 + num[i];
        else
            n2 = n2 * 10 + num[i];
    }
}

void entry()
{
    int k, n, n1, n2;
    scanf("%d", &k);
    for (int i = 0; i < k; ++i)
    {
        scanf("%d", &n);
        cut_two_num(n, n1, n2);
        long product = 1L * n1 * n2;
        if (product != 0 && n % product == 0)
            printf("Yes\n");
        else
            printf("No\n");
    }
}
}

namespace pat_a1133 {
constexpr int N = 100'005;

struct node
{
    int addr;
    int data;
    int next;
};

node list[N];

void entry()
{
    int h, n, k;
    scanf("%d%d%d", &h, &n, &k);
    for (int i = 0; i < n; ++i)
    {
        int ad, data, next;
        scanf("%d%d%d", &ad, &data, &next);
        list[ad].addr = ad;
        list[ad].data = data;
        list[ad].next = next;
    }
    std::vector<node> list1, list2, list3;
    while (h != -1)
    {
        if (list[h].data < 0)
            list1.push_back(list[h]);
        else if (list[h].data <= k)
            list2.push_back(list[h]);
        else
            list3.push_back(list[h]);
        h = list[h].next;
    }
    for (auto &node : list2)
        list1.push_back(node);
    for (auto &node : list3)
        list1.push_back(node);
    int i;
    for (i = 0; i < list1.size() - 1; ++i)
    {
        printf("%05d %d %05d\n", list1[i].addr, list1[i].data, list1[i+1].addr);
    }
    printf("%05d %d -1\n", list1[i].addr, list1[i].data);
}
}

namespace pat_a1134 {
constexpr int N = 10'005;

struct edge
{
    int u, v;
};

edge graph[N];
bool visit[N];

void entry()
{
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; ++i)
    {
        scanf("%d%d", &graph[i].u, &graph[i].v);
    }
    int k;
    scanf("%d", &k);
    while (k-- > 0)
    {
        int t, index;
        scanf("%d", &t);
        memset(visit, false, sizeof(visit));
        for (int j = 0; j < t; ++j)
        {
            scanf("%d", &index);
            visit[index] = true;
        }
        bool flag = true;
        for (int j = 0; j < m; ++j)
        {
            int u = graph[j].u;
            int v = graph[j].v;
            if (!visit[u] && !visit[v])
            {
                flag = false;
                break;
            }
        }
        if (flag)
            printf("Yes\n");
        else
            printf("No\n");
    }
}
}

namespace pat_a1135 {

enum { BLACK, RED };

struct rb_node
{
    int color;
    int data;
    rb_node *left, *right;
};

int abs(int x)
{
    return x < 0 ? -x : x;
}

int max(int x, int y)
{
    return x < y ? y : x;
}

void insert(rb_node *&root, int data)
{
    if (root == nullptr)
    {
        root = new rb_node;
        root->data = abs(data);
        if (data < 0)
            root->color = RED;
        else
            root->color = BLACK;
        root->left = root->right = nullptr;
        return ;
    }
    if (abs(data) < root->data)
        insert(root->left, data);
    else
        insert(root->right, data);
}

bool is_f_red_c_black(rb_node *root)
{
    if (root == nullptr)
        return true;
    if (root->color == RED)
    {
        if ((root->left != nullptr && root->left->color == RED)
            || (root->right != nullptr && root->right->color == RED))
            return false;
    }
    return is_f_red_c_black(root->left)
            && is_f_red_c_black(root->right);
}

int black_num(rb_node *root)
{
    if (root == nullptr)
        return 0;
    int left_n = black_num(root->left);
    int right_n = black_num(root->right);
    return root->color == BLACK ? max(left_n, right_n) + 1 : max(left_n, right_n);
}

bool is_equal_path_black_num(rb_node *root)
{
    if (root == nullptr)
        return true;
    int left_n = black_num(root->left);
    int right_n = black_num(root->right);
    if (left_n != right_n)
        return false;
    return is_equal_path_black_num(root->left)
            && is_equal_path_black_num(root->right);
}

void entry()
{
    int k;
    scanf("%d", &k);
    while (k--)
    {
        int n, x;
        rb_node *root = nullptr;
        scanf("%d", &n);
        for (int i = 0; i < n; ++i)
        {
            scanf("%d", &x);
            insert(root, x);
        }
        if (root->color == RED || !is_f_red_c_black(root) || !is_equal_path_black_num(root))
            printf("No\n");
        else
            printf("Yes\n");
    }
}
}

namespace pat_a1136 {
constexpr int N = 1005;

struct big_integer
{
    int data[N], len;
};

big_integer add(big_integer a, big_integer b)
{
    big_integer c;
    c.len = 0;
    int r = 0;
    for (int i = 0; i < a.len || i < b.len; ++i)
    {
        int tmp = a.data[i] + b.data[i] + r;
        c.data[c.len++] = tmp % 10;
        r = tmp / 10;
    }
    if (r > 0)
        c.data[c.len++] = r;
    return c;
}

big_integer str_to_num(const char *str, int n)
{
    big_integer c;
    c.len = 0;
    for (int i = n - 1; i >= 0; --i)
    {
        c.data[c.len++] = str[i] - '0';
    }
    return c;
}

big_integer reverse_of(big_integer a)
{
    for (int i = 0, j = a.len - 1; i < j; ++i, --j)
    {
        std::swap(a.data[i], a.data[j]);
    }
    return a;
}

std::string to_string(big_integer a)
{
    std::string s;
    for (int i = a.len - 1; i >= 0; --i)
        s.push_back(a.data[i] + '0');
    return s;
}

bool is_palindromic_num(big_integer a)
{
    while (a.len > 0 && a.data[a.len-1] == 0)
        --a.len;
    if (a.len == 1 && a.data[0] == 0)
        return true;
    for (int i = 0, j = a.len - 1; i < j; ++i, --j)
    {
        if (a.data[i] != a.data[j])
            return false;
    }
    return true;
}

void entry()
{
    char str[N];
    scanf("%s", str);
    int str_len = strlen(str);
    big_integer a, b;
    big_integer c = str_to_num(str, str_len);
    int k = 10;
    while (k-- > 0)
    {
        if (is_palindromic_num(c))
        {
            printf("%s is a palindromic number.\n", to_string(c).c_str());
            break;
        }
        a = c;
        b = reverse_of(a);
        c = add(a, b);
        printf("%s + %s = %s\n", to_string(a).c_str(), to_string(b).c_str(), to_string(c).c_str());
    }
    if (k == -1)
        printf("Not found in 10 iterations.\n");
}
}

namespace pat_a1137 {
constexpr int N = 10'005 * 3;

using std::string;

struct record
{
    char id[25];
    int gp = -1;
    int gm = -1;
    int gf = -1;
    int g = -1;
};

std::map<string, int> id_index;

record list[N];
static int n = 0;

int get_index(const string &id)
{
    auto it = id_index.find(id);
    if (it == id_index.end())
    {
        id_index[id] = n;
        return n++;
    }
    return it->second;
}


bool cmp(record a, record b)
{
    if (a.g != b.g)
        return a.g > b.g;
    else
        return strcmp(a.id, b.id) < 0;
}

void entry()
{
    int p, m, s;
    scanf("%d%d%d", &p, &m, &s);
    char id[25]; int score;
    while (p--)
    {
        scanf("%s%d", id, &score);
        int i = get_index(id);
        strcpy(list[i].id, id);
        list[i].gp = score;
    }
    while (m--)
    {
        scanf("%s%d", id, &score);
        int i = get_index(id);
        strcpy(list[i].id, id);
        list[i].gm = score;
    }
    while (s--)
    {
        scanf("%s%d", id, &score);
        int i = get_index(id);
        strcpy(list[i].id, id);
        list[i].gf = score;
        if (list[i].gm > list[i].gf)
            list[i].g = round(list[i].gm * 0.4 + list[i].gf * 0.6);
        else
            list[i].g = list[i].gf;
    }
    std::sort(list, list + n, cmp);
    for (int i = 0; i < n; ++i)
    {
        if (list[i].gp < 200 || list[i].g < 60)
            continue;
        printf("%s %d %d %d %d\n",
               list[i].id, list[i].gp,
               list[i].gm,
               list[i].gf,
               list[i].g);
    }
}
}

namespace pat_a1138 {
constexpr int N = 50'005;

int pre[N], in[N], n;

int first_in_postorder(int preL, int preR, int inL, int inR)
{
    if (preL == preR)
        return pre[preL];
    int k;
    for (k = inL; k <= inR; ++k)
        if (pre[preL] == in[k])
            break;
    int left_n = k - inL;
    if (left_n > 0)
        return pre[preL + left_n];
    else
        return first_in_postorder(preL + 1, preR, inL + 1, inR);
}

void entry()
{
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &pre[i]);
    }
    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &in[i]);
    }
    int x = first_in_postorder(0, n - 1, 0, n - 1);
    printf("%d\n", x);
}
}

namespace pat_a1139 {
constexpr int N = 10'000;

struct node
{
    int c, p;
};

auto cmp = [](node a, node b)
{
    if (a.c != b.c)
        return a.c < b.c;
    return a.p < b.p;
};

std::map<int, bool> table;
std::vector<int> friends[N];

void process_relations(int c, int p)
{
    c = abs(c);
    p = abs(p);
    std::vector<node> ans;
    for (auto c_ : friends[c])
    {
        for (auto p_ : friends[p])
        {
            if (c_ == p || p_ == c)
                continue;
            if (table[c_ * N + p_])
                ans.push_back({c_, p_});
        }
    }
    std::sort(ans.begin(), ans.end(), cmp);
    printf("%zu\n", ans.size());
    for (auto &e : ans)
        printf("%04d %04d\n", e.c, e.p);
}

void entry()
{
    int n, m;
    scanf("%d%d", &n, &m);
    char str_c[10], str_p[10];
    int c, p;
    for (int i = 0; i < m; ++i)
    {
        scanf("%s%s", str_c, str_p);
        c = std::abs(std::stoi(str_c));
        p = std::abs(std::stoi(str_p));
        table[c * N + p] = table[p * N + c] = true;
        if (strlen(str_c) == strlen(str_p))
        {
            friends[c].push_back(p);
            friends[p].push_back(c);
        }
    }
    scanf("%d", &n);
    while (n-- > 0)
    {
        scanf("%d%d", &c, &p);
        process_relations(c, p);
    }
}
}

namespace pat_a1140 {

std::vector<int> look_say_seq(const std::vector<int> &seq)
{
    std::vector<int> ans;
    for (int i = 0, j = 0; j < seq.size(); )
    {
        int cnt = 0;
        while (j < seq.size() && seq[i] == seq[j])
        {
            ++cnt;
            ++j;
        }
        ans.push_back(seq[i]);
        ans.push_back(cnt);
        i = j;
    }
    return ans;
}

void entry()
{
    int d, n;
    scanf("%d%d", &d, &n);
    std::vector<int> seq;
    seq.push_back(d);
    for (int i = 1; i < n; ++i)
    {
        seq = look_say_seq(seq);
    }
    for (auto e : seq)
        printf("%d", e);
    printf("\n");
}
}

namespace pat_a1141 {
constexpr int N = 100'005;
using std::string;

struct record
{
   char id[10];
   int score;
};

struct school
{
    char name[10];
    int tws;
    int ns;
    std::vector<record> records;
};

school list[N];
static int len = 0;
std::map<string, int> str_num;

int get_index(char *name)
{
    char *p = name;
    while (*p)
    {
        *p = tolower(*p);
        ++p;
    }
    auto it = str_num.find(name);
    if (it == str_num.end())
    {
        str_num[name] = len;
        return len++;
    }
    else
        return str_num[name];
}

bool cmp_rank(const school &a, const school &b)
{
    if (a.tws != b.tws)
        return a.tws > b.tws;
    else if (a.ns != b.ns)
        return a.ns < b.ns;
    else
        return strcmp(a.name, b.name) < 0;
}

void entry()
{
    int n;
    scanf("%d", &n);
    char code[10];
    record tmp;
    while (n--)
    {
        scanf("%s%d%s", tmp.id, &tmp.score, code);
        int i = get_index(code);
        strcpy(list[i].name, code);
        list[i].records.push_back(tmp);
    }

    for (int j = 0; j < len; ++j)
    {
        list[j].ns = list[j].records.size();
        int score_a = 0, score_b = 0, score_t = 0;
        for (auto &r : list[j].records)
        {
            if (r.id[0] == 'A')
                score_a += r.score;
            else if (r.id[0] == 'B')
                score_b += r.score;
            else if (r.id[0] == 'T')
                score_t += r.score;
        }
        list[j].tws = int(1.0 * score_b / 1.5 + score_a + 1.5 * score_t);
    }
    std::sort(list, list + len, cmp_rank);
    printf("%d\n", len);
    int r = 1;
    for (int i = 0; i < len; ++i)
    {
        if (i > 0 && list[i].tws != list[i-1].tws)
            r = i + 1;
        printf("%d %s %d %d\n", r, list[i].name, list[i].tws, list[i].ns);
    }
}
}

namespace pat_a1142 {
constexpr int N = 205;
constexpr int INF = 0x3fff'ffff;

int G[N][N], n;
bool inset[N];

bool is_clique(const std::vector<int> &set)
{
    int u, v;
    if (set.size() == 1)
        return true;
    for (int i = 0; i < set.size(); ++i)
    {
        for (int j = i + 1; j < set.size(); ++j)
        {
            u = set[i], v = set[j];
            if (G[u][v] == INF)
                return false;
        }
    }
    return true;
}


bool is_max_clique(std::vector<int> set)
{
    if (!is_clique(set))
        return false;
    for (int i = 1; i <= n; ++i)
    {
        if (!inset[i])
        {
            set.push_back(i);
            if (is_clique(set))
                return false;
            set.pop_back();
        }
    }
    return true;
}

void entry()
{
    int m;
    scanf("%d%d", &n, &m);
    std::fill(G[0], G[0] + N * N, INF);
    int u, v;
    while (m--)
    {
        scanf("%d%d", &u, &v);
        G[u][v] = G[v][u] = 1;
    }
    scanf("%d", &m);
    int k;
    while (m--)
    {
        scanf("%d", &k);
        memset(inset, false, sizeof(inset));
        std::vector<int> set;
        for (int i = 0; i < k; ++i)
        {
            scanf("%d", &u);
            set.push_back(u);
            inset[u] = true;
        }
        if (is_max_clique(set))
            printf("Yes\n");
        else if (is_clique(set))
            printf("Not Maximal\n");
        else
            printf("Not a Clique\n");
    }
}
}

namespace pat_a1143_runtime_out {

struct bst_node
{
    int data;
    bst_node *left, *right;
};


void insert(bst_node *&root, int x)
{
    if (root == nullptr)
    {
        root = new bst_node;
        root->data = x;
        root->left = root->right = nullptr;
        return;
    }
    if (x < root->data)
        insert(root->left, x);
    else
        insert(root->right, x);
}

void dfs_path(bst_node *root, std::vector<int> &path, int data)
{
    if (root == nullptr)
        return ;
    if (root->data == data)
    {
        path.push_back(root->data);
        return ;
    }
    path.push_back(root->data);
    if (data < root->data)
        dfs_path(root->left, path, data);
    else dfs_path(root->right, path, data);
}

bst_node *find(bst_node *root, int x)
{
    if (root == nullptr)
        return nullptr;
    if (root->data == x)
        return root;
    if (x < root->data)
        return find(root->left, x);
    else
        return find(root->right, x);
}


void entry()
{
    int m, n;
    int data;
    bst_node *root = nullptr;
    scanf("%d%d", &m, &n);
    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &data);
        insert(root, data);
    }
    while (m--)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        bst_node *unode = find(root, u), *vnode = find(root, v);
        if (unode == nullptr && vnode == nullptr)
            printf("ERROR: %d and %d are not found.\n", u, v);
        else if (unode == nullptr)
            printf("ERROR: %d is not found.\n", u);
        else if (vnode == nullptr)
            printf("ERROR: %d is not found.\n", v);
        else
        {
            std::vector<int> path1, path2;
            dfs_path(root, path1, u);
            dfs_path(root, path2, v);
            int i;
            for (i = 0; i < path1.size() && i < path2.size(); ++i)
            {
                if (path1[i] != path2[i])
                    break;
            }
            if (u == v)
                printf("%d is an ancestor of %d.\n", u, v);
            else
            {
                if (path1[i-1] == u)
                    printf("%d is an ancestor of %d.\n", u, v);
                else if (path1[i-1] == v)
                    printf("%d is an ancestor of %d.\n", v, u);
                else
                    printf("LCA of %d and %d is %d.\n", u, v, path1[i-1]);
            }
        }
    }
}
}

namespace pat_a1143 {
constexpr int N = 10'005;

int pre[N];
std::map<int, bool> visit;

void entry()
{
    int m, n;
    scanf("%d%d", &m, &n);
    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &pre[i]);
        visit[pre[i]] = true;
    }
    while (m--)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        if (!visit[u] && !visit[v])
            printf("ERROR: %d and %d are not found.\n", u, v);
        else if (!visit[u])
            printf("ERROR: %d is not found.\n", u);
        else if (!visit[v])
            printf("ERROR: %d is not found.\n", v);
        else
        {
            if (u == v)
                printf("%d is an ancestor of %d.\n", u, v);
            else
            {
                int mid;
                for (int i = 0; i < n; ++i)
                {
                    mid = pre[i];
                    if ((u <= mid && mid <= v) || (v <= mid && mid <= u))
                        break;
                }
                if (mid == u)
                    printf("%d is an ancestor of %d.\n", u, v);
                else if (mid == v)
                    printf("%d is an ancestor of %d.\n", v, u);
                else
                    printf("LCA of %d and %d is %d.\n", u, v, mid);
            }
        }
    }
}
}

namespace pat_a1144 {
constexpr int N = 100'005;

std::map<int, bool> visit;

void entry()
{
    int n, x;
    scanf("%d", &n);
    while (n--)
    {
        scanf("%d", &x);
        if (x > 0)
            visit[x] = true;
    }
    int i = 1;
    while (visit[i]) ++i;
    printf("%d\n", i);
}
}

namespace pat_a1145 {
constexpr int N = 10'010;

int table[N], T;

bool is_prime(int n)
{
    if (n <= 1)
        return false;
    int sqrt_n = sqrt(n);
    for (int i = 2; i <= sqrt_n; ++i)
    {
        if (n % i == 0)
            return false;
    }
    return true;
}

int put(int key)
{
    int pos, i;
    for (i = 0; i < T; ++i)
    {
        pos = (key % T + i * i) % T;
        if (table[pos] == 0)
        {
            table[pos] = key;
            break;
        }
    }
    return i == T ? -1 : pos;
}

int get(int key)
{
    int pos, i;
    for (i = 0; i < T; ++i)
    {
        pos = (key % T + i * i) % T;
        if (table[pos] == key || table[pos] == 0)
            break;
    }
    return i + 1;
}


void entry()
{
    int n, m;
    scanf("%d%d%d", &T, &n, &m);
    while (!is_prime(T)) ++T;
    int x;
    while (n--)
    {
        scanf("%d", &x);
        if (put(x) == -1)
            printf("%d cannot be inserted.\n", x);
    }
    int sum = 0;
    for (int i = 0; i < m; ++i)
    {
        scanf("%d", &x);
        sum += get(x);
    }
    printf("%.1f\n", 1.0 * sum / m);
}
}

namespace pat_a1146 {
constexpr int N = 1005;

std::vector<int> G[N];
int in_degree[N];

void entry()
{
    int n, m;
    scanf("%d%d", &n, &m);
    while (m--)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        G[u].push_back(v);
        ++in_degree[v];
    }
    scanf("%d", &m);
    std::vector<int> ans;
    for (int j = 0; j < m; ++j)
    {
        int u;
        std::vector<int> tmp(n + 1, 0);
        for (int i = 1; i <= n; ++i)
            tmp[i] = in_degree[i];
        bool flag = true;
        for (int i = 0; i < n; ++i)
        {
            scanf("%d", &u);
            if (!flag)
                continue;
            if (tmp[u] == 0)
            {
                for (auto v : G[u])
                    --tmp[v];
            }
            else
                flag = false;
        }
        if (!flag)
            ans.push_back(j);
    }
    for (int j = 0; j < ans.size(); ++j)
    {
        printf("%d", ans[j]);
        if (j < ans.size() - 1)
            printf(" ");
        else
            printf("\n");
    }
}
}

namespace pat_a1147 {
constexpr int N = 1005;

int heap[N], n;

bool is_max_heap(int index)
{
    if (index > n)
        return true;
    int flag = true;
    if (2 * index <= n)
        flag = flag && (heap[index] >= heap[index*2]);
    if (2 * index + 1 <= n)
        flag = flag && (heap[index] >= heap[index*2+1]);

    if (flag == false)
        return false;
    return is_max_heap(index * 2) && is_max_heap(index * 2 + 1);
}

bool is_min_heap(int index)
{
    if (index > n)
        return true;
    int flag = true;
    if (2 * index <= n)
        flag = flag && (heap[index] <= heap[index*2]);
    if (2 * index + 1 <= n)
        flag = flag && (heap[index] <= heap[index*2+1]);

    if (flag == false)
        return false;
    return is_min_heap(index * 2) && is_min_heap(index * 2 + 1);
}

void postorder(int root, std::vector<int> &seq)
{
    if (root > n)
        return ;
    postorder(root * 2, seq);
    postorder(root * 2 + 1, seq);
    seq.push_back(heap[root]);
}

void print_postorder()
{
    std::vector<int> seq;
    postorder(1, seq);
    for (int i = 0; i < seq.size(); ++i)
    {
        printf("%d", seq[i]);
        if (i < seq.size() - 1)
            printf(" ");
        else
            printf("\n");
    }
}

void entry()
{
    int m;
    scanf("%d%d", &m, &n);
    while (m--)
    {
        for (int i = 1; i <= n; ++i)
            scanf("%d", &heap[i]);
        if (is_max_heap(1))
            printf("Max Heap\n");
        else if (is_min_heap(1))
            printf("Min Heap\n");
        else
            printf("Not Heap\n");
        print_postorder();
    }
}
}

namespace pat_a1148 {
constexpr int N = 105;

int say[N], real_player[N], liar[N];

void entry()
{
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &say[i]);
    }
    for (int i = 1; i <= n; ++i)
    {
        for (int j = i + 1; j <= n; ++j)
        {
            std::fill(real_player, real_player + N, 1);
            std::fill(liar, liar + N, 0);
            real_player[i] = real_player[j] = -1;
            int cnt = 0;
            for (int k = 1; k <= n; ++k)
            {
                if (say[k] * real_player[abs(say[k])] < 0)
                {
                    ++cnt;
                    liar[k] = 1;
                }
                else
                    real_player[abs(say[k])] = say[k];
            }
            if (cnt == 2 && liar[i] + liar[j] == 1)
            {
                printf("%d %d\n", i, j);
                return ;
            }
        }
    }
    printf("No Solution\n");
}
}

namespace pat_a1149 {
constexpr int N = 1005;

std::map<int, std::vector<int>> table;
//int goods[N];

void entry()
{
    int m1, m2;
    scanf("%d%d", &m1, &m2);
    while (m1--)
    {
        int c, p;
        scanf("%d%d", &c, &p);
        table[c].push_back(p);
        table[p].push_back(c);
    }
    while (m2--)
    {
        int n, id;
        scanf("%d", &n);
        std::set<int> goods;
        for (int i = 0; i < n; ++i)
        {
            scanf("%d", &id);
            goods.insert(id);
        }
        bool flag = true;
        for (auto e : goods)
        {
            if (table[e].empty())
                continue;
            for (auto e_ : table[e])
            {
                auto it = goods.find(e_);
                if (it != goods.end())
                {
                    printf("No\n");
                    flag = false;
                    goto label;
                }
            }
        }
        label:
        if (flag)
            printf("Yes\n");
    }
}
}

namespace pat_a1150 {
constexpr int N = 205;
constexpr int INF = 0x3fff'ffff;


int G[N][N], n;
bool visit[N];

bool is_simple_cycle(const std::vector<int> &path)
{
    int sz = path.size();
    if (sz != n + 1 || path[0] != path[sz-1])
        return false;
    memset(visit, false, sizeof(visit));
    int u = path[0], s = u, v;
    visit[u] = true;
    for (int i = 1; i < sz - 1; ++i)
    {
        v = path[i];
        if (G[u][v] != INF && !visit[v])
        {
            visit[v] = true;
            u = v;
        }
        else
            return false;
    }
    return G[u][s] != INF;
}

bool is_cycle(const std::vector<int> &path)
{
    int sz = path.size();
    if (sz <= n + 1 || path[0] != path[sz-1])
        return false;
    memset(visit, false, sizeof(visit));
    int u = path[0], v;
    visit[u] = true;
    for (int i = 1; i < sz; ++i)
    {
        v = path[i];
        if (G[u][v] != INF)
        {
            visit[v] = true;
            u = v;
        }
        else
            return false;
    }
    for (int i = 1; i <= n; ++i)
    {
        if (!visit[i])
            return false;
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
    int index = m, shortest = INF;
    for (int i = 1; i <= m; ++i)
    {
        std::vector<int> tmp;
        int k, u, v;
        long total_dist = 0;
        bool cycle = false;
        scanf("%d%d", &k, &u);
        tmp.push_back(u);
        for (int j = 1; j < k; ++j)
        {
            scanf("%d", &v);
            total_dist += G[u][v];
            tmp.push_back(v);
            u = v;
        }
        if ((cycle = is_simple_cycle(tmp)))
            printf("Path %d: %ld (TS simple cycle)\n", i, total_dist);
        else if ((cycle = is_cycle(tmp)))
            printf("Path %d: %ld (TS cycle)\n", i, total_dist);
        else
        {
            if (total_dist == INF)
                printf("Path %d: NA (Not a TS cycle)\n", i);
            else
                printf("Path %d: %ld (Not a TS cycle)\n", i, total_dist);
        }
        if (cycle && total_dist < shortest)
        {
            shortest = total_dist;
            index = i;
        }
    }
    printf("Shortest Dist(%d) = %d\n", index, shortest);
}
}

namespace pat_a1151 {
constexpr int N = 10'005;

struct node
{
    int data;
    int left, right;
    int parent = -1;
};

int in[N], pre[N];
node tree[N];
int n, len = 0;
std::map<int, int> key_pos;
bool visit[N];

int built_tree(int inL, int inR, int preL, int preR)
{
    if (inL > inR)
        return -1;
    int root = len;
    tree[len++].data = pre[preL];
    int i;
    for (i = inL; i <= inR; ++i)
    {
        if (pre[preL] == in[i])
            break;
    }
    int left_n = i - inL;
    tree[root].left = built_tree(inL, i - 1, preL + 1, preL + left_n);
    tree[root].right = built_tree(i + 1, inR, preL + left_n + 1, preR);
    if (tree[root].left != -1)
        tree[tree[root].left].parent = root;
    if (tree[root].right != -1)
        tree[tree[root].right].parent = root;
    return root;
}

void dfs(int root)
{
    if (root == -1)
        return ;
    key_pos[tree[root].data] = root;
    dfs(tree[root].left);
    dfs(tree[root].right);
}

void lowest_common_ancestor(int root, int u, int v)
{
    auto it_u = key_pos.find(u), it_v = key_pos.find(v), end = key_pos.end();
    if (it_u == end && it_v == end)
        printf("ERROR: %d and %d are not found.\n", u, v);
    else if (it_u == end)
        printf("ERROR: %d is not found.\n", u);
    else if (it_v == end)
        printf("ERROR: %d is not found.\n", v);
    else
    {
        memset(visit, false, n);
        int ancestor = -1;
        int parent = it_u->second;
        while (parent != -1)
        {
            visit[parent] = true;
            parent = tree[parent].parent;
        }
        parent = it_v->second;
        while (parent != -1)
        {
            if (visit[parent])
            {
                ancestor = parent;
                break;
            }
            parent = tree[parent].parent;
        }
        if (tree[ancestor].data == u)
            printf("%d is an ancestor of %d.\n", u, v);
        else if (tree[ancestor].data == v)
            printf("%d is an ancestor of %d.\n", v, u);
        else
        {
            printf("LCA of %d and %d is %d.\n", u, v, tree[ancestor].data);
        }
    }
}






void entry()
{
    int m;
    scanf("%d%d", &m, &n);
    for (int i = 0; i < n; ++i)
        scanf("%d", &in[i]);
    for (int i = 0; i < n; ++i)
        scanf("%d", &pre[i]);
    int root = built_tree(0, n - 1, 0, n - 1);
    dfs(root);
    while (m--)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        lowest_common_ancestor(root, u, v);
    }
}
}



int main(int argc, char **argv)
{
    pat_a1121::entry();
    pat_a1122_x::entry();
    pat_a1123::entry();
    pat_a1124::entry();
    pat_a1125::entry();
    pat_a1126::entry();
    pat_a1127::entry();
    pat_a1128::entry();
    pat_a1129::entry();
    pat_a1130::entry();
    pat_a1131_part_right_run_timeout::entry();
    pat_a1131_run_timeout::entry();
    pat_a1131_x::entry();
    pat_a1132::entry();
    pat_a1133::entry();
    pat_a1134::entry();
    pat_a1135::entry();
    pat_a1136::entry();
    pat_a1137::entry();
    pat_a1138::entry();
    pat_a1139::entry();
    pat_a1140::entry();
    pat_a1141::entry();
    pat_a1142::entry();
    pat_a1143_runtime_out::entry();
    pat_a1143::entry();
    pat_a1144::entry();
    pat_a1145::entry();
    pat_a1146::entry();
    pat_a1147::entry();
    pat_a1148::entry();
    pat_a1149::entry();
    pat_a1150::entry();
    pat_a1151::entry();
    return 0;
}