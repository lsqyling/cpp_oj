#include <cstdio>
#include <cstring>
#include <queue>
#include <map>
#include <algorithm>
#include <sstream>
#include <set>
#include <iostream>
#include <cmath>
using std::endl;

namespace pat_a1091 {
constexpr int M = 1290;
constexpr int N = 130;
constexpr int Z = 61;


struct node
{
    int x, y, z;
};

int pixel[M][N][Z];
bool inq[M][N][Z];

int m, n, slice, t;

int delta_x[6] = {0, 0, 0, 0, 1, -1};
int delta_y[6] = {0, 0, 1, -1, 0, 0};
int delta_z[6] = {1, -1, 0, 0, 0, 0};

bool judge(int x, int y, int z)
{
    if (x >= m || x < 0 || y >= n || y < 0 || z >= slice || z < 0)
    {
        return false;
    }
    if (pixel[x][y][z] == 0 || inq[x][y][z])
    {
        return false;
    }
    return true;
}

int bfs(int x, int y, int z)
{
    int tok = 0;
    std::queue<node> queue;
    queue.push({x, y, z});
    inq[x][y][z] = true;
    while (!queue.empty())
    {
        ++tok;
        node top = queue.front();
        queue.pop();
        for (int i = 0; i < 6; ++i)
        {
            int new_x = top.x + delta_x[i];
            int new_y = top.y + delta_y[i];
            int new_z = top.z + delta_z[i];
            if (judge(new_x, new_y, new_z))
            {
                queue.push({new_x, new_y, new_z});
                inq[new_x][new_y][new_z] = true;
            }
        }
    }
    if (tok >= t)
    {
        return tok;
    }
    return 0;
}

void entry()
{
    scanf("%d%d%d%d", &m, &n, &slice, &t);
    for (int z = 0; z < slice; ++z)
    {
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                scanf("%d", &pixel[i][j][z]);
            }
        }
    }
    int ans = 0;
    for (int z = 0; z < slice; ++z)
    {
        for (int x = 0; x < m; ++x)
        {
            for (int y = 0; y < n; ++y)
            {
                if (pixel[x][y][z] == 1 && !inq[x][y][z])
                {
                    ans += bfs(x, y, z);
                }
            }
        }
    }

    printf("%d\n", ans);
}
}


namespace pat_a1092 {
constexpr int N = 1005;
constexpr int CHAR_LEN = 256;

int table[CHAR_LEN];

void entry()
{
    char shop_own[N], self[N];
    scanf("%s%s", shop_own, self);

    int len1 = strlen(shop_own);
    int len2 = strlen(self);
    for (int i = 0; i < len1; ++i)
        ++table[shop_own[i]];
    int miss = 0;
    for (int j = 0; j < len2; ++j)
    {
        if (table[self[j]] < 1)
            ++miss;
        else
            --table[self[j]];
    }

    if (miss)
        printf("No %d", miss);
    else
        printf("Yes %d", len1 - len2);

}
}

namespace pat_a1093 {
constexpr int N = 100'005;
constexpr int MOD = 1000000007;

char input[N];

void entry()
{
    int c, len = 0;
    int num_t = 0;
    while ((c = getchar()) != EOF)
    {
        if (c == '\n')
            break;
        input[len++] = c;
        if (c == 'T')
            ++num_t;
    }

    int left_num_p = 0;
    int right_num_t = num_t;
    int sum = 0;
    for (int i = 0; i < len; ++i)
    {
        switch (input[i])
        {
            case 'P':
                ++left_num_p;
                break;
            case 'A':
                sum = (sum + left_num_p * right_num_t) % MOD;
                break;
            case 'T':
                --right_num_t;
                break;
            default:
                abort();
        }
    }

    printf("%d\n", sum);
}
}

namespace pat_a1094 {
constexpr int N = 105;

std::vector<int> tree[N];

int table[N];

void dfs(int index, int level)
{
    ++table[level];
    for (auto idx : tree[index])
    {
        dfs(idx, level + 1);
    }
}

void entry()
{
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; ++i)
    {
        int parent, child, k;
        scanf("%d%d", &parent, &k);
        for (int i = 0; i < k; ++i)
        {
            scanf("%d", &child);
            tree[parent].push_back(child);
        }
    }

    dfs(1, 1);
    int max_num = 0, level = -1;
    for (int i = 1; i <= n; ++i)
    {
        if (table[i] > max_num)
        {
            max_num = table[i];
            level = i;
        }
    }
    printf("%d %d\n", max_num, level);
}
}

