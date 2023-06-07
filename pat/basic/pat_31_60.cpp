#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#include <iostream>
#include <map>

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
const char *ones_digits[13] =
        {"tret", "jan", "feb", "mar", "apr", "may", "jun", "jly", "aug", "sep", "oct", "nov", "dec"};
const char *tens_digits[13] =
        {"", "tam", "hel", "maa", "huh", "tou", "kes", "hei", "elo", "syy", "lok", "mer", "jou"};
const std::map<std::string, int> mars_ones_num = {
        {"tret", 0}, {"jan", 1}, {"feb", 2}, {"mar", 3},
        {"apr", 4}, {"may", 5}, {"jun", 6}, {"jly", 7},
        {"aug", 8}, {"sep", 9}, {"oct", 10}, {"nov", 11},
        {"dec", 12}};
const std::map<std::string, int> mars_tens_num = {
        {"tam", 1}, {"hel", 2}, {"maa", 3},
        {"huh", 4}, {"tou", 5}, {"kes", 6},
        {"hei", 7}, {"elo", 8}, {"syy", 9},
        {"lok", 10}, {"mer", 11}, {"jou", 12}};

int digits[5], len = 0;

void conversion_of(int n, int radix)
{
    len = 0;
    do
    {
        digits[len++] = n % radix;
        n /= radix;
    } while (n);
}

void print_mars()
{
    if (len > 1 && digits[0] != 0)
        printf("%s %s\n", tens_digits[digits[1]], ones_digits[digits[0]]);
    else if (len == 2 && digits[0] == 0)
        printf("%s\n", tens_digits[digits[1]]);
    else
        printf("%s\n", ones_digits[digits[0]]);
}

int conversion_ten_nums(int radix)
{
    int sum = 0;
    for (int i = 0; i < len; ++i)
    {
        sum = sum * radix + digits[i];
    }
    return sum;
}

std::vector<std::string> split(char str[], const char *delim)
{
    std::vector<std::string> res;
    char *s = strtok(str, delim);
    while (s != NULL)
    {
        res.emplace_back(s);
        s = strtok(NULL, delim);
    }
    return res;
}



void entry()
{
    int n;
    scanf("%d", &n);
    getchar();
    char line[10];
    for (int i = 0; i < n; ++i)
    {
        fgets(line, sizeof(line), stdin);
        int size = strlen(line);
        if (line[size-1] == '\n')
            line[size-1] = '\0';

        auto words = split(line, " ");
        if ('0' <= words[0][0] && words[0][0] <= '9')
        {
            int t = std::stoi(words[0]);
            conversion_of(t, 13);
            print_mars();
        }
        else if ('a' <= words[0][0] && words[0][0] <= 'z')
        {
            if (words.size() == 2)
            {
                len = 0;
                digits[len++] = mars_tens_num.at(words[0]);
                digits[len++] = mars_ones_num.at(words[1]);
                printf("%d\n", conversion_ten_nums(13));
            }
            else if (words.size() == 1)
            {
                len = 0;
                auto it = mars_tens_num.find(words[0]);
                if (it != mars_tens_num.end())
                {
                    digits[len++] = mars_tens_num.at(words[0]);
                    digits[len++] = 0;
                }
                else
                {
                    digits[len++] = mars_ones_num.at(words[0]);
                }

                printf("%d\n", conversion_ten_nums(13));
            }
        }
    }
}
}

namespace basic_45 {
constexpr int N = 100'005;
constexpr int INF = 0x3fff'ffff;

int seq[N];
int left_max[N], right_min[N];
int pivots[N], len = 0;

void dp_left_right(int n)
{
    left_max[0] = 0;
    for (int i = 1; i < n; ++i)
    {
        left_max[i] = std::max(left_max[i-1], seq[i-1]);
    }
    right_min[n-1] = INF;
    for (int j = n - 2; j >= 0; --j)
    {
        right_min[j] = std::min(right_min[j+1], seq[j+1]);
    }
}



void entry()
{
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &seq[i]);
    }
    dp_left_right(n);
    for (int j = 0; j < n; ++j)
    {
        if (left_max[j] < seq[j] && seq[j] < right_min[j])
            pivots[len++] = seq[j];
    }
    printf("%d\n", len);
    for (int k = 0; k < len; ++k)
    {
        printf("%d", pivots[k]);
        if (k < len - 1)
            printf(" ");
    }
    printf("\n");
}
}

