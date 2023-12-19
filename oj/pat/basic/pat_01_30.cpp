#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#include <iostream>

namespace basic_1001 {
void entry()
{
    int n, step = 0;
    scanf("%d", &n);
    while (n != 1)
    {
        n & 1 ? n = (3 * n + 1) / 2 : n >>= 1;
        ++step;
    }
    printf("%d\n", step);
}
}

namespace basic_1002 {
constexpr int N = 105;
const char *PIN_YING[10] = {"0", "yi", "er", "san", "si", "wu", "liu", "qi", "ba", "jiu"};
char str[N];
int digit[N], len;

void entry()
{
    scanf("%s", str);
    int sum = 0;
    len = strlen(str);
    for (int i = 0; i < len; ++i)
    {
        sum += str[i] - '0';
    }
    len = 0;
    do
    {
        digit[len++] = sum % 10;
        sum /= 10;
    } while (sum);

    for (int i = len - 1; i >= 0; --i)
    {
        printf("%s", PIN_YING[digit[i]]);
        if (i > 0)
            printf(" ");
    }
}
}

namespace basic_1003 {
constexpr int N = 105;

void entry()
{
    int n;
    scanf("%d", &n);
    while (n--)
    {
        char str[N];
        scanf("%s", str);
        int num_p = 0, num_t = 0, other = 0;
        int loc_p = -1, loc_t = -1;
        int len = strlen(str);
        for (int i = 0; i < len; ++i)
        {
            if (str[i] == 'P')
            {
                ++num_p;
                loc_p = i;
            }
            else if (str[i] == 'T')
            {
                ++num_t;
                loc_t = i;
            }
            else if (str[i] != 'A')
                ++other;
        }
        if (num_p != 1 || num_t != 1 || other != 0 || loc_t - loc_p <= 1)
        {
            printf("NO\n");
            continue;
        }
        int x = loc_p, y = loc_t - loc_p - 1, z = len - loc_t - 1;
        if (z - x * (y - 1) == x)
            printf("YES\n");
        else
            printf("NO\n");
    }
}
}

namespace basic_1004 {
struct stu
{
    char name[15];
    char id[15];
    int score;
};

auto cmp = [](const stu &a, const stu &b)
{
    return a.score > b.score;
};


void entry()
{
    int n;
    scanf("%d", &n);
    std::vector<stu> all;
    stu tmp;
    for (int i = 0; i < n; ++i)
    {
        scanf("%s%s%d", tmp.name, tmp.id, &tmp.score);
        all.push_back(tmp);
    }
    std::sort(all.begin(), all.end(), cmp);
    printf("%s %s\n", all[0].name, all[0].id);
    printf("%s %s\n", all[n-1].name, all[n-1].id);
}
}

namespace basic_1005 {
constexpr int N = 105;
constexpr int M = 10005;

bool hash_table[M];
int nums[N];

void entry()
{
    int n;
    scanf("%d", &n);
    int count = 0, m;
    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &nums[i]);
        m = nums[i];
        while (m != 1)
        {
            m & 1 ? m = (3 * m + 1) / 2 : m >>= 1;
            hash_table[m] = true;
        }
    }
    for (int i = 0; i < n; ++i)
    {
        if (!hash_table[nums[i]])
            ++count;
    }
    std::sort(nums, nums + n, [](int a, int b){ return a > b; });
    for (int i = 0; i < n; ++i)
    {
        if (!hash_table[nums[i]])
        {
            printf("%d", nums[i]);
            --count;
            if (count > 0)
                printf(" ");
        }
    }
}
}

namespace basic_1006 {

int digit[3];

void entry()
{
    int n;
    scanf("%d", &n);
    int len = 0;
    do
    {
        digit[len++] = n % 10;
        n /= 10;
    } while (n);
    for (int i = 0; i < digit[2]; ++i)
    {
        printf("B");
    }
    for (int i = 0; i < digit[1]; ++i)
    {
        printf("S");
    }
    for (int i = 1; i <= digit[0]; ++i)
    {
        printf("%d", i);
    }
}
}