namespace pat_a1095 {
constexpr int N = 10'005;

enum { IN = 0, OUT};

struct car
{
    char plate[10];
    int time;
    int status;
};

auto cmp_by_plate_time = [](car a, car b)
{
    auto r = strcmp(a.plate, b.plate);
    if (r != 0)
    {
        return r < 0;
    }
    else
    {
        return a.time < b.time;
    }
};

car all[N], valid[N];
int len = 0;

std::map<std::string, int> car_park_time;

void entry()
{
    int n, k;
    scanf("%d%d", &n, &k);
    int h, m, s;
    char tmp[5];
    for (int i = 0; i < n; ++i)
    {
        scanf("%s %d:%d:%d %s", all[i].plate, &h, &m, &s, tmp);
        all[i].time = h * 3600 + m * 60 + s;
        if (strcmp(tmp, "in") == 0)
            all[i].status = IN;
        else if (strcmp(tmp, "out") == 0)
            all[i].status = OUT;
    }

    std::sort(all, all + n, cmp_by_plate_time);
    int max_time = 0;
    for (int i = 0; i < n - 1; ++i)
    {
        if (strcmp(all[i].plate, all[i+1].plate) == 0)
        {
            if (all[i].status == IN && all[i+1].status == OUT)
            {
                valid[len++] = all[i];
                valid[len++] = all[i+1];
                car_park_time[all[i].plate] += all[i+1].time - all[i].time;
                max_time = std::max(max_time, car_park_time[all[i].plate]);
            }
        }
    }

    auto cmp_by_time = [](car a, car b)
    {
        return a.time < b.time;
    };
    std::sort(valid, valid + len, cmp_by_time);

    int num = 0, now = 0;
    for (int i = 0; i < k; ++i)
    {
        scanf("%d:%d:%d", &h, &m, &s);
        while (now < len && valid[now].time <= h * 3600 + m * 60 + s)
        {
            if (valid[now].status == IN)
                ++num;
            else if (valid[now].status == OUT)
                --num;
            ++now;
        }
        printf("%d\n", num);
    }

    for (const auto &item : car_park_time)
    {
        if (item.second == max_time)
        {
            printf("%s ", item.first.c_str());
        }
    }
    printf("%02d:%02d:%02d\n", max_time / 3600, max_time % 3600 / 60, max_time % 60);
}
}

namespace pat_a1096 {

void entry()
{
    int n;
    scanf("%d", &n);
    int sqrt_n = sqrt(1.0 * n);
    int base = 0, len = 0;
    for (int i = 2; i <= sqrt_n; ++i)
    {
        int tmp = 1, j = i;
        while (1)
        {
            tmp *= j;
            if (n % tmp != 0)
                break;
            if (j - i + 1 > len)
            {
                base = i;
                len = j - i + 1;
            }
            ++j;
        }
    }
    if (len == 0)
    {
        printf("1\n%d\n", n);
    }
    else
    {
        printf("%d\n", len);
        for (int i = base; i < base + len; ++i)
        {
            printf("%d", i);
            if (i < base + len - 1)
            {
                printf("*");
            }
        }
    }
}
}

namespace pat_a1097 {
constexpr int N = 100'005;
constexpr int M = 10'005;

struct node
{
    int id;
    int key;
    int next;
};

node list[N], removed_list[N];
int len = 0;
bool is_duplicate[M];


void entry()
{
    int h, n;
    scanf("%d%d", &h, &n);
    int id, v, next;
    for (int i = 0; i < n; ++i)
    {
        scanf("%d%d%d", &id, &v, &next);
        list[id].id = id;
        list[id].key = v;
        list[id].next = next;
    }
    int cur = h, p = -1;
    while (cur != -1)
    {
        if (is_duplicate[std::abs(list[cur].key)])
        {
            removed_list[len++] = list[cur];
            list[p].next = list[cur].next;

        }
        else
        {
            is_duplicate[std::abs(list[cur].key)] = true;
            p = cur;
        }

        cur = list[cur].next;
    }

    p = h;
    while (p != -1)
    {
        if (list[p].next != -1)
        {
            printf("%05d %d %05d\n", list[p].id, list[p].key, list[p].next);
        }
        else
        {
            printf("%05d %d -1\n", list[p].id, list[p].key);
        }
        p = list[p].next;
    }
    for (int i = 0; i < len; ++i)
    {
        if (i != len - 1)
        {
            printf("%05d %d %05d\n", removed_list[i].id, removed_list[i].key, removed_list[i+1].id);
        }
        else
        {
            printf("%05d %d -1\n", removed_list[i].id, removed_list[i].key);
        }
    }
}
}

namespace pat_a1098 {
constexpr int N = 105;

int nums[N], n;
std::vector<int> one_step_result;
bool is_insert_sort;


void insert_sort()
{
    std::vector<int> seq(nums, nums + n);
    for (int i = 1; i < n; ++i)
    {
        if (i != 1 && seq == one_step_result)
        {
            is_insert_sort = true;
        }
        int bak = seq[i], j;
        for (j = i - 1; j >= 0 && seq[j] > bak; --j)
        {
            seq[j + 1] = seq[j];
        }
        seq[j + 1] = bak;
        if (is_insert_sort)
        {
            printf("Insertion Sort\n");
            for (int k = 0; k < n; ++k)
            {
                printf("%d", seq[k]);
                if (k != n - 1)
                {
                    printf(" ");
                }
            }
            break;
        }
    }
}

int heap[N];

void init_heap()
{
    for (int i = 1; i <= n; ++i)
    {
        heap[i] = nums[i - 1];
    }
}

void down_adjust(int low, int high)
{
    int i = low, j = 2 * i;
    while (j <= high)
    {
        if (j + 1 <= high && heap[j + 1] > heap[j])
        {
            j = j + 1;
        }
        if (heap[j] > heap[i])
        {
            std::swap(heap[j], heap[i]);
            i = j;
            j = 2 * i;
        }
        else
            break;
    }
}

void build_heap()
{
    init_heap();
    for (int i = n / 2; i >= 1; --i)
    {
        down_adjust(i, n);
    }
}

bool is_same()
{
    for (int i = 1; i <= n; ++i)
    {
        if (heap[i] != one_step_result[i - 1])
            return false;
    }
    return true;
}

void heap_sort()
{
    if (is_insert_sort)
        return;

    build_heap();
    bool flag = false;
    for (int i = n; i > 1; --i)
    {
        if (is_same())
        {
            flag = true;
        }
        std::swap(heap[1], heap[i]);
        down_adjust(1, i - 1);
        if (flag)
        {
            printf("Heap Sort\n");
            for (int j = 1; j <= n; ++j)
            {
                printf("%d", heap[j]);
                if (j < n)
                {
                    printf(" ");
                }
            }
            break;
        }
    }
}

void entry()
{
    int x;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &nums[i]);
    }
    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &x);
        one_step_result.push_back(x);
    }
    insert_sort();
    heap_sort();
}
}


