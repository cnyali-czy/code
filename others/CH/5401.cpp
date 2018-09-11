#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 6000 + 10, maxm = maxn;

int bg[maxn], ne[maxm << 1], to[maxm << 1], e = 1;
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

int dp[maxn][2], v[maxn];
void dfs(int x, int fa = -1)
{
	dp[x][1] = v[x];
	for (register int i = bg[x]; i ; i = ne[i])
		if (to[i] ^ fa)
		{
			dfs(to[i], x);
			dp[x][0] += max(dp[to[i]][0], dp[to[i]][1]);
			dp[x][1] += dp[to[i]][0];
		}
}

int main()
{
#ifdef CraZYali
	freopen("5401.in", "r", stdin);
	freopen("5401.out", "w", stdout);
#endif
	while (scanf("%d", &n) * n)
	{
		REP(i, 1, n) scanf("%d", v + i), chkmax(v[i], 0);
		e = 1;
		REP(i, 1, n) bg[i] = dp[i][0] = 0;
		REP(i, 2, n)
		{
			register int x, y;
			scanf("%d%d", &x, &y);
			add(x, y);
			add(y, x);
		}
		dfs(1);
		printf("%d\n", max(dp[1][0], dp[1][1]));
	}
	return 0;
}
