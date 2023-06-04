#include <vector>
#include <stack>
#include <list>
#include <string>
#include <algorithm>
#include <map>
#include <unordered_map>
#include <iostream>
#include <set>


namespace bm62 {
class Solution
{
public:
    int Fibonacci(int n)
    {
        int g = 0, q = 1;
        while (n--)
        {
            g = g + q;
            q = g -q;
        }

        return g;
    }

    void test()
    {
        for (int i = 1; i <= 10; ++i)
        {
            std::cout << Fibonacci(i) << " ";
        }

    }
};
}


namespace bm63 {
class Solution
{
public:

    struct fib
    {
        int operator()(int n)
        {
            g = 1;
            f = 0;
            while (n-- > 0)
            {
                g = g + f;
                f = g - f;
            }
            return g;
        }

        int g, f;
    };

    void test()
    {
        fib f;
        for (int i = 1; i < 10; ++i)
        {
            std::cout << f(i) << " ";
        }
    }


    int jumpFloor(int number)
    {
        fib f;

        return f(number);
    }
};
}

namespace bm64 {
class Solution
{
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     *
     * @param cost int整型vector
     * @return int整型
     */


    int minCostClimbingStairs(std::vector<int> &cost)
    {
        std::vector<int> dp(cost.size() + 1, 0);
        for (int i = 2; i <= cost.size(); ++i)
        {
            dp[i] = std::min(dp[i-1] + cost[i-1], dp[i-2] + cost[i-2]);
        }
        return dp[cost.size()];
    }
};
}

namespace bm65 {

class Solution
{
public:
    /**
     * longest common subsequence
     * @param s1 string字符串 the string
     * @param s2 string字符串 the string
     * @return string字符串
     */

    std::string same_of(int i, int j, std::string &s1, std::string &s2, std::vector<std::vector<int>> &b)
    {
        std::string res;
        if (i == 0 || j == 0)
            return res;
        if (b[i][j] == 1)
        {
            res += same_of(i - 1, j - 1, s1, s2, b);
            res += s1[i-1];
        }
        else if (b[i][j] == 2)
            res += same_of(i - 1, j, s1, s2, b);
        else if (b[i][j] == 3)
            res += same_of(i, j - 1, s1, s2, b);
        return res;
    }



    std::string LCS(std::string s1, std::string s2)
    {
        if (s1.empty() || s2.empty())
            return "-1";
        int len1 = s1.size();
        int len2 = s2.size();

        std::vector<std::vector<int>> dp(len1 + 1, std::vector<int>(len2 + 1, 0));
        std::vector<std::vector<int>> b(len1 + 1, std::vector<int>(len2 + 1, 0));
        for (int i = 1; i <= len1; ++i)
        {
            for (int j = 1; j <= len2; ++j)
            {
                if (s1[i-1] == s2[j-1])
                {
                    dp[i][j] = dp[i-1][j-1] + 1;
                    b[i][j] = 1;
                }
                else
                {
                    if (dp[i-1][j] > dp[i][j-1])
                    {
                        dp[i][j] = dp[i-1][j];
                        b[i][j] = 2;
                    }
                    else
                    {
                        dp[i][j] = dp[i][j-1];
                        b[i][j] = 3;
                    }
                }
            }
        }

        std::string res = same_of(len1, len2, s1, s2, b);
        return res.empty() ? "-1" : res;
    }

    void test()
    {
        std::cout << LCS("1A2C3D4B56", "B1D23A456A") << std::endl;

    }



};
}

namespace bm66 {

class Solution
{
public:
    /**
     * longest common substring
     * @param str1 string字符串 the string
     * @param str2 string字符串 the string
     * @return string字符串
     */
    std::string LCS(std::string str1, std::string str2)
    {
        int len1 = str1.size();
        int len2 = str2.size();
        std::vector<std::vector<int>> dp(len1 + 1, std::vector<int>(len2 + 1, 0));
        int max = 0;
        int pos = 0;
        for (int i = 1; i <= len1; ++i)
        {
            for (int j = 1; j <= len2; ++j)
            {
                if (str1[i-1] == str2[j-1])
                {
                    dp[i][j] = dp[i-1][j-1] + 1;
                }
                else
                {
                    dp[i][j] = 0;
                }
                if (dp[i][j] > max)
                {
                    max = dp[i][j];
                    pos = i - 1;
                }
            }
        }

        return str1.substr(pos - max +  1, max);
    }


    void test()
    {
        std::cout << LCS("1AB2345CD","12345EF") << std::endl;
    }
};
}