namespace basic_1007 {

bool is_prime(int n)
{
    if (n <= 1)
        return false;
    int sqrt_n = sqrt(n);
    for (int i = 2; i <= sqrt_n; ++i)
    {
        if (n % i == 0)
            return false;
    }
    return true;
}

void entry()
{
    int n;
    scanf("%d", &n);
    std::vector<int> primes;
    for (int i = 2; i <= n; ++i)
    {
        if (is_prime(i))
            primes.push_back(i);
    }
    int count = 0;
    for (int j = 1; j < primes.size(); ++j)
    {
        if (primes[j] - primes[j-1] == 2)
            ++count;
    }
    printf("%d", count);
}
}

namespace basic_1007_b {
constexpr int N = 10001;

void eratosthenes(std::vector<int> &primes, int n)
{
    bool table[N]{false};
    for (int i = 2; i < n; ++i)
    {
        if (!table[i])
        {
            primes.push_back(i);
            for (int j = i + i; j < n; j += i)
            {
                table[j] = true;
            }
        }
    }
}

void entry()
{
    int n;
    scanf("%d", &n);
    std::vector<int> primes;
    eratosthenes(primes, n + 1);
    int count = 0;
    for (int j = 1; j < primes.size(); ++j)
    {
        if (primes[j] - primes[j-1] == 2)
            ++count;
    }
    printf("%d", count);
}
}

namespace basic_1008 {

void reverse(std::vector<int> &array, int left, int right)
{
    for (int i = left, j = right; i < j; ++i, --j)
    {
        std::swap(array[i], array[j]);
    }
}

void entry()
{
    int n, m, s;
    scanf("%d%d", &n, &m);
    std::vector<int> nums;
    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &s);
        nums.push_back(s);
    }
    m %= n;
    reverse(nums, 0, n - 1);
    reverse(nums, 0, m - 1);
    reverse(nums, m, n - 1);
    for (int i = 0; i < n; ++i)
    {
        printf("%d", nums[i]);
        if (i < n - 1)
            printf(" ");
    }
}
}

namespace basic_1009 {
void entry()
{
    std::string s;
    std::vector<std::string> line;
    while (std::cin >> s)
        line.emplace_back(s);
    for (int i = line.size() - 1; i >= 0; --i)
    {
        std::cout << line[i];
        if (i > 0)
            std::cout << " ";
    }
}
}

namespace basic_1010 {
constexpr int N = 1005;

int polynomial[N];


void entry()
{
    int coef, exp;
    int count = 0;
    while (std::cin >> coef >> exp)
    {
        polynomial[exp] = coef;
    }
    polynomial[0] = 0;
    for (int i = 1; i < N; ++i)
    {
        polynomial[i-1] = polynomial[i] * i;
        polynomial[i] = 0;
        if (polynomial[i-1])
            ++count;
    }
    if (count == 0)
        printf("0 0");
    else
    {
        for (int i = N - 1; i >= 0; --i)
        {
            if (polynomial[i])
            {
                std::cout << polynomial[i] << " " << i;
                --count;
                if (count != 0)
                    std::cout << " ";
            }
        }
    }
}
}

namespace basic_1011 {

    void entry()
    {
        int n;
        scanf("%d", &n);
        long a, b, c;
        for (int i = 1; i <= n; ++i)
        {
            scanf("%ld%ld%ld", &a, &b, &c);
            if (a + b > c)
                printf("Case #%d: true\n", i);
            else
                printf("Case #%d: false\n", i);

        }
    }
}

namespace basic_1012 {

std::vector<int> a_1_5[6];

void entry()
{
    int n, x;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &x);
        switch (x % 5)
        {
            case 0:
                if (x % 2 == 0)
                    a_1_5[1].push_back(x);
                break;
            case 1:
                a_1_5[2].push_back(x);
                break;
            case 2:
                a_1_5[3].push_back(x);
                break;
            case 3:
                a_1_5[4].push_back(x);
                break;
            case 4:
                a_1_5[5].push_back(x);
                break;
        }

    }
    int a1 = 0;
    int a2 = 0;
    int a4 = 0;
    if (a_1_5[1].empty())
        printf("N ");
    else
    {
        for (int i = 0; i < a_1_5[1].size(); ++i)
        {
            a1 += a_1_5[1][i];
        }
        printf("%d ", a1);
    }
    if (a_1_5[2].empty())
        printf("N ");
    else
    {
        for (int i = 0; i < a_1_5[2].size(); ++i)
        {
            if (i % 2 == 0)
                a2 += a_1_5[2][i];
            else
                a2 -= a_1_5[2][i];
        }
        printf("%d ", a2);
    }
    if (a_1_5[3].empty())
        printf("N ");
    else
    {
        printf("%zu ", a_1_5[3].size());
    }
    if (a_1_5[4].empty())
        printf("N ");
    else
    {
        for (int i = 0; i < a_1_5[4].size(); ++i)
        {
            a4 += a_1_5[4][i];
        }
        double avg = 1.0 * a4 / a_1_5[4].size();
        printf("%.1f ", avg);
    }
    if (a_1_5[5].empty())
        printf("N\n");
    else
    {
        std::sort(a_1_5[5].begin(), a_1_5[5].end(), std::greater<int>{});
        printf("%d", a_1_5[5][0]);
    }
}
}

