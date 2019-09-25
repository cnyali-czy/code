#define  REP(i, s, e) for (register int i = (s), end_##i = (e); i <= end_##i; i++)
#define DREP(i, s, e) for (register int i = (s), end_##i = (e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, (b))
#define chkmin(a, b) a = min(a, (b))

#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <queue>

using namespace std;
const int maxn = 10000 + 10;

int bg[maxn], ne[maxn << 1], to[maxn << 1], w[maxn << 1], e;
inline void add(int x, int y, int z)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
	w[e] = z;
}

template <typename T> T read()
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

void file(string s)
{
	freopen((s + ".in").c_str(), "r", stdin);
	freopen((s + ".out").c_str(), "w", stdout);
}

int n, max_len, rt, dp[maxn];
inline void clear()
{
	e = 0;
	REP(i, 1, n) bg[i] = dp[i] = 0;
}

void dfs(int x, int fa, int len)
{
	if (len >= max_len)
	{
		rt = x;
		max_len = len;
	}
	for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa)
	{
		dfs(to[i], x, len + w[i]);
		chkmax(dp[to[i]], len + w[i]);
	}
}

int main()
{
#ifdef CraZYali
	file("2196");
#endif
	while (scanf("%d", &n) != EOF)
	{
		clear();
		REP(i, 2, n)
		{
			int fa(read<int>()), z(read<int>());
			add(fa, i, z);
			add(i, fa, z);
		}
		rt = 0;
		max_len = 0;
		dfs(1, -1, 0);
		dfs(rt, -1, 0);
		dfs(rt, -1, 0);
		REP(i, 1, n) printf("%d\n", dp[i]);
	}
	return 0;
}