namespace bm67 {

class Solution
{
public:
    /**
     *
     * @param m int整型
     * @param n int整型
     * @return int整型
     */
    int uniquePaths(int m, int n)
    {
        if (m == 1 || n == 1)
            return 1;

        return uniquePaths(m - 1, n) + uniquePaths(m, n - 1);
    }
};
}

namespace bm68 {

class Solution
{
public:
    /**
     *
     * @param matrix int整型vector<vector<>> the matrix
     * @return int整型
     */
    int minPathSum(std::vector <std::vector<int>> &matrix)
    {
        int m = matrix.size();
        int n = matrix[0].size();
        std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1, 0));
        dp[0][0] = matrix[0][0];
//        the first column
        for (int i = 1; i < m; ++i)
        {
            dp[i][0] = dp[i-1][0] + matrix[i][0];
        }
//        the first line
        for (int j = 1; j < n; ++j)
        {
            dp[0][j] = dp[0][j-1] + matrix[0][j];
        }

        for (int i = 1; i < m; ++i)
        {
            for (int j = 1; j < n; ++j)
            {
                dp[i][j] = std::min(dp[i-1][j], dp[i][j-1]) + matrix[i][j];
            }
        }
        return dp[m-1][n-1];
    }
};
}

namespace bm69 {

class Solution
{
public:
    /**
     * 解码
     * @param nums string字符串 数字串
     * dp -> 用辅助数组dp表示前i个数的译码方法有多少种
     * @return int整型
     */
    int solve(std::string nums)
    {
        if (nums == "0")
            return 0;
        if (nums == "10" || nums == "20")
            return 1;

        for (int i = 1; i < nums.size(); ++i)
        {
            if (nums[i] == '0')
            {
                if (nums[i-1] != '1' && nums[i-1] != '2')
                    return 0;
            }
        }

        std::vector<int> dp(nums.size() + 1, 1);
        for (int i = 2; i <= nums.size(); ++i)
        {
//            11-19 21-26
            if ((nums[i-2] == '1' && nums[i-1] != '0') || (nums[i-2] == '2' && nums[i-1] >= '1' && nums[i-1] < '7'))
                dp[i] = dp[i-1] + dp[i-2];
            else
                dp[i] = dp[i-1];
        }

        return dp[nums.size()];
    }


    void test()
    {
        std::cout << solve("11") << std::endl;
    }



};
}

namespace bm70 {

class Solution
{
public:
    /**
     * 最少货币数
     * @param arr int整型vector the array
     * @param aim int整型 the target
     * @return int整型
     */
    int minMoney(std::vector<int> &arr, int aim)
    {
        if (aim < 1)
            return 0;

        std::vector<int> dp(aim + 1, aim + 1);
        dp[0] = 0;
        for (int i = 1; i <= aim; ++i)
        {
            for (int j = 0; j < arr.size(); ++j)
            {
                if (arr[j] <= i)
                {
                    dp[i] = std::min(dp[i], dp[i-arr[j] + 1]);
                }

            }
        }

        return dp[aim] > aim ? -1 : dp[aim];
    }
};
}

namespace bm71 {
class Solution
{
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     * 给定数组的最长严格上升子序列的长度。
     * @param arr int整型vector 给定的数组
     * @return int整型
     */
    int LIS(std::vector<int> &arr)
    {
        /*
         * Use dp[i] to represent the length of the longest subsequence at the end of element i,
         * initialized to 1, because only the array has elements,
         * and at least one is considered to be incremented.
         */
        std::vector<int> dp(arr.size(), 1);
        int res;
        for (int i = 1; i < arr.size(); ++i)
        {
            for (int j = 0; j < i; ++j)
            {
                if (arr[i] > arr[j] && dp[i] < dp[j] + 1)
                {
                    dp[i] = dp[j] + 1;
                    res = std::max(res, dp[i]);
                }
            }
        }

        return res;
    }
};
}

namespace bm72 {

class Solution
{
public:
    int FindGreatestSumOfSubArray(std::vector<int> array)
    {
        /*
         * The dp array can be used to represent the maximum continuous subarray
         * sum with the subscript i as the end point.
         */
        std::vector<int> dp(array.size(), 0);
        dp[0] = array[0];
        int maxsum = dp[0];
        for (int i = 1; i < array.size(); ++i)
        {
            dp[i] = std::max(dp[i-1] + array[i], array[i]);
            maxsum = std::max(maxsum, dp[i]);
        }

        return maxsum;
    }
};

}

