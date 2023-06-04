#include <cstdio>
#include <iostream>
#include <queue>
#include <algorithm>
#include <cstring>

namespace binary_tree {

template<typename T>
struct Node
{
    T data_;
    Node *left_, *right_;
};

template<typename T>
Node<T> *NewNode(T val)
{
    auto p = new Node<T>;
    p->data_ = val;
    p->left_ = p->right_ = nullptr;
    return p;
}

template<typename T>
void Search(Node<T> *root, T old_val, T new_val)
{
    if (root == nullptr)
    {
        return;
    }
    if (root->data_ == old_val)
    {
        root->data_ = new_val;
        return;
    }
    Search(root->left_, old_val, new_val);
    Search(root->right_, old_val, new_val);
}

template<typename T>
void Insert(Node<T> *&root, T val)
{
    if (root == nullptr)
    {
        root = new Node<T>;
        root->data_ = val;
        root->left_ = root->right_ = nullptr;
        return;
    }
    if (root->data_ >= val)
    {
        Insert(root->left_, val);
    }
    else
    {
        Insert(root->right_, val);
    }
}

template<typename T>
void Preorder(Node<T> *root)
{
    if (root == nullptr)
    {
        return;
    }
    std::cout << root->data_ << std::endl;
    Preorder(root->left_);
    Preorder(root->right_);
}

template<typename T>
void Inorder(Node<T> *root)
{
    if (root == nullptr)
    {
        return;
    }
    Inorder(root->left_);
    std::cout << root->data_ << std::endl;
    Inorder(root->right_);
}

template<typename T>
void Postorder(Node<T> *root)
{
    if (root == nullptr)
    {
        return;
    }
    Postorder(root->left_);
    Postorder(root->right_);
    std::cout << root->data_ << std::endl;
}

template<typename T>
void LayerOrder(Node<T> *root)
{
    std::queue<Node<T> *> Q;
    Q.push(root);
    while (!Q.empty())
    {
        Node<T> *top = Q.front();
        Q.pop();
        std::cout << top->data_ << " ";
        if (top->left_)
        {
            Q.push(top->left_);
        }
        if (top->right_)
        {
            Q.push(top->right_);
        }
    }
}
/*
 * Q: Given the pre-order traversal sequence and the middle-order traversal sequence of a binary tree,
 * reconstruct the binary tree.
 */
namespace rebuilt_tree {
constexpr int kN = 105;

int pre[kN], in[kN];

struct Node
{
    int data_;
    Node *left_, *right_;
};

Node *Creat(int pre_l, int pre_r, int in_l, int in_r)
{
    if (pre_l > pre_r)
    {
        return nullptr;
    }
    Node *root = new Node;
    root->data_ = pre[pre_l];
    int k;
    for (k = in_l; k <= in_r; ++k)
    {
        if (in[k] == pre[pre_l])
        {
            break;
        }
    }
    int n_left = k - in_l;
    root->left_ = Creat(pre_l + 1, pre_l + n_left, in_l, k - 1);
    root->right_ = Creat(pre_l + n_left + 1, pre_r, k + 1, in_r);
    return root;
}
}

namespace pat_a1020 {
constexpr int kN = 35;

struct Node
{
    int data_;
    Node *left_, *right_;
};

int post[kN], in[kN];

Node *Creat(int pl, int pr, int in_l, int in_r)
{
    if (pl > pr)
    {
        return nullptr;
    }
    Node *root = new Node;
    root->data_ = post[pr];
    int k;
    for (k = in_l; k <= in_r; ++k)
    {
        if (in[k] == post[pr])
        {
            break;
        }
    }
    int n_left = k - in_l;
    root->left_ = Creat(pl, pl + n_left - 1, in_l, k - 1);
    root->right_ = Creat(pl + n_left, pr - 1, k + 1, in_r);
    return root;
}

void LayerOrder(Node *root, int n)
{
    std::queue<Node *> Q;
    Q.push(root);
    int cnt = 0;
    while (!Q.empty())
    {
        Node *top = Q.front();
        Q.pop();
        printf("%d", top->data_);
        ++cnt;
        if (cnt < n) printf(" ");
        if (top->left_) Q.push(top->left_);
        if (top->right_) Q.push(top->right_);
    }
}

void Entry()
{
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &post[i]);
    }
    for (int j = 0; j < n; ++j)
    {
        scanf("%d", in + j);
    }
    Node *root = Creat(0, n - 1, 0, n - 1);
    LayerOrder(root, n);
}
}
}