namespace basic_1012_b {
int ans[5], count[5];

void entry()
{
    int n, x;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &x);
        switch (x % 5)
        {
            case 0:
                if (x % 2 == 0)
                {
                    ans[0] += x;
                    ++count[0];
                }
                break;
            case 1:
                if (count[1] % 2 == 0)
                    ans[1] += x;
                else
                    ans[1] -= x;
                ++count[1];
                break;
            case 2:
                ++count[2];
                break;
            case 3:
                ans[3] += x;
                ++count[3];
                break;
            case 4:
                if (ans[4] < x)
                    ans[4] = x;
                ++count[4];
                break;
        }
    }
    if (count[0] == 0)
        printf("N ");
    else
        printf("%d ", ans[0]);
    if (count[1] == 0)
        printf("N ");
    else
        printf("%d ", ans[1]);
    if (count[2] == 0)
        printf("N ");
    else
        printf("%d ", count[2]);
    if (count[3] == 0)
        printf("N ");
    else
        printf("%.1f ", 1.0 * ans[3]/ count[3]);
    if (count[4] == 0)
        printf("N");
    else
        printf("%d", ans[4]);
}
}

namespace basic_1013 {
constexpr int N = 1000000;

bool table[N];
std::vector<int> primes;

void eratosthenes()
{
    for (int i = 2; i < N; ++i)
    {
        if (!table[i])
        {
            primes.push_back(i);
            for (int j = i + i; j < N; j += i)
            {
                table[j] = true;
            }
        }
    }
}

void entry()
{
    int m, n;
    scanf("%d%d", &m, &n);
    eratosthenes();
    int count = 0;
    for (int i = m - 1; i < n; ++i)
    {
        printf("%d", primes[i]);
        ++count;
        if (count == 10)
        {
            printf("\n");
            count = 0;
        }
        else if (i < n - 1)
        {
            printf(" ");
        }
    }
}
}

namespace basic_1014 {
const char *DAY[7] = {"MON", "TUE", "WED", "THU", "FRI", "SAT", "SUN"};

void entry()
{
    char text[4][65];
    for (int i = 0; i < 4; ++i)
    {
        scanf("%s", text[i]);
    }
    int len = std::min(strlen(text[0]), strlen(text[1]));
    int i;
    for (i = 0; i < len; ++i)
    {
        if (text[0][i] == text[1][i])
        {
            char c = text[0][i];
            if (c >= 'A' && c <= 'G')
            {
                printf("%s ", DAY[c - 'A']);
                break;
            }
        }
    }
    for (++i; i < len; ++i)
    {
        if (text[0][i] == text[1][i])
        {
            char c = text[0][i];
            if (c >= '0' && c <= '9')
            {
                printf("%02d", c - '0');
                break;
            }
            else if (c >= 'A' && c <= 'N')
            {
                printf("%02d", 10 + c - 'A');
                break;
            }
        }
    }
    len = std::min(strlen(text[2]), strlen(text[3]));
    for (i = 0; i < len; ++i)
    {
        if (text[2][i] == text[3][i])
        {
            char c = text[2][i];
            if (isalpha(c))
            {
                printf(":%02d", i);
                break;
            }
        }
    }
}
}

