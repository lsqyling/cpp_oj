#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <climits>
#include <list>
#include <set>

using std::string;
namespace bm83 {
/*
 *
 */
class Solution
{
public:

    void reverse(std::string &s, int i, int j, bool flag)
    {
        for (; i < j; ++i, --j)
        {
            std::swap(s[i], s[j]);
            if (flag)
            {
                if (islower(s[i])) s[i] = toupper(s[i]);
                else if (isupper(s[i])) s[i] = tolower(s[i]);
                if (islower(s[j])) s[j] = toupper(s[j]);
                else if (isupper(s[j])) s[j] = tolower(s[j]);
            }
        }
        if (i == j && flag)
        {
            if (islower(s[i])) s[i] = toupper(s[i]);
            else if (isupper(s[i])) s[i] = tolower(s[i]);
        }

    }




    std::string trans(std::string s, int n)
    {
        reverse(s, 0, n - 1, true);
        for (int i = 0, j = 0; j < n; )
        {
            while (i < n && s[i] == ' ') ++i;
            j = i;
            while (j < n && s[j] != ' ') ++j;
            reverse(s, i, j - 1, false);
            i = j;
        }
        return s;
    }

    void test()
    {
        std::vector<string> list{"This is a sample", "nowcoder", "iOS"};
        for (auto item : list)
        {
            std::cout  << item << std::endl;
            std::cout << trans(item, item.size()) << std::endl;
        }

        string s("iOS");
        std::cout << trans(s, s.size()) << std::endl;

    }
};
}


namespace bm84 {

class Solution
{
public:
    /**
     *
     * @param strs string字符串vector
     * @return string字符串
     */
    string longestCommonPrefix(std::vector <string> &strs)
    {
        if (strs.empty())
            return {};
        if (strs.size() == 1)
            return strs[0];
        int j;
        bool flag = false;
        for (j = 0; ; ++j)
        {
            for (int i = 1; i < strs.size(); ++i)
            {
                if (j >= std::min(strs[i].size(), strs[i-1].size()) || strs[i][j] != strs[i-1][j])
                {
                    flag = true;
                    break;
                }
            }
            if (flag)
                break;
        }
        return strs[0].substr(0, j);
    }

    void test()
    {
        std::vector<string> strs = {"c","c"};
        std::cout << longestCommonPrefix(strs) << std::endl;
    }
};
}

namespace bm85 {

class Solution
{
public:
    /**
     * 验证IP地址
     * @param IP string字符串 一个IP地址字符串
     * @return string字符串
     */
    std::vector<string> split(string str, string spliter)
    {
        std::vector<string> res;
        string::size_type i;
        while ((i = str.find(spliter)) != string::npos)
        {
            res.push_back(str.substr(0, i));
            str = str.substr(i + 1);
        }
        res.push_back(str);
        return res;
    }

    bool is_ipv4(string ip)
    {
        std::vector<string> s = split(ip, ".");
        if (s.size() != 4)
            return false;

        for (int i = 0; i < s.size(); ++i)
        {
            if (s[i].empty())
                return false;

            if (s[i].size() > 3 || (s[i][0] == '0' && s[i].size() != 1))
                return false;
            for (int j = 0; j < s[i].size(); ++j)
            {
                if (!isdigit(s[i][j]))
                    return false;
            }
            int n = std::stoi(s[i]);
            if (n < 0 || n > 255)
                return false;
        }
        return true;
    }


    bool is_ipv6(string ip)
    {
        std::vector<string> s = split(ip, ":");
        if (s.size() != 8)
            return false;
        for (int i = 0; i < s.size(); ++i)
        {
            if (s[i].empty() || s[i].size() > 4)
                return false;
            for (int j = 0; j < s[i].size(); ++j)
            {
                if (!((s[i][j] >= 'a' && s[i][j] < 'f') || (s[i][j] >= 'A' && s[i][j] <= 'F') || isdigit(s[i][j])))
                    return false;
            }
        }
        return true;
    }


