//
// Created by shiqing on 2021/4/8.
//
#include <algorithm>
#include <vector>
#include <set>
#include <queue>
#include <map>
#include <cstring>
#include <cstdio>
#include <string>

namespace graph_traversal_matrix {
constexpr int kV = 1000;
constexpr int kInf = 0x3fff'ffff;

int G[kV][kV], n;
bool visit[kV];

void Dfs(int u, int depth)
{
    visit[u] = true;
    for (int v = 0; v < n; ++v)
    {
        if (!visit[v] && G[u][v] != kInf)
        {
            Dfs(v, depth + 1);
        }
    }
}

void GraphTraversal()
{
    for (int u = 0; u < n; ++u)
    {
        if (!visit[u])
        {
            Dfs(u, 1);
        }
    }
}
}

namespace graph_traversal_adj {
constexpr int kV = 1005;

std::vector<int> G[kV];
bool visit[kV];
int n;

void Dfs(int u, int depth)
{
    visit[u] = true;
    for (int v : G[u])
    {
        if (!visit[u])
        {
            Dfs(v, depth + 1);
        }
    }
}

void GraphTraversal()
{
    for (int u = 0; u < n; ++u)
    {
        if (!visit[u])
        {
            Dfs(u, 1);
        }
    }
}
}

namespace pat_a1034 {
constexpr int kN = 2020;

std::map<int, std::string> id_to_name;
std::map<std::string, int> name_to_id;
std::map<std::string, int> gang;

int G[kN][kN], weight[kN];
int n, k, num_person = 0;
bool visit[kN];

void Dfs(int u, int &head, int &num_member, int &total_value)
{
    visit[u] = true;
    ++num_member;
    if (weight[u] > weight[head])
    {
        head = u;
    }
    for (int v = 0; v < num_person; ++v)
    {
        if (G[u][v])
        {
            total_value += G[u][v];
            G[u][v] = G[v][u] = 0;
            if (!visit[v])
            {
                Dfs(v, head, num_member, total_value);
            }
        }
    }
}

void DfsTraversal()
{
    for (int u = 0; u < num_person; ++u)
    {
        if (!visit[u])
        {
            int head = u, num_member = 0, total_value = 0;
            Dfs(u, head, num_member, total_value);
            if (num_member > 2 && total_value > k)
            {
                gang[id_to_name[head]] = num_member;
            }
        }
    }
}

int GetId(const std::string &name)
{
    if (name_to_id.find(name) != name_to_id.end())
    {
        return name_to_id[name];
    }
    else
    {
        name_to_id[name] = num_person;
        id_to_name[num_person] = name;
        return num_person++;
    }
}

void Entry()
{
    int w;
    char u_name[5], v_name[5];
    scanf("%d%d", &n, &k);
    for (int i = 0; i < n; ++i)
    {
        scanf("%s %s %d", u_name, v_name, &w);
        int u = GetId(u_name);
        int v = GetId(v_name);
        weight[u] += w;
        weight[v] += w;
        G[u][v] += w;
        G[v][u] += w;
    }
    DfsTraversal();
    printf("%lu\n", gang.size());
    for (auto it = gang.begin(); it != gang.end(); ++it)
    {
        printf("%s %d\n", it->first.c_str(), it->second);
    }
}
}

namespace bfs_graph {
constexpr int kV = 1005;
constexpr int kInf = 0x3fff'ffff;

namespace matrix {

int G[kV][kV], n;
bool inq[kV];

void Bfs(int s)
{
    std::queue<int> Q;
    Q.push(s);
    inq[s] = true;
    while (!Q.empty())
    {
        int u = Q.front();
        Q.pop();
        for (int v = 0; v < n; ++v)
        {
            if (!inq[v] && G[u][v] != kInf)
            {
                Q.push(v);
                inq[v] = true;
            }
        }
    }
}

void BfsTraversal()
{
    for (int u = 0; u < n; ++u)
    {
        if (!inq[u])
        {
            Bfs(u);
        }
    }
}
}
namespace adjacency {
std::vector<int> G[kV];
int n;
bool inq[kV];

void Bfs(int s)
{
    std::queue<int> Q;
    Q.push(s);
    inq[s] = true;
    while (!Q.empty())
    {
        int u = Q.front();
        Q.pop();
        for (int v : G[u])
        {
            if (!inq[v])
            {
                Q.push(v);
                inq[v] = true;
            }
        }
    }
}

void BfsTraversal()
{
    for (int u = 0; u < n; ++u)
    {
        if (!inq[u])
        {
            Bfs(u);
        }
    }
}
}
}

