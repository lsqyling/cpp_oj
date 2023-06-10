#include <cstdio>
#include <algorithm>
#include <vector>
#include <cmath>
#include <cstring>
#include <iostream>
#include <string>
#include <map>


namespace basic_61 {

int score[105];
int right_ans[105];


void entry()
{
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; ++i)
    {
        scanf("%d", &score[i]);
    }
    for (int j = 0; j < m; ++j)
    {
        scanf("%d", &right_ans[j]);
    }
    for (int k = 0; k < n; ++k)
    {
        int sum = 0;
        int tmp;
        for (int i = 0; i < m; ++i)
        {
            scanf("%d", &tmp);
            if (right_ans[i] == tmp)
                sum += score[i];
        }
        printf("%d\n", sum);
    }
}
}

namespace basic_62 {
struct fraction
{
    int up, down;
};

int gcd(int a, int b)
{
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

int lcm(int a, int b)
{
    int g = gcd(a, b);
    return a * b / g;
}

void simply(fraction &f)
{
    int g = gcd(f.up, f.down);
    f.up /= g;
    f.down /= g;
}

bool operator<(fraction a, fraction b)
{
    int d = lcm(a.down, b.down);
    int t = d / a.down;
    a.down *= t;
    a.up *= t;

    t = d / b.down;
    b.down *= t;
    b.up *= t;
    return a.up < b.up;
}


void same_down(fraction &a, fraction &b, fraction &c)
{
    int d = lcm(a.down, b.down);
    d = lcm(d, c.down);

    int t = d / a.down;
    a.down *= t;
    a.up *= t;

    t = d / b.down;
    b.down *= t;
    b.up *= t;

    t = d / c.down;
    c.down *= t;
    c.up *= t;
}

void entry()
{
    fraction a, b, c;
    scanf("%d/%d %d/%d %d", &a.up, &a.down, &b.up, &b.down, &c.down);
    c.up = 1;

    int old = c.down;
    same_down(a, b, c);
    if (b < a)
        std::swap(a, b);

    std::vector<fraction> ans;
    for (int i = a.up + 1; i < b.up; ++i)
    {
        int t = c.down / old;
        if (i % t == 0)
        {
            c.up = i;
            auto tmp = c;
            simply(tmp);
            if (tmp.down == old)
            {
                ans.push_back(tmp);
            }

        }
    }

    for (int j = 0; j < ans.size(); ++j)
    {
        printf("%d/%d", ans[j].up, ans[j].down);
        if (j < ans.size() - 1)
            printf(" ");
    }
}
}

namespace basic_63 {
void entry()
{
    int n;
    scanf("%d", &n);
    int a, b, c;
    int max = 0;
    for (int i = 0; i < n; ++i)
    {
        scanf("%d%d", &a, &b);
        c = a * a + b * b;
        if (c > max)
            max = c;
    }

    printf("%.2f\n", sqrt(1.0 * max));
}
}

namespace basic_64 {

int digit[10], len = 0;
bool table[40];


void convert(int n, int radix)
{
    len = 0;
    do
    {
        digit[len++] = n % radix;
        n /= radix;
    } while (n);
}

void entry()
{
    int n, x;
    scanf("%d", &n);
    int count = 0;
    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &x);
        convert(x, 10);
        int sum = 0;
        for (int j = 0; j < len; ++j)
        {
            sum += digit[j];
        }
        if (!table[sum])
        {
            ++count;
            table[sum] = true;
        }
    }
    printf("%d\n", count);
    for (int k = 0; k < 40; ++k)
    {
        if (table[k])
        {
            printf("%d", k);
            if (--count > 0)
                printf(" ");
        }
    }
}
}

namespace basic_65 {
constexpr int N = 100'005;
constexpr int M = 10'005;

int couple[N], guest[M];
bool table[N];

void entry()
{
    int n;
    int c, p;
    scanf("%d", &n);
    memset(couple, -1, sizeof(couple));
    for (int i = 0; i < n; ++i)
    {
        scanf("%d%d", &c, &p);
        couple[c] = p;
        couple[p] = c;
    }

    int m;
    scanf("%d", &m);
    std::vector<int> ans;
    for (int j = 0; j < m; ++j)
    {
        scanf("%d", &c);
        guest[j] = c;
        table[c] = true;
    }

    for (int j = 0; j < m; ++j)
    {
        c = guest[j];
        p = couple[c];
        if (p == -1 || !table[p])
            ans.push_back(c);
    }

    std::sort(ans.begin(), ans.end());
    printf("%zu\n", ans.size());
    for (int k = 0; k < ans.size(); ++k)
    {
        printf("%05d", ans[k]);
        if (k < ans.size() - 1)
            printf(" ");
    }
}
}

