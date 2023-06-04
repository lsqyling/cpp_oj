#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#include <iostream>

namespace basic_31 {
const int WEIGHTS[17] = {7, 9, 10, 5, 8, 4, 2, 1, 6, 3, 7, 9, 10, 5, 8, 4, 2};
const char M_MAP[11] = {'1', '0', 'X', '9', '8', '7', '6', '5', '4', '3', '2'};


bool is_valid(char *id, int len)
{
    if (len != 18)
        return false;
    int s = 0;
    for (int i = 0; i < 17; ++i)
    {
        if (!isdigit(id[i]))
            return false;
        s += (id[i] - '0') * WEIGHTS[i];
    }
    char m = M_MAP[s % 11];
    return m == id[len-1];
}

void entry()
{
    char id[20];
    int n;
    scanf("%d", &n);
    int cnt = 0;
    char ans[105][20];
    for (int i = 0; i < n; ++i)
    {
        scanf("%s", id);
        int len = strlen(id);
        if (!is_valid(id, len))
        {
            sprintf(ans[cnt++], "%s", id);
        }
    }
    if (cnt > 0)
    {
        for (int i = 0; i < cnt; ++i)
        {
            printf("%s\n", ans[i]);
        }
    }
    else
        printf("All passed");
}
}

namespace basic_32 {
constexpr int N = 100005;

struct stu
{
    int id;
    int score;
};

stu all[N];

bool operator<(const stu &a, const stu &b)
{
    return a.score > b.score;
}

void entry()
{
    int n;
    scanf("%d", &n);
    stu tmp;
    int max_id = 1;
    for (int i = 0; i < n; ++i)
    {
        scanf("%d%d", &tmp.id, &tmp.score);
        if (tmp.id > max_id)
            max_id = tmp.id;
        all[tmp.id].id = tmp.id;
        all[tmp.id].score += tmp.score;
    }
    std::sort(all + 1, all + max_id + 1);
    printf("%d %d", all[1].id, all[1].score);
}
}

namespace basic_33 {
constexpr int N = 100005;

char str[N];
bool table[256];

void entry()
{

    fgets(str, sizeof(str), stdin);
    int len = strlen(str);
    memset(table, 1, sizeof(table));

    for (int i = 0; i < len; ++i)
    {
        if ('A' <= str[i] && str[i] <= 'Z')
            str[i] = str[i] - 'A' + 'a';
        table[str[i]] = false;
    }
    fgets(str, sizeof(str), stdin);
    len = strlen(str);
    for (int i = 0; i < len; ++i)
    {
        if ('A' <= str[i] && str[i] <= 'Z')
        {
            int low = str[i] - 'A' + 'a';
            if (table[low] && table['+'])
                printf("%c", str[i]);
        }
        else if (table[str[i]])
            printf("%c", str[i]);
    }
    printf("\n");
}
}

namespace basic_34 {
struct fraction
{
    long up;
    long down;
};

long gcd(long a, long b)
{
    if (b == 0)
        return a;
    return gcd(b, a % b);
}


void simplify(fraction &a)
{
    bool is_negative = false;
    if (a.down < 0)
    {
        a.down = -a.down;
        a.up = -a.up;
    }
    if (a.up < 0)
    {
        is_negative = true;
        a.up = -a.up;
    }
    if (a.up == 0)
    {
        a.down = 1;
        return ;
    }
    long g = gcd(a.up, a.down);
    a.up /= g;
    a.down /= g;
    if (is_negative)
        a.up = -a.up;
}



fraction operator+(fraction a, fraction b)
{
    fraction ans;
    ans.up = a.up * b.down + a.down * b.up;
    ans.down = a.down * b.down;
    simplify(ans);
    return ans;
}

fraction operator-(fraction a, fraction b)
{
    fraction ans;
    ans.up = a.up * b.down - a.down * b.up;
    ans.down = a.down * b.down;
    simplify(ans);
    return ans;
}

fraction operator*(fraction a, fraction b)
{
    fraction ans;
    ans.up = a.up * b.up;
    ans.down = a.down * b.down;
    simplify(ans);
    return ans;
}

fraction operator/(fraction a, fraction b)
{
    fraction ans;
    ans.up = a.up * b.down;
    ans.down = a.down * b.up;
    simplify(ans);
    return ans;
}

std::ostream &operator<<(std::ostream &os, fraction a)
{
    simplify(a);
    bool is_negative = false;
    if (a.up < 0)
    {
        is_negative = true;
        a.up = -a.up;
    }
    long p = a.up / a.down;
    long r = a.up % a.down;
    if (r == 0)
    {
        if (is_negative)
            os << "(-" << p << ")";
        else
            os << p;
    }
    else
    {
        if (p == 0)
        {
            if (is_negative)
                os << "(" << (r * -1) << "/" << a.down << ")";
            else
                os << r << "/" << a.down;
        }
        else
        {
            if (is_negative)
                os << "(-" << p << " " << r << "/" << a.down << ")";
            else
                os << p << " " << r << "/" << a.down;
        }
    }
    return os;
}



void entry()
{
    fraction a, b;
    scanf("%ld/%ld %ld/%ld", &a.up, &a.down, &b.up, &b.down);

    std::cout << a << " + " << b << " = " << (a + b) << std::endl;
    std::cout << a << " - " << b << " = " << (a - b) << std::endl;
    std::cout << a << " * " << b << " = " << (a * b) << std::endl;
    if (b.up == 0)
        std::cout << a << " / " << b << " = " << "Inf" << std::endl;
    else
        std::cout << a << " / " << b << " = " << (a / b) << std::endl;
}
}