namespace tree_traversal {
constexpr int kN = 1005;

struct Node
{
    int data_;
    int layer_;
    std::vector<int> children_;
};

Node tree[kN];

void Preorder(int root)
{
    printf("%d ", tree[root].data_);
    for (int index : tree[root].children_)
    {
        Preorder(index);
    }
}

void LayerOrder(int root)
{
    std::queue<int> Q;
    Q.push(root);
    tree[root].layer_ = 0;
    while (!Q.empty())
    {
        int top = Q.front();
        printf("%d ", tree[top].data_);
        Q.pop();
        for (int index : tree[top].children_)
        {
            tree[index].layer_ = tree[top].layer_ + 1;
            Q.push(index);
        }
    }
}

namespace pat_a1053 {
constexpr int kN = 105;

struct Node
{
    int weight_;
    std::vector<int> children_;
};

Node tree[kN];

auto cmp = [](int a, int b)
{
    return tree[a].weight_ > tree[b].weight_;
};

int path[kN], S;

void Dfs(int index, int n_nodes, int sum_w)
{
    if (sum_w > S) return;
    if (sum_w == S)
    {
        if (!tree[index].children_.empty()) return;
        for (int i = 0; i < n_nodes; ++i)
        {
            printf("%d", tree[path[i]].weight_);
            if (i < n_nodes - 1) printf(" ");
        }
        printf("\n");
        return;
    }
    for (int idx : tree[index].children_)
    {
        path[n_nodes] = idx;
        Dfs(idx, n_nodes + 1, sum_w + tree[idx].weight_);
    }
}

void Entry()
{
    int n, m;
    scanf("%d%d%d", &n, &m, &S);
    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &tree[i].weight_);
    }
    for (int i = 0; i < m; ++i)
    {
        int id, k, c_id;
        scanf("%d%d", &id, &k);
        for (int j = 0; j < k; ++j)
        {
            scanf("%d", &c_id);
            tree[id].children_.push_back(c_id);
        }
        std::sort(tree[id].children_.begin(), tree[id].children_.end(), cmp);
    }
    path[0] = 0;
    Dfs(0, 1, tree[0].weight_);
}
}
}
/*
 * Binary Search Tree
 */
namespace bst {
struct Node
{
    int data_;
    Node *left_, *right_;
};

void Search(Node *root, int x)
{
    if (root == nullptr)
    {
        printf("search failed.\n");
        return;
    }
    if (x == root->data_)
    {
        printf("%d\n", root->data_);
    }
    else if (x < root->data_)
    {
        Search(root->left_, x);
    }
    else
    {
        Search(root->right_, x);
    }
}

void Insert(Node *&root, int x)
{
    if (root == nullptr)
    {
        root = new Node;
        root->data_ = x;
        return;
    }
    if (x == root->data_)
    {
        return;
    }
    else if (x < root->data_)
    {
        Insert(root->left_, x);
    }
    else
    {
        Insert(root->right_, x);
    }
}

Node *Create(int data[], int n)
{
    Node *root = nullptr;
    for (int i = 0; i < n; ++i)
    {
        Insert(root, data[i]);
    }
    return root;
}

Node *FindMax(Node *root)
{
    while (root->right_)
    {
        root = root->right_;
    }
    return root;
}

Node *FindMin(Node *root)
{
    while (root->left_)
    {
        root = root->left_;
    }
    return root;
}

/*
 * 删除以root 为根节点的树中权值为x的结点
 */
void Delete(Node *&root, int x)
{
    if (root == nullptr)
    {
        return;
    }
    if (root->data_ == x)
    {
        if (root->left_ == nullptr && root->right_ == nullptr)
        {
            delete root;
            root = nullptr;
        }
        else if (root->left_)
        {
            Node *pre = FindMax(root->left_);
            root->data_ = pre->data_;
            Delete(root->left_, pre->data_);
        }
        else
        {
            Node *next = FindMin(root->right_);
            root->data_ = next->data_;
            Delete(root->right_, next->data_);
        }
    }
    else if (root->data_ > x)
    {
        Delete(root->left_, x);
    }
    else
    {
        Delete(root->right_, x);
    }
}
}

namespace pat_a1043 {
struct Node
{
    int data_;
    Node *left_, *right_;