namespace pat_a1099 {
constexpr int N = 105;

struct node
{
    int data;
    int left, right;
};

node tree[N];
int nums[N], n, len = 0;

void inorder_traversal(int root)
{
    if (root == -1)
        return ;
    inorder_traversal(tree[root].left);
    tree[root].data = nums[len++];
    inorder_traversal(tree[root].right);
}

void layer_traversal(int root)
{
    std::queue<node> q;
    q.push(tree[root]);
    int cnt = 0;
    while (!q.empty())
    {
        node top = q.front();
        q.pop();
        ++cnt;
        printf("%d", top.data);
        if (cnt < n)
            printf(" ");
        if (top.left != -1)
        {
            q.push(tree[top.left]);
        }
        if (top.right != -1)
        {
            q.push(tree[top.right]);
        }
    }
}

void entry()
{
    scanf("%d", &n);
    int left, right;
    for (int i = 0; i < n; ++i)
    {
        scanf("%d%d", &left, &right);
        tree[i].left = left;
        tree[i].right = right;
    }
    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &nums[i]);
    }
    std::sort(nums, nums + n);
    inorder_traversal(0);
    layer_traversal(0);
}
}

namespace pat_a1100 {
const char *single_digit[13] = {"tret", "jan", "feb", "mar",
                                "apr", "may", "jun", "jly",
                                "aug", "sep", "oct", "nov", "dec"};
const char *tens_digit[13] = {"tret", "tam", "hel", "maa",
                              "huh", "tou", "kes", "hei",
                              "elo", "syy", "lok", "mer", "jou"};
std::map<std::string, int> tens_to_n{{"tret", 0}, {"tam", 1}, {"hel", 2}, {"maa", 3},
                                     {"huh", 4}, {"tou", 5}, {"kes", 6}, {"hei", 7},
                                     {"elo", 8}, {"syy", 9}, {"lok", 10}, {"mer", 11},
                                     {"jou", 12}};
std::map<std::string, int> single_to_n{{"tret", 0}, {"jan", 1}, {"feb", 2}, {"mar", 3},
                                       {"apr", 4}, {"may", 5}, {"jun", 6}, {"jly", 7},
                                       {"aug", 8}, {"sep", 9}, {"oct", 10}, {"nov", 11},
                                       {"dec", 12}};

bool is_mars_num(std::vector<std::string> &line)
{
    bool is_mars_n = false;
    for (auto &s : line)
    {
        try
        {
            std::stoi(s);
        } catch (...)
        {
            is_mars_n = true;
            break;
        }
    }
    return is_mars_n;
}

int mars_to_num(std::vector<std::string> &line)
{
    int sum = 0;
    for (auto &s : line)
    {
        auto it = single_to_n.find(s);
        if (it != single_to_n.end())
        {
            sum += it->second;
        }
        else
        {
            sum += tens_to_n[s] * 13;
        }
    }
    return sum;
}

std::vector<std::string> num_to_mars(std::vector<std::string> &line)
{
    std::vector<std::string> r;
    int n = 0;
    for (auto &s : line)
    {
        n += std::stoi(s);
    }
    int tens = n / 13;
    int s = n % 13;
    if (tens)
    {
        r.push_back(tens_digit[tens]);
    }
    if (s)
    {
        r.push_back(single_digit[s]);
    }
    if (tens == 0 && s == 0)
    {
        r.push_back(single_digit[0]);
    }
    return r;
}


void entry()
{
    int n;
    std::cin >> n;
    std::cin.get();
    std::string line, word;
    for (int i = 0; i < n; ++i)
    {
        std::getline(std::cin, line);
        std::istringstream os(line);
        std::vector<std::string> line_words;
        while (os >> word)
        {
            line_words.push_back(word);
        }
        if (is_mars_num(line_words))
        {
            std::cout << mars_to_num(line_words);
        }
        else
        {
            auto v = num_to_mars(line_words);
            for (int j = 0; j < v.size(); ++j)
            {
                std::cout << v[j];
                if (j != v.size() - 1)
                {
                    std::cout << " ";
                }
            }
        }
        std::cout << endl;
    }
}
}

namespace pat_a1101 {
constexpr int N = 100'005;
constexpr int INF = 0x3fff'ffff;

int nums[N], n;
int left_max[N], right_min[N];

void init_left_right()
{
    left_max[0] = 0;
    for (int i = 1; i < n; ++i)
    {
        if (nums[i-1] > left_max[i-1])
        {
            left_max[i] = nums[i-1];
        }
        else
        {
            left_max[i] = left_max[i-1];
        }
    }
    right_min[n-1] = INF;
    for (int i = n - 2; i >= 0; --i)
    {
        if (nums[i+1] < right_min[i+1])
        {
            right_min[i] = nums[i+1];
        }
        else
        {
            right_min[i] = right_min[i+1];
        }
    }
}

void entry()
{
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &nums[i]);
    }
    init_left_right();
    std::vector<int> ans;
    for (int i = 0; i < n; ++i)
    {
        if (left_max[i] < nums[i] && nums[i] < right_min[i])
        {
            ans.push_back(nums[i]);
        }
    }
    std::sort(ans.begin(), ans.end());
    printf("%zu\n", ans.size());
    for (int i = 0; i < ans.size(); ++i)
    {
        printf("%d", ans[i]);
        if (i != ans.size() - 1)
        {
            printf(" ");
        }
    }
}
}

