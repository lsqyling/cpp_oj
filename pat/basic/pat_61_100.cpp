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

namespace basic_74 {
constexpr int N = 25;

char base_num[N];


void add_pat_numbers(char a[], char b[], int len1, int len2, int sum[])
{
    int r = 0;
    int i, s, t, base;
    for (i = 0; i < len1 || i < len2; ++i)
    {
        s = a[i] - '0';
        t = b[i] - '0';

        s = s < 0 ? 0 : s;
        t = t < 0 ? 0 : t;


        base = base_num[i] == '0' ? 10 : (base_num[i] - '0');

        sum[i] = (r + s + t) % base;
        r = (r + s + t) / base;

    }
    if (r)
    {
        base = base_num[i] == '0' ? 10 : (base_num[i] - '0');
        sum[i++] += r % base;
    }
    int j = i - 1;
    while (j > 0 && sum[j] == 0) --j;
    for ( ; j >= 0; --j)
    {
        printf("%d", sum[j]);
    }
}



void entry()
{
    char a[N], b[N];
    memset(a, '\0', sizeof(a));
    memset(b, '\0', sizeof(b));

    scanf("%s%s%s", base_num, a, b);
    int len1 = strlen(a);
    int len2 = strlen(b);

    std::reverse(a, a + len1);
    std::reverse(b, b + len2);
    std::reverse(base_num, base_num + strlen(base_num));

    int sum[N];
    memset(sum, 0, sizeof(sum));
    add_pat_numbers(a, b, len1, len2, sum);
}
}

namespace basic_75 {
constexpr int N = 100'005;

struct node
{
    int addr, data, next;
    int id;
};

node input[N];
int K;

bool operator<(node a, node b)
{
    if (a.data < 0 && b.data < 0)
        return a.id < b.id;
    else if ((0 <= a.data && a.data <= K) && (0 <= b.data && b.data <= K))
        return a.id < b.id;
    else if (a.data > K && b.data > K)
        return a.id < b.id;
    else
    {
        return a.data < b.data;
    }
}


void entry()
{
    int h, n;
    scanf("%d%d%d", &h, &n, &K);
    int addr, data, next;
    for (int i = 0; i < n; ++i)
    {
        scanf("%d%d%d", &addr, &data, &next);
        input[addr].addr = addr;
        input[addr].data = data;
        input[addr].next = next;
    }

    std::vector<node> list;
    int id = 0;
    while (h != -1)
    {
        input[h].id = id;
        list.push_back(input[h]);
        ++id;
        h = input[h].next;
    }

    std::sort(list.begin(), list.end());


    int j;
    for (j = 0; j < list.size() - 1; ++j)
    {
        printf("%05d %d %05d\n", list[j].addr, list[j].data, list[j+1].addr);
    }
    printf("%05d %d -1\n", list[j].addr, list[j].data);
}
}

namespace basic_76 {


void entry()
{
    int n;
    scanf("%d", &n);
    getchar();
    char c, judge;
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            scanf("%c-%c", &c, &judge);
            getchar();
            if (judge == 'T')
                printf("%d", c - 'A' + 1);
        }
    }
}


















}

namespace basic_77 {

void entry()
{
    int n, M;
    scanf("%d%d", &n, &M);

    for (int i = 0; i < n; ++i)
    {
        int t, max = 0, min = M + 1, tmp, s = 0, len = 0;
        scanf("%d", &t);
        for (int j = 1; j < n; ++j)
        {
            scanf("%d", &tmp);
            if (0 <= tmp && tmp <= M)
            {
                s += tmp;
                ++len;
                if (tmp > max)
                    max = tmp;
                if (tmp < min)
                    min = tmp;
            }
        }

        double d = round((t + 1.0 * (s - min - max) / (len - 2)) / 2);
        printf("%.0f\n", d);
    }
}
}

