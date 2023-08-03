#include <iostream>
#include <vector>
#include <algorithm>

struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

namespace bm1_reverselist {
class Solution
{
public:
    ListNode* ReverseList(ListNode* pHead)
    {
        ListNode *prev, *curr, *next;
        prev = nullptr, curr = pHead;
        while (curr)
        {
            next = curr->next;
            curr->next = prev;

            prev = curr;
            curr = next;
        }
        return prev;
    }
};
}

namespace bm2 {
class Solution
{
public:
    /**
     *
     * @param head ListNode类
     * @param m int整型
     * @param n int整型
     * @return ListNode类
     */

    ListNode *reverseList(ListNode *head)
    {
        ListNode *cur = head, *prev = nullptr;
        ListNode *next;
        while (cur)
        {
            next = cur->next;

            cur->next = prev;
            prev = cur;
            cur = next;
        }
        return prev;
    }

    ListNode *reverseBetween(ListNode *head, int m, int n)
    {
        ListNode *mnode, *prevm = nullptr, *nnode, *nextn;
        ListNode *p = head;

        if ((m == 1 && n == 1) || m == n)
            return head;

        for (int i = 1; p; ++i)
        {
            if (i == m - 1)
                prevm = p;
            if (i == m)
                mnode = p;
            if (i == n)
                nnode = p;
            p = p->next;
        }
        nextn = nnode->next;
        nnode->next = nullptr;

        if (prevm)
        {
            prevm->next = nullptr;
            prevm->next = reverseList(mnode);
        }
        else
        {
            head = reverseList(mnode);
        }
        mnode->next = nextn;

        return head;
    }
};
}

namespace bm3 {
class Solution
{
public:
    ListNode *reverseKGroup(ListNode *head, int k)
    {
        ListNode *tail = head;
        for (int i = 0; i < k; ++i)
        {
            if (tail == nullptr)
                return head;
            tail = tail->next;
        }
        ListNode *prev, *curr;
        prev = nullptr, curr = head;
        while (curr != tail)
        {
            auto tmp = curr->next;
            curr->next = prev;

            prev = curr;
            curr = tmp;
        }
        head->next = reverseKGroup(tail, k);
        return prev;
    }

};
}