namespace pat_a1102 {
constexpr int N = 15;

struct node
{
    int data;
    int left, right;
};

node tree[N];
int n;
bool is_child[N];


void invert_tree(int root)
{
    if (root == -1)
        return ;
    invert_tree(tree[root].left);
    invert_tree(tree[root].right);
    std::swap(tree[root].left, tree[root].right);
}

void level_order(int root)
{
    std::queue<node> q;
    q.push(tree[root]);
    int cnt = 0;
    while (!q.empty())
    {
        node top = q.front();
        q.pop();
        ++cnt;
        printf("%d", top.data);
        if (cnt < n)
        {
            printf(" ");
        }
        if (top.left != -1)
        {
            q.push(tree[top.left]);
        }
        if (top.right != -1)
        {
            q.push(tree[top.right]);
        }
    }
    printf("\n");
}

void inorder_traversal(int root)
{
    if (root == -1)
        return ;
    static int cnt = 0;
    inorder_traversal(tree[root].left);
    printf("%d", tree[root].data);
    if (++cnt < n)
    {
        printf(" ");
    }
    inorder_traversal(tree[root].right);
}


int find_root()
{
    for (int i = 0; i < n; ++i)
    {
        if (!is_child[i])
        {
            return i;
        }
    }
    return -1;
}


void entry()
{
    scanf("%d", &n);
    char left, right;
    for (int i = 0; i < n; ++i)
    {
        scanf("%*c%c %c", &left, &right);
        tree[i].data = i;
        if (left != '-')
        {
            tree[i].left = left - '0';
            is_child[left - '0'] = true;
        }
        else
        {
            tree[i].left = -1;
        }
        if (right != '-')
        {
            tree[i].right = right - '0';
            is_child[right - '0'] = true;
        }
        else
        {
            tree[i].right = -1;
        }
    }
    int root = find_root();
    invert_tree(root);
    level_order(root);
    inorder_traversal(root);
}
}

namespace pat_a1103 {

std::vector<int> fac, tmp, ans;
int n, k;
int max_fac_sum = -1;

int pow(int base, int p)
{
    int r = 1;
    for (int i = 0; i < p; ++i)
    {
        r *= base;
    }
    return r;
}

void init_fac(int p)
{
    int t = 0, i = 0;
    while (t <= n)
    {
        fac.push_back(t);
        t = pow(++i, p);
    }
}

void dfs(int index, int now_k, int sum, int fac_sum)
{
    if (now_k == k && sum == n)
    {
        if (fac_sum > max_fac_sum)
        {
            max_fac_sum = fac_sum;
            ans = tmp;
        }
        return ;
    }
    if (now_k > k || sum > n)
        return ;
    if (index >= 1)
    {
        tmp.push_back(index);
        dfs(index, now_k + 1, sum + fac[index], fac_sum + index);
        tmp.pop_back();
        dfs(index - 1, now_k, sum, fac_sum);
    }
}

void entry()
{
    int p;
    scanf("%d%d%d", &n, &k, &p);
    init_fac(p);
    dfs(fac.size() - 1, 0, 0, 0);
    if (max_fac_sum == -1)
    {
        printf("Impossible\n");
    }
    else
    {
        printf("%d = %d^%d", n, ans[0], p);
        for (int i = 1; i < ans.size(); ++i)
        {
            printf(" + %d^%d", ans[i], p);
        }
    }
}
}

namespace pat_a1104 {
void entry()
{
    int n;
    scanf("%d", &n);
    long double sum = 0, a_i;
    for (int i = 1; i <= n; ++i)
    {
        scanf("%Lf", &a_i);
        sum += a_i * i * (n - i + 1);
    }
    printf("%.2Lf\n", sum);
}
}

namespace pat_a1105 {
constexpr int N = 1000;

int matrix[N][N];
int nums[N * N], total_nums;


void fill_matrix(int m, int n)
{
    int index = 0;
    int row = 0, col = 0;
    while (index < total_nums)
    {
        for (int i = row; i < n; ++i)
        {
            matrix[row][i] = nums[index++];
        }
        for (int i = row + 1; i < m; ++i)
        {
            matrix[i][n-1] = nums[index++];
        }
        for (int j = n - 2; j >= col; --j)
        {
            matrix[m-1][j] = nums[index++];
        }
        if (index < total_nums)
        {
            for (int j = m - 2; j > row; --j)
            {
                matrix[j][col] = nums[index++];
            }
        }
        ++row;
        ++col;
        --m;
        --n;
    }
}

void entry()
{
    scanf("%d", &total_nums);
    for (int i = 0; i < total_nums; ++i)
    {
        scanf("%d", &nums[i]);
    }
    std::sort(nums, nums + total_nums, [](int a, int b) { return a > b; });
    int m = std::sqrt(total_nums);
    int n = m;
    while (1)
    {
        if (m * n < total_nums)
        {
            ++m;
        }
        else if (m * n > total_nums)
        {
            --n;
        }
        else
        {
            break;
        }
    }
    fill_matrix(m, n);
    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            printf("%d", matrix[i][j]);
            if (j != n - 1)
            {
                printf(" ");
            }
        }
        printf("\n");
    }
}
}

namespace pat_a1106 {
constexpr int N = 100'005;


std::vector<int> tree[N];
int lowest_depth = N, lowest_num = 0;
double p, r;


void dfs(int index, int depth)
{
    if (tree[index].empty())
    {
        if (depth < lowest_depth)
        {
            lowest_depth = depth;
            lowest_num = 1;
        }
        else if (depth == lowest_depth)
        {
            ++lowest_num;
        }
        return ;
    }
    for (auto child : tree[index])
    {
        dfs(child, depth + 1);
    }
}

void entry()
{
    int n;
    scanf("%d%lf%lf", &n, &p, &r);
    r /= 100;
    for (int i = 0; i < n; ++i)
    {
        int k, x;
        scanf("%d", &k);
        for (int j = 0; j < k; ++j)
        {
            scanf("%d", &x);
            tree[i].push_back(x);
        }
    }
    dfs(0, 0);
    printf("%.4f %d\n", p * std::pow(1 + r, lowest_depth), lowest_num);
}
}