namespace basic_78 {
constexpr int N = 1024;

char str[N];

void compress(char in[], int len)
{
    for (int i = 0, j = 0; i < len; )
    {
        while (j < len && in[j] == in[i])
            ++j;
        int n = j - i;
        if (n > 1)
        {
            printf("%d", n);
        }

        printf("%c", in[i]);
        i = j;
    }
}

void decompress(char in[], int len)
{
    for (int i = 0, j; i < len; ++i)
    {
        int n = 0;
        for (j = i; '0' <= in[j] && in[j] <= '9'; ++j)
            n = n * 10 + (in[j] - '0');

        i = j;
        if (n > 1)
        {
            while (n--)
                printf("%c", in[i]);
        }
        else
            printf("%c", in[i]);
    }
}




void entry()
{
    char c;
    scanf("%c", &c);
    getchar();
    fgets(str, sizeof(str), stdin);

    int len = strlen(str);

    if (c == 'C')
        compress(str, len);
    else if (c == 'D')
        decompress(str, len);

}
}

namespace basic_79 {
constexpr int N = 1005;

struct bign
{
    int arr[N];
    int len;

    bign() : arr{0}, len(0) {}
};

std::istream &operator>>(std::istream &is, bign &n)
{
    std::string str;
    is >> str;
    for (int i = str.size() -1; i >= 0; --i)
    {
        n.arr[n.len++] = str[i] - '0';
    }
    return is;
}

bign reverse(bign n)
{
    for (int i = 0, j = n.len - 1; i < j; ++i, --j)
    {
        std::swap(n.arr[i], n.arr[j]);
    }
    return n;
}

bign operator+(const bign &a, const bign &b)
{
    bign c;
    int i, r = 0;
    for (i = 0; i < a.len || i < b.len; ++i)
    {
        int s = r + a.arr[i] + b.arr[i];

        c.arr[c.len++] = s % 10;
        r = s / 10;
    }
    if (r)
    {
        c.arr[c.len++] = r % 10;
    }

    return c;
}

std::ostream &operator<<(std::ostream &os, const bign &a)
{
    for (int i = a.len - 1; i >= 0; --i)
    {
        os << a.arr[i];
    }
    return os;
}

bool is_palindromic(const bign &a)
{
    for (int i = 0, j = a.len - 1; i < j; ++i, --j)
    {
        if (a.arr[i] != a.arr[j])
            return false;
    }
    return true;
}


void entry()
{
    bign a, b, c;
    std::cin >> a;

    bool flag = false;

    if (is_palindromic(a))
    {
        std::cout << a << " is a palindromic number." << std::endl;
        return ;
    }

    for (int i = 0; i < 10; ++i)
    {
        b = reverse(a);
        c = a + b;
        std::cout << a << " + " << b << " = " << (a+b) << std::endl;
        if (is_palindromic(c))
        {
            std::cout << c << " is a palindromic number." << std::endl;
            flag = true;
            break;
        }
        a = c;
    }

    if (!flag)
        std::cout << "Not found in 10 iterations." << std::endl;
}
}

namespace basic_80 {
struct stu
{
    char id[25];
    int Gp, Gmid, Gf, G;

    stu() : id{'\0'}, Gp(-1), Gmid(-1), Gf(-1), G(0) {}
};

bool operator<(const stu &a, const stu &b)
{
    if (a.G != b.G)
        return a.G > b.G;
    else
        return strcmp(a.id, b.id) < 0;
}

std::map<std::string, stu> all;


void entry()
{
    int p, m, n;
    scanf("%d%d%d", &p, &m, &n);

    stu tmp;
    for (int i = 0; i < p; ++i)
    {
        scanf("%s%d", tmp.id, &tmp.Gp);
        all[tmp.id] = tmp;
    }
    for (int j = 0; j < m; ++j)
    {
        scanf("%s%d", tmp.id, &tmp.Gmid);
        strcpy(all[tmp.id].id, tmp.id);
        all[tmp.id].Gmid = tmp.Gmid;
    }
    for (int k = 0; k < n; ++k)
    {
        scanf("%s%d", tmp.id, &tmp.Gf);
        strcpy(all[tmp.id].id, tmp.id);
        all[tmp.id].Gf = tmp.Gf;
    }

    std::vector<stu> list;
    for (const auto &item : all)
    {
        auto s = item.second;
        if (s.Gp < 200)
            continue;
        if (s.Gmid > s.Gf)
            s.G = round(0.4 * s.Gmid + 0.6 * s.Gf);
        else
            s.G = s.Gf;
        if (s.G < 60)
            continue;
        list.push_back(std::move(s));
    }

    std::sort(list.begin(), list.end());

    for (int i = 0; i < list.size(); ++i)
    {
        printf("%s %d %d %d %d\n", list[i].id, list[i].Gp, list[i].Gmid, list[i].Gf, list[i].G);

    }

}
}