namespace basic_46 {

void entry()
{
    int n;
    scanf("%d", &n);
    int arr[4];
    int a_win = 0, b_win = 0;
    for (int i = 0; i < n; ++i)
    {
        scanf("%d%d%d%d", &arr[0], &arr[1], &arr[2], &arr[3]);
        bool a = arr[1] == arr[0] + arr[2];
        bool b = arr[3] == arr[0] + arr[2];
        if (a && !b)
            ++a_win;
        else if (b && !a)
            ++b_win;
    }
    printf("%d %d\n", b_win, a_win);
}
}

namespace basic_47 {
constexpr int N = 1005;

int score[N];

void entry()
{
    int n;
    scanf("%d", &n);
    int tid, id, s;
    for (int i = 0; i < n; ++i)
    {
        scanf("%d-%d %d", &tid, &id, &s);
        score[tid] += s;
    }
    int max_id = 0;
    for (int j = 0; j < N; ++j)
    {
        if (score[j] > score[max_id])
            max_id = j;
    }
    printf("%d %d\n", max_id, score[max_id]);
}
}

namespace basic_48 {

const char OUT[13] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'J', 'Q', 'K'};
using std::string;


void entry()
{
    string s1, s2, ans;
    std::cin >> s1 >> s2;

    std::reverse(s1.begin(), s1.end());
    std::reverse(s2.begin(), s2.end());

    for (int i = 0, s; i < std::max(s1.size(), s2.size()); ++i)
    {
        int a = i < s2.size() ? s2[i] - '0' : 0;
        int b = i < s1.size() ? s1[i] - '0' : 0;

        if (i % 2 == 0)
            s = (a + b) % 13;
        else
        {
            s = a - b;
            if (s < 0)
                s += 10;
        }
        ans.push_back(OUT[s]);
    }
    std::reverse(ans.begin(), ans.end());
    std::cout << ans << std::endl;
}
}

namespace basic_49 {

void entry()
{
    int n;
    scanf("%d", &n);
    double v;
    long long sum = 0;
    for (int i = 1; i <= n; ++i)
    {

        scanf("%lf", &v);
        long long t = (long long)(1000 * v * i * (n + 1 - i));

        sum += t;
    }
    printf("%.2f\n", sum/1000.0);
}
}

namespace basic_50 {

constexpr int N = 10'005;

int seq[N];
void calc_mn(int total_num, int &m, int &n)
{
    m = sqrt(total_num);
    n = total_num / m;
    while (total_num % m != 0 || m < n)
    {
        m++;
        n = total_num / m;
    }
}



void print_matrix(int m, int n)
{
    std::vector<std::vector<int>> ans(m, std::vector<int>(n));
    int len = 0, sz = m * n;
    int row = m, col = n;
    for (int x = 0, y = 0, i, j; len < sz; ++x, ++y)
    {
        i = x;
        j = y;
        for ( ; j < n && len < sz; ++j)
        {
            ans[i][j] = seq[len++];
        }
        ++i, --j;
        for (; i < m && len < sz; ++i)
        {
            ans[i][j] = seq[len++];
        }
        --i, --j;
        for (; j >= y && len < sz; --j)
        {
            ans[i][j] = seq[len++];
        }
        ++j, --i;
        for (; i > x && len < sz; --i)
        {
            ans[i][j] = seq[len++];
        }
        --m, --n;
    }
    for (int i = 0; i < row; ++i)
    {
        for (int j = 0; j < col; ++j)
        {
            printf("%d", ans[i][j]);
            if (j < col - 1)
                printf(" ");
        }
        printf("\n");
    }
}

void entry()
{
    int total_num, m, n;
    scanf("%d", &total_num);
    for (int i = 0; i < total_num; ++i)
    {
        scanf("%d", &seq[i]);
    }

    std::sort(seq, seq + total_num, [](int a, int b) { return a > b; });
    calc_mn(total_num, m, n);
    print_matrix(m, n);
}
}

namespace basic_51 {

void entry()
{
    double r1, p1, r2, p2;
    scanf("%lf%lf%lf%lf", &r1, &p1, &r2, &p2);

    double a = r1 * r2 * cos(p1 + p2);
    double b = r1 * r2 * sin(p1 + p2);
    /*
     * Pay attention to the math of floating point numbers.
     */
    if (fabs(a) < 0.005) a = 0;
    if (fabs(b) < 0.005) b = 0;

    if (b < 0)
        printf("%.2f-%.2fi\n", a, fabs(b));
    else
        printf("%.2f+%.2fi\n", a, b);
}
}

