/*
	Problem:	3349.cpp
	Time:		2020-03-16 22:05
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <iostream>
#include <cstdio>
#define i64 long long
using namespace std;
const int maxn = 17 + 5;

int bg[maxn], ne[maxn << 1], to[maxn << 1], e;
inline void add(int x, int y)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
}

template <typename T>
inline T read()
{
	T ans = 0, flag = 1;
	char c = getchar();
	while (!isdigit(c))
	{
		if (c == '-') flag = -1;
		c = getchar();
	}
	while (isdigit(c))
	{
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * flag;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

int n, m;
bool G[maxn][maxn], ban[maxn];
i64 dp[maxn][maxn];

void dfs(int x, int fa = 0)
{
	REP(i, 1, n) dp[x][i] = ban[i];
	for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa)
	{
		dfs(to[i], x);
		REP(j, 1, n) if (ban[j])
		{
			i64 sum = 0;
			REP(k, 1, n) sum += dp[to[i]][k] * (G[k][j] & ban[k]);
			dp[x][j] *= sum;
		}
	}
}

int main()
{
#ifdef CraZYali
	file("3349");
#endif
	n = read<int>();m = read<int>();
	while (m--)
	{
		int x(read<int>()), y(read<int>());
		G[x][y] = G[y][x] = 1;
	}
	REP(i, 2, n)
	{
		int x(read<int>()), y(read<int>());
		add(x, y);add(y, x);
	}
	i64 ans = 0;
	REP(S, 1, (1 << n) - 1)
	{
		REP(i, 1, n) ban[i] = (S >> i - 1) & 1;
		dfs(1);
		i64 res = 0;
		REP(i, 1, n) res += dp[1][i];
		if ((n - __builtin_popcount(S)) & 1) ans -= res;
		else ans += res;
	}
	cout << ans << '\n';
	return 0;
}