namespace basic_81 {

using std::string;

void entry()
{
    int n;
    string line;
    std::cin >> n;
    getchar();
    for (int i = 0; i < n; ++i)
    {
        std::getline(std::cin, line);
        if (line.size() < 6)
            std::cout << "Your password is tai duan le." << std::endl;
        else
        {

            bool has_alpha = false;
            bool has_digit = false;
            bool exist_illegal = false;

            for (int j = 0; j < line.size(); ++j)
            {
                if (('A' <= line[j] && line[j] <= 'Z')
                    || ('a' <= line[j] && line[j] <= 'z'))
                {
                    has_alpha = true;
                }
                else if ('0' <= line[j] && line[j] <= '9')
                {
                    has_digit = true;
                }
                else if (line[j] != '.')
                {
                    exist_illegal = true;
                }
            }
            if (exist_illegal)
            {
                std::cout << "Your password is tai luan le." << std::endl;
            }
            else if (has_digit && has_alpha)
            {
                std::cout << "Your password is wan mei." << std::endl;
            }
            else if (!has_digit && has_alpha)
            {
                std::cout << "Your password needs shu zi." << std::endl;
            }
            else
            {
                std::cout << "Your password needs zi mu." << std::endl;
            }
        }
    }
}
}

namespace basic_82 {


void entry()
{
    int n;
    scanf("%d", &n);
    int id, x, y, max_id, min_id;
    double max = 0, min = 0x3fff'ffff;
    double dist;
    for (int i = 0; i < n; ++i)
    {
        scanf("%d%d%d", &id, &x, &y);
        dist = 1.0 * x * x + 1.0 * y * y;
        if (dist > max)
        {
            max = dist;
            max_id = id;
        }
        if (dist < min)
        {
            min = dist;
            min_id = id;
        }
    }

    printf("%04d %04d\n", min_id, max_id);
}
}

namespace basic_83 {
constexpr int N = 10'005;

int table[N];

void entry()
{
    int n;
    scanf("%d", &n);
    memset(table, -1, sizeof(table));
    for (int i = 1; i <= n; ++i)
    {
        int up = i, down;
        scanf("%d", &down);
        int c = up >= down ? up - down : down - up;
        table[c]++;
    }
    for (int j = n; j >= 0; --j)
    {
        if (table[j] > 0)
        {
            printf("%d %d\n", j, table[j] + 1);
        }
    }

}
}

namespace basic_84 {
constexpr int N = 45;

std::vector<int> seq[N];

void entry()
{
    int d, n;
    scanf("%d%d", &d, &n);
    seq[1].push_back(d);
    for (int k = 2; k <= n; ++k)
    {
        for (int i = 0, j = 0; j < seq[k - 1].size();)
        {
            while (j < seq[k - 1].size() && seq[k - 1][j] == seq[k - 1][i])
                ++j;

            int t = j - i;
            int x = seq[k - 1][i];
            seq[k].push_back(x);
            seq[k].push_back(t);

            i = j;
        }
    }

    for (int i = 0; i < seq[n].size(); ++i)
    {
        printf("%d", seq[n][i]);
    }

}
}

