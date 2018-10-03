#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 200 + 5, maxm = 200 + 5;

int bg[maxn], ne[maxn << 1], to[maxn << 1], e = 1;
inline void add(int x, int y)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
}

template <typename T> inline T read()
{
	T ans(0), p(1);
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

template <typename T> void write(T x)
{
	if (x < 0) putchar('-'), write(-x);
	else if (x / 10) write(x / 10);
	putchar(x % 10 + '0');
}

int m, n, k;
int val[maxn], fa;

int dp[maxn][maxm];

void dfs(int x, int left = m)
{
	dp[x][1] = val[x];
	for (register int i = bg[x]; i ; i = ne[i])
	{
		dfs(to[i], left - 1);
		DREP(j, left, 2)
			REP(k, 0, j - 1)
			chkmax(dp[x][j], dp[x][j - k] + dp[to[i]][k]);
	}
}

int main()
{
#ifdef CraZYali
	freopen("C.in", "r", stdin);
	freopen("C.out", "w", stdout);
#endif
	while (scanf("%d%d", &n, &m) * (n + m))
	{
		e = 0;
		REP(i, 1, n + 1) bg[i] = 0;
		REP(i, 1, n)
		{
			fa = read<int>();
			val[i] = read<int>();
			if (fa) add(fa, i);
			else add(n + 1, i);
		}
		n++;m++;
		REP(i, 1, n)
			REP(j, 1, m)
			dp[i][j] = 0;
		dfs(n);
		write(dp[n][m]);putchar(10);
	}

	return 0;
}