namespace basic_66 {

void entry()
{
    int m, n, A, B, v, x;
    scanf("%d%d%d%d%d", &m, &n, &A, &B, &v);
    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            scanf("%d", &x);
            if (A <= x && x <= B)
                x = v;
            printf("%03d", x);
            if (j < n - 1)
                printf(" ");
        }
        printf("\n");
    }
}
}

namespace basic_67 {
void entry()
{
    std::string password;
    int n;
    std::cin >> password >> n;
    getchar();
    std::string tmp;
    for (int j = 0; j < n; ++j)
    {

        std::getline(std::cin, tmp);
        if (tmp == "#")
            return ;
        if (tmp == password)
        {
            std::cout << "Welcome in";
            return ;
        }
        else
            std::cout << "Wrong password: " << tmp << std::endl;
    }
    std::cout << "Account locked";
}
}

namespace basic_68 {
constexpr int N = 1005;
const int Direct[8][2] = {{-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}};

int graph[N][N];
int TOL;

bool judge(int n, int m, int x1, int y1)
{
    for (int k = 0; k < 8; ++k)
    {
        int x2 = x1 + Direct[k][0];
        int y2 = y1 + Direct[k][1];
        if (0 <= x2 && x2 <= n
            && 0 <= y2 && y2 <= m
            && abs(graph[x1][y1] - graph[x2][y2]) <= TOL)
            return false;
    }
    return true;
}

void entry()
{
    int m, n;
    scanf("%d%d%d", &m, &n, &TOL);
    std::map<int, int> maps;
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            scanf("%d", &graph[i][j]);
            ++maps[graph[i][j]];
        }
    }
    int count = 0;
    int x, y;
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            if (maps[graph[i][j]] == 1 && judge(n, m, i, j))
            {
                ++count;
                x = i + 1;
                y = j + 1;
            }
        }
    }

    if (count == 0)
        printf("Not Exist");
    else if (count == 1)
        printf("(%d, %d): %d", y, x, graph[x-1][y-1]);
    else
        printf("Not Unique");
}
}

namespace basic_69 {
constexpr int M = 1005;

std::string nickname[M];


void entry()
{
    int m, n, s;
    std::cin >> m >> n >> s;
    for (int i = 1; i <= m; ++i)
        std::cin >> nickname[i];

    if (s > m)
    {
        std::cout << "Keep going...\n";
        return ;
    }
    std::map<std::string, bool> mps;
    for (int i = s; i <= m; i += n)
    {
        while (i <= m && mps[nickname[i]])
            ++i;
        if (i > m)
            break;
        std::cout << nickname[i] << std::endl;
        mps[nickname[i]] = true;
    }
}
}

namespace basic_70 {
constexpr int N = 10'005;

int num[N];

void entry()
{
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &num[i]);
    }

    std::sort(num, num + n);
    double s = num[0];

    for (int j = 1; j < n; ++j)
    {
        s += num[j];
        s /= 2;
    }
    printf("%.0f", floor(s));
}
}

namespace basic_71 {

void entry()
{
    int T, K;
    scanf("%d%d", &T, &K);
    int n1, b, t, n2;
    for (int i = 0; i < K; ++i)
    {
        scanf("%d%d%d%d", &n1, &b, &t, &n2);
        if (T <= 0)
        {
            printf("Game Over.");
            return;
        }
        else if (t > T)
        {
            printf("Not enough tokens.  Total = %d.\n", T);
        }
        else
        {
            bool flag;
            if (b == 0)
                flag = n2 < n1;
            if (b == 1)
                flag = n2 > n1;

            if (flag)
            {
                T += t;
                printf("Win %d!  Total = %d.\n", t, T);
            }
            else
            {
                T -= t;
                printf("Lose %d.  Total = %d.\n", t, T);
            }
        }
    }
}
}

