#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>





namespace advanced_170 {

struct pair
{
    int first, second;
};


void entry()
{
    int n, r, k;
    scanf("%d%d%d", &n, &r, &k);
    pair *neighbours = new pair[r];
    for (int i = 0; i < r; ++i)
    {
        scanf("%d%d", &neighbours[i].first, &neighbours[i].second);
    }

    int m;
    scanf("%d", &m);
    bool *table = new bool[n+1];
    int *species = new int[n+1];
    for (int j = 0; j < m; ++j)
    {
        memset(table, false, sizeof(table));
        memset(species, 0, sizeof(species));
        for (int i = 1; i <= n; ++i)
        {
            scanf("%d", &species[i]);
            table[species[i]] = true;
        }
        int num = 0;
        for (int i = 1; i <= n; ++i)
        {
            num += table[i];
        }
        if (num > k)
            printf("Error: Too many species.\n");
        else if (num < k)
            printf("Error: Too few species.\n");
        else
        {
            bool flag = true;
            int u, v;
            for (int i = 0; i < r; ++i)
            {
                u = neighbours[i].first;
                v = neighbours[i].second;
                if (species[u] == species[v])
                {
                    flag = false;
                    break;
                }
            }
            if (flag)
                printf("Yes\n");
            else
                printf("No\n");
        }
    }
    delete[] table;
    delete[] species;
    delete[] neighbours;
}
}

namespace advanced_171 {

const int N = 100'005;
int num[N];

void entry()
{
    int n, m;
    std::vector<int> current, next;
    std::priority_queue<int, std::vector<int>, std::greater<int>> Q;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++)
        scanf("%d", &num[i]);
    int index = 0, count = 0, last;
    for (; index < m; index++)
        Q.push(num[index]);
    while (count != n)
    {
        last = Q.top();
        current.push_back(last);
        Q.pop();
        count++;
        if (index < n)
        {
            if (last < num[index])
            {
                Q.push(num[index++]);
            }
            else
            {
                next.push_back(num[index++]);
            }
        }
        if (Q.empty())
        {
            //输出当前
            for (int i = 0; i < current.size(); i++)
            {
                if (i != 0)printf(" ");
                printf("%d", current[i]);
            }
            printf("\n");
            current.clear();
            //
            for (int i = 0; i < next.size(); i++)
            {
                Q.push(next[i]);
            }
            next.clear();

        }
    }
}
}





int main(int argc, char **argv)
{
//    advanced_170::entry();
    advanced_171::entry();



    return 0;
}
