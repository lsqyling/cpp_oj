#include <vector>
#include <stack>
#include <list>
#include <string>
#include <algorithm>
#include <map>
#include <unordered_map>
#include <cstring>

namespace bm42 {
class Solution
{
public:
    void push(int node)
    {
        stack1.push(node);
    }

    int pop()
    {
        if (stack2.empty())
        {
            while (!stack1.empty())
            {
                auto tmp = stack1.top();
                stack1.pop();
                stack2.push(tmp);
            }
        }
        auto top = stack2.top();
        stack2.pop();
        return top;
    }

private:
    std::stack<int> stack1;
    std::stack<int> stack2;
};
}

namespace bm43 {
class Solution
{
public:
    void push(int value)
    {
        list.push_back(value);
    }

    void pop()
    {
        list.pop_back();
    }

    int top()
    {
        return list.back();
    }

    int min()
    {
        int min = list.front();
        for (const auto &item : list)
        {
            if (item < min)
                min = item;
        }
        return min;
    }

private:
    std::list<int> list;
};
}

namespace bm44 {

class Solution
{
public:
    /**
     *
     * @param s string字符串
     * @return bool布尔型
     */
    bool isValid(std::string s)
    {
        std::stack<char> stack;
        for (int i = 0; i < s.size(); ++i)
        {
            switch (s[i])
            {
                case '[':
                    stack.push('[');
                    break;
                case '{':
                    stack.push('{');
                    break;
                case '(':
                    stack.push('(');
                    break;
                case ']':
                {
                    if (stack.empty())
                        return false;
                    auto top = stack.top();
                    stack.pop();
                    if (top != '[')
                        return false;
                    break;
                }
                case '}':
                {
                    if (stack.empty())
                        return false;
                    auto top = stack.top();
                    stack.pop();
                    if (top != '{')
                        return false;
                    break;
                }
                case ')':
                {
                    if (stack.empty())
                        return false;
                    auto top = stack.top();
                    stack.pop();
                    if (top != '(')
                        return false;
                    break;
                }
                default:
                    abort();
            }
        }
        return stack.empty();
    }
};
}

namespace bm45 {
class Solution
{
public:

    std::vector<int> maxInWindows(const std::vector<int> &num, unsigned int size)
    {
        std::vector<int> res;
        if (size == 0 || size > num.size())
            return res;
        std::deque<int> dq;
        for (int i = 0; i < size; ++i)
        {
            while (!dq.empty() && num[dq.back()] < num[i])
                dq.pop_back();
            dq.push_back(i);
        }

        for (int i = size; i < num.size(); ++i)
        {
            res.push_back(num[dq.front()]);
            while (!dq.empty() && dq.front() < i - size + 1)
                dq.pop_front();
            while (!dq.empty() && num[dq.back()] < num[i])
                dq.pop_back();
            dq.push_back(i);
        }
        res.push_back(num[dq.front()]);
        return res;
    }

    void test()
    {
        std::vector<int> num{2, 3, 4, 2, 6, 2, 5, 1};
        auto res = maxInWindows(num, 3);
        for (int i = 0; i < res.size(); ++i)
        {
            printf("%d ", res[i]);
        }
    }


};
}


namespace bm46 {
class Solution
{
public:
    int partition(std::vector<int> &num, int lo, int hi)
    {
        int pivot = num[lo];
        while (lo < hi)
        {
            while (lo < hi && num[hi] >= pivot) --hi;
            num[lo] = num[hi];
            while (lo < hi && num[lo] <= pivot) ++lo;
            num[hi] = num[lo];
        }
        num[lo] = pivot;
        return lo;
    }

    std::vector<int> GetLeastNumbers_Solution(std::vector<int> input, int k)
    {
        std::vector<int> ret;
        if (k == 0 || k > input.size())
            return ret;
        int lo = 0, hi = input.size() - 1;
        while (lo <= hi)
        {

            int p = partition(input, lo, hi);
            if (p + 1 == k)
                return std::vector<int>(input.begin(), input.begin() + k);
            else if (p + 1 < k)
                lo = p + 1;
            else
                hi = p - 1;
        }
        return ret;
    }

    void test()
    {
        std::vector<int> input{4,5,1,6,2,7,3,8};
        auto res = GetLeastNumbers_Solution(input, 4);
        for (const auto &item : res)
        {
            printf("%d ", item);
        }
    }
};
}

namespace bm47 {
class Solution
{
public:

    int partition(std::vector<int> &num, int lo, int hi)
    {
        int pivot = num[lo];
        while (lo < hi)
        {
            while (lo < hi && num[hi] >= pivot) --hi;
            num[lo] = num[hi];
            while (lo < hi && num[lo] <= pivot) ++lo;
            num[hi] = num[lo];
        }
        num[lo] = pivot;
        return lo;
    }

    int findkth_(std::vector<int> &num, int lo, int hi, int k)
    {
        int p = partition(num, lo, hi);
        if (p == num.size() - k)
            return num[p];
        else if (p < num.size() - k)
            return findkth_(num, p + 1, hi, k);
        else
            return findkth_(num, lo, p - 1, k);
    }



    int findKth(std::vector<int> a, int n, int K)
    {
        if (K == 0 || K > a.size())
            return -1;
        return findkth_(a, 0, a.size() - 1, K);
    }


    void test()
    {
        std::vector<int> num{10,10,9,9,8,7,5,6,4,3,4,2};
        printf("%d\n", findKth(num, 0, 1));
    }
};
}