namespace basic_1015 {
struct talent
{
    int id;
    int moral_score, talent_score;
    int total;
};

bool operator<(const talent &a, const talent &b)
{
    if (a.total != b.total)
        return a.total > b.total;
    else if (a.moral_score != b.moral_score)
        return a.moral_score > b.moral_score;
    else
        return a.id < b.id;
}

std::vector<talent> all[4];

void entry()
{
    int n, L, H;
    scanf("%d%d%d", &n, &L, &H);
    talent tmp;
    for (int i = 0; i < n; ++i)
    {
        scanf("%d%d%d", &tmp.id, &tmp.moral_score, &tmp.talent_score);
        if (tmp.talent_score < L || tmp.moral_score < L)
            continue;
        tmp.total = tmp.moral_score + tmp.talent_score;
        if (tmp.moral_score >= H && tmp.talent_score >= H)
            all[0].push_back(tmp);
        else if (tmp.moral_score >= H && tmp.talent_score < H)
            all[1].push_back(tmp);
        else if (tmp.moral_score < H && tmp.talent_score < H && tmp.moral_score >= tmp.talent_score)
            all[2].push_back(tmp);
        else
            all[3].push_back(tmp);
    }
    int count = 0;
    for (int i = 0; i < 4; ++i)
    {
        count += all[i].size();
        std::sort(all[i].begin(), all[i].end());
    }
    printf("%d\n", count);
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < all[i].size(); ++j)
        {
            printf("%08d %d %d\n", all[i][j].id, all[i][j].moral_score, all[i][j].talent_score);
        }
    }
}
}

namespace basic_1015_b {
struct talent
{
    int id, type;
    int moral_score, talent_score;
    int total;
};

bool operator<(const talent &a, const talent &b)
{
    if (a.type != b.type)
        return a.type < b.type;
    else if (a.total != b.total)
        return a.total > b.total;
    else if (a.moral_score != b.moral_score)
        return a.moral_score > b.moral_score;
    else
        return a.id < b.id;
}

std::vector<talent> all;

void entry()
{
    int n, L, H;
    scanf("%d%d%d", &n, &L, &H);
    talent tmp;
    for (int i = 0; i < n; ++i)
    {
        scanf("%d%d%d", &tmp.id, &tmp.moral_score, &tmp.talent_score);
        if (tmp.talent_score < L || tmp.moral_score < L)
            continue;
        tmp.total = tmp.moral_score + tmp.talent_score;
        if (tmp.moral_score >= H && tmp.talent_score >= H)
            tmp.type = 1;
        else if (tmp.moral_score >= H && tmp.talent_score < H)
            tmp.type = 2;
        else if (tmp.moral_score < H && tmp.talent_score < H && tmp.moral_score >= tmp.talent_score)
            tmp.type = 3;
        else
            tmp.type = 4;
        all.push_back(tmp);
    }
    std::sort(all.begin(), all.end());
    printf("%zu\n", all.size());
    for (int j = 0; j < all.size(); ++j)
    {
        printf("%08d %d %d\n", all[j].id, all[j].moral_score, all[j].talent_score);
    }
}
}

namespace basic_1016 {

int A[10], B[10];

void entry()
{
    int a, da, b, db;
    scanf("%d%d%d%d", &a, &da, &b, &db);
    int len_a = 0, len_b = 0;
    do
    {
        A[len_a++] = a % 10;
        a /= 10;
    } while (a);
    do
    {
        B[len_b++] = b % 10;
        b /= 10;
    } while (b);
    int count_a = 0, count_b = 0;
    for (int i = 0; i < len_a; ++i)
    {
        if (A[i] == da)
            ++count_a;
    }
    for (int i = 0; i < len_b; ++i)
    {
        if (B[i] == db)
            ++count_b;
    }
    int pa = 0, pb = 0;
    for (int i = 0; i < count_a; ++i)
    {
        pa = pa * 10 + da;
    }
    for (int i = 0; i < count_b; ++i)
    {
        pb = pb * 10 + db;
    }
    printf("%d\n", pa + pb);
}
}

namespace basic_1017 {
struct bign
{
    int d[1005];
    int len;
};

bign divide(bign a, int b, int &r)
{
    bign c;
    c.len = a.len;
    for (int i = a.len - 1; i >= 0; --i)
    {
        r = r * 10 + a.d[i];
        if (r < b)
            c.d[i] = 0;
        else
        {
            c.d[i] = r / b;
            r = r % b;
        }
    }
    while (c.len > 1 && c.d[c.len - 1] == 0)
        --c.len;
    return c;
}

void entry()
{
    char strn[1005];
    int b;
    scanf("%s%d", strn, &b);
    bign a;
    a.len = strlen(strn);
    for (int i = a.len - 1, j = 0; i >= 0; --i, ++j)
    {
        a.d[j] = strn[i] - '0';
    }

    int r = 0;
    bign c = divide(a, b, r);
    for (int i = c.len - 1; i >= 0; --i)
    {
        printf("%d", c.d[i]);
    }
    printf(" %d\n", r);
}
}

