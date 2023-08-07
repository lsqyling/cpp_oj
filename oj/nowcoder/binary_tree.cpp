#include <vector>
#include <queue>
#include <climits>
#include <complex>
#include <cstring>

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

namespace bm23 {
class Solution
{
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     *
     * @param root TreeNode类
     * @return int整型vector
     */
    void preorder(TreeNode *root, std::vector<int> &nums)
    {
        if (root == nullptr)
            return ;
        nums.push_back(root->val);
        preorder(root->left, nums);
        preorder(root->right, nums);
    }


    std::vector<int> preorderTraversal(TreeNode *root)
    {
        std::vector<int> nums;
        preorder(root, nums);
        return nums;
    }
};
}

namespace bm24 {
class Solution
{
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     *
     * @param root TreeNode类
     * @return int整型vector
     */

    void inorder(TreeNode *root, std::vector<int> &nums)
    {
        if (root == nullptr)
            return;
        inorder(root->left, nums);
        nums.push_back(root->val);
        inorder(root->right, nums);
    }


    std::vector<int> inorderTraversal(TreeNode *root)
    {
        std::vector<int> res;
        inorder(root, res);
        return res;
    }
};
}

namespace bm25 {
class Solution
{
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     *
     * @param root TreeNode类
     * @return int整型vector
     */
    void postorder(TreeNode *root, std::vector<int> &nums)
    {
        if (root == nullptr)
            return;
        postorder(root->left, nums);
        postorder(root->right, nums);
        nums.push_back(root->val);
    }


    std::vector<int> postorderTraversal(TreeNode *root)
    {
        std::vector<int> res;
        postorder(root, res);
        return res;
    }
};
}

namespace bm26 {
class Solution
{
public:
    /**
     *
     * @param root TreeNode类
     * @return int整型vector<vector<>>
     */
    std::vector <std::vector<int>> levelOrder(TreeNode *root)
    {
        std::vector<std::vector<int>> res;
        if (root == nullptr)
            return res;
        std::queue<TreeNode *> q;
        q.push(root);
        while (!q.empty())
        {
            int size = q.size();
            std::vector<int> tmp;
            while (size--)
            {
                auto front = q.front();
                q.pop();
                tmp.push_back(front->val);
                if (front->left)
                    q.push(front->left);
                if (front->right)
                    q.push(front->right);

            }

            if (tmp.size())
                res.push_back(tmp);

        }
        return res;
    }
};
}

namespace bm27 {
class Solution
{
public:
    std::vector <std::vector<int>> Print(TreeNode *pRoot)
    {
        std::vector<std::vector<int>> res;
        if (pRoot == nullptr)
            return res;
        std::queue<TreeNode *> q;
        q.push(pRoot);
        int level = 0;
        while (!q.empty())
        {
            int size = q.size();
            std::vector<int> tmp;
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
                res.push_back(tmp);
        }
        return res;
    }

};
}

namespace bm28 {
class Solution
{
public:
    /**
     *
     * @param root TreeNode类
     * @return int整型
     */

    int maxDepth(TreeNode *root)
    {
        if (root == nullptr)
            return 0;
        return std::max(maxDepth(root->left), maxDepth(root->right)) + 1;
    }
};
}

namespace bm29 {
class Solution
{
public:
    /**
     *
     * @param root TreeNode类
     * @param sum int整型
     * @return bool布尔型
     */

    bool dfs(TreeNode *node, int target)
    {
        if (node == nullptr)
            return false;
        target -= node->val;
        if (node->left == nullptr && node->right == nullptr && target == 0)
            return true;

        return dfs(node->left, target) || dfs(node->right, target);
    }



    bool hasPathSum(TreeNode *root, int sum)
    {
        return dfs(root, sum);
    }
};
}

namespace bm30 {
class Solution
{
public:

    TreeNode *prenode = nullptr;

    void inorder(TreeNode *root)
    {
        if (root == nullptr)
            return ;
        inorder(root->left);
        root->left = prenode;
        if (prenode)
            prenode->right = root;
        prenode = root;
        inorder(root->right);
    }

    TreeNode *Convert(TreeNode *pRootOfTree)
    {
        if (pRootOfTree == nullptr)
            return nullptr;
        auto p = pRootOfTree;
        while (p->left)
            p = p->left;

        inorder(pRootOfTree);

        return p;
    }
};
}

namespace bm31 {
class Solution
{
public:

    bool symmetrical_self(TreeNode *node1, TreeNode *node2)
    {
        if (node1 == nullptr && node2 == nullptr)
            return true;
        if (node1 == nullptr || node2 == nullptr || node1->val != node2->val)
            return false;
        return symmetrical_self(node1->left, node2->right)
               && symmetrical_self(node1->right, node2->left);

    }