namespace basic_85 {
struct sch
{
    char name[8];
    int num;
    int score;
    double total_score;
    int total_score_;
    sch() : name{'\0'}, num(1), score(0), total_score(0), total_score_(0) {}
};

bool operator<(const sch &a, const sch &b)
{
    if (a.total_score_ != b.total_score_)
        return a.total_score_ > b.total_score_;
    else if (a.num != b.num)
        return a.num < b.num;
    else
        return strcmp(a.name, b.name) < 0;
}



std::map<std::string, sch> table;

void to_lower_str(char str[])
{
    int len = strlen(str);
    for (int i = 0; i < len; ++i)
    {
        str[i] = tolower(str[i]);
    }
}

void entry()
{
    int n;
    scanf("%d", &n);
    char id[10];
    for (int i = 0; i < n; ++i)
    {
        sch tmp;
        scanf("%s%d%s", id, &tmp.score, tmp.name);
        to_lower_str(tmp.name);
        switch (id[0])
        {
            case 'A':
                tmp.total_score += tmp.score;
                break;
            case 'B':
                tmp.total_score += 1.0 * tmp.score / 1.5;
                break;
            case 'T':
                tmp.total_score += 1.0 * tmp.score * 1.5;
                break;
            default:
                exit(1);
        }
        auto it = table.find(tmp.name);
        if (it != table.end())
        {
            ++table[tmp.name].num;
            table[tmp.name].total_score += tmp.total_score;
        }
        else
        {
            table[tmp.name] = tmp;
        }
    }

    std::vector<sch> list;
    for (auto &item : table)
    {
        auto &s = item.second;
        s.total_score_ = floor(s.total_score);
        list.push_back(s);
    }

    std::sort(list.begin(), list.end());


    printf("%zu\n", list.size());
    int r = 1;
    for (int j = 0; j < list.size(); ++j)
    {
        if (j > 0 && list[j].total_score_ != list[j-1].total_score_)
            r = j + 1;
        printf("%d %s %d %d\n", r, list[j].name, list[j].total_score_, list[j].num);
    }
}
}

namespace basic_86 {
constexpr int N = 35;

int digit[N], len;

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
    int a, b;
    scanf("%d%d", &a, &b);
    int c = a * b;
    convert(c, 10);
    int i = 0;
    while (i < len - 1 && digit[i] == 0)
        ++i;
    for (; i < len; ++i)
    {
        printf("%d", digit[i]);
    }
}
}

namespace basic_87 {

void entry()
{
    int N, m, m0 = -1, count = 0;
    scanf("%d", &N);
    for (int n = 1; n <= N; ++n)
    {
        m = n/2 + n/3 + n/5;
        if (m > m0)
            count++;
        m0 = m;
    }
    printf("%d\n", count);
}
}

namespace basic_88 {

inline int convert(int a)
{
    int ones = a % 10;
    int tens = a / 10;

    return ones * 10 + tens;
}


void entry()
{
    int M, X, Y;
    scanf("%d%d%d", &M, &X, &Y);
    int a, b; double c;
    for (a = 99; a >= 10; --a)
    {
        b = convert(a);

        if (abs(a - b) * Y == b * X)
        {
            c = 1.0 * b / Y;
            break;
        }
    }
    if (a == 9)
        printf("No Solution");
    else
    {
        printf("%d", a);
        printf(" %s", a >= M ? (a == M ? "Ping" : "Cong") : "Gai");
        printf(" %s", b >= M ? (b == M ? "Ping" : "Cong") : "Gai");
        printf(" %s", c >= M ? (c == M ? "Ping" : "Cong") : "Gai");
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
//    basic_73::entry();
//    basic_74::entry();
//    basic_75::entry();
//    basic_76::entry();
//    basic_77::entry();
//    basic_78::entry();
//    basic_79::entry();
//    basic_80::entry();
//    basic_81::entry();
//    basic_82::entry();
//    basic_83::entry();
//    basic_84::entry();
//    basic_85::entry();
//    basic_86::entry();
//    basic_87::entry();
    basic_88::entry();
    return 0;
}