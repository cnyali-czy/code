#define DEBUG fprintf(stderr, "Passing [%s] in LINE %d\n", __FUNCTION__, __LINE__)
#define chkmin(a, b) a = min(a, b)
#define chkmax(a, b) a = max(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 12, maxm = 11;

int n, m, k;
int a[maxn], I, times, i, j, ok;
bool forbid[maxn][maxn], flag;

int main()
{
#ifdef CraZYali
	freopen("D.in", "r", stdin);
	freopen("D.out", "w", stdout);
#endif
	cin >> n >> m >> k;

	for (i = 1; i <= m; i++)
	{
		register int x , y;
		scanf("%d%d", &x, &y); 
		forbid[x][y] = forbid[y][x] = 1;
	}
	srand(n ^ k ^ m ^ 19260817);

	times = 2e6;
	for (I = 1; I <= times; I++)
	{
		for (i = 0 ; i < n ; i++) a[i] = i;
		for (i = 1 ; i <= k ; i++)
		{
			register int x = rand() % n;
			register int y = rand() % n;
			while (x == y) y = rand() % n;
			a[x] ^= a[y] ^= a[x] ^= a[y];
		}
		flag = 1;
		for (i = 0 ; i < n; i++)
			if (forbid[a[i]][a[(i == n - 1) ? 0 : i + 1]])
			{
				flag = 0;
				break;
			}
		ok += flag;
	}

	printf("%.8lf\n", ok * 1.0 / times);

	return 0;
}