namespace pat_a1076 {
constexpr int kN = 1010;

struct Node
{
    int id_, layer_;
};

std::vector<Node> G[kN];
bool inq[kN];

int Bfs(int s, int L)
{
    int num_forward = 0;
    std::queue<Node> Q;
    Q.push({s, 0});
    inq[s] = true;
    while (!Q.empty())
    {
        Node u = Q.front();
        Q.pop();
        for (Node v : G[u.id_])
        {
            v.layer_ = u.layer_ + 1;
            if (!inq[v.id_] && v.layer_ <= L)
            {
                Q.push(v);
                inq[v.id_] = true;
                ++num_forward;
            }
        }
    }
    return num_forward;
}

void Entry()
{
    int n, L, id_follow, num_follow;
    scanf("%d%d", &n, &L);
    Node u;
    for (int i = 1; i <= n; ++i)
    {
        u.id_ = i;
        scanf("%d", &num_follow);
        for (int j = 0; j < num_follow; ++j)
        {
            scanf("%d", &id_follow);
            G[id_follow].push_back(u);
        }
    }
    int num_query, s;
    scanf("%d", &num_query);
    for (int i = 0; i < num_query; ++i)
    {
        memset(inq, false, sizeof(inq));
        scanf("%d", &s);
        int n_forward = Bfs(s, L);
        printf("%d\n", n_forward);
    }
}
}

namespace shortest_path {
constexpr int kN = 1005;
constexpr int kInf = 0x3fff'ffff;

namespace matrix {
int G[kN][kN], n;
int d[kN];
bool visit[kN];

void Dijkstra(int s)
{
    std::fill(d, d + kN, kInf);
    d[s] = 0;
    for (int i = 0; i < n; ++i)
    {
        int u = -1, min = kInf;
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
            if (!visit[v] && G[u][v] != kInf && d[u] + G[u][v] < d[v])
            {
                d[v] = d[u] + G[u][v];
            }
        }
    }
}
}

namespace adjacency {
struct Node
{
    int v_, dis_;
};

std::vector<Node> G[kN];
int n, d[kN];
bool visit[kN];

void Dijkstra(int s)
{
    std::fill(d, d + kN, kInf);
    d[s] = 0;
    for (int i = 0; i < n; ++i)
    {
        int u = -1, min = kInf;
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
        for (Node node : G[u])
        {
            int v = node.v_;
            if (!visit[v] && d[u] + node.dis_ < d[v])
            {
                d[v] = d[u] + node.dis_;
            }
        }
    }
}
}