namespace basic_1018 {
const int map[3] = {'B', 'C', 'J'};

int change(int c)
{
    if (c == 'B') return 0;
    if (c == 'C') return 1;
    if (c == 'J') return 2;
    return -1;
}

void entry()
{
    int times_A[3]{0}, times_B[3]{0};
    int hand_A[3]{0}, hand_B[3]{0};

    int n;
    scanf("%d", &n);
    char c1, c2;
    int k1, k2;
    for (int i = 0; i < n; ++i)
    {
        getchar();
        scanf("%c %c", &c1, &c2);
        k1 = change(c1);
        k2 = change(c2);
        if ((k1 + 1) % 3 == k2)
        {
            ++times_A[0];
            ++times_B[2];
            ++hand_A[k1];
        }
        else if (k1 == k2)
        {
            ++times_A[1];
            ++times_B[1];
        }
        else
        {
            times_A[2]++;
            times_B[0]++;
            hand_B[k2]++;
        }
    }
    printf("%d %d %d\n", times_A[0], times_A[1], times_A[2]);
    printf("%d %d %d\n", times_B[0], times_B[1], times_B[2]);
    int id1 = 0, id2 = 0;
    for (int i = 0; i < 3; ++i)
    {
        if (hand_A[i] > hand_A[id1])
            id1 = i;
        if (hand_B[i] > hand_B[id2])
            id2 = i;
    }
    printf("%c %c\n", map[id1], map[id2]);
}
}

namespace basic_1019 {

int digit[5], len = 0;

void do_digit(int n)
{
    len = 0;
    do
    {
        digit[len++] = n % 10;
        n /= 10;
    } while (n);
    while (len < 4) digit[len++] = 0;
    std::sort(digit, digit + len);
}

int big_change(int)
{
    int sum = 0;
    for (int i = len - 1; i >= 0; --i)
    {
        sum = sum * 10 + digit[i];
    }
    return sum;
}

int little_change(int)
{
    int sum = 0;
    for (int i = 0; i < len; ++i)
    {
        sum = sum * 10 + digit[i];
    }
    return sum;
}

void entry()
{
    int n, a, b;
    scanf("%d", &n);
    do
    {
        do_digit(n);
        a = big_change(n);
        b = little_change(n);
        n = a - b;
        printf("%04d - %04d = %04d\n", a, b, n);
    } while (n != 0 && n != 6174);
}
}

namespace basic_1020 {
struct moon_cake
{
    double stock;
    double total;
    double price;
};

bool operator<(const moon_cake &a, const moon_cake &b)
{
    return a.price > b.price;
}

void entry()
{
    int n;
    double D;
    scanf("%d%lf", &n, &D);
    moon_cake tmp;
    std::vector<moon_cake> cakes;
    for (int i = 0; i < n; ++i)
    {
        scanf("%lf", &tmp.stock);
        cakes.push_back(tmp);
    }
    for (int i = 0; i < n; ++i)
    {
        scanf("%lf", &cakes[i].total);
        cakes[i].price = cakes[i].total / cakes[i].stock;
    }
    std::sort(cakes.begin(), cakes.end());

    double max_profit = 0;
    for (int i = 0; i < cakes.size(); ++i)
    {
        if (cakes[i].stock <= D)
        {
            max_profit += cakes[i].total;
            D -= cakes[i].stock;
        }
        else
        {
            max_profit += D * cakes[i].price;
            break;
        }
    }

    printf("%.2f", max_profit);
}
}

namespace basic_1021 {
int count[10];

void entry()
{
    char strn[1005];
    scanf("%s", strn);
    int len = strlen(strn);
    for (int i = 0; i < len; ++i)
    {
        ++count[strn[i] - '0'];
    }
    for (int i = 0; i < 10; ++i)
    {
        if (count[i])
            printf("%d:%d\n", i, count[i]);
    }
}
}