    bool isSymmetrical(TreeNode *pRoot)
    {
        return symmetrical_self(pRoot, pRoot);

    }

};
}


namespace bm32 {
class Solution
{
public:
    /**
     *
     * @param t1 TreeNode类
     * @param t2 TreeNode类
     * @return TreeNode类
     */
    TreeNode *mergeTrees(TreeNode *t1, TreeNode *t2)
    {
        if (t1 == nullptr)
            return t2;
        if (t2 == nullptr)
            return t1;

        auto root = new TreeNode(t1->val + t2->val);
        root->left = mergeTrees(t1->left, t2->left);
        root->right = mergeTrees(t1->right, t2->right);
        return root;
    }
};
}

namespace bm33 {
class Solution
{
public:
    TreeNode *Mirror(TreeNode *pRoot)
    {
        if (pRoot == nullptr)
            return pRoot;

        Mirror(pRoot->left);
        Mirror(pRoot->right);
        std::swap(pRoot->left, pRoot->right);

        return pRoot;
    }
};
}

namespace bm34 {
class Solution
{
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     *
     * @param root TreeNode类
     * @return bool布尔型
     */

    long pre = INT_MIN;

    bool isValidBST(TreeNode *root)
    {
        if (root == nullptr)
            return true;
        if (!isValidBST(root->left))
            return false;

        if (root->val <= pre)
            return false;
        pre = root->val;
        if (!isValidBST(root->right))
            return false;
        return true;
    }
};
}

namespace bm35 {
class Solution
{
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     *
     * @param root TreeNode类
     * @return bool布尔型
     */
    bool isCompleteTree(TreeNode *root)
    {
        if (root == nullptr)
            return true;
        std::queue<TreeNode *> q;
        q.push(root);
        bool flag = false;
        while (!q.empty())
        {
            auto front = q.front();
            q.pop();
            if (front == nullptr)
            {
                flag = true;
            }
            else
            {
                if (flag)
                    return false;
                q.push(front->left);
                q.push(front->right);
            }
        }
        return true;
    }
};
}

namespace bm36 {
class Solution
{
public:

    int height_of(TreeNode *root)
    {
        if (root == nullptr)
            return 0;
        return std::max(height_of(root->left), height_of(root->right)) + 1;
    }



    bool IsBalanced_Solution(TreeNode *pRoot)
    {
        if (pRoot == nullptr)
            return true;
        int left_high = height_of(pRoot->left);
        int right_high = height_of(pRoot->right);

        if (std::abs(left_high - right_high) > 1)
            return false;
        return IsBalanced_Solution(pRoot->left) && IsBalanced_Solution(pRoot->right);
    }
};
}

namespace bm37 {
class Solution
{
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     *
     * @param root TreeNode类
     * @param p int整型
     * @param q int整型
     * @return int整型
     */
     std::vector<int> get_path(TreeNode *root, int x)
    {
         std::vector<int> path;
         auto node = root;
        while (node->val != x)
        {
            path.push_back(node->val);
            if (x < node->val)
                node = node->left;
            else
                node = node->right;
        }
        path.push_back(x);
        return path;
    }

    int lowestCommonAncestor(TreeNode *root, int p, int q)
    {
        std::vector<int> p_path = get_path(root, p);
        std::vector<int> q_path = get_path(root, q);

        int res;
        for (int i = 0; i < p_path.size() && i < q_path.size(); ++i)
        {
            if (p_path[i] == q_path[i])
                res = p_path[i];
            else
                break;
        }
        return res;
    }
};
}

namespace bm38 {
class Solution {
public:
    /**
     *
     * @param root TreeNode类
     * @param o1 int整型
     * @param o2 int整型
     * @return int整型
     */
    bool found = false;
    void dfs(TreeNode *root, int target, std::vector<int> &tmp)
    {
        if (found || root == nullptr)
            return ;
        tmp.push_back(root->val);
        if (root->val == target)
        {
            found = true;
            return ;
        }
        dfs(root->left, target, tmp);
        dfs(root->right, target, tmp);
        if (found)
            return ;
        tmp.pop_back();
    }


    int lowestCommonAncestor(TreeNode* root, int o1, int o2) {
        std::vector<int> path_o1, path_o2;
        dfs(root, o1, path_o1);
        this->found = false;
        dfs(root, o2, path_o2);

        int res;
        for (int i = 0; i < path_o1.size() && i < path_o2.size(); ++i)
        {
            if (path_o1[i] == path_o2[i])
                res = path_o1[i];
            else
                break;
        }
        return res;
    }