    explicit Node(int x) : data_(x), left_(nullptr), right_(nullptr)
    {
    }
};

void Insert(Node *&root, int val)
{
    if (root == nullptr)
    {
        root = new Node(val);
        return;
    }
    if (val < root->data_)
    {
        Insert(root->left_, val);
    }
    else
    {
        Insert(root->right_, val);
    }
}

void Preorder(Node *root, std::vector<int> &vi)
{
    if (root == nullptr) return;
    vi.push_back(root->data_);
    Preorder(root->left_, vi);
    Preorder(root->right_, vi);
}

void PreorderMirror(Node *root, std::vector<int> &vi)
{
    if (root == nullptr) return;
    vi.push_back(root->data_);
    PreorderMirror(root->right_, vi);
    PreorderMirror(root->left_, vi);
}

void Postorder(Node *root, std::vector<int> &vi)
{
    if (root == nullptr) return;
    Postorder(root->left_, vi);
    Postorder(root->right_, vi);
    vi.push_back(root->data_);
}

void PostorderMirror(Node *root, std::vector<int> &vi)
{
    if (root == nullptr) return;
    PostorderMirror(root->right_, vi);
    PostorderMirror(root->left_, vi);
    vi.push_back(root->data_);
}

void Entry()
{
    std::vector<int> origin, pre, pre_mirror, post, post_mirror;
    int n, x;
    Node *root = nullptr;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &x);
        origin.push_back(x);
        Insert(root, x);
    }
    Preorder(root, pre);
    PreorderMirror(root, pre_mirror);
    Postorder(root, post);
    PostorderMirror(root, post_mirror);
    if (origin == pre)
    {
        printf("YES\n");
        for (int i = 0; i < post.size(); ++i)
        {
            printf("%d", post[i]);
            if (i < post.size() - 1) printf(" ");
        }
    }
    else if (origin == pre_mirror)
    {
        printf("YES\n");
        for (int i = 0; i < post_mirror.size(); ++i)
        {
            printf("%d", post_mirror[i]);
            if (i < post_mirror.size() - 1)
            {
                printf(" ");
            }
        }
    }
    else
    {
        printf("NO\n");
    }
}
}

namespace avl_tree {
struct Node
{
    int val_, height_;
    Node *left_, *right_;

    explicit Node(int x = 0) : val_(x), height_(1), left_(nullptr), right_(nullptr)
    {
    }
};

int get_height(Node *root)
{
    if (root == nullptr) return 0;
    return root->height_;
}

void UpdateHeight(Node *root)
{
    root->height_ = std::max(get_height(root->left_), get_height(root->right_)) + 1;
}

int GetBalanceFactor(Node *root)
{
    return get_height(root->left_) - get_height(root->right_);
}

void Search(Node *root, int x)
{
    if (root == nullptr)
    {
        printf("search failed.\n");
        return;
    }
    if (x == root->val_)
    {
        printf("%d\n", root->val_);
    }
    else if (x < root->val_)
    {
        Search(root->left_, x);
    }
    else
    {
        Search(root->right_, x);
    }
}

void LeftRotation(Node *&root)
{
    auto tmp = root->right_;
    root->right_ = tmp->left_;
    tmp->left_ = root;
    UpdateHeight(root);
    UpdateHeight(tmp);
    root = tmp;
}

void RightRotation(Node *&root)
{
    auto tmp = root->left_;
    root->left_ = tmp->right_;
    tmp->right_ = root;
    UpdateHeight(root);
    UpdateHeight(tmp);
    root = tmp;
}

void Insert(Node *&root, int v)
{
    if (root == nullptr)
    {
        root = new Node(v);
        return;
    }
    if (v < root->val_)
    {
        Insert(root->left_, v);
        UpdateHeight(root);
        if (GetBalanceFactor(root) == 2)
        {
            if (GetBalanceFactor(root->left_) == 1)
            {
                RightRotation(root);
            }
            else if (GetBalanceFactor(root->left_) == -1)
            {
                LeftRotation(root->left_);
                RightRotation(root);
            }
        }
    }
    else
    {
        Insert(root->right_, v);
        UpdateHeight(root);
        if (GetBalanceFactor(root) == -2)
        {
            if (GetBalanceFactor(root->right_) == -1)
            {
                LeftRotation(root);
            }
            else if (GetBalanceFactor(root->right_) == 1)
            {
                RightRotation(root->right_);
                LeftRotation(root);
            }
        }
    }
}

Node *Create(int data[], int n)
{
    Node *root = nullptr;
    for (int i = 0; i < n; ++i)
    {
        Insert(root, data[i]);
    }
    return root;
}
}