namespace basic_1022 {
constexpr int N = 35;

int digit[N], len;

void do_digit(int n, int radix)
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
    int a, b, D;
    scanf("%d%d%d", &a, &b, &D);
    int n = a + b;
    do_digit(n, D);
    for (int i = len - 1; i >= 0; --i)
    {
        printf("%d", digit[i]);
    }
}
}

namespace basic_1023 {
void entry()
{
    int ans[10], len = 0;
    int m, min = 0, flag = 1;
    for (int i = 0; i < 10; ++i)
    {
        scanf("%d", &m);
        if (m > 0 && i > 0 && flag)
        {
            min = len;
            flag = 0;
        }
        while (m--)
            ans[len++] = i;
    }
    std::swap(ans[0], ans[min]);
    std::sort(ans + 1, ans + len);
    for (int i = 0; i < len; ++i)
    {
        printf("%d", ans[i]);
    }
}
}

namespace basic_1024 {
using std::string;

void entry()
{
    string s;
    std::cin >> s;
    bool is_negative, e_negative;
    s[0] == '-' ? (is_negative = true) : (is_negative = false);

    s.erase(s.begin());

    auto e_pos = s.find("E");
    if (e_pos == string::npos)
        exit(1);
    int n = std::stoi(s.substr(e_pos + 2));
    s[e_pos+1] == '-' ? (e_negative = true) : (e_negative = false);

    s.erase(e_pos);
    if (e_negative)
    {
        s.insert(s.begin(), n, '0');
        s.erase(s.find('.'), 1);
        s.insert(1, 1, '.');
        if (is_negative)
            s.insert(s.begin(), '-');
        std::cout << s << std::endl;
    }
    else
    {
        int t = n, m = n;
        while (t--)
            s.push_back('0');

        int dot;
        for (int i = dot = s.find('.'); m > 0 && i < s.size() - 1; ++i, --m)
        {
            std::swap(s[i], s[i+1]);
        }

        if (n < e_pos - dot - 1)
            s.erase(e_pos);
        else
            s.erase(s.find('.'));

        if (is_negative)
            s.insert(s.begin(), '-');
        std::cout << s << std::endl;
    }
}
}

namespace basic_1025 {
constexpr int N = 100005;

struct node
{
    int adr, data, next;
};

node input[N];
std::vector<node> list;

void entry()
{
    int h, n, k;
    scanf("%d%d%d", &h, &n, &k);
    int adr, data, next;
    for (int i = 0; i < n; ++i)
    {
        scanf("%d%d%d", &adr, &data, &next);
        input[adr].adr = adr;
        input[adr].data = data;
        input[adr].next = next;
    }
    int p = h;
    while (p != -1)
    {
        list.push_back(input[p]);
        p = input[p].next;
    }

    for (int i = 0; i < list.size() / k; ++i)
    {
        std::reverse(list.begin() + i * k, list.begin() + (i + 1) * k);
    }
    int i;
    for (i = 0; i < list.size() - 1; ++i)
    {
        printf("%05d %d %05d\n", list[i].adr, list[i].data, list[i+1].adr);
    }
    printf("%05d %d -1\n", list[i].adr, list[i].data);
}
}

namespace basic_1025_b {
constexpr int N = 100005;

struct node
{
    int adr, data, next;
};

node list[N];

int reverse(int head, int k)
{
    if (head == -1 || list[head].next == -1 || k < 2)
        return head;

    int tail = head;
    for (int i = 0; i < k; ++i)
    {
        if (tail == -1)
            return head;
        tail = list[tail].next;
    }
    int pre = -1;
    int cur = head;
    while (cur != tail)
    {
        auto next = list[cur].next;

        list[cur].next = pre;
        pre = cur;
        cur = next;
    }

    list[head].next = reverse(tail, k);
    return pre;
}

void entry()
{
    int h, n, k;
    scanf("%d%d%d", &h, &n, &k);

    int adr, data, next;
    for (int i = 0; i < n; ++i)
    {
        scanf("%d%d%d", &adr, &data, &next);
        list[adr].adr = adr;
        list[adr].data = data;
        list[adr].next = next;
    }

    int new_head = reverse(h, k);
    int p = new_head;
    while (p != -1)
    {
        if (list[p].next != -1)
            printf("%05d %d %05d\n", list[p].adr, list[p].data, list[p].next);
        else
            printf("%05d %d -1\n", list[p].adr, list[p].data);
        p = list[p].next;
    }
}
}