namespace pat_a1003 {
constexpr int kN = 505;
constexpr int kInf = 0x3fff'ffff;

int G[kN][kN];
int d[kN], num[kN], weight[kN], w[kN];
bool visit[kN];

void Dijkstra(int s, int n)
{
    std::fill(d, d + kN, kInf);
    memset(num, 0, sizeof(num));
    memset(w, 0, sizeof(w));
    d[s] = 0;
    num[s] = 1;
    w[s] = weight[s];
    for (int i = 0; i < n; ++i)
    {
        int u = -1, min = kInf;
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
            if (!visit[v] && G[u][v] != kInf)
            {
                if (d[u] + G[u][v] < d[v])
                {
                    d[v] = d[u] + G[u][v];
                    w[v] = w[u] + weight[v];
                    num[v] = num[u];
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

void Entry()
{
    int n, m, s, e;
    scanf("%d%d%d%d", &n, &m, &s, &e);
    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &weight[i]);
    }
    std::fill(G[0], G[0] + kN * kN, kInf);
    for (int i = 0; i < m; ++i)
    {
        int u, v, x;
        scanf("%d%d%d", &u, &v, &x);
        G[v][u] = G[u][v] = x;
    }
    Dijkstra(s, n);
    printf("%d %d\n", num[e], w[e]);
}
}

namespace pat_a1030_v1 {
constexpr int kN = 505;
constexpr int kInf = 0x3fff'ffff;

struct Node
{
    int dis_, cost_;
};

Node G[kN][kN];
int d[kN], c[kN], pre[kN];
bool visit[kN];

void Dijkstra(int s, int n)
{
    std::fill(d, d + kN, kInf);
    std::memset(c, 0, sizeof(c));
    d[s] = 0;
    c[s] = 0;
    for (int i = 0; i < n; ++i)
    {
        int u = -1, min = kInf;
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
            if (!visit[v] && G[u][v].dis_ != kInf)
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

void PrintfPath(int s, int v)
{
    if (s == v)
    {
        printf("%d ", s);
        return;
    }
    PrintfPath(s, pre[v]);
    printf("%d ", v);
}

void Entry()
{
    int n, m, s, e;
    scanf("%d%d%d%d", &n, &m, &s, &e);
    std::fill(G[0], G[0] + kN * kN, Node{kInf, 0});
    for (int i = 0; i < m; ++i)
    {
        int u, v, dis, cost;
        scanf("%d%d%d%d", &u, &v, &dis, &cost);
        G[u][v].dis_ = dis;
        G[u][v].cost_ = cost;
        G[v][u] = G[u][v];
    }
    Dijkstra(s, n);
    PrintfPath(s, e);
    printf("%d %d", d[e], c[e]);
}
}

namespace pat_a1030_v2 {
constexpr int kN = 505;
constexpr int kInf = 0x3fff'ffff;

struct Node
{
    int dis_, cost_;
};

Node G[kN][kN];
bool visit[kN];
std::vector<int> pre[kN], tmp, path;
int opt_value = kInf, d[kN];

void Dijkstra(int s, int n)
{
    std::fill(d, d + kN, kInf);
    d[s] = 0;
    for (int i = 0; i < n; ++i)
    {
        int u = -1, min = kInf;
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
            if (!visit[v] && G[u][v].dis_ != kInf)
            {
                if (d[u] + G[u][v].dis_ < d[v])
                {
                    d[v] = d[u] + G[u][v].dis_;
                    pre[v].clear();
                    pre[v].push_back(u);
                }
                else if (d[u] + G[u][v].dis_ == d[v])
                {
                    pre[v].push_back(u);
                }
            }
        }
    }
}

void Dfs(int v, int s)
{
    if (v == s)
    {
        tmp.push_back(v);
        int tmp_cost = 0;
        for (int i = tmp.size() - 1; i > 0; --i)
        {
            int id = tmp[i], id_next = tmp[i - 1];
            tmp_cost += G[id][id_next].cost_;
        }
        if (tmp_cost < opt_value)
        {
            opt_value = tmp_cost;
            path = tmp;
        }
        tmp.pop_back();
        return;
    }
    tmp.push_back(v);
    for (int u : pre[v])
    {
        Dfs(u, s);
    }
    tmp.pop_back();
}

void Entry()
{
    int n, m, s, e;
    scanf("%d%d%d%d", &n, &m, &s, &e);
    std::fill(G[0], G[0] + kN * kN, Node{kInf, kInf});
    for (int i = 0; i < m; ++i)
    {
        int u, v, dis, cost;
        scanf("%d%d%d%d", &u, &v, &dis, &cost);
        G[u][v].dis_ = dis;
        G[u][v].cost_ = cost;
        G[v][u] = G[u][v];
    }
    Dijkstra(s, n);
    Dfs(e, s);
    for (int i = path.size() - 1; i >= 0; --i)
    {
        printf("%d ", path[i]);
    }
    printf("%d %d\n", d[e], opt_value);
}
}
}

namespace bellman_ford {
constexpr int kN = 1005;
constexpr int kInf = 0x3fff'ffff;

struct Node
{
    int v_, dis_;
};
std::vector<Node> G[kN];
int d[kN], n;

bool Bellman(int s)
{
    std::fill(d, d + kN, kInf);
    d[s] = 0;
    for (int i = 0; i < n - 1; ++i)
    {
        bool is_slack = false;
        for (int u = 0; u < n; ++u)
        {
            for (Node node : G[u])
            {
                int v = node.v_;
                int dis = node.dis_;
                if (d[u] + dis < d[v])
                {
                    d[v] = d[u] + dis;
                    is_slack = true;
                }
            }
        }
        if (!is_slack) return true;
    }
    for (int u = 0; u < n; ++u)
    {
        for (Node node : G[u])
        {
            int v = node.v_;
            int dis = node.dis_;
            if (d[u] + dis < d[v])
            {
                return false;
            }
        }
    }
    return true;
}
}

namespace pat_a1003_v1 {
constexpr int kN = 505;
constexpr int kInf = 0x3fff'ffff;

struct Node
{
    int v_, dis_;
};
std::vector<Node> G[kN];
int weight[kN], d[kN], num[kN], w[kN];
std::set<int> pre[kN];

void Bellman(int s, int n)
{
    std::fill(d, d + kN, kInf);
    std::memset(num, 0, sizeof(num));
    std::memset(w, 0, sizeof(w));
    d[s] = 0;
    num[s] = 1;
    w[s] = weight[s];
    for (int i = 0; i < n - 1; ++i)
    {
        for (int u = 0; u < n; ++u)
        {
            for (Node node : G[u])
            {
                int v = node.v_;
                int dis = node.dis_;
                if (d[u] + dis < d[v])
                {
                    d[v] = d[u] + dis;
                    w[v] = w[u] + weight[v];
                    num[v] = num[u];
                    pre[v].clear();
                    pre[v].insert(u);
                }
                else if (d[u] + dis == d[v])
                {
                    if (w[u] + weight[v] > w[v])
                    {
                        w[v] = w[u] + weight[v];
                    }
                    pre[v].insert(u);
                    num[v] = 0;
                    for (auto it = pre[v].begin(); it != pre[v].end(); ++it)
                    {
                        num[v] += num[*it];
                    }
                }
            }
        }
    }
}

void Entry()
{
    int n, m, s, e;
    scanf("%d%d%d%d", &n, &m, &s, &e);
    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &weight[i]);
    }
    for (int i = 0; i < m; ++i)
    {
        int u, v, wt;
        scanf("%d%d%d", &u, &v, &wt);
        G[u].push_back({v, wt});
        G[v].push_back({u, wt});
    }
    Bellman(s, n);
    printf("%d %d", d[e], w[e]);
}
}