namespace basic_35 {

std::ostream &operator<<(std::ostream &os, std::vector<int> &seq)
{
    for (int i = 0; i < seq.size(); ++i)
    {
        os << seq[i];
        if (i < seq.size() - 1)
            os << " ";
    }
    return os;
}

bool is_insertion_sort(std::vector<int> raw, const std::vector<int> &target)
{
    bool flag = false;
    for (int i = 1; i < raw.size(); ++i)
    {
//        exclude initial sequence
        if (i != 1)
            flag = raw == target;
        int k = raw[i], j;
        for (j = i - 1; j >= 0 && raw[j] > k; --j)
        {
            raw[j+1] = raw[j];
        }
        raw[j+1] = k;

        if (flag)
        {
            std::cout << "Insertion Sort" << std::endl;
            std::cout << raw << std::endl;
            break;
        }
    }
    return flag;
}


bool is_merge_sort(std::vector<int> raw, const std::vector<int> &target)
{
    bool flag = false;
    for (int step = 2; step / 2 <= raw.size(); step *= 2)
    {
        if (step != 2)
            flag = raw == target;

        for (int i = 0; i < raw.size(); i += step)
        {
            auto end = raw.begin() + i + step;
            if (end - raw.end() > 0)
                end = raw.end();
            std::sort(raw.begin() + i, end);
        }

        if (flag)
        {
            std::cout << "Merge Sort" << std::endl;
            std::cout << raw << std::endl;
            break;
        }
    }
    return flag;
}





void entry()
{
    int n, x;
    scanf("%d", &n);
    std::vector<int> raw, target;
    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &x);
        raw.push_back(x);
    }
    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &x);
        target.push_back(x);
    }

    if (is_insertion_sort(raw, target))
    {
    }
    else if (is_merge_sort(raw, target))
    {
    }

}
}

namespace basic_36 {
void entry()
{
    int col;
    char c;
    scanf("%d %c", &col, &c);
    int row = round(1.0 * col / 2.0);
    for (int i = 1; i <= row; ++i)
    {
        for (int j = 1; j <= col; ++j)
        {
            if (i == 1 || i == row)
                printf("%c", c);
            else if (1 < j && j < col)
                printf(" ");
            else
                printf("%c", c);
        }
        printf("\n");
    }

}
}

namespace basic_37 {
struct money
{
    int galleon, sickle, knut;
};

money operator-(money a, money b)
{
    money res;
    res.knut = a.knut - b.knut;
    if (res.knut < 0)
    {
        --a.sickle;
        res.knut += 29;
    }
    res.sickle = a.sickle - b.sickle;
    if (res.sickle < 0)
    {
        --a.galleon;
        res.sickle += 17;
    }
    res.galleon = a.galleon - b.galleon;
    return res;
}

bool operator<(money a, money b)
{
    money res = a - b;
    return res.galleon < 0;
}



void entry()
{
    money b, a, res;
    scanf("%d.%d.%d %d.%d.%d", &b.galleon, &b.sickle, &b.knut,
            &a.galleon, &a.sickle, &a.knut);
    if (a < b)
    {
        res = b - a;
        res.galleon *= -1;
    }
    else
    {
        res = a - b;
    }
    printf("%d.%d.%d", res.galleon, res.sickle, res.knut);
}
}