namespace basic_1026 {

void entry()
{
    int c1, c2;
    scanf("%d%d", &c1, &c2);

    int total_s = round(1.0 * (c2 - c1) / 100);
    int h, m, s;

    h = total_s / 3600;
    m = (total_s % 3600) / 60;
    s = (total_s % 3600) % 60;

    printf("%02d:%02d:%02d\n", h, m, s);
}
}

namespace basic_1027 {

void entry()
{
    int N;
    char c;
    scanf("%d %c", &N, &c);
    int n = 1;
    while (2 * n * n - 1 <= N) ++n;
    --n;
    int r = N + 1 - 2 * n * n;
    int row = 2 * n - 1, col = 2 * n - 1;
    for (int i = 0; i < row; ++i)
    {
        if (i < row / 2 + 1)
            for (int j = 0; j < col; ++j)
            {
                if (j < i || j > col - 1 - i)
                    printf(" ");
                else
                    printf("%c", c);
            }
        else
            for (int j = 0; j < col; ++j)
            {
                if (j < (col - 1 - i) || j > i)
                    printf(" ");
                else
                    printf("%c", c);
            }
        printf("\n");
    }
    printf("%d", r);
}
}

namespace basic_1028 {
struct person
{
    char name[8];
    int year, month, day;
};

bool operator<(const person &a, const person &b)
{
    if (a.year != b.year)
        return a.year > b.year;
    else if (a.month != b.month)
        return a.month > b.month;
    else
        return a.day > b.day;
}

bool is_valid(const person &a)
{
    person young{"xxx", 2014, 9, 6};
    person old{"xxx", 2014 - 200, 9, 6};
    return !(operator<(a, young) || operator<(old, a));
}

void entry()
{
    int n;
    scanf("%d", &n);
    person p;
    std::vector<person> all;
    for (int i = 0; i < n; ++i)
    {
        scanf("%s %d/%d/%d", p.name, &p.year, &p.month, &p.day);
        if (is_valid(p))
            all.push_back(p);
    }
    std::sort(all.begin(), all.end());
    if (all.size() == 0)
        printf("0\n");
    else
        printf("%zu %s %s\n", all.size(), all[all.size()-1].name, all[0].name);
}
}

namespace basic_1029 {
constexpr int N = 100;

int table[256];

void entry()
{
    char input[N], show[N];
    scanf("%s%s", input, show);

    int len1 = strlen(input);
    int len2 = strlen(show);
    for (int i = 0; i < len1; ++i)
    {
        ++table[toupper(input[i])];
    }
    for (int i = 0; i < len2; ++i)
    {
        --table[toupper(show[i])];
    }
    for (int i = 0; i < len1; ++i)
    {
        if (table[toupper(input[i])])
        {
            printf("%c", toupper(input[i]));
            table[toupper(input[i])] = 0;
        }
    }
}
}

namespace basic_1030 {
constexpr int N = 100005;

int nums[N];


void entry()
{
    int n, p;
    scanf("%d%d", &n, &p);
    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &nums[i]);
    }
    std::sort(nums, nums + n);
    int i = 0, j = 0;
    int count = 1;
    while (i < n && j < n)
    {
        while (j < n && nums[j] <= (long)nums[i] * p)
        {
            count = std::max(count, j - i + 1);
            ++j;
        }
        ++i;
    }
    printf("%d", count);
}
}


int main(int argc, char **argv)
{
    basic_1001::entry();
    basic_1002::entry();
    basic_1003::entry();
    basic_1004::entry();
    basic_1005::entry();
    basic_1006::entry();
    basic_1007::entry();
    basic_1007_b::entry();
    basic_1008::entry();
    basic_1009::entry();
    basic_1010::entry();
    basic_1011::entry();
    basic_1012::entry();
    basic_1012_b::entry();
    basic_1013::entry();
    basic_1014::entry();
    basic_1015::entry();
    basic_1015_b::entry();
    basic_1016::entry();
    basic_1017::entry();
    basic_1018::entry();
    basic_1019::entry();
    basic_1020::entry();
    basic_1021::entry();
    basic_1022::entry();
    basic_1023::entry();
    basic_1024::entry();
    basic_1025::entry();
    basic_1025_b::entry();
    basic_1026::entry();
    basic_1027::entry();
    basic_1028::entry();
    basic_1029::entry();
    basic_1030::entry();
    return 0;
}