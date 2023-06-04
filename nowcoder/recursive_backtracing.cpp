#include <vector>
#include <stack>
#include <list>
#include <string>
#include <algorithm>
#include <map>
#include <unordered_map>
#include <cstring>
#include <iostream>
#include <set>

namespace bm55 {
class Solution
{
public:


    void permute_(std::vector<std::vector<int>> &res, std::vector<int> &num, int index)
    {
        if (index == num.size())
        {
            res.push_back(num);
            return ;
        }
        for (int i = index; i < num.size(); ++i)
        {
            std::swap(num[i], num[index]);
            permute_(res, num, index + 1);
            std::swap(num[i], num[index]);
        }
    }



    std::vector <std::vector<int>> permute(std::vector<int> &num)
    {
        if (num.empty())
            return {};

        std::sort(num.begin(), num.end());
        std::vector<std::vector<int>> res;

        permute_(res, num, 0);
        return res;
    }
};
}

namespace bm56 {
class Solution
{
public:
    using matrix_t = std::vector<std::vector<int>>;


    int visit[10];

    void permute_(std::vector<int> &num, matrix_t &res, std::vector<int> &tmp)
    {
        if (tmp.size() == num.size())
        {
            res.push_back(tmp);
            return ;
        }
        for (int i = 0; i < num.size(); ++i)
        {
            if (visit[i])
                continue;
            if (i > 0 && num[i-1] == num[i] && !visit[i-1])
                continue;
            visit[i] = 1;
            tmp.push_back(num[i]);
            permute_(num, res, tmp);
            visit[i] = 0;
            tmp.pop_back();
        }
    }


    std::vector <std::vector<int>> permuteUnique(std::vector<int> &num)
    {
        memset(visit, 0, sizeof(visit));
        std::sort(num.begin(), num.end());
        matrix_t res;
        std::vector<int> tmp;
        permute_(num, res, tmp);
        return res;
    }
};
}

namespace bm57 {
class Solution
{
public:
    /**
     * 判断岛屿数量
     * @param grid char字符型vector<vector<>>
     * @return int整型
     */

    using matrix_t = std::vector<std::vector<char>>;

    void dfs(matrix_t &grid, int i, int j)
    {
        int m = grid.size();
        int n = grid[0].size();

        grid[i][j] = '0';
        if (i - 1 >= 0 && grid[i-1][j] == '1')
            dfs(grid, i - 1, j);
        if (i + 1 < m && grid[i+1][j] == '1')
            dfs(grid, i + 1, j);
        if (j - 1 >= 0 && grid[i][j-1] == '1')
            dfs(grid, i, j - 1);
        if (j + 1 < n && grid[i][j+1] == '1')
            dfs(grid, i, j + 1);
    }

    int solve(std::vector <std::vector<char>> &grid)
    {
        int m = grid.size();
        if (m == 0)
            return 0;
        int n = grid[0].size();
        int count = 0;
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (grid[i][j] == '1')
                {
                    ++count;
                    dfs(grid, i, j);

                }
            }
        }

        return count;
    }
};


}

namespace bm58 {
class Solution
{
public:

    char tmp[10]{'\0'};
    int hash_table[10]{0};

    void permute_(int index, std::string &str, std::vector<std::string> &res)
    {
        if (index == str.size())
        {
            res.push_back(tmp);
            return ;
        }

        for (int i = 0; i < str.size(); ++i)
        {
            if (!hash_table[i])
            {
                tmp[index] = str[i];
                hash_table[i] = 1;
                permute_(index + 1, str, res);
                hash_table[i] = 0;
            }
        }
    }



    std::vector <std::string> Permutation(std::string str)
    {
        std::vector<std::string> res;
        permute_(0, str, res);
        std::set<std::string> unique{res.begin(), res.end()};
        return {unique.begin(), unique.end()};
    }

    void test()
    {
        auto res = Permutation("ABCDEF");
        for (const auto &str : res)
        {
            std::cout << str << std::endl;
        }
    }
};
}

namespace bm59 {

class Solution
{
public:
    /**
     *
     * @param n int整型 the n
     * @return int整型
     */

    int p[10]{0};
    int hash_table[10]{0};

    void permute_(int index, int &count, int n)
    {
        if (index == n + 1)
        {
            ++count;
            return ;
        }
        for (int i = 1; i <= n; ++i)
        {
            if (!hash_table[i])
            {
                bool flag = true;
                for (int j = 1; j < index; ++j)
                {
                    if (std::abs(index - j) == std::abs(i - p[j]))
                    {
                        flag = false;
                        break;
                    }
                }
                if (flag)
                {
                    p[index] = i;
                    hash_table[i] = 1;
                    permute_(index + 1, count, n);
                    hash_table[i] = 0;
                }
            }
        }
    }


    int Nqueen(int n)
    {
        int count = 0;
        permute_(1, count, n);
        return count;
    }
};
}

namespace bm60 {

class Solution
{
public:
    /**
     *
     * @param n int整型
     * @return string字符串vector
     */

    void parenthesis_(int left, int right, std::string tmp, int n, std::vector<std::string> &res)
    {
        if (left == n && right == n)
        {
            res.push_back(tmp);
            return ;
        }
        if (left < n)
            parenthesis_(left + 1, right, tmp + "(", n, res);
        if (right < n && right < left)
            parenthesis_(left, right + 1, tmp + ")", n, res);
    }



    std::vector <std::string> generateParenthesis(int n)
    {
        std::string tmp;
        std::vector<std::string> res;
        parenthesis_(0, 0, tmp, n, res);
        return res;
    }
};
}

namespace bm61 {

class Solution
{
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     * 递增路径的最大长度
     * @param matrix int整型vector<vector<>> 描述矩阵的每个数
     * @return int整型
     */
    int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    int m, n;

    int dfs(int i, int j, std::vector<std::vector<int>> &matrix, std::vector<std::vector<int>> &dp)
    {
        if (dp[i][j])
            return dp[i][j];
        ++dp[i][j];
        for (int k = 0; k < 4; ++k)
        {
            int nexti = i + dirs[k][0];
            int nextj = j + dirs[k][1];

            if (nexti >= 0 && nexti < n && nextj >= 0 && nextj < m && matrix[i][j] < matrix[nexti][nextj])
                dp[i][j] = std::max(dp[i][j], dfs(nexti, nextj, matrix, dp) + 1);
        }
        return dp[i][j];
    }

    int solve(std::vector <std::vector<int>> &matrix)
    {
        if (matrix.empty() || matrix[0].empty())
            return 0;

        int res = 0;
        n = matrix.size();
        m = matrix[0].size();

        std::vector<std::vector<int>> dp(n, std::vector<int>(m));
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < m; ++j)
            {
                res = std::max(res, dfs(i, j, matrix, dp));
            }
        }
        return res;
    }
};
}




















int main()
{
    using namespace bm58;
    Solution so;
    so.test();


    return 0;
}