namespace pat_a1107 {
constexpr int N = 1005;

int father[N], n;
int is_root[N], hobby[N];

void init()
{
    for (int i = 1; i <= n; ++i)
    {
        father[i] = i;
        is_root[i] = 0;
    }
}

int find_father(int x)
{
    int a = x;
    while (x != father[x])
    {
        x = father[x];
    }
    while (a != father[a])
    {
        int z = a;
        a = father[a];
        father[z] = x;
    }
    return x;
}

void union_(int a, int b)
{
    int fa_a = find_father(a);
    int fa_b = find_father(b);
    if (fa_a != fa_b)
    {
        father[fa_a] = fa_b;
    }
}

void entry()
{
    int k, h;
    scanf("%d", &n);
    init();
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d:", &k);
        for (int j = 0; j < k; ++j)
        {
            scanf("%d", &h);
            if (hobby[h] == 0)
            {
                hobby[h] = i;
            }
            union_(i, find_father(hobby[h]));
        }
    }

    for (int i = 1; i <= n; ++i)
    {
        ++is_root[find_father(i)];
    }
    int ans = 0;
    for (int i = 1; i <= n; ++i)
    {
        if (is_root[i])
        {
            ++ans;
        }
    }

    auto gt = [](int a, int b) { return a > b; };
    std::sort(is_root + 1, is_root + 1 + n, gt);
    printf("%d\n", ans);
    for (int i = 1; i <= ans; ++i)
    {
        printf("%d", is_root[i]);
        if (i < ans)
        {
            printf(" ");
        }
    }
}
}

namespace pat_a1108 {


bool is_legal(const std::string &num, double &d)
{
    bool flag = true;
    try
    {
        d = std::stod(num);
    } catch (...)
    {
        flag = false;
    }
    flag = flag && (d >= -1000 && d <= 1000);
    if (flag)
    {
        auto dot_pos = num.find('.');
        if (dot_pos == std::string::npos)
        {
            return flag;
        }
        else
        {
            return num.size() - 1 - dot_pos <= 2;
        }

    }
    return flag;
}

void entry()
{
    int n, cnt = 0;
    std::cin >> n;
    std::string s;
    double d, total = 0;
    for (int i = 0; i < n; ++i)
    {
        std::cin >> s;
        if (is_legal(s, d))
        {
            ++cnt;
            total += d;
        }
        else
        {
            printf("ERROR: %s is not a legal number\n", s.c_str());
        }
    }
    if (cnt != 0)
    {
        double average = total / (1.0 * cnt);
        printf("The average of %d %s is %.2f", cnt, cnt == 1 ? "number" : "numbers", average);
    }
    else
    {
        printf("The average of 0 numbers is Undefined");
    }
}
}


namespace pat_a1109 {
constexpr int N = 10'005;

struct stu
{
    char name[10];
    int height;
};

auto cmp = [](stu a, stu b)
{
    if (a.height != b.height)
    {
        return a.height > b.height;
    }
    else
    {
        return strcmp(a.name, b.name) < 0;
    }
};

stu all[N];
static bool turn_flag;

void turn_insert(std::vector<stu> &row, stu a)
{
    if (turn_flag)
    {
        row.insert(row.begin(), a);
        turn_flag = false;
    }
    else
    {
        row.push_back(a);
        turn_flag = true;
    }
}

void print_row(const std::vector<stu> &row)
{
    for (int i = 0; i < row.size(); ++i)
    {
        printf("%s", row[i].name);
        if (i < row.size() - 1)
        {
            printf(" ");
        }
    }
    printf("\n");
}

void entry()
{
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++i)
    {
        scanf("%s%d", all[i].name, &all[i].height);
    }
    std::sort(all, all + n, cmp);
    int first_row = n / m + n % m;
    std::vector<stu> row;
    for (int i = 0; i <= n; ++i)
    {
        if (i == 0 || (i - first_row >= 0 && (i - first_row) % (n/m) == 0))
        {
            turn_flag = true;
            if (i - first_row >= 0 && (i - first_row) % (n/m) == 0)
            {
                print_row(row);
                row.clear();
            }
            if (i < n)
            {
                row.push_back(all[i]);
            }
        }
        else
        {
            turn_insert(row, all[i]);
        }
    }
}
}

namespace pat_a1110 {
constexpr int N = 25;

struct node
{
    int left, right;
};

node tree[N];
bool is_child[N];
int n;

int root_of_tree()
{
    for (int i = 0; i < n; ++i)
    {
        if (!is_child[i])
            return i;
    }
    return -1;
}

int read_id()
{
    int ans = 0;
    char id[3];
    scanf("%s", id);
    if (id[0] == '-')
    {
        return -1;
    }
    else
    {
        int len = strlen(id);
        for (int i = 0; i < len; ++i)
        {
            ans = ans * 10 + (id[i] - '0');
        }
    }
    return ans;
}

bool is_complete_binary_tree(int root, int &index)
{
    std::queue<int> q;
    q.push(root);
    while (n)
    {
        auto top = q.front();
        q.pop();
        --n;
        if (top == -1)
            return false;
        index = top;
        q.push(tree[top].left);
        q.push(tree[top].right);
    }
    return true;
}


void entry()
{
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
    {
        int left = read_id();
        int right = read_id();
        tree[i].left = left;
        tree[i].right = right;
        if (left != -1)
        {
            is_child[left] = true;
        }
        if (right != -1)
        {
            is_child[right] = true;
        }
    }
    int root = root_of_tree(), index = -1;
    if (is_complete_binary_tree(root, index))
    {
        printf("YES %d\n", index);
    }
    else
    {
        printf("NO %d\n", root);
    }
}
}