    string solve(string IP)
    {
        if (is_ipv4(IP))
            return "IPv4";
        else if (is_ipv6(IP))
            return "IPv6";
        else
            return "Neither";
    }


    void test()
    {

    }
};
}

namespace bm86 {

class Solution
{
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     * 计算两个数之和
     * @param s string字符串 表示第一个整数
     * @param t string字符串 表示第二个整数
     * @return string字符串
     */

    void remove_prefix_zero(string &s)
    {
        auto it = s.begin();
        while (s.size() > 1 && *it == '0')
        {
            s.erase(it);
            it = s.begin();
        }
    }

    string solve(string s, string t)
    {
        int dif = s.size() - t.size();
        if (dif < 0)
        {
            int n = -dif;
            while (n--)
                s.insert(s.begin(), '0');
        }
        else if (dif > 0)
        {
            int n = dif;
            while (n--)
                t.insert(t.begin(), '0');
        }

        string ans;
        int r = 0, sum;
        for (int i = s.size() - 1; i >= 0; --i)
        {
            sum = (s[i] - '0') + (t[i] - '0') + r;
            ans.insert(ans.begin(), sum % 10 + '0');
            r = sum / 10;
        }
        if (r)
            ans.insert(ans.begin(), r + '0');
        remove_prefix_zero(ans);
        return ans;
    }

    void test()
    {
        std::cout << solve("1", "99") << std::endl;
        std::cout << solve("114514", "") << std::endl;
        std::cout << solve("0123456789", "0123456789") << std::endl;
    }
};
}

namespace bm87 {
class Solution
{
public:
    void merge(int A[], int m, int B[], int n)
    {
        int *tmp = new int[m+n];
        int i, j, k;
        k = 0;
        for (i = j = 0; i < m && j < n; )
        {
            if (A[i] <= B[j])
                tmp[k++] = A[i++];
            else
                tmp[k++] = B[j++];
        }
        while (j < n) tmp[k++] = B[j++];
        while (i < m) tmp[k++] = A[i++];

        for (int s = 0; s < m + n; ++s)
        {
            A[s] = tmp[s];
        }
        delete[] tmp;
    }
};
}

namespace bm88 {

class Solution
{
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     * @param str string字符串 待判断的字符串
     * @return bool布尔型
     */
    bool judge(string str)
    {
        for (int i = 0, j = str.size(); i < j; ++i, --j)
        {
            if (str[i] != str[j])
                return false;
        }
        return true;
    }
};
}

namespace bm89 {

struct Interval
{
    int start;
    int end;

    Interval() : start(0), end(0)
    {
    }

    Interval(int s, int e) : start(s), end(e)
    {
    }
};

class Solution
{
public:
    std::vector <Interval> merge(std::vector <Interval> &intervals)
    {
        std::vector<Interval> res;
        if (intervals.empty())
            return res;
        auto cmp = [](Interval a, Interval b)
        {
            return a.start < b.start;
        };
        std::sort(intervals.begin(), intervals.end(), cmp);
        res.push_back(intervals[0]);
        for (int i = 1; i < intervals.size(); ++i)
        {
            if (intervals[i].start <= res.back().end)
                res.back().end = std::max(intervals[i].end, res.back().end);
            else
                res.push_back(intervals[i]);
        }
        return res;
    }
};
}

namespace bm90 {

class Solution
{
public:
    /**
     *
     * @param S string字符串
     * @param T string字符串
     * @return string字符串
     */
    string minWindow(string S, string T)
    {
        std::unordered_map<char, int> window, need;
        for (auto c : T)
            ++need[c];

        int left = 0, right = 0;
        int valid = 0;
        int start = 0, len = INT_MAX;

        while (right < S.size())
        {
            char c = S[right];
            ++right;
            if (need.count(c))
            {
                ++window[c];
                if (window[c] == need[c])
                    ++valid;
            }

            while (valid == need.size())
            {
                if (right - left < len)
                {
                    start = left;
                    len = right - left;
                }
                char d = S[left];
                ++left;

                if (need.count(d))
                {
                    if (window[d] == need[d])
                        --valid;
                    --window[d];
                }
            }
        }

        return len == INT_MAX ? "" : S.substr(start, len);
    }
};
}

