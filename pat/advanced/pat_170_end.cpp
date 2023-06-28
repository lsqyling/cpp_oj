#include <cstdio>
#include <cstring>

namespace advanced_170 {

struct pair
{
    int first, second;
};


void entry()
{
    int n, r, k;
    scanf("%d%d%d", &n, &r, &k);
    pair neighbours[r];
    for (int i = 0; i < r; ++i)
    {
        scanf("%d%d", &neighbours[i].first, &neighbours[i].second);
    }

    int m;
    scanf("%d", &m);
    bool table[n+1];
    int species[n+1];
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
}
}

namespace advanced_171 {

void entry()
{

    
}









}





int main(int argc, char **argv)
{
    advanced_170::entry();



    return 0;
}