#include <iostream>
using namespace std;

void combination(int a[], int n, int m, int b[], int M)
{
    if (m == 0) {
        for (int i = 0; i < M; i++) {
            cout << b[i] << " ";
        }
        cout << endl;
        return;
    }

    for (int i = n; i >= m; i--) {
        b[m - 1] = a[i - 1];
        combination(a, i - 1, m - 1, b, M);
    }
}

int main()
{
    int a[6] = {3, 4, 5, 6, 8, 9};
    int b[4];
    combination(a, 6, 4, b, 4);
    return 0;
}
