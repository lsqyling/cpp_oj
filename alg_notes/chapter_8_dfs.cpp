//
// Created by shiqing on 2021/4/5.
//
#include <algorithm>
#include <cstdio>
#include <queue>

/*
 * Q:有n件物品，每件物品的重量为w[i],价值为c[i].现在需要选出若干件物品放入一个容量为V的背包中，使得选入背包的物品的重量和容量不超过V的
 * 前提下，让背包中物品的价值之和为最大，求最大值.(1 <= n <= 20)
 */
namespace bag {
constexpr int kN = 25;

int n, V, max_value = 0;
int w[kN], c[kN];

void Dfs(int index, int sum_w, int sum_c)
{
    if (index == n)
    {
        if (sum_w <= V && sum_c > max_value)
        {
            max_value = sum_c;
        }
        return;
    }
    Dfs(index + 1, sum_w, sum_c);
    Dfs(index + 1, sum_w + w[index], sum_c + c[index]);
}

void DfsMoreEfficient(int index, int sum_w, int sum_c)
{
    if (index == n)
    {
        return;
    }
    DfsMoreEfficient(index + 1, sum_w, sum_c);
    if (sum_w + w[index] <= V)
    {
        if (sum_c + c[index] > max_value)
        {
            max_value = sum_c + c[index];
        }
        DfsMoreEfficient(index + 1, sum_w + w[index], sum_c + c[index]);
    }
}

void TestingDfs()
{
    scanf("%d%d", &n, &V);
    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &w[i]);
    }
    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &c[i]);
    }
    Dfs(0, 0, 0);
    printf("max_value = %d\n", max_value);
}

void TestingDfsMoreEfficient()
{
    scanf("%d%d", &n, &V);
    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &w[i]);
    }
    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &c[i]);
    }
    DfsMoreEfficient(0, 0, 0);
    printf("max_value = %d\n", max_value);
}
}

/*
 * Q:给定一个整数N(可能为负数), 从中选择K个数，使得这K个数之和等于一个的数X;如果有多种方案, 选择它们中元素平方和最大的一个。数据保证
 * 这样的方案唯一。
 */
namespace enumerate_subsequence {
constexpr int kMaxN = 15;

int n, k, x, max_sum_squ = -1, A[kMaxN];
std::vector<int> tmp, ans;

void Dfs(int index, int now_k, int sum, int sum_squ)
{
    if (now_k == k && sum == x)
    {
        if (sum_squ > max_sum_squ)
        {
            max_sum_squ = sum_squ;
            ans = tmp;
        }
        return;
    }
    if (index == n || now_k > k || sum > x)
    {
        return;
    }
    tmp.push_back(A[index]);
    Dfs(index + 1, now_k + 1, sum + A[index], sum_squ + A[index] * A[index]);
    tmp.pop_back();
    Dfs(index + 1, now_k, sum, sum_squ);
}
}

namespace matrix_search_1_block {
constexpr int kN = 105;

int matrix[kN][kN], n, m;
bool inq[kN][kN];

struct Node
{
    int x_, y_;
};

int X[4] = {0, 0, 1, -1};
int Y[4] = {-1, 1, 0, 0};

bool judgeVisited(int x, int y)
{
    if (x >= m || x < 0 || y >= n || y < 0)
    {
        return false;
    }
    if (matrix[x][y] == 0 || inq[x][y])
    {
        return false;
    }
    return true;
}

void Bfs(int x, int y)
{
    std::queue<Node> Q;
    Q.push({x, y});
    inq[x][y] = true;
    while (!Q.empty())
    {
        auto top = Q.front();
        Q.pop();
        for (int i = 0; i < 4; ++i)
        {
            int new_x = top.x_ + X[i];
            int new_y = top.y_ + Y[i];
            if (judgeVisited(new_x, new_y))
            {
                Q.push({new_x, new_y});
                inq[new_x][new_y] = true;
            }
        }
    }
}

void Entry()
{
    scanf("%d%d", &m, &n);
    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            scanf("%d", &matrix[i][j]);
        }
    }
    int ans = 0;
    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (matrix[i][j] == 1 && !inq[i][j])
            {
                Bfs(i, j);
                ++ans;
            }
        }
    }
    printf("%d", ans);
}
}

namespace matrix_find_min_steps {
constexpr int kN = 105;

char matrix[kN][kN];
int m, n;
bool inq[kN][kN];
int X[4] = {0, 0, 1, -1};
int Y[4] = {-1, 1, 0, 0};

struct Node
{
    int x_, y_;
    int step;
};

bool IsValid(int x, int y)
{
    if (x >= m || x < 0 || y >= n || y < 0)
    {
        return false;
    }
    if (matrix[x][y] == '*')
    {
        return false;
    }
    if (inq[x][y]) return false;
    return true;
}

int Bfs(int x, int y, int x_end, int y_end)
{
    std::queue<Node> Q;
    Q.push({x, y, 0});
    inq[x][y] = true;
    while (!Q.empty())
    {
        auto top = Q.front();
        Q.pop();
        if (top.x_ == x_end && top.y_ == y_end)
        {
            return top.step;
        }
        for (int i = 0; i < 4; ++i)
        {
            int new_x = top.x_ + X[i];
            int new_y = top.y_ + Y[i];
            if (IsValid(new_x, new_y))
            {
                Q.push({new_x, new_y, top.step + 1});
                inq[new_x][new_y] = true;
            }
        }
    }
    return -1;
}

void Entry()
{
    scanf("%d%d", &m, &n);
    for (int i = 0; i < m; ++i)
    {
        scanf("%s", matrix[i]);
    }
    Node S, T;
    scanf("%d%d%d%d", &S.x_, &S.y_, &T.x_, &T.y_);
    int min_steps = Bfs(S.x_, S.y_, T.x_, T.y_);
    printf("min_step = %d", min_steps);
}
}


int main(int argc, char *argv[])
{
    bag::TestingDfs();
    bag::TestingDfsMoreEfficient();
    matrix_search_1_block::Entry();
    matrix_find_min_steps::Entry();

    return 0;
}