namespace bm73 {
class Solution
{
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     *
     * @param A string字符串
     * @return int整型
     */
    int getLongestPalindrome(std::string A)
    {
//        Whether the substring from i to j is a palindrome substring
        int n = A.size();
        std::vector<std::vector<bool>> dp(n, std::vector<bool>(n, false));
        int max = 0;
        for (int c = 0; c <= n - 1; ++c)
        {
            for (int i = 0; i < n - c; ++i)
            {
                int j = i + c;
                if (A[i] == A[j])
                {
                    if (c <= 1)
                        dp[i][j] = true;
                    else
                        dp[i][j] = dp[i+1][j-1];
                    if (dp[i][j])
                        max = c + 1;
                }
            }
        }

        return max;
    }
};
}

namespace bm74 {

class Solution
{
public:
    /**
     *
     * @param s string字符串
     * @return string字符串vector
     */
    std::vector <std::string> restoreIpAddresses(std::string s)
    {
        int n = s.size();
        std::vector<std::string> res;
        for (int i = 1; i < 4 && i < n - 2; ++i)
        {
            for (int j = i + 1; j < i + 4 && j < n - 1; ++j)
            {
                for (int k = j + 1; k < j + 4 && k < n; ++k)
                {
                    if (n - k >= 4)
                        continue;
                    std::string a = s.substr(0, i);
                    std::string b = s.substr(i, j - i);
                    std::string c = s.substr(j, k - j);
                    std::string d = s.substr(k);
                    if (std::stoi(a) > 255 || std::stoi(b) > 255 || std::stoi(c) > 255 || std::stoi(d) > 255)
                        continue;
                    if (a.size() != 1 && a[0] == '0' || b.size() != 1 && b[0] == '0'
                        || c.size() != 1 && c[0] == '0' || d.size() != 1 && d[0] == '0')
                        continue;
                    std::string tmp = a + "." + b + "." + c + "." + d;
                    res.push_back(tmp);
                }
            }
        }

        return res;
    }
};
}

namespace bm75 {
class Solution
{
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     *
     * @param str1 string字符串
     * @param str2 string字符串
     * @return int整型
     */
    int editDistance(std::string str1, std::string str2)
    {
        int len1 = str1.size();
        int len2 = str2.size();

        std::vector<std::vector<int>> dp(len1 + 1, std::vector<int>(len2 + 1, 0));
        for (int i = 1; i <= len1; ++i)
        {
            dp[i][0] = dp[i-1][0] + 1;
        }
        for (int j = 1; j <= len2; ++j)
        {
            dp[0][j] = dp[0][j-1] + 1;
        }

        for (int i = 1; i <= len1; ++i)
        {
            for (int j = 1; j <= len2; ++j)
            {
                if (str1[i-1] == str2[j-1])
                    dp[i][j] = dp[i-1][j-1];
                else
                {
                    dp[i][j] = std::min(dp[i-1][j-1], std::min(dp[i-1][j], dp[i][j-1])) + 1;
                }
            }

        }

        return dp[len1][len2];
    }
};
}

namespace bm76 {
class Solution
{
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     *
     * @param str string字符串
     * @param pattern string字符串
     * @return bool布尔型
     */
    bool match(std::string str, std::string pattern)
    {
        int n = str.size();
        int m = pattern.size();
//        dp[i][j] represents whether the first i of str and the first j of pattern can match
        std::vector<std::vector<bool>> dp(n + 1, std::vector<bool>(m + 1, 0));

        dp[0][0] = 1;
        for (int j = 2; j <= m; ++j)
        {
            if (pattern[j-1] == '*')
                dp[0][j] = dp[0][j-2];
        }

        for (int i = 1; i <= n; ++i)
        {
            for (int j = 1; j <= m; ++j)
            {
                if (pattern[j-1] != '*')
                {
                    if (pattern[j-1] == '.' || str[i-1] == pattern[j-1])
                        dp[i][j] = dp[i-1][j-1];
                }
                else if (j >= 2)
                {

                    if (str[i-1] == pattern[j-2] || pattern[j-2] == '.')
                        dp[i][j] = dp[i-1][j] || dp[i][j-2];
                    else
                        dp[i][j] = dp[i][j-2];
                }
            }
        }

        return dp[n][m];
    }
};
}

namespace bm77 {

class Solution
{
public:
    /**
     *
     * @param s string字符串
     * @return int整型
     */
    int longestValidParentheses(std::string s)
    {
        std::stack<int> st;
        int res = 0;
        int start = -1;

        for (int i = 0; i < s.size(); ++i)
        {
            if (s[i] == '(')
                st.push(i);
            else
            {
                if (st.empty())
                    start = i;
                else
                {
                    st.pop();
                    if (!st.empty())
                        res = std::max(res, i - st.top());
                    else
                        res = std::max(res, i - start);
                }
            }
        }

        return res;
    }
};
}

