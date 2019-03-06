#define  REP(i, s, e) for (int i = s; i <= e; i++)
#define DREP(i, s, e) for (int i = s; i >= e; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 5000 + 5;

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

int sum[maxn][maxn],ans, n, R;

int main()
{
#ifdef CraZYali
	freopen("E.in", "r", stdin);
	freopen("E.out", "w", stdout);
#endif
	cin >> n >> R;
	REP(i, 1, n)
	{
		int x(read<int>() + 1), y(read<int>() + 1), v(read<int>());
		sum[x][y] += v;
	}
	REP(i, 1, 5001)
		REP(j, 1, 5001) sum[i][j] += sum[i-1][j] + sum[i][j-1] - sum[i-1][j-1];
	REP(i, 1, 5001 - R + 1)
		REP(j, 1, 5001 - R + 1)
		{
			int ret = sum[i+R-1][j+R-1] - sum[i+R-1][j-1] - sum[i-1][j+R-1] + sum[i-1][j-1];
			chkmax(ans, ret);
		}
	cout << ans << endl;
	return 0;
}