namespace pat_a1111 {
constexpr int N = 505;
constexpr int INF = 0x3fff'ffff;

struct node {
    int dist;
    int time;
};

node G[N][N];
int d[N], t[N], pre_dist[N], pre_time[N];
int w[N], n;
bool visit[N];

void dijkstra_dis(int s)
{
    std::fill(d, d + N, INF);
    std::fill(t, t + N, INF);
    memset(visit, false, sizeof(visit));
    for (int i = 0; i < n; ++i)
    {
        pre_dist[i] = i;
        pre_time[i] = i;
    }
    d[s] = 0;
    t[s] = 0;
    for (int i = 0; i < n; ++i)
    {
        int u = -1, min = INF;
        for (int j = 0; j < n; ++j)
        {
            if (!visit[j] && d[j] < min)
            {
                u = j;
                min = d[j];
            }
        }
        if (u == -1)
            return ;
        visit[u] = true;
        for (int v = 0; v < n; ++v)
        {
            if (!visit[v] && G[u][v].dist != INF)
            {
                if (d[u] + G[u][v].dist < d[v])
                {
                    d[v] = d[u] + G[u][v].dist;
                    t[v] = t[u] + G[u][v].time;
                    pre_dist[v] = u;
                }
                else if (d[u] + G[u][v].dist == d[v])
                {
                    if (t[u] + G[u][v].time < t[v])
                    {
                        t[v] = t[u] + G[u][v].time;
                        pre_dist[v] = u;
                    }
                }
            }
        }
    }
}


void dijkstra_time(int s)
{
    std::fill(t, t + n, INF);
    memset(visit, false, sizeof(visit));
    for (int i = 0; i < n; ++i)
    {
        pre_time[i] = i;
    }
    t[s] = 0;
    w[s] = 1;
    for (int i = 0; i < n; ++i)
    {
        int u = -1, min = INF;
        for (int j = 0; j < n; ++j)
        {
            if (!visit[j] && t[j] < min)
            {
                u = j;
                min = t[j];
            }
        }
        if (u == -1)
            return ;
        visit[u] = true;
        for (int v = 0; v < n; ++v)
        {
            if (!visit[v] && G[u][v].time != INF)
            {
                if (t[u] + G[u][v].time < t[v])
                {
                    t[v] = t[u] + G[u][v].time;
                    w[v] = w[u] + 1;
                    pre_time[v] = u;
                }
                else if (t[u] + G[u][v].time == t[v])
                {
                    if (w[u] + 1 < w[v])
                    {
                        w[v] = w[u] + 1;
                        pre_time[v] = u;
                    }
                }
            }
        }
    }
}

bool is_same(int s, int v)
{
    while (1)
    {
        if (pre_dist[v] != pre_time[v])
            return false;
        v = pre_dist[v];
        if (v == s)
            break;
    }
    return true;
}

void print_path(int pre[], int s, int v)
{
    if (v == s)
    {
        printf("%d", v);
        return ;
    }
    print_path(pre, s, pre[v]);
    printf(" -> %d", v);
}


void entry()
{
    int m;
    scanf("%d%d", &n, &m);
    std::fill(G[0], G[0] + N * N, node{INF, INF});
    for (int i = 0; i < m; ++i)
    {
        int u, v, one_way, len, time;
        scanf("%d%d%d%d%d", &u, &v, &one_way, &len, &time);
        G[u][v].dist = len;
        G[u][v].time = time;
        if (one_way == 0)
        {
            G[v][u] = G[u][v];
        }
    }
    int s, e;
    scanf("%d%d", &s, &e);

    dijkstra_dis(s);
    dijkstra_time(s);

    if (is_same(s, e))
    {
        printf("Distance = %d; Time = %d: ",d[e],t[e]);
        print_path(pre_dist, s, e);
        return ;
    }

    printf("Distance = %d: ", d[e]);
    print_path(pre_dist, s, e);
    printf("\nTime = %d: ", t[e]);
    print_path(pre_time, s, e);
}
}

namespace pat_a1112 {
constexpr int N = 1005;

char str[N];
int table[256];
bool is_printed[256];


void entry()
{
    int k;
    scanf("%d", &k);
    memset(table, -1, sizeof(table));
    scanf("%s", str);
    int len = strlen(str);

    int i = 0, j = i + 1;
    while (i < len)
    {
        while (j < len && str[j] == str[i])
        {
            ++j;
        }
        if ((j - i) % k == 0)
        {
            table[str[i]] += (j - i) / k;
        }
        else
        {
            if (table[str[i]] > -1)
            {
                table[str[i]] = -1;
            }
        }
        i = j;
        ++j;
    }

    for (int u = 0; u < len; ++u)
    {
        if (table[str[u]] > -1 && !is_printed[str[u]])
        {
            printf("%c", str[u]);
            is_printed[str[u]] = true;
        }
        if (u == len - 1)
        {
            printf("\n");
        }
    }

    i = 0, j = i + 1;
    while (i < len)
    {
        if (table[str[i]] > -1)
        {
            while (j < len && str[j] == str[i])
            {
                ++j;
            }
        }
        if ((j - i) % k == 0)
        {
            for (int s = 0; s < (j - i) / k; ++s)
            {
                printf("%c", str[i]);
            }
        }
        else
        {
            printf("%c", str[i]);
        }

        i = j;
        ++j;
    }
}
}

