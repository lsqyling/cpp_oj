//
// Created by shiqing on 2021/4/3.
//
#include <algorithm>
#include "../common/CommonHeaders.h"


namespace codeup_1918 {

int FactorValue()
{
    int ans = 0;
    char c = cin.peek();
    while (std::isdigit(c))
    {
        ans = ans * 10 + c - '0';
        cin.get();
        c = cin.peek();
    }
    return ans;
}

double TermValue()
{
    double result = FactorValue();
    for (;;)
    {
        char op = cin.peek();
        if (op == '*' || op == '/')
        {
            cin.get();
            double value = FactorValue();
            if (op == '*')
            {
                result *= value;
            }
            else
            {
                result /= value;
            }
        }
        else
        {
            break;
        }
    }
    return result;
}

double ExpressionValue()
{
    double result = TermValue();
    for (;;)
    {
        char op = cin.peek();
        if (op == '+' || op == '-')
        {
            cin.get();
            double value = TermValue();
            if (op == '+')
            {
                result += value;
            }
            else
            {
                result -= value;
            }
        }
        else
        {
            break;
        }
    }
    return result;
}

void Entry()
{
    double val = ExpressionValue();
    printf("%.2f", val);
}
}

namespace codeup_1918_b {
constexpr int kSize = 256;
struct Node
{
    double num_;
    char op_;
    bool is_num_;
};

Node s[kSize], q[kSize];
int top = -1, front = -1, rear = -1;

int priority_table[kSize];

void TransformSuffixExpr(string str)
{
    Node tmp;
    for (int i = 0; i < str.size();)
    {
        if (std::isdigit(str[i]))
        {
            tmp.is_num_ = true;
            tmp.num_ = str[i++] - '0';
            while (i < str.size() && std::isdigit(str[i]))
            {
                tmp.num_ = tmp.num_ * 10 + (str[i] - '0');
                ++i;
            }
            q[++rear] = tmp;
        }
        else
        {
            tmp.is_num_ = false;
            while (top != -1 && priority_table[str[i]] <= priority_table[s[top].op_])
            {
                q[++rear] = s[top];
                --top;
            }
            tmp.op_ = str[i];
            s[++top] = tmp;
            ++i;
        }
    }
    while (top != -1)
    {
        q[++rear] = s[top];
        --top;
    }
}

double CalcInfixExpr()
{
    Node tmp;
    while (front != rear)
    {
        auto curr = q[front + 1];
        ++front;
        if (curr.is_num_)
        {
            s[++top] = curr;
        }
        else
        {
            auto left_n = s[top].num_;
            --top;
            auto right_n = s[top].num_;
            --top;
            tmp.is_num_ = true;
            switch (curr.op_)
            {
                case '+':
                    tmp.num_ = left_n + right_n;
                    break;
                case '-':
                    tmp.num_ = left_n - right_n;
                    break;
                case '*':
                    tmp.num_ = left_n * right_n;
                    break;
                case '/':
                    tmp.num_ = left_n / right_n;
                    break;
                default:
                    exit(-1);
            }
            s[++top] = tmp;
        }
    }
    return s[top].num_;
}

void Entry()
{
    priority_table['+'] = priority_table['-'] = 1;
    priority_table['*'] = priority_table['/'] = 2;
    string inputs, str;
    getline(cin, inputs);
    for (int i = 0; i < inputs.size(); ++i)
    {
        if (inputs[i] != ' ')
        {
            str += inputs[i];
        }
    }
    TransformSuffixExpr(str);
    printf("%.2f", CalcInfixExpr());
}
}

namespace circle_queen {
constexpr int kMaxSize = 1007;

struct Queen
{
    int data_[kMaxSize]{};
    int front_ = 0, rear_ = 0;
};

bool Empty(const Queen &q)
{
    return q.front_ == q.rear_;
}

bool Full(const Queen &q)
{
    return (q.rear_ + 1) % kMaxSize == q.front_;
}

void Enqueen(Queen &q, int x)
{
    q.rear_ = (q.rear_ + 1) % kMaxSize;
    q.data_[q.rear_] = x;
}

int Dequeen(Queen &q)
{
    q.front_ = (q.front_ + 1) % kMaxSize;
    return q.data_[q.front_];
}

int get_front(const Queen &q)
{
    return q.data_[(q.front_ + 1) % kMaxSize];
}

int get_rear(const Queen &q)
{
    return q.data_[q.rear_];
}

int size(const Queen &q)
{
    return (q.rear_ - q.front_ + kMaxSize) % kMaxSize;
}
}

namespace pat_a1032 {
constexpr int kN = 100'005;

struct Node
{
    char data_;
    int next_;
};

Node words[kN];

int FindCommonNode(int h1, int h2)
{
    int h = h1, len1 = 0, len2 = 0;
    while (h != -1)
    {
        h = words[h].next_;
        ++len1;
    }
    h = h2;
    while (h != -1)
    {
        h = words[h].next_;
        ++len2;
    }
    int len = len1 - len2;
    if (len < 0)
    {
        len = -len;
        while (len--)
        {
            h2 = words[h2].next_;
        }
    }
    else
    {
        while (len--)
        {
            h1 = words[h1].next_;
        }
    }
    while (h1 != -1 && h2 != -1)
    {
        if (h1 == h2) return h1;
        h1 = words[h1].next_;
        h2 = words[h2].next_;
    }
    return -1;
}

void Entry()
{
    int h1, h2, n;
    scanf("%d%d%d", &h1, &h2, &n);
    for (int i = 0; i < n; ++i)
    {
        int idx;
        char c;
        int next;
        scanf("%d %c %d", &idx, &c, &next);
        words[idx].data_ = c;
        words[idx].next_ = next;
    }
    int h = FindCommonNode(h1, h2);
    if (h != -1)
    {
        printf("%05d", FindCommonNode(h1, h2));
    }
    else printf("-1");
}
}

namespace pat_a1052 {
constexpr int kN = 100'005;

struct Node
{
    int address_, data_, next_;
    bool is_on_list_;
};

auto cmp = [](Node a, Node b)
{
    if (a.is_on_list_ != b.is_on_list_)
    {
        return a.is_on_list_ > b.is_on_list_;
    }
    else
    {
        return a.data_ < b.data_;
    }
};

Node list[kN];

void Entry()
{
    int n, h;
    scanf("%d%d", &n, &h);
    for (int i = 0; i < n; ++i)
    {
        int idx, data, next;
        scanf("%d%d%d", &idx, &data, &next);
        list[idx].address_ = idx;
        list[idx].data_ = data;
        list[idx].next_ = next;
    }
    int count = 0;
    while (h != -1)
    {
        list[h].is_on_list_ = true;
        h = list[h].next_;
        ++count;
    }
    std::sort(list, list + kN, cmp);
    printf("%d %05d\n", count, list[0].address_);
    for (int i = 0; i < count; ++i)
    {
        if (i < count - 1)
        {
            printf("%05d %d %05d\n", list[i].address_, list[i].data_, list[i + 1].address_);
        }
        else
        {
            printf("%05d %d -1\n", list[i].address_, list[i].data_);
        }
    }
}
}


int main(int argc, char *argv[])
{
    codeup_1918::Entry();
    codeup_1918_b::Entry();
    pat_a1032::Entry();
    pat_a1052::Entry();
    return 0;
}