namespace bm91 {

class Solution
{
public:
    /**
     * 反转字符串
     * @param str string字符串
     * @return string字符串
     */
    string solve(string str)
    {
        for (int i = 0, j = str.size() - 1; i < j; ++i, --j)
            std::swap(str[i], str[j]);
        return str;
    }
};
}

namespace bm92 {

class Solution
{
public:
    /**
     *
     * @param arr int整型vector the array
     * @return int整型
     */
    int maxLength(std::vector<int> &arr)
    {
        std::unordered_map<char, int> window;
        int left = 0, right = 0;
        int res = 0;

        while (right < arr.size())
        {
            int c = arr[right];
            ++right;
            ++window[c];

            while (window[c] > 1)
            {
                int d = arr[left];
                ++left;
                --window[d];
            }
            res = std::max(res, right - left);
        }
        return res;
    }
};
}

namespace bm93 {
class Solution
{
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     *
     * @param height int整型vector
     * @return int整型
     */
    int maxArea(std::vector<int> &height)
    {
        if (height.size() < 2)
            return 0;
        int left = 0, right = height.size() - 1;
        int res = 0;

        while (left < right)
        {
            int capacity = std::min(height[left], height[right]) * (right - left);
            res = std::max(res, capacity);
            if (height[left] < height[right])
                ++left;
            else
                --right;
        }

        return res;
    }
};
}

namespace bm94 {

class Solution
{
public:
    /**
     * max water
     * @param arr int整型vector the array
     * @return long长整型
     */
    long long maxWater(std::vector<int> &arr)
    {
        if (arr.empty())
            return 0;
        int left = 0;
        int right = arr.size() - 1;
        int res = 0;

        int l_max = arr[left];
        int r_max = arr[right];

        while (left <= right)
        {
            l_max = std::max(l_max, arr[left]);
            r_max = std::max(r_max, arr[right]);

            if (l_max < r_max)
            {
                res += l_max - arr[left];
                ++left;
            }
            else
            {
                res += r_max - arr[right];
                --right;
            }
        }
        return res;
    }
};
}

namespace bm95 {

class Solution
{
public:
    /**
     * pick candy
     * @param arr int整型vector the array
     * @return int整型
     */
    int candy(std::vector<int> &arr)
    {
        std::vector<int> num(arr.size(), 1);
        for (int i = 1; i < arr.size(); ++i)
        {
            if (arr[i-1] < arr[i])
                num[i] = num[i-1] + 1;
        }

        int res = num[arr.size() - 1];
        for (int j = arr.size() - 2; j >= 0; --j)
        {
            if (arr[j] > arr[j+1] && num[j] <= num[j+1])
            {
                num[j] = num[j+1] + 1;
            }
            res += num[j];
        }

        return res;
    }
};
}

namespace bm96 {

class Solution
{
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     * 计算成功举办活动需要多少名主持人
     * @param n int整型 有n个活动
     * @param startEnd int整型vector<vector<>> startEnd[i][0]用于表示第i个活动的开始时间，startEnd[i][1]表示第i个活动的结束时间
     * @return int整型
     */
    int minmumNumberOfHost(int n, std::vector <std::vector<int>> &startEnd)
    {
        std::vector<int> start, end;
        for (int i = 0; i < n; ++i)
        {
            start.push_back(startEnd[i][0]);
            end.push_back(startEnd[i][1]);
        }

        std::sort(start.begin(), start.end());
        std::sort(end.begin(), end.end());
        int res = 0;
        int j = 0;
        for (int i = 0; i < n; ++i)
        {
            if (start[i] >= end[j])
                ++j;
            else
                ++res;
        }

        return res;
    }
};
}