namespace pat_a1113 {
constexpr int N = 100'005;

int nums[N];

void entry()
{
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &nums[i]);
    }
    std::sort(nums, nums + n);
    int s1 = 0, s2 = 0;
    int n1 = n / 2, n2 = n - n1;
    for (int i = 0; i < n1; ++i)
    {
        s1 += nums[i];
    }
    for (int i = n1; i < n; ++i)
    {
        s2 += nums[i];
    }
    printf("%d %d", std::abs(n1 - n2), s2 - s1);
}
}

namespace pat_a1114 {
constexpr int N = 10'000;

struct entry
{
    int id;
    int total_num;
    double total_sets;
    double total_area;
};

int father[N];
entry is_root[N];
entry entries[N];

auto cmp_avg = [](entry a, entry b)
{
    if (a.total_num == 0 || b.total_num == 0)
    {
        if (a.total_num != 0)
            return true;
        else if (b.total_num != 0)
            return false;
    }
    else
    {
        if (a.total_area / a.total_num != b.total_area / b.total_num)
            return a.total_area / a.total_num > b.total_area / b.total_num;
    }
    return a.id < b.id;
};

int find_father(int x)
{
    int a = x;
    while (x != father[x])
    {
        x = father[x];
    }
    while (a != father[a])
    {
        int z = a;
        a = father[a];
        father[z] = x;
    }
    return x;
}

void union_(int a, int b)
{
    int fa = find_father(a);
    int fb = find_father(b);
    if (fa != fb)
    {
        if (fa > fb)
        {
            std::swap(fa, fb);
        }
        father[fb] = fa;
    }
}

void init_father()
{
    for (int i = 0; i < N; ++i)
    {
        father[i] = i;
    }
}

void entry()
{
    int n;
    scanf("%d", &n);
    std::set<int> all;
    init_father();
    for (int i = 0; i < n; ++i)
    {
        int id, fa, mo, k, child;
        double set, area;
        scanf("%d%d%d%d", &id, &fa, &mo, &k);
        all.insert(id);
        if (fa != -1)
        {
            union_(id, fa);
            all.insert(fa);
        }
        if (mo != -1)
        {
            union_(id, mo);
            all.insert(mo);
        }
        for (int j = 0; j < k; ++j)
        {
            scanf("%d", &child);
            union_(id, child);
            all.insert(child);
        }
        scanf("%lf%lf", &set, &area);
        entries[id].id = id;
        entries[id].total_sets = set;
        entries[id].total_area = area;

    }

    for (auto id : all)
    {
        int fa = find_father(id);
        is_root[fa].id = fa;
        ++is_root[fa].total_num;
        is_root[fa].total_area += entries[id].total_area;
        is_root[fa].total_sets += entries[id].total_sets;
    }
    int families = 0;
    for (int i = 0; i < N; ++i)
    {
        if (is_root[i].total_num != 0)
        {
            ++families;
        }
    }

    std::sort(is_root, is_root + N, cmp_avg);
    printf("%d\n", families);
    for (int i = 0; i < families; ++i)
    {
        printf("%04d %d %.3f %.3f\n", is_root[i].id, is_root[i].total_num,
               is_root[i].total_sets / is_root[i].total_num,
               is_root[i].total_area / is_root[i].total_num);
    }
}
}

namespace pat_a1115 {

struct node
{
    int data, layer;
    node *left, *right;
};

int max(int a, int b)
{
    return a < b ? b : a;
}

void insert(node *&root, int x)
{
    if (root == nullptr)
    {
        root = new node;
        root->data = x;
        root->left = root->right = nullptr;
        return ;
    }
    if (x <= root->data)
    {
        insert(root->left, x);
    }
    else
    {
        insert(root->right, x);
    }
}

int high(node *root)
{
    if (root == nullptr)
        return -1;
    return max(high(root->left), high(root->right)) + 1;
}

void layer_traversal(node *root, int &n1, int &n2)
{
    std::queue<node *> q;
    q.push(root);
    int h = high(root);
    n1 = n2 = 0;
    while (!q.empty())
    {
        node *top = q.front();
        q.pop();
        if (top->layer == h)
            ++n1;
        if (top->layer == h - 1)
            ++n2;
        if (top->left)
        {
            q.push(top->left);
            top->left->layer = top->layer + 1;
        }
        if (top->right)
        {
            q.push(top->right);
            top->right->layer = top->layer + 1;
        }
    }
}

void entry()
{
    int n, x;
    scanf("%d", &n);
    node *root = nullptr;
    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &x);
        insert(root, x);
    }
    int n1 = 0, n2 = 0;
    layer_traversal(root, n1, n2);
    printf("%d + %d = %d", n1, n2, n1 + n2);
}
}

namespace pat_a1116 {
constexpr int N = 1000'5;

struct contestant
{
    int id;
    int rank;
    bool checked;
};

contestant r_arr[N];

bool is_prime(int n)
{
    if (n <= 1)
        return false;
    int sqrt_n = std::sqrt(n);
    for (int i = 2; i <= sqrt_n; ++i)
    {
        if (n % i == 0)
            return false;
    }
    return true;
}


const char *out_wards(int id)
{
    int r = r_arr[id].rank;
    bool flag = r_arr[id].checked;
    if (flag)
        return "Checked";
    if (r == 0)
        return "Are you kidding?";
    else if (r == 1)
        return "Mystery Award";
    else if (is_prime(r))
        return "Minion";
    else
        return "Chocolate";
}



void entry()
{
    int n, k, id;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &id);
        r_arr[id].id = id;
        r_arr[id].rank = i;
    }
    scanf("%d", &k);
    for (int j = 0; j < k; ++j)
    {
        scanf("%d", &id);
        int r = r_arr[id].rank;
        if (r != 0)
        {
            printf("%04d: %s\n", id, out_wards(id));
            r_arr[id].checked = true;
        }
        else
            printf("%04d: %s\n", id, out_wards(id));
    }
}
}