namespace spfa_alg {
constexpr int kN = 505;
constexpr int kInf = 0x3fff'ffff;

struct Node
{
    int v_, dis_;
};
std::vector<Node> G[kN];
int d[kN], num[kN], n;
bool inq[kN];

bool Spfa(int s)
{
    std::fill(d, d + kN, kInf);
    std::memset(inq, false, sizeof(inq));
    std::memset(num, 0, sizeof(num));
    std::queue<int> Q;
    Q.push(s);
    inq[s] = true;
    ++num[s];
    d[s] = 0;
    while (!Q.empty())
    {
        int u = Q.front();
        Q.pop();
        inq[u] = false;
        for (Node node : G[u])
        {
            int v = node.v_;
            int dis = node.dis_;
            if (d[u] + dis < d[v])
            {
                d[v] = d[u] + dis;
                if (!inq[v])
                {
                    Q.push(v);
                    inq[v] = true;
                    ++num[v];
                    if (num[v] >= n) return false;
                }
            }
        }
    }
    return true;
}
}

namespace floyd {
constexpr int kInf = 0x3fff'ffff;
constexpr int kN = 200;

int dis[kN][kN], n, m;

void Floyd()
{
    for (int k = 0; k < n; ++k)
    {
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (dis[i][k] != kInf && dis[k][j] != kInf)
                {
                    if (dis[i][k] + dis[k][j] < dis[i][j])
                    {
                        dis[i][j] = dis[i][k] + dis[k][j];
                    }
                }
            }
        }
    }
}

void Entry()
{
    int u, v, w;
    std::fill(dis[0], dis[0] + kN * kN, kInf);
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++i)
    {
        dis[i][i] = 0;
    }
    for (int i = 0; i < m; ++i)
    {
        scanf("%d%d%d", &u, &v, &w);
        dis[u][v] = w;
    }
    Floyd();
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            printf("%d ", dis[i][j]);
        }
        printf("\n");
    }
}
}