namespace bm97 {

class Solution
{
public:
    /**
     * 旋转数组
     * @param n int整型 数组长度
     * @param m int整型 右移距离
     * @param a int整型vector 给定数组
     * @return int整型vector
     */

    void reverse(std::vector<int> &array, int i, int j)
    {
        for (; i < j; ++i, --j)
            std::swap(array[i], array[j]);
    }

    std::vector<int> solve(int n, int m, std::vector<int> &a)
    {
        m = m % n;
        reverse(a, 0, n - 1);
        reverse(a, 0, m - 1);
        reverse(a, m, n - 1);
        return a;
    }
};
}

namespace bm98 {
class Solution
{
public:
    std::vector<int> spiralOrder(std::vector <std::vector<int>> &matrix)
    {
        if (matrix.empty())
            return {};
        std::vector<int> ans;
        int left, right, up, down;

        left = up = 0;
        right = matrix[0].size() - 1;
        down = matrix.size() - 1;
        while (left <= right && up <= down)
        {
            for (int i = left; i <= right; ++i)
            {
                ans.push_back(matrix[up][i]);
            }
            ++up;
            if (up > down)
                break;
            for (int i = up; i <= down; ++i)
            {
                ans.push_back(matrix[i][right]);
            }
            --right;
            if (right < left)
                break;
            for (int i = right; i >= left; --i)
            {
                ans.push_back(matrix[down][i]);
            }
            --down;
            if (up > down)
                break;
            for (int i = down; i >= up; --i)
            {
                ans.push_back(matrix[i][left]);
            }
            ++left;
            if (left > right)
                break;
        }

        return ans;
    }
};
}

namespace bm99 {
class Solution
{
public:
    std::vector <std::vector<int>> rotateMatrix(std::vector <std::vector<int>> mat, int n)
    {
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < i; ++j)
            {
                std::swap(mat[i][j], mat[j][i]);
            }
        }

        for (int i = 0; i < n; ++i)
        {
            std::reverse(mat[i].begin(), mat[i].end());
        }

        return mat;
    }
};
}
namespace detail {

template<class K, class V>
class lru_cache
{
public:

    explicit lru_cache(int cap) : capacity_(cap) {}

    V get(K key, V null = V{});
    void put(K key, V val);

private:



    int capacity_;
    std::list<K> cache_;
    std::unordered_map<K, V> store_;
};

template<class K, class V>
V lru_cache<K, V>::get(K key, V null)
{
    if (!store_.count(key))
        return null;

    cache_.remove(key);
    cache_.push_back(key);
    return store_[key];
}

template<class K, class V>
void lru_cache<K, V>::put(K key, V val)
{
    if (store_.count(key))
    {
        cache_.remove(key);
        cache_.push_back(key);
        store_[key] = val;
        return ;
    }
    if (capacity_ == cache_.size())
    {
        K tmp = cache_.front();
        cache_.pop_front();
        store_.erase(tmp);
    }

    cache_.push_back(key);
    store_[key] = val;

}

}
namespace bm100 {

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* solution = new Solution(capacity);
 * int output = solution->get(key);
 * solution->set(key,value);
 */

/*
 * ["set","set","set","get","set","get"],[[1,1],[2,2],[3,2],[1],[4,4],[2]],3
 * ["null","null","null","1","null","-1"]
 * ["null","null","null","1","null","2"]
 */

using namespace detail;
using cache_t = lru_cache<int, int>;
class Solution
{
public:
    Solution(int capacity) : lru_(capacity)
    {
    }

    int get(int key)
    {
        return lru_.get(key, -1);
    }

    void set(int key, int value)
    {
        lru_.put(key, value);
    }