namespace basic_52 {

char handset[15][30];
char eyeset[15][30];
char mouthset[15][30];

void do_set(char line[], int len, char set[][30])
{
    int j = 1;
    for (int i = 0; i < len; ++i)
    {
        if (line[i] == '[')
        {
            int k = 0;
            ++i;
            while (i < len && line[i] != ']')
            {
                set[j][k++] = line[i++];
            }
            ++j;
        }
    }
}

void entry()
{
    char line[1024];
    memset(line, '\0', sizeof(line));
    memset(handset, '\0', sizeof(handset));
    memset(eyeset, '\0', sizeof(eyeset));
    memset(mouthset, '\0', sizeof(mouthset));



    fgets(line, sizeof(line), stdin);
    do_set(line, strlen(line), handset);

    fgets(line, sizeof(line), stdin);
    do_set(line, strlen(line), eyeset);

    fgets(line, sizeof(line), stdin);
    do_set(line, strlen(line), mouthset);

    int k, id[6];
    scanf("%d", &k);
    for (int i = 0; i < k; ++i)
    {
        for (int j = 1; j <= 5; ++j)
        {
            scanf("%d", &id[j]);
        }
//        左手、左眼、口、右眼、右手
        if (strlen(handset[id[1]]) == 0
            || strlen(eyeset[id[2]]) == 0
            || strlen(mouthset[id[3]]) == 0
            || strlen(eyeset[id[4]]) == 0
            || strlen(handset[id[5]]) == 0)
        {
            printf("Are you kidding me? @\\/@\n");
        }
        else
        {

            printf("%s(%s%s%s)%s\n", handset[id[1]], eyeset[id[2]],
                    mouthset[id[3]], eyeset[id[4]], handset[id[5]]);
        }
    }
}
}

namespace basic_53 {

void entry()
{
    int house, D;
    double e;
    scanf("%d%lf%d", &house, &e, &D);
    int may_vacant = 0, vacant = 0;
    for (int i = 0; i < house; ++i)
    {
        int k, count = 0;
        scanf("%d", &k);
        double ei;
        for (int j = 0; j < k; ++j)
        {
            scanf("%lf", &ei);
            if (ei < e)
                ++count;
        }
        if (count > k / 2)
        {
            ++may_vacant;
            if (k > D)
                ++vacant;
        }
    }

    printf("%.1f%% %.1f%%\n", 1.0 * 100 * (may_vacant - vacant) / house,
                            1.0 * 100 * vacant / house);
}
}

namespace basic_54 {

void entry()
{
    int n;
    std::cin >> n;
    std::string str;
    int count = 0;
    double sum = 0;
    for (int i = 0; i < n; ++i)
    {
        bool is_float = true;
        std::cin >> str;

        auto it = str.find('.');
        if (it != std::string::npos)
        {
            int sz = str.size();
            if (sz - (int)it > 3)
                is_float = false;

            it = str.find('.', it + 1);
            if (it != std::string::npos)
                is_float = false;
        }
        else
        {
            for (int j = 0; j < str.size(); ++j)
            {
                if (!(('0' <= str[j] && str[j] <= '9') || str[j] == '-' || str[j] == '+'))
                {
                    is_float = false;
                    break;
                }
            }
        }

        if (str.size() > 8)
            is_float = false;

        double d;
        if (is_float)
        {
            try
            {
                d = std::stod(str);

            } catch (...)
            {
                is_float = false;
            }
        }

        if (is_float && -1000 - 0.005 < d && d < 1000 + 0.005)
        {
            ++count;
            sum += d;
        }
        else
        {
            std::cout << "ERROR: "<< str << " is not a legal number" << std::endl;
        }
    }

    if (count == 0)
        printf("The average of 0 numbers is Undefined\n");
    else if (count == 1)
    {
        printf("The average of %d number is %.2f", count, sum);
    }
    else
    {
        printf("The average of %d numbers is %.2f\n", count, sum / count);
    }
}
}