namespace prim_matrix {
constexpr int kN = 1005;
constexpr int kInf = 0x3fff'ffff;

int G[kN][kN];
int d[kN];
bool visit[kN];

int Prim(int s, int n)
{
    std::fill(d, d + kN, kInf);
    d[s] = 0;
    int ans = 0;
    for (int i = 0; i < n; ++i)
    {
        int u = -1, min = kInf;
        for (int j = 0; j < n; ++j)
        {
            if (!visit[j] && d[j] < min)
            {
                u = j;
                min = d[j];
            }
        }
        if (u == -1) return -1;
        visit[u] = true;
        ans += d[u];
        for (int v = 0; v < n; ++v)
        {
            if (!visit[v] && G[u][v] != kInf && G[u][v] < d[v])
            {
                d[v] = G[u][v];
            }
        }

    }
    return ans;
}
}
namespace prim_adj {
constexpr int kN = 1005;
constexpr int kInf = 0x3fff'ffff;

struct Node
{
    int v_, dis_;
};
std::vector<Node> G[kN];
int d[kN];
bool visit[kN];

int Prim(int s, int n)
{
    std::fill(d, d + kN, kInf);
    d[s] = 0;
    int ans = 0;
    for (int i = 0; i < n; ++i)
    {
        int u = -1, min = kInf;
        for (int j = 0; j < n; ++j)
        {
            if (!visit[j] && d[j] < min)
            {
                u = j;
                min = d[j];
            }
        }
        if (u == -1) return -1;
        visit[u] = true;
        ans += d[u];
        for (Node node : G[u])
        {
            int v = node.v_;
            if (!visit[v] && node.dis_ < d[v])
            {
                d[v] = node.dis_;
            }
        }
    }
    return ans;
}
}

namespace alexander_prim {
constexpr int kN = 1005;
constexpr int kInf = 0x3fff'ffff;

int G[kN][kN], d[kN];
bool visit[kN];

int Prim(int s, int n)
{
    std::fill(d, d + kN, kInf);
    d[s] = 0;
    int ans = 0;
    for (int i = 0; i < n; ++i)
    {
        int u = -1, min = kInf;
        for (int j = 0; j < n; ++j)
        {
            if (!visit[j] && d[j] < min)
            {
                u = j;
                min = d[j];
            }
        }
        if (u == -1) return -1;
        visit[u] = true;
        ans += d[u];
        for (int v = 0; v < n; ++v)
        {
            if (!visit[v] && G[u][v] != kInf && G[u][v] < d[v])
            {
                d[v] = G[u][v];
            }
        }
    }
    return ans;
}

void Entry()
{
    int n, m, u, v, w;
    scanf("%d%d", &n, &m);
    std::fill(G[0], G[0] + kN * kN, kInf);
    for (int i = 0; i < m; ++i)
    {
        scanf("%d%d%d", &u, &v, &w);
        G[u][v] = G[v][u] = w;
    }
    int ans = Prim(0, n);
    printf("ans = %d\n", ans);
}
}

namespace kruskal {
constexpr int kE = 1005;
constexpr int kN = 1005;
constexpr int kInf = 0x3fff'ffff;

struct Edge
{
    int u_, v_;
    int weight_;
};
auto cmp = [](Edge a, Edge b)
{ return a.weight_ < b.weight_; };
Edge edges[kE];

//union-find
int father[kN];

int Find(int x)
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

int Kruskal(int n, int m)
{
    int sum_e_w = 0, n_edge = 0;
    for (int i = 0; i < n; ++i)
    {
        father[i] = i;
    }
    std::sort(edges, edges + m, cmp);
    for (int i = 0; i < m; ++i)
    {
        int fu = Find(edges[i].u_);
        int fv = Find(edges[i].v_);
        if (fu != fv)
        {
            father[fu] = fv;
            sum_e_w += edges[i].weight_;
            ++n_edge;
            if (n_edge == n - 1) break;
        }
    }
    if (n_edge != n - 1)
    {
        return -1;
    }
    return sum_e_w;
}

void Entry()
{
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; ++i)
    {
        scanf("%d%d%d", &edges[i].u_, &edges[i].v_, &edges[i].weight_);
    }
    int s = Kruskal(n, m);
    printf("sum_ew = %d", s);
}
}
namespace topological_sort {
//Directed Acyclic graph
constexpr int kN = 1005;
std::vector<int> G[kN];
int in_degree[kN], n, m;

bool TopologicalSort()
{
    int num = 0;
    std::queue<int> Q;
    for (int i = 0; i < n; ++i)
    {
        if (in_degree[i] == 0)
        {
            Q.push(i);
        }
    }
    while (!Q.empty())
    {
        int u = Q.front();
        printf("%d", u);
        Q.pop();
        for (int v : G[u])
        {
            --in_degree[v];
            if (in_degree[v] == 0)
            {
                Q.push(v);
            }
        }
        G[u].clear();
        ++num;
    }
    return num == n;
}
}

