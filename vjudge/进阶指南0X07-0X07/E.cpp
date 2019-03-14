#define  REP(i, s, e) for (int i = s; i <= e; i++)
#define DREP(i, s, e) for (int i = s; i >= e; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 100 + 5;

template <typename T> T read()
{
	T ans = 0, p = 1;
	char c = getchar();
	while (!isdigit(c))
	{
		if (c == '-') p = -1;
		c = getchar();
	}
	while (isdigit(c))
	{
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * p;
}

int n, a[maxn][maxn], sum[maxn][maxn], ans;

int main()
{
#ifdef CraZYali
	freopen("E.in", "r", stdin);
	freopen("E.out", "w", stdout);
#endif
	while (scanf("%d", &n) != EOF)
	{
		REP(i, 1, n)
			REP(j, 1, n) sum[i][j] = sum[i][j-1] + (a[i][j] = read<int>());
		ans = a[1][1];
		REP(i, 1, n)
			REP(j, 1, n) chkmax(ans, a[i][j]);
		REP(i, 1, n)
			REP(j, i, n)
			{
				//选取[i,j]列
				int ret = 0;
				REP(k, 1, n)
				{
					ret += sum[k][j] - sum[k][i-1];
					if (ret < 0) ret = 0;
					chkmax(ans, ret);
				}
			}
		printf("%d\n", ans);
	}
	return 0;
}