namespace bm4 {
class Solution
{
public:
    ListNode *Merge(ListNode *pHead1, ListNode *pHead2)
    {
        ListNode *head = new ListNode(0);
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

namespace bm5 {
class Solution
{
public:
    ListNode *merge(ListNode *head1, ListNode *head2)
    {
        if (head1 == nullptr)
            return head2;
        if (head2 == nullptr)
            return head1;

        ListNode *head = new ListNode(0);
        ListNode *cur = head;
        while (head1 && head2)
        {
            if (head1->val <= head2->val)
            {
                cur->next = new ListNode(head1->val);
                head1 = head1->next;
            }
            else
            {
                cur->next = new ListNode(head2->val);
                head2 = head2->next;
            }
            cur = cur->next;
        }
        if (head1)
            cur->next = head1;
        if (head2)
            cur->next = head2;
        return head->next;
    }

    ListNode *divide(std::vector<ListNode *> &lists, int left, int right)
    {
        if (left > right)
            return nullptr;
        else if (left == right)
            return lists[left];
        int mid = (left + right) / 2;
        auto l = divide(lists, left, mid);
        auto r = divide(lists, mid + 1, right);
        return merge(l, r);
    }


    ListNode *mergeKLists(std::vector<ListNode *> &lists)
    {
        return divide(lists, 0, lists.size() - 1);
    }
};

namespace bm6 {
class Solution
{
public:
    bool hasCycle(ListNode *head)
    {
        ListNode *fast, *slow;
        fast = slow = head;
        while (fast && slow)
        {
            slow = slow->next;
            if (fast->next)
                fast = fast->next->next;
            else
                return false;
            if (slow == fast)
                return true;
        }
        return false;
    }
};
}

namespace bm7 {
class Solution
{
public:
    ListNode *EntryNodeOfLoop(ListNode *pHead)
    {
        ListNode *fast, *slow;
        fast = slow = pHead;
        while (fast && fast->next)
        {
            fast = fast->next->next;
            slow = slow->next;
            if (slow == fast)
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

namespace bm8 {
class Solution
{
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     *
     * @param pHead ListNode类
     * @param k int整型
     * @return ListNode类
     */
    ListNode *FindKthToTail(ListNode *pHead, int k)
    {
        int len = 0;
        ListNode *p = pHead;
        while (p)
        {
            p = p->next;
            ++len;
        }
        int m = len - k;
        if (m < 0)
            return nullptr;
        p = pHead;
        for (int i = 0; i < m; ++i)
            p = p->next;
        return p;
    }
};
}

namespace bm9 {
class Solution
{
public:
    /**
     *
     * @param head ListNode类
     * @param n int整型
     * @return ListNode类
     */
    ListNode *FindKthToTail(ListNode *pHead, int k)
    {
        int len = 0;
        ListNode *p = pHead;
        while (p)
        {
            p = p->next;
            ++len;
        }
        int m = len - k;
        if (m < 0)
            return nullptr;
        p = pHead;
        for (int i = 0; i < m; ++i)
            p = p->next;
        return p;
    }




    ListNode *removeNthFromEnd(ListNode *head, int n)
    {
        ListNode *node = FindKthToTail(head, n + 1);
        if (node == nullptr)
        {
            auto tmp = head->next;
            head->next = nullptr;
            delete head;
            return tmp;
        }
        else if (node->next == nullptr)
        {
            return head;
        }
        else
        {
            auto tmp = node->next;
            node->next = node->next->next;
            tmp->next = nullptr;
            delete tmp;
        }

        return head;
    }
};
}

namespace bm10 {
class Solution
{
public:
    ListNode *FindFirstCommonNode(ListNode *pHead1, ListNode *pHead2)
    {
        ListNode *p1, *p2;
        p1 = pHead1, p2 = pHead2;
        while (p1 != p2)
        {
            p1 = p1 == nullptr ? pHead2 : p1->next;
            p2 = p2 == nullptr ? pHead1: p2->next;
        }
        return p1;
    }
};
}

namespace bm11 {
class Solution
{
public:
    /**
     *
     * @param head1 ListNode类
     * @param head2 ListNode类
     * @return ListNode类
     */
    ListNode *reverse(ListNode *head)
    {
        ListNode *cur, *pre, *next_;
        pre = nullptr, cur = head;
        while (cur)
        {
            next_ = cur->next;
            cur->next = pre;

            pre = cur;
            cur = next_;
        }
        return pre;
    }



    ListNode *addInList(ListNode *head1, ListNode *head2)
    {
        ListNode *rh1 = reverse(head1);
        ListNode *rh2 = reverse(head2);
        ListNode *head = new ListNode(0);
        ListNode *p = head;
        int carry = 0;
        while (rh1 || rh2)
        {
            int s = carry;
            if (rh1)
            {
                s += rh1->val;
                rh1 = rh1->next;
            }
            if (rh2)
            {
                s += rh2->val;
                rh2 = rh2->next;
            }

            p->next = new ListNode(s % 10);
            carry = s / 10;

            p = p->next;
        }
        if (carry)
            p->next = new ListNode(carry);
        return reverse(head->next);
    }
};

}

namespace bm12 {
class Solution
{
public:
    /**
     *
     * @param head ListNode类 the head node
     * @return ListNode类
     */
    ListNode *sortInList(ListNode *head)
    {
        std::vector<ListNode *> list;
        auto p = head;
        while (p)
        {
            list.push_back(p);
            p = p->next;
        }

        auto cmp = [](ListNode *a, ListNode *b)
        {
            return a->val < b->val;
        };

        std::sort(list.begin(), list.end(), cmp);
        int i;
        for (i = 0; i < (int)list.size() - 1; ++i)
        {
            list[i]->next = list[i+1];
        }
        list[i]->next = nullptr;
        return list[0];
    }
};
}

namespace bm13 {
class Solution
{
public:
    /**
     *
     * @param head ListNode类 the head
     * @return bool布尔型
     */
    bool isPail(ListNode *head)
    {
        auto p = head;
        std::vector<ListNode *> list;
        while (p)
        {
            list.push_back(p);
            p = p->next;
        }
        for (int i = 0, j = list.size() - 1; i < j; ++i, --j)
        {
            if (list[i]->val != list[j]->val)
                return false;
        }
        return true;
    }
};
}

namespace bm14 {
class Solution
{
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     *
     * @param head ListNode类
     * @return ListNode类
     */
    ListNode *oddEvenList(ListNode *head)
    {
        auto p = head;
        std::vector<ListNode *> list, odd, even;
        list.push_back(new ListNode(-1));
        while (p)
        {
            list.push_back(p);
            p = p->next;
        }

        if (list.size() == 1 || list.size() == 2)
            return head;


        for (int i = 1; i < list.size(); ++i)
        {
            if (i & 1)
                odd.push_back(list[i]);
            else
                even.push_back(list[i]);
        }
        int j, k;
        for (j = 0; j < odd.size() - 1; ++j)
        {
            odd[j]->next = odd[j+1];
        }
        for (k = 0; k < (int)even.size() - 1; ++k)
        {
            even[k]->next = even[k+1];
        }
        even[k]->next = nullptr;
        odd[j]->next = even[0];

        return odd[0];
    }
};

namespace bm15 {
class Solution
{
public:
    /**
     *
     * @param head ListNode类
     * @return ListNode类
     */
    ListNode *deleteDuplicates(ListNode *head)
    {
        ListNode *p, *q;
        p = q = head;
        while (p && p->next)
        {
            q = p->next;
            if (q->val == p->val)
            {
                p->next = q->next;
                q->next = nullptr;
                delete q;
            }
            else
            {
                p = q;
            }
        }
        return head;
    }
};
}

namespace bm16 {
class Solution
{
public:
    /**
     *
     * @param head ListNode类
     * @return ListNode类
     */
    ListNode *deleteDuplicates(ListNode *head)
    {
        ListNode *pre, *newhead, *cur;
        pre = newhead = new ListNode(0);
        cur = head;
        int count = 0;
        while (cur && cur->next)
        {
            if (cur->val == cur->next->val)
            {
                cur->next = cur->next->next;
                ++count;
            }
            else
            {
                if (count > 0)
                {
                    pre->next = cur->next;
                    count = 0;
                }
                else
                {
                    pre = cur;
                }
                cur = cur->next;
            }
        }
        if (count)
            pre->next = cur->next;
        return newhead->next;
    }
};




















}






















































}
























































}







