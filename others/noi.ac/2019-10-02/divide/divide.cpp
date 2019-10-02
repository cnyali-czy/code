#define  REP(i, s, e) for (int i(s), end_##i(e); i <= end_##i; i++)
#define DREP(i, s, e) for (int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 50 + 5;

int n, m, x1, y1, x2, y2, p1, p2, a[maxn][maxn];

inline void fill(int x1, int y1, int x2, int y2, bool qaq)
{
	REP(i, x1, x2)
		REP(j, y1, y2) a[i][j] = qaq;
}

inline void output()
{
	if (p1)
		REP(i, 1, m)
			REP(j, 1, n)
			printf("%d%c", p2 ^ a[j][i], j == n ? '\n' : ' ');
	else
		REP(i, 1, n)
			REP(j, 1, m)
			printf("%d%c", p2 ^ a[i][j], j == m ? '\n' : ' ');
}

int main()
{
#ifdef CraZYali
	freopen("divide.in", "r", stdin);
	freopen("divide.out", "w", stdout);
#endif
	int T;
	cin >> T;
	while (T--)
	{
		scanf("%d%d%d%d%d%d",&n,&m,&x1,&y1,&x2,&y2);
		if (n * m % 2 == 1)
		{
			printf("-1\n");
			continue;
		}
		p1 = p2 = 0;
		if (m & 1)
		{
			p1 = 1;
			swap(n, m);
			swap(x1, y1);
			swap(x2, y2);
		}
		if (y1 > y2 || y1 == y2 && x1 > x2)
		{
			p2 = 1;
			swap(x1, x2);
			swap(y1, y2);
		}
		fill(1, 1, n, m / 2, 0);
		fill(1, m/2+1, n, m, 1);
		if (y1 <= m / 2 && m / 2 < y2)
		{
			output();
			continue;
		}
		if (n == 1)
		{
			printf("-1\n");
			continue;
		}
		if (y2 <= m / 2)
		{
			if (1<x2)
			{
				fill(x2, y2, n, m / 2, 1);
				fill(1, m / 2 + 1, n - x2 + 1, m - y2 + 1, 0);
			}
			else
			{
				fill(1, y2, x2, m/2, 1);
				fill(n-x2+1, m/2+1, n, m-y2+1, 0);
			}
			output();
			continue;
		}
		if (x1<n)
		{
			fill(1, m / 2 + 1, x1, y1, 0);
			fill(n - x1 + 1, m - y1 + 1, n, m / 2, 1);
		}
		else
		{
			fill(x1, m / 2 + 1, n, y1, 0);
			fill(1, m - y1 + 1, n - x1 + 1, m / 2, 1);
		}
		output();
	}
	return 0;
}