    void test()
    {
        auto node0 = new TreeNode(0);
        auto node1 = new TreeNode(1);
        auto node2 = new TreeNode(2);
        auto node3 = new TreeNode(3);
        auto node4 = new TreeNode(4);
        auto node5 = new TreeNode(5);
        auto node6 = new TreeNode(6);
        auto node7 = new TreeNode(7);
        auto node8 = new TreeNode(8);

        auto root = node3;
        node3->left = node5;
        node3->right = node1;

        node5->left = node6;
        node5->right = node2;

        node1->left = node0;
        node1->right = node8;

        node2->left = node7;
        node2->right = node4;

        printf("%d\n", lowestCommonAncestor(root, 7, 6));
    }
};
}

namespace bm39 {
class Solution
{
public:
    void serialize_func(TreeNode *root, std::string &res)
    {
        if (root == nullptr)
        {
            res += "#";
            return ;
        }

        res += std::to_string(root->val) + "!";
        serialize_func(root->left, res);
        serialize_func(root->right, res);
    }


    const char *Serialize(TreeNode *root)
    {
        if (root == nullptr)
            return "#";
        std::string res;
        serialize_func(root, res);
        char *char_res = new char[res.size() + 1];
        memset(char_res, '\0', res.size() + 1);
        strcpy(char_res, res.c_str());
        return char_res;
    }


    TreeNode *deserialize_func(char *&str)
    {
        if (*str == '#')
        {
            ++str;
            return nullptr;
        }
        int val = 0;
        while (*str != '!' && *str != '\0')
        {
            val = val * 10 + (*str - '0');
            ++str;
        }
        auto root = new TreeNode(val);
        if (*str == '\0')
            return root;
        else
            ++str;
        root->left = deserialize_func(str);
        root->right = deserialize_func(str);
        return root;
    }


    TreeNode *Deserialize(char *str)
    {
        if (*str == '#')
            return nullptr;
        return deserialize_func(str);
    }
};
}

namespace bm40 {
class Solution
{
public:
    std::vector<int> pre_, in_;

    TreeNode *build(int preL, int preR, int inL, int inR)
    {
        if (preL > preR)
            return nullptr;
        auto root = new TreeNode(pre_[preL]);

        int k;
        for (k = inL; k <= inR; ++k)
        {
            if (in_[k] == pre_[preL])
                break;
        }
        int left_num = k - inL;

        root->left = build(preL + 1, preL + left_num, inL, k - 1);
        root->right = build(preL + left_num + 1, preR, k + 1, inR);
        return root;
    }



    TreeNode *reConstructBinaryTree(const std::vector<int> &pre, const std::vector<int> &vin)
    {
        this->pre_ = pre;
        this->in_ = vin;

        if (pre.empty())
            return nullptr;

        return build(0, pre.size() - 1, 0, vin.size() - 1);
    }
};
}

namespace bm41 {
class Solution
{
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     * 求二叉树的右视图
     * @param xianxu int整型vector 先序遍历
     * @param zhongxu int整型vector 中序遍历
     * @return int整型vector
     */
    std::vector<int> pre_, in_;

    TreeNode *build(int preL, int preR, int inL, int inR)
    {
        if (preL > preR)
            return nullptr;
        auto root = new TreeNode(pre_[preL]);

        int k;
        for (k = inL; k <= inR; ++k)
        {
            if (in_[k] == pre_[preL])
                break;
        }
        int left_num = k - inL;

        root->left = build(preL + 1, preL + left_num, inL, k - 1);
        root->right = build(preL + left_num + 1, preR, k + 1, inR);
        return root;
    }



    TreeNode *reconstruct(std::vector<int> &pre, std::vector<int> &vin)
    {
        this->pre_ = pre;
        this->in_ = vin;

        if (pre.empty())
            return nullptr;

        return build(0, pre.size() - 1, 0, vin.size() - 1);
    }


    std::vector<int> solve(std::vector<int> &xianxu, std::vector<int> &zhongxu)
    {
        auto root = reconstruct(xianxu, zhongxu);
        if (root == nullptr)
            return {};

        std::vector<int> res;
        std::queue<TreeNode *> q;
        q.push(root);
        while (!q.empty())
        {
            int size = q.size();
            std::vector<int> tmp;
            while (size--)
            {
                auto front = q.front();
                q.pop();
                tmp.push_back(front->val);

                if (front->left)
                    q.push(front->left);
                if (front->right)
                    q.push(front->right);
            }
            if (!tmp.empty())
                res.push_back(tmp[tmp.size() - 1]);
        }
        return res;
    }
};











}


































































































int main()
{
    bm38::Solution so;
    so.test();
    printf("%lld", 0x3fff'ffffLL * 2);
    return 0;
}