namespace dynamic {
namespace fibonacci {
constexpr int kL = 1005;

int dp[kL];

int F(int n)
{
    if (n == 0 || n == 1) return 1;
    if (dp[n] != -1) return dp[n];
    else
    {
        dp[n] = F(n - 1) + F(n - 2);
        return dp[n];
    }
}

void TestingFibonacci()
{
    std::memset(dp, -1, sizeof(dp));
    int cnt = 0;
    for (int i = 0; i < 65; ++i)
    {
        printf("%d", F(i));
        if (i < 64) printf(" ");
        if (++cnt % 10 == 0) printf("\n");
    }
    printf("\n");
}
}
namespace tower_problem {
constexpr int kN = 1005;

int tower[kN][kN], dp[kN][kN];

void Entry()
{
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= i; ++j)
        {
            scanf("%d", &tower[i][j]);
        }
    }
    for (int j = 1; j <= n; ++j)
    {
        dp[n][j] = tower[n][j];
    }
    for (int i = n - 1; i >= 1; --i)
    {
        for (int j = 1; j <= i; ++j)
        {
            dp[i][j] = std::max(dp[i + 1][j], dp[i + 1][j + 1]) + tower[i][j];
        }
    }
    printf("%d\n", dp[1][1]);
}
}
/*
 * Given a number sequence A1, A2,...,An,
 * find i, j(1<= i <= j <= n),make Ai+...+Aj the largest,
 * and output this largest sum.
 * Maximum consecutive subsequence sum
 */
namespace mcs {
constexpr int kN = 1005;

int A[kN], dp[kN];

void Entry()
{
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &A[i]);
    }
    dp[0] = A[0];
    for (int i = 1; i < n; ++i)
    {
        dp[i] = std::max(dp[i - 1] + A[i], A[i]);
    }
    int k = 0;
    for (int i = 1; i < n; ++i)
    {
        if (dp[i] > dp[k])
        {
            k = i;
        }
    }
    printf("%d", dp[k]);
}
}
/*
 * In a sequence of numbers,
 * find the longest subsequence (may not be continuous),
 * so that this subsequence is non-decreasing (non-decreasing).
 */
namespace lis {
constexpr int kN = 105;

int A[kN], dp[kN];

void Entry()
{
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &A[i]);
    }
    int max_len = -1;
    for (int i = 1; i <= n; ++i)
    {
        dp[i] = 1;
        for (int j = 1; j < i; ++j)
        {
            if (A[i] >= A[j] && dp[j] + 1 > dp[i])
            {
                dp[i] = dp[j] + 1;
            }
        }
        if (dp[i] > max_len) max_len = dp[i];
    }
    printf("%d", max_len);
}
}
/*
 * longest common subsequence, LCS
 * Given two strings (or sequence of numbers) A and B,
 * find a string such that this string is the longest common part of A and B (subsequences may not be continuous).
 */