namespace pat_a1117 {
constexpr int N = 1000'05;

int dis[N];


void entry()
{
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &dis[i]);
    }
    std::sort(dis, dis + n, [](int a, int b) { return a > b; });
    int s = 0;
    while (s < n && dis[s] > s + 1) ++s;
    printf("%d\n", s);
}
}

namespace pat_a1118 {
constexpr int N = 1'0005;

int father[N];
bool is_root[N];

void init()
{
    for (int i = 0; i < N; ++i)
        father[i] = i;
}

int find_father(int x)
{
    int a = x;
    while (x != father[x])
    {
        x = father[x];
    }
    while (a != father[a])
    {
        int z = a;
        a = father[a];
        father[z] = x;
    }

    return x;
}

void union_(int a, int b)
{
    int fa = find_father(a);
    int fb = find_father(b);
    if (fa != fb)
    {
        father[fa] = fb;
    }
}

void entry()
{
    int n, k, a, b;
    scanf("%d", &n);
    init();
    int num_tree = 0;
    for (int i = 0; i < n; ++i)
    {
        scanf("%d%d", &k, &a);
        if (num_tree < a)
            num_tree = a;
        for (int j = 1; j < k; ++j)
        {
            scanf("%d", &b);
            if (num_tree < b)
                num_tree = b;
            union_(a, b);
        }
    }

    scanf("%d", &k);
    for (int i = 1; i <= num_tree; ++i)
    {
        is_root[find_father(i)] = true;
    }
    int sum = 0;
    for (int i = 0; i < N; ++i)
    {
        sum += is_root[i];
    }
    printf("%d %d\n", sum, num_tree);
    for (int i = 0; i < k; ++i)
    {
        scanf("%d%d", &a, &b);
        int fa = find_father(a);
        int fb = find_father(b);
        if (fa == fb)
            printf("Yes\n");
        else
            printf("No\n");
    }
}
}

namespace pat_a1119 {
constexpr int N = 35;

struct node
{
    int data;
    int left, right;
};

node tree[N];
int pre[N], post[N];
bool unique = true;
std::vector<int> in;


int create(int preL, int preR, int postL, int postR)
{
    if (preL > preR)
        return -1;
    if (preL + 1 == preR)
        unique = false;
    int root = preL;
    tree[root].data = pre[preL];
    int num_left = 0;
    for (int i = postL; i < postR; ++i)
    {
        if (pre[preL+1] == post[i])
        {
            num_left = i - postL + 1;
            break;
        }
    }
    tree[root].left = create(preL + 1, preL + num_left, postL, postL + num_left - 1);
    tree[root].right = create(preL + num_left + 1, preR, postL + num_left, postR - 1);
    return root;
}

void inorder(int root)
{
    if (root == -1)
        return ;
    inorder(tree[root].left);
    in.push_back(tree[root].data);
    inorder(tree[root].right);
}

void entry()
{
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &pre[i]);
    }
    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &post[i]);
    }
    int root = create(0, n - 1, 0, n - 1);
    inorder(root);
    if (unique)
        printf("Yes\n");
    else
        printf("No\n");
    for (int i = 0; i < n; ++i)
    {
        printf("%d", in[i]);
        if (i < n - 1)
            printf(" ");
        else
            printf("\n");
    }
}
}

namespace pat_a1120 {
constexpr int N = 1'0005;

int id_arr[N];

int calc_id(int n)
{
    int s = 0;
    do
    {
        s += n % 10;
        n /= 10;
    } while (n);
    return s;
}

std::vector<int> unique(const int A[], int n)
{
    std::vector<int> ans;

    int i = 0, j = 0;
    while (j < n)
    {
        while (A[i] == A[j]) ++j;
        ans.push_back(A[i]);
        i = j;
    }
    return ans;
}

void entry()
{
    int n, x;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &x);
        id_arr[i] = calc_id(x);
    }
    std::sort(id_arr, id_arr + n);
    auto ans = unique(id_arr, n);
    int s = ans.size();
    printf("%d\n", s);
    for (int i = 0; i < s; ++i)
    {
        printf("%d", ans[i]);
        if (i < s - 1)
            printf(" ");
        else
            printf("\n");
    }
}
}


int main(int argc, char **argv)
{
    pat_a1091::entry();
    pat_a1092::entry();
    pat_a1093::entry();
    pat_a1094::entry();
    pat_a1095::entry();
    pat_a1096::entry();
    pat_a1097::entry();
    pat_a1098::entry();
    pat_a1099::entry();
    pat_a1100::entry();
    pat_a1101::entry();
    pat_a1102::entry();
    pat_a1103::entry();
    pat_a1104::entry();
    pat_a1105::entry();
    pat_a1106::entry();
    pat_a1107::entry();
    pat_a1108::entry();
    pat_a1109::entry();
    pat_a1110::entry();
    pat_a1111::entry();
    pat_a1112::entry();
    pat_a1113::entry();
    pat_a1114::entry();
    pat_a1115::entry();
    pat_a1116::entry();
    pat_a1117::entry();
    pat_a1118::entry();
    pat_a1119::entry();
    pat_a1120::entry();
    return 0;
}