    void test()
    {
        set(1, 1);
        std::cout << "null, ";
        set(2, 2);
        std::cout << "null, ";
        set(3, 2);
        std::cout << "null, ";
        std::cout << get(1) << ", ";



        set(4, 4);
        std::cout << "null" << ", ";
        std::cout << get(2) << ", ";
    }





private:
    cache_t lru_;
};

}

namespace detail {
template<class K, class V>
class lfu_cache
{
public:

    explicit lfu_cache(int cap) : capacity_(cap) {}


    V get(K key, V null = V{});

    void put(K key, V val);



private:
    int capacity_;
    std::set<int> frequency_;
    std::unordered_map<K, V> kv_table_;
    std::unordered_map<K, int> kf_table_;
    std::unordered_map<int, std::list<K>> fk_table_;
};

template<class K, class V>
V lfu_cache<K, V>::get(K key, V null)
{
    if (!kv_table_.count(key))
        return null;

    int freq = kf_table_[key];
    if (fk_table_[freq].size() > 1)
        fk_table_[freq].remove(key);
    else
    {
        fk_table_.erase(freq);
        frequency_.erase(freq);
    }
    ++kf_table_[key];
    fk_table_[freq+1].push_back(key);
    frequency_.insert(freq + 1);
    return kv_table_[key];
}

template<class K, class V>
void lfu_cache<K, V>::put(K key, V val)
{
    if (kv_table_.count(key))
    {
        kv_table_[key] = val;
        int freq = kf_table_[key];
        ++kf_table_[key];

        if (fk_table_[freq].size() > 1)
            fk_table_[freq].remove(key);
        else
            fk_table_.erase(freq);
        fk_table_[freq + 1].push_back(key);
        frequency_.insert(freq + 1);

        return ;
    }
    if (kv_table_.size() == capacity_)
    {
        int min_freq = *frequency_.begin();
        K tmp_k = fk_table_[min_freq].front();
        fk_table_[min_freq].pop_front();
        if (fk_table_[min_freq].empty())
        {
            fk_table_.erase(min_freq);
            frequency_.erase(min_freq);
            kf_table_.erase(tmp_k);
        }
        else
        {
            --kf_table_[tmp_k];
        }
        kv_table_.erase(tmp_k);
    }
    kv_table_[key] = val;
    ++kf_table_[key];
    fk_table_[1].push_back(key);
    frequency_.insert(1);
}
}


namespace bm101 {

class Solution
{
public:
    /**
     * lfu design
     * @param operators int整型vector<vector<>> ops
     * @param k int整型 the k
     * @return int整型vector
     */
    std::vector<int> LFU(std::vector <std::vector<int>> &operators, int k)
    {
        detail::lfu_cache<int, int> lfu(k);
        std::vector<int> res;

        for (int i = 0; i < operators.size(); ++i)
        {
            auto op = operators[i];
            if(op[0] == 1)
                //set操作
                lfu.put(op[1], op[2]);
            else
                //get操作
                res.push_back(lfu.get(op[1], -1));
        }
        return res;
    }

    void test()
    {
        std::vector<std::vector<int>> operators{{1,1,1},
                                                {1,2,2},
                                                {1,3,3},
                                                {1,4,4},
                                                {2,4},
                                                {2,3},
                                                {2,2},
                                                {2,1},
                                                {1,5,5},
                                                {2,4}};

        auto res = LFU(operators, 4);
        for (const auto &item : res)
        {
            std::cout << item << ", ";
        }
    }






};
}


namespace test_virtual {
class base
{
public:
    virtual base *get_instance();
};

base *base::get_instance()
{
    return this;
}

class derived : public base
{
public:
    derived *get_instance() override;

public:

};

derived *derived::get_instance()
{
    return this;
}

}










































int main()
{
    using namespace bm101;
    Solution so;
    so.test();




    return 0;
}