namespace lcs {
constexpr int kN = 105;

char A[kN], B[kN];
int dp[kN][kN];

void Entry()
{
    scanf("%s%s", A + 1, B + 1);
    int len_a = strlen(A + 1);
    int len_b = strlen(B + 1);
//    boundary
    for (int i = 0; i <= len_a; ++i)
    {
        dp[i][0] = 0;
    }
    for (int j = 0; j <= len_b; ++j)
    {
        dp[0][j] = 0;
    }
//    state transition equation
    for (int i = 1; i <= len_a; ++i)
    {
        for (int j = 1; j <= len_b; ++j)
        {
            if (A[i] == B[j])
            {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            }
            else
            {
                dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }
    printf("%d", dp[len_a][len_b]);
}
}
/*
 * Longest palindrome string
 * Given a string s, find the length of the longest palindrome string of s.
 */
namespace lps {
constexpr int kN = 1005;

char s[kN], dp[kN][kN];

void Entry()
{
    scanf("%s", s);
    int len = strlen(s), ans = 1;
//    boundary
    for (int i = 0; i < len; ++i)
    {
        dp[i][i] = 1;
        if (i < len - 1)
        {
            if (s[i] == s[i + 1])
            {
                dp[i][i + 1] = 1;
                ans = 2;
            }
        }
    }
//    State transition equation
    for (int sub_l = 0; sub_l <= len; ++sub_l)
    {
        for (int i = 0; i + sub_l - 1 < len; ++i)
        {
            int j = i + sub_l - 1;
            if (s[i] == s[j] && dp[i + 1][j - 1] == 1)
            {
                dp[i][j] = 1;
                ans = sub_l;
            }
        }
    }
    printf("%d", ans);
}
}
/*
 * Directed Acyclic Graph
 * Given a directed acyclic graph,
 * how to find the one with the largest sum of weights among all paths in the entire graph.
 */
namespace dag {
constexpr int kN = 105;
constexpr int kInf = 0x3fff'ffff;

int G[kN][kN], choice[kN], n;
int dp[kN];
bool visit[kN];

int LongestOfPath_v1(int i)
{
    if (dp[i]) return dp[i];
    for (int j = 0; j < n; ++j)
    {
        if (G[i][j] != kInf)
        {
            dp[i] = std::max(dp[i], LongestOfPath_v1(j) + G[i][j]);
        }
    }
    return dp[i];
}

int LongestOfPath_v2(int i)
{
    if (dp[i]) return dp[i];
    for (int j = 0; j < n; ++j)
    {
        if (G[i][j] != kInf)
        {
            int tmp = LongestOfPath_v2(j) + G[i][j];
            if (tmp > dp[i])
            {
                dp[i] = tmp;
                choice[i] = j;
            }
        }
    }
    return dp[i];
}

/*
 * Before calling'PrintPath', you need to get the largest dp[i],
 * and then pass in i as the starting point of the path.
 */
void PrintPath(int i)
{
    printf("%d", i);
    while (choice[i] != -1)
    {
        i = choice[i];
        printf("->%d", i);
    }
}

int LongestOfPath_v3(int i)
{
    if (visit[i]) return dp[i];
    visit[i] = true;
    for (int j = 0; j < n; ++j)
    {
        if (G[i][j] != kInf)
        {
            dp[i] = std::max(dp[i], LongestOfPath_v3(j) + G[i][j]);
        }
    }
    return dp[i];
}
}

namespace bag_problem {
/*
 * 01 The knapsack problem is like this:
 * There are n items, and each item has a weight of w[i] and a value of c[i].
 * Now there is a backpack with a capacity of V.
 * Ask how to select items to put in the backpack to maximize the total value of the items in the backpack.
 * There is only one of each item.
 */
namespace bag_01 {
constexpr int kN = 105;
constexpr int kV = 1005;

int w[kN], c[kN], dp[kN];

void Entry()
{
    int n, V;
    scanf("%d%d", &n, &V);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &w[i]);
    }
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &c[i]);
    }
    for (int v = 0; v <= V; ++v)
    {
        dp[v] = 0;
    }
    for (int i = 1; i <= n; ++i)
    {
        for (int v = V; v >= w[i]; --v)
        {
            dp[v] = std::max(dp[v], dp[v - w[i]] + c[i]);
        }
    }
    int max = 0;
    for (int v = 0; v <= V; ++v)
    {
        if (dp[v] > max)
        {
            max = dp[v];
        }
    }
    printf("%d\n", max);
}
}
}
}

int main(int argc, char *argv[])
{
    pat_a1034::Entry();
    pat_a1076::Entry();
    shortest_path::pat_a1003::Entry();
    shortest_path::pat_a1030_v1::Entry();
    shortest_path::pat_a1030_v2::Entry();
    pat_a1003_v1::Entry();
    floyd::Entry();
    alexander_prim::Entry();
    kruskal::Entry();
    dynamic::fibonacci::TestingFibonacci();
    dynamic::tower_problem::Entry();
    dynamic::mcs::Entry();
    dynamic::lis::Entry();
    dynamic::lcs::Entry();
    dynamic::lps::Entry();
    dynamic::bag_problem::bag_01::Entry();
    return 0;
}