namespace basic_38 {
constexpr int N = 105;

int table[N];

void entry()
{
    int n, s;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &s);
        table[s]++;
    }

    int k, q;
    scanf("%d", &k);
    for (int j = 0; j < k; ++j)
    {
        scanf("%d", &q);
        printf("%d", table[q]);
        if (j < k - 1)
            printf(" ");
    }
}
}

namespace basic_39 {
constexpr int N = 1005;
constexpr int N2 = 256;

char s1[N], s2[N];
int table1[N2], table2[N2];

void entry()
{
    scanf("%s%s", s1, s2);
    int n1 = strlen(s1);
    int n2 = strlen(s2);

    for (int i = 0; i < n1; ++i)
    {
        ++table1[s1[i]];
    }
    for (int j = 0; j < n2; ++j)
    {
        ++table2[s2[j]];
    }

    int extra = 0;
    for (int c = 0; c < N2; ++c)
    {
        if (table2[c] != 0)
            extra += (table1[c] - table2[c] > 0 ? 0 : table1[c] - table2[c]);
    }
    if (extra >= 0)
    {
        printf("Yes %d", n1 - n2);
    }
    else
    {
        printf("No %d", -extra);
    }
}
}

namespace basic_40 {
constexpr int MOD = 1000000007;
constexpr int N = 100'005;

char str[N];

void entry()
{
    scanf("%s", str);
    int n = strlen(str);
    long ans = 0;

    int left_p = 0, right_t = 0;
    for (int j = 0; j < n; ++j)
    {
        if (str[j] == 'T') ++right_t;
    }
    for (int i = 0; i < n; ++i)
    {
        if (str[i] == 'P')
            ++left_p;
        else if (str[i] == 'T')
            --right_t;
        else
        {
            ans += (left_p * right_t) % MOD;
            ans %= MOD;
        }
    }


    printf("%ld", ans);
}
}

namespace basic_41 {
constexpr int N = 1005;

struct stu
{
    long long id;
    int num_test, num_seat;
};

stu all[N];

void entry()
{
    int n;
    scanf("%d", &n);
    stu tmp;
    for (int i = 0; i < n; ++i)
    {
        scanf("%lld%d%d", &tmp.id, &tmp.num_test, &tmp.num_seat);
        all[tmp.num_test] = tmp;
    }
    int m, tid;
    scanf("%d", &m);
    for (int j = 0; j < m; ++j)
    {
        scanf("%d", &tid);
        printf("%lld %d\n", all[tid].id, all[tid].num_seat);
    }

}
}

namespace basic_42 {
constexpr int N = 1005;

char text[N];
int table[26];

void entry()
{
    fgets(text, N, stdin);
    int len = strlen(text);

    for (int i = 0; i < len; ++i)
    {
        auto c = text[i];
        if ('a' <= c  && c <= 'z')
        {
            ++table[c-'a'];
        }
        else if ('A' <= c && c <= 'Z')
        {
            ++table[c-'A'];
        }
    }
    int max_index = 0;
    for (int j = 0; j < 26; ++j)
    {
        if (table[j] > table[max_index])
            max_index = j;
    }
    printf("%c %d", max_index + 'a', table[max_index]);
}
}

namespace basic_43 {
constexpr int N = 10'005;
const char dict[6] = {'P', 'A', 'T', 'e', 's', 't'};

char str[N];
int table[6];

void entry()
{
    fgets(str, N, stdin);
    int len = strlen(str);
    int sum = 0;
    for (int i = 0; i < len; ++i)
    {
        for (int j = 0; j < 6; ++j)
        {
            if (str[i] == dict[j])
            {
                table[j]++;
                sum++;
            }
        }
    }

    while (sum > 0)
    {
        for (int i = 0; i < 6; ++i)
        {
            if (table[i] > 0)
            {
                printf("%c", dict[i]);
                --table[i];
                --sum;
            }
        }
    }
}
}

namespace basic_44 {














}






























int main(int argc, char **argv)
{
//    basic_31::entry();
//    basic_32::entry();
//    basic_33::entry();
//    basic_34::entry();
//    basic_35::entry();
//    basic_36::entry();
//    basic_37::entry();
//    basic_38::entry();
//    basic_39::entry();
//    basic_40::entry();
//    basic_41::entry();
//    basic_42::entry();
    basic_43::entry();
    return 0;
}
