#include <vector>
#include <iostream>
#include <map>
#include <unordered_map>
#include <queue>

namespace nc140 {

class Solution
{
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     * 将给定数组排序
     * @param arr int整型vector 待排序的数组
     * @return int整型vector
     */
    std::vector<int> MySort(std::vector<int> &arr)
    {
        /*
         * quick sort
         */
        quick_sort(arr, 0, arr.size() - 1);

        /*
         * insert sort
         */
        insert_sort(arr);
        /*
         * shell sort
         */
        shell_sort(arr);


        return arr;
    }
    
    /*
     * quick sort [2, 3, 5, 6, 0, 4, 2] [low, high]
     */
    void quick_sort(std::vector<int> &array, int low, int high)
    {
        if (low >= high)
            return;
        int pivot = partition(array, low, high);
        quick_sort(array, low, pivot);
        quick_sort(array, pivot + 1, high);
    }
    
    int partition(std::vector<int> &array, int low, int high)
    {
        int pivot = array[low];
        while (low < high)
        {
            while (low < high && pivot <= array[high]) --high;
            array[low] = array[high];
            while (low < high && pivot >= array[low]) ++low;
            array[high] = array[low];
        }
        array[low] = pivot;
        return low;
    }

    void bubble_sort(std::vector<int> &arr)
    {
        int n = arr.size();
        for (int i = 0; i < n - 1; ++i)
        {
            bool flag = true;
            for (int j = n - 1; j > i; --j)
            {
                if (arr[j-1] > arr[j])
                {
                    std::swap(arr[j-1], arr[j]);
                    flag = false;
                }
            }
            if (flag)
                return ;
        }
    }

    void insert_sort(std::vector<int> &array)
    {
        int n = array.size();
        int k, j;
        for (int i = 1; i < n; ++i)
        {
            k = array[i];
            for (j = i - 1; j >= 0 && array[j] > k; --j)
            {
                array[j+1] = array[j];
            }
            array[j+1] = k;
        }
    }

    void shell_sort(std::vector<int> &array)
    {
        int n = array.size();
        int h = 1;
        while (h < n/3) h = h * 3 + 1;
        while (h >= 1)
        {
            for (int i = 0 + h, t, j; i < n; ++i)
            {
                t = array[i];
                for (j = i - h; j >= 0 && array[j] > t; j -= h)
                {
                    array[j+h] = array[j];
                }
                array[j+h] = t;
            }
            h /= 3;
        }
    }
};
}

namespace test_inline {
class base
{
public:
    virtual void say();
};

inline void base::say()
{
    std::cout << "hello, base!" << std::endl;
}

class derived : public base
{
public:
    void say() override;

};

inline void derived::say()
{
    std::cout << "hello, derived!" << std::endl;
}
}

namespace template_test {
template<class T>
concept C = std::is_integral_v<typename T::type> || (sizeof(T) > 1);
static_assert(C<double>);
}

struct TreeNode
{
    int val;
    TreeNode *left = nullptr, *right = nullptr;
};

namespace nc45 {
class Solution
{
public:
    /**
     *
     * @param root TreeNode类 the root of binary tree
     * @return int整型vector<vector<>>
     */

    void preorder(TreeNode *root, std::vector<int> &res)
    {
        if (root == nullptr)
            return ;
        res.push_back(root->val);
        preorder(root->left, res);
        preorder(root->right, res);
    }

    void inorder(TreeNode *root, std::vector<int> &res)
    {
        if (root == nullptr)
            return ;
        inorder(root->left, res);
        res.push_back(root->val);
        inorder(root->right, res);
    }

    void postorder(TreeNode *root, std::vector<int> &res)
    {
        if (root == nullptr)
            return ;
        postorder(root->left, res);
        postorder(root->right, res);
        res.push_back(root->val);
    }

    std::vector<std::vector<int> > threeOrders(TreeNode *root)
    {
        std::vector<int> pre, in, post;
        preorder(root, pre);
        inorder(root, in);
        postorder(root, post);

        return {pre, in, post};
    }
};
}
/*
 * NC119 最小的K个数
 */
namespace nc119 {
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

/*
 * NC88 寻找第K大
 */
namespace nc88 {
class Solution
{
public:

    int partition(std::vector<int> &arr, int lo, int hi)
    {
        int pivot = arr[lo];
        while (lo < hi)
        {
            while (lo < hi && arr[hi] >= pivot) --hi;
            arr[lo] = arr[hi];
            while (lo < hi && arr[lo] <= pivot) ++lo;
            arr[hi] = arr[lo];
        }
        arr[lo] = pivot;
        return lo;
    }

    int findkth_(std::vector<int> &arr, int lo, int hi, int K)
    {
        int p = partition(arr, lo, hi);
        if (p == arr.size() - K)
            return arr[p];
        else if (p < arr.size() - K)
            return findkth_(arr, p + 1, hi, K);
        else
            return findkth_(arr, lo, p - 1, K);
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
        printf("%d", findKth(num, 0, 5));
    }

};
}

/*
 * NC61 两数之和
 */
namespace nc61 {

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
            int two = target - numbers[i];
            if (table.find(two) == table.end())
            {
                table[numbers[i]] = i + 1;
            }
            else
            {
                res.push_back(table[two]);
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

/*
 * NC33 合并两个排序的链表
 */
struct ListNode
{
    int val;
    ListNode *next;
    explicit ListNode(int n = 0) : val(n), next(nullptr) {}
};

namespace nc33 {
class Solution {
public:
    ListNode *Merge(ListNode *pHead1, ListNode *pHead2)
    {
        ListNode *head = new ListNode;
        ListNode *cur = head;
        ListNode *p1, *p2;

        for (p1 = pHead1, p2 = pHead2; p1 && p2; )
        {
            if (p1->val <= p2->val)
            {
                cur->next = new ListNode(p1->val);
                p1 = p1->next;
            }
            else
            {
                cur->next = new ListNode(p2->val);
                p2 = p2->next;
            }
            cur = cur->next;
        }
        while (p1)
        {
            cur->next = new ListNode(p1->val);
            p1 = p1->next;
            cur = cur->next;
        }
        while (p2)
        {
            cur->next = new ListNode(p2->val);
            p2 = p2->next;
            cur = cur->next;
        }

        return head->next;
    }

};
}
/*
 * NC50 链表中的节点每k个一组翻转
 */
namespace nc50 {
class Solution
{
public:
    /**
     *
     * @param head ListNode类
     * @param k int整型
     * @return ListNode类
     */
    ListNode *reverseKGroup(ListNode *head, int k)
    {
        ListNode *tail = head;
        for (int i = 0; i < k; ++i)
        {
            if (tail == nullptr)
                return head;
            tail = tail->next;
        }

        ListNode *prev = nullptr;
        ListNode *cur = head;
        while (cur != tail)
        {
            auto tmp = cur->next;
            cur->next = prev;

            prev = cur;
            cur = tmp;
        }
        head->next = reverseKGroup(tail, k);
        return prev;
    }


};
}

/*
 * NC19 连续子数组的最大和
 */
namespace nc19 {
class Solution
{
public:
    int FindGreatestSumOfSubArray(std::vector<int> array)
    {
        std::vector<int> dp(array.size(), 0);
        dp[0] = array[0];
        int maxsum = array[0];

        for (int i = 1; i < array.size(); ++i)
        {
            dp[i] = std::max(array[i], dp[i-1] + array[i]);
            maxsum = std::max(maxsum, dp[i]);
        }
        return maxsum;
    }
};
}

/*
 * NC41 最长无重复子数组
 */
namespace nc41 {
class Solution
{
public:
    int maxLength(std::vector<int> &arr)
    {
        std::unordered_map<int, int> window;
        int left = 0;
        int right = 0;
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

/*
 * NC4 判断链表中是否有环
 */
namespace nc4 {
class Solution
{
public:
    bool hasCycle(ListNode *head)
    {
        ListNode *fast, *slow;
        slow = fast = head;
        while (slow && fast)
        {
            if (fast->next)
                fast = fast->next->next;
            else
                return false;
            slow = slow->next;

            if (slow == fast)
                return true;
        }
        return false;
    }
};
}

/*
 * NC3 链表中环的入口结点
 */
namespace nc3 {
class Solution
{
public:
    void remove_prefix_zero(std::string &s)
    {
        auto it = s.begin();
        while (s.size() > 1 && *it == '0')
            s.erase(it);
    }

    void test()
    {
        std::string s0 = "00000";
        std::string s1 = "00100";
        std::string s2 = "10000";
        std::string s3 = "0";
        remove_prefix_zero(s0);
        remove_prefix_zero(s1);
        remove_prefix_zero(s2);
        remove_prefix_zero(s3);
        std::cout << s0 << std::endl;
        std::cout << s1 << std::endl;
        std::cout << s2 << std::endl;
        std::cout << s3 << std::endl;

    }

    ListNode *EntryNodeOfLoop(ListNode *pHead)
    {
        ListNode *fast, *slow;
        fast = slow = pHead;

        while (fast && fast->next)
        {
            fast = fast->next->next;
            slow = slow->next;
            if (fast == slow)
                break;
        }

        if (fast == nullptr || fast->next == nullptr)
            return nullptr;
        fast = pHead;

        while (fast != slow)
        {
            fast = fast->next;
            slow = slow->next;
        }

        return fast;
    }
};
}

/*
 * NC14 按之字形顺序打印二叉树
 */
namespace nc14 {
class Solution
{
public:
    std::vector<std::vector<int>> Print(TreeNode *pRoot)
    {
        std::vector<std::vector<int>> res;
        if (pRoot == nullptr)
            return res;
        std::queue<TreeNode *>  q;
        q.push(pRoot);
        int level = 0;
        while (!q.empty())
        {
            std::vector<int> tmp;
            int size = q.size();
            while (size-- > 0)
            {
                auto front = q.front();
                q.pop();

                if (front->left)
                    q.push(front->left);
                if (front->right)
                    q.push(front->right);

                if (level % 2 == 0)
                    tmp.push_back(front->val);
                else
                    tmp.insert(tmp.begin(), front->val);
            }
            ++level;
            if (!tmp.empty())
                res.emplace_back(tmp);
        }
        return res;
    }

};
}

/*
 * NC127 最长公共子串
 */
namespace nc127 {
class Solution
{
public:
    std::string LCS(std::string str1, std::string str2)
    {
//        dp[i][j]表示到s1第i个个到s2第j个为止的公共子串长度
        int len1 = str1.size();
        int len2 = str2.size();
        std::vector<std::vector<int>> dp(len1 + 1, std::vector<int>(len2 + 1, 0));
        int max = 0;
        int pos = 0;
        for (int i = 1; i <= len1; ++i)
        {
            for (int j = 1; j <= len2; ++j)
            {
                if (str1[i - 1] == str2[j - 1])
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                else
                    dp[i][j] = 0;

                if (dp[i][j] > max)
                {
                    max = dp[i][j];
                    pos = i - 1;
                }
            }
        }
        return str1.substr(pos - max + 1, max);
    }
};
}

namespace bs {
/*
 * [left, right]--->[0, n-1]
 */
int binary_search(int A[], int left, int right, int x)
{
    int mid;
    while (left <= right)
    {
        mid = left + (right - left) / 2;
        if (A[mid] == x)
            return mid;
        else if (A[mid] < x)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -1;
}

/*
 * [left, right] ---> [0, n]
 */
int lower_bound(int A[], int left, int right, int x)
{
    int mid;
    while (left < right)
    {
        mid = left + (right - left) / 2;
        if (A[mid] >= x)
            right = mid;
        else
            left = mid + 1;
    }
    return left;
}

/*
 * [left, right] ---> [0, n]
 */
int upper_bound(int A[], int left, int right, int x)
{
    int mid;
    while (left < right)
    {
        mid = left + (right - left) / 2;
        if (A[mid] > x)
            right = mid;
        else
            left = mid + 1;
    }
    return left;
}
}

/*
 * NC66 两个链表的第一个公共结点
 */
namespace nc66 {
class Solution
{
public:
    ListNode *reverse(ListNode *pHead)
    {
        ListNode *pre = nullptr;
        ListNode *cur = pHead;

        while (cur != nullptr)
        {
            auto tmp = cur->next;

            cur->next = pre;
            pre = cur;
            cur = tmp;
        }

        return pre;
    }

    ListNode *FindFirstCommonNode(ListNode *pHead1, ListNode *pHead2)
    {
        ListNode *p1 = pHead1;
        ListNode *p2 = pHead2;

        while (p1 != p2)
        {
            p1 = p1 == nullptr ? pHead2 : p1->next;
            p2 = p2 == nullptr ? pHead1 : p2->next;
        }

        return p1;
    }
};
}




































int main()
{
    using namespace nc3;
    Solution so;
    so.test();


    return 0;
}