namespace basic_54_b {

void entry()
{
    int n;
    scanf("%d", &n);
    char raw[32], format[32];
    int count = 0;
    double sum = 0, tmp;
    for (int i = 0; i < n; ++i)
    {
        scanf("%s", raw);
        sscanf(raw, "%lf", &tmp);
        sprintf(format, "%.2f", tmp);
        int flag = 0;
        for (int j = 0; j < strlen(raw); ++j)
        {
            if (raw[j] != format[j])
            {
                flag = 1;
                break;
            }
        }
        if (flag == 1 || tmp > 1000 || tmp < -1000)
        {
            printf("ERROR: %s is not a legal number\n", raw);
        }
        else
        {
            sum += tmp;
            ++count;
        }
    }
    if (count == 0)
    {
        printf("The average of 0 numbers is Undefined");

    }
    else if (count == 1)
    {
        printf("The average of 1 number is %.2f", sum);
    }
    else
    {
        printf("The average of %d numbers is %.2f", count, sum / count);

    }
}
}

namespace basic_55 {
constexpr int N = 10'005;

struct stu
{
    char name[10];
    int height;
};

bool operator<(const stu &a, const stu &b)
{
    if (a.height != b.height)
        return a.height > b.height;
    else
        return strcmp(a.name, b.name) < 0;
}

stu all[N];

void line_up(int n, int k, std::vector<std::vector<stu>> &queue)
{
    int m, first_m;
    for (int i = 0; i < k; ++i)
    {
        bool flag1 = false, flag2 = false;
        bool left = true;
        int t = 1;
        m = (i == 0 ? (first_m = n / k + n % k) : n / k);
        if (i == 0)
        {
            for (int j = 0; j < m; ++j)
            {
                if (j == 0)
                    queue[i][m/2] = all[j];
                else
                {
                    if (left)
                    {
                        queue[i][m/2-t] = all[j];
                        flag1 = true;
                        left = false;
                    }
                    else
                    {
                        queue[i][m/2+t] = all[j];
                        flag2 = true;
                        left = true;
                    }
                }
                if (flag1 && flag2)
                {
                    ++t;
                    flag1 = flag2 = false;
                }
            }
        }
        else
        {
            for (int j = first_m + (i - 1) * m; j < first_m + (i - 1) * m + m; ++j)
            {
                if (j == first_m + (i - 1) * m)
                    queue[i][m/2] = all[j];
                else
                {
                    if (left)
                    {
                        queue[i][m/2-t] = all[j];
                        flag1 = true;
                        left = false;
                    }
                    else
                    {
                        queue[i][m/2+t] = all[j];
                        flag2 = true;
                        left = true;
                    }
                }
                if (flag1 && flag2)
                {
                    ++t;
                    flag1 = flag2 = false;
                }


            }
        }
    }
}


void entry()
{
    int n, k;
    scanf("%d%d", &n, &k);
    for (int i = 0; i < n; ++i)
    {
        scanf("%s%d", all[i].name, &all[i].height);
    }
    std::sort(all, all + n);
    std::vector<std::vector<stu>> queue(k, std::vector<stu>(n / k + n % k));
    line_up(n, k, queue);

    for (int j = 0; j < k; ++j)
    {
        for (int i = 0; i < (j == 0 ? n / k + n % k : n / k); ++i)
        {
            printf("%s", queue[j][i].name);
//            printf("%d", queue[j][i].height);
            if (i < (j == 0 ? n / k + n % k : n / k) - 1)
                printf(" ");
        }
        printf("\n");
    }
}
}

namespace basic_56 {

void entry()
{
    int n;
    std::cin >> n;
    std::vector<std::string> nums;
    std::string tmp;
    for (int i = 0; i < n; ++i)
    {
        std::cin >> tmp;
        nums.push_back(tmp);
    }

    int sum = 0;
    for (int j = 0; j < nums.size(); ++j)
    {

        for (int i = j + 1; i < nums.size(); ++i)
        {
            sum += std::stoi(nums[i]+nums[j]);
            sum += std::stoi(nums[j]+nums[i]);
        }
    }

    printf("%d\n", sum);

}
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
//    basic_43::entry();
//    basic_44::entry();
//    basic_45::entry();
//    basic_46::entry();
//    basic_47::entry();
//    basic_48::entry();
//    basic_49::entry();
//    basic_50::entry();
//    basic_51::entry();
//    basic_52::entry();
//    basic_53::entry();
//    basic_54::entry();
//    basic_54_b::entry();
//    basic_55::entry();
    basic_56::entry();
    return 0;
}