namespace union_find_set {
constexpr int kN = 1005;

int father[kN];

void Init(int n)
{
    for (int i = 1; i <= n; ++i)
    {
        father[i] = i;
    }
}

int FindFather(int x)
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

void Union(int a, int b)
{
    int fa = FindFather(a);
    int fb = FindFather(b);
    if (fa != fb)
    {
        father[fa] = fb;
    }
}

namespace good_friends {
constexpr int kN = 110;

int father[kN];
bool is_root[kN];

void Init(int n)
{
    for (int i = 1; i <= n; ++i)
    {
        father[i] = i;
        is_root[i] = false;
    }
}

int Find(int x)
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

void Union(int a, int b)
{
    int fa = Find(a);
    int fb = Find(b);
    if (fa != fb)
    {
        father[fa] = fb;
    }
}

void Entry()
{
    int n, m, a, b;
    scanf("%d%d", &n, &m);
    Init(n);
    for (int i = 0; i < m; ++i)
    {
        scanf("%d%d", &a, &b);
        Union(a, b);
    }
    for (int i = 1; i <= n; ++i)
    {
        is_root[Find(i)] = true;
    }
    int ans = 0;
    for (int i = 1; i <= n; ++i)
    {
        ans += is_root[i];
    }
    printf("%d", ans);
}
}
}

namespace heap {
constexpr int kN = 105;

int heap[kN], n;

/*
 * heap [lo, hi]
 */
void DownAdjust(int lo, int hi)
{
    int i = lo, j = 2 * i;
    while (j <= hi)
    {
        if (j + 1 <= hi && heap[j + 1] > heap[j])
        {
            j = j + 1;
        }
        if (heap[j] > heap[i])
        {
            std::swap(heap[j], heap[i]);
            i = j;
            j = i * 2;
        }
        else break;
    }
}

void BuildHeap()
{
    for (int i = n / 2; i >= 1; --i)
    {
        DownAdjust(i, n);
    }
}

void DeleteTop()
{
    heap[1] = heap[n--];
    DownAdjust(1, n);
}

/*
 * heap[lo, hi]
 */
void UpAdjust(int lo, int hi)
{
    int i = hi, j = i / 2;
    while (j >= lo)
    {
        if (heap[j] < heap[i])
        {
            std::swap(heap[j], heap[i]);
            i = j;
            j = i / 2;
        }
        else break;
    }
}

void Insert(int x)
{
    heap[++n] = x;
    UpAdjust(1, n);
}

void HeapSort()
{
    BuildHeap();
    for (int i = n; i > 1; --i)
    {
        std::swap(heap[1], heap[i]);
        DownAdjust(1, i - 1);
    }
}
}

namespace inorder_level_built_tree {
constexpr int N = 128;

struct node
{
    int data;
    node *left, *right;
};

int in[N], level[N];

node *build_tree(int inL, int inR, int n, int *layer)
{
    if (n == 0)
        return nullptr;
    int k, a = 0, b = 0;
    int tmp_left[N], tmp_right[N];

    node *root = new node;
    root->data = layer[0];
    for (k = inL; k <= inR; ++k)
    {
        if (layer[0] == in[k])
            break;
    }
    for (int i = 0; i < n; ++i)
    {
        for (int j = inL; j < k; ++j)
        {
            if (layer[i] == in[j])
            {
                tmp_left[a++] = layer[i];
                break;
            }
        }
        for (int j = k + 1; j <= inR; ++j)
        {
            if (layer[i] == in[j])
            {
                tmp_right[b++] = layer[i];
                break;
            }
        }
    }

    root->left = build_tree(inL, k - 1, a, tmp_left);
    root->right = build_tree(k + 1, inR, b, tmp_right);
    return root;
}

void preorder(node *root, int &cnt, int n)
{
    if (root == nullptr)
        return ;
    printf("%d", root->data);
    if (++cnt < n)
        printf(" ");
    else
        printf("\n");
    preorder(root->left, cnt, n);
    preorder(root->right, cnt, n);
}

void entry()
{
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &level[i]);
    }
    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &in[i]);
    }
    node *root = build_tree(0, n - 1, n, level);
    int cnt = 0;
    preorder(root, cnt, n);
}
}























int main(int argc, char *argv[])
{
//    binary_tree::pat_a1020::Entry();
//    tree_traversal::pat_a1053::Entry();
//    pat_a1043::Entry();
//    union_find_set::good_friends::Entry();
    inorder_level_built_tree::entry();
    return 0;
}