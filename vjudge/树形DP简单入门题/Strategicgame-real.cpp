#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;
const int maxn = 1500 + 10, maxm = maxn, inf((((1 << 30) - 1) << 1) + 1);

int bg[maxn], ne[maxm << 1], to[maxm << 1], e = 1;
inline void add(int x, int y)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
}

int m, n, k, x;

int dp[maxn][2];
void dfs(int x, int fa)
{
	for (register int i = bg[x]; i ; i = ne[i]) if (to[i] ^ fa) dfs(to[i], x);
	dp[x][0] = 0;
	dp[x][1] = 1;
	for (register int i = bg[x]; i ; i = ne[i])
		if (to[i] ^ fa)
		{
			dp[x][0] += dp[to[i]][1];
			dp[x][1] += min(dp[to[i]][1], dp[to[i]][0]);
		}
}

int main()
{
#ifdef CraZYali
	freopen("Strategicgame.in", "r", stdin);
	freopen("Strategicgame.out", "w", stdout);
#endif
	while (scanf("%d", &n) != EOF)
	{
		e = 1;
		memset(bg, 0, sizeof(bg));
		
		REP(aksjdhfljkasdjkf, 1, n)
		{
			int i;
			scanf("%d:(%d)", &i, &k);
			i++;
			while (k --> 0)
			{
				scanf("%d", &x);
				x++;
				add(i, x);
				add(x, i);
			}
		}

		dfs(1, 1);
		printf("%d\n", min(dp[1][0], dp[1][1]));
	}
	return 0;
}