namespace basic_72 {
constexpr int N = 1'0005;

struct stu
{
    char name[5];
    std::vector<int> goods;
};
bool table[N];


void entry()
{
    int n, m, id;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; ++i)
    {
        scanf("%d", &id);
        table[id] = true;
    }

    int count = 0;
    std::vector<stu> pss;
    for (int j = 0; j < n; ++j)
    {
        int k;
        stu st;
        scanf("%s%d", st.name, &k);
        for (int i = 0; i < k; ++i)
        {
            scanf("%d", &id);
            if (table[id])
            {
                st.goods.push_back(id);
            }
        }
        if (!st.goods.empty())
            pss.push_back(st);
    }
    for (int i = 0; i < pss.size(); ++i)
    {
        printf("%s: ", pss[i].name);
        count += pss[i].goods.size();
        for (int j = 0; j < pss[i].goods.size(); ++j)
        {
            printf("%04d", pss[i].goods[j]);
            if (j < pss[i].goods.size() - 1)
                printf(" ");
        }
        printf("\n");
    }
    printf("%d %d", pss.size(), count);
}
}

namespace basic_73 {
constexpr int M = 105;
constexpr int OPT_SZ = 5;


struct answer
{
    int score;
    int total_ops;
    int correct_ops;
    bool options[OPT_SZ];
};

struct choice_question
{
    int num;
    bool options[OPT_SZ];
};

answer all_answer[M];

int error_op[M][OPT_SZ];
int max_opt_error_times = 0;


double calc_score(choice_question &choice, int i)
{
    double s = 0;
    answer &ans = all_answer[i];
    bool flag = true;
    for (int j = 0; j < OPT_SZ; ++j)
    {
        if (choice.options[j])
        {
            if (!ans.options[j])
            {
                flag = false;
                ++error_op[i][j];

                if (error_op[i][j] > max_opt_error_times)
                    max_opt_error_times = error_op[i][j];
            }
        }
        if (ans.options[j])
        {
            if (!choice.options[j])
            {
                ++error_op[i][j];
                if (error_op[i][j] > max_opt_error_times)
                    max_opt_error_times = error_op[i][j];
            }
        }
    }
    if (flag && choice.num == ans.correct_ops)
        s += ans.score;
    else if (flag)
        s += 1.0 * ans.score / 2;
    return s;
}

void entry()
{
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; ++i)
    {
        scanf("%d%d%d", &all_answer[i].score, &all_answer[i].total_ops, &all_answer[i].correct_ops);
        for (int j = 0; j < all_answer[i].correct_ops; ++j)
        {
            char c;
            scanf(" %c", &c);
            all_answer[i].options[c-'a'] = true;
        }
    }


    for (int k = 0; k < n; ++k)
    {
        double s = 0;
        for (int i = 1; i <= m; ++i)
        {
            choice_question choice;
            memset(&choice, 0, sizeof(choice));
            getchar();
            scanf("(%d", &choice.num);
            char c;
            int j;
            for (j = 0; j < choice.num - 1; ++j)
            {
                scanf(" %c", &c);
                choice.options[c-'a'] = true;
            }
            scanf(" %c)", &c);
            choice.options[c-'a'] = true;

            s += calc_score(choice, i);
        }
        printf("%.1f\n", s);
    }
    if (max_opt_error_times == 0)
        printf("Too simple");
    else
    {
        for (int i = 1; i <= m; ++i)
        {
            for (int k = 0; k < OPT_SZ; ++k)
            {
                if (error_op[i][k] == max_opt_error_times)
                    printf("%d %d-%c\n", max_opt_error_times, i, k + 'a');
            }
        }
    }
}
}















int main(int argc, char **argv)
{
//    basic_61::entry();
//    basic_62::entry();
//    basic_63::entry();
//    basic_64::entry();
//    basic_65::entry();
//    basic_66::entry();
//    basic_67::entry();
//    basic_68::entry();
//    basic_69::entry();
//    basic_70::entry();
//    basic_71::entry();
//    basic_72::entry();
    basic_73::entry();
    return 0;

}