namespace bm78 {
class Solution
{
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     *
     * @param nums int整型vector
     * @return int整型
     */
    int rob(std::vector<int> &nums)
    {
        std::vector<int> dp(nums.size() + 1, 0);
        dp[1] = nums[0];

        for (int i = 2; i <= nums.size(); ++i)
        {
            dp[i] = std::max(dp[i-1], dp[i-2] + nums[i-1]);
        }

        return dp[nums.size()];
    }
};
}

namespace bm79 {
class Solution
{
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     *
     * @param nums int整型vector
     * @return int整型
     */
    int rob(std::vector<int> &nums)
    {
        std::vector<int> dp(nums.size() + 1, 0);
        dp[1] = nums[0];

        for (int i = 2; i < nums.size(); ++i)
        {
            dp[i] = std::max(dp[i-1], dp[i-2] + nums[i-1]);
        }

        int res = dp[nums.size()-1];
        dp.clear();
        dp[1] = 0;
        for (int i = 2; i <= nums.size(); ++i)
        {
            dp[i] = std::max(dp[i-1], dp[i-2] + nums[i-1]);
        }

        return std::max(res, dp[nums.size()]);
    }
};
}

namespace bm80 {

class Solution
{
public:
    /**
     *
     * @param prices int整型vector
     * @return int整型
     */

    /*
     * 推导状态转移方程：
dp[i][0]：规定了今天不持股，有以下两种情况：
    昨天不持股，今天什么都不做；
    昨天持股，今天卖出股票（现金数增加），
    状态转移方程：dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] + prices[i]);
dp[i][1]：规定了今天持股，有以下两种情况：
    昨天持股，今天什么都不做（现金数与昨天一样）；
    昨天不持股，今天买入股票（注意：只允许交易一次，因此手上的现金数就是当天的股价的相反数）
    状态转移方程：dp[i][1] = max(dp[i - 1][1], -prices[i]);
     */
    int maxProfit(std::vector<int> &prices)
    {
        int len = prices.size();
        // 特殊判断
        if (len < 2) {
            return 0;
        }
        std::vector<std::vector<int>> dp(len, std::vector<int>(2, 0));

        // dp[i][0] 下标为 i 这天结束的时候，不持股，手上拥有的现金数
        // dp[i][1] 下标为 i 这天结束的时候，持股，手上拥有的现金数

        // 初始化：不持股显然为 0，持股就需要减去第 1 天（下标为 0）的股价
        dp[0][0] = 0;
        dp[0][1] = -prices[0];

        // 从第 2 天开始遍历
        for (int i = 1; i < len; i++) {
            dp[i][0] = std::max(dp[i - 1][0], dp[i - 1][1] + prices[i]);
            dp[i][1] = std::max(dp[i - 1][1], -prices[i]);
        }
        return dp[len - 1][0];
    }
};
}

namespace bm81 {

class Solution
{
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     * 计算最大收益
     * @param prices int整型vector 股票每一天的价格
     * @return int整型
     */
    int maxProfit(std::vector<int> &prices)
    {
        int ans = 0;
        for (int i = 1; i < prices.size(); ++i)
        {
            if (prices[i] > prices[i-1])
                ans += prices[i] - prices[i-1];
        }

        return ans;
    }
};
}

namespace bm82 {

class Solution
{
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     * 两次交易所能获得的最大收益
     * @param prices int整型vector 股票每一天的价格
     * @return int整型
     */
    int maxProfit(std::vector<int> &prices)
    {
        /*
         * dp[i][0]表示到第i天为止没有买过股票的最大收益
         * dp[i][1]表示到第i天为止买过一次股票还没有卖出的最大收益
         * dp[i][2]表示到第i天为止买过一次也卖出过一次股票的最大收益
         * dp[i][3]表示到第i天为止买过两次只卖出过一次股票的最大收益
         * dp[i][4]表示到第i天为止买过两次同时也买出过两次股票的最大收益
         */
        int n = prices.size();
        std::vector<std::vector<int>> dp(n, std::vector<int>(5, -1'000'000'000));

        dp[0][0] = 0;
        dp[0][1] = -prices[0];

        for (int i = 1; i < n; ++i)
        {
            dp[i][0] = dp[i-1][0];
            dp[i][1] = std::max(dp[i-1][1], dp[i-1][0] - prices[i]);
            dp[i][2] = std::max(dp[i-1][2], dp[i-1][1] + prices[i]);
            dp[i][3] = std::max(dp[i-1][3], dp[i-1][2] - prices[i]);
            dp[i][4] = std::max(dp[i-1][4], dp[i-1][3] + prices[i]);
        }


        return std::max(dp[n-1][2], dp[n-1][4]);
    }
};
}












































int main()
{
    using namespace bm69;
    Solution so;
    so.test();
    return 0;
}