namespace bm48 {
class Solution
{
public:
    std::vector<int> data_stream_;

    void Insert(int num)
    {
        if (data_stream_.empty())
            data_stream_.push_back(num);
        else
        {
            int i;
            for (i = 0; i < data_stream_.size(); ++i)
            {
                if (num <= data_stream_[i])
                    break;
            }
            data_stream_.insert(data_stream_.begin() + i, num);
        }
    }

    double GetMedian()
    {
        int n = data_stream_.size();
        if (n % 2 == 1)
        {
            return double(data_stream_[n/2]);
        }
        else
        {
            double x = data_stream_[n/2];
            double y = data_stream_[n/2-1];
            return (x + y) / 2;
        }
    }

};
}


namespace bm49 {

int get_char();
int peek();
int expr_value();
int item_value();
int factor_value();

char *p;

int get_char()
{
    int c;
    do
    {
        c = *p;
        ++p;
    } while (c == ' ');
    return c;
}

int peek()
{
    int c;
    do
    {
        c = *p;
        ++p;
    } while (c == ' ');
    --p;
    return c;
}


int factor_value()
{
    int res = 0;
    int c;

    c = peek();
    if (c == '(')
    {
        get_char();
        res = expr_value();
        get_char();
    }
    else
    {
        while (isdigit(c))
        {
            res = res * 10 + (c - '0');
            get_char();
            c = peek();
        }
    }
    return res;
}

int item_value()
{
    int res, val;
    int op;

    res = factor_value();
    while (1)
    {
        op = peek();
        if (op == '*' || op == '/')
        {
            get_char();
            val = factor_value();
            if (op == '*')
                res *= val;
            else
                res /= val;
        }
        else
        {
            break;
        }
    }
    return res;
}



int expr_value()
{
    int result, value;
    int op;

    result = item_value();
    while (1)
    {
        op = peek();
        if (op == '+' || op == '-')
        {
            get_char();
            value = item_value();
            if (op == '+')
                result += value;
            else
                result -= value;
        }
        else
        {
            break;
        }
    }
    return result;
}

int solve(char *s)
{
    p = s;
    return expr_value();
}
}

namespace bm50 {

class Solution
{
public:
    /**
     *
     * @param numbers int整型vector
     * @param target int整型
     * @return int整型vector
     */
    std::vector<int> twoSum(std::vector<int> &numbers, int target)
    {
        std::map<int, int> table;
        std::vector<int> res;

        for (int i = 0; i < numbers.size(); ++i)
        {
            int an = target - numbers[i];
            if (table.find(an) == table.end())
            {
                table[numbers[i]] = i + 1;
            }
            else
            {
                res.push_back(table[an]);
                res.push_back(i + 1);
                break;
            }
        }
        return res;
    }


    void test()
    {
        std::vector<int> num{20,70,110,150};
        auto res = twoSum(num, 90);
        for (const auto &item : res)
        {
            printf("%d ", item);
        }
        printf("\n");
    }
};
}

namespace bm51 {
class Solution
{
public:
    int MoreThanHalfNum_Solution(std::vector<int> numbers)
    {
        int target = numbers[0];
        int cnt = 1;

        for (int i = 1; i < numbers.size(); ++i)
        {
            if (cnt == 0)
            {
                target = numbers[i];
                cnt = 1;
            }
            else
            {
                if (target == numbers[i])
                    ++cnt;
                else
                    --cnt;
            }
        }
        return target;
    }
};
}

namespace bm52 {
class Solution
{
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     *
     * @param array int整型vector
     * @return int整型vector
     */
    std::vector<int> FindNumsAppearOnce(std::vector<int> &array)
    {
        int res = 0;
        for (int i = 0; i < array.size(); ++i)
        {
            res ^= array[i];
        }

        int bit = 1;
        while ((res & bit) == 0) bit <<= 1;

        int a = 0, b = 0;

        for (auto x : array)
        {
            if ((x & bit) == 0)
                a ^= x;
            else
                b ^= x;
        }
        if (a > b)
            return {b ,a};
        else
            return {a, b};
    }
};
}


namespace bm53 {
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
    int minNumberDisappeared(std::vector<int> &nums)
    {
        std::unordered_map<int, int> table;
        for (auto  x : nums)
        {
            ++table[x];
        }

        int n = 1;
        while (table.find(n) != table.end())
        {
            ++n;
        }
        return n;
    }
};
}


namespace bm54 {
class Solution
{
public:
    std::vector <std::vector<int>> threeSum(std::vector<int> &num)
    {
        if (num.size() < 3)
            return {};
        std::vector<std::vector<int>> res;
        std::sort(num.begin(), num.end());

        for (int k = 0; k < num.size() - 2; ++k)
        {
            if (k > 0 && num[k] == num[k-1])
                continue;

            for (int i = k + 1, j = num.size() - 1; i < j; )
            {
                if (num[k] + num[i] + num[j] < 0)
                    ++i;
                else if (num[k] + num[i] + num[j] > 0)
                    --j;
                else
                {
                    res.push_back({num[k], num[i], num[j]});
                    while (i < j && num[i] == num[i+1])
                        ++i;
                    while (i < j && num[j] == num[j-1])
                        --j;
                    ++i;
                    --j;
                }
            }
        }
        return res;
    }
};
}



int main()
{
    using bm50::Solution;
    Solution so;
    so.test();




    return 0;
}























































































