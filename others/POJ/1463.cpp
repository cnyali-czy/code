/*
 * File Name:	1463.cpp
 * Author	:	CraZYali
 * Year		:	2019.09.26 23:07
 * Email	:	yms-chenziyang@outlook.com
 */

#define DREP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define  REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, (b))
#define chkmin(a, b) a = min(a, (b))

#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 1500 + 10, inf(2e3);

int bg[maxn], ne[maxn << 1], to[maxn << 1], e;
inline void add(int x, int y)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
}

int n;
inline void clear()
{
	REP(i, 1, n) bg[i] = 0;
	e = 0;
}

template <typename T> inline T read()
{
	T ans(0), flag(1);
	char c(getchar());
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

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout);

int dp[maxn][2];
void dfs(int x, int fa = -1)
{
	dp[x][0] = 0;
	dp[x][1] = 1;
	for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa)
	{
		dfs(to[i], x);
		dp[x][1] += min(dp[to[i]][1], dp[to[i]][0]);
		dp[x][0] += dp[to[i]][1];
	}
}

int main()
{
#ifdef CraZYali
	file("1463");
#endif
	while (scanf("%d", &n) != EOF)
	{
		clear();
		REP(i, 1, n)
		{
			int x, qaq;
			scanf("%d:(%d)", &x, &qaq);
			while (qaq--)
			{
				int y(read<int>());
				add(x + 1, y + 1);add(y + 1, x + 1);
			}
		}
		dfs(1);
		printf("%d\n", min(dp[1][0], dp[1][1]));
	}
	return 0;
}
